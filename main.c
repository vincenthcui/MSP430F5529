#include <msp430f5529.h>
#include "LDC1000_cmd.h"

void SetVCoreUp(unsigned int level);

char spi_readByte( char addr, char * data);
char spi_readWord(char addr, unsigned int * data);  // Big Endian
char spi_readBytes( char addr, char * buffer, unsigned char len);
char spi_writeByte(char addr, char data);
char spi_writeWord(char addr, unsigned int data);  // Big Endian
char spi_writeBytes( char addr, char * buffer, unsigned char len);

static unsigned char txlen;
static unsigned char rxlen;
static char *txbuf;
static char *rxbuf;
static char txaddr;
static char wordbuf[2];

char proximtyData[2];
char frequencyData[3];

int proximtyDataMIN;
int frequencyDataMIN;

int proximtyDataMAX;
int frequencyDataMAX;

int proximtyDataTEMP;
int frequencyDataTEMP;

#define RPMIN 0x3A
#define RPMAX 0x13

/** @} */
/*
 * main.c
 */
char main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	SetVCoreUp(1);
	SetVCoreUp(2);
	SetVCoreUp(3);

//	//UCS SETTING
    UCSCTL3 |= SELREF__REFOCLK;
    __bis_SR_register(SCG0);                  // Disable the FLL control loop
    UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_6;                      // Select DCO range 24MHz operation
	UCSCTL2 = FLLD_0 + 731;                   // Set DCO Multiplier for 24MHz
												// (N + 1) * FLLRef = Fdco
											   // (731 + 1) * 32768 = 24MHz
											   // Set FLL Div = fDCOCLK/2
    __bic_SR_register(SCG0);                  // Enable the FLL control loop
	UCSCTL4 |= SELA__DCOCLK + SELS__XT1CLK +SELM__DCOCLK; //ACLK,SMCLK,MCLK Source select
    UCSCTL5 |= DIVPA_2;                                   //ACLK output divide
    UCSCTL6 |= XT1DRIVE_3 + XCAP_0;                       //XT1 cap

    //PORT INIT

    P1DIR |= BIT0;                        // LDC CLK for Freq counter (set to output selected clock)
    P1SEL |= BIT0;

	// LEDs
	P7DIR |= BIT0;
	P4DIR |= BIT7;

	//INTB INIT
//	P1DIR &= ~BIT2;                            // Set P1.2 input
//	P1IES |= BIT2;                           // P1.2 Hi/Lo edge
//	P1IFG &= ~BIT2;                           // P1.2 IFG cleared
//	P1IE |= BIT2;                             // P1.2 interrupt enabled

	// initialize SPI
	P4DIR |= BIT0;  // Output
	P4SEL &= ~BIT0;
	
	//SPI SETUP
	P4SEL |=BIT1 + BIT2 + BIT3;
	UCB1CTL1 |=UCSWRST;
	UCB1CTL0 |= UCMST+UCMSB+UCSYNC+UCCKPL;   // 3-pin, 8-bit SPI master,Clock polarity high, MSB
    UCB1CTL1 |= UCSSEL_1;                 // CLOCK ACLK
	UCB1BR0 = 0x06;
    UCB1BR1 = 0;
    UCB1CTL1 &= ~UCSWRST;
    //read all REG value using default setting
    char orgVal[0x25];

    //write to register
    spi_writeByte(LDC1000_CMD_RPMAX,       RPMAX);
    spi_writeByte(LDC1000_CMD_RPMIN,       RPMIN);
	spi_writeByte(LDC1000_CMD_SENSORFREQ,  0x94);
	spi_writeByte(LDC1000_CMD_LDCCONFIG,   0x17);
	spi_writeByte(LDC1000_CMD_CLKCONFIG,   0x02);
	spi_writeByte(LDC1000_CMD_INTCONFIG,   0x04);		//open int

	spi_writeByte(LDC1000_CMD_THRESHILSB,  0x50);
	spi_writeByte(LDC1000_CMD_THRESHIMSB,  0x14);
	spi_writeByte(LDC1000_CMD_THRESLOLSB,  0xC0);
	spi_writeByte(LDC1000_CMD_THRESLOMSB,  0x12);

	spi_writeByte(LDC1000_CMD_PWRCONFIG,   0x01);

	//read all registers

    spi_readBytes(LDC1000_CMD_REVID, &orgVal[0],0x25);

    int i;

    //read all registers using extended SPI
    while (1)
    {
    	spi_readBytes(LDC1000_CMD_REVID, &orgVal[0],0x25);
    	spi_readBytes(LDC1000_CMD_REVID, &orgVal[0],0x25);
    }
}


/**sub functions**/

char spi_readByte( char addr, char * data)
{
	    rxlen = 1;
		rxbuf = data;
		txaddr = addr | 0x80;

		P4OUT &= ~BIT0;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = txaddr;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = 0;
		while (UCB1STAT & UCBUSY);
		* rxbuf = UCB1RXBUF;

		while (UCB1STAT & UCBUSY);
		P4OUT |= BIT0;

		return 0;
}

char spi_readWord(char addr, unsigned int * data)
{
		rxlen = 2;
		rxbuf = &wordbuf[0];
		txaddr = addr | 0x80;

		P4OUT &= ~BIT0;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = txaddr;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = 0;
		while (UCB1STAT & UCBUSY);
		* rxbuf = UCB1RXBUF;
		rxbuf++;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = 0;
		while (UCB1STAT & UCBUSY);
		* rxbuf = UCB1RXBUF;

		while (UCB1STAT & UCBUSY);
		P4OUT |= BIT0;

		return 0;

}
char spi_readBytes( char addr, char * buffer, unsigned char len)
{
		rxlen = len;
		rxbuf = buffer;
		txaddr = addr | 0x80;

		P4OUT &= ~BIT0;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = txaddr;

		while (rxlen > 0) {
			while (!(UCB1IFG&UCTXIFG));
			UCB1TXBUF = 0;
			while (UCB1STAT & UCBUSY);
			* rxbuf = UCB1RXBUF;
			rxbuf++;
			rxlen--;
			}

		while (UCB1STAT & UCBUSY);
		P4OUT |= BIT0;

		return 0;
	}

char spi_writeByte(char addr, char data)
{
		wordbuf[0] = data;          // copy from stack to memory
		txlen = 1;
		txbuf = &wordbuf[0];
		txaddr = addr & ~0x80;

		P4OUT &= ~BIT0;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = txaddr;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = *txbuf;

		while (UCB1STAT & UCBUSY);
		P4OUT |= BIT0;

		return 0;
	}

char spi_writeWord(char addr, unsigned int data)
{
		wordbuf[0] = data >> 8;    // Big Endian
		wordbuf[1] = data & 0xFF;
		txlen = 2;
		txbuf = &wordbuf[0];
		txaddr = addr & ~0x80;

		P4OUT &= ~BIT0;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = txaddr;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = *txbuf;
		txbuf++;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = *txbuf;

		while (UCB1STAT & UCBUSY);
		P4OUT |= BIT0;

		return 0;

}

char spi_writeBytes( char addr, char * buffer, unsigned char len)
{
		txlen = len;
		txbuf = buffer;
		txaddr = addr & ~0x80;

		P4OUT &= ~BIT0;
		while (!(UCB1IFG&UCTXIFG));
		UCB1TXBUF = txaddr;

		while (txlen > 0) {
			while (!(UCB1IFG&UCTXIFG));
			UCB1TXBUF = *txbuf;
			txbuf++;
			txlen--;
				}

		while (UCB1STAT & UCBUSY);
		P4OUT |= BIT0;

		return 0;

	}


void SetVCoreUp (unsigned int level)
{
		// Open PMM registers for write access
		PMMCTL0_H = 0xA5;
		// Make sure no flags are set for iterative sequences
//		while ((PMMIFG & SVSMHDLYIFG) == 0);
//		while ((PMMIFG & SVSMLDLYIFG) == 0);
		// Set SVS/SVM high side new level
		SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
		// Set SVM low side to new level
		SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
		// Wait till SVM is settled
		while ((PMMIFG & SVSMLDLYIFG) == 0);
		// Clear already set flags
		PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
		// Set VCore to new level
		PMMCTL0_L = PMMCOREV0 * level;
		// Wait till new level reached
		if ((PMMIFG & SVMLIFG))
		while ((PMMIFG & SVMLVLRIFG) == 0);
		// Set SVS/SVM low side to new level
		SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
		// Lock PMM registers for write access
		PMMCTL0_H = 0x00;
}
