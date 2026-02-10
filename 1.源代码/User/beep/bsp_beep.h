#ifndef __BEEP_H
#define	__BEEP_H


#include "sys.h" 


/* 相关端口配置宏 */
#define Execute3_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define Execute3_GPIO_PORT    	GPIOA						/* GPIO端口 */
#define Execute3_GPIO_PIN		    GPIO_Pin_8					/* 连接到SCL时钟线的GPIO */








/* 定义控制IO的宏 */
#define Execute3_TOGGLE		    digitalToggle(Execute3_GPIO_PORT,Execute3_GPIO_PIN)
#define Execute3_ON		       digitalHi(Execute3_GPIO_PORT,Execute3_GPIO_PIN)
#define Execute3_OFF			   digitalLo(Execute3_GPIO_PORT,Execute3_GPIO_PIN)

void Beep_Init(void);
//void Beep_StateRefresh(uint8_t BeepState); 





#endif 
