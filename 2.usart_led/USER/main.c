#include <stm32f10x.h>
#include "lcd.h"
#include "stdio.h"

char sbuf[20];

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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Pin=0x0000FF00;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}
void key_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_8;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);	
}
unsigned char key_id_lib()
{
	unsigned char id=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
		id=1;
	else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
		id=2;
	else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		id=3;
	else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)==0)
		id=4;
	return id;
}
void key_lcd_display(unsigned char id)
{
	unsigned int a=0;
	if(id==1)
		a=1;
	if(id==2)
		a=2;
	if(id==3)
		a=3;
	if(id==4)
		a=4;
	
	sprintf(sbuf,"     key_id=%u",a);
	LCD_DisplayStringLine(Line0,(u8*)sbuf);
}

void key_proc(unsigned char id)
{
	if(id==1)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<8);
	else if(id==2)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<9);
	else if(id==3)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<10);
	else if(id==4)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<11);
	else
		GPIOC->ODR=GPIOC->ODR|0x0000FF00;
	
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}
void uart_config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate=9600;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b ;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx;
	USART_Init(USART2,&USART_InitStruct);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART2,ENABLE);
}

extern char led_01_on;
extern char led_02_on;
extern char buf[20];
void usart_led()
{
	if(led_01_on)
		GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<12);
	else if(led_02_on)
			GPIOC->ODR=(GPIOC->ODR|0x0000FF00)&~(1<<13);
	    GPIO_SetBits(GPIOD,GPIO_Pin_2);
		  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void usart_lcd_display()
{
	LCD_DisplayStringLine(Line1,(u8*)buf);
}

int main(void)
{
	led_config();
	key_config();
	uart_config();
	
	STM3210B_LCD_Init();
	LCD_Clear(Blue);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(White);
	while(1)
	{
		key_proc(key_id_lib());
		usart_led();
    key_lcd_display(key_id_lib());		
		usart_lcd_display();
	}
	
}