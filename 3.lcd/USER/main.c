#include <stm32f10x.h>
#include "lcd.h"
#include <stdio.h>

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
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
}

/*void key_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_8;
		
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

unsigned char key_id()
{
	unsigned char id=0;
	if((GPIOA->IDR&(1<<0))==0) //B1
		id=1;
	if((GPIOA->IDR&(1<<8))==0) //B2
		id=2;
	if((GPIOB->IDR&(1<<1))==0) //B3
		id=3;
	if((GPIOB->IDR&(1<<2))==0) //B4
		id=4;
	return id;	
}

unsigned char key_id_lib() //the version of library
{
	//static unsigned char id=0;
	unsigned char id=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
		id=1;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		id=2;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		id=3;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
		id=4;
	
	return id;
	
}

void key_led(unsigned char id)
{
	if(id==1)
	  GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<10);
	else if(id==2)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<11);
	else if(id==3)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<12);
	else if(id==4)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<13);
	else
		GPIOC->ODR=GPIOC->ODR|0x0000FF00;
	
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

char buf[21];

void lcd_display(unsigned char id)
{
	unsigned int a=0;
	if(id==1)
		a=1;
	else if(id==2)
		a=2;
	else if(id==3)
		a=3;
	else if(id==4)
		a=4;
	
	sprintf(buf,"     key_led=%u",a); //20bit in a line 
	LCD_DisplayStringLine(Line0,(u8*)buf);
	
}
*/
int main(void)
{
	led_config();
	//key_config();
	
	//STM3210B_LCD_Init();
	//LCD_Clear(Black);
	//LCD_SetBackColor(Black);
	//LCD_SetTextColor(White);
	
	STM3210B_LCD_Init();
	LCD_Clear(Red);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(Black);
	
//	LCD_DrawLine(10,30,100,Horizontal);
	LCD_DrawRect(10,319-30,60,120); //draw rectangle ,distance top10,distance right 319-30,height,width
	
	while(1)
	{
		
		/*int i;
		for(i=8;i<15;i++)
		{
			GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<i);
		 // GPIO_SetBits(GPIOD,GPIO_Pin_2);
			delay_ms(1000);
		}*/
		
		//lcd_display(key_id_lib());
		//key_led(key_id_lib());
	}
}
