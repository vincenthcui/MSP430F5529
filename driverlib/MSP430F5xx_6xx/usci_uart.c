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
//usci_uart.c - Driver for the UART Module.
//THIS FILE IS INCLUDED FOR BACKWARD COMPATIBILTY. PLEASE DO NOT USE THIS FILE
//AND INCLUDED APIS FOR NEW APPLICATIONS. PLEASE REFER usci_a_uart.c 
//FOR NEW PROJECTS
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "assert.h"
#include "usci_uart.h"
#include "usci_uartbaudrate.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif

//*****************************************************************************
//
//! DEPRECATED. Please use USCI_UART_initAdvance() to initialize the 
//! USCI_UART_ module
//!
//! Initializes the UART block.
//!
//! \param baseAddress is the base address of the UART module.
//! \param selectClockSource selects Clock source. Valid values are
//!         \b USCI_UART_CLOCKSOURCE_SMCLK
//!         \b USCI_UART_CLOCKSOURCE_ACLK
//! \param clockSourceFrequency is the frequency of the slected clock source
//! \param desiredUartClock is the desired clock rate for UART communication
//! \param parity is the desired parity. Valid values are
//!        \b USCI_UART_NO_PARITY  [Default Value],
//!        \b USCI_UART_ODD_PARITY,
//!        \b USCI_UART_EVEN_PARITY
//! \param msborLsbFirst controls direction of receive and transmit shift
//!     register. Valid values are
//!        \b USCI_UART_MSB_FIRST
//!        \b USCI_UART_LSB_FIRST [Default Value]
//! \param numberofStopBits indicates one/two STOP bits
//!      Valid values are
//!        \b USCI_UART_ONE_STOP_BIT [Default Value]
//!        \b USCI_UART_TWO_STOP_BITS
//! \param uartMode selects the mode of operation
//!      Valid values are
//!        \b USCI_UART_MODE  [Default Value],
//!        \b USCI_UART_IDLE_LINE_MULTI_PROCESSOR_MODE,
//!        \b USCI_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE,
//!        \b USCI_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE
//! \param overSampling indicates low frequency or oversampling baud generation
//!      Valid values are
//!        \b USCI_UART_OVERSAMPLING_BAUDRATE_GENERATION
//!        \b USCI_UART_LOW_FREQUENCY_BAUDRATE_GENERATION
//!
//! Upon successful initialization of the UART block, this function
//! will have initialized the module, but the UART block still remains
//! disabled and must be enabled with USCI_UART_enable()
//!
//! Modified bits are \b UCPEN, \b UCPAR, \b UCMSB, \b UC7BIT, \b UCSPB,
//! \b UCMODEx, \b UCSYNC bits of \b UCAxCTL0 and \b UCSSELx,
//! \b UCSWRST bits of \b UCAxCTL1
//!
//! \return STATUS_SUCCESS or
//!         STATUS_FAIL of the initialization process
//
//*****************************************************************************
unsigned short USCI_UART_init ( uint32_t baseAddress,
    uint8_t selectClockSource,
    uint32_t clockSourceFrequency,
    uint32_t desiredUartBaudRate,
    uint8_t parity,
    uint8_t msborLsbFirst,
    uint8_t numberofStopBits,
    uint8_t uartMode,
    uint8_t overSampling
    )
{
    assert(
        (USCI_UART_MODE == uartMode) ||
        (USCI_UART_IDLE_LINE_MULTI_PROCESSOR_MODE == uartMode) ||
        (USCI_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE == uartMode) ||
        (USCI_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE == uartMode)
        );

    assert(
        (USCI_UART_CLOCKSOURCE_ACLK == selectClockSource) ||
        (USCI_UART_CLOCKSOURCE_SMCLK == selectClockSource)
        );

    assert(
        (USCI_UART_MSB_FIRST == msborLsbFirst) ||
        (USCI_UART_LSB_FIRST == msborLsbFirst)
        );

    assert(
        (USCI_UART_ONE_STOP_BIT == numberofStopBits) ||
        (USCI_UART_TWO_STOP_BITS == numberofStopBits)
        );

    assert(
        (USCI_UART_NO_PARITY == parity) ||
        (USCI_UART_ODD_PARITY == parity) ||
        (USCI_UART_EVEN_PARITY == parity)
        );

	if(USCI_UART_LOW_FREQUENCY_BAUDRATE_GENERATION == overSampling)
	{
		assert ( clockSourceFrequency >= (desiredUartBaudRate * 3));
	
		if( clockSourceFrequency < (3 * desiredUartBaudRate))
			return STATUS_FAIL;
	}
	else
	{
		assert ( clockSourceFrequency >= (desiredUartBaudRate * 6));
	
		if( clockSourceFrequency < (6 * desiredUartBaudRate))
			return STATUS_FAIL;
	}

    uint8_t retVal = STATUS_SUCCESS;
    uint8_t UCAxBR0_value = 0x00;
    uint8_t UCAxBR1_value = 0x00;
    uint16_t UCAxMCTL_value = 0x00;

    //Disable the USCI Module
    HWREG8(baseAddress + OFS_UCAxCTL1) |= UCSWRST;

    //Clock source select
    HWREG8(baseAddress + OFS_UCAxCTL1) &= ~UCSSEL_3;
    HWREG8(baseAddress + OFS_UCAxCTL1) |= selectClockSource;

    //MSB, LSB select
    HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCMSB;
    HWREG8(baseAddress + OFS_UCAxCTL0) |= msborLsbFirst;


    //UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCSPB;
    HWREG8(baseAddress + OFS_UCAxCTL0) |= numberofStopBits;


    //Parity
    switch (parity){
        case USCI_UART_NO_PARITY:
            //No Parity
            HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCPEN;
            break;
        case USCI_UART_ODD_PARITY:
            //Odd Parity
            HWREG8(baseAddress + OFS_UCAxCTL0) |= UCPEN;
            HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCPAR;
            break;
        case USCI_UART_EVEN_PARITY:
            //Even Parity
            HWREG8(baseAddress + OFS_UCAxCTL0) |= UCPEN;
            HWREG8(baseAddress + OFS_UCAxCTL0) |= UCPAR;
            break;
    }

    //Calculate Baud rate divider values for Modulation control registers
    if ( STATUS_FAIL == USCI_UARTBAUDRATE_calculateBaudDividers(clockSourceFrequency,
             desiredUartBaudRate,
             &UCAxBR0_value,
             &UCAxBR1_value,
             &UCAxMCTL_value,
             overSampling
             )){
        return ( STATUS_FAIL) ;
    }

    //Modulation Control Registers
    HWREG8(baseAddress + OFS_UCAxBR0 ) = UCAxBR0_value;
    HWREG8(baseAddress + OFS_UCAxBR1) = UCAxBR1_value;
    HWREG8(baseAddress + OFS_UCAxMCTL) = UCAxMCTL_value;

    //Asynchronous mode & 8 bit character select & clear mode
    HWREG8(baseAddress + OFS_UCAxCTL0) &=  ~(UCSYNC +
                                             UC7BIT +
                                             UCMODE_3
                                             );

    //Configure  UART mode.
    HWREG8(baseAddress + OFS_UCAxCTL0) |= uartMode ;

    //Reset UCRXIE, UCBRKIE, UCDORM, UCTXADDR, UCTXBRK
    HWREG8(baseAddress + OFS_UCAxCTL1)  &= ~(UCRXEIE + UCBRKIE + UCDORM +
                                             UCTXADDR + UCTXBRK
                                             );

    return ( retVal) ;
}

//*****************************************************************************
//
//! Advanced initialization routine for the UART block. The values to be written
//! into the UCAxBRW and UCAxMCTLW registers should be pre-computed and passed
//! into the initialization function
//!
//! \param baseAddress is the base address of the UART module.
//! \param selectClockSource selects Clock source. Valid values are
//!         \b USCI_UART_CLOCKSOURCE_SMCLK
//!         \b USCI_UART_CLOCKSOURCE_ACLK
//! \param clockPrescalar is the value to be written into UCBRx bits
//! \param firstModReg  is First modulation stage register setting. This value
//! 	is a pre-calculated value which can be obtained from the Device User’s
//!		Guide.This value is written into UCBRFx bits of UCAxMCTLW.
//! \param secondModReg is Second modulation stage register setting.
//! 	This value is a pre-calculated value which can be obtained from the Device
//! 	User’s Guide. This value is written into UCBRSx bits of UCAxMCTLW.
//! \param parity is the desired parity. Valid values are
//!        \b USCI_UART_NO_PARITY  [Default Value],
//!        \b USCI_UART_ODD_PARITY,
//!        \b USCI_UART_EVEN_PARITY
//! \param msborLsbFirst controls direction of receive and transmit shift
//!     register. Valid values are
//!        \b USCI_UART_MSB_FIRST
//!        \b USCI_UART_LSB_FIRST [Default Value]
//! \param numberofStopBits indicates one/two STOP bits
//!      Valid values are
//!        \b USCI_UART_ONE_STOP_BIT [Default Value]
//!        \b USCI_UART_TWO_STOP_BITS
//! \param uartMode selects the mode of operation
//!      Valid values are
//!        \b USCI_UART_MODE  [Default Value],
//!        \b USCI_UART_IDLE_LINE_MULTI_PROCESSOR_MODE,
//!        \b USCI_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE,
//!        \b USCI_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE
//! \param overSampling indicates low frequency or oversampling baud generation
//!      Valid values are
//!        \b USCI_UART_OVERSAMPLING_BAUDRATE_GENERATION
//!        \b USCI_UART_LOW_FREQUENCY_BAUDRATE_GENERATION
//!
//! Upon successful initialization of the UART block, this function
//! will have initialized the module, but the UART block still remains
//! disabled and must be enabled with USCI_UART_enable()
//!
//! Modified bits are \b UCPEN, \b UCPAR, \b UCMSB, \b UC7BIT, \b UCSPB,
//! \b UCMODEx, \b UCSYNC bits of \b UCAxCTL0 and \b UCSSELx,
//! \b UCSWRST bits of \b UCAxCTL1
//!
//! \return STATUS_SUCCESS or
//!         STATUS_FAIL of the initialization process
//
//*****************************************************************************
unsigned short USCI_UART_initAdvance ( uint32_t baseAddress,
    uint8_t selectClockSource,
    uint16_t clockPrescalar,
    uint8_t firstModReg,
    uint8_t secondModReg,
    uint8_t parity,
    uint8_t msborLsbFirst,
    uint8_t numberofStopBits,
    uint8_t uartMode,
    uint8_t overSampling
    )
{
    assert(
        (USCI_UART_MODE == uartMode) ||
        (USCI_UART_IDLE_LINE_MULTI_PROCESSOR_MODE == uartMode) ||
        (USCI_UART_ADDRESS_BIT_MULTI_PROCESSOR_MODE == uartMode) ||
        (USCI_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE == uartMode)
        );

    assert(
        (USCI_UART_CLOCKSOURCE_ACLK == selectClockSource) ||
        (USCI_UART_CLOCKSOURCE_SMCLK == selectClockSource)
        );

    assert(
        (USCI_UART_MSB_FIRST == msborLsbFirst) ||
        (USCI_UART_LSB_FIRST == msborLsbFirst)
        );

    assert(
        (USCI_UART_ONE_STOP_BIT == numberofStopBits) ||
        (USCI_UART_TWO_STOP_BITS == numberofStopBits)
        );

    assert(
        (USCI_UART_NO_PARITY == parity) ||
        (USCI_UART_ODD_PARITY == parity) ||
        (USCI_UART_EVEN_PARITY == parity)
        );


    uint8_t retVal = STATUS_SUCCESS;

    //Disable the USCI Module
    HWREG8(baseAddress + OFS_UCAxCTL1) |= UCSWRST;

    //Clock source select
    HWREG8(baseAddress + OFS_UCAxCTL1) &= ~UCSSEL_3;
    HWREG8(baseAddress + OFS_UCAxCTL1) |= selectClockSource;

    //MSB, LSB select
    HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCMSB;
    HWREG8(baseAddress + OFS_UCAxCTL0) |= msborLsbFirst;


    //UCSPB = 0(1 stop bit) OR 1(2 stop bits)
    HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCSPB;
    HWREG8(baseAddress + OFS_UCAxCTL0) |= numberofStopBits;


    //Parity
    switch (parity){
        case USCI_UART_NO_PARITY:
            //No Parity
            HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCPEN;
            break;
        case USCI_UART_ODD_PARITY:
            //Odd Parity
            HWREG8(baseAddress + OFS_UCAxCTL0) |= UCPEN;
            HWREG8(baseAddress + OFS_UCAxCTL0) &= ~UCPAR;
            break;
        case USCI_UART_EVEN_PARITY:
            //Even Parity
            HWREG8(baseAddress + OFS_UCAxCTL0) |= UCPEN;
            HWREG8(baseAddress + OFS_UCAxCTL0) |= UCPAR;
            break;
    }

    //Modulation Control Registers
    HWREG8(baseAddress + OFS_UCAxBRW ) = clockPrescalar;
    HWREG8(baseAddress + OFS_UCAxMCTL) = ((firstModReg<<4) + (secondModReg <<1) +
    									  overSampling );

    //Asynchronous mode & 8 bit character select & clear mode
    HWREG8(baseAddress + OFS_UCAxCTL0) &=  ~(UCSYNC +
                                             UC7BIT +
                                             UCMODE_3
                                             );

    //Configure  UART mode.
    HWREG8(baseAddress + OFS_UCAxCTL0) |= uartMode ;

    //Reset UCRXIE, UCBRKIE, UCDORM, UCTXADDR, UCTXBRK
    HWREG8(baseAddress + OFS_UCAxCTL1)  &= ~(UCRXEIE + UCBRKIE + UCDORM +
                                             UCTXADDR + UCTXBRK
                                             );

    return ( retVal) ;
}

//*****************************************************************************
//
//! Transmits a byte from the UART Module.
//!
//! \param baseAddress is the base address of the UART module.
//! \param transmitData data to be transmitted from the UART module
//!
//! This function will place the supplied data into UART trasmit data register
//! to start transmission
//!
//! Modified register is \b UCAxTXBUF
//! \return None.
//
//*****************************************************************************
void USCI_UART_transmitData ( uint32_t baseAddress,
    uint8_t transmitData
    )
{
    HWREG8(baseAddress + OFS_UCAxTXBUF) = transmitData;
}

//*****************************************************************************
//
//! Receives a byte that has been sent to the UART Module.
//!
//! \param baseAddress is the base address of the UART module.
//!
//! This function reads a byte of data from the UART receive data Register.
//!
//! Modified register is \b UCAxRXBUF
//!
//! \return Returns the byte received from by the UART module, cast as an
//! uint8_t.
//
//*****************************************************************************
uint8_t USCI_UART_receiveData (uint32_t baseAddress)
{
    return ( HWREG8(baseAddress + OFS_UCAxRXBUF)) ;
}

//*****************************************************************************
//
//! Enables individual UART interrupt sources.
//!
//! \param baseAddress is the base address of the UART module.
//! \param mask is the bit mask of the interrupt sources to be enabled.
//!
//! Enables the indicated UART interrupt sources.  The interrupt flag is first
//! and then the corresponfing interrupt is enabled. Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor. <b>Does not clear interrupt flags.</b>
//!
//! The mask parameter is the logical OR of any of the following:
//! - \b USCI_UART_RECEIVE_INTERRUPT -Receive interrupt
//! - \b USCI_UART_TRANSMIT_INTERRUPT - Transmit interrupt
//! - \b USCI_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT - Receive erroneous-character
//!                             interrupt enable
//! - \b USCI_UART_BREAKCHAR_INTERRUPT - Receive break character interrupt enable
//!
//! Modified register is \b UCAxIFG, \b UCAxIE and \b UCAxCTL1
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_enableInterrupt (uint32_t baseAddress,
    uint8_t mask
    )
{
    assert( 0x00 != mask && (USCI_UART_RECEIVE_INTERRUPT +
			USCI_UART_TRANSMIT_INTERRUPT +
			USCI_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT +
			USCI_UART_BREAKCHAR_INTERRUPT
			) );
			
    switch (mask){
        case USCI_UART_RECEIVE_INTERRUPT:
        case USCI_UART_TRANSMIT_INTERRUPT:
            //Enable Interrupt
            HWREG8(baseAddress + OFS_UCAxIE) |= mask;
            break;
        case USCI_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT:
        case USCI_UART_BREAKCHAR_INTERRUPT:
            //Enable Interrupt
            HWREG8(baseAddress + OFS_UCAxCTL1) |= mask;
            break;
    }
}

//*****************************************************************************
//
//! Disables individual UART interrupt sources.
//!
//! \param baseAddress is the base address of the UART module.
//! \param mask is the bit mask of the interrupt sources to be
//! disabled.
//!
//! Disables the indicated UART interrupt sources.  Only the sources that
//! are enabled can be reflected to the processor interrupt; disabled sources
//! have no effect on the processor.
//!
//! The mask parameter is the logical OR of any of the following:
//! - \b USCI_UART_RECEIVE_INTERRUPT -Receive interrupt
//! - \b USCI_UART_TRANSMIT_INTERRUPT - Transmit interrupt
//! - \b USCI_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT - Receive erroneous-character
//!                             interrupt enable
//! - \b USCI_UART_BREAKCHAR_INTERRUPT - Receive break character interrupt enable
//!
//! Modified register is \b UCAxIFG, \b UCAxIE and \b UCAxCTL1
//! \return None.
//
//*****************************************************************************
void USCI_UART_disableInterrupt (uint32_t baseAddress,
    uint8_t mask
    )
{
   assert( 0x00 != mask && (USCI_UART_RECEIVE_INTERRUPT +
			USCI_UART_TRANSMIT_INTERRUPT +
			USCI_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT +
			USCI_UART_BREAKCHAR_INTERRUPT
			) );

    switch (mask){
        case USCI_UART_RECEIVE_INTERRUPT:
        case USCI_UART_TRANSMIT_INTERRUPT:
            //Disable Interrupt
            HWREG8(baseAddress + OFS_UCAxIE) &= ~mask;
            break;
        case USCI_UART_RECEIVE_ERRONEOUSCHAR_INTERRUPT:
        case USCI_UART_BREAKCHAR_INTERRUPT:
            //Disable Interrupt
            HWREG8(baseAddress + OFS_UCAxCTL1) &= ~mask;
            break;
    }
}

//*****************************************************************************
//
//! Gets the current UART interrupt status.
//!
//! \param baseAddress is the base address of the UART module.
//! \param mask is the masked interrupt flag status to be returned.
//!
//! This returns the interrupt status for the UART  module based on which
//! flag is passed. mask parameter can be either any of the following
//! selection.
//! - \b USCI_UART_RECEIVE_INTERRUPT_FLAG -Receive interrupt flag
//! - \b USCI_UART_TRANSMIT_INTERRUPT_FLAG - Transmit interrupt flag
//!
//! Modified register is \b UCAxIFG.
//!
//! \return The current interrupt status, returned as with the respective bits
//! set if the corresponding interrupt flag is set
//
//*****************************************************************************
uint8_t USCI_UART_getInterruptStatus (uint32_t baseAddress,
    uint8_t mask)
{
   assert( 0x00 != mask && (USCI_UART_RECEIVE_INTERRUPT_FLAG +
			USCI_UART_TRANSMIT_INTERRUPT_FLAG 
			) );

    return ( HWREG8(baseAddress + OFS_UCAxIFG) & mask );
}

//*****************************************************************************
//
//! Clears UART interrupt sources.
//!
//! \param baseAddress is the base address of the UART module.
//! \param mask is a bit mask of the interrupt sources to be cleared.
//!
//! The UART interrupt source is cleared, so that it no longer asserts.
//! The highest interrupt flag is automatically cleared when an interrupt vector
//! generator is used.
//!
//! The mask parameter has the same definition as the mask parameter to
//! USCI_UART_enableInterrupt().
//!
//! Modified register is \b UCAxIFG
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_clearInterruptFlag (uint32_t baseAddress, uint8_t mask)
{
    //Clear the UART interrupt source.
    HWREG8(baseAddress + OFS_UCAxIFG) &= ~(mask);
}

//*****************************************************************************
//
//! Enables the UART block.
//!
//! \param baseAddress is the base address of the USCI UART module.
//!
//! This will enable operation of the UART block.
//!
//! Modified register is \b UCAxCTL1
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_enable (uint32_t baseAddress)
{
    //Reset the UCSWRST bit to enable the USCI Module
    HWREG8(baseAddress + OFS_UCAxCTL1) &= ~(UCSWRST);
}

//*****************************************************************************
//
//! Disables the UART block.
//!
//! \param baseAddress is the base address of the USCI UART module.
//!
//! This will disable operation of the UART block.
//!
//! Modified register is \b UCAxCTL1
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_disable (uint32_t baseAddress)
{
    //Set the UCSWRST bit to disable the USCI Module
    HWREG8(baseAddress + OFS_UCAxCTL1) |= UCSWRST;
}

//*****************************************************************************
//
//! Gets the current UART status flags.
//!
//! \param baseAddress is the base address of the UART module.
//! \param mask is the masked interrupt flag status to be returned.
//!
//! This returns the status for the UART  module based on which
//! flag is passed. mask parameter can be either any of the following
//! selection.
//! - \b USCI_UART_LISTEN_ENABLE
//! - \b USCI_UART_FRAMING_ERROR
//! - \b USCI_UART_OVERRUN_ERROR
//! - \b USCI_UART_PARITY_ERROR
//! - \b USCI_UART_BREAK_DETECT
//! - \b USCI_UART_RECEIVE_ERROR
//! - \b USCI_UART_ADDRESS_RECEIVED
//! - \b USCI_UART_IDLELINE
//! - \b USCI_UART_BUSY
//!
//! Modified register is \b UCAxSTAT
//!
//! \return the masked status flag
//
//*****************************************************************************
uint8_t USCI_UART_queryStatusFlags (uint32_t baseAddress,
    uint8_t mask)
{
    assert( 0x00 != mask && (USCI_UART_LISTEN_ENABLE +
			USCI_UART_FRAMING_ERROR +
			USCI_UART_OVERRUN_ERROR + 
			USCI_UART_PARITY_ERROR +
			USCI_UART_BREAK_DETECT + 
			USCI_UART_RECEIVE_ERROR +
			USCI_UART_ADDRESS_RECEIVED +
			USCI_UART_IDLELINE +
			USCI_UART_BUSY 
			));

    return ( HWREG8(baseAddress + OFS_UCAxSTAT) & mask );
}

//*****************************************************************************
//
//! Sets the UART module in dormant mode
//!
//! \param baseAddress is the base address of the UART module.
//!
//! Puts USCI in sleep mode
//! Only characters that are preceded by an idle-line or with address bit set
//! UCRXIFG. In UART mode with automatic baud-rate detection, only the
//! combination of a break and synch field sets UCRXIFG.
//!
//! Modified register is \b UCAxCTL1
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_setDormant (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_UCAxCTL1) |= UCDORM;
}

//*****************************************************************************
//
//! Re-enables UART module from dormant mode
//!
//! \param baseAddress is the base address of the UART module.
//!
//! Not dormant. All received characters set UCRXIFG.
//!
//! Modified register is \b UCAxCTL1
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_resetDormant (uint32_t baseAddress)
{
    HWREG8(baseAddress + OFS_UCAxCTL1) &= ~UCDORM;
}

//*****************************************************************************
//
//! Transmits the next byte to be transmitted marked as address depending on
//! selected multiprocessor mode
//!
//! \param baseAddress is the base address of the UART module.
//! \param transmitAddress is the next byte to be transmitted
//!
//! Modified register is \b UCAxCTL1, \b UCAxTXBUF
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_transmitAddress (uint32_t baseAddress,
    uint8_t transmitAddress)
{
    //Set UCTXADDR bit
    HWREG8(baseAddress + OFS_UCAxCTL1) |= UCTXADDR;

    //Place next byte to be sent into the transmit buffer
    HWREG8(baseAddress + OFS_UCAxTXBUF) = transmitAddress;
}

//*****************************************************************************
//
//! Transmit break. Transmits a break with the next write to the transmit
//! buffer. In UART mode with automatic baud-rate detection,
//! USCI_UART_AUTOMATICBAUDRATE_SYNC(0x55) must be written into UCAxTXBUF to
//! generate the required break/synch fields.
//! Otherwise, DEFAULT_SYNC(0x00) must be written into the transmit buffer.
//! Also ensures module is ready for transmitting the next data
//!
//! \param baseAddress is the base address of the UART module.
//!
//! Modified register is \b UCAxCTL1, \b UCAxTXBUF
//!
//! \return None.
//
//*****************************************************************************
void USCI_UART_transmitBreak (uint32_t baseAddress)
{
    //Set UCTXADDR bit
    HWREG8(baseAddress + OFS_UCAxCTL1) |= UCTXBRK;

    //If current mode is automatic baud-rate detection
    if (USCI_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE ==
        (HWREG8(baseAddress + OFS_UCAxCTL0) &
         USCI_UART_AUTOMATIC_BAUDRATE_DETECTION_MODE)){
        HWREG8(baseAddress + OFS_UCAxTXBUF) = USCI_UART_AUTOMATICBAUDRATE_SYNC;
    } else   {
        HWREG8(baseAddress + OFS_UCAxTXBUF) = DEFAULT_SYNC;
    }

    //USCI TX buffer ready?
    while (!USCI_UART_getInterruptStatus(baseAddress, UCTXIFG)) ;
}

//*****************************************************************************
//
//! Returns the address of the RX Buffer of the UART for the DMA module.
//!
//! \param baseAddress is the base address of the UART module.
//!
//! Returns the address of the UART RX Buffer. This can be used in conjunction
//! with the DMA to store the received data directly to memory.
//!
//! \return None
//
//*****************************************************************************
uint32_t USCI_UART_getReceiveBufferAddressForDMA (uint32_t baseAddress)
{
    return ( baseAddress + OFS_UCAxRXBUF );
}

//*****************************************************************************
//
//! Returns the address of the TX Buffer of the UART for the DMA module.
//!
//! \param baseAddress is the base address of the UART module.
//!
//! Returns the address of the UART TX Buffer. This can be used in conjunction
//! with the DMA to obtain transmitted data directly from memory.
//!
//! \return None
//
//*****************************************************************************
uint32_t USCI_UART_getTransmitBufferAddressForDMA (uint32_t baseAddress)
{
    return ( baseAddress + OFS_UCAxTXBUF );
}

//*****************************************************************************
//
//Close the Doxygen group.
//! @}
//
//*****************************************************************************
