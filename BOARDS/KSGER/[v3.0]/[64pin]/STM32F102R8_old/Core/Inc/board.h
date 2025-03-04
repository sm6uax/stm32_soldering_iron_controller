
#ifndef SETUP_H_
#define SETUP_H_
/*
 * Setup.h file
*/
// This is left here just to have it handy for copying when debugging a specific function
// Don't uncomment!!
//               __attribute__((optimize("O0")))
#define HWSTRING "HW:KSGER30F102"
/********************************
 * 			PWM Settings        *
 ********************************/
#define DELAY_TIMER			htim4			                    // Timer for the dead time
#define PWM_TIMER 			htim3			                    // PWM Timer
#define PWM_CHANNEL 		TIM_CHANNEL_1	                    // PWM Timer Channel
//#define PWM_CHxN							                    // Using CHxN Output type
#define PWM_CHx								                    // Using CHx Output type

/********************************
 * 			Display Settings    *
 ********************************/
#define OLED_SPI												// Hardware DMA SPI
//#define OLED_I2C												// Hardware DMA I2C
//#define OLED_SOFT_SPI											// Software bitbang SPI
//#define OLED_SOFT_I2C											// Software bitbang I2C
#define OLED_DEVICE			hspi2								// SPI / I2C handler if used
#define OLED_ADDRESS 		(0x3c<<1)						    // Only used for i2c
#define FILL_DMA			hdma_memtomem_dma1_channel2		    // DMA mem2mem for filling
#define USE_RST
#define USE_DC
//#define USE_CS

/********************************
 * 			ADC Settings        *
 ********************************/
#define ADC_DEVICE 			hadc1			                    // ADC device
#define ADC_MEASURE_TIME	100				                    // in uS
#define ADC_TRGO			ADC_EXTERNALTRIGCONV_T3_TRGO		// TRGO source for ADC trigger
#define ADC_BFSIZ 	        16	+2		                        // ADC DMA buffer size Buffer[ADC_BFSIZ][Adc_Buffer_Elements](+2 to compensate min/max value discard in filtering)

// Order for secondary measurements, ADC channels not requiring sampling in the PWM low period. Order as ADC rank order (usually ch0-ch18)
#define ADC_1st				NTC			                    	// ADC 1st used channel (CH1)
#define ADC_2nd				VIN				                    // ADC 2nd used channel (CH2)
//#define ADC_3rd			VREF			                    // ADC 2nd used channel (CH2)
#define ADC_AuxNum			2				                    // Number of secondary elements

// Channel assignment
#define ADC_CH_1ST			ADC_CHANNEL_5	                    //  CH5 = NTC
#define ADC_CH_2ND			ADC_CHANNEL_8	                    //  CH8 = VIN
//#define ADC_CH_3RD		ADC_CHANNEL_						//  NO VREF
#define ADC_TIP				ADC_CHANNEL_9	                    //  CH9 = IRON TIP (Sampled independently)

// To enable specific functions in code
//#define USE_VREF
#define USE_VIN
#define USE_NTC
/********************************
 * 			Buzzer				*
 ********************************/
#define BUZZER_OFF 			HAL_GPIO_WritePin(BUZ0_GPIO_Port, BUZ0_Pin, GPIO_PIN_SET);\
							HAL_GPIO_WritePin(BUZ1_GPIO_Port, BUZ1_Pin, GPIO_PIN_SET);

#define BUZZER_ON 			HAL_GPIO_WritePin(BUZ0_GPIO_Port, BUZ0_Pin, GPIO_PIN_RESET);\
							HAL_GPIO_WritePin(BUZ1_GPIO_Port, BUZ1_Pin, GPIO_PIN_RESET);

#define BUZZER_TOGGLE 		HAL_GPIO_TogglePin(BUZ0_GPIO_Port, BUZ0_Pin);\
							HAL_GPIO_TogglePin(BUZ1_GPIO_Port, BUZ1_Pin);

/********************************
 * 			Misc		*
 ********************************/
#define HIWDG				hiwdg							// iwdg used
#define HCRC				hcrc							// crc used
#define FLASH_SZ			64								// Flash Size (KB)
//#define NOSAVESETTINGS									// Don't use flash to save or load settings. Always use defaults (for debugging purposes)


/********************************
 * 			NTC TABLE			*
 ********************************/
/*
	Table of ADC sum value, corresponding to temperature. Starting from higher value to lower.
	Next parameters had been used to build table:
	R1: 4K7 pullup to 3.3V
	R/T characteristics table used: EPCOS R/T:7003; B25/100:3625K
	In the temperature range from -20°C to 125°C the error caused by the usage of a table is 0.135°C

	This must be adjusted if the board uses different circuit

	Source: http://www.sebulli.com/ntc/index.php
*/
#ifdef USE_NTC
#define NTC_TABLE 	NTC_Table[257] = {																				\
					4485, 3742, 2999, 2637, 2406, 2239, 2110, 2006, 1919, 1845, 1780, 1722, 1671, 1625, 1582, 1544,	\
					1508, 1475, 1444, 1415, 1387, 1362, 1337, 1314, 1292, 1272, 1252, 1232, 1214, 1197, 1180, 1163, \
					1148, 1132, 1118, 1104, 1090, 1076, 1063, 1051, 1039, 1027, 1015, 1004, 993, 982, 971, 961,		\
					951, 941, 931, 922, 912, 903, 894, 886, 877, 868, 860, 852, 844, 836, 828, 820,					\
					813, 805, 798, 791, 784, 777, 770, 763, 756, 749, 743, 736, 730, 723, 717, 711,					\
					704, 698, 692, 686, 680, 674, 668, 663, 657, 651, 646, 640, 634, 629, 623, 618,					\
					613, 607, 602, 597, 592, 586, 581, 576, 571, 566, 561, 556, 551, 546, 541, 536,					\
					531, 526, 522, 517, 512, 507, 503, 498, 493, 488, 484, 479, 475, 470, 465, 461,					\
					456, 452, 447, 443, 438, 434, 429, 425, 420, 416, 411, 407, 402, 398, 393, 389,					\
					384, 380, 376, 371, 367, 362, 358, 354, 349, 345, 340, 336, 331, 327, 323, 318,					\
					314, 309, 305, 300, 296, 291, 287, 282, 278, 273, 269, 264, 260, 255, 251, 246,					\
					241, 237, 232, 228, 223, 218, 213, 209, 204, 199, 194, 189, 185, 180, 175, 170,					\
					165, 160, 155, 150, 144, 139, 134, 129, 123, 118, 113, 107, 101, 96, 90, 85,					\
					79, 73, 67, 61, 55, 49, 42, 36, 30, 23, 16, 10, 3, -4, -11, -19,								\
  	  	  	  		-26, -34, -41, -49, -57, -66, -74, -83, -92, -102, -111, -121, -132, -142, -154, -165,			\
					-177, -190, -204, -218, -233, -249, -267, -286, -307, -330, -356, -385, -421, -465, -524, -617, -710 }

#endif

// To stop peripherals when debugging
#define DebugOpts()			__HAL_DBGMCU_FREEZE_IWDG();\
							__HAL_DBGMCU_FREEZE_TIM3();\
							__HAL_DBGMCU_FREEZE_TIM4()

#endif
