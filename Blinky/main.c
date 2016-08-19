/* Copyright (c) 2016 pcbreflux. All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>. *
 */

/** @file main.c
 * @brief Blinky Example Application main file.
 *
 */
#include <stdio.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime);

/**
 * @brief Function for application main entry.
 */
int main(void) {

	if (SysTick_Config(SystemCoreClock/1000)) 
		while(1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	uint16_t iCount1 = 0;
	static int ledval = 1;

	while (1) {
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, (ledval) ? Bit_SET : Bit_RESET);
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, (ledval) ? Bit_RESET : Bit_SET);
		ledval = 1 - ledval;

		Delay(200);
		iCount1++;
	}
}



/** @brief Function Timing delay.
 */
void Delay(uint32_t nTime) {
	TimingDelay = nTime;
	while (TimingDelay != 0);
}

/** @brief Function SysTick Handler.
 */
void SysTick_Handler(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
	while (1);
}
#endif


