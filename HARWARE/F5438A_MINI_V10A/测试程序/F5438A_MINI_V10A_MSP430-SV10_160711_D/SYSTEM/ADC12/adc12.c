//******************************************************************************
//  Init adc12, Using the AVCC Reference
//
//  Description: This example shows how to use the shared reference for ADC12
//  sampling and performs a single conversion on channel A0. The conversion 
//  results are stored in ADC12MEM0. Test by applying a voltage to channel A0, 
//  then setting and running to a break point at the "__no_operation()" 
//  instruction. To view the conversion results, open an ADC12 register window 
//  in debugger and view the contents of ADC12MEM0
//
//                MSP430F543xA
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//    Vbat -->|P6.0/A0          |
//            |                 |

//
//   xxxlzjxxx
//   SICHUAN HUIYUAN OPTICAL CONMUNICATION CO.LTD
//   June 2015
//   IAR Embedded Workbench Version: 6.10.5
//******************************************************************************

#include "includes.h"

void ADC12_Init(void)
{
  	ADC12CTL0 &= ~ADC12ENC;
  	P6SEL |= BIT0;   
  
/* Initialize REF module */
// Enable 2.5V shared reference, disable temperature sensor to save power
  	REFCTL0 |= REFMSTR+REFVSEL_2+REFON+REFTCOFF; 
/* Initialize adc12 */ 
  	ADC12CTL0 = ADC12SHT0_15 + ADC12ON + ADC12MSC; 
  	ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1 + ADC12SSEL_1;// Use sampling timer, repeated sequence,ADCCLK=ACLK
  	ADC12MCTL0 = ADC12SREF_0 + ADC12INCH_0 + ADC12EOS;        // ref+=AVcc, channel = A0, end seq.
  	ADC12CTL0 |=  ADC12ENC;  
}
