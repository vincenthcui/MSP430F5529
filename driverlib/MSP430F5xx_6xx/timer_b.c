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
//timer_b.c - Driver for the TIMERB Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "assert.h"
#include "timer_b.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif

static void privateTimerBProcessClockSourceDivider (uint32_t baseAddress,
    uint16_t clockSourceDivider);

//*****************************************************************************
//
//! Starts TimerB counter
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CONTINUOUS_MODE [Default value]
//!         \b TIMER_B_UPDOWN_MODE
//!         \b TIMER_B_UP_MODE
//! Modified register is \b TAxCTL
//!
//!NOTE: This function assumes that the timer has been previously configured
//! using TIMER_B_configureContinuousMode,  TIMER_B_configureUpMode or
//!TIMER_B_configureUpDownMode.
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_startCounter ( uint32_t baseAddress,
    uint16_t timerMode
    )
{
    assert(
        (TIMER_B_UPDOWN_MODE == timerMode) ||
        (TIMER_B_CONTINUOUS_MODE == timerMode) ||
        (TIMER_B_UP_MODE == timerMode)
         );


    HWREG16(baseAddress + OFS_TBxCTL) |= timerMode;
}

//*****************************************************************************
//
//! Configures TimerB in continuous mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified reister is \b TAxCTL
//!
//!This API does not start the timer. Timer needs to be started when required
//!using the TIMER_B_startCounter API.
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_configureContinuousMode ( uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t timerClear
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_B_TBIE_INTERRUPT_ENABLE == timerInterruptEnable_TBIE) ||
        (TIMER_B_TBIE_INTERRUPT_DISABLE == timerInterruptEnable_TBIE)
        );

    assert(
        (TIMER_B_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );


    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress +
        OFS_TBxCTL) &= ~(TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
        				 TIMER_B_UPDOWN_MODE +
                         TIMER_B_DO_CLEAR +
                         TIMER_B_TBIE_INTERRUPT_ENABLE +
                         CNTL_3
                         );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource + 
                                          timerClear +
                                          timerInterruptEnable_TBIE);
}
//*****************************************************************************
//
//! Configures TimerB in up mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerPeriod is the specified TimerB period. This is the value that gets
//!         written into the CCR0. Limited to 16 bits[uint16_t]
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE and
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param captureCompareInterruptEnable_CCR0_CCIE is to enable or disable
//!         TimerB CCR0 captureComapre interrupt. Valid values are
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE and
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified registers are  \b TAxCTL, \b TAxCCR0, \b TAxCCTL0
//!
//!This API does not start the timer. Timer needs to be started when required
//!using the TIMER_B_startCounter API.
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_configureUpMode (   uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerPeriod,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t captureCompareInterruptEnable_CCR0_CCIE,
    uint16_t timerClear
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress + OFS_TBxCTL) &=
        ~(TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
          TIMER_B_UPDOWN_MODE +
          TIMER_B_DO_CLEAR +
          TIMER_B_TBIE_INTERRUPT_ENABLE +
          CNTL_3
          );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource +
                                            timerClear +
                                            timerInterruptEnable_TBIE
                                          );

    if (TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE ==
        captureCompareInterruptEnable_CCR0_CCIE){
        HWREG16(baseAddress + OFS_TBxCCTL0)  |= TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    } else   {
        HWREG16(baseAddress + OFS_TBxCCTL0)  &= ~TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    }

    HWREG16(baseAddress + OFS_TBxCCR0)  = timerPeriod;
}

//*****************************************************************************
//
//! Configures TimerB in up down mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerPeriod is the specified TimerB period
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param captureCompareInterruptEnable_CCR0_CCIE is to enable or disable
//!         TimerB CCR0 captureComapre interrupt. Valid values are
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE and
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified registers are  \b TAxCTL, \b TAxCCR0, \b TAxCCTL0
//!
//!This API does not start the timer. Timer needs to be started when required
//!using the TIMER_B_startCounter API.
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_configureUpDownMode (
    uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerPeriod,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t captureCompareInterruptEnable_CCR0_CCIE,
    uint16_t timerClear
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress + OFS_TBxCTL) &=
        ~(TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
          TIMER_B_UPDOWN_MODE +
          TIMER_B_DO_CLEAR +
          TIMER_B_TBIE_INTERRUPT_ENABLE +
          CNTL_3
          );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource +
    									  TIMER_B_STOP_MODE +
                                          timerClear +
                                          timerInterruptEnable_TBIE
                                          );
    if (TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE ==
        captureCompareInterruptEnable_CCR0_CCIE){
        HWREG16(baseAddress + OFS_TBxCCTL0)  |= TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    } else   {
        HWREG16(baseAddress + OFS_TBxCCTL0)  &= ~TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    }

    HWREG16(baseAddress + OFS_TBxCCR0)  = timerPeriod;
}

//*****************************************************************************
//
//! DEPRPECATED - Replaced by TIMER_B_configureContinuousMode and TIMER_B_startCounter
//! API
//! Starts TimerB in continuous mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified reister is \b TAxCTL
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_startContinuousMode ( uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t timerClear
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_B_TBIE_INTERRUPT_ENABLE == timerInterruptEnable_TBIE) ||
        (TIMER_B_TBIE_INTERRUPT_DISABLE == timerInterruptEnable_TBIE)
        );

    assert(
        (TIMER_B_CLOCKSOURCE_DIVIDER_1 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_2 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_4 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_8 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_3 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_5 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_6 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_7 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_10 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_12 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_14 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_16 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_20 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_24 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_28 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_32 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_40 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_48 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_56 == clockSourceDivider) ||
        (TIMER_B_CLOCKSOURCE_DIVIDER_64 == clockSourceDivider)
        );


    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress +
        OFS_TBxCTL) &= ~(TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
                         TIMER_B_UPDOWN_MODE +
                         TIMER_B_DO_CLEAR +
                         TIMER_B_TBIE_INTERRUPT_ENABLE +
                         CNTL_3
                         );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource + TIMER_B_CONTINUOUS_MODE +
                                          timerClear +
                                          timerInterruptEnable_TBIE);
}

//*****************************************************************************
//
//! DEPRECATED- Spelling Error Fixed
//! Starts TimerB in continuous mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified register is \b TAxCTL
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_startContinousMode ( uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t timerClear
    )
{
	TIMER_B_startContinuousMode (baseAddress,
    clockSource,
    clockSourceDivider,
    timerInterruptEnable_TBIE,
    timerClear
    );
}
//*****************************************************************************
//
//! DEPRPECATED - Replaced by TIMER_B_configureUpMode and TIMER_B_startCounter  API
//!
//! Starts TimerB in up mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerPeriod is the specified TimerB period. This is the value that gets
//!         written into the CCR0. Limited to 16 bits[uint16_t]
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE and
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param captureCompareInterruptEnable_CCR0_CCIE is to enable or disable
//!         TimerB CCR0 captureComapre interrupt. Valid values are
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE and
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified registers are  \b TAxCTL, \b TAxCCR0, \b TAxCCTL0
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_startUpMode (   uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerPeriod,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t captureCompareInterruptEnable_CCR0_CCIE,
    uint16_t timerClear
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress + OFS_TBxCTL) &=
        ~(TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
          TIMER_B_UPDOWN_MODE +
          TIMER_B_DO_CLEAR +
          TIMER_B_TBIE_INTERRUPT_ENABLE +
          CNTL_3
          );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource +
                                          TIMER_B_UP_MODE +
                                          timerClear +
                                          timerInterruptEnable_TBIE
                                          );

    if (TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE ==
        captureCompareInterruptEnable_CCR0_CCIE){
        HWREG16(baseAddress + OFS_TBxCCTL0)  |= TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    } else   {
        HWREG16(baseAddress + OFS_TBxCCTL0)  &= ~TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    }

    HWREG16(baseAddress + OFS_TBxCCR0)  = timerPeriod;
}

//*****************************************************************************
//
//! DEPRPECATED - Replaced by TIMER_B_configureUpDownMode and TIMER_B_startCounter  API
//!
//! Starts TimerB in up down mode.
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK [Default value]
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1 [Default value]
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerPeriod is the specified TimerB period
//! \param timerInterruptEnable_TBIE is to enable or disable TimerB interrupt
//!        Valid values are
//!        \b TIMER_B_TBIE_INTERRUPT_ENABLE
//!        \b TIMER_B_TBIE_INTERRUPT_DISABLE [Default value]
//! \param captureCompareInterruptEnable_CCR0_CCIE is to enable or disable
//!         TimerB CCR0 captureComapre interrupt. Valid values are
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE and
//!        \b TIMER_B_CCIE_CCR0_INTERRUPT_DISABLE [Default value]
//! \param timerClear decides if TimerB clock divider, count direction, count
//!        need to be reset. Valid values are
//!        \b TIMER_B_DO_CLEAR
//!        \b TIMER_B_SKIP_CLEAR [Default value]
//!
//! Modified registers are  \b TAxCTL, \b TAxCCR0, \b TAxCCTL0
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_startUpDownMode (
    uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerPeriod,
    uint16_t timerInterruptEnable_TBIE,
    uint16_t captureCompareInterruptEnable_CCR0_CCIE,
    uint16_t timerClear
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    assert(
        (TIMER_B_DO_CLEAR == timerClear) ||
        (TIMER_B_SKIP_CLEAR == timerClear)
        );

    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress + OFS_TBxCTL) &=
        ~(TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
          TIMER_B_UPDOWN_MODE +
          TIMER_B_DO_CLEAR +
          TIMER_B_TBIE_INTERRUPT_ENABLE +
          CNTL_3
          );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource +
                                          TIMER_B_UPDOWN_MODE +
                                          timerClear +
                                          timerInterruptEnable_TBIE
                                          );
    if (TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE ==
        captureCompareInterruptEnable_CCR0_CCIE){
        HWREG16(baseAddress + OFS_TBxCCTL0)  |= TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    } else   {
        HWREG16(baseAddress + OFS_TBxCCTL0)  &= ~TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    }

    HWREG16(baseAddress + OFS_TBxCCR0)  = timerPeriod;
}

//*****************************************************************************
//
//! Initializes Capture Mode
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param captureMode is the capture mode selected. Valid values are
//!        \b TIMER_B_CAPTUREMODE_NO_CAPTURE [Default value]
//!        \b TIMER_B_CAPTUREMODE_RISING_EDGE
//!        \b TIMER_B_CAPTUREMODE_FALLING_EDGE
//!        \b TIMER_B_CAPTUREMODE_RISING_AND_FALLING_EDGE
//! \param captureInputSelect decides the Input Select
//!        \b TIMER_B_CAPTURE_INPUTSELECT_CCIxA [Default value]
//!        \b TIMER_B_CAPTURE_INPUTSELECT_CCIxB
//!        \b TIMER_B_CAPTURE_INPUTSELECT_GND
//!        \b TIMER_B_CAPTURE_INPUTSELECT_Vcc
//! \param synchronizeCaptureSource decides if capture source should be
//!         synchronized with TimerB clock
//!        Valid values are
//!        \b TIMER_B_CAPTURE_ASYNCHRONOUS [Default value]
//!        \b TIMER_B_CAPTURE_SYNCHRONOUS
//! \param captureInterruptEnable is to enable or disable
//!         TimerB captureComapre interrupt. Valid values are
//!        \b TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE [Default value]
//!        \b TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE
//! \param captureOutputMode specifies the ouput mode. Valid values are
//!        \b TIMER_B_OUTPUTMODE_OUTBITVALUE [Default value],
//!        \b TIMER_B_OUTPUTMODE_SET,
//!        \b TIMER_B_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_B_OUTPUTMODE_SET_RESET
//!        \b TIMER_B_OUTPUTMODE_TOGGLE,
//!        \b TIMER_B_OUTPUTMODE_RESET,
//!        \b TIMER_B_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_B_OUTPUTMODE_RESET_SET
//!
//! Modified register is \b TAxCCTLn
//! \return None
//
//*****************************************************************************
void TIMER_B_initCapture (uint32_t baseAddress,
    uint16_t captureRegister,
    uint16_t captureMode,
    uint16_t captureInputSelect,
    unsigned short synchronizeCaptureSource,
    unsigned short captureInterruptEnable,
    uint16_t captureOutputMode
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureRegister)
        );

    assert((TIMER_B_CAPTUREMODE_NO_CAPTURE == captureMode) ||
        (TIMER_B_CAPTUREMODE_RISING_EDGE == captureMode) ||
        (TIMER_B_CAPTUREMODE_FALLING_EDGE == captureMode) ||
        (TIMER_B_CAPTUREMODE_RISING_AND_FALLING_EDGE == captureMode)
        );

    assert((TIMER_B_CAPTURE_INPUTSELECT_CCIxA == captureInputSelect) ||
        (TIMER_B_CAPTURE_INPUTSELECT_CCIxB == captureInputSelect) ||
        (TIMER_B_CAPTURE_INPUTSELECT_GND == captureInputSelect) ||
        (TIMER_B_CAPTURE_INPUTSELECT_Vcc == captureInputSelect)
        );

    assert((TIMER_B_CAPTURE_ASYNCHRONOUS == synchronizeCaptureSource) ||
        (TIMER_B_CAPTURE_SYNCHRONOUS == synchronizeCaptureSource)
        );

    assert(
        (TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE == captureInterruptEnable) ||
        (TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE == captureInterruptEnable)
        );

    assert((TIMER_B_OUTPUTMODE_OUTBITVALUE == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_SET == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE_RESET == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_SET_RESET == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_RESET == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE_SET == captureOutputMode) ||
        (TIMER_B_OUTPUTMODE_RESET_SET == captureOutputMode)
        );

    if (TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureRegister){
        //CaptureCompare register 0 only supports certain modes
        assert((TIMER_B_OUTPUTMODE_OUTBITVALUE == captureOutputMode) ||
            (TIMER_B_OUTPUTMODE_SET == captureOutputMode) ||
            (TIMER_B_OUTPUTMODE_TOGGLE == captureOutputMode) ||
            (TIMER_B_OUTPUTMODE_RESET == captureOutputMode)
            );
    }

    HWREG16(baseAddress + captureRegister ) |=   CAP;

    HWREG16(baseAddress + captureRegister) &=
        ~(TIMER_B_CAPTUREMODE_RISING_AND_FALLING_EDGE +
          TIMER_B_CAPTURE_INPUTSELECT_Vcc +
          TIMER_B_CAPTURE_SYNCHRONOUS +
          TIMER_B_DO_CLEAR +
          TIMER_B_TBIE_INTERRUPT_ENABLE +
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
//! \param baseAddress is the base address of the TimerB module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param compareInterruptEnable is to enable or disable
//!         TimerB captureComapre interrupt. Valid values are
//!        \b TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE and
//!        \b TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE [Default value]
//! \param compareOutputMode specifies the ouput mode. Valid values are
//!        \b TIMER_B_OUTPUTMODE_OUTBITVALUE [Default value],
//!        \b TIMER_B_OUTPUTMODE_SET,
//!        \b TIMER_B_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_B_OUTPUTMODE_SET_RESET
//!        \b TIMER_B_OUTPUTMODE_TOGGLE,
//!        \b TIMER_B_OUTPUTMODE_RESET,
//!        \b TIMER_B_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_B_OUTPUTMODE_RESET_SET
//! \param compareValue is the count to be compared with in compare mode
//!
//! Modified register is \b TAxCCTLn and \b TAxCCRn
//! \return None
//
//*****************************************************************************
void TIMER_B_initCompare (  uint32_t baseAddress,
    uint16_t compareRegister,
    unsigned short compareInterruptEnable,
    uint16_t compareOutputMode,
    uint16_t compareValue
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == compareRegister)
        );

   assert((TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE == compareInterruptEnable) ||
        (TIMER_B_CAPTURECOMPARE_INTERRUPT_DISABLE == compareInterruptEnable)
        );

    assert((TIMER_B_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_SET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE_RESET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_SET_RESET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_RESET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE_SET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_RESET_SET == compareOutputMode)
        );

    if (TIMER_B_CAPTURECOMPARE_REGISTER_0 == compareRegister){
        //CaptureCompare register 0 only supports certain modes
        assert((TIMER_B_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
            (TIMER_B_OUTPUTMODE_SET == compareOutputMode) ||
            (TIMER_B_OUTPUTMODE_TOGGLE == compareOutputMode) ||
            (TIMER_B_OUTPUTMODE_RESET == compareOutputMode)
            );
    }


    HWREG16(baseAddress + compareRegister ) &=   ~CAP;

    HWREG16(baseAddress + compareRegister) &=
        ~(TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE +
          TIMER_B_OUTPUTMODE_RESET_SET
          );

    HWREG16(baseAddress + compareRegister)  |= ( compareInterruptEnable +
                                               compareOutputMode
                                               );

    HWREG16(baseAddress + compareRegister + OFS_TBxR) = compareValue;
}

//*****************************************************************************
//
//! Enable TimerB interrupt
//!
//! \param baseAddress is the base address of the TimerB module.
//!
//! <b>Does not clear interrupt flags.</b>
//! Modified register is \b TBxCTL
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_enableInterrupt (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TBxCTL) |= TBIE;
}

//*****************************************************************************
//
//! Disable TimerB interrupt
//!
//! \param baseAddress is the base address of the TimerB module.
//!
//! Modified register is \b TAxCTL
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_disableInterrupt (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TBxCTL) &= ~TBIE;
}

//*****************************************************************************
//
//! Get TimerB interrupt status
//!
//! \param baseAddress is the base address of the TimerB module.
//!
//! \return uint32_t. Return interrupt status. Valid values are
//!         \b TIMER_B_INTERRUPT_PENDING
//!         \b TIMER_B_INTERRUPT_NOT_PENDING
//
//*****************************************************************************
uint32_t TIMER_B_getInterruptStatus (uint32_t baseAddress)
{
    return ( HWREG16(baseAddress + OFS_TBxCTL) & TBIFG );
}

//*****************************************************************************
//
//! Enable capture compare interrupt
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureCompareRegister is the selected capture compare regsiter
//!
//! Modified register is \b TAxCCTLn
//!
//! <b>Does not clear interrupt flags.</b>
//! \return None
//
//*****************************************************************************
void TIMER_B_enableCaptureCompareInterrupt (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    HWREG16(baseAddress + captureCompareRegister) |= CCIE;
}

//*****************************************************************************
//
//! Disable capture compare interrupt
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureCompareRegister is the selected capture compare regsiter
//!
//! Modified register is \b TAxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_disableCaptureCompareInterrupt (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );
    HWREG16(baseAddress + captureCompareRegister) &= ~CCIE;
}

//*****************************************************************************
//
//! Return capture compare interrupt status
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param mask is the mask for the interrupt status
//!         Valid values is and OR of
//!         \b TIMER_B_CAPTURE_OVERFLOW,
//!         \b TIMER_B_CAPTURECOMPARE_INTERRUPT_FLAG
//!
//!
//! \returns uint32_t. The mask of the set flags.
//
//*****************************************************************************
uint32_t TIMER_B_getCaptureCompareInterruptStatus (uint32_t baseAddress,
		 uint16_t captureCompareRegister,
		 uint16_t mask
		 )
{
    return ( HWREG16(baseAddress + captureCompareRegister) & mask );
}

//*****************************************************************************
//
//! Reset/Clear the TimerB clock divider, count direction, count
//!
//! \param baseAddress is the base address of the TimerB module.
//!
//! Modified register is \b TAxCTL
//!
//! \returns None
//
//*****************************************************************************
void TIMER_B_clear (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TBxCTL) |= TBCLR;
}

//*****************************************************************************
//
//! Get synchrnozied capturecompare input
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param synchronized is to select type of capture compare input.
//!         Valid values are
//!        \b TIMER_B_READ_CAPTURE_COMPARE_INPUT
//!        \b TIMER_B_READ_SYNCHRONIZED_CAPTURECOMPAREINPUT
//!
//! \return \b TIMER_B_CAPTURECOMPARE_INPUT_HIGH or
//!         \b TIMER_B_CAPTURECOMPARE_INPUT_LOW
//
//*****************************************************************************
unsigned short TIMER_B_getSynchronizedCaptureCompareInput
    (uint32_t baseAddress,
    uint16_t captureCompareRegister,
    unsigned short synchronized
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    assert((TIMER_B_READ_CAPTURE_COMPARE_INPUT == synchronized) ||
        (TIMER_B_READ_SYNCHRONIZED_CAPTURECOMPAREINPUT == synchronized)
        );

    if (HWREG16(baseAddress + captureCompareRegister) & synchronized){
        return ( TIMER_B_CAPTURECOMPARE_INPUT_HIGH) ;
    } else   {
        return ( TIMER_B_CAPTURECOMPARE_INPUT_LOW) ;
    }
}

//*****************************************************************************
//
//! Get ouput bit for output mode
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! \return \b TIMER_B_OUTPUTMODE_OUTBITVALUE_HIGH or
//!         \b TIMER_B_OUTPUTMODE_OUTBITVALUE_LOW
//
//*****************************************************************************
uint8_t TIMER_B_getOutputForOutputModeOutBitValue
    (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    if (HWREG16(baseAddress + captureCompareRegister) & OUT){
        return ( TIMER_B_OUTPUTMODE_OUTBITVALUE_HIGH) ;
    } else   {
        return ( TIMER_B_OUTPUTMODE_OUTBITVALUE_LOW) ;
    }
}

//*****************************************************************************
//
//! Get current capturecompare count
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! \return current count as uint16_t
//
//*****************************************************************************
uint16_t TIMER_B_getCaptureCompareCount
    (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    return  (HWREG16(baseAddress + OFS_TBxR + captureCompareRegister));
}

//*****************************************************************************
//
//! Set ouput bit for output mode
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureCompareRegister selects the Capture register being used.
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param outputModeOutBitValueis the value to be set for out bit
//!     Valid values are \b TIMER_B_OUTPUTMODE_OUTBITVALUE_HIGH
//!                      \b TIMER_B_OUTPUTMODE_OUTBITVALUE_LOW
//!
//! Modified register is \b TAxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_setOutputForOutputModeOutBitValue
    (uint32_t baseAddress,
    uint16_t captureCompareRegister,
    uint8_t outputModeOutBitValue
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    assert((TIMER_B_OUTPUTMODE_OUTBITVALUE_HIGH == outputModeOutBitValue) ||
        (TIMER_B_OUTPUTMODE_OUTBITVALUE_LOW == outputModeOutBitValue)
        );

    HWREG16(baseAddress + captureCompareRegister) &= ~OUT;
    HWREG16(baseAddress + captureCompareRegister) |= outputModeOutBitValue;
}

//*****************************************************************************
//
//! Generate a PWM with TimerB running in up mode
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSource selects Clock source. Valid values are
//!         \b TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK
//!         \b TIMER_B_CLOCKSOURCE_ACLK
//!         \b TIMER_B_CLOCKSOURCE_SMCLK
//!         \b TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK
//! \param clockSourceDivider is the divider for Clock source. Valid values are
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_1
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_2
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_4
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_8
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_3
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_5
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_6
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_7
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_10
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_12
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_14
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_16
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_20
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_24
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_28
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_32
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_40
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_48
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_56
//!        \b TIMER_B_CLOCKSOURCE_DIVIDER_64
//! \param timerPeriod selects the desired TimerB period
//! \param compareRegister selects the compare register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param compareOutputMode specifies the ouput mode. Valid values are
//!        \b TIMER_B_OUTPUTMODE_OUTBITVALUE,
//!        \b TIMER_B_OUTPUTMODE_SET,
//!        \b TIMER_B_OUTPUTMODE_TOGGLE_RESET,
//!        \b TIMER_B_OUTPUTMODE_SET_RESET
//!        \b TIMER_B_OUTPUTMODE_TOGGLE,
//!        \b TIMER_B_OUTPUTMODE_RESET,
//!        \b TIMER_B_OUTPUTMODE_TOGGLE_SET,
//!        \b TIMER_B_OUTPUTMODE_RESET_SET
//! \param dutyCycle specifies the dutycycle for the generated waveform
//!
//! Modified registers are \b TAxCTL, \b TAxCCR0, \b TAxCCTL0,\b TAxCCTLn
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_generatePWM (  uint32_t baseAddress,
    uint16_t clockSource,
    uint16_t clockSourceDivider,
    uint16_t timerPeriod,
    uint16_t compareRegister,
    uint16_t compareOutputMode,
    uint16_t dutyCycle
    )
{
    assert(
        (TIMER_B_CLOCKSOURCE_EXTERNAL_TXCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_ACLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_SMCLK == clockSource) ||
        (TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK == clockSource)
        );

    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == compareRegister)
        );


    assert((TIMER_B_OUTPUTMODE_OUTBITVALUE == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_SET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE_RESET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_SET_RESET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_RESET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_TOGGLE_SET == compareOutputMode) ||
        (TIMER_B_OUTPUTMODE_RESET_SET == compareOutputMode)
        );

    privateTimerBProcessClockSourceDivider(baseAddress,
        clockSourceDivider
        );

    HWREG16(baseAddress + OFS_TBxCTL)  &=
        ~( TIMER_B_CLOCKSOURCE_INVERTED_EXTERNAL_TXCLK +
           TIMER_B_UPDOWN_MODE + TIMER_B_DO_CLEAR +
           TIMER_B_TBIE_INTERRUPT_ENABLE
           );

    HWREG16(baseAddress + OFS_TBxCTL)  |= ( clockSource +
                                          TIMER_B_UP_MODE +
                                          TIMER_B_DO_CLEAR
                                          );

    HWREG16(baseAddress + OFS_TBxCCR0)  = timerPeriod;

    HWREG16(baseAddress + OFS_TBxCCTL0)  &=
        ~(TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE +
          TIMER_B_OUTPUTMODE_RESET_SET
          );
    HWREG16(baseAddress + compareRegister)  |= compareOutputMode;

    HWREG16(baseAddress + compareRegister + OFS_TBxR) = dutyCycle;
}

//*****************************************************************************
//
//! Stops the TimerB
//!
//! \param baseAddress is the base address of the TimerB module.
//!
//! Modified registers are \b TAxCTL
//!
//! \returns None
//
//*****************************************************************************
void TIMER_B_stop ( uint32_t baseAddress )
{
    HWREG16(baseAddress + OFS_TBxCTL)  &= ~MC_3;
    HWREG16(baseAddress + OFS_TBxCTL)  |= MC_0;
}

//*****************************************************************************
//
//! Private clock source divider helper function
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param clockSourceDivider is the desired divider for the clock source
//!
//! Modified registers are TAxEX0, TAxCTL
//!
//! \returns None
//
//*****************************************************************************
void privateTimerBProcessClockSourceDivider (uint32_t baseAddress,
    uint16_t clockSourceDivider)
{
    HWREG16(baseAddress + OFS_TBxCTL) &= ~ID__8;
    HWREG16(baseAddress + OFS_TBxEX0) &= ~TBIDEX_7;
    switch (clockSourceDivider){
        case TIMER_B_CLOCKSOURCE_DIVIDER_1:
        case TIMER_B_CLOCKSOURCE_DIVIDER_2:
        case TIMER_B_CLOCKSOURCE_DIVIDER_4:
        case TIMER_B_CLOCKSOURCE_DIVIDER_8:
            HWREG16(baseAddress + OFS_TBxCTL) |= ((clockSourceDivider - 1) << 6);
            HWREG16(baseAddress + OFS_TBxEX0) = TBIDEX_0;
            break;

        case TIMER_B_CLOCKSOURCE_DIVIDER_3:
        case TIMER_B_CLOCKSOURCE_DIVIDER_5:
        case TIMER_B_CLOCKSOURCE_DIVIDER_6:
        case TIMER_B_CLOCKSOURCE_DIVIDER_7:
            HWREG16(baseAddress + OFS_TBxCTL) |= ID__1;
            HWREG16(baseAddress + OFS_TBxEX0) = (clockSourceDivider - 1);
            break;

        case TIMER_B_CLOCKSOURCE_DIVIDER_10:
        case TIMER_B_CLOCKSOURCE_DIVIDER_12:
        case TIMER_B_CLOCKSOURCE_DIVIDER_14:
        case TIMER_B_CLOCKSOURCE_DIVIDER_16:
            HWREG16(baseAddress + OFS_TBxCTL) |= ID__2;
            HWREG16(baseAddress + OFS_TBxEX0) = (clockSourceDivider / 2 - 1 );
            break;

        case TIMER_B_CLOCKSOURCE_DIVIDER_20:
        case TIMER_B_CLOCKSOURCE_DIVIDER_24:
        case TIMER_B_CLOCKSOURCE_DIVIDER_28:
        case TIMER_B_CLOCKSOURCE_DIVIDER_32:
            HWREG16(baseAddress + OFS_TBxCTL) |= ID__4;
            HWREG16(baseAddress + OFS_TBxEX0) = (clockSourceDivider / 4 - 1);
            break;
        case TIMER_B_CLOCKSOURCE_DIVIDER_40:
        case TIMER_B_CLOCKSOURCE_DIVIDER_48:
        case TIMER_B_CLOCKSOURCE_DIVIDER_56:
        case TIMER_B_CLOCKSOURCE_DIVIDER_64:
            HWREG16(baseAddress + OFS_TBxCTL) |= ID__8;
            HWREG16(baseAddress + OFS_TBxEX0) = (clockSourceDivider / 8 - 1);
            break;
    }
}

//*****************************************************************************
//
//! Sets the value of the capture-compare register
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param compareRegister selects the Capture register being used. Valid values
//!     are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//! \param compareValue is the count to be compared with in compare mode
//!
//! Modified register is \b TAxCCRn
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_setCompareValue (  uint32_t baseAddress,
    uint16_t compareRegister,
    uint16_t compareValue
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == compareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == compareRegister)
        );

    HWREG16(baseAddress + compareRegister + OFS_TBxR) = compareValue;
}

//*****************************************************************************
//
//! Clears the TimerB TBIFG interrupt flag
//!
//! \param baseAddress is the base address of the TimerB module.
//!
//! Modified bits are TBIFG of TAxCTL register
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_clearTimerInterruptFlag (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_TBxCTL) &= ~TBIFG;
}

//*****************************************************************************
//
//! Clears the capture-compare interrupt flag
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param captureCompareRegister selects the Capture-compare register being
//! used. Valid values are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//!    Refer datasheet to ensure the device has the capture compare register
//!    being used
//!
//! Modified bits are CCIFG of \b TAxCCTLn register
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_clearCaptureCompareInterruptFlag (uint32_t baseAddress,
    uint16_t captureCompareRegister
    )
{
    assert((TIMER_B_CAPTURECOMPARE_REGISTER_0 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_1 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_2 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_3 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_4 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_5 == captureCompareRegister) ||
        (TIMER_B_CAPTURECOMPARE_REGISTER_6 == captureCompareRegister)
        );

    HWREG16(baseAddress + captureCompareRegister)  &= ~CCIFG;
}

//*****************************************************************************
//
//! Selects TimerB counter length
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param counterLength selects the value of counter length.
//! Valid values are
//!     \b TIMER_B_COUNTER_16BIT [Default value]
//!     \b TIMER_B_COUNTER_12BIT
//!     \b TIMER_B_COUNTER_10BIT
//!     \b TIMER_B_COUNTER_8BIT
//!
//! Modified bits are CNTL of \b TBxCTL register
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_selectCounterLength (uint16_t  baseAddress,
		uint16_t counterLength
		)
{
	assert((TIMER_B_COUNTER_8BIT == counterLength) ||
	        (TIMER_B_COUNTER_10BIT == counterLength) ||
	        (TIMER_B_COUNTER_12BIT == counterLength) ||
	        (TIMER_B_COUNTER_16BIT == counterLength)
	        );


	HWREG16(baseAddress + OFS_TBxCTL) &= ~CNTL_3;
	HWREG16(baseAddress + OFS_TBxCTL) |= counterLength;
}
//*****************************************************************************
//
//! Selects TimerB Latching Group
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param groupLatch selects the value of counter length.
//! Valid values are
//!     \b TIMER_B_GROUP_NONE [Default value]
//!     \b TIMER_B_GROUP_CL12_CL23_CL56
//!     \b TIMER_B_GROUP_CL123_CL456
//!     \b TIMER_B_GROUP_ALL
//!
//! Modified bits are TBCLGRP of \b TBxCTL register
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_selectLatchingGroup(uint16_t  baseAddress,
		uint16_t  groupLatch)
{
	assert((TIMER_B_GROUP_NONE  == groupLatch) ||
		   (TIMER_B_GROUP_CL12_CL23_CL56 == groupLatch) ||
		   (TIMER_B_GROUP_CL123_CL456 == groupLatch) ||
		   (TIMER_B_GROUP_ALL == groupLatch)
		   );


	HWREG16(baseAddress + OFS_TBxCTL) &= ~TBCLGRP_3;
	HWREG16(baseAddress + OFS_TBxCTL) |= groupLatch;
}
//*****************************************************************************
//
//! Selects Compare Latch Load Event
//!
//! \param baseAddress is the base address of the TimerB module.
//! \param compareRegister selects the Capture-compare register being
//! used. Valid values are
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_0
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_1
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_2
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_3
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_4
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_5
//!     \b TIMER_B_CAPTURECOMPARE_REGISTER_6
//! \param compareLatchLoadEvent selects the latch load event
//! Valid values are
//!     \b TIMER_B_LATCH_ON_WRITE_TO_TBxCCRn_COMPARE_REGISTER [Default value]
//!     \b TIMER_B_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UP_OR_CONT_MODE
//!     \b TIMER_B_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UPDOWN_MODE
//!     \b TIMER_B_LATCH_WHEN_COUNTER_COUNTS_TO_CURRENT_COMPARE_LATCH_VALUE
//!
//! Modified bits are CLLD of \b TBxCCTLn register
//!
//! \return None
//
//*****************************************************************************
void TIMER_B_initCompareLatchLoadEvent(uint16_t  baseAddress,
		uint16_t  compareRegister,
		uint16_t  compareLatchLoadEvent
		)
{
	assert((TIMER_B_LATCH_ON_WRITE_TO_TBxCCRn_COMPARE_REGISTER  == compareLatchLoadEvent) ||
		(TIMER_B_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UP_OR_CONT_MODE == compareLatchLoadEvent) ||
		(TIMER_B_LATCH_WHEN_COUNTER_COUNTS_TO_0_IN_UPDOWN_MODE == compareLatchLoadEvent) ||
		(TIMER_B_LATCH_WHEN_COUNTER_COUNTS_TO_CURRENT_COMPARE_LATCH_VALUE == compareLatchLoadEvent)
		);

	HWREG16(baseAddress + compareRegister)  &= ~CLLD_3;
	HWREG16(baseAddress + compareRegister)  |= compareLatchLoadEvent;
}

//*****************************************************************************
//
//! Reads the current timer count value
//!
//! \param baseAddress is the base address of the Timer module.
//!
//! Reads the current count value of the timer. There is a majority vote
//! system in place to confirm an accurate value is returned. The
//! TIMER_B_THRESHOLD #define in timer_b.h can be modified so that the votes
//! must be closer together for a consensus to occur.
//!
//! \return Majority vote of timer count value
//
//*****************************************************************************
uint16_t TIMER_B_getCounterValue (uint32_t baseAddress)
{
	uint16_t voteOne, voteTwo, res;

    voteTwo = HWREG16(baseAddress + OFS_TBxR);

	do
    {
        voteOne = voteTwo;
        voteTwo = HWREG16(baseAddress + OFS_TBxR);

		if(voteTwo > voteOne) {
			res = voteTwo - voteOne;
		} else if(voteOne > voteTwo) {
			res = voteOne - voteTwo;
		} else{
			res = 0;
		}

    } while ( res > TIMER_B_THRESHOLD);

    return voteTwo;
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
