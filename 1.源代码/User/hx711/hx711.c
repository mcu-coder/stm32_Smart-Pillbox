#include "sys.h"


u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8  Flag_Error=0;


#define GapValue 550.5


void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //??PF????

	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				     //????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					     //?????????GPIOB
	
	//HX711_DOUT
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //????
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
  GPIO_SetBits(GPIOB,GPIO_Pin_14);					             //??????0
}

u32 HX711_Read(void)	
{
	unsigned long count; 
	unsigned char i; 
  HX711_DOUT=1; 
	delay_us(1);
  HX711_SCK=0; 
  count=0; 
  while(HX711_DOUT); 
  for(i=0;i<24;i++)
	{ 
	  HX711_SCK=1; 
	  count=count<<1; 
		delay_us(1);
		HX711_SCK=0; 
	  if(HX711_DOUT)
		count++; 
		delay_us(1);
	} 
 	HX711_SCK=1; 
  count=count^0x800000;
	delay_us(1);
	HX711_SCK=0;  
	return(count);
}

void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 


void Get_Weight(void)
{
	HX711_Buffer = HX711_Read();
	 
}


/******************************************************/
//   Init_HX711pin(); 
//	Get_Maopi();				  
//	delay_ms(1000);
//	delay_ms(1000);
//	Get_Maopi();	
//			 Get_Weight();  
//			oled_ShowCHinese(16*0,2*2,1);
//    oled_ShowCHinese(16*1,2*2,5);			
////		oled_ShowNum(16*2,2*2,Weight_Shiwu,5,16);
//		oled_ShowCHinese(16*6,2*2,10);	
