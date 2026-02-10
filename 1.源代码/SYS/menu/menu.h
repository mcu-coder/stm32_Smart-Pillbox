#ifndef __MENU_H
#define __MENU_H
#include "sys.h"

extern uint8_t OperateMode;

extern uint8_t InterFace;




extern uint8_t IndexFlag1;//选项索引
extern uint8_t CursorFlag1;//光标索引



extern uint8_t IndexFlag3;//选项索引
extern uint8_t CursorFlag3;//光标索引


void Inform_Show(void) ;
void Inform_Show2(void) ;
void Mode_Decide(void);//模式判定
void AutoContrl(void);
void Manual_Contrl(void);
void ThresholdSet(void);
void ThresholdSet1(void);
void SeasonSet(void);
void Timed_mode(void);
void Manual_Mode(void);
void Voice_settings(void);
void musi(void);



extern uint8_t WhatTime;
extern uint8_t Lock;
extern uint8_t IndexFlag4;
//时间1
extern uint8_t Hour1;
extern uint8_t Min1;

extern uint8_t State1;
extern uint8_t GoFlag1;
//时间2
extern uint8_t Hour2;
extern uint8_t Min2;

extern uint8_t State2;
extern uint8_t GoFlag2;
//时间3
extern uint8_t Hour3;
extern  uint8_t Min3;

extern uint8_t State3;
extern uint8_t GoFlag3;
//时间4
extern uint8_t Hour4;
extern uint8_t Min4;

extern uint8_t State4;
extern uint8_t GoFlag4;
//时间5
extern uint8_t Hour5;
extern uint8_t Min5;

extern uint8_t State5;
extern uint8_t GoFlag5;

//void Threshold_Init(THRESHOLD *Threshold);
#endif

