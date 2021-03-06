/*
 Rocrail - Model Railroad Software

Copyright (c) 2002-2015 Robert Jan Versluis, Rocrail.net

 


 All rights reserved.
*/

#ifndef ROCNETNODE_I2C_H_
#define ROCNETNODE_I2C_H_

#define PWM_SUBADR1      0x02
#define PWM_SUBADR2      0x03
#define PWM_SUBADR3      0x04
#define PWM_MODE1        0x00
#define PWM_PRESCALE     0xFE
#define PWM_LED0_ON_L    0x06
#define PWM_LED0_ON_H    0x07
#define PWM_LED0_OFF_L   0x08
#define PWM_LED0_OFF_H   0x09
#define PWM_ALLLED_ON_L  0xFA
#define PWM_ALLLED_ON_H  0xFB
#define PWM_ALLLED_OFF_L 0xFC
#define PWM_ALLLED_OFF_H 0xFD


int raspiWriteRegI2C( int descriptor, unsigned char dev_addr, unsigned char regaddr, unsigned char data );
int raspiReadRegI2C( int descriptor, unsigned char dev_addr, unsigned char regaddr, unsigned char* data );
int raspiWriteI2C( int descriptor, unsigned char dev_addr, unsigned char data );
int raspiReadI2C(int descriptor, unsigned char dev_addr, unsigned char* data);
int raspiOpenI2C( const char* devicename );
int raspiCloseI2C( int descriptor );

int pwmSetFreq(int descriptor, unsigned char dev_addr, int freq);
int pwmSetChannel(int descriptor, unsigned char dev_addr, int channel, int on, int off);
int pwmStop(int descriptor, unsigned char dev_addr);
int pwmStart(int descriptor, unsigned char dev_addr);

#endif

