#include "sys.h"


uint8_t OperateMode = 0; //运行模式标志位



uint8_t MUSEICE=0;
uint8_t TESTING=0;
//修正时间
uint8_t IndexFlag3=1;//选项索引
uint8_t CursorFlag3=1;//光标索引
uint8_t InterFace=0;

//定时模式需要的标志位
//锁住位置
uint8_t Lock=0;
//设置哪一个时间
uint8_t WhatTime=1;
//标志位
uint8_t IndexFlag4=1;
//时间1
uint8_t Hour1=9;
uint8_t Min1=14;

uint8_t State1=0;
uint8_t GoFlag1=0;
//时间2
uint8_t Hour2=11;
uint8_t Min2=15;

uint8_t State2=0;
uint8_t GoFlag2=0;
//时间3
uint8_t Hour3=13;
uint8_t Min3=16;

uint8_t State3=0;
uint8_t GoFlag3=0;
//时间4
uint8_t Hour4=15;
uint8_t Min4=17;

uint8_t State4=0;
uint8_t GoFlag4=0;
//时间5
uint8_t Hour5=17;
uint8_t Min5=18;

uint8_t State5=0;
uint8_t GoFlag5=0;
//计数来播报语音
uint8_t musicdelay=0;

/******************
功能：模式选择及控制界面
参数：无
返回值：无
******************/
void Mode_Decide(void)//模式判定
{
    Manual_Mode();

    //按键判定
	  //如果按键1按下页面不是在修正时间页面并且时间未锁 则切换下一个页面
    if (isKey1&&(InterFace==0)&&(Lock==0)) { //若按键1按下
        isKey1 = 0; //清除按键按下标志
        oled_Clear();
        OperateMode++;
    }
		
		
		//如果按键1按下页面是在修正页面 则返回数据显示页面
		if (isKey1&&(InterFace==1)) {
			     isKey1 = 0; //清除按键按下标志
          oled_Clear();
	        InterFace=0;
		}
		
		
  //如果按键1按下时 时间锁住 则解锁时间锁
		if(isKey1&&(Lock==1)){
			  oled_Clear();
        Lock=0;
        isKey1=0;			
		}

		
    //标志位限制
    if (OperateMode >= 2) {
        OperateMode = 0;
    }

    /**根据模式选择显示界面**/
    switch (OperateMode) {
    case 0:
        Inform_Show();//显示信息
        AutoContrl();//自动控制
        break;

    case 1:
        Timed_mode();//定时
        AutoContrl();//自动控制
        break;


    }
}

/******************
功能：显示界面
参数：无
返回值：无
******************/
void Inform_Show(void)


{
  
      if (isKey2&&(InterFace==0)) {
				 oled_Clear();
        InterFace=1;
        isKey2 = 0;
        }

				if (isKey2&&(InterFace==1)) {
		    IndexFlag3++;
		    isKey2 = 0;
		       }
				
				if(IndexFlag3==7){
				IndexFlag3=1;
				}
					 
			
								
				
				
				if(InterFace==0){

        //第一行  药品余量
        oled_ShowCHinese(16 * 0, 2 * 0, 22);
        oled_ShowCHinese(16 * 1, 2 * 0, 23);
				oled_ShowCHinese(16 * 2, 2 * 0, 24);
        oled_ShowCHinese(16 * 3, 2 * 0, 25);	
        oled_ShowString(16 * 4, 2 * 0, ":", 16);
        oled_ShowNum(16 * 5, 2 * 0, SensorData.Sensor1, 4, 16);
        oled_ShowString(16 * 7, 2 * 0, "g", 16);
			
					
					
			 //第二行 温度湿度
			  oled_ShowCHinese(16 * 0, 2 * 1, 6);
        oled_ShowCHinese(16 * 1, 2 * 1, 7);
        oled_ShowString(16 * 2, 2 * 1, ":", 16);
        oled_ShowNum(16 * 3, 2 * 1, SensorData.Sensor2, 2, 16);
					
        oled_ShowCHinese(16 * 4, 2 * 1, 8);
        oled_ShowCHinese(16 * 5, 2 * 1, 9);
        oled_ShowString(16 * 6, 2 * 1, ":", 16);
        oled_ShowNum(16 * 7, 2 * 1, SensorData.Sensor3, 2, 16);
					
					
					
				oled_ShowNum(16 * 0,2 * 2,MyRTC_Time[0],4,16);
				oled_ShowCHinese(16 * 2, 2 * 2, 45);
				
				oled_ShowNum(16 * 3,2 * 2,MyRTC_Time[1],2,16);
				oled_ShowCHinese(16 * 4, 2 * 2, 46);
				
			  oled_ShowNum(16 * 5,2 * 2,MyRTC_Time[2],2,16);
				oled_ShowCHinese(16 * 6, 2 * 2, 47);

				oled_ShowNum(16 * 1,2 * 3,MyRTC_Time[3],2,16);
				oled_ShowCHinese(16 * 2, 2 * 3, 48);
				
				oled_ShowNum(16 * 3,2 * 3,MyRTC_Time[4],2,16);
				oled_ShowCHinese(16 * 4, 2 * 3, 49);
				
			  oled_ShowNum(16 * 5,2 * 3,MyRTC_Time[5],2,16);
				oled_ShowCHinese(16 * 6, 2 * 3, 50); 
					
				}
				
				
			if(InterFace==1){
				
					if(isKey3){
				//年	
				 if(IndexFlag3==1){
				  MyRTC_Time[0]++;
				}
				 //月
				 if(IndexFlag3==2){
				 MyRTC_Time[1]++;
				}	
				 //日
				 if(IndexFlag3==3){
				 MyRTC_Time[2]++;
				}
       //时				 
				if(IndexFlag3==4){
				 MyRTC_Time[3]++;
				}	
				//分
				if(IndexFlag3==5){
				 MyRTC_Time[4]++;
				}	
				//秒	
				if(IndexFlag3==6){
				 MyRTC_Time[5]++;
				}
				
				isKey3=0;
				}
					
				
       
				if(isKey4){
				//年	
				 if(IndexFlag3==1){
				  MyRTC_Time[0]--;
				}
				 //月
				 if(IndexFlag3==2){
				 MyRTC_Time[1]--;
				}	
				 //日
				 if(IndexFlag3==3){
				 MyRTC_Time[2]--;
				}
       //时				 
				if(IndexFlag3==4){
				 MyRTC_Time[3]--;
				}	
				//分
				if(IndexFlag3==5){
				 MyRTC_Time[4]--;
				}	
				//秒	
				if(IndexFlag3==6){
				 MyRTC_Time[5]--;
				}
				
				isKey4=0;
				}
				
				
				//光标显示
			  //年	
				if(IndexFlag3==1)   oled_ShowString(16*0,2*1,"----",16);  
				else oled_ShowString(16*0,2*1,"    ",16);
				 //月
				if(IndexFlag3==2)   oled_ShowString(16*3,2*1,"--",16);  
				else oled_ShowString(16*3,2*1,"  ",16);
				 //日
				if(IndexFlag3==3)   oled_ShowString(16*5,2*1,"--",16);  
				else oled_ShowString(16*5,2*1,"  ",16);
       //时				 
			 if(IndexFlag3==4)    oled_ShowString(16*1,2*3,"--",16);  
				else oled_ShowString(16*1,2*3,"  ",16);
				//分
			 if(IndexFlag3==5)     oled_ShowString(16*3,2*3,"--",16);  
				else oled_ShowString(16*3,2*3,"  ",16);
				//秒	
		   if(IndexFlag3==6)     oled_ShowString(16*5,2*3,"--",16);  
				else oled_ShowString(16*5,2*3,"  ",16);
				
				
					oled_ShowNum(16 * 0,2 * 0,MyRTC_Time[0],4,16);
				oled_ShowCHinese(16 * 2, 2 * 0, 45);
				 //月
				oled_ShowNum(16 * 3,2 * 0,MyRTC_Time[1],2,16);
				oled_ShowCHinese(16 * 4, 2 * 0, 46);
			  //日
			  oled_ShowNum(16 * 5,2 * 0,MyRTC_Time[2],2,16);
				oled_ShowCHinese(16 * 6, 2 * 0, 47);
        //时	
				oled_ShowNum(16 * 1,2 * 2,MyRTC_Time[3],2,16);
				oled_ShowCHinese(16 * 2, 2 * 2, 48);
				//分
				oled_ShowNum(16 * 3,2 * 2,MyRTC_Time[4],2,16);
				oled_ShowCHinese(16 * 4, 2 * 2, 49);
					//秒	
			  oled_ShowNum(16 * 5,2 * 2,MyRTC_Time[5],2,16);
				oled_ShowCHinese(16 * 6, 2 * 2, 50); 
				
				}
				
				
				
				//年
			
	
    
    if(MyRTC_Time[1]>12) MyRTC_Time[1]=0;
    if(MyRTC_Time[2]>31) MyRTC_Time[2]=0;	
    if(MyRTC_Time[3]>23) MyRTC_Time[3]=0;
    if(MyRTC_Time[4]>59) MyRTC_Time[4]=0;
    if(MyRTC_Time[5]>59) MyRTC_Time[5]=0;			
		}
			





/******************
功能：自动控制
参数：无
返回值：无
******************/

void AutoContrl(void)
{

	if(State1==1){	
 
	  if((Hour1==MyRTC_Time[3])&&(Min1==MyRTC_Time[4])){
		    GoFlag1=1; 	  
		}else{
		    GoFlag1=0; 
		}
	}
	else{
	 GoFlag1=0; 
	}

	

  

	if(State2==1){	
 
	  if((Hour2==MyRTC_Time[3])&&(Min2==MyRTC_Time[4])){
		    GoFlag2=1; 	  
		}else{
		    GoFlag2=0; 
		}
	}	   
	else{
	 GoFlag2=0; 
	}


	
		if(State3==1){	
 
	  if((Hour3==MyRTC_Time[3])&&(Min3==MyRTC_Time[4])){
		    GoFlag3=1; 	  
		}else{
		    GoFlag3=0; 
		}
	}  
			else{
	 GoFlag3=0; 
	}

	
	
		if(State4==1){	
 
	  if((Hour4==MyRTC_Time[3])&&(Min4==MyRTC_Time[4])){
		    GoFlag4=1; 	  
		}else{
		    GoFlag4=0; 
		}
	}  
			else{
	 GoFlag4=0; 
	}
	
	
		if(State5==1){	
 
	  if((Hour5==MyRTC_Time[3])&&(Min5==MyRTC_Time[4])){
		    GoFlag5=1; 	  
		}else{
		    GoFlag5=0; 
		}
	} 
		else{
	 GoFlag5=0; 
	}	
	
	
	if((GoFlag1==1||GoFlag2==1||GoFlag3==1||GoFlag4==1||GoFlag5==1)&&(SensorData.Sensor4==1)&&(TESTING==0)){
   		MUSEICE=1;
		 TESTING=1;
	}
		if(SensorData.Sensor4==0){
   		MUSEICE=0;
	}
    
	if((GoFlag1==0)&&(GoFlag2==0)&&(GoFlag3==0)&&(GoFlag4==0)&&(GoFlag5==0)){
	   TESTING=0;
	}
	


		if(SensorData.Sensor1<=0)  System.Execute1=1;
	   else  System.Execute1=0;
	

}

/******************
功能：定时模式
参数：无
返回值：无
******************/
void Timed_mode()
{
  oled_ShowCHinese(16*0,2*0,51); 
  oled_ShowCHinese(16*1,2*0,52);
  oled_ShowCHinese(16*2,2*0,53); 
  oled_ShowCHinese(16*3,2*0,54); 	
	oled_ShowNum(16*5,2*0,WhatTime,1,16);
	
	//没有锁定时
	//-------
  if(Lock==0){
		oled_ShowString(16*7,2*0,"*",16);
		//按键3按下设置的时间加
	   if(isKey3){
		    WhatTime++;
        isKey3=0;			 
		 }
				//按键4按下设置的时间减
	   if(isKey4){
		 WhatTime--;
		 isKey4=0;			 
		 }
   //按下按键2 确定设置的时间
		 if(isKey2){
		Lock=1;
		isKey2=0;
		}
		 
	  }else  oled_ShowString(16*7,2*0,"  ",16);
		//------
		


		
		
		//锁住时间时
		if(Lock==1){
			oled_ShowCHinese(16*1,2*1,48);
			oled_ShowCHinese(16*3,2*1,49);
//			oled_ShowCHinese(16*4,2*1,55);
//			oled_ShowCHinese(16*5,2*1,56);
			
			oled_ShowCHinese(16*0,2*3,57);
			oled_ShowCHinese(16*1,2*3,58);
			oled_ShowString(16*2,2*3,":",16);
			//按键2按下去选中
		 if(isKey2){
		 IndexFlag4++;
   	 isKey2=0;		 
		 }
	  //在标志位1 设置时
     if(IndexFlag4==1){
		 oled_ShowString(16*0,2*2,"--",16);
			 
		 if(isKey3){
			 
		 switch(WhatTime){
			   case 1:      Hour1++;
				 break;
			 
		 			 case 2:      Hour2++;
				 break;
			 
			 		 			 case 3:      Hour3++;
				 break;
			 
			 		 			 case 4:      Hour4++;
				 break;
			 
			 		 			 case 5:      Hour5++;
				 break;
		 }
		 
		 isKey3=0;
		 }
	 
			

    		 if(isKey4){
			 
		    switch(WhatTime){
			   case 1:      Hour1--;
				 break;
			 
		 			 case 2:      Hour2--;
				 break;
			 
			 		 			 case 3:      Hour3--;
				 break;
			 
			 		 			 case 4:      Hour4--;
				 break;
			 
			 		 			 case 5:      Hour5--;
				 break;
		 }
		 
		 isKey4=0;
		 }		 
			 
			 
		 }else  oled_ShowString(16*0,2*2,"  ",16);
     		 
			  //在标志位2 设置时
     if(IndexFlag4==2){
		 oled_ShowString(16*2,2*2,"--",16);
			 
		 if(isKey3){
			 
		 switch(WhatTime){
			   case 1:      Min1++;
				 break;
			 
		 			 case 2:      Min2++;
				 break;
			 
			 		 			 case 3:      Min3++;
				 break;
			 
			 		 			 case 4:      Min4++;
				 break;
			 
			 		 			 case 5:      Min5++;
				 break;
		 }
		 
		 isKey3=0;
		 }
	 
			

    		 if(isKey4){
			 
		    switch(WhatTime){
			   case 1:      Min1--;
				 break;
			 
		 			 case 2:      Min2--;
				 break;
			 
			 		 			 case 3:      Min3--;
				 break;
			 
			 		 			 case 4:      Min4--;
				 break;
			 
			 		 			 case 5:      Min5--;
				 break;
		 }
		 
		 isKey4=0;
		 }		 
			 
			 
		 }else  oled_ShowString(16*2,2*2,"  ",16);	
		 
		 
					  //在标志位3 设置时

		 
		 					  //在标志位4 设置时
     if(IndexFlag4==3){
		 oled_ShowString(16*7,2*3,"*",16);
			 
		 if(isKey3){
			 
		 switch(WhatTime){
			   case 1:      State1=!State1;
				 break;
			 
		 			 case 2:      State2=!State2;
				 break;
			 
			 		 			 case 3:      State3=!State3;
				 break;
			 
			 		 			 case 4:      State4=!State4;
				 break;
			 
			 		 			 case 5:      State5=!State5;
				 break;
		 }
		 
		 isKey3=0;
		 }
	 }else oled_ShowString(16*7,2*3,"  ",16);
		 
		 
		//显示不同的设置时间 
		 //1
		 if(WhatTime==1){
		 oled_ShowNum(16*0,2*1,Hour1,2,16);
		 oled_ShowNum(16*2,2*1,Min1,2,16);

		 if(State1==1){
		  oled_ShowCHinese(16*4,2*3,18);
			oled_ShowCHinese(16*5,2*3,19);
		 }else{
		  oled_ShowCHinese(16*4,2*3,20);
			oled_ShowCHinese(16*5,2*3,21);		 
		 }
		 }
		//2
		 if(WhatTime==2){
		 oled_ShowNum(16*0,2*1,Hour2,2,16);
		 oled_ShowNum(16*2,2*1,Min2,2,16);

		 if(State2==1){
		  oled_ShowCHinese(16*4,2*3,18);
			oled_ShowCHinese(16*5,2*3,19);
		 }else{
		  oled_ShowCHinese(16*4,2*3,20);
			oled_ShowCHinese(16*5,2*3,21);		 
		 }
		 }		 
		//3
		 if(WhatTime==3){
		 oled_ShowNum(16*0,2*1,Hour3,2,16);
		 oled_ShowNum(16*2,2*1,Min3,2,16);

		 if(State3==1){
		  oled_ShowCHinese(16*4,2*3,18);
			oled_ShowCHinese(16*5,2*3,19);
		 }else{
		  oled_ShowCHinese(16*4,2*3,20);
			oled_ShowCHinese(16*5,2*3,21);		 
		 }
		 }
//4
		 if(WhatTime==4){
		 oled_ShowNum(16*0,2*1,Hour4,2,16);
		 oled_ShowNum(16*2,2*1,Min4,2,16);
 
		 if(State4==1){
		  oled_ShowCHinese(16*4,2*3,18);
			oled_ShowCHinese(16*5,2*3,19);
		 }else{
		  oled_ShowCHinese(16*4,2*3,20);
			oled_ShowCHinese(16*5,2*3,21);		 
		 }
		 }
//5
		 if(WhatTime==5){
		 oled_ShowNum(16*0,2*1,Hour5,2,16);
		 oled_ShowNum(16*2,2*1,Min5,2,16);
//
		 if(State5==1){
		  oled_ShowCHinese(16*4,2*3,18);
			oled_ShowCHinese(16*5,2*3,19);
		 }else{
		  oled_ShowCHinese(16*4,2*3,20);
			oled_ShowCHinese(16*5,2*3,21);		 
		 }
		 }		 
		//---------
		}

		
		
		
			//限位
		if(WhatTime>=6){
		WhatTime=1;
		}
				if(WhatTime<1){
		WhatTime=1;
		}
		
		if(IndexFlag4==4){
	  IndexFlag4=1;
		}
		
		if(Hour1>24)      Hour1=0;
		if(Min1>59)       Min1=0;

		
		if(Hour2>24)      Hour2=0;
		if(Min2>59)       Min2=0;

		
		if(Hour3>24)      Hour3=0;
		if(Min3>59)       Min3=0;

		
		if(Hour4>24)      Hour4=0;
		if(Min4>59)       Min4=0;

		
		
		if(Hour5>24)      Hour5=0;
		if(Min5>59)       Min5=0;

}









void Manual_Contrl(void)
{
//  
}

void Voice_settings(void){

  
}




void ThresholdSet(void)
{
   
}
void Manual_Mode()
{
	
	
		if(InterFace==1) MyRTC_SetTime();
    else  MyRTC_ReadTime();//RTC读取时间，最新的时间存储到MyRTC_Time数组中 
	
    //蜂鸣器
    if (System.Execute1 == 1)   {
			  Execute2_ON;
        Execute3_ON;
    }   else  {
			   Execute2_OFF;
        Execute3_OFF;
    }
		
   if(MUSEICE==1){
   musi(); 
    }



		
}
void musi(){
musicdelay++;
if(musicdelay >  30){
musicdelay=0;
u3_printf("A7:00002");
}	


}

