#include <msp430.h>
#include "spi.h"
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
