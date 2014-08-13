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
//dac12_a.c - Driver for the DAC12_A Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "dac12_a.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif
#include "assert.h"


//*****************************************************************************
//
//! Initializes the DAC12_A module with the specified settings.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//! \param outputSelect selects the output pin that the selected DAC12_A module
//!       will output to.
//!        Valid values are
//!        \b DAC12_A_OUTPUT_1 [Default]
//!        \b DAC12_A_OUTPUT_2
//!        Modified bits are \b DAC12OPS of \b DAC12_A_xCTL0 register.
//! \param positiveReferenceVoltage is the upper limit voltage that the data can
//!       be converted in to.
//!        Valid values are
//!        \b DAC12_A_VREF_VCC [Default]
//!        \b DAC12_A_VREF_INT
//!        \b DAC12_A_VREF_EXT
//!        Modified bits are \b DAC12SREFx of \b DAC12_A_xCTL0 register.
//! \param outputVoltageMultiplier is the multiplier of the Vout voltage.
//!        Valid values are
//!        \b DAC12_A_VREFx1 [Default]
//!        \b DAC12_A_VREFx2
//!        \b DAC12_A_VREFx3
//!        Modified bits are \b DAC12IR of \b DAC12_A_xCTL0 register and
//!        \b DAC12OG of \b DAC12CTL1 register.
//! \param amplifierSetting is the setting of the settling speed and current of
//!       the Vref+ and the Vout buffer.
//!        Valid values are
//!        \b DAC12_A_AMP_OFF_PINOUTHIGHZ - Initialize the DAC12_A Module with
//!             settings, but do not turn it on. [Default]
//!        \b DAC12_A_AMP_OFF_PINOUTLOW - Initialize the DAC12_A Module with
//!             settings, and allow it to take control of the selected output
//!             pin to pull it low (Note: this takes control away port mapping
//!             module).
//!        \b DAC12_A_AMP_LOWIN_LOWOUT - Select a slow settling speed and current
//!             for Vref+ input buffer and for Vout output buffer.
//!        \b DAC12_A_AMP_LOWIN_MEDOUT - Select a slow settling speed and current
//!             for Vref+ input buffer and a medium settling speed and current
//!             for Vout output buffer.
//!        \b DAC12_A_AMP_LOWIN_HIGHOUT - Select a slow settling speed and current
//!             for Vref+ input buffer and a high settling speed and current for
//!             Vout output buffer.
//!        \b DAC12_A_AMP_MEDIN_MEDOUT - Select a medium settling speed and
//!             current for Vref+ input buffer and for Vout output buffer.
//!        \b DAC12_A_AMP_MEDIN_HIGHOUT - Select a medium settling speed and
//!             current for Vref+ input buffer and a high settling speed and
//!             current for Vout output buffer.
//!        \b DAC12_A_AMP_HIGHIN_HIGHOUT - Select a high settling speed and
//!             current for Vref+ input buffer and for Vout output buffer.
//!        Modified bits are \b DAC12AMPx of \b DAC12_A_xCTL0 register.
//! \param conversionTriggerSelect selects the trigger that will start a
//!       conversion.
//!        Valid values are
//!        \b DAC12_A_TRIGGER_ENCBYPASS - Automatically converts data as soon as
//!             it is written into the data buffer. (Note: Do not use this
//!             selection if grouping DAC's). [Default]
//!        \b DAC12_A_TRIGGER_ENC - Requires a call to enableConversions() to
//!             allow a conversion, but starts a conversion as soon as data is
//!             written to the data buffer (Note: with DAC12_A module's grouped,
//!             data has to be set in BOTH DAC12_A data buffers to start a
//!             conversion).
//!        \b DAC12_A_TRIGGER_TA - Requires a call to enableConversions() to allow
//!             a conversion, and a rising edge of Timer_A's Out1 (TA1) to start
//!             a conversion.
//!        \b DAC12_A_TRIGGER_TB - Requires a call to enableConversions() to allow
//!             a conversion, and a rising edge of Timer_B's Out2 (TB2) to start
//!             a conversion.
//!        Modified bits are \b DAC12LSELx of \b DAC12_A_xCTL0 register.
//!
//! This function initializes the DAC12_A module with the specified settings. Upon
//! successful completion of the initialization of this module the control
//! registers and interrupts of this module are all reset, and the specified
//! variables will be set. Please note, that if conversions are enabled with the
//! enableConversions() function, then disableConversions() must be called
//! before re-initializing the DAC12_A module with this function.
//!
//! \return STATUS_SUCCESS or STATUS_FAILURE of the initialization process.
//
//*****************************************************************************
unsigned short DAC12_A_init (uint32_t baseAddress,
    uint8_t submoduleSelect,
    unsigned short outputSelect,
    uint16_t positiveReferenceVoltage,
    uint16_t outputVoltageMultiplier,
    uint8_t amplifierSetting,
    uint16_t conversionTriggerSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);
    assert(outputSelect <= DAC12_A_OUTPUT_2);
    assert(positiveReferenceVoltage <= DAC12_A_VREF_EXT);
    assert(outputVoltageMultiplier <= DAC12_A_VREFx3);
    assert(amplifierSetting <= DAC12_A_AMP_HIGHIN_HIGHOUT);
    assert(conversionTriggerSelect <= DAC12_A_TRIGGER_TB);

    baseAddress += submoduleSelect;           //Add 0x10 to base address IF
                                              //DAC12_A_1 is selected.
    uint8_t retVal = STATUS_SUCCESS;

    HWREG16(baseAddress + OFS_DAC12_0CTL1) &= ~(DAC12OG + DAC12DFJ);

    //Reset and Set DAC12_A Control 0 Bits
    HWREG16(baseAddress + OFS_DAC12_0CTL0) = DAC12OPS
                                           + positiveReferenceVoltage
                                           + amplifierSetting
                                           + conversionTriggerSelect;

    if (DAC12_A_VREFx1 == outputVoltageMultiplier){
        HWREG16(baseAddress + OFS_DAC12_0CTL0) |= DAC12IR;
    } else if (DAC12_A_VREFx2 == outputVoltageMultiplier){
        HWREG16(baseAddress + OFS_DAC12_0CTL1) |= DAC12OG;
    }
    //else if(DAC12_A_VREFx3 == outputVoltageMultiplier)
    //Both DAC12IR and DAC12OG values == 0

    return ( retVal) ;
}

//*****************************************************************************
//
//! Sets the amplifier settings for the Vref+ and Vout buffers.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//! \param amplifierSetting is the setting of the settling speed and current of
//!       the Vref+ and the Vout buffer.
//!        Valid values are
//!        \b DAC12_A_AMP_OFF_PINOUTHIGHZ - Initialize the DAC12_A Module with
//!             settings, but do not turn it on. [Default]
//!        \b DAC12_A_AMP_OFF_PINOUTLOW - Initialize the DAC12_A Module with
//!             settings, and allow it to take control of the selected output
//!             pin to pull it low (Note: this takes control away port mapping
//!             module).
//!        \b DAC12_A_AMP_LOWIN_LOWOUT - Select a slow settling speed and current
//!             for Vref+ input buffer and for Vout output buffer.
//!        \b DAC12_A_AMP_LOWIN_MEDOUT - Select a slow settling speed and current
//!             for Vref+ input buffer and a medium settling speed and current
//!             for Vout output buffer.
//!        \b DAC12_A_AMP_LOWIN_HIGHOUT - Select a slow settling speed and current
//!             for Vref+ input buffer and a high settling speed and current for
//!             Vout output buffer.
//!        \b DAC12_A_AMP_MEDIN_MEDOUT - Select a medium settling speed and
//!             current for Vref+ input buffer and for Vout output buffer.
//!        \b DAC12_A_AMP_MEDIN_HIGHOUT - Select a medium settling speed and
//!             current for Vref+ input buffer and a high settling speed and
//!             current for Vout output buffer.
//!        \b DAC12_A_AMP_HIGHIN_HIGHOUT - Select a high settling speed and
//!             current for Vref+ input buffer and for Vout output buffer.
//!        Modified bits are \b DAC12LSELx of \b DAC12_A_xCTL0 register.
//!
//! This function sets the amplifier settings of the DAC12_A module for the Vref+
//! and Vout buffers without re-initializing the DAC12_A module. This can be used
//! to disable the control of the pin by the DAC12_A module.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_setAmplifierSetting (uint32_t baseAddress,
    uint8_t submoduleSelect,
    uint8_t amplifierSetting)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);
    assert(amplifierSetting <= DAC12_A_AMP_HIGHIN_HIGHOUT);

    //Reset amplifier setting to set it
    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) &= ~(DAC12AMP_7);
    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) |= amplifierSetting;
}

//*****************************************************************************
//
//! Clears the amplifier settings to disable the DAC12_A module.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function clears the amplifier settings for the selected DAC12_A module to
//! disable the DAC12_A module.
//! Modified bits are \b DAC12AMP_7 of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_disable (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
  assert(submoduleSelect <= DAC12_A_SUBMODULE_1);
  //Reset amplifier setting to turn DAC12_A off completely
  HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) &= ~(DAC12AMP_7);
}

//*****************************************************************************
//
//! Enables grouping of two DAC12_A modules in a dual DAC12_A system.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//!
//! This function enables grouping two DAC12_A modules in a dual DAC12_A system.
//! Both DAC12_A modules will work in sync, converting data at the same time. To
//! convert data, the same trigger should be set for both DAC12_A modules during
//! initialization (which should not be DAC12_A_TRIGGER_ENCBYPASS), the
//! enableConversions() function needs to be called with both DAC12_A modules, and
//! data needs to be set for both DAC12_A modules seperately.
//!
//! Modified bits are \b DAC12GRP of \b DAC12_A_xCTL0 register.
//! \return NONE
//
//*****************************************************************************
void DAC12_A_enableGrouping (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_DAC12_0CTL0) |= DAC12GRP;
}

//*****************************************************************************
//
//! Disables grouping of two DAC12_A modules in a dual DAC12_A system.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//!
//! This function disables grouping of two DAC12_A modules in a dual DAC12_A system.
//!
//! Modified bits are \b DAC12GRP of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_disableGrouping (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_DAC12_0CTL0) &= ~(DAC12GRP);
}

//*****************************************************************************
//
//! Enables the DAC12_A module interrupt source.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function to enable the DAC12_A module interrupt, which throws an
//! interrupt when the data buffer is available for new data to be set. Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor. Note that an interrupt is
//! not thrown when DAC12_A_TRIGGER_AUTO has been set for the parameter
//! conversionTriggerSelect in initialization.<b>Does not clear interrupt 
//! flags.</b>
//!
//! Modified bits are \b DAC12IE of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_enableInterrupt (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) |= DAC12IE;
}

//*****************************************************************************
//
//! Disables the DAC12_A module interrupt source.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! Enables the DAC12_A module interrupt source. Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! Modified bits are \b DAC12IE bits of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_disableInterrupt (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) &= ~(DAC12IE);
}

//*****************************************************************************
//
//! Returns the status of the DAC12_A module interrupt flag.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function returns the status of the DAC12_A module interrupt flag. Note
//! that an interrupt is not thrown when DAC12_A_TRIGGER_AUTO has been set for
//! the conversionTriggerSelect parameter in initialization.
//!
//! \return The current interrupt flag status for the selected DAC submodule,
//!        DAC12_A_INT_ACTIVE if the interrupt flag is asserted,
//!        DAC12_A_INT_INACTIVE otherwise.
//
//*****************************************************************************
unsigned short DAC12_A_getInterruptStatus (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    if (HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) & DAC12IFG){
        return ( DAC12_A_INT_ACTIVE) ;
    } else   {
        return ( DAC12_A_INT_INACTIVE) ;
    }
}

//*****************************************************************************
//
//! Clears the DAC12_A module interrupt flag.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! The DAC12_A module interrupt flag is cleared, so that it no longer asserts.
//! Note that an interrupt is not thrown when DAC12_A_TRIGGER_AUTO has been set
//! for the parameter conversionTriggerSelect in initialization.
//!
//! Modified bits are \b DAC12IFG of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_clearInterrupt (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) &= ~(DAC12IFG);
}

//*****************************************************************************
//
//! Calibrates the output offset.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function disables the calibration lock, starts the calibration, whats
//! for the calibration to complete, and then relocks the calibration lock.
//! Please note, this function should be called after initializing the dac12
//! module, and before using it.
//!
//! Modified bits are \b DAC12CALON of \b DAC12_A_xCTL0 register and \b DAC12PW of
//! \b DAC12_A_0CALCTL register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_calibrateOutput (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    //Unlock Calibration
    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CALCTL) = DAC12PW;

    //Start Calibration
    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) |= DAC12CALON;

    //Wait for Calibration to Finish
    while (HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) & DAC12CALON);

    //Lock Calibration
    HWREG16(baseAddress + submoduleSelect +
        OFS_DAC12_0CALCTL) = DAC12PW + DAC12LOCK;
}

//*****************************************************************************
//
//! Returns the calibrated offset of the output buffer.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function returns the calibrated offset of the output buffer. The output
//! buffer offset is used to obtain accurate results from the output pin. This
//! function should only be used while the calibration lock is enabled. Only the
//! lower byte of the word of the register is returned, and the value is between
//! -128 and +127.
//!
//! \return The calibrated offset of the output buffer.
//
//*****************************************************************************
int DAC12_A_getCalibrationData (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    return ( (int)( HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CALDAT) )) ;
}

//*****************************************************************************
//
//! Returns the calibrated offset of the output buffer.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function is used to manually set the calibration offset value. The
//! calibration is automatically unlocked and relocked to be able to allow for
//! the offset value to be set.
//!
//! Modified bits are 
//!     \b DAC12PW of \b DAC12_A_xCTL0 register 
//!     \b DAC12PW and \b DAC12LOCK of \b OFS_DAC12_A_0CALCTL register
//!     \b DAC12_A_0CALDAT register
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_setCalibrationOffset (uint32_t baseAddress,
    uint8_t submoduleSelect,
    int calibrationOffsetValue)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    //Unlock Calibration
    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CALCTL) = DAC12PW;

    //Set Calibration Offset
    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CALDAT) =
        calibrationOffsetValue;

    //Lock Calibration
    HWREG16(baseAddress + submoduleSelect +
        OFS_DAC12_0CALCTL) = DAC12PW + DAC12LOCK;
}

//*****************************************************************************
//
//! Enables triggers to start conversions.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function is used to allow triggers to start a conversion. Note that
//! this function does not need to be used if DAC12_A_TRIGGER_AUTO was set for the
//! conversionTriggerSelect parameter during initialization. If DAC grouping is
//! enabled, this has to be called for both DAC's.
//!
//! Modified bits are \b DAC12ENC of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_enableConversions (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) |= DAC12ENC;
}

//*****************************************************************************
//
//! Sets the given data into the buffer to be converted.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//! \param data is the data to be set into the DAC12_A data buffer to be
//!       converted.
//!        Modified bits are \b DAC12_A_Data of \b DAC12_A_xDAT register.
//!
//! This function is used to set the given data into the data buffer of the
//! DAC12_A module. The data given should be in the format set (12-bit Unsigned,
//! Right-justified by default). Note if DAC12_A_TRIGGER_AUTO was set for the
//! conversionTriggerSelect during initialization then using this function will
//! set the data and automatically trigger a conversion. If any other trigger
//! was set during initialization, then the DAC12_A_enableConversions() function
//! needs to be called before a conversion can be started. If grouping DAC's and
//! DAC12_A_TRIGGER_ENC was set during initialization, then both data buffers must
//! be set before a conversion will be started.
//!
//! Modified registers are \b DAC12_A_0DAT.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_setData (uint32_t baseAddress,
    uint8_t submoduleSelect,
    uint16_t data)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0DAT) = data;
}

//*****************************************************************************
//
//! Disables triggers to start conversions.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! This function is used to disallow triggers to start a conversion. Note that
//! this function does not have any affect if DAC12_A_TRIGGER_AUTO was set for the
//! conversionTriggerSelect parameter during initialization.
//! 
//! Modified bits are \b DAC12ENC of \b DAC12_A_xCTL0 register.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_disableConversions (uint32_t baseAddress,
    uint8_t submoduleSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);

    HWREG16(baseAddress + submoduleSelect + OFS_DAC12_0CTL0) &= ~(DAC12ENC);
}

//*****************************************************************************
//
//! Sets the resolution to be used by the DAC12_A module.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//! \param resolutionSelect is the resolution to use for conversions.
//!        Valid values are
//!        \b DAC12_A_RESOLUTION_8BIT
//!        \b DAC12_A_RESOLUTION_12BIT [Default]
//!        Modified bits are \b DAC12RES of \b DAC12_A_xCTL0 register.
//!
//! This function sets the resolution of the data to converted.
//!
//! Modified bits are \b DAC12ENC of \b DAC12_A_xCTL0 register.
//!                   \b DAC12RES of \b DAC12_A_xCTL0 register.
//! \return NONE
//
//*****************************************************************************
void DAC12_A_setResolution (uint32_t baseAddress,
    uint8_t submoduleSelect,
    uint16_t resolutionSelect)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);
    assert(resolutionSelect <= DAC12_A_RESOLUTION_12BIT);

    //Store the ENC bit status
    uint16_t conversionsEnabledStatus =
        ( HWREG16(baseAddress + OFS_DAC12_0CTL0) & (DAC12ENC) );

    baseAddress += submoduleSelect;           //Add 0x10 to base address IF
                                              //DAC12_A_1 is selected.

    if (DAC12_A_RESOLUTION_8BIT == resolutionSelect){
        HWREG16(baseAddress + OFS_DAC12_0CTL0) |= DAC12RES;
    } else if (DAC12_A_RESOLUTION_12BIT == resolutionSelect){
        HWREG16(baseAddress + OFS_DAC12_0CTL0) &= ~(DAC12RES);
    }

    //Restore the ENC bit status
    HWREG16(baseAddress + OFS_DAC12_0CTL0) |= conversionsEnabledStatus;
}

//*****************************************************************************
//
//! Sets the input data format for the DAC12_A module.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//! \param inputJustification is the justification of the data to be converted.
//!        Valid values are
//!        \b DAC12_A_JUSTIFICATION_RIGHT [Default]
//!        \b DAC12_A_JUSTIFICATION_LEFT
//!        Modified bits are \b DAC12DFJ of \b DAC12_A_xCTL1 register.
//! \param inputSign is the sign of the data to be converted.
//!        Valid values are
//!        \b DAC12_A_UNSIGNED_BINARY [Default]
//!        \b DAC12_A_SIGNED_2SCOMPLEMENT
//!        Modified bits are \b DAC12DF of \b DAC12_A_xCTL0 register.
//!
//! This function sets the input format for the binary data to be converted.
//!
//! \return NONE
//
//*****************************************************************************
void DAC12_A_setInputDataFormat (uint32_t baseAddress,
    uint8_t submoduleSelect,
    uint8_t inputJustification,
    uint8_t inputSign)
{
    assert(submoduleSelect <= DAC12_A_SUBMODULE_1);
    assert(inputJustification <= DAC12_A_JUSTIFICATION_LEFT);
    assert(inputSign <= DAC12_A_SIGNED_2SCOMPLEMENT);

    //Store the ENC bit status
    uint16_t conversionsEnabledStatus =
        ( HWREG16(baseAddress + OFS_DAC12_0CTL0) & (DAC12ENC) );

    baseAddress += submoduleSelect;           //Add 0x10 to base address IF
                                              //DAC12_A_1 is selected.

    if (DAC12_A_JUSTIFICATION_LEFT == inputJustification){
        HWREG16(baseAddress + OFS_DAC12_0CTL1) |= DAC12DFJ;
    } else if (DAC12_A_JUSTIFICATION_RIGHT == inputJustification){
        HWREG16(baseAddress + OFS_DAC12_0CTL1) &= ~(DAC12DFJ);
    }

    if (DAC12_A_SIGNED_2SCOMPLEMENT == inputSign){
        HWREG16(baseAddress + OFS_DAC12_0CTL0) |= DAC12DF;
    } else if (DAC12_A_UNSIGNED_BINARY == inputSign){
        HWREG16(baseAddress + OFS_DAC12_0CTL0) &= ~(DAC12DF);
    }

    //Restore the ENC bit status
    HWREG16(baseAddress + OFS_DAC12_0CTL0) |= conversionsEnabledStatus;
}

//*****************************************************************************
//
//! Returns the address of the specified DAC12_A data buffer for the DMA module.
//!
//! \param baseAddress is the base address of the DAC12_A module.
//! \param submoduleSelect decides which DAC12_A sub-module to configure.
//!        Valid values are
//!        \b DAC12_A_SUBMODULE_0
//!        \b DAC12_A_SUBMODULE_1
//!
//! Returns the address of the specified  memory buffer. This can be used in
//! conjunction with the DMA to obtain the data directly from memory.
//!
//! \return NONE
//
//*****************************************************************************
uint32_t DAC12_A_getDataBufferMemoryAddressForDMA (unsigned baseAddress,
    uint8_t submoduleSelect)
{
  assert(submoduleSelect <= DAC12_A_SUBMODULE_1);
  return ( baseAddress + submoduleSelect + OFS_DAC12_0DAT );
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
