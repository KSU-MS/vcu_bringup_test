#ifndef PINDEFS_H
#define PINDEFS_H
#include <stdint.h>
#define WSFL 28 //Input Pullup
#define WSFR 29 //Input Pullup
#define SDCVSENSE 39 //analog
#define SDCISENSE 20 //analog
#define BSPDSENSE 16 //analog
#define GLV_VSENSE 41 //analog
#define GLV_ISENSE 38 //analog
#define _5V_VSENSE 40 //analog
#define A9 27 //analog
#define A10 26 //analog


// analog_pin analog_pins[]={wsfl,wsfr,sdcvsense,sdcisense,bspdsense,glv_vsense,glv_isense,_5v_vsense,a9,a10};

#define BUZZER 4 //Output
#define LOWSIDE1 5 //output
#define LOWSIDE2 6 //output

uint8_t DIGITAL_OUTPUTS[] = {BUZZER,LOWSIDE1,LOWSIDE2};
/*
 * ADC pin definitions
 */
#define ADC_BRAKE_1_CHANNEL 2
#define ADC_HALL_CHANNEL 3 //currently offline because i cooked one of the filter hcips
#define ADC_ACCEL_1_CHANNEL 0
#define ADC_ACCEL_2_CHANNEL 1
#define CS_ADC 10

#define ADC_RESOLUTION 4095
#define ADC_VREF 5.0
#define ADC_CONVERSION_FACTOR (ADC_RESOLUTION / ADC_VREF)

#define NUM_TX_MAILBOXES 32
#define NUM_RX_MAILBOXES 32
uint8_t ANALOG_INPUTS[] = {WSFL,WSFR,SDCVSENSE,SDCISENSE,BSPDSENSE,GLV_VSENSE,GLV_ISENSE,_5V_VSENSE,A9,A10};
String sensor_names[] = {"wsfl","wsfr","sdcvsense","sdcisense","bspdsense","glv_vsense","glv_isense","5v vsense","a9","a10"};

#endif