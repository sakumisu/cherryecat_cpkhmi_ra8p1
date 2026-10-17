/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hal_data.h"
#include "console.h"
#include <string.h>

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);

FSP_CPP_FOOTER

/* Linker symbols for the user DMA non-cacheable section defined in
 * script/fsp.lld. The section lives at the start of RAM (placed before
 * 'INCLUDE fsp_gen.lld' so that GNU LD's input-section matching wins over
 * fsp_gen.lld's __ram_zero$$ '*(.bss*)' wildcard). It is OUTSIDE the FSP
 * auto-managed MPU nocache range, so we configure an extra MPU region for
 * it ourselves below. It is also outside the BSP zero-init list, so we
 * zero it ourselves below. */
extern uint32_t __user_dma_nocache_start;
extern uint32_t __user_dma_nocache_end;

#if BSP_CFG_DCACHE_ENABLED

/* MPU region index used for the user DMA nocache range. The BSP allocates
 * regions 0..(g_init_info.nocache_count - 1) in bsp_init_mpu(); for this
 * project nocache_count == 4 (SDRAM, OSPI0_CS0, OSPI1_CS0, RAM). RA8T2
 * (Cortex-M85) provides 16 MPU regions, so index 4 is free. */
#define USER_DMA_NOCACHE_MPU_REGION    (4U)

/* MAIR attribute index 0 is configured as Normal/Non-Cacheable by the BSP
 * (see bsp_init_mpu() in system.c); reuse it here. */
#define USER_DMA_NOCACHE_MAIR_IDX      (0U)

#endif

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart (bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

#if BSP_CFG_OSPI_B_STARTUP_ENABLED && defined(BSP_CFG_OSPI_B_STARTUP_FN)
    if (BSP_WARM_START_POST_CLOCK == event)
    {
        /* Setup OSPI_B SiP flash and initialize it. */
        R_BSP_OspiBInit(BSP_CFG_OSPI_B_STARTUP_FN, true);
    }
#endif

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

#if BSP_CFG_DCACHE_ENABLED
        /* Install an extra MPU region marking the user DMA nocache section as
         * Normal/Non-Cacheable/Shareable. At this point bsp_init_mpu() has
         * already enabled the MPU and SCB_EnableDCache() has been called, so:
         *   1) Any speculative D-Cache fills for this range under the prior
         *      (default cacheable) mapping must be flushed/invalidated.
         *   2) After the MPU re-map, all subsequent accesses bypass D-Cache.
         *   3) Then we can safely zero-init the section without leaving stale
         *      cache lines that DMA wouldn't see.
         * ARMv8-M MPU regions have 32-byte granularity; the linker section is
         * ALIGN(32) at both ends. */
        {
            uint32_t base  = (uint32_t) &__user_dma_nocache_start;
            uint32_t limit = (uint32_t) &__user_dma_nocache_end;

            /* Clean+invalidate any cache lines currently shadowing this range
             * before we change the memory attributes. */
            SCB_CleanInvalidateDCache_by_Addr((void *) base, (int32_t) (limit - base));

            /* RBAR: base, Outer-Shareable, RW, privileged-or-not, XN.
             * RLAR: limit-32 (RLAR encodes inclusive last 32B unit), MAIR idx. */
            uint32_t rbar = ARM_MPU_RBAR(base, ARM_MPU_SH_OUTER, 0U, 1U, 1U);
            uint32_t rlar = ARM_MPU_RLAR(limit - 32U, USER_DMA_NOCACHE_MAIR_IDX);
            ARM_MPU_SetRegion(USER_DMA_NOCACHE_MPU_REGION, rbar, rlar);
            __DSB();
            __ISB();
        }
#endif

        /* Zero-initialize the user DMA non-cacheable section. It lives outside
         * the BSP zero-init list (g_init_info.p_zero_list[]) so the BSP
         * startup loop does not touch it. With D-Cache enabled this writes
         * straight through to memory because we just re-mapped the region as
         * Non-Cacheable above. With D-Cache disabled the memset is harmless. */
        {
            uint8_t * p_start = (uint8_t *) &__user_dma_nocache_start;
            uint8_t * p_end   = (uint8_t *) &__user_dma_nocache_end;
            memset(p_start, 0, (size_t) (p_end - p_start));
        }

        /* Configure pins. */
        R_IOPORT_Open(&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);

#if BSP_CFG_SDRAM_ENABLED

        /* Setup SDRAM and initialize it. Must configure pins first. */
        R_BSP_SdramInit(true);
#endif
        CONSOLE_Init();
    }
}
