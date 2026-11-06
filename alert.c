/*
 * alert.c
 *
 * Controls the status LEDs and buzzer connected to PORT1 (P1.24 - P1.27).
 * All outputs are ACTIVE LOW:
 *    IOCLR1 (drive pin low)  -> device ON
 *    IOSET1 (drive pin high) -> device OFF
 */
#include <LPC21xx.H>
#include"types.h"
#include"delay.h"
#include"compare.h"
#include"alert.h"

// Pin masks on PORT1
#define GREEN_LED (1<<24)   // P1.24 - train on time

#define YELLOW_LED (1<<25)  // P1.25 - train approaching

#define RED_LED (1<<26)     // P1.26 - train delayed

#define BUZZER (1<<27)      // P1.27 - buzzer

/*
 * Alert_Init
 * Configures the LED and buzzer pins as outputs and switches them all OFF
 * (pins driven high because the devices are active low).
 */
void Alert_Init(void)
{
        IODIR1|=GREEN_LED|YELLOW_LED|RED_LED|BUZZER;    // Set pins as outputs

        IOSET1=GREEN_LED|YELLOW_LED|RED_LED|BUZZER;     // All devices OFF
}

// ---- Green LED ----
void GreenLED_ON(void)
{
    IOCLR1=GREEN_LED;       // Low = ON
}
void GreenLED_OFF(void)
{
    IOSET1=GREEN_LED;       // High = OFF
}

// ---- Yellow LED ----
void YellowLED_ON(void)
{
    IOCLR1=YELLOW_LED;
}
void YellowLED_OFF(void)
{
    IOSET1=YELLOW_LED;
}

// ---- Red LED ----
void RedLED_ON(void)
{
    IOCLR1=RED_LED;
}
void RedLED_OFF(void)
{
    IOSET1=RED_LED;
}

// ---- Buzzer ----
void Buzzer_ON(void)
{
    IOCLR1=BUZZER;
}

void Buzzer_OFF(void)
{
    IOSET1=BUZZER;
}

/*
 * TrainAlert
 * ----------
 * Indicates the status of a train using the LEDs/buzzer.
 * Despite its name, the argument is a STATUS CODE (value returned by
 * GetTrainStatus(): TRAIN_APPROACHING, TRAIN_ONTIME, TRAIN_DELAYED,
 * TRAIN_DEPARTED, ...), not a train index.
 *
 *   APPROACHING -> yellow LED for 5 s
 *   ONTIME      -> green LED for 5 s
 *   DELAYED     -> red LED for 5 s
 *   DEPARTED/other -> all LEDs off
 * (the buzzer is switched on after the 5 s LED period / in the idle cases)
 */
void TrainAlert(u8 TrainIndex)
{
//u8 status;
     // status=GetTrainStatus(TrainIndex);

	  // Start from a clean state: everything OFF
	  GreenLED_OFF();
	  YellowLED_OFF();
	  RedLED_OFF();
	  Buzzer_OFF();

   if(TrainIndex==TRAIN_APPROACHING)
   {
   YellowLED_ON();          // Warn: train is about to arrive

   Buzzer_OFF();

   delay_ms(5000);          // Keep indication for 5 seconds
   Buzzer_ON();
   YellowLED_OFF();
}


else if(TrainIndex==TRAIN_ONTIME)
{
   GreenLED_ON();           // Train is on time / at platform
   delay_ms(5000);

   Buzzer_ON();
   GreenLED_OFF();
}



else if(TrainIndex==TRAIN_DELAYED)
{
     RedLED_ON();           // Train is delayed
	 delay_ms(5000);

	 Buzzer_ON();
	 RedLED_OFF();

}
else if(TrainIndex==TRAIN_DEPARTED)
{
     // Train has left: no LED indication
     GreenLED_OFF();
	 YellowLED_OFF();
	 RedLED_OFF();

	 Buzzer_ON();

}
else
{
   // Unknown / no train: no LED indication
   GreenLED_OFF();
   YellowLED_OFF();
   RedLED_OFF();

   Buzzer_ON();
   }
}
