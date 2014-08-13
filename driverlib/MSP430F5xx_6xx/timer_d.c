/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
//
//timer_d.c - Driver for the TIMER Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "assert.h"
#include "timer_d.h"
#include "tlv.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif

static void privateTimerDProcessClockSourceDivider (uint32_t baseAddress,
    uint16_t clockSourceDivider);

//*****************************************************************************
//
//! Starts TimerD counter
//!
//! \param baseAddress is the base address of the TimerA module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CONTINUOUS_MODE [Default value]
//!         \b TIMER_D_UPDOWN_MODE
//!         \b TIMER_D_UP_MODE
//! Modified register is \b TDxCTL0
//!
//!NOTE: This function assumes that the timer has been previously configured
//! using TIMER_D_configureContinuousMode,  TIMER_D_configureUpMode or
//!TIMER_D_configureUpDownMode.
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_startCounter ( uint32_t baseAddress,
    uint16_t timerMode
    )
{
    assert(
        (TIMER_D_UPDOWN_MODE == timerMode) ||
        (TIMER_D_CONTINUOUS_MODE == timerMode) ||
        (TIMER_D_UP_MODE == timerMode)
         );


    HWREG16(baseAddress + OFS_TDxCTL0) |= timerMode;
}
//*****************************************************************************
//
//! Configures timer in continuous mode.
//!
//! \param baseAddress is the base address of the Timer module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK [Default value]
//!         \b TIMER_D_CLOCKSOURCE_ACLK
//!         \b TIMER_D_CLOCKSOURCE_SMCLK
//!         \b TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK
//! \param clockSourceDivider is the divider for Clock source.
//! 	Valid values are
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_64
//! \param clockingMode is the selected clock mode register values.
//! Valid values are
//!     \b TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK [Default value]
//!     \b TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK
//!	\b TIMER_D_CLOCKINGMODE_AUXILIARY_CLK
//! \param timerInterruptEnable_TDIE is to enable or disable timer interrupt
//!        Valid values are
//!        \b TIMER_D_TDIE_INTERRUPT_ENABLE
//!        \b TIMER_D_TDIE_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if timer clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_D_DO_CLEAR
//!        \b TIMER_D_SKIP_CLEAR [Default value]
//!
//! Modified registers are \b TDxCTL0 and \b TDxCTL1
//!
//!This API does not start the timer. Timer needs to be started when required
//!using the TIMER_D_start API.
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_configureContinuousMode ( uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t clockingMode,
    uint16_t timerInterruptEnable_TDIE,
    uint16_t timerClear
    )
{
    
    assert(
        (TIMER_D_DO_CLEAR == timerClear) ||
        (TIMER_D_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_D_TDIE_INTERRUPT_ENABLE == timerInterruptEnable_TDIE) ||
        (TIMER_D_TDIE_INTERRUPT_DISABLE == timerInterruptEnable_TDIE)
        );
    
    assert(
        (TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK == clockSource)
        );


    assert(
        (TIMER_D_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );

    assert(
        (TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_AUXILIARY_CLK == clockingMode)
        );

    HWREG16(baseAddress +
        OFS_TDxCTL0) &= ~(TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK +
        				 TIMER_D_UPDOWN_MODE +
                         TIMER_D_DO_CLEAR +
                         TIMER_D_TDIE_INTERRUPT_ENABLE
                         );

    HWREG16(baseAddress + OFS_TDxCTL1)  &= ~(TDCLKM0 + TDCLKM1);
    
    privateTimerDProcessClockSourceDivider(baseAddress,
    		        clockSourceDivider
    		        );
    HWREG16(baseAddress + OFS_TDxCTL0)  |=  clockSource;
    HWREG16(baseAddress + OFS_TDxCTL1) |= clockingMode;
  
    HWREG16(baseAddress + OFS_TDxCTL0)  |= (  
											timerClear +
        	                                timerInterruptEnable_TDIE
											);

}
//*****************************************************************************
//
//! Configures timer in up mode.
//!
//! \param baseAddress is the base address of the Timer module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK [Default value]
//!         \b TIMER_D_CLOCKSOURCE_ACLK
//!         \b TIMER_D_CLOCKSOURCE_SMCLK
//!         \b TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK
//! \param clockSourceDivider is the divider for Clock source.
//! 	Valid values are
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_64
//! \param clockingMode is the selected clock mode register values.
//! Valid values are
//!     \b TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK [Default value]
//!     \b TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK
//!	\b TIMER_D_CLOCKINGMODE_AUXILIARY_CLK
//! \param timerPeriod is the specified timer period. This is the value that gets
//!         written into the CCR0. Limited to 16 bits[uint16_t]
//! \param timerInterruptEnable_TDIE is to enable or disable timer interrupt
//!        Valid values are
//!        \b TIMER_D_TDIE_INTERRUPT_ENABLE and
//!        \b TIMER_D_TDIE_INTERRUPT_DISABLE [Default value]
//! \param captureCompareInterruptEnable_CCR0_CCIE is to enable or disable
//!         timer CCR0 captureComapre interrupt. Valid values are
//!        \b TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE and
//!        \b TIMER_D_CCIE_CCR0_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if timer clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_D_DO_CLEAR
//!        \b TIMER_D_SKIP_CLEAR [Default value]
//!
//! Modified registers are  \b TDxCTL0, \b TDxCTL1,\b TDxCCR0, \b TDxCCTL0
//!
//!This API does not start the timer. Timer needs to be started when required
//!using the TIMER_D_start API.
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_configureUpMode (   uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t clockingMode,
    uint16_t timerPeriod,
    uint16_t timerInterruptEnable_TDIE,
    uint16_t captureCompareInterruptEnable_CCR0_CCIE,
    uint16_t timerClear
    )
{

    assert(
        (TIMER_D_DO_CLEAR == timerClear) ||
        (TIMER_D_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK == clockSource)
        );


    assert(
        (TIMER_D_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );

    assert(
        (TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_AUXILIARY_CLK == clockingMode)
        );

    HWREG16(baseAddress + OFS_TDxCTL0) &=
        ~(TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK +
          TIMER_D_UPDOWN_MODE +
          TIMER_D_DO_CLEAR +
          TIMER_D_TDIE_INTERRUPT_ENABLE
          );

    HWREG16(baseAddress + OFS_TDxCTL1)  &= ~(TDCLKM0 + TDCLKM1);

    privateTimerDProcessClockSourceDivider(baseAddress,
    		        clockSourceDivider
    		        );
    HWREG16(baseAddress + OFS_TDxCTL0)  |=  clockSource;
    HWREG16(baseAddress + OFS_TDxCTL1) |= clockingMode;

    HWREG16(baseAddress + OFS_TDxCTL0)  |= ( TIMER_D_STOP_MODE +
                                          timerClear +
                                          timerInterruptEnable_TDIE
                                          );

    if (TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE ==
        captureCompareInterruptEnable_CCR0_CCIE){
        HWREG16(baseAddress + OFS_TDxCCTL0)  |= TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE;
    } else   {
        HWREG16(baseAddress + OFS_TDxCCTL0)  &= ~TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE;
    }

    HWREG16(baseAddress + OFS_TDxCCR0)  = timerPeriod;
}

//*****************************************************************************
//
//! Configures timer in up down mode.
//!
//! \param baseAddress is the base address of the Timer module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK [Default value]
//!         \b TIMER_D_CLOCKSOURCE_ACLK
//!         \b TIMER_D_CLOCKSOURCE_SMCLK
//!         \b TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK
//! \param clockSourceDivider is the divider for Clock source.
//! 	Valid values are
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_64
//! \param clockingMode is the selected clock mode register values.
//! Valid values are
//!     \b TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK [Default value]
//!     \b TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK
//!	\b TIMER_D_CLOCKINGMODE_AUXILIARY_CLK
//! \param timerPeriod is the specified timer period
//! \param timerInterruptEnable_TDIE is to enable or disable timer interrupt
//!        Valid values are
//!        \b TIMER_D_TDIE_INTERRUPT_ENABLE
//!        \b TIMER_D_TDIE_INTERRUPT_DISABLE [Default value]
//! \param captureCompareInterruptEnable_CCR0_CCIE is to enable or disable
//!         timer CCR0 captureComapre interrupt. Valid values are
//!        \b TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE and
//!        \b TIMER_D_CCIE_CCR0_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if timer clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_D_DO_CLEAR
//!        \b TIMER_D_SKIP_CLEAR [Default value]
//!
//! Modified registers are  \b TDxCTL0, \b TDxCTL1, \b TDxCCR0, \b TDxCCTL0
//!
//!This API does not start the timer. Timer needs to be started when required
//!using the TIMER_D_start API.
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_configureUpDownMode (
    uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t clockingMode,
    uint16_t timerPeriod,
    uint16_t timerInterruptEnable_TDIE,
    uint16_t captureCompareInterruptEnable_CCR0_CCIE,
    uint16_t timerClear
    )
{
	
    assert(
        (TIMER_D_DO_CLEAR == timerClear) ||
        (TIMER_D_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK == clockSource)
        );


    assert(
        (TIMER_D_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );

    assert(
        (TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_AUXILIARY_CLK == clockingMode)
        );

    HWREG16(baseAddress + OFS_TDxCTL0) &=
        ~(TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK +
          TIMER_D_UPDOWN_MODE +
          TIMER_D_DO_CLEAR +
          TIMER_D_TDIE_INTERRUPT_ENABLE
          );

    HWREG16(baseAddress + OFS_TDxCTL1)  &= ~(TDCLKM0 + TDCLKM1);

    privateTimerDProcessClockSourceDivider(baseAddress,
    		        clockSourceDivider
    		        );
    HWREG16(baseAddress + OFS_TDxCTL0)  |=  clockSource;
    HWREG16(baseAddress + OFS_TDxCTL1) |= clockingMode;

    HWREG16(baseAddress + OFS_TDxCTL0)  |= ( TIMER_D_STOP_MODE +
                                          timerClear +
                                          timerInterruptEnable_TDIE
                                          );
    if (TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE ==
        captureCompareInterruptEnable_CCR0_CCIE){
        HWREG16(baseAddress + OFS_TDxCCTL0)  |= TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE;
    } else   {
        HWREG16(baseAddress + OFS_TDxCCTL0)  &= ~TIMER_D_CCIE_CCR0_INTERRUPT_ENABLE;
    }

    HWREG16(baseAddress + OFS_TDxCCR0)  = timerPeriod;
}


//*****************************************************************************
//
//! Initializes Capture Mode
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param captureMode is the capture mode selected. Valid values are
//!        \b TIMER_D_CAPTUREMODE_NO_CAPTURE [Default value]
//!        \b TIMER_D_CAPTUREMODE_RISING_EDGE
//!        \b TIMER_D_CAPTUREMODE_FALLING_EDGE
//!        \b TIMER_D_CAPTUREMODE_RISING_AND_FALLING_EDGE
//! \param captureInputSelect decides the Input Select
//!        \b TIMER_D_CAPTURE_INPUTSELECT_CCIxA [Default value]
//!        \b TIMER_D_CAPTURE_INPUTSELECT_CCIxB
//!        \b TIMER_D_CAPTURE_INPUTSELECT_GND
//!        \b TIMER_D_CAPTURE_INPUTSELECT_Vcc
//! \param synchronizeCaptureSource decides if capture source should be
//!         synchronized with timer clock
//!        Valid values are
//!        \b TIMER_D_CAPTURE_ASYNCHRONOUS [Default value]
//!        \b TIMER_D_CAPTURE_SYNCHRONOUS
//! \param captureInterruptEnable is to enable or disable
//!         timer captureComapre interrupt. Valid values are
//!        \b TIMER_D_CAPTURECOMPARE_INTERRUPT_DISABLE [Default value]
//!        \b TIMER_D_CAPTURECOMPARE_INTERRUPT_ENABLE
//! \param captureOutputMode specifies the output mode. Valid values are
//!        \b TIMER_D_OUTPUTMODE_OUTBITVALUE [Default value],
//!        \b TIMER_D_OUTPUTMODE_SET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_D_OUTPUTMODE_SET_RESET
//!        \b TIMER_D_OUTPUTMODE_TOGGLE,
//!        \b TIMER_D_OUTPUTMODE_RESET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_D_OUTPUTMODE_RESET_SET
//! \param channelCaptureMode specifies single/dual capture mode.
//!		Valid values are
//!        \b TIMER_D_SINGLE_CAPTURE_MODE [Default value],
//!        \b TIMER_D_DUAL_CAPTURE_MODE
//!
//! Modified registers are \b TDxCTL2, \b TDxCCTLn
//! \return None
//
//*****************************************************************************
void TIMER_D_initCapture (uint32_t baseAddress,
    uint16_t captureRegister,
    uint16_t captureMode,
    uint16_t captureInputSelect,
    unsigned short synchronizeCaptureSource,
    unsigned short captureInterruptEnable,
    uint16_t captureOutputMode,
    uint8_t channelCaptureMode
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureRegister) 
        );

    assert((TIMER_D_CAPTUREMODE_NO_CAPTURE == captureMode) ||
        (TIMER_D_CAPTUREMODE_RISING_EDGE == captureMode) ||
        (TIMER_D_CAPTUREMODE_FALLING_EDGE == captureMode) ||
        (TIMER_D_CAPTUREMODE_RISING_AND_FALLING_EDGE == captureMode)
        );

    assert((TIMER_D_CAPTURE_INPUTSELECT_CCIxA == captureInputSelect) ||
        (TIMER_D_CAPTURE_INPUTSELECT_CCIxB == captureInputSelect) ||
        (TIMER_D_CAPTURE_INPUTSELECT_GND == captureInputSelect) ||
        (TIMER_D_CAPTURE_INPUTSELECT_Vcc == captureInputSelect)
        );

    assert((TIMER_D_CAPTURE_ASYNCHRONOUS == synchronizeCaptureSource) ||
        (TIMER_D_CAPTURE_SYNCHRONOUS == synchronizeCaptureSource)
        );

    assert(
        (TIMER_D_CAPTURECOMPARE_INTERRUPT_DISABLE == captureInterruptEnable) ||
        (TIMER_D_CAPTURECOMPARE_INTERRUPT_ENABLE == captureInterruptEnable)
        );

    assert((TIMER_D_OUTPUTMODE_OUTBITVALUE == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_SET == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE_RESET == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_SET_RESET == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_RESET == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE_SET == captureOutputMode) ||
        (TIMER_D_OUTPUTMODE_RESET_SET == captureOutputMode)
        );

    assert((TIMER_D_SINGLE_CAPTURE_MODE == channelCaptureMode) ||
            (TIMER_D_DUAL_CAPTURE_MODE == channelCaptureMode)
            );

    if (TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureRegister){
        //CaptureCompare register 0 only supports certain modes
        assert((TIMER_D_OUTPUTMODE_OUTBITVALUE == captureOutputMode) ||
            (TIMER_D_OUTPUTMODE_SET == captureOutputMode) ||
            (TIMER_D_OUTPUTMODE_TOGGLE == captureOutputMode) ||
            (TIMER_D_OUTPUTMODE_RESET == captureOutputMode) 
            );
    }

    HWREG16(baseAddress + captureRegister ) |=   CAP;

    HWREG8(baseAddress + OFS_TDxCTL2) |=
    		(channelCaptureMode << ((captureRegister - TIMER_D_CAPTURECOMPARE_REGISTER_0)/6));

    HWREG16(baseAddress + captureRegister) &=
        ~(TIMER_D_CAPTUREMODE_RISING_AND_FALLING_EDGE +
          TIMER_D_CAPTURE_INPUTSELECT_Vcc +
          TIMER_D_CAPTURE_SYNCHRONOUS +
          TIMER_D_DO_CLEAR +
          TIMER_D_TDIE_INTERRUPT_ENABLE +
          CM_3
          );

    HWREG16(baseAddress + captureRegister)  |= (captureMode +
                                              captureInputSelect +
                                              synchronizeCaptureSource +
                                              captureInterruptEnable +
                                              captureOutputMode
                                              );
}

//*****************************************************************************
//
//! Initializes Compare Mode
//!
//! \param baseAddress is the base address of the Timer module.
//! \param compareRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param compareInterruptEnable is to enable or disable
//!         timer captureComapre interrupt. Valid values are
//!        \b TIMER_D_CAPTURECOMPARE_INTERRUPT_ENABLE and
//!        \b TIMER_D_CAPTURECOMPARE_INTERRUPT_DISABLE [Default value]
//! \param compareOutputMode specifies the ouput mode. Valid values are
//!        \b TIMER_D_OUTPUTMODE_OUTBITVALUE [Default value],
//!        \b TIMER_D_OUTPUTMODE_SET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_D_OUTPUTMODE_SET_RESET
//!        \b TIMER_D_OUTPUTMODE_TOGGLE,
//!        \b TIMER_D_OUTPUTMODE_RESET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_D_OUTPUTMODE_RESET_SET
//! \param compareValue is the count to be compared with in compare mode
//!
//! Modified register is \b TDxCCTLn and \b TDxCCRn
//! \return None
//
//*****************************************************************************
void TIMER_D_initCompare (  uint32_t baseAddress,
    uint16_t compareRegister,
    unsigned short compareInterruptEnable,
    uint16_t compareOutputMode,
    uint16_t compareValue
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == compareRegister) 
        );

   assert((TIMER_D_CAPTURECOMPARE_INTERRUPT_ENABLE == compareInterruptEnable) ||
        (TIMER_D_CAPTURECOMPARE_INTERRUPT_DISABLE == compareInterruptEnable)
        );

    assert((TIMER_D_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_SET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE_RESET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_SET_RESET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_RESET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE_SET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_RESET_SET == compareOutputMode)
        );

    if (TIMER_D_CAPTURECOMPARE_REGISTER_0 == compareRegister){
        //CaptureCompare register 0 only supports certain modes
        assert((TIMER_D_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
            (TIMER_D_OUTPUTMODE_SET == compareOutputMode) ||
            (TIMER_D_OUTPUTMODE_TOGGLE == compareOutputMode) ||
            (TIMER_D_OUTPUTMODE_RESET == compareOutputMode) 
            );
    }


    HWREG16(baseAddress + compareRegister ) &=   ~CAP;

    HWREG16(baseAddress + compareRegister) &=
        ~(TIMER_D_CAPTURECOMPARE_INTERRUPT_ENABLE +
          TIMER_D_OUTPUTMODE_RESET_SET
          );

    HWREG16(baseAddress + compareRegister)  |= ( compareInterruptEnable +
                                               compareOutputMode
                                               );

    HWREG16(baseAddress + compareRegister + 2) = compareValue;
}

//*****************************************************************************
//
//! Enable timer interrupt
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified register is TDxCTL0
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_enableTimerInterrupt (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_TDxCTL0) &=  ~TDIFG;
    HWREG8(baseAddress + OFS_TDxCTL0) |= TDIE;
}

//*****************************************************************************
//
//! Enable High Resolution interrupt
//!
//! \param baseAddress is the base address of the Timer module.
//! \param mask is the mask for the interrupt status
//!         Valid values is an OR of
//!         \b TIMER_D_HIGH_RES_FREQUENCY_UNLOCK,
//!         \b TIMER_D_HIGH_RES_FREQUENCY_LOCK
//!         \b TIMER_D_HIGH_RES_FAIL_HIGH,
//!         \b TIMER_D_HIGH_RES_FAIL_LOW
//!
//! Modified register is TDxHINT
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_enableHighResInterrupt (uint32_t baseAddress,
				uint16_t mask)
{
    HWREG16(baseAddress + OFS_TDxHINT) &=  ~(mask >> 8);
    HWREG16(baseAddress + OFS_TDxHINT) |= mask;
}

//*****************************************************************************
//
//! Disable timer interrupt
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified register is \b TDxCTL0
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_disableTimerInterrupt (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_TDxCTL0) &= ~TDIE;
}

//*****************************************************************************
//
//! Disable High Resolution interrupt
//!
//! \param baseAddress is the base address of the Timer module.
//! \param mask is the mask for the interrupt status
//!         Valid values is an OR of
//!         \b TIMER_D_HIGH_RES_FREQUENCY_UNLOCK,
//!         \b TIMER_D_HIGH_RES_FREQUENCY_LOCK
//!         \b TIMER_D_HIGH_RES_FAIL_HIGH,
//!         \b TIMER_D_HIGH_RES_FAIL_LOW
//!
//! Modified register is TDxHINT
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_disableHighResInterrupt (uint32_t baseAddress,
						uint16_t mask)
{
    HWREG16(baseAddress + OFS_TDxHINT) &= ~mask;
}
//*****************************************************************************
//
//! Get timer interrupt status
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! \return uint8_t. Return interrupt status. Valid values are
//!         \b TIMER_D_INTERRUPT_PENDING
//!         \b TIMER_D_INTERRUPT_NOT_PENDING
//
//*****************************************************************************
uint32_t TIMER_D_getTimerInterruptStatus (uint32_t baseAddress)
{
    return ( HWREG8(baseAddress + OFS_TDxCTL0) & TDIFG );
}

//*****************************************************************************
//
//! Enable capture compare interrupt
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister is the selected capture compare regsiter
//!
//! Modified register is \b TDxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_enableCaptureCompareInterrupt (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    HWREG8(baseAddress + captureCompareRegister) &= ~CCIFG;
    HWREG16(baseAddress + captureCompareRegister) |= CCIE;
}

//*****************************************************************************
//
//! Disable capture compare interrupt
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister is the selected capture compare regsiter
//!
//! Modified register is \b TDxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_disableCaptureCompareInterrupt (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );
    HWREG16(baseAddress + captureCompareRegister) &= ~CCIE;
}

//*****************************************************************************
//
//! Return capture compare interrupt status
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister is the selected capture compare register
//! \param mask is the mask for the interrupt status
//!         Valid values is an OR of
//!         \b TIMER_D_CAPTURE_OVERFLOW,
//!         \b TIMER_D_CAPTURECOMPARE_INTERRUPT_FLAG
//!
//! \returns uint32_t. The mask of the set flags.
//! Modifed Registers None
//
//*****************************************************************************
uint32_t TIMER_D_getCaptureCompareInterruptStatus (uint32_t baseAddress,
	    uint16_t captureCompareRegister,
	    uint16_t mask
	    )
{
	return ( HWREG16(baseAddress + captureCompareRegister) & mask );
}

//*****************************************************************************
//
//! Returns High Resolution interrupt status
//!
//! \param baseAddress is the base address of the Timer module.
//! \param mask is the mask for the interrupt status
//!         Valid values is an OR of
//!         \b TIMER_D_HIGH_RES_FREQUENCY_UNLOCK,
//!         \b TIMER_D_HIGH_RES_FREQUENCY_LOCK
//!         \b TIMER_D_HIGH_RES_FAIL_HIGH,
//!         \b TIMER_D_HIGH_RES_FAIL_LOW
//!
//! Modified register is \b TDxHINT
//!
//! \returns uint32_t. The mask of the set flags.
//
//*****************************************************************************
uint16_t TIMER_D_getHighResInterruptStatus (uint32_t baseAddress,
    uint16_t mask)
{
	mask = (mask >> 8);
    return ( (HWREG16(baseAddress + OFS_TDxHINT) & mask) << 8 );
}
//*****************************************************************************
//
//! Reset/Clear the timer clock divider, count direction, count
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified register is \b TDxCTL0
//!
//! \returns None
//
//*****************************************************************************
void TIMER_D_clear (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxCTL0) |= TDCLR;
}
//*****************************************************************************
//
//! Clears High Resolution interrupt status
//!
//! \param baseAddress is the base address of the Timer module.
//! \param mask is the mask for the interrupt status
//!         Valid values is an OR of
//!         \b TIMER_D_HIGH_RES_FREQUENCY_UNLOCK,
//!         \b TIMER_D_HIGH_RES_FREQUENCY_LOCK
//!         \b TIMER_D_HIGH_RES_FAIL_HIGH,
//!         \b TIMER_D_HIGH_RES_FAIL_LOW
//!
//! Modified register is \b TDxHINT
//!
//! \returns none
//
//*****************************************************************************
void TIMER_D_clearHighResInterruptStatus (uint32_t baseAddress,
    uint16_t mask)
{
	mask = (mask >> 8);
	HWREG16(baseAddress + OFS_TDxHINT) &= ~mask;
}

//*****************************************************************************
//
//! Get synchrnozied capturecompare input
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param synchronized is to select type of capture compare input.
//!         Valid values are
//!        \b TIMER_D_READ_CAPTURE_COMPARE_INPUT
//!        \b TIMER_D_READ_SYNCHRONIZED_CAPTURECOMPAREINPUT
//!
//! \return \b TIMER_D_CAPTURECOMPARE_INPUT_HIGH or
//!         \b TIMER_D_CAPTURECOMPARE_INPUT_LOW
//! Modifed Registers None
//
//*****************************************************************************
unsigned short TIMER_D_getSynchronizedCaptureCompareInput
    (uint32_t baseAddress,
    uint16_t captureCompareRegister,
    unsigned short synchronized
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister) 
        );

    assert((TIMER_D_READ_CAPTURE_COMPARE_INPUT == synchronized) ||
        (TIMER_D_READ_SYNCHRONIZED_CAPTURECOMPAREINPUT == synchronized)
        );

    if (HWREG16(baseAddress + captureCompareRegister) & synchronized){
        return ( TIMER_D_CAPTURECOMPARE_INPUT_HIGH) ;
    } else   {
        return ( TIMER_D_CAPTURECOMPARE_INPUT_LOW) ;
    }
}

//*****************************************************************************
//
//! Get ouput bit for output mode
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! \return \b TIMER_D_OUTPUTMODE_OUTBITVALUE_HIGH or
//!         \b TIMER_D_OUTPUTMODE_OUTBITVALUE_LOW
//
//*****************************************************************************
uint8_t TIMER_D_getOutputForOutputModeOutBitValue
    (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister) 
        );

    if (HWREG16(baseAddress + captureCompareRegister) & OUT){
        return ( TIMER_D_OUTPUTMODE_OUTBITVALUE_HIGH) ;
    } else   {
        return ( TIMER_D_OUTPUTMODE_OUTBITVALUE_LOW) ;
    }
}

//*****************************************************************************
//
//! Get current capturecompare count
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister selects the Capture register being used.
//!	Valid values are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! \return current count as uint16_t
//! Modifed Registers None
//
//*****************************************************************************
uint16_t TIMER_D_getCaptureCompareCount
    (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    return  (HWREG16(baseAddress + captureCompareRegister + 2));
}

//*****************************************************************************
//
//! Get current capture compare latch register count
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister selects the Capture register being used.
//!	Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! \return current count as uint16_t
//! Modifed Registers None
//
//*****************************************************************************
uint16_t TIMER_D_getCaptureCompareLatchCount
    (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    return  (HWREG16(baseAddress + captureCompareRegister + 4));
}
//*****************************************************************************
//
//! Get current capturecompare input signal
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister selects the Capture register being used.
//! Valid values are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! \return current input signal  as TIMER_D_CAPTURECOMPARE_INPUT
//!		or 0x00
//! Modifed Registers None
//
//*****************************************************************************
uint8_t TIMER_D_getCaptureCompareInputSignal
    (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    return  ((HWREG8(baseAddress + captureCompareRegister) & CCI));
}
//*****************************************************************************
//
//! Set ouput bit for output mode
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister selects the Capture register being used.
//!	Valid values are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param outputModeOutBitValueis the value to be set for out bit
//!     Valid values are \b TIMER_D_OUTPUTMODE_OUTBITVALUE_HIGH
//!                      \b TIMER_D_OUTPUTMODE_OUTBITVALUE_LOW
//!
//! Modified register is \b TDxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_setOutputForOutputModeOutBitValue
    (uint32_t baseAddress,
    uint16_t captureCompareRegister,
    uint8_t outputModeOutBitValue
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister) 
        );

    assert((TIMER_D_OUTPUTMODE_OUTBITVALUE_HIGH == outputModeOutBitValue) ||
        (TIMER_D_OUTPUTMODE_OUTBITVALUE_LOW == outputModeOutBitValue)
        );

    HWREG16(baseAddress + captureCompareRegister) &= ~OUT;
    HWREG16(baseAddress + captureCompareRegister) |= outputModeOutBitValue;
}

//*****************************************************************************
//
//! Generate a PWM with timer running in up mode
//!
//! \param baseAddress is the base address of the Timer module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK [Default value]
//!         \b TIMER_D_CLOCKSOURCE_ACLK
//!         \b TIMER_D_CLOCKSOURCE_SMCLK
//!         \b TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK
//! \param clockSourceDivider is the divider for Clock source.
//! 	Valid values are
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_64
//! \param clockingMode is the selected clock mode register values.
//! Valid values are
//!     \b TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK [Default value]
//!     \b TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK
//!	\b TIMER_D_CLOCKINGMODE_AUXILIARY_CLK
//! \param timerPeriod selects the desired timer period
//! \param compareRegister selects the compare register being used. Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param compareOutputMode specifies the ouput mode. Valid values are
//!        \b TIMER_D_OUTPUTMODE_OUTBITVALUE,
//!        \b TIMER_D_OUTPUTMODE_SET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_D_OUTPUTMODE_SET_RESET
//!        \b TIMER_D_OUTPUTMODE_TOGGLE,
//!        \b TIMER_D_OUTPUTMODE_RESET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_D_OUTPUTMODE_RESET_SET
//! \param dutyCycle specifies the dutycycle for the generated waveform
//!
//! Modified registers are \b TDxCTL0, \b TDxCTL1, \b TDxCCR0,
//!						   \b TDxCCTL0,\b TDxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_generatePWM (  uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t clockingMode,
    uint16_t timerPeriod,
    uint16_t compareRegister,
    uint16_t compareOutputMode,
    uint16_t dutyCycle
    )
{
    
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == compareRegister) 
        );

    assert(
        (TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK == clockSource)
        );


    assert(
        (TIMER_D_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );

    assert(
        (TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_AUXILIARY_CLK == clockingMode)
        );
    
    assert((TIMER_D_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_SET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE_RESET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_SET_RESET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_RESET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_TOGGLE_SET == compareOutputMode) ||
        (TIMER_D_OUTPUTMODE_RESET_SET == compareOutputMode)
        );

    HWREG16(baseAddress + OFS_TDxCTL1)  &= ~(TDCLKM0 + TDCLKM1);

    HWREG16(baseAddress + OFS_TDxCTL0)  &=
            ~( TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK +
               TIMER_D_UPDOWN_MODE + TIMER_D_DO_CLEAR +
               TIMER_D_TDIE_INTERRUPT_ENABLE
               );


    privateTimerDProcessClockSourceDivider(baseAddress,
    		        clockSourceDivider
    		        );
    HWREG16(baseAddress + OFS_TDxCTL0)  |=  clockSource;
    HWREG16(baseAddress + OFS_TDxCTL1) |= clockingMode;

    HWREG16(baseAddress + OFS_TDxCTL0)  |= ( TIMER_D_UP_MODE +
                                          TIMER_D_DO_CLEAR
                                          );

    HWREG16(baseAddress + OFS_TDxCCR0)  = timerPeriod;

    HWREG16(baseAddress + OFS_TDxCCTL0)  &=
        ~(TIMER_D_CAPTURECOMPARE_INTERRUPT_ENABLE +
          TIMER_D_OUTPUTMODE_RESET_SET
          );
    HWREG16(baseAddress + compareRegister)  |= compareOutputMode;

    HWREG16(baseAddress + compareRegister + 2) = dutyCycle;
}

//*****************************************************************************
//
//! Stops the timer
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified registers are \b TDxCTL0
//!
//! \returns None
//
//*****************************************************************************
void TIMER_D_stop ( uint32_t baseAddress )
{
    HWREG16(baseAddress + OFS_TDxCTL0)  &= ~MC_3;
    HWREG16(baseAddress + OFS_TDxCTL0)  |= MC_0;
}

//*****************************************************************************
//
//! Private clock source divider helper function
//!
//! \param baseAddress is the base address of the Timer module.
//! \param clockSourceDivider is the desired divider for the clock source
//!
//! Modified registers are TDxCTL1, TDxCTL0
//!
//! \returns None
//
//*****************************************************************************
void privateTimerDProcessClockSourceDivider (uint32_t baseAddress,
    uint16_t clockSourceDivider)
{
    HWREG16(baseAddress + OFS_TDxCTL0) &= ~ID__8;
    HWREG16(baseAddress + OFS_TDxCTL1) &= ~TDIDEX_7;
    switch (clockSourceDivider){
        case TIMER_D_CLOCKSOURCE_DIVIDER_1:
        case TIMER_D_CLOCKSOURCE_DIVIDER_2:
        case TIMER_D_CLOCKSOURCE_DIVIDER_4:
        case TIMER_D_CLOCKSOURCE_DIVIDER_8:
            HWREG16(baseAddress + OFS_TDxCTL0) |= ((clockSourceDivider - 1) << 6);
            HWREG16(baseAddress + OFS_TDxCTL1) = TDIDEX_0;
            break;

        case TIMER_D_CLOCKSOURCE_DIVIDER_3:
        case TIMER_D_CLOCKSOURCE_DIVIDER_5:
        case TIMER_D_CLOCKSOURCE_DIVIDER_6:
        case TIMER_D_CLOCKSOURCE_DIVIDER_7:
            HWREG16(baseAddress + OFS_TDxCTL0) |= ID__1;
            HWREG16(baseAddress + OFS_TDxCTL1) = (clockSourceDivider - 1);
            break;

        case TIMER_D_CLOCKSOURCE_DIVIDER_10:
        case TIMER_D_CLOCKSOURCE_DIVIDER_12:
        case TIMER_D_CLOCKSOURCE_DIVIDER_14:
        case TIMER_D_CLOCKSOURCE_DIVIDER_16:
            HWREG16(baseAddress + OFS_TDxCTL0) |= ID__2;
            HWREG16(baseAddress + OFS_TDxCTL1) = (clockSourceDivider / 2 - 1 );
            break;

        case TIMER_D_CLOCKSOURCE_DIVIDER_20:
        case TIMER_D_CLOCKSOURCE_DIVIDER_24:
        case TIMER_D_CLOCKSOURCE_DIVIDER_28:
        case TIMER_D_CLOCKSOURCE_DIVIDER_32:
            HWREG16(baseAddress + OFS_TDxCTL0) |= ID__4;
            HWREG16(baseAddress + OFS_TDxCTL1) = (clockSourceDivider / 4 - 1);
            break;
        case TIMER_D_CLOCKSOURCE_DIVIDER_40:
        case TIMER_D_CLOCKSOURCE_DIVIDER_48:
        case TIMER_D_CLOCKSOURCE_DIVIDER_56:
        case TIMER_D_CLOCKSOURCE_DIVIDER_64:
            HWREG16(baseAddress + OFS_TDxCTL0) |= ID__8;
            HWREG16(baseAddress + OFS_TDxCTL1) = (clockSourceDivider / 8 - 1);
            break;
    }
}

//*****************************************************************************
//
//! Sets the value of the capture-compare register
//!
//! \param baseAddress is the base address of the Timer module.
//! \param compareRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param compareValue is the count to be compared with in compare mode
//!
//! Modified register is \b TDxCCRn
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_setCompareValue (  uint32_t baseAddress,
    uint16_t compareRegister,
    uint16_t compareValue
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == compareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == compareRegister) 
        );

    HWREG16(baseAddress + compareRegister + 0x02) = compareValue;
}

//*****************************************************************************
//
//! Clears the Timer TAIFG interrupt flag
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bits are TAIFG of TDxCTL0 register
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_clearTimerInterruptFlag (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxCTL0) &= ~TDIFG;
}

//*****************************************************************************
//
//! Clears the capture-compare interrupt flag
//!
//! \param baseAddress is the base address of the Timer module.
//! \param captureCompareRegister selects the Capture-compare register being
//! used. Valid values are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! Modified bits are CCIFG of \b TDxCCTLn register
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_clearCaptureCompareInterruptFlag (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_D_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_D_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister) 
        );

    HWREG16(baseAddress + captureCompareRegister)  &= ~CCIFG;
}

//*****************************************************************************
//
//! Configures Timer_D in free running mode
//!
//! \param baseAddress is the base address of the Timer module.
//! \param desiredHighResFrequency selects the desired High 
//! Resolution frequency
//! used. Valid values are
//!     \b TIMER_D_HIGHRES_64MHZ
//!     \b TIMER_D_HIGHRES_128MHZ
//!     \b TIMER_D_HIGHRES_200MHZ
//!     \b TIMER_D_HIGHRES_256MHZ
//!
//! Modified registers are \b TDxHCTL1, \b TDxCTL1 and  TDxHCTL0 register
//!
//! \return STATUS_SUCCESS or STATUS_FAIL
//
//*****************************************************************************
uint8_t TIMER_D_configureHighResGeneratorInFreeRunningMode 
	(uint32_t baseAddress,
    uint8_t desiredHighResFrequency
    )
{
	struct s_TLV_Timer_D_Cal_Data * pTD0CAL; 
  	uint8_t TD0CAL_bytes;   
  	
  	assert((TIMER_D_HIGHRES_64MHZ == desiredHighResFrequency) ||
        (TIMER_D_HIGHRES_128MHZ == desiredHighResFrequency) ||
        (TIMER_D_HIGHRES_200MHZ == desiredHighResFrequency) ||
        (TIMER_D_HIGHRES_256MHZ == desiredHighResFrequency)        
        );
  	
  	// Read the TimerD TLV Data
	TLV_getInfo(TLV_TIMER_D_CAL, 
              0, 
              &TD0CAL_bytes, 
              (uint16_t **)&pTD0CAL
              );
              
	if(0x00 == TD0CAL_bytes)
  	{
    	// No TimerD free running cal data found
      	return STATUS_FAIL;
  	}  
  	
	HWREG16(baseAddress + OFS_TDxHCTL1) = TDHCLKTRIM6;
  	HWREG16(baseAddress + OFS_TDxCTL1) = 0x00;
  	HWREG16(baseAddress + OFS_TDxHCTL0) = 0x00;

  	switch( desiredHighResFrequency )
  	{
  		case TIMER_D_HIGHRES_64MHZ:
  			HWREG16(baseAddress + OFS_TDxHCTL1) = pTD0CAL->TDH0CTL1_64; 
  			break;
  			
  		case TIMER_D_HIGHRES_128MHZ:
  			HWREG16(baseAddress + OFS_TDxHCTL1) = pTD0CAL->TDH0CTL1_128; 
  			break;
  			
  		case TIMER_D_HIGHRES_200MHZ:
  			HWREG16(baseAddress + OFS_TDxHCTL1) = pTD0CAL->TDH0CTL1_200;
  			break;
  			 
  		case TIMER_D_HIGHRES_256MHZ:
  			HWREG16(baseAddress + OFS_TDxHCTL1) = pTD0CAL->TDH0CTL1_256;
  			break; 
  	}
  	


	// Select Hi-res local clock
  	HWREG16(baseAddress + OFS_TDxCTL1) |= TDCLKM_1;
  	        
    // CALEN=0 => free running mode; enable Hi-res mode
 	if(TIMER_D_HIGHRES_256MHZ == desiredHighResFrequency)
  		HWREG16(baseAddress + OFS_TDxHCTL0) |= TDHM_1;
  	
  	HWREG16(baseAddress + OFS_TDxHCTL0) |= TDHEN; 
  							
  	   
  	return STATUS_SUCCESS;
    
}

//*****************************************************************************
//
//! Configures Timer_D in Regulated mode
//!
//! \param baseAddress is the base address of the Timer module.
///! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK [Default value]
//!         \b TIMER_D_CLOCKSOURCE_ACLK
//!         \b TIMER_D_CLOCKSOURCE_SMCLK
//!         \b TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK
//! \param clockSourceDivider is the divider for Clock source.
//! 	Valid values are
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_64
//! \param clockingMode is the selected clock mode register values.
//! Valid values are
//!     \b TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK [Default value]
//!     \b TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK
//!	\b TIMER_D_CLOCKINGMODE_AUXILIARY_CLK
//! \param highResClockMultiplyFactor selects the high resolution
//! multiply factor.
//!     \b TIMER_D_HIGHRES_CLK_MULTIPLY_FACTOR_8x
//!     \b TIMER_D_HIGHRES_CLK_MULTIPLY_FACTOR_16x
//! \param highResClockDivider selects the high resolution
//! divider.
//!     \b TIMER_D_HIGHRES_CLK_DIVIDER_1 [Default value]
//!     \b TIMER_D_HIGHRES_CLK_DIVIDER_2
//!     \b TIMER_D_HIGHRES_CLK_DIVIDER_4
//!     \b TIMER_D_HIGHRES_CLK_DIVIDER_8
//!
//! Modified registers are \b OFS_TDxCTL0, \b TDxCTL1 and  TDxHCTL0 register
//!
//! \return NONE
//
//*****************************************************************************
void TIMER_D_configureHighResGeneratorInRegulatedMode (uint32_t baseAddress,
     uint16_t clockSource, 
     uint16_t clockSourceDivider,
     uint16_t clockingMode, 
     uint8_t highResClockMultiplyFactor,
     uint8_t highResClockDivider
    )
{	
	assert(
        (TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK == clockSource)
        );


    assert(
        (TIMER_D_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );

    assert(
        (TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_AUXILIARY_CLK == clockingMode)
        );
    
	assert((TIMER_D_HIGHRES_CLK_MULTIPLY_FACTOR_8x == highResClockMultiplyFactor) ||
        (TIMER_D_HIGHRES_CLK_MULTIPLY_FACTOR_16x == highResClockMultiplyFactor)
        );

	assert((TIMER_D_HIGHRES_CLK_DIVIDER_1 == highResClockDivider) ||
	        (TIMER_D_HIGHRES_CLK_DIVIDER_2 == highResClockDivider) ||
	        (TIMER_D_HIGHRES_CLK_DIVIDER_4 == highResClockDivider) ||
	        (TIMER_D_HIGHRES_CLK_DIVIDER_8 == highResClockDivider)
	        );

	/**********how abt MCx and TDCLGRPx and CNTLx*/
	HWREG16(baseAddress + OFS_TDxCTL0) &= ~(TDSSEL_3 + TDHD_3 + TDCLR);  
        
	HWREG16(baseAddress + OFS_TDxCTL1)  &= ~(TDCLKM0 + TDCLKM1);
	
        privateTimerDProcessClockSourceDivider(baseAddress,
    		        clockSourceDivider
    		        );
        HWREG16(baseAddress + OFS_TDxCTL0)  |=  clockSource;
        HWREG16(baseAddress + OFS_TDxCTL1) |= clockingMode;

  	// Select Hi-res local clock
  	// Calibration and Hi-res mode enable
  	HWREG16(baseAddress + OFS_TDxCTL1) |= TDCLKM_1;                      
  	// Select Hi-res local clock
  	HWREG16(baseAddress + OFS_TDxHCTL0) =  TDHREGEN + TDHEN ;
  	HWREG16(baseAddress + OFS_TDxHCTL0) |= highResClockMultiplyFactor +
  					highResClockDivider;
 
}
//*****************************************************************************
//
//! Combine TDCCRto get PWM
//!
//! \param baseAddress is the base address of the Timer module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK [Default value]
//!         \b TIMER_D_CLOCKSOURCE_ACLK
//!         \b TIMER_D_CLOCKSOURCE_SMCLK
//!         \b TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK
//! \param clockSourceDivider is the divider for Clock source.
//! 	Valid values are
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_D_CLOCKSOURCE_DIVIDER_64
//! \param clockingMode is the selected clock mode register values.
//! Valid values are
//!     \b TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK [Default value]
//!     \b TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK
//!	\b TIMER_D_CLOCKINGMODE_AUXILIARY_CLK
//!//! \param timerPeriod selects the desired timer period
//! \param combineCCRRegistersCombination selects desired CCR registers to
//!			combine
//!			\b TIMER_D_COMBINE_CCR1_CCR2
//!			\b TIMER_D_COMBINE_CCR3_CCR4 (available on Timer_D5, Timer_D7)
//!			\b TIMER_D_COMBINE_CCR5_CCR6(available only on Timer_D7)
//! \param compareOutputMode specifies the ouput mode. Valid values are
//!        \b TIMER_D_OUTPUTMODE_OUTBITVALUE,
//!        \b TIMER_D_OUTPUTMODE_SET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_D_OUTPUTMODE_SET_RESET
//!        \b TIMER_D_OUTPUTMODE_TOGGLE,
//!        \b TIMER_D_OUTPUTMODE_RESET,
//!        \b TIMER_D_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_D_OUTPUTMODE_RESET_SET
//! \param dutyCycle specifies the dutycycle for the generated waveform
//!
//! Modified registers are \b TDxCTL0, \b TDxCTL1, \b TDxCCR0,
//!						   \b TDxCCTL0,\b TDxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_combineTDCCRToGeneratePWM (  uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t clockingMode,
    uint16_t timerPeriod,
    uint16_t combineCCRRegistersCombination,
    uint16_t compareOutputMode,
    uint16_t dutyCycle1,
    uint16_t dutyCycle2
    )
{
	assert(
                (TIMER_D_COMBINE_CCR1_CCR2 == combineCCRRegistersCombination) ||
                (TIMER_D_COMBINE_CCR3_CCR4 == combineCCRRegistersCombination) ||
                (TIMER_D_COMBINE_CCR5_CCR6 == combineCCRRegistersCombination)
                );

	assert(
        (TIMER_D_CLOCKSOURCE_EXTERNAL_TDCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_D_CLOCKSOURCE_INVERTED_EXTERNAL_TDCLK == clockSource)
        );


    assert(
        (TIMER_D_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_D_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );

    assert(
        (TIMER_D_CLOCKINGMODE_EXTERNAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_HIRES_LOCAL_CLOCK == clockingMode) ||
        (TIMER_D_CLOCKINGMODE_AUXILIARY_CLK == clockingMode)
        );

	assert((TIMER_D_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_SET == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_TOGGLE_RESET == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_SET_RESET == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_TOGGLE == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_RESET == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_TOGGLE_SET == compareOutputMode) ||
	        (TIMER_D_OUTPUTMODE_RESET_SET == compareOutputMode)
	        );


	HWREG16(baseAddress + OFS_TDxCCTL2) &= ~OUTMOD_7;
	HWREG16(baseAddress + OFS_TDxCCTL2)  |= compareOutputMode;

    HWREG16(baseAddress + OFS_TDxCCR0)  = timerPeriod;
    
    HWREG16(baseAddress + OFS_TDxCCR1 + (0x05 *
    		(combineCCRRegistersCombination - TIMER_D_COMBINE_CCR1_CCR2))) = dutyCycle1;
    HWREG16(baseAddress + OFS_TDxCCR2 + (0x05 *
    		(combineCCRRegistersCombination - TIMER_D_COMBINE_CCR1_CCR2))) = dutyCycle2;
    
    HWREG16(baseAddress + OFS_TDxCTL1)  &= ~(TDCLKM0 + TDCLKM1);

    privateTimerDProcessClockSourceDivider(baseAddress,
    		        clockSourceDivider
    		        );
    
    HWREG16(baseAddress + OFS_TDxCTL0)  |=  clockSource;
    HWREG16(baseAddress + OFS_TDxCTL1) |= clockingMode;
    HWREG16(baseAddress + OFS_TDxCTL1)  |=
    		(TD2CMB << (combineCCRRegistersCombination - TIMER_D_COMBINE_CCR1_CCR2));
}

//*****************************************************************************
//
//! Selects TimerD Latching Group
//!
//! \param baseAddress is the base address of the TimerD module.
//! \param groupLatch selects the value of counter length.
//! Valid values are
//!     \b TIMER_D_GROUP_NONE [Default value]
//!     \b TIMER_D_GROUP_CL12_CL23_CL56
//!     \b TIMER_D_GROUP_CL123_CL456
//!     \b TIMER_D_GROUP_ALL
//!
//! Modified bits are TDCLGRP of \b TDxCTL0 register
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_selectLatchingGroup(uint16_t  baseAddress,
		uint16_t groupLatch)
{
	assert((TIMER_D_GROUP_NONE  == groupLatch) ||
		   (TIMER_D_GROUP_CL12_CL23_CL56 == groupLatch) ||
		   (TIMER_D_GROUP_CL123_CL456 == groupLatch) ||
		   (TIMER_D_GROUP_ALL == groupLatch)
		   );


	HWREG16(baseAddress + OFS_TDxCTL0) &= ~TDCLGRP_3;
	HWREG16(baseAddress + OFS_TDxCTL0) |= groupLatch;
}

//*****************************************************************************
//
//! Selects TimerD counter length
//!
//! \param baseAddress is the base address of the TimerD module.
//! \param counterLength selects the value of counter length.
//! Valid values are
//!     \b TIMER_D_COUNTER_16BIT [Default value]
//!     \b TIMER_D_COUNTER_12BIT
//!     \b TIMER_D_COUNTER_10BIT
//!     \b TIMER_D_COUNTER_8BIT
//!
//! Modified bits are CNTL of \b TDxCTL0 register
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_selectCounterLength (uint16_t  baseAddress,
		uint16_t counterLength
		)
{
	assert((TIMER_D_COUNTER_8BIT == counterLength) ||
	        (TIMER_D_COUNTER_10BIT == counterLength) ||
	        (TIMER_D_COUNTER_12BIT == counterLength) ||
	        (TIMER_D_COUNTER_16BIT == counterLength)
	        );


	HWREG16(baseAddress + OFS_TDxCTL0) &= ~CNTL_3;
	HWREG16(baseAddress + OFS_TDxCTL0) |= counterLength;
}

//*****************************************************************************
//
//! Selects Compare Latch Load Event
//!
//! \param baseAddress is the base address of the TimerD module.
//! \param captureCompareRegister selects the Capture-compare register being
//! used. Valid values are
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_D_CAPTURECOMPARE_REGISTER_6
//! \param compareLatchLoadEvent selects the latch load event
//! Valid values are
//!     \b TIMER_D_LATCH_ON_WRITE_TO_TDxCCRn_COMPARE_REGISTER [Default value]
//!     \b TIMER_D_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UP_OR_CONT_MODE
//!     \b TIMER_D_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UPDOWN_MODE
//!     \b TIMER_D_LATCH_WHEN_COUNTER_COUNTS_TO_CURRENT_COMPARE_LATCH_VALUE
//!
//! Modified bits are CLLD of \b TDxCCTLn register
//!
//! \return None
//
//*****************************************************************************
void TIMER_D_initCompareLatchLoadEvent(uint16_t  baseAddress,
		uint16_t  compareRegister,
		uint16_t  compareLatchLoadEvent
		)
{
	assert((TIMER_D_LATCH_ON_WRITE_TO_TDxCCRn_COMPARE_REGISTER  == compareLatchLoadEvent) ||
		(TIMER_D_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UP_OR_CONT_MODE == compareLatchLoadEvent) ||
		(TIMER_D_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UPDOWN_MODE == compareLatchLoadEvent) ||
		(TIMER_D_LATCH_WHEN_COUNTER_COUNTS_TO_CURRENT_COMPARE_LATCH_VALUE
				== compareLatchLoadEvent)
		);

	HWREG16(baseAddress + compareRegister)  &= ~CLLD_3;
	HWREG16(baseAddress + compareRegister)  |= compareLatchLoadEvent;
}

//*****************************************************************************
//
//! Disable High Resolution fast wakeup
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bits are TDHFW of TDxHCTL0 register.
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_disableHighResFastWakeup (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxHCTL0) &= ~TDHFW;
}

//*****************************************************************************
//
//! Enable High Resolution fast wakeup
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bits are TDHFW of TDxHCTL0 register.
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_enableHighResFastWakeup (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxHCTL0) |= TDHFW;
}

//*****************************************************************************
//
//! Disable High Resolution Clock Enhanced Accuracy
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bits are TDHEAEN of TDxHCTL0 register.
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_disableHighResClockEnhancedAccuracy (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxHCTL0) &= ~TDHEAEN;
}

//*****************************************************************************
//
//! Enable High Resolution Clock Enhanced Accuracy
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bits are TDHEAEN of TDxHCTL0 register.
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_enableHighResClockEnhancedAccuracy (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxHCTL0) |= TDHEAEN;
}

//*****************************************************************************
//
//! Disable High Resolution Clock Enhanced Accuracy
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bit is TDHRON of register TDxHCTL0
//!
//!High-resolution generator is on if the Timer_D counter
//!MCx bits are 01, 10 or 11.
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_DisableHighResGeneratorForceON (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxHCTL0) &= ~TDHRON;
}

//*****************************************************************************
//
//! Enable High Resolution Clock Enhanced Accuracy
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Modified bit is TDHRON of register TDxHCTL0
//!
//!High-resolution generator is on in all Timer_D MCx modes. The PMM
//!remains in high-current mode.
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_EnableHighResGeneratorForceON (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TDxHCTL0) |= TDHRON;
}

//*****************************************************************************
//
//! Select High Resolution Coarse Clock Range
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! \param highResCoarseClockRange selects the High Resolution Coarse
//! Clock Range
//! Valid values are
//!     \b TIMER_D_HIGHRES_BELOW_15MHz [Default value]
//!     \b TIMER_D_HIGHRES_ABOVE_15MHz
//!
//! Modified bits are TDHCLKCR of registers TDxHCTL1.
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_selectHighResCoarseClockRange (uint32_t baseAddress,
		uint16_t highResCoarseClockRange
		)
{
	assert((TIMER_D_HIGHRES_BELOW_15MHz  == highResCoarseClockRange) ||
		(TIMER_D_HIGHRES_ABOVE_15MHz == highResCoarseClockRange)
		);
	HWREG16(baseAddress + OFS_TDxHCTL1) &= ~TDHCLKCR;
    HWREG16(baseAddress + OFS_TDxHCTL1) |= highResCoarseClockRange;
}

//*****************************************************************************
//
//! Select High Resolution Clock Range Selection
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! \param highResClockRange selects the High Resolution
//! Clock Range
//! Valid values are
//!     \b TIMER_D_CLOCK_RANGE0 [Default value]
//!     \b TIMER_D_CLOCK_RANGE1
//!     \b TIMER_D_CLOCK_RANGE2
//!Refer Datasheet for frequency details
//!
//!Modified bits are TDHCLKRx of registers TDxHCTL1
//! NOTE: In Regulated mode these bits are modified by hardware.
//!
//! \returns NONE
//
//*****************************************************************************
void TIMER_D_selectHighResClockRange (uint32_t baseAddress,
		uint16_t highResClockRange
		)
{
	assert((TIMER_D_CLOCK_RANGE0  == highResClockRange) ||
		(TIMER_D_CLOCK_RANGE1 == highResClockRange) 	||
		(TIMER_D_CLOCK_RANGE2 == highResClockRange)
		);
	HWREG16(baseAddress + OFS_TDxHCTL1) &= ~TDHCLKCR;
    HWREG16(baseAddress + OFS_TDxHCTL1) |= highResClockRange;
}

//*****************************************************************************
//
//! Reads the current timer count value
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Reads the current count value of the timer. There is a majority vote
//! system in place to confirm an accurate value is returned. The
//! TIMER_D_THRESHOLD #define in timer_d.h can be modified so that the votes
//! must be closer together for a consensus to occur.
//!
//! \return Majority vote of timer count value
//
//*****************************************************************************
uint16_t TIMER_D_getCounterValue (uint32_t baseAddress)
{
	uint16_t voteOne, voteTwo, res;

    voteTwo = HWREG16(baseAddress + OFS_TDxR);

	do
    {
        voteOne = voteTwo;
        voteTwo = HWREG16(baseAddress + OFS_TDxR);

		if(voteTwo > voteOne) {
			res = voteTwo - voteOne;
		} else if(voteOne > voteTwo) {
			res = voteOne - voteTwo;
		} else{
			res = 0;
		}

    } while ( res > TIMER_D_THRESHOLD);

    return voteTwo;
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************

