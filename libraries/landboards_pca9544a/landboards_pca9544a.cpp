////////////////////////////////////////////////////////////////////////////
//  landboards_pca9544a.cpp - I2C Bridge PCA9544A Library 
//  Created by Douglas Gilliland. 2015-09-05
//  landboards_pca9544a
//	http://land-boards.com/blwiki/index.php?title=I2C-RPT
////////////////////////////////////////////////////////////////////////////

#include "landboards_pca9544a.h"
#include <Wire.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

landboards_pca9544a::landboards_pca9544a()
{
	
}


////////////////////////////////////////////////////////////////////////////
// begin(uint8_t addr) - 
////////////////////////////////////////////////////////////////////////////

void landboards_pca9544a::begin(uint8_t addr) 
{
	i2caddr = addr & 0x7;
	Wire.begin();
	ctrl_copy = 0;  // ctrl reg initialized 
	Wire.beginTransmission(PCA9544A_ADDRESS | i2caddr);
	Wire.write((byte)ctrl_copy);
	Wire.endTransmission();
}

////////////////////////////////////////////////////////////////////////////
// begin(void) - 
////////////////////////////////////////////////////////////////////////////

void landboards_pca9544a::begin(void)
{	
	begin(0);
}

////////////////////////////////////////////////////////////////////////////
// setI2CChannel() - 
////////////////////////////////////////////////////////////////////////////

void landboards_pca9544a::setI2CChannel(uint8_t chNum)
{
	if (chNum > 3)
		return;
	ctrl_copy = 0x04 | chNum;
	Wire.beginTransmission(PCA9544A_ADDRESS | i2caddr);
	Wire.write((byte)ctrl_copy);
	Wire.endTransmission();
	return;
}

////////////////////////////////////////////////////////////////////////////
// getCurrentChannel(void) 
////////////////////////////////////////////////////////////////////////////

uint8_t landboards_pca9544a::setI2CChannel(void)
{
	Wire.requestFrom(PCA9544A_ADDRESS | i2caddr, 1);
	return (Wire.read() & 0x3);
}

////////////////////////////////////////////////////////////////////////////
// getIntStatus
////////////////////////////////////////////////////////////////////////////

uint8_t landboards_pca9544a::getIntStatus(void)
{
	Wire.requestFrom(PCA9544A_ADDRESS | i2caddr, 1);
	return ((Wire.read() >> 4) & 0xf);
}
