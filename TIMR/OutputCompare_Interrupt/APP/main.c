#include "SWM241.h"


int main(void)
{	
	uint32_t i;
	SystemInit();
	
	PORT_Init(PORTB, PIN2,  PORTB_PIN2_TIMR2_OUT, 0);
	PORT_Init(PORTB, PIN14, PORTB_PIN14_TIMR2_OUT, 0);
	
	TIMR_Init(TIMR2, TIMR_MODE_TIMER, 1, 10000, 0);	//�������ʱTIMRֻ��16λ��Ƶ��Ϊ24MHz/10000 = 2.4KHz
	
	TIMR_OC_Init(TIMR2, 2500, 1, 0);				//ռ�ձ�2500/10000 = 25%
	
	while(1==1)
	{
		TIMR_Start(TIMR2);
		
		for(i = 0; i < 100000; i++);
	}
}

void TIMR2_Handler(void)
{
	static uint32_t times = 0;
	
	if(TIMR_OC_INTStat(TIMR2))
	{
		TIMR_OC_INTClr(TIMR2);
		
		if(++times == 6)
		{
			times = 0;
			
			TIMR_Stop(TIMR2);
		}
	}
}