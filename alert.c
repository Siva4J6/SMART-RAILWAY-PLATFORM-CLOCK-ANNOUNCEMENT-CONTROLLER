#include <LPC21xx.H>
#include"types.h"
#include"delay.h"
#include"compare.h"
#include"alert.h"

#define GREEN_LED (1<<24)

#define YELLOW_LED (1<<25)

#define RED_LED (1<<26)

#define BUZZER (1<<27)

void Alert_Init(void)
{
        IODIR1|=GREEN_LED|YELLOW_LED|RED_LED|BUZZER;

        IOSET1=GREEN_LED|YELLOW_LED|RED_LED|BUZZER;
}


void GreenLED_ON(void)
{
    IOCLR1=GREEN_LED;
}
void GreenLED_OFF(void)
{
    IOSET1=GREEN_LED;
}




void YellowLED_ON(void)
{
    IOCLR1=YELLOW_LED;
}
void YellowLED_OFF(void)
{
    IOSET1=YELLOW_LED;
}




void RedLED_ON(void)
{
    IOCLR1=RED_LED;
}
void RedLED_OFF(void)
{
    IOSET1=RED_LED;
}





void Buzzer_ON(void)
{
    IOCLR1=BUZZER;
}

void Buzzer_OFF(void)
{
    IOSET1=BUZZER;
}



void TrainAlert(u8 TrainIndex)
{
//u8 status;
     // status=GetTrainStatus(TrainIndex);
	  GreenLED_OFF();
	  YellowLED_OFF();
	  RedLED_OFF();
	  Buzzer_OFF();

   if(TrainIndex==TRAIN_APPROACHING)
   {
   YellowLED_ON();

   Buzzer_OFF();

   delay_ms(5000);
   Buzzer_ON();
   YellowLED_OFF();
}


else if(TrainIndex==TRAIN_ONTIME)
{
   GreenLED_ON();
   delay_ms(5000);

   Buzzer_ON();
   GreenLED_OFF();
}



else if(TrainIndex==TRAIN_DELAYED)
{
     RedLED_ON();
	 delay_ms(5000);

	 Buzzer_ON();
	 RedLED_OFF();

}
else if(TrainIndex==TRAIN_DEPARTED)
{
     GreenLED_OFF();
	 YellowLED_OFF();
	 RedLED_OFF();

	 Buzzer_ON();

}
else
{
   GreenLED_OFF();
   YellowLED_OFF();
   RedLED_OFF();

   Buzzer_ON();
   }
}

   




































