#include "sys.h"
//#include "usart3.h"
SENSOR SensorData;//传感器结构体定义
THRESHOLD Threshold;//阈值结构体定义
SYSTEM System;//系统标志位结构体定义

void Public(void);
void Threshold_Init(THRESHOLD *Threshold);

int main(void)
{
    delay_init();//延时函数初始化
	  MyRTC_Init();
		MyRTC_SetTime();

    NVIC_Config(); //中断优先级配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Usart3_Init(9600);
	 
    KEY_Init();//按键初始化
    Threshold_Init(&Threshold);//传感器阈值及执行器件开关变量初始化
    
    //
    oled_ShowCHinese(16 * 1, 2 * 0, 0);
    oled_ShowCHinese(16 * 2, 2 * 0, 1);
    oled_ShowCHinese(16 * 3, 2 * 0, 2);
    oled_ShowCHinese(16 * 4, 2 * 0, 3);
    oled_ShowCHinese(16 * 5, 2 * 0, 4);
    oled_ShowCHinese(16 * 6, 2 * 0, 5);
    Init_HX711pin();
    Get_Maopi();
    delay_ms(1000);
    delay_ms(1000);
 //   Get_Maopi();
    oled_Clear();
//    TIM2_Init(2000-1,7200-1);
    //    oled_ShowString(0,2,"Connecting...",16);
    /*******************************************/
    while (1) {
			

        KeyScan();//按键扫描
			  
        Get_Weight();
        SensorData.Sensor1 = Weight_Shiwu; //获取药品重量
			  SensorData.Sensor4 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
        Get_dht11();//获取温湿度数据
        Mode_Decide();//模式判定 （按键1选择模式）
        Public();
        delay_ms(50);

    }
}

//向MQTT服务器发布消息
void   Public(void)
{
	u1_printf("A:%d#,B:%d#,C:%d#,D:%d#,E:%d#,F:%d#,G:%d#,H:%d#,I:%d#,J:%d#,K:%d#,L:%d#,M:%d#,N:%d#",   
	           SensorData.Sensor1,
             SensorData.Sensor2,
             SensorData.Sensor3,
            WhatTime,
            Hour1,
            Min1,
            Hour2,
            Min2,           
            Hour3,
            Min3,       
            Hour4,
            Min4,         
            Hour5,
            Min5           );  


}


void Threshold_Init(THRESHOLD *Threshold)
{

}


