//alert.c
#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"compare.h"
#include"alert.h"
// gpio pin definitions
#define GREEN_LED (1<<24)
#define YELLOW_LED (1<<25)
#define RED_LED (1<<26)
#define BUZZER (1<<27)

//ALERT INITIALIZATION
void Alert_Init(void)
{
  //IOSET1=GREEN_LED|YELLOW_LED|RED_LED|BUZZER;
  IODIR1|=GREEN_LED|YELLOW_LED|RED_LED|BUZZER;

  IOSET1=GREEN_LED|YELLOW_LED|RED_LED;
  
}

void GreenLED_ON(void)
{
  IOCLR1=GREEN_LED;
}
void GreenLED_OFF(void)
{
  IOSET1=GREEN_LED;
}
void YELLOWLED_ON(void)
{
 IOCLR1=YELLOW_LED;
}
void YELLOWLED_OFF(void)
{
   IOSET1=YELLOW_LED;
}
void REDLED_ON(void)
{
IOCLR1=RED_LED;
}
void REDLED_OFF(void)
{
IOSET1=RED_LED;
}
void BUZZER_ON(void)
{
   IOCLR1=BUZZER;
}
void BUZZER_OFF(void)
{
 IOSET1=BUZZER;
}
void TrainAlert(u8 TrainIndex)
{
   //u8 status;
   //status=GetTrainStatus(TrainIndex);

  GreenLED_OFF();
  YELLOWLED_OFF();
  REDLED_OFF();
  BUZZER_OFF();

  if(TrainIndex==TRAIN_APPROACHING)
  {
    YELLOWLED_ON();
	BUZZER_OFF();
	delay_ms(2000);
	BUZZER_ON();
  }
  else if(TrainIndex==TRAIN_ONTIME)
  {
     GreenLED_ON();
	 BUZZER_ON();
  }
  else if(TrainIndex==TRAIN_DELAYED)
  {
   	REDLED_ON();
	 BUZZER_ON();
  }
  else if(TrainIndex==TRAIN_DEPARTED)
  {
	GreenLED_OFF();
	YELLOWLED_OFF();
	REDLED_OFF();
	BUZZER_ON();
	}
   else
   {
   	GreenLED_OFF();
	YELLOWLED_OFF();
	REDLED_OFF();
	BUZZER_ON();
	}
	}
     
    



    

    


 
