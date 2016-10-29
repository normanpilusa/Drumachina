/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **                STMicroelectronics STM32F4xx Standard Peripherals Library
 **
 **  Distribution: The file is distributed “as is,” without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. Distribution of this file (unmodified or modified) is not
 **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
 **  rights to distribute the assembled, compiled & linked contents of this
 **  file as part of an application binary file, provided that it is built
 **  using the Atollic TrueSTUDIO(R) toolchain.
 **
 **
 *****************************************************************************
 */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* Private variables */
const uint16_t GPIO_PB[7] = { GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_11, GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15 };
const uint16_t GPIO_Ldn[7] = { GPIO_Pin_6, GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_11, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15 };

/* Private function prototypes -----------------------------------------------*/
void Timer_Configuration(void);
void NVIC_Configuration(void);
void delay_ms(uint32_t milli);
void LEDInit(void);
void LEDOn(uint32_t ledn);
void LEDOff(uint32_t ledn);
void LEDToggle(uint32_t ledn);
void PBInit(void);
uint8_t PBGetState(uint32_t PBn);

/*******************************************************************************
 * TIM2_IRQHandler
 * @brief	This function handles TIM2 global interrupt request.
 * @param    None
 * @retval   None
 *******************************************************************************/
void TIM2_IRQHandler(void) {
	/* Check if interrupt has occured */
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		/* Clear interrupt pending bit */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		/* WHAT EVER YOU NEED TO DO IN THE INTERRUPT HANDLER GOES HERE */
		if (PBGetState(0) == 0) {
			//do nothing while it is pressed
			while (PBGetState(0) == 0)
				;
			LEDToggle(0);
		} else if (PBGetState(1) == 0) {
			//do nothing while it is pressed
			while (PBGetState(1) == 0)
				;
			LEDToggle(1);
		} else if (PBGetState(2) == 0) {
			//do nothing while it is pressed
			while (PBGetState(2) == 0)
				;
			LEDToggle(2);
		} else if (PBGetState(3) == 0) {
			//do nothing while it is pressed
			while (PBGetState(3) == 0)
				;
			LEDToggle(3);
		} else if (PBGetState(4) == 0) {
			//do nothing while it is pressed
			while (PBGetState(4) == 0)
				;
			LEDToggle(4);
		} else if (PBGetState(5) == 0) {
			//do nothing while it is pressed
			while (PBGetState(5) == 0)
				;
			LEDToggle(5);
		} else if (PBGetState(6) == 0) {
			//do nothing while it is pressed
			while (PBGetState(6) == 0)
				;
			LEDToggle(6);
		}
		//switch debounce:
		uint32_t smalldelay = 17612;
		for (; smalldelay != 0; smalldelay--);
		//switch debounce (a small delay)
	}

}

/**
 * @brief  Main program.
 * @param  None
 * @retval Int
 */
int main(void) {


	/* NVIC configuration */
	NVIC_Configuration();

	/* Configure the LEDs and Buttons */
	PBInit();
	LEDInit();

	/* Timer Configuration */
	Timer_Configuration();

	/* Forever loop */
	for (;;) {
		/* DOES NOTHING HERE */
	}

	/* Program will never get here... */
	return 0;
}


/**
 * @brief  Configures the Nested Vectored interrupt controller.
 * @param  None
 * @retval None
 */
void NVIC_Configuration(void) {
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//Clock TIM2

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //set up the interrupt handler for TIM2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  Configures the Timers
 * @param  None
 * @retval None
 */
void Timer_Configuration(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

	/* Put your timer initialisation here */
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);

	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1; //TIM2 has a frequency of 1Hz
	TIM_TimeBaseInitStruct.TIM_Prescaler = 8400 - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	/* TIM interrupt enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

}

/*
 * Initialize LEDs, takes LED no. from 0 to 6
 */
void LEDInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;//GPIO_Ldn[ledn];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void LEDOn(uint32_t ledn) {
	GPIOC->BSRRL = GPIO_Ldn[ledn];
}

void LEDOff(uint32_t ledn) {
	GPIOC->BSRRH = GPIO_Ldn[ledn];
}

void LEDToggle(uint32_t ledn) {
	GPIOC->ODR ^= GPIO_Ldn[ledn];
}

/*
 * Initialize the puch buttons, takes button no. from 0 to 6
 */
void PBInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the BUTTON Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure Button pin as input */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;//GPIO_PB[PBn];
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*
 * State of a button, pressed or not. int 0 or 1
 */
uint8_t PBGetState(uint32_t PBn) {
	return GPIO_ReadInputDataBit(GPIOB, GPIO_PB[PBn]);
}

void delay_ms(uint32_t milli) {
	uint32_t delay = milli * 17612;
	for (; delay != 0; delay--) {

	}
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size) {
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void) {
	/* TODO, implement your code here */
	return -1;
}
