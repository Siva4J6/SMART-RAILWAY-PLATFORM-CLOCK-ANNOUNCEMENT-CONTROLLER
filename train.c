/*
 * train.c
 * Train database. The admin module can modify the "Upd..." fields,
 * Platform and Delay at run time.
 */
#include <LPC21xx.H>
#include"types.h"
#include"train.h"

/*
 * Field order for each entry:
 * {TrainNo, TrainName, Destination,
 *  ArrHour, ArrMin, DepHour, DepMin,                  <- scheduled times
 *  UpdArrHour, UpdArrMin, UpdDepHour, UpdDepMin,      <- updated times
 *  Platform, Delay}
 *
 * 1) 12627 Karnataka Exp -> NewDelhi : arr 18:30, dep 18:35, platform 1, no delay
 * 2) 12028 Shatabdi Exp  -> Chennai  : arr 19:15, dep 19:20, platform 2, no delay
 * 3) 12785 Kacheguda Exp -> Hyderabad: scheduled arr 20:00, dep 20:05,
 *    updated to arr 20:20, dep 20:25, platform 3, delayed by 20 min
 */
TrainInfo TrainDB[TOTAL_TRAINS]={{12627,"Karnataka Exp","NewDelhi",18,30,18,35,18,30,18,35,1,0},{12028,"Shatabdi Exp","Chennai",19,15,19,20,19,15,19,20,2,0},{12785,"Kacheguda Exp","Hyderabad",20,00,20,05,20,20,20,25,3,20}};
