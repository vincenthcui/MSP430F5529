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
//pmm.c - Driver for the PMM Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "assert.h"
#include "pmm.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif

//*****************************************************************************
//
//! Enables the low-side SVS circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvsL (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= SVSLE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the low-side SVS circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvsL (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~SVSLE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the low-side SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvmL (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= SVMLE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the low-side SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvmL (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~SVMLE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the high-side SVS circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvsH (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= SVSHE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the high-side SVS circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvsH (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~SVSHE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the high-side SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvmH (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= SVMHE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the high-side SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvmH (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~SVMHE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the low-side SVS and SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvsLSvmL (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= (SVSLE + SVMLE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the low-side SVS and SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvsLSvmL (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~(SVSLE + SVMLE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the high-side SVS and SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvsHSvmH (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= (SVSHE + SVMHE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the high-side SVS and SVM circuitry
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvsHSvmH (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~(SVSHE + SVMHE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the POR signal generation when a low-voltage event is
//! registered by the low-side SVS
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvsLReset (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) |= SVSLPE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the POR signal generation when a low-voltage event is
//! registered by the low-side SVS
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvsLReset (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) &= ~SVSLPE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the interrupt generation when a low-voltage event is
//! registered by the low-side SVM
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvmLInterrupt (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) |= SVMLIE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the interrupt generation when a low-voltage event is
//! registered by the low-side SVM
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvmLInterrupt (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) &= ~SVMLIE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the POR signal generation when a low-voltage event is
//! registered by the high-side SVS
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvsHReset (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) |= SVSHPE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the POR signal generation when a low-voltage event is
//! registered by the high-side SVS
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvsHReset (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) &= ~SVSHPE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables the interrupt generation when a low-voltage event is
//! registered by the high-side SVM
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_enableSvmHInterrupt (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) |= SVMHIE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables the interrupt generation when a low-voltage event is
//! registered by the high-side SVM
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_disableSvmHInterrupt (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_PMMRIE) &= ~SVMHIE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Clear all interrupt flags for the PMM
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b PMMIFG.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_clearPMMIFGS (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG8(baseAddress + OFS_PMMIFG) = 0;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables supervisor low side in LPM with twake-up-fast from LPM2, LPM3,
//! and LPM4
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************

void PMM_SvsLEnabledInLPMFastWake (uint32_t baseAddress)
{
    //These settings use SVSH/LACE = 0
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= (SVSLFP + SVSLMD);
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~SVSMLACE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables supervisor low side in LPM with twake-up-slow  from LPM2, LPM3,
//! and LPM4
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsLEnabledInLPMSlowWake (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= SVSLMD;
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~(SVSLFP + SVSMLACE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables supervisor low side in LPM with twake-up-fast from LPM2, LPM3,
//! and LPM4
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsLDisabledInLPMFastWake (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= SVSLFP;
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~(SVSLMD + SVSMLACE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables supervisor low side in LPM with twake-up-slow from LPM2, LPM3,
//! and LPM4
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsLDisabledInLPMSlowWake (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) &= ~(SVSLFP + SVSMLACE + SVSLMD);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables supervisor high side in LPM with tpd = 20 탎(1)
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsHEnabledInLPMNormPerf (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= SVSHMD;
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~(SVSMHACE + SVSHFP);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Enables supervisor high side in LPM with tpd = 2.5 탎(1)
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsHEnabledInLPMFullPerf (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= (SVSHMD + SVSHFP);
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~SVSMHACE;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables supervisor high side in LPM with tpd = 20 탎(1)
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsHDisabledInLPMNormPerf (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~(SVSMHACE + SVSHFP + SVSHMD);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Disables supervisor high side in LPM with tpd = 2.5 탎(1)
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMHCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsHDisabledInLPMFullPerf (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= SVSHFP;
    HWREG16(baseAddress + OFS_SVSMHCTL) &= ~(SVSMHACE + SVSHMD);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Optimized to provide twake-up-fast from LPM2, LPM3, and LPM4 with least
//! power
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsLOptimizedInLPMFastWake (uint32_t baseAddress)
{
    //These setting use SVSH/LACE = 1
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMLCTL) |= (SVSLFP + SVSLMD + SVSMLACE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Optimized to provide tpd = 2.5 탎(1) in LPM with least power
//!
//! \param baseAddress is the base address of the PMM module.
//!
//! Modified registers are \b PMMCTL0, \b SVSMLCTL.
//!
//! \return NONE
//
//*****************************************************************************
void PMM_SvsHOptimizedInLPMFullPerf (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;
    HWREG16(baseAddress + OFS_SVSMHCTL) |= (SVSHMD + SVSHFP + SVSMHACE);
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
}

//*****************************************************************************
//
//! Increase Vcore by one level
//!
//! \param baseAddress is the base address of the I2C module.
//! \param level level to which Vcore needs to be increased
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE, \b PMMIFG, \b SVSMLCTL,
//! \b SVSMHCTL.
//!
//! \return STATUS_SUCCESS or STATUS_FAIL
//
//*****************************************************************************
uint16_t PMM_setVCoreUp (uint32_t baseAddress, uint8_t level)
{
    uint32_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

    //The code flow for increasing the Vcore has been altered to work around
    //the erratum FLASH37.
    //Please refer to the Errata sheet to know if a specific device is affected
    //DO NOT ALTER THIS FUNCTION

    //Open PMM registers for write access
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;

    //Disable dedicated Interrupts
    //Backup all registers
    PMMRIE_backup = HWREG8(baseAddress + OFS_PMMRIE);
    HWREG8(baseAddress + OFS_PMMRIE) &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE |
                                          SVSLPE | SVMHVLRIE | SVMHIE |
                                          SVSMHDLYIE | SVMLVLRIE | SVMLIE |
                                          SVSMLDLYIE
                                          );
    SVSMHCTL_backup = HWREG8(baseAddress + OFS_SVSMHCTL);
    SVSMLCTL_backup = HWREG8(baseAddress + OFS_SVSMLCTL);

    //Clear flags
    HWREG8(baseAddress + OFS_PMMIFG) = 0;

    //Set SVM highside to new level and check if a VCore increase is possible
    HWREG8(baseAddress + OFS_SVSMHCTL) = SVMHE | SVSHE | (SVSMHRRL0 * level);

    //Wait until SVM highside is settled
    while ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMHDLYIFG) == 0) ;

    //Clear flag
    HWREG8(baseAddress + OFS_PMMIFG) &= ~SVSMHDLYIFG;

    //Check if a VCore increase is possible
    if ((HWREG8(baseAddress + OFS_PMMIFG) & SVMHIFG) == SVMHIFG){
        //-> Vcc is too low for a Vcore increase
        //recover the previous settings
        HWREG8(baseAddress + OFS_PMMIFG) &= ~SVSMHDLYIFG;
        HWREG8(baseAddress + OFS_SVSMHCTL) = SVSMHCTL_backup;

        //Wait until SVM highside is settled
        while ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMHDLYIFG) == 0) ;

        //Clear all Flags
        HWREG8(baseAddress +
            OFS_PMMIFG) &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                             SVMLVLRIFG | SVMLIFG |
                             SVSMLDLYIFG
                             );

        //Restore PMM interrupt enable register
        HWREG8(baseAddress + OFS_PMMRIE) = PMMRIE_backup;
        //Lock PMM registers for write access
        HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
        //return: voltage not set
        return ( STATUS_FAIL) ;
    }

    //Set also SVS highside to new level
    //Vcc is high enough for a Vcore increase
    HWREG8(baseAddress + OFS_SVSMHCTL) |= (SVSHRVL0 * level);

    //Wait until SVM highside is settled
    while ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMHDLYIFG) == 0) ;

    //Clear flag
    HWREG8(baseAddress + OFS_PMMIFG) &= ~SVSMHDLYIFG;

    //Set VCore to new level
    HWREG8(baseAddress + OFS_PMMCTL0_L) = PMMCOREV0 * level;

    //Set SVM, SVS low side to new level
    HWREG8(baseAddress + OFS_SVSMLCTL) = SVMLE | (SVSMLRRL0 * level) |
                                         SVSLE | (SVSLRVL0 * level);

    //Wait until SVM, SVS low side is settled
    while ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMLDLYIFG) == 0) ;

    //Clear flag
    HWREG8(baseAddress + OFS_PMMIFG) &= ~SVSMLDLYIFG;
    //SVS, SVM core and high side are now set to protect for the new core level

    //Restore Low side settings
    //Clear all other bits _except_ level settings
    HWREG8(baseAddress + OFS_SVSMLCTL) &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 +
                                           SVSMLRRL1 + SVSMLRRL2
                                           );

    //Clear level settings in the backup register,keep all other bits
    SVSMLCTL_backup &=
        ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

    //Restore low-side SVS monitor settings
    HWREG8(baseAddress + OFS_SVSMLCTL) |= SVSMLCTL_backup;

    //Restore High side settings
    //Clear all other bits except level settings
    HWREG8(baseAddress + OFS_SVSMHCTL) &= (SVSHRVL0 + SVSHRVL1 +
                                           SVSMHRRL0 + SVSMHRRL1 +
                                           SVSMHRRL2
                                           );

    //Clear level settings in the backup register,keep all other bits
    SVSMHCTL_backup &=
        ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

    //Restore backup
    HWREG8(baseAddress + OFS_SVSMHCTL) |= SVSMHCTL_backup;

    //Wait until high side, low side settled
    while (((HWREG8(baseAddress + OFS_PMMIFG) & SVSMLDLYIFG) == 0) &&
           ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMHDLYIFG) == 0)) ;

    //Clear all Flags
    HWREG8(baseAddress + OFS_PMMIFG) &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                                          SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG
                                          );

    //Restore PMM interrupt enable register
    HWREG8(baseAddress + OFS_PMMRIE) = PMMRIE_backup;

    //Lock PMM registers for write access
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;

    return ( STATUS_SUCCESS) ;
}

//*****************************************************************************
//
//! Decrease Vcore by one level
//!
//! \param baseAddress is the base address of the I2C module.
//! \param level level to which Vcore needs to be decreased
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE, \b PMMIFG, \b SVSMLCTL,
//! \b SVSMHCTL.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint16_t PMM_setVCoreDown (uint32_t baseAddress, uint8_t level)
{
    uint32_t PMMRIE_backup, SVSMHCTL_backup, SVSMLCTL_backup;

    //The code flow for decreasing the Vcore has been altered to work around
    //the erratum FLASH37.
    //Please refer to the Errata sheet to know if a specific device is affected
    //DO NOT ALTER THIS FUNCTION

    //Open PMM registers for write access
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0xA5;

    //Disable dedicated Interrupts
    //Backup all registers
    PMMRIE_backup = HWREG8(baseAddress + OFS_PMMRIE);
    HWREG8(baseAddress + OFS_PMMRIE) &= ~(SVMHVLRPE | SVSHPE | SVMLVLRPE |
                                          SVSLPE | SVMHVLRIE | SVMHIE |
                                          SVSMHDLYIE | SVMLVLRIE | SVMLIE |
                                          SVSMLDLYIE
                                          );
    SVSMHCTL_backup = HWREG8(baseAddress + OFS_SVSMHCTL);
    SVSMLCTL_backup = HWREG8(baseAddress + OFS_SVSMLCTL);

    //Clear flags
    HWREG8(baseAddress + OFS_PMMIFG) &= ~(SVMHIFG | SVSMHDLYIFG |
                                          SVMLIFG | SVSMLDLYIFG
                                          );

    //Set SVM, SVS high & low side to new settings in normal mode
    HWREG8(baseAddress + OFS_SVSMHCTL) = SVMHE | (SVSMHRRL0 * level) |
                                         SVSHE | (SVSHRVL0 * level);
    HWREG8(baseAddress + OFS_SVSMLCTL) = SVMLE | (SVSMLRRL0 * level) |
                                         SVSLE | (SVSLRVL0 * level);

    //Wait until SVM high side and SVM low side is settled
    while ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMHDLYIFG) == 0 ||
           (HWREG8(baseAddress + OFS_PMMIFG) & SVSMLDLYIFG) == 0) ;

    //Clear flags
    HWREG8(baseAddress + OFS_PMMIFG) &= ~(SVSMHDLYIFG + SVSMLDLYIFG);
    //SVS, SVM core and high side are now set to protect for the new core level

    //Set VCore to new level
    HWREG8(baseAddress + OFS_PMMCTL0_L) = PMMCOREV0 * level;

    //Restore Low side settings
    //Clear all other bits _except_ level settings
    HWREG8(baseAddress + OFS_SVSMLCTL) &= (SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 +
                                           SVSMLRRL1 + SVSMLRRL2
                                           );

    //Clear level settings in the backup register,keep all other bits
    SVSMLCTL_backup &=
        ~(SVSLRVL0 + SVSLRVL1 + SVSMLRRL0 + SVSMLRRL1 + SVSMLRRL2);

    //Restore low-side SVS monitor settings
    HWREG8(baseAddress + OFS_SVSMLCTL) |= SVSMLCTL_backup;

    //Restore High side settings
    //Clear all other bits except level settings
    HWREG8(baseAddress + OFS_SVSMHCTL) &= (SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 +
                                           SVSMHRRL1 + SVSMHRRL2
                                           );

    //Clear level settings in the backup register, keep all other bits
    SVSMHCTL_backup &=
        ~(SVSHRVL0 + SVSHRVL1 + SVSMHRRL0 + SVSMHRRL1 + SVSMHRRL2);

    //Restore backup
    HWREG8(baseAddress + OFS_SVSMHCTL) |= SVSMHCTL_backup;

    //Wait until high side, low side settled
    while (((HWREG8(baseAddress + OFS_PMMIFG) & SVSMLDLYIFG) == 0) &&
           ((HWREG8(baseAddress + OFS_PMMIFG) & SVSMHDLYIFG) == 0)) ;

    //Clear all Flags
    HWREG8(baseAddress + OFS_PMMIFG) &= ~(SVMHVLRIFG | SVMHIFG | SVSMHDLYIFG |
                                          SVMLVLRIFG | SVMLIFG | SVSMLDLYIFG
                                          );

    //Restore PMM interrupt enable register
    HWREG8(baseAddress + OFS_PMMRIE) = PMMRIE_backup;
    //Lock PMM registers for write access
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0x00;
    //Return: OK
    return ( STATUS_SUCCESS) ;
}

//*****************************************************************************
//
//! Set Vcore to expected level
//!
//! \param baseAddress is the base address of the I2C module.
//! \param level level to which Vcore needs to be decreased/increased
//!         Valid values are
//!         \b PMM_CORE_LEVEL_0 [Default Value],
//!         \b PMM_CORE_LEVEL_1
//!         \b PMM_CORE_LEVEL_2
//!         \b PMM_CORE_LEVEL_3
//!
//! Modified registers are \b PMMCTL0, \b PMMRIE, \b PMMIFG, \b SVSMLCTL,
//! \b SVSMHCTL.
//!
//! \return STATUS_SUCCESS or STATUS_FAIL
//
//*****************************************************************************
unsigned short PMM_setVCore (uint32_t baseAddress, uint8_t level)
{
    assert(
        (PMM_CORE_LEVEL_0 == level) ||
        (PMM_CORE_LEVEL_1 == level) ||
        (PMM_CORE_LEVEL_2 == level) ||
        (PMM_CORE_LEVEL_3 == level)
        );

    uint8_t actlevel;
    uint16_t status = STATUS_SUCCESS;

    //Set Mask for Max. level
    level &= PMMCOREV_3;

    //Get actual VCore
    actlevel = (HWREG8(baseAddress + OFS_PMMCTL0) & PMMCOREV_3);

    //step by step increase or decrease
    while ((level != actlevel) && (status == STATUS_SUCCESS))
    {
        if (level > actlevel){
            status = PMM_setVCoreUp(baseAddress, ++actlevel);
        } else   {
            status = PMM_setVCoreDown(baseAddress, --actlevel);
        }
    }

    return ( status) ;
}

//*****************************************************************************
//
//! Returns interrupt status
//!
//! \param baseAddress is the base address of the I2C module.
//! \param mask is the mask for specifying the required flag
//!        Valid values are
//!            \b  PMM_SVSMLDLYIFG
//!            \b  PMM_SVMLIFG,
//!            \b  PMM_SVMLVLRIFG,
//!            \b  PMM_SVSMHDLYIFG,
//!            \b  PMM_SVMHIFG,
//!            \b  PMM_SVMHVLRIFG,
//!            \b  PMM_PMMBORIFG,
//!            \b  PMM_PMMRSTIFG,
//!            \b  PMM_PMMPORIFG,
//!            \b  PMM_SVSHIFG,
//!            \b  PMM_SVSLIFG,
//!            \b  PMM_PMMLPM5IFG
//!
//! \return STATUS_SUCCESS or STATUS_FAIL
//
//*****************************************************************************
uint16_t PMM_getInterruptStatus (uint32_t baseAddress,
    uint16_t mask)
{
    return ( (HWREG16(baseAddress + OFS_PMMIFG)) & mask );
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
