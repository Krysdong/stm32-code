#include <stm32f10x.h>

void Delay_Ms(u32 nms)
{
	SysTick->LOAD=9000*nms;
	SysTick->VAL=0;
	SysTick->CTRL=1;
	while((SysTick->CTRL&(1<<16))==0);
	SysTick->CTRL=0;
		
}

void led_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	
  GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=0x0000FF00;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void timer2_init()
{
	
}

int main(void)
{
	while(1)
	{
		
	}
}



