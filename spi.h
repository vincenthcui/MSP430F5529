/*
 * spi.h
 *
 *  Created on: 2014Äê8ÔÂ13ÈÕ
 *      Author: Chrics
 *      For: spi connect in 1 to 1 module.
 */

#ifndef SPI_H_
#define SPI_H_

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

#endif /* SPI_H_ */
