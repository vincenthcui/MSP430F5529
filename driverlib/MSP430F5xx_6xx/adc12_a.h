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
#ifndef __MSP430WARE_ADC12_A_H__
#define __MSP430WARE_ADC12_A_H__

//*****************************************************************************
//
//The following are the defines to include the required modules for this
//peripheral in msp430xgeneric.h file
//
//*****************************************************************************
#define __MSP430_HAS_ADC12_PLUS__

#include "inc/hw_regaccess.h"

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_init() in the
//sampleTimerSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_A_SAMPLEHOLDSOURCE_SC (ADC12SHS_0)
#define ADC12_A_SAMPLEHOLDSOURCE_1  (ADC12SHS_1)
#define ADC12_A_SAMPLEHOLDSOURCE_2  (ADC12SHS_2)
#define ADC12_A_SAMPLEHOLDSOURCE_3  (ADC12SHS_3)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_init() in the
//clockSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_A_CLOCKSOURCE_ADC12OSC (ADC12SSEL_0)
#define ADC12_A_CLOCKSOURCE_ACLK     (ADC12SSEL_1)
#define ADC12_A_CLOCKSOURCE_MCLK     (ADC12SSEL_2)
#define ADC12_A_CLOCKSOURCE_SMCLK    (ADC12SSEL_3)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_init() in the
//clockSourceDivider parameter.
//Note: Bit 1 determines if the pre-divider is 1 (0x00) or 4 (0x01)
//Bits 5-7 determine the the post-divider 1-8 (0x00 - 0xE0)
//
//*****************************************************************************
#define ADC12_A_CLOCKDIVIDER_1  (ADC12DIV_0)
#define ADC12_A_CLOCKDIVIDER_2  (ADC12DIV_1)
#define ADC12_A_CLOCKDIVIDER_3  (ADC12DIV_2)
#define ADC12_A_CLOCKDIVIDER_4  (ADC12DIV_3)
#define ADC12_A_CLOCKDIVIDER_5  (ADC12DIV_4)
#define ADC12_A_CLOCKDIVIDER_6  (ADC12DIV_5)
#define ADC12_A_CLOCKDIVIDER_7  (ADC12DIV_6)
#define ADC12_A_CLOCKDIVIDER_8  (ADC12DIV_7)
#define ADC12_A_CLOCKDIVIDER_12 (ADC12DIV_2 + ADC12PDIV)
#define ADC12_A_CLOCKDIVIDER_16 (ADC12DIV_3 + ADC12PDIV)
#define ADC12_A_CLOCKDIVIDER_20 (ADC12DIV_4 + ADC12PDIV)
#define ADC12_A_CLOCKDIVIDER_24 (ADC12DIV_5 + ADC12PDIV)
#define ADC12_A_CLOCKDIVIDER_28 (ADC12DIV_6 + ADC12PDIV)
#define ADC12_A_CLOCKDIVIDER_32 (ADC12DIV_7 + ADC12PDIV)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_setResolution() in the
//resolutionSelect parameter.
//
//*****************************************************************************
#define ADC12_A_RESOLUTION_8BIT  (ADC12RES_0)
#define ADC12_A_RESOLUTION_10BIT (ADC12RES_1)
#define ADC12_A_RESOLUTION_12BIT (ADC12RES_2)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_setupSamplingTimer() in
//the clockCycleHoldCountLowMem and clockCycleHoldCountHighMem parameters.
//
//*****************************************************************************
#define ADC12_A_CYCLEHOLD_4_CYCLES    (ADC12SHT0_0)
#define ADC12_A_CYCLEHOLD_8_CYCLES    (ADC12SHT0_1)
#define ADC12_A_CYCLEHOLD_16_CYCLES   (ADC12SHT0_2)
#define ADC12_A_CYCLEHOLD_32_CYCLES   (ADC12SHT0_3)
#define ADC12_A_CYCLEHOLD_64_CYCLES   (ADC12SHT0_4)
#define ADC12_A_CYCLEHOLD_96_CYCLES   (ADC12SHT0_5)
#define ADC12_A_CYCLEHOLD_128_CYCLES  (ADC12SHT0_6)
#define ADC12_A_CYCLEHOLD_192_CYCLES  (ADC12SHT0_7)
#define ADC12_A_CYCLEHOLD_256_CYCLES  (ADC12SHT0_8)
#define ADC12_A_CYCLEHOLD_384_CYCLES  (ADC12SHT0_9)
#define ADC12_A_CYCLEHOLD_512_CYCLES  (ADC12SHT0_10)
#define ADC12_A_CYCLEHOLD_768_CYCLES  (ADC12SHT0_11)
#define ADC12_A_CYCLEHOLD_1024_CYCLES (ADC12SHT0_12)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_setupSamplingTimer() in
//the multipleSamplesEnabled parameter.
//
//*****************************************************************************
#define ADC12_A_MULTIPLESAMPLESDISABLE ( !(ADC12MSC) )
#define ADC12_A_MULTIPLESAMPLESENABLE  (ADC12MSC)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_memoryConfigure(),
//ADC12_A_startConversion(), and ADC12_A_readResults() in the memoryIndex and
//startingMemoryIndex parameters.
//
//*****************************************************************************
#define ADC12_A_MEMORY_0  (0x0)
#define ADC12_A_MEMORY_1  (0x1)
#define ADC12_A_MEMORY_2  (0x2)
#define ADC12_A_MEMORY_3  (0x3)
#define ADC12_A_MEMORY_4  (0x4)
#define ADC12_A_MEMORY_5  (0x5)
#define ADC12_A_MEMORY_6  (0x6)
#define ADC12_A_MEMORY_7  (0x7)
#define ADC12_A_MEMORY_8  (0x8)
#define ADC12_A_MEMORY_9  (0x9)
#define ADC12_A_MEMORY_10 (0xA)
#define ADC12_A_MEMORY_11 (0xB)
#define ADC12_A_MEMORY_12 (0xC)
#define ADC12_A_MEMORY_13 (0xD)
#define ADC12_A_MEMORY_14 (0xE)
#define ADC12_A_MEMORY_15 (0xF)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_memoryConfigure() in the
//inputSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_A_INPUT_A0              (ADC12INCH_0)
#define ADC12_A_INPUT_A1              (ADC12INCH_1)
#define ADC12_A_INPUT_A2              (ADC12INCH_2)
#define ADC12_A_INPUT_A3              (ADC12INCH_3)
#define ADC12_A_INPUT_A4              (ADC12INCH_4)
#define ADC12_A_INPUT_A5              (ADC12INCH_5)
#define ADC12_A_INPUT_A6              (ADC12INCH_6)
#define ADC12_A_INPUT_A7              (ADC12INCH_7)
#define ADC12_A_INPUT_A8              (ADC12INCH_8)
#define ADC12_A_INPUT_A9              (ADC12INCH_9)
#define ADC12_A_INPUT_TEMPSENSOR      (ADC12INCH_10)
#define ADC12_A_INPUT_BATTERYMONITOR  (ADC12INCH_11)
#define ADC12_A_INPUT_A12             (ADC12INCH_12)
#define ADC12_A_INPUT_A13             (ADC12INCH_13)
#define ADC12_A_INPUT_A14             (ADC12INCH_14)
#define ADC12_A_INPUT_A15             (ADC12INCH_15)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_memoryConfigure() in the
//positiveRefVoltageSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_A_VREFPOS_AVCC ( !(ADC12SREF0 + ADC12SREF1) )
#define ADC12_A_VREFPOS_INT  (ADC12SREF0)
#define ADC12_A_VREFPOS_EXT  (ADC12SREF1)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_memoryConfigure() in the
//negativeRefVoltageSourceSelect parameter.
//
//*****************************************************************************
#define ADC12_A_VREFNEG_AVSS ( !(ADC12SREF2) )
#define ADC12_A_VREFNEG_EXT  (ADC12SREF2)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_memoryConfigure() in the
//endOfSequence parameter.
//
//*****************************************************************************
#define ADC12_A_NOTENDOFSEQUENCE ( !(ADC12EOS) )
#define ADC12_A_ENDOFSEQUENCE    (ADC12EOS)

//*****************************************************************************
//
//The following are mask values that can be passed to ADC12_A_enableInterrupt()
//or ADC12_A_disableInterrupt in the interruptMask parameter.
//
//*****************************************************************************
#define ADC12OVIE0  ( (uint32_t)ADC12OVIE << 16)

#define ADC12TOVIE0 ( (uint32_t)ADC12TOVIE << 16)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_startConversion() in the
//conversionSequenceModeSelect parameter.
//
//*****************************************************************************
#define ADC12_A_SINGLECHANNEL          (ADC12CONSEQ_0)
#define ADC12_A_SEQOFCHANNELS          (ADC12CONSEQ_1)
#define ADC12_A_REPEATED_SINGLECHANNEL (ADC12CONSEQ_2)
#define ADC12_A_REPEATED_SEQOFCHANNELS (ADC12CONSEQ_3)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_disableConversions() in
//the preempt parameter.
//
//*****************************************************************************
#define ADC12_A_COMPLETECONVERSION (0x0)
#define ADC12_A_PREEMPTCONVERSION  (0x1)

//*****************************************************************************
//
//The following are values that can be passed to
//ADC12_A_setSampleHoldSignalInversion() in the invertedSignal parameter.
//
//*****************************************************************************
#define ADC12_A_NONINVERTEDSIGNAL ( !(ADC12ISSH) )
#define ADC12_A_INVERTEDSIGNAL    (ADC12ISSH)

//*****************************************************************************
//
//The following are values that can be passed to ADC12_A_setDataReadBackFormat()
//in the readBackFormat parameter.
//
//*****************************************************************************
#define ADC12_A_UNSIGNED_BINARY     ( !(ADC12DF) )
#define ADC12_A_SIGNED_2SCOMPLEMENT (ADC12DF)

//*****************************************************************************
//
//The following are values that can be passed to
//ADC12_A_setReferenceBufferSamplingRate() in the samplingRateSelect parameter.
//
//*****************************************************************************
#define ADC12_A_MAXSAMPLINGRATE_200KSPS ( !(ADC12SR) )
#define ADC12_A_MAXSAMPLINGRATE_50KSPS  (ADC12SR)

//*****************************************************************************
//
//The following are values that are returned by ADC12_A_isBusy().
//
//*****************************************************************************
#define ADC12_A_NOTBUSY (0x0)
#define ADC12_A_BUSY    (0x1)

//*****************************************************************************
//
//Prototypes for the APIs.
//
//*****************************************************************************

extern unsigned short ADC12_A_init (uint32_t baseAddress,
    uint16_t sampleHoldSourceSelect,
    uint8_t clockSourceSelect,
    uint16_t clockSourceDivider);

void ADC12_A_enable (uint32_t baseAddress);

void ADC12_A_disable (uint32_t baseAddress);

extern void ADC12_A_setupSamplingTimer (uint32_t baseAddress,
    uint16_t clockCycleHoldCountLowMem,
    uint16_t clockCycleHoldCountHighMem,
    unsigned short multipleSamplesEnabled);

extern void ADC12_A_disableSamplingTimer (uint32_t baseAddress);

extern void ADC12_A_memoryConfigure (uint32_t baseAddress,
    uint8_t memoryBufferControlIndex,
    uint8_t inputSourceSelect,
    uint8_t positiveRefVoltageSourceSelect,
    uint8_t negativeRefVoltageSourceSelect,
    unsigned short endOfSequence);

extern void ADC12_A_enableInterrupt (uint32_t baseAddress,
    uint32_t interruptMask);

extern void ADC12_A_disableInterrupt (uint32_t baseAddress,
    uint32_t interruptMask);

extern void ADC12_A_clearInterrupt (uint32_t baseAddress,
    uint16_t memoryBufferInterruptFlagMask);

extern uint8_t ADC12_A_getInterruptStatus (uint32_t baseAddress,
    uint16_t memoryBufferInterruptFlagMask);

extern void ADC12_A_startConversion (uint32_t baseAddress,
    uint16_t startingMemoryBufferIndex,
    uint8_t conversionSequenceModeSelect);

void ADC12_A_disableConversions (uint32_t baseAddress,
    unsigned short preempt);

int ADC12_A_getResults (uint32_t baseAddress,
    uint8_t memoryBufferIndex);

void ADC12_A_setResolution (uint32_t baseAddress,
    uint8_t resolutionSelect);

extern void ADC12_A_setSampleHoldSignalInversion (uint32_t baseAddress,
    uint16_t invertedSignal);

extern void ADC12_A_setDataReadBackFormat (uint32_t baseAddress,
    unsigned short readBackFormat);

extern void ADC12_A_enableReferenceBurst (uint32_t baseAddress);

extern void ADC12_A_disableReferenceBurst (uint32_t baseAddress);

extern void ADC12_A_setReferenceBufferSamplingRate (uint32_t baseAddress,
    unsigned short samplingRateSelect);

extern uint32_t ADC12_A_getMemoryAddressForDMA (uint32_t baseAddress,
    uint8_t memoryIndex);

extern unsigned short ADC12_A_isBusy (uint32_t baseAddress);

#endif
