/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_NUM_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
            [1] = layer3_switch_gwdi_isr, /* ETHER GWDI0 (GWCA Data Interrupt 0) */
            [2] = layer3_switch_eaei_isr, /* ETHER EAEI0 (ETHA0 Error Interrupt) */
            [3] = layer3_switch_eaei_isr, /* ETHER EAEI1 (ETHA1 Error Interrupt) */
            [4] = sci_b_uart_rxi_isr, /* SCI9 RXI (Receive data full) */
            [5] = sci_b_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [6] = sci_b_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [7] = sci_b_uart_eri_isr, /* SCI9 ERI (Receive error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_NUM_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_GPT0_COUNTER_OVERFLOW,GROUP0), /* GPT0 COUNTER OVERFLOW (Overflow) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_ETHER_GWDI0,GROUP1), /* ETHER GWDI0 (GWCA Data Interrupt 0) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_ETHER_EAEI0,GROUP2), /* ETHER EAEI0 (ETHA0 Error Interrupt) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_ETHER_EAEI1,GROUP3), /* ETHER EAEI1 (ETHA1 Error Interrupt) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_SCI9_RXI,GROUP4), /* SCI9 RXI (Receive data full) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TXI,GROUP5), /* SCI9 TXI (Transmit data empty) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TEI,GROUP6), /* SCI9 TEI (Transmit end) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI9_ERI,GROUP7), /* SCI9 ERI (Receive error) */
        };
        #endif
        #endif
