#ifndef HEAD_FILE_DEFMACRO_H
#define HEAD_FILE_DEFMACRO_H

#define MAX_CH_NUM					2				//Channel Number
#define MAX_VOLTDIV_NUM				12				//Voltage Number

#define CAL_CHANNEL_MODEL			3				//Channel Model Number
#define CAL_VOLTDIV_NUM				24
#define CAL_CHANNEL_LEN				(96*CAL_CHANNEL_MODEL)
#define CAL_TRIGGER_LEN				(4*6)	
#define	CAL_DELAY_LEN				1
#define	CAL_EXT_TRIG_LEN			4
#define CAL_LEVEL_LEN				(CAL_CHANNEL_LEN+CAL_TRIGGER_LEN+CAL_DELAY_LEN+CAL_EXT_TRIG_LEN)

#define MAX_DATA					255				
#define MID_DATA					128	

#define CH1		0
#define CH2		1
#define CH3		2
#define CH4		3

//Data Length
#define BUF_10K_LEN					10240
#define BUF_40K_LEN					40960
#define BUF_1M_LEN					1048576

#define DEF_READ_DATA_LEN			BUF_10K_LEN			//The Default Length of Data Read from device
#define DEF_DRAW_DATA_LEN			10000				//The Default Length of Data show in Screen

//Couple Index Value
#define DC							0
#define AC							1

//Trigger Source
#define MAX_TRIGGER_SOURCE_NUM		(MAX_CH_NUM+2)		//CH1/CH2/EXT/(EXT/10)
#define MAX_ALT_TRIGGER_NUM			MAX_CH_NUM			//CH1/CH2
#define EXT							MAX_CH_NUM		
#define EXT10						(MAX_CH_NUM + 1)

//Trigger Couple
#define	TRIG_DC						0					//DC
#define	TRIG_AC						1					//A
#define MAX_TRIGCORR_NUM			3

//Trigger Mode
#define EDGE						0
#define	FORCE						6

//Trigger Sweep
#define TRIG_AUTO					0
#define TRIG_NORMAL					1
#define TRIG_SINGLE					2

//Insert Data
#define MAX_INSERT_TIMEDIV			8
#define MAX_DOUBLE_TIMEDIV			MAX_INSERT_TIMEDIV
#define MAX_SF_T_TIMEDIV			(MAX_INSERT_TIMEDIV - 4)

//color Def
#define CH1_COL 5
#define CH2_COL 4












#endif