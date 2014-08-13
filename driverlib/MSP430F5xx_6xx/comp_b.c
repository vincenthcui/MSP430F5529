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
//comp_b.c - Driver for the COMPARATOR_B Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "comp_b.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif
#include "assert.h"

//*****************************************************************************
//
//! Initializes the Comparator Module.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param positiveTerminalInput selects the input to the positive terminal.
//!        Valid values are
//!        \b COMP_B_INPUT0 [Default]
//!        \b COMP_B_INPUT1
//!        \b COMP_B_INPUT2
//!        \b COMP_B_INPUT3
//!        \b COMP_B_INPUT4
//!        \b COMP_B_INPUT5
//!        \b COMP_B_INPUT6
//!        \b COMP_B_INPUT7
//!        \b COMP_B_INPUT8
//!        \b COMP_B_INPUT9
//!        \b COMP_B_INPUT10
//!        \b COMP_B_INPUT11
//!        \b COMP_B_INPUT12
//!        \b COMP_B_INPUT13
//!        \b COMP_B_INPUT14
//!        \b COMP_B_INPUT15
//!        \b COMP_B_VREF
//!        Modified bits are \b CBIPSEL and \b CBIPEN of \b CBCTL0 register,
//!        \b CBRSEL of \b CBCTL2 register, and CBPDx of \b CBCTL3 register.
//! \param negativeTerminalInput selects the input to the negative terminal.
//!        Valid values are
//!        \b COMP_B_INPUT0 [Default]
//!        \b COMP_B_INPUT1
//!        \b COMP_B_INPUT2
//!        \b COMP_B_INPUT3
//!        \b COMP_B_INPUT4
//!        \b COMP_B_INPUT5
//!        \b COMP_B_INPUT6
//!        \b COMP_B_INPUT7
//!        \b COMP_B_INPUT8
//!        \b COMP_B_INPUT9
//!        \b COMP_B_INPUT10
//!        \b COMP_B_INPUT11
//!        \b COMP_B_INPUT12
//!        \b COMP_B_INPUT13
//!        \b COMP_B_INPUT14
//!        \b COMP_B_INPUT15
//!        \b COMP_B_VREF
//!        Modified bits are \b CBIMSEL and \b CBIMEN of \b CBCTL0 register,
//!        \b CBRSEL of \b CBCTL2 register, and CBPDx of \b CBCTL3 register.
//! \param powerModeSelect selects the power mode at which the comparator module
//!       will operate at.
//!        Valid values are
//!        \b COMP_B_POWERMODE_HIGHSPEED [Default]
//!        \b COMP_B_POWERMODE_NORMALMODE
//!        \b COMP_B_POWERMODE_ULTRALOWPOWER
//!        Modified bits are \b CBWRMD of \b CBCTL1 register.
//! \param outputFilterEnableAndDelayLevel controls the output filter delay
//!       state, which is either off or enabled with a specified delay level.
//!        Valid values are
//!        \b COMP_B_FILTEROUTPUT_OFF [Default]
//!        \b COMP_B_FILTEROUTPUT_DLYLVL1
//!        \b COMP_B_FILTEROUTPUT_DLYLVL2
//!        \b COMP_B_FILTEROUTPUT_DLYLVL3
//!        \b COMP_B_FILTEROUTPUT_DLYLVL4
//!        This parameter is device specific and delay levels should be found in
//!        the device's datasheet.
//!        Modified bits are \b CBF and \b CBFDLY of \b CBCTL1 register.
//! \param invertedOutput controls if the output will be inverted or not
//!        Valid values are
//!        \b COMP_B_NORMALOUTPUTPOLARITY - indicates the output should be normal.
//!             [Default]
//!        \b COMP_B_INVERTEDOUTPUTPOLARITY -  the output should be inverted.
//!        Modified bits are \b CBOUTPOL of \b CBCTL1 register.
//!
//! Upon successful initialization of the Comparator module, this function will
//! have reset all neccessary register bits and set the given options in the
//! registers. To actually use the comparator module, the COMP_B_enable()
//! function must be explicitly called before use.
//! If a Reference Voltage is set to a terminal, the Voltage should be set
//! using the setReferenceVoltage() function.
//!
//! \return STATUS_SUCCESS or STATUS_FAILURE of the initialization process.
//
//*****************************************************************************
unsigned short COMP_B_init (uint32_t baseAddress,
    uint8_t positiveTerminalInput,
    uint8_t negativeTerminalInput,
    uint16_t powerModeSelect,
    uint8_t outputFilterEnableAndDelayLevel,
    unsigned short invertedOutputPolarity)
{
    assert(positiveTerminalInput <= COMP_B_VREF);
    assert(negativeTerminalInput <= COMP_B_VREF);
    assert(positiveTerminalInput != negativeTerminalInput);
    assert(powerModeSelect <= COMP_B_POWERMODE_ULTRALOWPOWER);
    assert(outputFilterEnableAndDelayLevel <= COMP_B_FILTEROUTPUT_DLYLVL4);

    uint8_t retVal = STATUS_SUCCESS;

    //Reset COMPB Control 1 & Interrupt Registers for initialization (OFS_CBCTL3
    //is not reset because it controls the input buffers of the analog signals
    //and may cause parasitic effects if an analog signal is still attached and
    //the buffer is re-enabled
    HWREG16(baseAddress + OFS_CBCTL0) &= 0x0000;
    HWREG16(baseAddress + OFS_CBINT)  &= 0x0000;

    //Set the Positive Terminal
    if (COMP_B_VREF != positiveTerminalInput){
        //Enable Positive Terminal Input Mux and Set it to the appropriate input
        HWREG16(baseAddress + OFS_CBCTL0) |= CBIPEN + positiveTerminalInput;

        //Disable the input buffer
        HWREG16(baseAddress + OFS_CBCTL3) |= (1 << positiveTerminalInput);
    } else {
        //Reset and Set COMPB Control 2 Register
        HWREG16(baseAddress + OFS_CBCTL2) = ~(CBRSEL); //Set Vref to go to (+)terminal
    }

    //Set the Negative Terminal
    if (COMP_B_VREF != negativeTerminalInput){
        //Enable Negative Terminal Input Mux and Set it to the appropriate input
        HWREG16(baseAddress + OFS_CBCTL0) |= CBIMEN + (negativeTerminalInput << 8);

        //Disable the input buffer
        HWREG16(baseAddress + OFS_CBCTL3) |= (1 << negativeTerminalInput);
    } else {
        //Reset and Set COMPB Control 2 Register
        HWREG16(baseAddress + OFS_CBCTL2) = CBRSEL; //Set Vref to go to (-) terminal
    }

    //Reset and Set COMPB Control 1 Register
    HWREG16(baseAddress + OFS_CBCTL1) =
        powerModeSelect //Set the power mode
        + outputFilterEnableAndDelayLevel //Set the filter enable bit and delay
        + invertedOutputPolarity; //Set the polarity of the output

    return ( retVal) ;
}

//*****************************************************************************
//
//! Generates a Reference Voltage to the terminal selected during initialization.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param supplyVoltageBase decides the source and max amount of Voltage that
//!       can be used as a reference.
//!        Valid values are
//!        \b COMP_B_VREFBASE_VCC
//!        \b COMP_B_VREFBASE1_5V
//!        \b COMP_B_VREFBASE2_0V
//!        \b COMP_B_VREFBASE2_5V
//!        Modified bits are \b CBREFL of \b CBCTL2 register.
//! \param upperLimitSupplyVoltageFractionOf32 is the numerator of the equation
//!       to generate the reference voltage for the upper limit reference voltage.
//!        Modified bits are \b CBREF1 of \b CBCTL2 register.
//! \param lowerLimitSupplyVoltageFractionOf32 is the numerator of the equation
//!       to generate the reference voltage for the lower limit reference voltage.
//!        Modified bits are \b CBREF0 of \b CBCTL2 register.
//! \param refrenceAccuracy is the refrence accuracy setting of the comparator. Clocked
//!	      is for low power/low accuracy.
//!			Valid values are
//!			\b COMPD_ACCURACY_STATIC
//!			\b COMPD_ACCURACY_CLOCKED
//!		   Modified bits are \b CDREFACC of \b CDCTL2 register.
//!
//! Use this function to generate a voltage to serve as a reference to the
//! terminal selected at initialization. The voltage is determined by the
//! equation: Vbase * (Numerator / 32). If the upper and lower limit voltage
//! numerators are equal, then a static reference is defined, whereas they are
//! different then a hysteresis effect is generated.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_setReferenceVoltage (uint32_t baseAddress,
    uint16_t supplyVoltageReferenceBase,
    uint16_t lowerLimitSupplyVoltageFractionOf32,
    uint16_t upperLimitSupplyVoltageFractionOf32,
    uint16_t refrenceAccuracy)
{
    assert(supplyVoltageReferenceBase <= COMP_B_VREFBASE2_5V);
    assert(upperLimitSupplyVoltageFractionOf32 <= 32);
    assert(lowerLimitSupplyVoltageFractionOf32 <= 32);
    assert(upperLimitSupplyVoltageFractionOf32
        >= lowerLimitSupplyVoltageFractionOf32);

    HWREG16(baseAddress + OFS_CBCTL1) &= ~(CBMRVS); //Set to VREF0

    //Reset COMPB Control 2 Bits (Except for CBRSEL which is set in Comp_Init() )
    HWREG16(baseAddress + OFS_CBCTL2) &= CBRSEL;

    //Set Voltage Source (Vcc | Vref, resistor ladder or not)
    if (COMP_B_VREFBASE_VCC == supplyVoltageReferenceBase){
        HWREG16(baseAddress + OFS_CBCTL2) |= CBRS_1; //Vcc with resistor ladder
    } else if (lowerLimitSupplyVoltageFractionOf32 == 32){
        //If the lower limit is 32, then the upper limit has to be 32 due to the
        //assertion that upper must be >= to the lower limit. If the numerator is
        //equal to 32, then the equation would be 32/32 == 1, therefore no resistor
        //ladder is needed
        HWREG16(baseAddress + OFS_CBCTL2) |= CBRS_3; //Vref, no resistor ladder
    } else {
        HWREG16(baseAddress + OFS_CBCTL2) |= CBRS_2; //Vref with resistor ladder
    }

    //Set COMPD Control 2 Register
    HWREG16(baseAddress + OFS_CBCTL2) |=
        supplyVoltageReferenceBase //Set Supply Voltage Base
        + ((upperLimitSupplyVoltageFractionOf32 - 1) << 8) //Set Supply Voltage Num.
        + (lowerLimitSupplyVoltageFractionOf32 - 1);

    HWREG16(baseAddress + OFS_CBCTL2) &= ~(CBREFACC);
    HWREG16(baseAddress + OFS_CBCTL2) |= refrenceAccuracy;
}

//*****************************************************************************
//
//! Enables selected Comparator interrupt sources.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param mask is the bit mask of the interrupt sources to be enabled.
//!        Mask vlaue is the logical OR of any of the following
//!        \b CBIE - Output interrupt enable
//!        \b CBIIE - Output interrupt enable inverted polarity
//!
//! Enables the indicated Comparator interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor. <b>Does not clear interrupt flags.</b>
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_enableInterrupt (uint32_t baseAddress,
    uint16_t interruptMask)
{
    //Set the Interrupt enable bit
    HWREG16(baseAddress + OFS_CBINT) |= interruptMask;
}

//*****************************************************************************
//
//! Disables selected Comparator interrupt sources.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param mask is the bit mask of the interrupt sources to be disabled.
//!        Mask vlaue is the logical OR of any of the following
//!        \b CBIE - Output interrupt enable
//!        \b CBIIE - Output interrupt enable inverted polarity
//!
//! Disables the indicated Comparator interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_disableInterrupt (uint32_t baseAddress,
    uint16_t interruptMask)
{
    HWREG16(baseAddress + OFS_CBINT) &= ~(interruptMask);
}

//*****************************************************************************
//
//! Clears Comparator interrupt flags.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param mask is a bit mask of the interrupt sources to be cleared.
//!        Mask vlaue is the logical OR of any of the following
//!        \b CBIFG - Output interrupt flag
//!        \b CBIIFG - Output interrupt flag inverted polarity
//!
//! The Comparator interrupt source is cleared, so that it no longer asserts.
//! The highest interrupt flag is automatically cleared when an interrupt vector
//! generator is used.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_clearInterrupt (uint32_t baseAddress,
    uint16_t interruptFlagMask)
{
    HWREG16(baseAddress + OFS_CBINT) &= ~(interruptFlagMask);
}

//*****************************************************************************
//
//! Gets the current Comparator interrupt status.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param mask is the masked interrupt flag status to be returned.
//!        Mask vlaue is the logical OR of any of the following
//!        \b CBIFG - Output interrupt flag
//!        \b CBIIFG - Output interrupt flag inverted polarity
//!
//! This returns the interrupt status for the Comparator module based on which
//! flag is passed.
//!
//! \return The current interrupt flag status for the corresponding mask.
//
//*****************************************************************************
uint8_t COMP_B_getInterruptStatus (uint32_t baseAddress,
    uint16_t interruptFlagMask)
{
    return ( HWREG16(baseAddress + OFS_CBINT) & interruptFlagMask );
}

//*****************************************************************************
//
//! Explicitly sets the edge direction that would trigger an interrupt.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param edgeDirection determines which direction the edge would have to go to
//!       generate an interrupt based on the non-inverted interrupt flag.
//!        Valid values are
//!        \b COMP_B_FALLINGEDGE - sets the bit to generate an interrupt when the
//!             output of the comparator falls from HIGH to LOW if the normal
//!             interrupt bit is set(and LOW to HIGH if the inverted interrupt
//!             enable bit is set). [Default]
//!        \b COMP_B_RISINGEDGE - sets the bit to generate an interrupt when the
//!             output of the comparator rises from LOW to HIGH if the normal
//!             interrupt bit is set(and HIGH to LOW if the inverted interrupt
//!             enable bit is set).
//!        Modified bits are \b CBIES of \b CBCTL1 register.
//!
//! This function will set which direction the output will have to go, whether
//! rising or falling, to generate an interrupt based on a non-inverted
//! interrupt.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_interruptSetEdgeDirection (uint32_t baseAddress,
    unsigned short edgeDirection)
{
    assert(edgeDirection <= COMP_B_RISINGEDGE);

    //Set the edge direction that will trigger an interrupt
    if (COMP_B_RISINGEDGE == edgeDirection){
        HWREG16(baseAddress + OFS_CBCTL1) |= CBIES;
    } else if (COMP_B_FALLINGEDGE == edgeDirection){
        HWREG16(baseAddress + OFS_CBCTL1) &= ~(CBIES);
    }
}

//*****************************************************************************
//
//! Toggles the edge direction that would trigger an interrupt.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! This function will toggle which direction the output will have to go,
//! whether rising or falling, to generate an interrupt based on a non-inverted
//! interrupt. If the direction was rising, it is now falling, if it was
//! falling, it is now rising.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_interruptToggleEdgeDirection (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_CBCTL1) ^= CBIES;
}

//*****************************************************************************
//
//! Turns on the Comparator module.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! This function sets the bit that enables the operation of the
//! Comparator module.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_enable (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_CBCTL1) |= CBON;
}

//*****************************************************************************
//
//! Turns off the Comparator module.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! This function clears the CBON bit disabling the operation of the Comparator
//! module, saving from excess power consumption.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_disable (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_CBCTL1) &= ~(CBON);
}

//*****************************************************************************
//
//! Shorts the two input pins chosen during initialization.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! This function sets the bit that shorts the devices attached to the input
//! pins chosen from the initialization of the comparator.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_shortInputs (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_CBCTL1) |= CBSHORT;
}

//*****************************************************************************
//
//! Disables the short of the two input pins chosen during initialization.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! This function clears the bit that shorts the devices attached to the input
//! pins chosen from the initialization of the comparator.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_unshortInputs (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_CBCTL1) &= ~(CBSHORT);
}

//*****************************************************************************
//
//! Disables the input buffer of the selected input port to effectively allow
//! for analog signals.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param inputPort is the port in which the input buffer will be disabled.
//!        Valid values are
//!        \b COMP_B_INPUT0 [Default]
//!        \b COMP_B_INPUT1
//!        \b COMP_B_INPUT2
//!        \b COMP_B_INPUT3
//!        \b COMP_B_INPUT4
//!        \b COMP_B_INPUT5
//!        \b COMP_B_INPUT6
//!        \b COMP_B_INPUT7
//!        \b COMP_B_INPUT8
//!        \b COMP_B_INPUT9
//!        \b COMP_B_INPUT10
//!        \b COMP_B_INPUT11
//!        \b COMP_B_INPUT12
//!        \b COMP_B_INPUT13
//!        \b COMP_B_INPUT14
//!        \b COMP_B_INPUT15
//!        \b COMP_B_VREF
//!        Modified bits are \b CBPDx of \b CBCTL3 register.
//!
//! This function sets the bit to disable the buffer for the specified input
//! port to allow for analog signals from any of the comparator input pins. This
//! bit is automatically set when the input is initialized to be used with the
//! comparator module. This function should be used whenever an analog input is
//! connected to one of these pins to prevent parasitic voltage from causing
//! unexpected results.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_disableInputBuffer (uint32_t baseAddress,
    uint8_t inputPort)
{
    HWREG16(baseAddress + OFS_CBCTL3) |= (1 << inputPort);
}

//*****************************************************************************
//
//! Enables the input buffer of the selected input port to allow for digital
//! signals.
//!
//! \param baseAddress is the base address of the Comparator module.
//! \param inputPort is the port in which the input buffer will be enabled.
//!        Valid values are
//!        \b COMP_B_INPUT0 [Default]
//!        \b COMP_B_INPUT1
//!        \b COMP_B_INPUT2
//!        \b COMP_B_INPUT3
//!        \b COMP_B_INPUT4
//!        \b COMP_B_INPUT5
//!        \b COMP_B_INPUT6
//!        \b COMP_B_INPUT7
//!        \b COMP_B_INPUT8
//!        \b COMP_B_INPUT9
//!        \b COMP_B_INPUT10
//!        \b COMP_B_INPUT11
//!        \b COMP_B_INPUT12
//!        \b COMP_B_INPUT13
//!        \b COMP_B_INPUT14
//!        \b COMP_B_INPUT15
//!        \b COMP_B_VREF
//!        Modified bits are \b CBPDx of \b CBCTL3 register.
//!
//! This function clears the bit to enable the buffer for the specified input
//! port to allow for digital signals from any of the comparator input pins.
//! This should not be reset if there is an analog signal connected to the
//! specified input pin to prevent from unexpected results.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_enableInputBuffer (uint32_t baseAddress, uint8_t inputPort)
{
    HWREG16(baseAddress + OFS_CBCTL3) &= ~(1 << inputPort);
}

//*****************************************************************************
//
//! Toggles the bit that swaps which terminals the inputs go to, while also
//! inverting the output of the comparator.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! This function toggles the bit that controls which input goes to which
//! terminal. After initialization, this bit is set to 0, after toggling it once
//! the inputs are routed to the opposite terminal and the output is inverted.
//!
//! \return NONE
//
//*****************************************************************************
void COMP_B_IOSwap (uint32_t baseAddress)
{
    HWREG16(baseAddress + OFS_CBCTL1) ^= CBEX; //Toggle CBEX bit
}

//*****************************************************************************
//
//! Returns the output value of the Comparator module.
//!
//! \param baseAddress is the base address of the Comparator module.
//!
//! Returns the output value of the Comparator module.
//!
//! \return COMP_B_HIGH or COMP_B_LOW as the output value of the Comparator module.
//
//*****************************************************************************
unsigned short COMP_B_outputValue (uint32_t baseAddress)
{
    if ( HWREG16(baseAddress + OFS_CBCTL1) & CBOUT){
        return ( COMP_B_HIGH) ;
    } else {
        return ( COMP_B_LOW) ;
    }
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
