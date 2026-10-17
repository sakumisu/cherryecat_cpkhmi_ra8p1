/*
 * r_rmac_phy_target_yt8512h.c
 *
 *  Created on: 2026年3月11日
 *      Author: Eli.Kang
 */


/* Access to peripherals and board defines. */
#include "bsp_api.h"
#include "r_rmac_phy.h"

#if (ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE)

#define RMAC_PHY_REG_PHY_RST_AN_OFFSET                 (0x09)
#define RMAC_PHY_REG_SPEED_SELECT1_OFFSET              (0x06)
#define RMAC_PHY_REG_SPEED_SELECT0_OFFSET              (0x0D)
#define RMAC_PHY_REG_BASIC_CONTROL                     (0x00)
#define RMAC_PHY_REG_BASIC_STATUS                      (0x01)
#define RMAC_PHY_REG_EXTEND_STATUS_OFFSET              (0x08)
#define RMAC_PHY_REG_DEBUG_REGISTER_ADDRESS_OFFSET      (0x1E)
#define RMAC_PHY_REG_DEBUG_REGISTER_DATA                (0x1F)

void rmac_phy_target_yt8512h_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
bool rmac_phy_target_yt8512h_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex);


void rmac_phy_target_yt8512h_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl)
{
    //LED0 control
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_DEBUG_REGISTER_ADDRESS_OFFSET, 0x40C0);
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_DEBUG_REGISTER_DATA, 0x0030);
    //LED1 control
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_DEBUG_REGISTER_ADDRESS_OFFSET, 0x40C3);
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_DEBUG_REGISTER_DATA, 0x0320);


//    uint32_t reg = 0;
//    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_BASIC_CONTROL, &reg);//read 0x00
//    if(reg != 0x2100) R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_BASIC_CONTROL, 0x2100 | 0x1000);

//    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_BASIC_STATUS, &reg);
//    if(reg & (1<<RMAC_PHY_REG_EXTEND_STATUS_OFFSET)) //Autoneg_Complete
//    {
//        R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_BASIC_CONTROL, &reg);//read 0x00
//        reg &= (uint32_t)(~(1<<RMAC_PHY_REG_SPEED_SELECT1_OFFSET | 1<<RMAC_PHY_REG_SPEED_SELECT0_OFFSET));
//        reg |= 1 << RMAC_PHY_REG_SPEED_SELECT0_OFFSET;
//        R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_BASIC_CONTROL, reg);
//
//        R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_BASIC_CONTROL, &reg);
//        reg |= 1 << RMAC_PHY_REG_PHY_RST_AN_OFFSET;
//        R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_BASIC_CONTROL, reg);
//    }
}

bool rmac_phy_target_yt8512h_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex)
{
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
    FSP_PARAMETER_NOT_USED(line_speed_duplex);

    /* This PHY-LSI supports half and full duplex mode. */
    return true;
}

#endif /* ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE */


