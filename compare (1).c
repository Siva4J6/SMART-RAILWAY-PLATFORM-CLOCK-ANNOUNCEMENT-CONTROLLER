#include<lpc21xx.h>
#include"types.h"
#include"rtc1.h"
#include"train.h"
#include"compare.h"
extern TrainInfo TrainDB[TOTAL_TRAINS];

extern s32 hour;
extern s32 min;
u8 FindCurrentTrain(s32 hour,s32 min)
{
  u8 i;
  u8 found=0;
  u8 index=0;
  for(i=0;i<TOTAL_TRAINS;i++)
  {
    if((TrainDB[i].UpdDepHour>hour)||((TrainDB[i].UpdDepHour==hour)&&(TrainDB[i].UpdDepMin>=min)))
	{
	   if(found==0)
	   {
	    index=i;
		found=1;
		}
		else
		{
		  if((TrainDB[i].UpdDepHour<TrainDB[index].UpdDepHour)||((TrainDB[i].UpdDepHour==TrainDB[index].UpdDepHour)&&(TrainDB[i].UpdDepMin<TrainDB[index].UpdDepMin)))
		  {
		   index=i;
		   }
		   }
		   }
		   }
		   if(found)
		   {
		     return index;
			 }
			 index=0;
			 for(i=1;i<TOTAL_TRAINS;i++)
			 {
			   if((TrainDB[i].UpdDepHour<TrainDB[index].UpdDepHour)||((TrainDB[i].UpdDepHour==TrainDB[index].UpdDepHour)&&(TrainDB[i].UpdDepMin<TrainDB[index].UpdDepMin)))
			   {
			   index =i;
			   }
			   }
			   return index;
			   }
/*u8 GetTrainStatus(u8 index)
{
   if(TrainDB[index].Delay>0)
   {
     return TRAIN_DELAYED;
   }
  if((hour==TrainDB[index].UpdArrHour)&&(min<TrainDB[index].UpdDepMin))
  {
    return TRAIN_APPROACHING;
	}
	if((hour==TrainDB[index].UpdArrHour)&&(min>=TrainDB[index].UpdArrMin)&&(min<=TrainDB[index].UpdDepMin))
	{
	   return TRAIN_ONTIME;
	}
	if((hour>TrainDB[index].UpdDepHour)||((hour==TrainDB[index].UpdDepHour)&&(min>TrainDB[index].UpdDepMin)))
	{
	  return TRAIN_DEPARTED;
	}
	return TRAIN_NONE;
	} */
u8 GetTrainStatus(u8 index)
{
   s32 currentTime;
   s32 arrTime;
   s32 depTime;

   currentTime=(hour*60)+min;
   arrTime=(TrainDB[index].UpdArrHour*60)+TrainDB[index].UpdArrMin;
   depTime=(TrainDB[index].UpdDepHour*60)+TrainDB[index].UpdDepMin;
   if(TrainDB[index].Delay>0)
   {
    return TRAIN_DELAYED;
	}
	if(currentTime<arrTime)
	{
	  return TRAIN_APPROACHING;
	  }
	  if((currentTime>=arrTime)&&(currentTime<=depTime))
	  {
	    return TRAIN_ONTIME;
		}
	   if(currentTime>depTime)
	   {
	    return TRAIN_DEPARTED;
		}
		return TRAIN_NONE;
		}
		   


