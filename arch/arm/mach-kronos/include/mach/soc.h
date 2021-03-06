/*
 * Copyright (C) 2014, Entropic Communications. All Rights Reserved
 * Author: Srinivas Rao L <srinivas.rao@entropic.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ARCH_KRONOS_H
#define __ARCH_KRONOS_H

#include <asm/sizes.h>
#include <mach/iomap.h>

#ifdef CONFIG_EXECUTE_ON_EMULATOR
#define SOC_CORTEX_FREQ           	(800 * 1000 * 1000)
#define SOC_PERIPHERALS_FREQ      	(SOC_CORTEX_FREQ / 2)
#else
#define SOC_CORTEX_FREQ			(get_arm_freq())
#define SOC_PERIPHERALS_FREQ   		(SOC_CORTEX_FREQ / 2)
#endif /* CONFIG_EXECUTE_ON_EMULATOR */

#ifdef CONFIG_EXECUTE_ON_EMULATOR
#define UART_CLOCK_RATE			(46293)  
#else
#define UART_CLOCK_RATE			(50000000)
#endif

#define MAX_TIMER			2
#define MAX_PERIOD			699050
#define TICKS_PER_uSEC			1

/* These are u_seconds NOT ticks */
#define mSEC_1				1000
#define mSEC_5				(mSEC_1 * 5)
#define mSEC_10				(mSEC_1 * 10)
#define mSEC_25				(mSEC_1 * 25)
#define SEC_1				(mSEC_1 * 1000)

/* SDRAM */
#define SOC_SDRAM_BASE		0x00000000

/* ChipID and Revision ID defines */
#define CHIPID_KRONOS			0x1

#define CHIP_REV_A			0x0
#define CHIP_REV_B			0x1

/* Bit [15] of the FUNCTION_CODE fuse field will identify Krome4K.
 * 1 = Krome4K. 0 = Not Krome4K 
 */
#define FUSE_REG_FUNCTION_CODE		__IOMEM(0xE06281DC)
#define FUSE_REG_KRONOS_4K_MASK		0x8000

/* Cortex A9 Internal Peripheral IP */
#define CORTEX_A9_PERIPHBASE		__IOMEM(0xE0100000)
#define CORTEX_A9_SCU_BASE		(CORTEX_A9_PERIPHBASE + 0x0000)
#define CORTEX_A9_INTC_BASE		(CORTEX_A9_PERIPHBASE + 0x0100)
#define CORTEX_A9_GLOB_TIMER_BASE	(CORTEX_A9_PERIPHBASE + 0x0200)
#define CORTEX_A9_PRIV_TIMER_BASE	(CORTEX_A9_PERIPHBASE + 0x0600)
#define CORTEX_A9_DISTR_BASE		(CORTEX_A9_PERIPHBASE + 0x1000)
#define CORTEX_A9_L2CACHE_BASE		(CORTEX_A9_PERIPHBASE + 0x2000)

/* MMIO Devices */
#define ARM_A9_HOST_MMIO_BASE			__IOMEM(0xE0600000)
#define HOST_ARM_MMIO_APERTURE			0x1FFFFF

/* DCS Network Controller */
#define DCS_AO_REGS_BASE      	(ARM_A9_HOST_MMIO_BASE + 0x0AD000)
#define DCS_HOST_REGS_BASE    	(ARM_A9_HOST_MMIO_BASE + 0x039000)
#define DCS_AVDSP_REGS_BASE  	(ARM_A9_HOST_MMIO_BASE + 0x103000)
#define DCS_FMVD_REGS_BASE    	(ARM_A9_HOST_MMIO_BASE + 0x1FF000)

/* Device port addresses */
#define SOC_MMIO_GCS_BASE	(ARM_A9_HOST_MMIO_BASE + 0x30000)
#define SOC_MMIO_SATA_BASE	(ARM_A9_HOST_MMIO_BASE + 0x38000)

#define SOC_MMIO_RGU_BASE       (ARM_A9_HOST_MMIO_BASE + 0xaf000)
#define  RST_GRESET0_REG        (SOC_MMIO_RGU_BASE + 0x0C)
#define   RST_GRESET0_IIC1      (1<<14)
#define   RST_GRESET0_IIC2      (1<<15)
#define   RST_GRESET0_IIC3      (1<<16)
#define  RST_GRESET1_REG        (SOC_MMIO_RGU_BASE + 0x10)
#define   RST_GRESET1_A9_CORE1  (1<<22)
#define   RST_GRESET1_IIC0      (1<<14)
#define   RST_GRESET1_SATA      (1 << 8)     /* SATA Reset - Active Low */

#define  RST_GRESET2_REG        (SOC_MMIO_RGU_BASE + 0x14)
#define   RST_GRESET2_IIC4      (1<<20)
#define  RST_LOCKCMD_REG        (SOC_MMIO_RGU_BASE + 0x28)
#define  RST_LOCKSTAT_REG       (SOC_MMIO_RGU_BASE + 0x2C)
#define   RST_LOCKSTAT_LOCK     (1 << 1)     /* 0 to unlock */


#define  RST_CONFIG_REG          	(SOC_MMIO_RGU_BASE + 0x30)
#define   PCI_HOST_MODE_ENABLED  	(((readl(RST_CONFIG_REG)&(1<<23)) &&   \
                                   	!(readl(RST_CONFIG_REG)&(1<<16)))?   \
                                  	true:false)

#define SOC_MMIO_CLOCK_BASE    		(ARM_A9_HOST_MMIO_BASE + 0x6a000)
#define SOC_MMIO_GLB_BASE            	(ARM_A9_HOST_MMIO_BASE + 0xbb000)
#define  GPIO_PIN_MUX_REG_0      	(SOC_MMIO_GLB_BASE + 0x100)
#define  GPIO_PIN_MUX_REG_1      	(SOC_MMIO_GLB_BASE + 0x104)
#define  GPIO_PIN_MUX_REG_2      	(SOC_MMIO_GLB_BASE + 0x108)
#define  GPIO_PIN_MUX_REG_3      	(SOC_MMIO_GLB_BASE + 0x10C)
#define  GPIO_PIN_MUX_REG_4      	(SOC_MMIO_GLB_BASE + 0x110)
#define  GPIO_PIN_MUX_REG_5      	(SOC_MMIO_GLB_BASE + 0x114)
#define  GPIO_PIN_MUX_REG_6      	(SOC_MMIO_GLB_BASE + 0x118)
#define  GPIO_SEC_PIN_MUX_REG_0 	(SOC_MMIO_GLB_BASE + 0x120)
#define  GPIO_SEC_PIN_MUX_REG_1  	(SOC_MMIO_GLB_BASE + 0x124)
#define  GPIO_SEC_PIN_MUX_REG_2  	(SOC_MMIO_GLB_BASE + 0x128)
#define  GPIO_SEC_PIN_MUX_REG_3  	(SOC_MMIO_GLB_BASE + 0x12C)
#define  GPIO_SEC_PIN_MUX_REG_4  	(SOC_MMIO_GLB_BASE + 0x130)
#define  GPIO_SEC_PIN_MUX_REG_5  	(SOC_MMIO_GLB_BASE + 0x134)
#define  GPIO_SEC_PIN_MUX_REG_6  	(SOC_MMIO_GLB_BASE + 0x138)
#define  ALT_PIN_MUX_REG_0       	(SOC_MMIO_GLB_BASE + 0x140)
#define  ALT_PIN_MUX_REG_1       	(SOC_MMIO_GLB_BASE + 0x144)
#define  ALT_PIN_MUX_REG_2       	(SOC_MMIO_GLB_BASE + 0x148)
#define  ALT_PIN_MUX_REG_2       	(SOC_MMIO_GLB_BASE + 0x148)
#define  HOST_CTL_REG            	(SOC_MMIO_GLB_BASE + 0x308)
#define   HOST_VINITHI_CPU1      	(1<<9)
#define  PAD_CONFIGURATION_0_REG 	(SOC_MMIO_GLB_BASE + 0x430)
#define  PAD_CONFIGURATION_5_REG 	(SOC_MMIO_GLB_BASE + 0x44C)
#define  GLBREG_MISC1            	(SOC_MMIO_GLB_BASE + 0x500)
#define  GLOBALREG_MODULE_ID_REG 	(SOC_MMIO_GLB_BASE + 0xffc)

#define SCRATCH_REG_OFFSET       	(0x8C000)
#define SCRATCHPAD_REG_BASE         (ARM_A9_HOST_MMIO_BASE + SCRATCH_REG_OFFSET)

/* 32bit writable and readable register. They are not 
 * supposed to be reset, so that their values survive 
 * a reset and allow passing of info through a reset.*/
#define SCRATCHPAD_REG(n)           	(SCRATCHPAD_REG_BASE + ((n)*4))
#define  SCRATCH_REG_CPU_PEN        	(SCRATCHPAD_REG(20))
#define   PRIMARY_CPU_HOLDING_PEN   	(0xCAFEBABE)
#define   SECONDARY_CPU_HOLDING_PEN 	(0xCAFED00D)

#define UART1_PORT0_OFFSET		0xb2000
#define UART2_PORT1_OFFSET		0xb3000
#define UART3_PORT2_OFFSET		0xb4000
#define USB_PORT0_OFFSET		0x6C000
#define USB_PORT1_OFFSET		0x6D000
#define GPIO_PORT0_OFFSET		0x69000
#define PCI_PORT0_OFFSET		0x2F000

/* MMIO device addresses */
#define SOC_MMIO_UART1_BASE		(ARM_A9_HOST_MMIO_BASE + UART1_PORT0_OFFSET)
#define SOC_MMIO_UART2_BASE		(ARM_A9_HOST_MMIO_BASE + UART2_PORT1_OFFSET)
#define SOC_MMIO_UART3_BASE		(ARM_A9_HOST_MMIO_BASE + UART3_PORT2_OFFSET)
#define SOC_MMIO_USB_PORT0		(ARM_A9_HOST_MMIO_BASE + USB_PORT0_OFFSET)
#define SOC_MMIO_USB_PORT1		(ARM_A9_HOST_MMIO_BASE + USB_PORT1_OFFSET)
#define SOC_MMIO_GPIO_PORT0		(ARM_A9_HOST_MMIO_BASE + GPIO_PORT0_OFFSET)
#define SOC_MMIO_PCI_PORT0		(ARM_A9_HOST_MMIO_BASE + PCI_PORT0_OFFSET)

/* DEVICE NAMES TO BE USED */
#define IP3106_UART_PORT_0		(SOC_MMIO_UART1_BASE)
#define IP3106_UART_PORT_1		(SOC_MMIO_UART2_BASE)
#define IP3106_UART_PORT_2		(SOC_MMIO_UART3_BASE)
//#define IP3106_UART_PORT_3		(SOC_MMIO_UART3_BASE)
#define SOC_UART_MMIO_SIZE		(0x1000)

#define IP9028_USB_PORT_0		SOC_MMIO_USB_PORT0
#define IP9028_USB_PORT_1		SOC_MMIO_USB_PORT1
#define IPXXXX_GPIO_PORT_0		SOC_MMIO_GPIO_PORT0
#define IPA051_PCI_PORT_0		SOC_MMIO_PCI_PORT0

#define SOC_GMAC0_BASE			(ARM_A9_HOST_MMIO_BASE + 0x7c000)
#define SOC_GMAC0_CTRL_REG		(SOC_MMIO_GLB_BASE + 0x300)
#define SOC_GMAC1_BASE			(ARM_A9_HOST_MMIO_BASE + 0xa4000)
#define SOC_GMAC1_CTRL_REG		(SOC_MMIO_GLB_BASE + 0x304)

/* GMAC0 Clock Registers */
#define SOC_CLK_GMAC0_AHBCLK     	(SOC_MMIO_CLOCK_BASE + 0x03C0)
#define SOC_CLK_GMAC0_AHBCLK_MASK       0x00000006
#define SOC_CLK_GMAC0_PHY_TX     	(SOC_MMIO_CLOCK_BASE + 0x03C4)
#define SOC_CLK_GMAC0_PHY_RX     	(SOC_MMIO_CLOCK_BASE + 0x03C8)
#define SOC_CLK_GMAC0_RMII       	(SOC_MMIO_CLOCK_BASE + 0x03CC)
#define SOC_CLK_GMAC0_TXCLK_OUT  	(SOC_MMIO_CLOCK_BASE + 0x03D0)
/* GMAC1 Clock Registers */
#define SOC_CLK_GMAC1_AHBCLK     	(SOC_MMIO_CLOCK_BASE + 0x03D4)
#define SOC_CLK_GMAC1_PHY_TX     	(SOC_MMIO_CLOCK_BASE + 0x03D8)
#define SOC_CLK_GMAC1_PHY_RX     	(SOC_MMIO_CLOCK_BASE + 0x03DC)
#define SOC_CLK_GMAC1_RMII       	(SOC_MMIO_CLOCK_BASE + 0x03E0)
#define SOC_CLK_GMAC1_TXCLK_OUT  	(SOC_MMIO_CLOCK_BASE + 0x03E4)

/* GPIO registers */
#define GPIO_0_15_MODE_CTL0		*(volatile unsigned long *)(IPXXXX_GPIO_PORT_0 + 0x000)

/* Cortex A9 Registers */
#define SOC_RESET_BASE			(ARM_A9_HOST_MMIO_BASE + 0xaf000)
#define SOC_RESET_LOCKCMD		(SOC_RESET_BASE + 0x28)
#define SOC_RESET_LOCKSTAT		(SOC_RESET_BASE + 0x2c)
#define SOC_RESET_SOFTRESET		(SOC_RESET_BASE + 0x08)

/* RTC */
#define SOC_RTC_BASE			(ARM_A9_HOST_MMIO_BASE + 0x8b000)

#endif /* __ARCH_KRONOS_H */
