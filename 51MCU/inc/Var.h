#ifndef Var_H_
#define Var_H_

/*************************************头文件**************************************/
	#include <STC12C5A60S2.h>
//	#include <STC89C5xRC.h>
	#include <intrins.h>
	#include <MATH.h>
	#include <stdio.h>	
	#include <Init.h>
//	#include <LCD1602.h> 
//	#include <LCD12864.h>
//	#include <ADC.h>
//	#include <huitu.h>
//	#include <DS18B20.h>
//	#include <DS1302.h>
	#include <shumaguan.h>
//	#include <keyboard.h>
	#include <Timer.h>
//	#include <PWM.h>
//	#include <I2C.h>
//	#include <MPU6050.h>
//	#include <HMC5883.h>
//	#include <Measure_Length.h>
//	#include <MMA7660.h>
	#include <Uart_Init.h>
//	#include <IMU.h>
/********************************************************************************/

	//typedef unsigned char uchar;
/***********************************端口定义*************************************/
	#define DATA P1
	#define keyboard  P3
	
//	sbit SCL=P0^5;			//IIC时钟引脚定义
//	sbit SDA=P0^6;			//IIC数据引脚定义
	sbit SCL=P3^5;			//IIC时钟引脚定义
	sbit SDA=P3^6;			//IIC数据引脚定义
//	sbit LE1=P2^0;
//	sbit LE2=P2^1;
//	sbit E = P2^2;
//	sbit RW = P2^3;
//	sbit RS= P2^4;
//	sbit RES = P2^5;
//	sbit PSB = P2^7;
//	sbit DQ = P3^3;
//	sbit Trig = P0^1;
//	sbit Echo = P0^2;
//	sbit SCLK=P0^0;		
//	sbit IO=P0^1;		
//	sbit CE=P0^2;
/********************************************************************************/

	#define Fosc 12				 	//晶振频率
	//#define Fosc 30				 	//晶振频率

/*******************************全局变量定义*************************************/
	extern unsigned char code number[];
	extern unsigned char code String2[];
	extern unsigned char code String1[];
	extern unsigned char code String[];
	extern unsigned char count;
/********************************************************************************/

#endif