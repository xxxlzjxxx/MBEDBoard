
#include "includes.h"

extern uchar timeout_10min_flag;
extern uchar FlagADCSampling;

#pragma vector=TIMERB0_VECTOR
__interrupt void TIMERB0_ISR(void)
{      
   FlagADCSampling = 1;
}