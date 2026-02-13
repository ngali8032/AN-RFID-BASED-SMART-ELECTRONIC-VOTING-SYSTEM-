#include <lpc21xx.h>
#include "lcd.h"
#include "delay.h"

void Init_i2c()
{
	PINSEL0 |= 0x00000050;
	I2SCLH = 0x4B;
	I2SCLL = 0x4B;
	I2CONSET = 1<<6;
}

void i2c_start()
{
	I2CONSET = 1<<5;
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR = 1<<5;
}

void i2c_restart()
{
	I2CONSET = 1<<5;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0);
	I2CONCLR = 1<<5; 
}

void i2c_stop()
{
	I2CONSET = 1<<4;
	I2CONCLR = 1<<3;
}

void i2c_write(unsigned char data)
{
	I2DAT = data;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0); 
}

unsigned char i2c_nack()
{
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0)	;
	return I2DAT;
}

unsigned char i2c_mack()
{
	I2CONSET = 1<<2;
	I2CONCLR = 1<<3;
	while(((I2CONSET>>3)&1)==0)	;
	I2CONCLR = 1<<2;
	return I2DAT;
}

void i2c_eeprom_write(short int wAddr, unsigned char slave,unsigned char data)
{
	i2c_start();
	i2c_write(slave<<1);
	i2c_write(wAddr>>8);
	i2c_write(wAddr);
	i2c_write(data);
	i2c_stop();	
	delay_ms(10);
}

unsigned char i2c_eeprom_read(short int wAddr, unsigned char slave)
{
	unsigned char data;
	i2c_start();
	i2c_write(slave<<1);
	i2c_write(wAddr>>8);
	i2c_write(wAddr);
	i2c_restart();
	i2c_write(slave<<1|1);
	data = i2c_nack(); 
	i2c_stop();
	return data;	
}

void i2c_eeprom_pagewrite(short int wAddr, unsigned char slave,char *p, int length)
{
	int i;
	i2c_start();
	i2c_write(slave<<1);
	i2c_write(wAddr>>8);
	i2c_write(wAddr);
	for(i=0; i<length; i++)
	{
		i2c_write(p[i]);
	}
	i2c_stop();	
	delay_ms(10);
}

void i2c_eeprom_pageread(short int wAddr, unsigned char slave,char *p, int length)

{

	int i;

	i2c_start();

	i2c_write(slave<<1);

	i2c_write(wAddr>>8);

	i2c_write(wAddr);

	i2c_restart();

	i2c_write(slave<<1|1);

	for(i=0; i<length-1; i++){

		p[i] = i2c_mack(); 

		delay_ms(10);
	}

	p[i] = i2c_nack();

	i2c_stop();	

}