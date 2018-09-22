//*****************************************************************************
//
//  oem_fan.c
//
//  Copyright (c) 2012-
//
//  Created on: 2012/11/21
//
//      Author: 
//
//*****************************************************************************

//*****************************************************************************
// Include all header file
#include "..\include.h"
//
//*****************************************************************************

//REJERRY055:start modify fan table 09/19.  //REJERRY072:start modify fan table 10/09.
//XITING0068:S remove UMA table Reduce EC stack usage
/*
const thermal ThermalTalbe1CPU[]= //UMA  
{
    {0,	34,	0,	0,	&Fan1On_Step1,	&Fan1Off_Step1,	&Fan1RPM_Step1	},	// Level 0 	
    {1,	43,	29,	19,	&Fan1On_Step2,	&Fan1Off_Step2,	&Fan1RPM_Step2	},	// Level 1  //REJERRY078:modify fan speed.	
    {2,	56,	38,	22,	&Fan1On_Step3,	&Fan1Off_Step3,	&Fan1RPM_Step3	},	// Level 2 	
    {3,	64,	51,	25,	&Fan1On_Step4,	&Fan1Off_Step4,	&Fan1RPM_Step4	},	// Level 3 	
    {4,	70,	60,	31,	&Fan1On_Step5,	&Fan1Off_Step5,	&Fan1RPM_Step5	},	// Level 4  
    {5, 70,	67,	34,	&Fan1On_Step6,	&Fan1Off_Step6,	&Fan1RPM_Step6	},	// Level 5  
    {6, 85,	80,	38,	&Fan1On_Step7,	&Fan1Off_Step7,	&Fan1RPM_Step7	},	// Level 6 
    {7, 85,	80,	38,	&Fan1On_Step8,	&Fan1Off_Step8,	&Fan1RPM_Step8	},	// Level 7
    {8, 85,	80,	38,	&Fan1On_Step9,	&Fan1Off_Step9,	&Fan1RPM_Step9	},	// Level 8			//XITING0068:add update Y530 1060 SDV fan table_0628
};
*/
//XITING0068:E

//XITING0070:S update Y530 1060 SDV fan table_0704-2
//XITING0068:S update Y530 1060 SDV fan table_0628
//XITING0019:S update fan table by 0404
//XITING0043:S update fan table by 0324
//XITING0040:S update fan table by 0321
//XITING0014:S modify table by fantable_0123
//XITING0009:S+ update fan table first version  fan speed = spec speed+100
const thermal ThermalTalbe1CPU_DIS[]= //DIS 			//CPU temp - Y530 1060 - board ID-01
{
    {0,	49,	0,	0,	&Fan1On_Step1,	&Fan1Off_Step1,	&Fan1RPM_Step1	},	// Level 0 	
    {1,	59,	44,	20,	&Fan1On_Step2,	&Fan1Off_Step2,	&Fan1RPM_Step2	},	// Level 1  //REJERRY078:modify fan speed.	
    {2,	64,	55,	23,	&Fan1On_Step3,	&Fan1Off_Step3,	&Fan1RPM_Step3	},	// Level 2 //HEGANG008:modify fan speed.	//HEGANG0009:Modify fan table follow'DY520 SIT fan table_0419'.	
    {3,	69,	60,	25,	&Fan1On_Step4,	&Fan1Off_Step4,	&Fan1RPM_Step4	},	// Level 3 	
    {4,	74,	65,	28,	&Fan1On_Step5,	&Fan1Off_Step5,	&Fan1RPM_Step5	},	// Level 4  
    {5, 79,	70,	32,	&Fan1On_Step6,	&Fan1Off_Step6,	&Fan1RPM_Step6	},	// Level 5   //HEGANG0010:Modify fan table follow'DY520 SIT fan table_0420'.
    {6, 84,	75,	35,	&Fan1On_Step7,	&Fan1Off_Step7,	&Fan1RPM_Step7	},	// Level 6 
    {7, 89, 80,	37,	&Fan1On_Step8,	&Fan1Off_Step8,	&Fan1RPM_Step8	},	// Level 7
    {8, 99, 85,	38,	&Fan1On_Step9,	&Fan1Off_Step9,	&Fan1RPM_Step9	},	// Level 8
};

const thermal ThermalTalbe1CPU_Sensor[]= 				//CPU銆�sensor temp - Y530 1060 - board ID-01
{
    {0,	49,	0,	0,	&Fan1OnCPU_Step1,	&Fan1OffCPU_Step1,	&Fan1RPMCPU_Step1	},	// Level 0 	
    {1,	59,	44,	20,	&Fan1OnCPU_Step2,	&Fan1OffCPU_Step2,	&Fan1RPMCPU_Step2	},	// Level 1  
    {2,	63,	55,	23,	&Fan1OnCPU_Step3,	&Fan1OffCPU_Step3,	&Fan1RPMCPU_Step3	},	// Level 2 
    {3,	67,	60,	25,	&Fan1OnCPU_Step4,	&Fan1OffCPU_Step4,	&Fan1RPMCPU_Step4	},	// Level 3 	
    {4,	71,	64,	28,	&Fan1OnCPU_Step5,	&Fan1OffCPU_Step5,	&Fan1RPMCPU_Step5	},	// Level 4  
    {5, 76, 68,	32,	&Fan1OnCPU_Step6,	&Fan1OffCPU_Step6,	&Fan1RPMCPU_Step6	},	// Level 5 
    {6, 81,	72,	35,	&Fan1OnCPU_Step7,	&Fan1OffCPU_Step7,	&Fan1RPMCPU_Step7	},	// Level 6 
    {7, 86, 77,	37,	&Fan1OnCPU_Step8,	&Fan1OffCPU_Step8,	&Fan1RPMCPU_Step8	},	// Level 7 
    {8, 99, 82,	38,	&Fan1OnCPU_Step9,	&Fan1OffCPU_Step9,	&Fan1RPMCPU_Step9	},	// Level 8 
};

const thermal ThermalTalbe1VGA[]= 						//GPU temp - Y530 1060 - board ID-01
{
    {0,	69,	0,	0,	&Fan1OnVGA_Step1,	&Fan1OffVGA_Step1,	&Fan1RPMVGA_Step1	},	// Level 0 	
    {1,	69,	65,	20,	&Fan1OnVGA_Step2,	&Fan1OffVGA_Step2,	&Fan1RPMVGA_Step2	},	// Level 1 	
    {2,	69,	65,	23,	&Fan1OnVGA_Step3,	&Fan1OffVGA_Step3,	&Fan1RPMVGA_Step3	},	// Level 2 	
    {3,	69,	65,	25,	&Fan1OnVGA_Step4,	&Fan1OffVGA_Step4,	&Fan1RPMVGA_Step4	},	// Level 3 	
    {4,	69,	65,	28,	&Fan1OnVGA_Step5,	&Fan1OffVGA_Step5,	&Fan1RPMVGA_Step5	},	// Level 4  
    {5, 69,	65,	32,	&Fan1OnVGA_Step6,	&Fan1OffVGA_Step6,	&Fan1RPMVGA_Step6	},	// Level 5  
    {6, 74,	65,	35,	&Fan1OnVGA_Step7,	&Fan1OffVGA_Step7,	&Fan1RPMVGA_Step7	},	// Level 6 
    {7, 82, 70,	37,	&Fan1OnVGA_Step8,	&Fan1OffVGA_Step8,	&Fan1RPMVGA_Step8	},	// Level 7 
    {8, 99, 78,	38,	&Fan1OnVGA_Step9,	&Fan1OffVGA_Step9,	&Fan1RPMVGA_Step9	},	// Level 8
};
//XITING0009:E+
//XITING0014:E
//XITING0040:E
//XITING0043:E
//XITING0019:E
//XITING0068:E
//XITING0070:E

//-----------------------------------------------------------------------------
// Fan table 2
//-----------------------------------------------------------------------------
//XITING0068:S remove UMA table Reduce EC stack usage
/*
const thermal ThermalTalbe2CPU[]=  //UMA
{
	{0,	34,	0,	0,	&Fan2On_Step1,	&Fan2Off_Step1,	&Fan2RPM_Step1	},	// Level 0 	
    {1,	43,	29,	16,	&Fan2On_Step2,	&Fan2Off_Step2,	&Fan2RPM_Step2	},	// Level 1  //REJERRY078:modify fan speed.
    {2,	56,	38,	19,	&Fan2On_Step3,	&Fan2Off_Step3,	&Fan2RPM_Step3	},	// Level 2 	
    {3,	64,	51,	22,	&Fan2On_Step4,	&Fan2Off_Step4,	&Fan2RPM_Step4	},	// Level 3 	
    {4,	70,	60,	28,	&Fan2On_Step5,	&Fan2Off_Step5,	&Fan2RPM_Step5	},	// Level 4  
    {5, 70,	67,	31,	&Fan2On_Step6,	&Fan2Off_Step6,	&Fan2RPM_Step6	},	// Level 5  
    {6, 85,	80,	35,	&Fan2On_Step7,	&Fan2Off_Step7,	&Fan2RPM_Step7	},	// Level 6  	
    {7, 85,	80,	35,	&Fan2On_Step8,	&Fan2Off_Step8,	&Fan2RPM_Step8	},	// Level 7
    {8, 85,	80,	35,	&Fan2On_Step9,	&Fan2Off_Step9,	&Fan2RPM_Step9	},	// Level 8 			//XITING0068:add update Y530 1060 SDV fan table_0628
};
*/
//XITING0068:E

//XITING0070:S update Y530 1060 SDV fan table_0704-2
//XITING0068:S update Y530 1060 SDV fan table_0628
//XITING0019:S update fan table by 0404
//XITING0043:S update fan table by 0324
//XITING0040:S update fan table by 0321
//XITING0014:S modify table by fantable_0123
//XITING0009:S+ update fan table first version		fan speed = spec speed+100
const thermal ThermalTalbe2CPU_DIS[]= //DIS 			//CPU temp - Y530 1060 - board ID-01
{
	{0,	49,	0,	0,	&Fan2On_Step1,	&Fan2Off_Step1,	&Fan2RPM_Step1	},	// Level 0 	
    {1,	59,	44,	17,	&Fan2On_Step2,	&Fan2Off_Step2,	&Fan2RPM_Step2	},	// Level 1  //REJERRY078:modify fan speed.
    {2,	64,	55,	20,	&Fan2On_Step3,	&Fan2Off_Step3,	&Fan2RPM_Step3	},	// Level 2  //HEGANG008:modify fan speed.//HEGANG0009:Modify fan table follow'DY520 SIT fan table_0419'.	
    {3,	69,	60,	22,	&Fan2On_Step4,	&Fan2Off_Step4,	&Fan2RPM_Step4	},	// Level 3 	
    {4,	74,	65,	25,	&Fan2On_Step5,	&Fan2Off_Step5,	&Fan2RPM_Step5	},	// Level 4  
    {5, 79,	70,	29,	&Fan2On_Step6,	&Fan2Off_Step6,	&Fan2RPM_Step6	},	// Level 5  
    {6, 84,	75,	32,	&Fan2On_Step7,	&Fan2Off_Step7,	&Fan2RPM_Step7	},	// Level 6  
    {7, 89,	80,	34,	&Fan2On_Step8,	&Fan2Off_Step8,	&Fan2RPM_Step8	},	// Level 7  
    {8, 99,	85,	40,	&Fan2On_Step9,	&Fan2Off_Step9,	&Fan2RPM_Step9	},	// Level 8 
};

const thermal ThermalTalbe2CPU_Sensor[]= 				//CPU sensor temp - Y530 1060 - board ID-01
{
	{0,	49,	0,	0,	&Fan2OnCPU_Step1,	&Fan2OffCPU_Step1,	&Fan2RPMCPU_Step1	},	// Level 0 	
    {1,	59,	44,	17,	&Fan2OnCPU_Step2,	&Fan2OffCPU_Step2,	&Fan2RPMCPU_Step2	},	// Level 1 
    {2,	63,	55,	20,	&Fan2OnCPU_Step3,	&Fan2OffCPU_Step3,	&Fan2RPMCPU_Step3	},	// Level 2 
    {3,	67,	60,	22,	&Fan2OnCPU_Step4,	&Fan2OffCPU_Step4,	&Fan2RPMCPU_Step4	},	// Level 3 	
    {4,	71,	64,	25,	&Fan2OnCPU_Step5,	&Fan2OffCPU_Step5,	&Fan2RPMCPU_Step5	},	// Level 4  
    {5, 76,	68,	29,	&Fan2OnCPU_Step6,	&Fan2OffCPU_Step6,	&Fan2RPMCPU_Step6	},	// Level 5  
    {6, 81,	72,	32,	&Fan2OnCPU_Step7,	&Fan2OffCPU_Step7,	&Fan2RPMCPU_Step7	},	// Level 6  
    {7, 86,	77,	34,	&Fan2OnCPU_Step8,	&Fan2OffCPU_Step8,	&Fan2RPMCPU_Step8	},	// Level 7  
    {8, 99,	82,	40,	&Fan2OnCPU_Step9,	&Fan2OffCPU_Step9,	&Fan2RPMCPU_Step9	},	// Level 8  
};


const thermal ThermalTalbe2VGA[]= 						//GPU temp - Y530 1060 - board ID-01
{
	{0,	69,	0,	0,	&Fan2OnVGA_Step1,	&Fan2OffVGA_Step1,	&Fan2RPMVGA_Step1	},	// Level 0 	
    {1,	69,	65,	17,	&Fan2OnVGA_Step2,	&Fan2OffVGA_Step2,	&Fan2RPMVGA_Step2	},	// Level 1 	
    {2,	69,	65,	20,	&Fan2OnVGA_Step3,	&Fan2OffVGA_Step3,	&Fan2RPMVGA_Step3	},	// Level 2 	
    {3,	69,	65,	22,	&Fan2OnVGA_Step4,	&Fan2OffVGA_Step4,	&Fan2RPMVGA_Step4	},	// Level 3 	
    {4,	69,	65,	25,	&Fan2OnVGA_Step5,	&Fan2OffVGA_Step5,	&Fan2RPMVGA_Step5	},	// Level 4  
    {5, 69,	65,	29,	&Fan2OnVGA_Step6,	&Fan2OffVGA_Step6,	&Fan2RPMVGA_Step6	},	// Level 5  
    {6, 74,	65,	32,	&Fan2OnVGA_Step7,	&Fan2OffVGA_Step7,	&Fan2RPMVGA_Step7	},	// Level 6  
    {7, 82,	70,	34,	&Fan2OnVGA_Step8,	&Fan2OffVGA_Step8,	&Fan2RPMVGA_Step8	},	// Level 7
    {8, 99,	78,	40,	&Fan2OnVGA_Step9,	&Fan2OffVGA_Step9,	&Fan2RPMVGA_Step9	},	// Level 8
};
//REJERRY055:end modify fan table.  //REJERRY072:end modify fan table.
//XITING0009:E+ 
//XITING0014:E
//XITING0040:E
//XITING0043:E
//XITING0019:E
//XITING0068:E
//XITING0070:E

//XITING0070:S add Y530P 1060 SIT fan table_0703
//XITING0068:S add Y530P 1060 SDV fan table_0627
//-----------------------------------------------------------------------------
// Fan table 1
//-----------------------------------------------------------------------------
const thermal ThermalTalbe1CPU_DIS_P[]= //DIS 				//CPU temp - Y530P 1060 - board ID-02
{
    {0,	65,	0,	0,	&Fan1On_Step1,	&Fan1Off_Step1,	&Fan1RPM_Step1	},	// Level 0 	
    {1,	65,	61,	19,	&Fan1On_Step2,	&Fan1Off_Step2,	&Fan1RPM_Step2	},	// Level 1 
    {2,	65,	61,	21,	&Fan1On_Step3,	&Fan1Off_Step3,	&Fan1RPM_Step3	},	// Level 2	
    {3,	70,	61,	23,	&Fan1On_Step4,	&Fan1Off_Step4,	&Fan1RPM_Step4	},	// Level 3 	
    {4,	74,	66,	27,	&Fan1On_Step5,	&Fan1Off_Step5,	&Fan1RPM_Step5	},	// Level 4  
    {5, 78,	71,	31,	&Fan1On_Step6,	&Fan1Off_Step6,	&Fan1RPM_Step6	},	// Level 5 
    {6, 82,	75,	33,	&Fan1On_Step7,	&Fan1Off_Step7,	&Fan1RPM_Step7	},	// Level 6 
    {7, 88, 79,	36,	&Fan1On_Step8,	&Fan1Off_Step8,	&Fan1RPM_Step8	},	// Level 7
    {8, 99, 83,	40,	&Fan1On_Step9,	&Fan1Off_Step9,	&Fan1RPM_Step9	},	// Level 8
};

const thermal ThermalTalbe1CPU_Sensor_P[]= 					//CPU銆�sensor temp - Y530P 1060 - board ID-02
{
    {0,	49,	0,	0,	&Fan1OnCPU_Step1,	&Fan1OffCPU_Step1,	&Fan1RPMCPU_Step1	},	// Level 0 	
    {1,	54,	45,	19,	&Fan1OnCPU_Step2,	&Fan1OffCPU_Step2,	&Fan1RPMCPU_Step2	},	// Level 1  
    {2,	58,	50,	21,	&Fan1OnCPU_Step3,	&Fan1OffCPU_Step3,	&Fan1RPMCPU_Step3	},	// Level 2 
    {3,	62,	55,	23,	&Fan1OnCPU_Step4,	&Fan1OffCPU_Step4,	&Fan1RPMCPU_Step4	},	// Level 3 	
    {4,	66,	59,	27,	&Fan1OnCPU_Step5,	&Fan1OffCPU_Step5,	&Fan1RPMCPU_Step5	},	// Level 4  
    {5, 70, 63,	31,	&Fan1OnCPU_Step6,	&Fan1OffCPU_Step6,	&Fan1RPMCPU_Step6	},	// Level 5 
    {6, 75,	67,	33,	&Fan1OnCPU_Step7,	&Fan1OffCPU_Step7,	&Fan1RPMCPU_Step7	},	// Level 6 
    {7, 80, 71,	36,	&Fan1OnCPU_Step8,	&Fan1OffCPU_Step8,	&Fan1RPMCPU_Step8	},	// Level 7 
    {8, 99, 76,	40,	&Fan1OnCPU_Step9,	&Fan1OffCPU_Step9,	&Fan1RPMCPU_Step9	},	// Level 8 
};

const thermal ThermalTalbe1VGA_P[]= 						//GPU temp - Y530P 1060 - board ID-02
{
    {0,	60,	0,	0,	&Fan1OnVGA_Step1,	&Fan1OffVGA_Step1,	&Fan1RPMVGA_Step1	},	// Level 0 	
    {1,	60,	55,	19,	&Fan1OnVGA_Step2,	&Fan1OffVGA_Step2,	&Fan1RPMVGA_Step2	},	// Level 1 	
    {2,	60,	55,	21,	&Fan1OnVGA_Step3,	&Fan1OffVGA_Step3,	&Fan1RPMVGA_Step3	},	// Level 2 	
    {3,	65,	55,	23,	&Fan1OnVGA_Step4,	&Fan1OffVGA_Step4,	&Fan1RPMVGA_Step4	},	// Level 3 	
    {4,	69,	61,	27,	&Fan1OnVGA_Step5,	&Fan1OffVGA_Step5,	&Fan1RPMVGA_Step5	},	// Level 4  
    {5, 73,	66,	31,	&Fan1OnVGA_Step6,	&Fan1OffVGA_Step6,	&Fan1RPMVGA_Step6	},	// Level 5  
    {6, 77,	70,	33,	&Fan1OnVGA_Step7,	&Fan1OffVGA_Step7,	&Fan1RPMVGA_Step7	},	// Level 6 
    {7, 85, 74,	36,	&Fan1OnVGA_Step8,	&Fan1OffVGA_Step8,	&Fan1RPMVGA_Step8	},	// Level 7 
    {8, 99, 81,	40,	&Fan1OnVGA_Step9,	&Fan1OffVGA_Step9,	&Fan1RPMVGA_Step9	},	// Level 8
};
//-----------------------------------------------------------------------------
// Fan table 2
//-----------------------------------------------------------------------------
const thermal ThermalTalbe2CPU_DIS_P[]= //DIS 			//CPU temp - Y530 1060 - board ID-02
{
	{0,	65,	0,	0,	&Fan2On_Step1,	&Fan2Off_Step1,	&Fan2RPM_Step1	},	// Level 0 	
    {1,	65,	61,	24,	&Fan2On_Step2,	&Fan2Off_Step2,	&Fan2RPM_Step2	},	// Level 1 
    {2,	65,	61,	26,	&Fan2On_Step3,	&Fan2Off_Step3,	&Fan2RPM_Step3	},	// Level 2
    {3,	70,	61,	29,	&Fan2On_Step4,	&Fan2Off_Step4,	&Fan2RPM_Step4	},	// Level 3 	
    {4,	74,	66,	33,	&Fan2On_Step5,	&Fan2Off_Step5,	&Fan2RPM_Step5	},	// Level 4  
    {5, 78,	71,	36,	&Fan2On_Step6,	&Fan2Off_Step6,	&Fan2RPM_Step6	},	// Level 5  
    {6, 82,	75,	39,	&Fan2On_Step7,	&Fan2Off_Step7,	&Fan2RPM_Step7	},	// Level 6  
    {7, 88,	79,	42,	&Fan2On_Step8,	&Fan2Off_Step8,	&Fan2RPM_Step8	},	// Level 7  
    {8, 99,	83,	49,	&Fan2On_Step9,	&Fan2Off_Step9,	&Fan2RPM_Step9	},	// Level 8 
};

const thermal ThermalTalbe2CPU_Sensor_P[]= 			//CPU sensor temp - Y530 1060 - board ID-02
{
	{0,	49,	0,	0,	&Fan2OnCPU_Step1,	&Fan2OffCPU_Step1,	&Fan2RPMCPU_Step1	},	// Level 0 	
    {1,	54,	45,	24,	&Fan2OnCPU_Step2,	&Fan2OffCPU_Step2,	&Fan2RPMCPU_Step2	},	// Level 1 
    {2,	58,	50,	26,	&Fan2OnCPU_Step3,	&Fan2OffCPU_Step3,	&Fan2RPMCPU_Step3	},	// Level 2 
    {3,	62,	55,	29,	&Fan2OnCPU_Step4,	&Fan2OffCPU_Step4,	&Fan2RPMCPU_Step4	},	// Level 3 	
    {4,	66,	59,	33,	&Fan2OnCPU_Step5,	&Fan2OffCPU_Step5,	&Fan2RPMCPU_Step5	},	// Level 4  
    {5, 70,	63,	36,	&Fan2OnCPU_Step6,	&Fan2OffCPU_Step6,	&Fan2RPMCPU_Step6	},	// Level 5  
    {6, 75,	67,	39,	&Fan2OnCPU_Step7,	&Fan2OffCPU_Step7,	&Fan2RPMCPU_Step7	},	// Level 6  
    {7, 80,	71,	42,	&Fan2OnCPU_Step8,	&Fan2OffCPU_Step8,	&Fan2RPMCPU_Step8	},	// Level 7  
    {8, 99,	76,	49,	&Fan2OnCPU_Step9,	&Fan2OffCPU_Step9,	&Fan2RPMCPU_Step9	},	// Level 8  
};


const thermal ThermalTalbe2VGA_P[]= 						//GPU temp - Y530 1060 - board ID-02
{
	{0,	60,	0,	0,	&Fan2OnVGA_Step1,	&Fan2OffVGA_Step1,	&Fan2RPMVGA_Step1	},	// Level 0 	
    {1,	60,	55,	24,	&Fan2OnVGA_Step2,	&Fan2OffVGA_Step2,	&Fan2RPMVGA_Step2	},	// Level 1 	
    {2,	60,	55,	26,	&Fan2OnVGA_Step3,	&Fan2OffVGA_Step3,	&Fan2RPMVGA_Step3	},	// Level 2 	
    {3,	65,	55,	29,	&Fan2OnVGA_Step4,	&Fan2OffVGA_Step4,	&Fan2RPMVGA_Step4	},	// Level 3 	
    {4,	69,	61,	33,	&Fan2OnVGA_Step5,	&Fan2OffVGA_Step5,	&Fan2RPMVGA_Step5	},	// Level 4  
    {5, 73,	66,	36,	&Fan2OnVGA_Step6,	&Fan2OffVGA_Step6,	&Fan2RPMVGA_Step6	},	// Level 5  
    {6, 77,	70,	39,	&Fan2OnVGA_Step7,	&Fan2OffVGA_Step7,	&Fan2RPMVGA_Step7	},	// Level 6  
    {7, 85,	74,	42,	&Fan2OnVGA_Step8,	&Fan2OffVGA_Step8,	&Fan2RPMVGA_Step8	},	// Level 7
    {8, 99,	81,	49,	&Fan2OnVGA_Step9,	&Fan2OffVGA_Step9,	&Fan2RPMVGA_Step9	},	// Level 8
};
//XITING0068:E
//XITING0070:E


//REJERRY096:Update fan table "DY512 SIT fan table_1129-取消布织布-1".
//HEGANG003:Modify fan table follow'DY520 SIT fan table_0329'.
//HEGANG004:update HEGANG003.
//MARTINH146:Add start
//-----------------------------------------------------------------------------
// Check Fan RPM count used.
//-----------------------------------------------------------------------------
void Check_FANRPM_Count(BYTE *BRPM_Cnt, BYTE TempType)
{
	if ( *BRPM_Cnt >= Fan_RPM_Cnt )	// Read 500ms*8 times: 4S
	{
		if ( TempType == TEMP_TYPE_FAN1RPM )
		{ 
			Fan1RPM = Fan1RPMTemp; 
		}	
		else if( TempType == TEMP_TYPE_FAN2RPM ) 
		{ 
			Fan2RPM = Fan2RPMTemp;
		}	

		*BRPM_Cnt = 0;
	}
	else
	{ 
		(*BRPM_Cnt)++; 
	}
}
//MARTINH146:Add end

//-----------------------------------------------------------------------------
// The function of check fan rpm 1  //martin0624A:change this function to meet 2 thermal table 1 fan.
//-----------------------------------------------------------------------------	
void CheckFanRPM1(void)
{
	BYTE FanLevel_tcpu = FanLevelCPU;	
	BYTE FanLevel_tvga = FanLevelVGA;
	BYTE FanLevel_tcpu_sensor = Fan1LevelCPU_Sensor;		//XITING0068:add
	//BYTE Fan1RPM_t = Fan1RPM;

	if((Debugtemperature1==0x00)&&(Debugtemperature2==0x00))
	{
		//temperature1 = TCPU_temp;//JERRYCR067: -Modify FAN control and fan table for SIV test.
		temperature1 = TEMP_Buff_3;//JERRYCR067:+ Modify FAN control and fan table for SIV test.
		temperature2 =  VGA_TBuff3;//JERRYCR067: +Modify FAN control and fan table for SIV test.
		//temperature2 = TVGA_temp;//JERRYCR067: -Modify FAN control and fan table for SIV test.

		temperature3 =  ThermistorCPU_TEMP;							//XITING0068:add  CPU sensor temp
	}
	else
	{
		temperature1 = Debugtemperature1;
		temperature2 = Debugtemperature2;
	}

	if((KeyBoardID == 0x01) || (KeyBoardID == 0x00))							//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		// check CPU fan table1:		
		if(FanLevel_tcpu <((sizeof(ThermalTalbe1CPU_DIS)/sizeof(thermal))-1))
		{
			if(temperature1> *ThermalTalbe1CPU_DIS[FanLevel_tcpu].FanOn)
			{
				FanLevel_tcpu += 1;
			}
		}
		
		if (FanLevel_tcpu>0)
		{
			if (temperature1< *ThermalTalbe1CPU_DIS[FanLevel_tcpu].FanOff)
			{			
				FanLevel_tcpu-=1;
			}
		}

		//XITING0068:S add CPU sensor temp check
		if(FanLevel_tcpu_sensor <((sizeof(ThermalTalbe1CPU_Sensor)/sizeof(thermal))-1))
		{
			if(temperature3> *ThermalTalbe1CPU_Sensor[FanLevel_tcpu_sensor].FanOn)
			{
				FanLevel_tcpu_sensor += 1;
			}
		}
		
		if (FanLevel_tcpu_sensor>0)
		{
			if (temperature3< *ThermalTalbe1CPU_Sensor[FanLevel_tcpu_sensor].FanOff)
			{			
				FanLevel_tcpu_sensor-=1;
			}
		}
		//XITING0068:E

	
		// check VGA fan table1:
		if(FanLevel_tvga <((sizeof(ThermalTalbe1VGA)/sizeof(thermal))-1))
		{
			if(temperature2> *ThermalTalbe1VGA[FanLevel_tvga].FanOn)
			{
				FanLevel_tvga += 1;
			}
		}
		
		if (FanLevel_tvga>0)
		{
			if (temperature2< *ThermalTalbe1VGA[FanLevel_tvga].FanOff)
			{			
				FanLevel_tvga-=1;
			}
		}
	}
	else if(KeyBoardID == 0x02)								//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		// check CPU fan table1:		
		if(FanLevel_tcpu <((sizeof(ThermalTalbe1CPU_DIS_P)/sizeof(thermal))-1))
		{
			if(temperature1> *ThermalTalbe1CPU_DIS_P[FanLevel_tcpu].FanOn)
			{
				FanLevel_tcpu += 1;
			}
		}
		
		if (FanLevel_tcpu>0)
		{
			if (temperature1< *ThermalTalbe1CPU_DIS_P[FanLevel_tcpu].FanOff)
			{			
				FanLevel_tcpu-=1;
			}
		}
	
		//XITING0068:S add CPU sensor temp check
		if(FanLevel_tcpu_sensor <((sizeof(ThermalTalbe1CPU_Sensor_P)/sizeof(thermal))-1))
		{
			if(temperature3> *ThermalTalbe1CPU_Sensor_P[FanLevel_tcpu_sensor].FanOn)
			{
				FanLevel_tcpu_sensor += 1;
			}
		}
		
		if (FanLevel_tcpu_sensor>0)
		{
			if (temperature3< *ThermalTalbe1CPU_Sensor_P[FanLevel_tcpu_sensor].FanOff)
			{			
				FanLevel_tcpu_sensor-=1;
			}
		}
		//XITING0068:E
	
		
		// check VGA fan table1:
		if(FanLevel_tvga <((sizeof(ThermalTalbe1VGA_P)/sizeof(thermal))-1))
		{
			if(temperature2> *ThermalTalbe1VGA_P[FanLevel_tvga].FanOn)
			{
				FanLevel_tvga += 1;
			}
		}
		
		if (FanLevel_tvga>0)
		{
			if (temperature2< *ThermalTalbe1VGA_P[FanLevel_tvga].FanOff)
			{			
				FanLevel_tvga-=1;
			}
		}
	}
	

	
	FanLevelCPU = FanLevel_tcpu;	
	FanLevelVGA = FanLevel_tvga;	
	Fan1LevelCPU_Sensor = FanLevel_tcpu_sensor;				//XITING0068:add

	if((KeyBoardID == 0x01) || (KeyBoardID == 0x00))					//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{	
		if((*ThermalTalbe1CPU_DIS[FanLevel_tcpu].RPM)>(*ThermalTalbe1VGA[FanLevel_tvga].RPM))
		{
			Fan1RPMTemp =*ThermalTalbe1CPU_DIS[FanLevel_tcpu].RPM;  //MARTINH146:Change 'Fan1RPM' to 'Fan1RPMTemp'
		}
		else
		{
			Fan1RPMTemp =*ThermalTalbe1VGA[FanLevel_tvga].RPM;  //MARTINH146:Change 'Fan1RPM' to 'Fan1RPMTemp'
		}

		if((*ThermalTalbe1CPU_Sensor[FanLevel_tcpu_sensor].RPM) > Fan1RPMTemp)		//XITING0068:S check CPU sensor fan1RPM faster than fan Fan1RPMTemp
		{
			Fan1RPMTemp = *ThermalTalbe1CPU_Sensor[FanLevel_tcpu_sensor].RPM;
		}
	}
	else if(KeyBoardID == 0x02)				//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		if((*ThermalTalbe1CPU_DIS_P[FanLevel_tcpu].RPM)>(*ThermalTalbe1VGA_P[FanLevel_tvga].RPM))
		{
			Fan1RPMTemp =*ThermalTalbe1CPU_DIS_P[FanLevel_tcpu].RPM;  //MARTINH146:Change 'Fan1RPM' to 'Fan1RPMTemp'
		}
		else
		{
			Fan1RPMTemp =*ThermalTalbe1VGA_P[FanLevel_tvga].RPM;  //MARTINH146:Change 'Fan1RPM' to 'Fan1RPMTemp'
		}

		if((*ThermalTalbe1CPU_Sensor_P[FanLevel_tcpu_sensor].RPM) > Fan1RPMTemp)		//XITING0068:S check CPU sensor fan1RPM faster than fan Fan1RPMTemp
		{
			Fan1RPMTemp = *ThermalTalbe1CPU_Sensor_P[FanLevel_tcpu_sensor].RPM;
		}
	}
	   
	//MARTINH146:Change:Add start
	//if(Fan1RPMTemp != Fan1RPM)  //MARTINH150:Remove
	if(Fan1RPMTemp == Fan1RPMBackUp)  //MARTINH150:Add
	{    
		Check_FANRPM_Count(&Fan1RPMCount,TEMP_TYPE_FAN1RPM);
	}	
	else
	{
		Fan1RPMBackUp = Fan1RPMTemp;  //MARTINH150:Add
		Fan1RPMCount = 0x00;
	}	
//MARTINH146:Change:Add end	
}

//-----------------------------------------------------------------------------
// The function of check fan rpm 2   //martin0624A:change this function to meet 2 thermal table 1 fan.
//-----------------------------------------------------------------------------
void CheckFanRPM2(void)
{
	BYTE FanLevel_tcpu = FanLevel2CPU;
	BYTE FanLevel_tvga = FanLevel2VGA;
	BYTE FanLevel_tcpu_sensor = Fan2LevelCPU_Sensor;		//XITING0068:add
	//BYTE Fan1RPM_t = Fan2RPM;

	if((Debugtemperature1==0x00)&&(Debugtemperature2==0x00))
	{
		//temperature1 = TCPU_temp;//JERRYCR067:- Modify FAN control and fan table for SIV test.
		//temperature2 = TVGA_temp;//JERRYCR067:- Modify FAN control and fan table for SIV test.
		temperature1 = TEMP_Buff_3;//JERRYCR067:+ Modify FAN control and fan table for SIV test.
		temperature2 =  VGA_TBuff3;//JERRYCR067: +Modify FAN control and fan table for SIV test.

		temperature3 =  ThermistorCPU_TEMP;							//XITING0068:add
	}
	else
	{
		temperature1 = Debugtemperature1;
		temperature2 = Debugtemperature2;
	}

	if((KeyBoardID == 0x01) || (KeyBoardID == 0x00))							//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		// check CPU fan table2:		
		if(FanLevel_tcpu <((sizeof(ThermalTalbe2CPU_DIS)/sizeof(thermal))-1))
		{
			if(temperature1> *ThermalTalbe2CPU_DIS[FanLevel_tcpu].FanOn)
			{
				FanLevel_tcpu+= 1;
			}
		}
		
		if (FanLevel_tcpu>0)
		{
			if (temperature1< *ThermalTalbe2CPU_DIS[FanLevel_tcpu].FanOff)
			{			
				FanLevel_tcpu-=1;
			}
		}

		//XITING0068:S add CPU sensor temp check
		if(FanLevel_tcpu_sensor <((sizeof(ThermalTalbe2CPU_Sensor)/sizeof(thermal))-1))
		{
			if(temperature3> *ThermalTalbe2CPU_Sensor[FanLevel_tcpu_sensor].FanOn)
			{
				FanLevel_tcpu_sensor += 1;
			}
		}
		
		if (FanLevel_tcpu_sensor>0)
		{
			if (temperature3< *ThermalTalbe2CPU_Sensor[FanLevel_tcpu_sensor].FanOff)
			{			
				FanLevel_tcpu_sensor-=1;
			}
		}
		//XITING0068:E

	
		// check VGA fan table2:
		if(FanLevel_tvga <((sizeof(ThermalTalbe2VGA)/sizeof(thermal))-1))
		{
			if(temperature2> *ThermalTalbe2VGA[FanLevel_tvga].FanOn)
			{
				FanLevel_tvga+= 1;
			}
		}
		
		if (FanLevel_tvga>0)
		{
			if (temperature2< *ThermalTalbe2VGA[FanLevel_tvga].FanOff)
			{			
				FanLevel_tvga-=1;
			}
		}
	}
	else if(KeyBoardID == 0x02)								//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		// check CPU fan table2:		
		if(FanLevel_tcpu <((sizeof(ThermalTalbe2CPU_DIS_P)/sizeof(thermal))-1))
		{
			if(temperature1> *ThermalTalbe2CPU_DIS_P[FanLevel_tcpu].FanOn)
			{
				FanLevel_tcpu+= 1;
			}
		}
	
		if (FanLevel_tcpu>0)
		{
			if (temperature1< *ThermalTalbe2CPU_DIS_P[FanLevel_tcpu].FanOff)
			{			
				FanLevel_tcpu-=1;
			}
		}

		//XITING0068:S add CPU sensor temp check
		if(FanLevel_tcpu_sensor <((sizeof(ThermalTalbe2CPU_Sensor_P)/sizeof(thermal))-1))
		{
			if(temperature3> *ThermalTalbe2CPU_Sensor_P[FanLevel_tcpu_sensor].FanOn)
			{
				FanLevel_tcpu_sensor += 1;
			}
		}
		
		if (FanLevel_tcpu_sensor>0)
		{
			if (temperature3< *ThermalTalbe2CPU_Sensor_P[FanLevel_tcpu_sensor].FanOff)
			{			
				FanLevel_tcpu_sensor-=1;
			}
		}
		//XITING0068:E
	
		// check VGA fan table2:
		if(FanLevel_tvga <((sizeof(ThermalTalbe2VGA_P)/sizeof(thermal))-1))
		{
			if(temperature2> *ThermalTalbe2VGA_P[FanLevel_tvga].FanOn)
			{
				FanLevel_tvga+= 1;
			}
		}
		
		if (FanLevel_tvga>0)
		{
			if (temperature2< *ThermalTalbe2VGA_P[FanLevel_tvga].FanOff)
			{			
				FanLevel_tvga-=1;
			}
		}
	}

	FanLevel2CPU = FanLevel_tcpu;	
	FanLevel2VGA= FanLevel_tvga;	
	Fan2LevelCPU_Sensor = FanLevel_tcpu_sensor;				//XITING0068:add

	if((KeyBoardID == 0x01) || (KeyBoardID == 0x00))					//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		if((*ThermalTalbe2CPU_DIS[FanLevel_tcpu].RPM)>(*ThermalTalbe2VGA[FanLevel_tvga].RPM))
		{
			Fan2RPMTemp =*ThermalTalbe2CPU_DIS[FanLevel_tcpu].RPM;    //MARTINH146:Change 'Fan2RPM' to 'Fan2RPMTemp'
		}
		else
		{
			Fan2RPMTemp =*ThermalTalbe2VGA[FanLevel_tvga].RPM;    //MARTINH146:Change 'Fan2RPM' to 'Fan2RPMTemp'
		}
		
		//XITING0068:S check CPU sensor fan1RPM faster than fan Fan1RPMTemp
		if((*ThermalTalbe2CPU_Sensor[FanLevel_tcpu_sensor].RPM) > Fan2RPMTemp)
		{
			Fan2RPMTemp = *ThermalTalbe2CPU_Sensor[FanLevel_tcpu_sensor].RPM;
		}
		//XITING0068:E
	}
	else if(KeyBoardID == 0x02)								//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		if((*ThermalTalbe2CPU_DIS_P[FanLevel_tcpu].RPM)>(*ThermalTalbe2VGA_P[FanLevel_tvga].RPM))
		{
			Fan2RPMTemp =*ThermalTalbe2CPU_DIS_P[FanLevel_tcpu].RPM;    //MARTINH146:Change 'Fan2RPM' to 'Fan2RPMTemp'
		}
		else
		{
			Fan2RPMTemp =*ThermalTalbe2VGA_P[FanLevel_tvga].RPM;    //MARTINH146:Change 'Fan2RPM' to 'Fan2RPMTemp'
		}
		
		//XITING0068:S check CPU sensor fan1RPM faster than fan Fan1RPMTemp
		if((*ThermalTalbe2CPU_Sensor_P[FanLevel_tcpu_sensor].RPM) > Fan2RPMTemp)
		{
			Fan2RPMTemp = *ThermalTalbe2CPU_Sensor_P[FanLevel_tcpu_sensor].RPM;
		}
		//XITING0068:E
	}

	//MARTINH146:Change:Add start
	//if(Fan2RPMTemp != Fan2RPM)  //MARTINH150:Remove
	if(Fan2RPMTemp == Fan2RPMBackUp)  //MARTINH150:Add
	{
		Check_FANRPM_Count(&Fan2RPMCount,TEMP_TYPE_FAN2RPM); 
	}
	else
	{
		Fan2RPMBackUp = Fan2RPMTemp;  //MARTINH150:Add
		Fan2RPMCount = 0x00;
	}
	//MARTINH146:Change:Add end

}

void Fan1MainControl(void)
{
	if(((Fan1RPM*100)-RPMACC)>RPM1)
	{
		if(FanValue<FAN_PWM_Max)
			FanValue++;	
	}
	else if(((Fan1RPM*100)+RPMACC)<RPM1)
	{
		if(FanValue>0x00)
			FanValue--;	
	}
}
void Fan2MainControl(void)
{
	if(((Fan2RPM*100)-RPMACC)>RPM2)
	{
		if(Fan2Value<FAN_PWM_Max)
		Fan2Value++;	
	}
	else if(((Fan2RPM*100)+RPMACC)<RPM2)
	{
		if(Fan2Value>0x00)
		Fan2Value--;	
	}			
}

//-----------------------------------------------------------------------------
// The function of fan rpm control
//-----------------------------------------------------------------------------
void FanControl(void)
{
	if(	RPM1==0x0000)
	{
		FanValue = FanInitValue;
	}
	Fan1MainControl(); //MARTINH031:add
}

//MARTINH031:add start
//-----------------------------------------------------------------------------
// The function of fan rpm control
//-----------------------------------------------------------------------------
void Fan2Control(void)
{
	if(	RPM2==0x0000)
	{
		Fan2Value = Fan2InitValue; //REJERRY055:modify to fan2 start rpm.
	}
	Fan2MainControl(); 
}
//MARTINH031:add end

//-----------------------------------------------------------------------------
// Init. thermal table 1
//-----------------------------------------------------------------------------
void InitThermalTable1(void)
{
	if((KeyBoardID == 0x01) || (KeyBoardID == 0x00))				//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		BYTE index;
		index=0x00;
		//MARTINH079:add start	
		if(IS_MASK_CLEAR(pProject0,b4VGAType)) 
		{
		     while(index<(sizeof(ThermalTalbe1CPU_DIS)/sizeof(thermal)))
		    {
		    	*ThermalTalbe1CPU_DIS[index].FanOn=ThermalTalbe1CPU_DIS[index].CFanOn;
			    *ThermalTalbe1CPU_DIS[index].FanOff=ThermalTalbe1CPU_DIS[index].CFanOff;
			    *ThermalTalbe1CPU_DIS[index].RPM=ThermalTalbe1CPU_DIS[index].CRPM;
			    index++;
		    }
		}
		else
		//MARTINH079: add end		
		{
		    while(index<(sizeof(ThermalTalbe1CPU_DIS)/sizeof(thermal)))
		    {
		    	*ThermalTalbe1CPU_DIS[index].FanOn=ThermalTalbe1CPU_DIS[index].CFanOn;
			    *ThermalTalbe1CPU_DIS[index].FanOff=ThermalTalbe1CPU_DIS[index].CFanOff;
			    *ThermalTalbe1CPU_DIS[index].RPM=ThermalTalbe1CPU_DIS[index].CRPM;
			    index++;
		    }
		}

		//XITING0068:S add CPU sensor temp init
		index=0x00;
		while(index<(sizeof(ThermalTalbe1CPU_Sensor)/sizeof(thermal)))
		{
			 *ThermalTalbe1CPU_Sensor[index].FanOn=ThermalTalbe1CPU_Sensor[index].CFanOn;
			 *ThermalTalbe1CPU_Sensor[index].FanOff=ThermalTalbe1CPU_Sensor[index].CFanOff;
			 *ThermalTalbe1CPU_Sensor[index].RPM=ThermalTalbe1CPU_Sensor[index].CRPM;
			 index++;
		}
		//XITING0068:E

		//MARTINH031: add start 
	    index=0x00;
	    while(index<(sizeof(ThermalTalbe1VGA)/sizeof(thermal)))
	    {
		   *ThermalTalbe1VGA[index].FanOn=ThermalTalbe1VGA[index].CFanOn;
		   *ThermalTalbe1VGA[index].FanOff=ThermalTalbe1VGA[index].CFanOff;
		   *ThermalTalbe1VGA[index].RPM=ThermalTalbe1VGA[index].CRPM;
		   index++;
	    } 
		//MARTINH031: add end 
	}
	else if(KeyBoardID == 0x02)								//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		BYTE index;
		index=0x00;
		//MARTINH079:add start	
		if(IS_MASK_CLEAR(pProject0,b4VGAType)) 
		{
			 while(index<(sizeof(ThermalTalbe1CPU_DIS_P)/sizeof(thermal)))
			{
				*ThermalTalbe1CPU_DIS_P[index].FanOn=ThermalTalbe1CPU_DIS_P[index].CFanOn;
				*ThermalTalbe1CPU_DIS_P[index].FanOff=ThermalTalbe1CPU_DIS_P[index].CFanOff;
				*ThermalTalbe1CPU_DIS_P[index].RPM=ThermalTalbe1CPU_DIS_P[index].CRPM;
				index++;
			}
		}
		else
		//MARTINH079: add end		
		{
			while(index<(sizeof(ThermalTalbe1CPU_DIS_P)/sizeof(thermal)))
			{
				*ThermalTalbe1CPU_DIS_P[index].FanOn=ThermalTalbe1CPU_DIS_P[index].CFanOn;
				*ThermalTalbe1CPU_DIS_P[index].FanOff=ThermalTalbe1CPU_DIS_P[index].CFanOff;
				*ThermalTalbe1CPU_DIS_P[index].RPM=ThermalTalbe1CPU_DIS_P[index].CRPM;
				index++;
			}
		}

		//XITING0068:S add CPU sensor temp init
		index=0x00;
		while(index<(sizeof(ThermalTalbe1CPU_Sensor_P)/sizeof(thermal)))
		{
			 *ThermalTalbe1CPU_Sensor_P[index].FanOn=ThermalTalbe1CPU_Sensor_P[index].CFanOn;
			 *ThermalTalbe1CPU_Sensor_P[index].FanOff=ThermalTalbe1CPU_Sensor_P[index].CFanOff;
			 *ThermalTalbe1CPU_Sensor_P[index].RPM=ThermalTalbe1CPU_Sensor_P[index].CRPM;
			 index++;
		}
		//XITING0068:E

		//MARTINH031: add start 
		index=0x00;
		while(index<(sizeof(ThermalTalbe1VGA_P)/sizeof(thermal)))
		{
			 *ThermalTalbe1VGA_P[index].FanOn=ThermalTalbe1VGA_P[index].CFanOn;
			 *ThermalTalbe1VGA_P[index].FanOff=ThermalTalbe1VGA_P[index].CFanOff;
			 *ThermalTalbe1VGA_P[index].RPM=ThermalTalbe1VGA_P[index].CRPM;
			 index++;
		} 
		//MARTINH031: add end 
	}
}

//-----------------------------------------------------------------------------
// Init. thermal table 2
//-----------------------------------------------------------------------------
void InitThermalTable2(void)
{
	if((KeyBoardID == 0x01) || (KeyBoardID == 0x00))			//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		BYTE index;
		index=0x00;
		//MARTINH079:add start	
		if(IS_MASK_CLEAR(pProject0,b4VGAType)) 
		{
	    	while(index<(sizeof(ThermalTalbe2CPU_DIS)/sizeof(thermal)))
	    	{
	    		*ThermalTalbe2CPU_DIS[index].FanOn=ThermalTalbe2CPU_DIS[index].CFanOn;
		    	*ThermalTalbe2CPU_DIS[index].FanOff=ThermalTalbe2CPU_DIS[index].CFanOff;
		    	*ThermalTalbe2CPU_DIS[index].RPM=ThermalTalbe2CPU_DIS[index].CRPM;
		    	index++;
	    	}
		}
		else
		//MARTINH079: add end
		{
	    	while(index<(sizeof(ThermalTalbe2CPU_DIS)/sizeof(thermal)))
	    	{
	    		*ThermalTalbe2CPU_DIS[index].FanOn=ThermalTalbe2CPU_DIS[index].CFanOn;
		    	*ThermalTalbe2CPU_DIS[index].FanOff=ThermalTalbe2CPU_DIS[index].CFanOff;
		    	*ThermalTalbe2CPU_DIS[index].RPM=ThermalTalbe2CPU_DIS[index].CRPM;
		    	index++;
	    	}
		}	

		//XITING0068:S add CPU Sensor temp init
		index=0x00;
		while(index<(sizeof(ThermalTalbe2CPU_Sensor)/sizeof(thermal)))
		{
			*ThermalTalbe2CPU_Sensor[index].FanOn=ThermalTalbe2CPU_Sensor[index].CFanOn;
			*ThermalTalbe2CPU_Sensor[index].FanOff=ThermalTalbe2CPU_Sensor[index].CFanOff;
		 	*ThermalTalbe2CPU_Sensor[index].RPM=ThermalTalbe2CPU_Sensor[index].CRPM;
		 	index++;
		}
		//XITING0068:E

		//MARTINH031: add start 
	    index=0x00;
	    while(index<(sizeof(ThermalTalbe2VGA)/sizeof(thermal)))
	   	{
		   *ThermalTalbe2VGA[index].FanOn=ThermalTalbe2VGA[index].CFanOn;
		   *ThermalTalbe2VGA[index].FanOff=ThermalTalbe2VGA[index].CFanOff;
		   *ThermalTalbe2VGA[index].RPM=ThermalTalbe2VGA[index].CRPM;
		   index++;
	   	}
		//MARTINH031: add end 
	}
	else if(KeyBoardID == 0x02)						//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
	{
		BYTE index;
		index=0x00;
		//MARTINH079:add start	
		if(IS_MASK_CLEAR(pProject0,b4VGAType)) 
		{
	    	while(index<(sizeof(ThermalTalbe2CPU_DIS_P)/sizeof(thermal)))
	    	{
	    		*ThermalTalbe2CPU_DIS_P[index].FanOn=ThermalTalbe2CPU_DIS_P[index].CFanOn;
		    	*ThermalTalbe2CPU_DIS_P[index].FanOff=ThermalTalbe2CPU_DIS_P[index].CFanOff;
		    	*ThermalTalbe2CPU_DIS_P[index].RPM=ThermalTalbe2CPU_DIS_P[index].CRPM;
		    	index++;
	    	}
		}
		else
		//MARTINH079: add end
		{
	    	while(index<(sizeof(ThermalTalbe2CPU_DIS_P)/sizeof(thermal)))
	    	{
	    		*ThermalTalbe2CPU_DIS_P[index].FanOn=ThermalTalbe2CPU_DIS_P[index].CFanOn;
		    	*ThermalTalbe2CPU_DIS_P[index].FanOff=ThermalTalbe2CPU_DIS_P[index].CFanOff;
		    	*ThermalTalbe2CPU_DIS_P[index].RPM=ThermalTalbe2CPU_DIS_P[index].CRPM;
		    	index++;
	    	}
		}	

		//XITING0068:S add CPU Sensor temp init
		index=0x00;
		while(index<(sizeof(ThermalTalbe2CPU_Sensor_P)/sizeof(thermal)))
		{
			*ThermalTalbe2CPU_Sensor_P[index].FanOn=ThermalTalbe2CPU_Sensor_P[index].CFanOn;
			*ThermalTalbe2CPU_Sensor_P[index].FanOff=ThermalTalbe2CPU_Sensor_P[index].CFanOff;
		 	*ThermalTalbe2CPU_Sensor_P[index].RPM=ThermalTalbe2CPU_Sensor_P[index].CRPM;
		 	index++;
		}
		//XITING0068:E

		//MARTINH031: add start 
	    index=0x00;
	    while(index<(sizeof(ThermalTalbe2VGA_P)/sizeof(thermal)))
	   	{
		   *ThermalTalbe2VGA_P[index].FanOn=ThermalTalbe2VGA_P[index].CFanOn;
		   *ThermalTalbe2VGA_P[index].FanOff=ThermalTalbe2VGA_P[index].CFanOff;
		   *ThermalTalbe2VGA_P[index].RPM=ThermalTalbe2VGA_P[index].CRPM;
		   index++;
	   	}
		//MARTINH031: add end 
	}	
}

//-----------------------------------------------------------------------------
// Fan full off control
//-----------------------------------------------------------------------------
void FanFullOff(void)
{
	FanValue = 0x00;
}
//MARTINH031: add start
//-----------------------------------------------------------------------------
// Fan full off control
//-----------------------------------------------------------------------------
void Fan2FullOff(void)
{
	Fan2Value = 0x00;
}
//MARTINH031: add end
//-----------------------------------------------------------------------------
// The function of get fan RPM
//-----------------------------------------------------------------------------
void GetRPM1(void)
{
	BYTE tach_H;
	BYTE tach_L;

	tach_H = F1TMRR;
	tach_L = F1TLRR;
	if((tach_H!=0x00)||(tach_L!=0x00))
	{
		if(((tach_H*256) + tach_L)<RPM1Max)
		{
			RPM1=(3750000/TACH1P/((tach_H*256) + tach_L)); //MARTINH103:change '4312500' to '3750000'
		}
		else
		{
			RPM1=RPM1Max; 
		}
	}
	else
	{
		RPM1=0x0000;
	}
}

//MARTINH031:add start
//-----------------------------------------------------------------------------
// The function of get fan2 RPM
//-----------------------------------------------------------------------------
void GetRPM2(void)
{
	BYTE tach_H;
	BYTE tach_L;

	tach_H = F2TMRR;
	tach_L = F2TLRR;
	if((tach_H!=0x00)||(tach_L!=0x00))
	{
		if(((tach_H*256) + tach_L)<RPM2Max)
		{
			RPM2=(3750000/TACH1P/((tach_H*256) + tach_L));  //MARTINH103:change '4312500' to '3750000'
		}
		else
		{
			RPM2=RPM2Max; 
		}
	}
	else
	{
		RPM2=0x0000;
	}
}

//-----------------------------------------------------------------------------
// Fan Speed Control When Fan Table Not Ready
//-----------------------------------------------------------------------------
void FanSpeedConWhenFanTableNotReady(void)
{
	if(DebugFan1RPMT!=0x00)
	{         
		FAN_PWM_ALT;
		GetRPM1();
		if( RPM1==0x0000)
		{
			FanValue = FanInitValue;
		}
		else
		{
			if(((DebugFan1RPMT*100)-RPMACC)>RPM1)
			{
				if(FanValue<FAN_PWM_Max)
					FanValue++; 
			}
			else if(((DebugFan1RPMT*100)+RPMACC)<RPM1)
			{
				if(FanValue>0x00)
					FanValue--; 
			}
		}
	}

	if(DebugFan2RPMT!=0x00) 	
	{
		FAN2_PWM_ALT;//JERRYCR018:Add FAN2 control setting.
		GetRPM2();
		if( RPM2==0x0000)
		{
			Fan2Value = Fan2InitValue; //REJERRY055:modify to fan2 start rpm.
		}
		else
		{
			if(((DebugFan2RPMT*100)-RPMACC)>RPM2)
			{
				if(Fan2Value<FAN_PWM_Max)
					Fan2Value++; 
			}
			else if(((DebugFan2RPMT*100)+RPMACC)<RPM2)
			{
				if(Fan2Value>0x00)
					Fan2Value--; 
			}
		}
	}
}
//MARTINH031:add end

//-----------------------------------------------------------------------------
// The function of smart fan  //martin0624A:change this function to meet 2 fan control.
//-----------------------------------------------------------------------------
void FanManager(void)
{
	// Check VGA and CPU Temperature error bit and full on bit.
	if ( (IS_MASK_SET(ERR_THMSTS, b1VGATempEr)) ||  //MARTINH116:remove "b3PECITempEr of ERR_THMSTS"
		(IS_MASK_SET(Thro_Status2, b4FAN1_FullOn)) )
	{
		FAN_PWM = FAN2_PWM = Target_Duty = FAN_PWM_Max;	// Fan turn on max.//JERRYCR018:Add FAN2 control setting.
		return;
	}

	if ( Fan_ON_Count != 0 )					// Turn on Fan x sec.
	{
		Fan_ON_Count--;
		FAN_PWM = FAN2_PWM = Target_Duty = FAN_PWM_Min;	// PWM min. 30%//JERRYCR018:Add FAN2 control setting.
		return;
	}

	if( SystemNotS0 )	// Not S0 status.
	{
		FAN_PWM = FAN2_PWM = Target_Duty = 0;	// Turn off FAN.//JERRYCR018:Add FAN2 control setting.
		return;
	}

	if(FanFullOnCont!=0x00)
	{
		FanFullOnCont--;
		GetRPM1();
		GetRPM2();  //MARTINH031:add
		return;
	}

	if(DebugFan1RPMT==0x00) 			// In normal control mode
	{
		//if((Fan1RPM!=0x00)||(Fan2RPM!=0x00))  //MARTINH031:remove
		if(Fan1RPM!=0x00)  //MARTINH031:add
		{
			GetRPM1();
			FanControl();
		}
		else
		{
			if(FanValue != 0x00)
			{
				RPM1=0x0000;
				FanFullOff();
			}
		}
	}
	else											// In RPM debug mode
	{
		GetRPM1();
		if( RPM1==0x0000)
		{
			FanValue = FanInitValue;
		}
		else
		{
			if(((DebugFan1RPMT*100)-RPMACC)>RPM1)
			{
				if(FanValue<FAN_PWM_Max)
					FanValue++; 
			}
			else if(((DebugFan1RPMT*100)+RPMACC)<RPM1)
			{
				if(FanValue>0x00)
				FanValue--; 
			}
		}
	}
	//MARTINH031: add start
	if(DebugFan2RPMT==0x00) 			// In normal control mode
	{
		if(Fan2RPM!=0x00)
		{
			GetRPM2();
			Fan2Control();
		}
		else
		{
			if(Fan2Value != 0x00)
			{
				RPM2=0x0000;
				Fan2FullOff();
			}
		}
	}
	else											// In RPM debug mode
	{
		GetRPM2();
		if( RPM2==0x0000)
		{
			Fan2Value = Fan2InitValue; //REJERRY055:modify to fan2 start rpm.
		}
		else
		{
			if(((DebugFan2RPMT*100)-RPMACC)>RPM2)
			{
				if(Fan2Value<FAN_PWM_Max)
					Fan2Value++; 
			}
			else if(((DebugFan2RPMT*100)+RPMACC)<RPM2)
			{
				if(Fan2Value>0x00)
					Fan2Value--; 
			}
		}
	}
//MARTINH031: add end
}


//martin0616 add end

void Fan_Init(void)
{
	nFanStatus1 = Fan_Num;
	nFanStatus1 = (nFanStatus1 << 4) | Fan_Step;
	nOSThrottlingTemp = 97;
	nOSShutdownTemp = 100;
	nShutDownTemp = 100;
}

/*****************************************************************************/
// Procedure: PWM_TimeCount									TimeDiv: 50mSec
// Description: PWM Beep function.
// GPIO:
// Referrals: Service short time PWM output, base on 50ms.
/*****************************************************************************/
void PWM_TimeCount(void)
{
	//if (IS_MASK_CLEAR(cReserve07,uACInOutBeep))//A88:for beep can't disable when reboot
	if(uACInOutBeep==1)  //MARTINH110:change 0 to 1
	{
		if( PWM_LEDBeep_CNT == 0x00 )
		{
			BEEP_INIT;
			//BEEP_LOW;//W46
			PWM_BEEP = 0x00;
			return;
		}

		BEEP_ALT;
		PWM_LEDBeep_CNT--;		// decrease timer
		RamDebug(0xA6);//W085:suddenly beep one time
		// AC IN/OUT beep time
		if( PWM_LEDBeep_CNT == 0x00 )
		{
			BEEP_INIT;
			//PWM_BEEP = 0x00;
			//CLEAR_MASK(GPDRA,BIT(6)); //W46
			//BEEP_LOW;//W46
		}
	}
	else
	{
		PWM_LEDBeep_CNT = 0;
		BEEP_INIT;
		//PWM_BEEP = 0x00;
		//CLEAR_MASK(GPDRA,BIT(6));//W46
		//BEEP_LOW;//W46
		
	}
}

/*****************************************************************************/
// Procedure: ThmIC_Temperature								TimeDiv: 500mSec
// Description: Read RAM temperature
// GPIO:
// Referrals:
/*****************************************************************************/
void ThmIC_Temperature(void)
{
	BYTE BsData,BTmlCmd;

	if( SystemNotS0 || (PwrOnDly5Sec!=0) ) 
	{ return; }


	switch( TmlICStep & 0x07 )  //T034: change 0x03 to 0x07
	{
		case 0:
			BTmlCmd = VRAM_Temp; //Remote //BROOKEW040		//XITING0038: remote1 :GPU temp
			break;
		case 1:
			BTmlCmd = TmlIC_CPU_Temp;								//XITING0038: remote2 :CPU temp
			break;
		case 2:
			BTmlCmd =TmlIC_Temp; //Thermal IC				//XITING0038: dimm temp
			break;
		default:
			TmlICStep = 0;
			return;
	}

	if(!bRWSMBus(SMbusChD, SMbusRB, TmlIC_Addr, BTmlCmd, &BsData, 0)) //JERRYCR029:Add read thermal IC temperature. 
	{
		TMErrCnt++;
		if( IS_MASK_CLEAR(ERR_THMSTS, b0ThmICError) )// Check bit0 is Error.
		{
			if ( TMErrCnt > 7 )		// 3 Sec.
			{
				SET_MASK(ERR_THMSTS, b0ThmICError);	// Set bit0 Thermal IC read temperature error.
			}
		}
		else
		{
			if ( TMErrCnt > 68 )	// 30 Sec.
			{
				ProcessSID(THERMALCOMMFAIL_ID);	// 0x0B shutdown ID.//W114
				TMErrCnt = 0;					// Clear error count.
				#if !EN_PwrSeqTest 
				  #if !EN_ThermalSensorTest //MartinH009:add
				 ETWCFG=EWDKEYEN;			 // enable external WDT key
		    EWDKEYR=0xFF;			// external WDT reset	
		    while(1);						   // Wait for watch dog time-out
				  #endif
				#endif
			}
		}
		ResetSMBus(SMbusChD);//JERRYCR029:Add read thermal IC temperature.
	}
	else
	{
		switch( TmlICStep & 0x03 )
		{
			case 0:																				//XITING0038: remote1 :GPU temp
				//if ( IS_MASK_CLEAR(Fan_Debug_Temp,b4RemoteSensor_Temp) ) // Debug CPU Temperature, Engineer myself control. //MARTINH138:Add	//XITING0038: remove
				EXTVGA_TEMP = BsData;	// Save VRAM temperature.//BROOKEW040						//XITING0038: change to to Ram4 0xB5
				TMErrCnt = 00;		// Clear error count.
				CLEAR_MASK(ERR_THMSTS,b0ThmICError);	// Clear bit0.
				TmlICStep++;		// next step 1.
				break;
			case 1:		
				//XITING0038: remote2 :CPU temp
				ThermistorCPU_TEMP = BsData;	// Save VRAM temperature.//BROOKEW040			//XITING0038: change to to Ram4 0xB3
				TMErrCnt = 00;		// Clear error count.
				CLEAR_MASK(ERR_THMSTS,b0ThmICError);	// Clear bit0.
				TmlICStep++;		// next step 2.
				break;
			case 2:																				//XITING0038: dimm temp
				nVramTemp = BsData;	// Save RAM temperature.//BROOKEW040						//XITING0038: change to to Ram4 0x0E
				TMErrCnt = 00;		// Clear error count.
				CLEAR_MASK(ERR_THMSTS,b0ThmICError);	// Clear bit0.
				TmlICStep = 0;		// next step 0.
				break;
			default:
				break;
		}
	}
}

//martin0624 add start:
/*****************************************************************************/
// Procedure: VGA_Temperature								TimeDiv: 1Sec
// Description: Read VGA temperature(M/B)
// GPIO:  
// Referrals:
/*****************************************************************************/
void VGA_Temperature(void)
{
	BYTE INIT_GPU_REG2[4] = {0x0f, 0x00, 0x00, 0x8f};
	BYTE INIT_GPU_REG1[4] = {0x0f, 0x00, 0x00, 0x8e};
	BYTE INIT_GPU_REG0[4] = {0xc0, 0x30, 0x00, 0x14};

	if( SystemNotS0|| (PwrOnDly5Sec!=0) ) 
	{ 
		VGAErrCnt = 00; 	                    
		CLEAR_MASK(ERR_THMSTS,b1VGATempEr);   
		return; 
	}

	if((CPU_TYPE & 0xC0) == 0x00)
	{
		VGAErrCnt = 00;  	
		CLEAR_MASK(ERR_THMSTS,b1VGATempEr);
		VGA_TEMP = VGA_TBuff3 = VGA_TBuff2 = VGA_TBuff1 = 0x00;	
		return;
	}
	
	if((CPU_TYPE &0xc0)==0x80)	//NV GPU
	{
		//if(!bRWSMBus(SMbusChC, SMbusRB, VGA_Addr, 0x00, &sdAMDTH0, 0)) //REJERRY028:remove.
		if(!bRWSMBus(SMbusChD, SMbusRB, EXTVGA_Addr, 0x00, &sdAMDTH0, 0)) //REJERRY028:add.
		{
			VGAErrCnt++;
			if( IS_MASK_CLEAR(ERR_THMSTS, b1VGATempEr) )// Check bit1 is Error.
			{
				if ( VGAErrCnt > 7 )	//W003:change 35 to 7    //T076F:change 7 to 35  // 3 Sec.
				{
					SET_MASK(ERR_THMSTS, b1VGATempEr);	// Set bit1 Thermal IC read temperature error.
				}
			}
			else
			{
				if ( VGAErrCnt > 68 )	//W003:change 254 to 68;	//T076F: from 68 to 255	// 30 Sec.
				{
					SET_MASK(SysStatus,ERR_ShuntDownFlag);
					VGAErrCnt = 00;				// Clear error count.
#if !EN_ThermalSensorTest 
					ProcessSID(VGACOMMFAIL_ID);	// 0x20 shutdown ID.
					ETWCFG=EWDKEYEN;			 // enable external WDT key
					EWDKEYR=0xFF;			// external WDT reset	
					while(1);						   // Wait for watch dog time-out
#endif 
				}
			}
			ResetSMBus(SMbusChD);
		}
		else
		{
			VGAErrCnt = 00;		// Clear error count.
			CLEAR_MASK(ERR_THMSTS,b1VGATempEr);	// Clear bit1,bit5.

			if ( IS_MASK_CLEAR(Fan_Debug_Temp,b1VGA_Temp) )	// Debug VGA Temperature, Engineer myself control.
			{
				if((sdAMDTH0&0x80)==0x80)//
				{
					return;
				}  
				else
				{
					VGA_TEMP = sdAMDTH0;   //W037C+
					VGA_TBuff3 = VGA_TBuff2;
					VGA_TBuff2 = VGA_TBuff1;
					VGA_TBuff1 = VGA_TEMP;
					VGA_TBuff3 = (VGA_TBuff1 + VGA_TBuff2 + VGA_TBuff3)/3;		// VGA average temperature.
					TVGA_temp =  VGA_TBuff3; //
				}
			}
		}
	}
	if((CPU_TYPE &0xc0)==0x40) //AMD GPU
	{
		if(!bWSMBusBlock(SMbusChD, SMbusWBK, VGA_Addr, 0x01,( BYTE* )&INIT_GPU_REG1,4,0))//load GPU register offset to SMB_ADDR
		{
			VGAErrCnt++;
		}
		if(!bWSMBusBlock(SMbusChD, SMbusWBK, VGA_Addr, 0x02,( BYTE* )&INIT_GPU_REG0,4,0))//sent data to be written into the DGPU rgister
		{
			VGAErrCnt++;
		}

		if(!bWSMBusBlock(SMbusChD, SMbusWBK, VGA_Addr, 0x01,( BYTE* )&INIT_GPU_REG2,4,0))//load GPU register offset to SMB_ADDR
		{
			VGAErrCnt++;
		}

		if(!bRSMBusBlock(SMbusChD, SMbusRBK, VGA_Addr, 0x03, &sdAMDTH0))//read data from GPU REGISTER
		{
			VGAErrCnt++;
			if( IS_MASK_CLEAR(ERR_THMSTS, b1VGATempEr) )// Check bit1 is Error.
			{
				if ( VGAErrCnt > 35 )	//T076F:change 7 to 35  // 3 Sec.
				{
					SET_MASK(ERR_THMSTS, b1VGATempEr);	// Set bit1 Thermal IC read temperature error.
				}
			}
			else
			{
				if ( VGAErrCnt > 254 )		//T076F: from 68 to 255	// 30 Sec.
				{
					SET_MASK(SysStatus,ERR_ShuntDownFlag);
					ProcessSID(VGACOMMFAIL_ID);	// 0x20 shutdown ID.
					VGAErrCnt = 00;				// Clear error count.
#if !EN_ThermalSensorTest 
					ETWCFG=EWDKEYEN;			 // enable external WDT key
					EWDKEYR=0xFF;			// external WDT reset	
					while(1);						   // Wait for watch dog time-out
#endif  
				}
			}
			ResetSMBus(SMbusChD);
		}
		else
		{
			VGA_TEMP=((sdAMDTH2>>1)+((sdAMDTH3<<8)&0XFF));
			VGAErrCnt = 00;		// Clear error count.
			CLEAR_MASK(ERR_THMSTS,b1VGATempEr);	// Clear bit1,bit5.

			if ( IS_MASK_CLEAR(Fan_Debug_Temp,b1VGA_Temp) )	// Debug VGA Temperature, Engineer myself control.
			{
				if((VGA_TEMP&0x80)==0x80)//G69:Filter the value of the GPU temperature greater than 128 //B02: optimize G69.
				{
					return;
				}  
				else
				{
					VGA_TBuff3 = VGA_TBuff2;
					VGA_TBuff2 = VGA_TBuff1;
					VGA_TBuff1 = VGA_TEMP;
					VGA_TBuff3 = (VGA_TBuff1 + VGA_TBuff2 + VGA_TBuff3)/3;		// VGA average temperature.
				}
			}
		}
	}
}


//-----------------------------------------------------------------------------
// Function Name : ReadCPUTemp
//-----------------------------------------------------------------------------
void ReadCPUTemp(void) 
{
#if (PLATFORM_CHIP == INTEL)

	if(SystemIsS0 &&Read_LPC_RST()&&(PwrOnDly5Sec==0)) 
	{
		// Use PECI interface to read cpu temperature
#ifdef PECI_Support
#if ReadCPUTemperature
		if(CPUTjmax==0x00)         // Need to read CPU Tjmax
		{
			PECI_ReadCPUTJMAX();
		}
		else
		{
			PECI_ReadCPUTemp();     // Use PECI interface to read cpu temperature
		}

		if( IS_MASK_SET(ERR_THMSTS, b3PECITempEr) )
		{
			DTS_ReadCPUTemp();
		}
#endif
#endif 
	}


#else

	BYTE BsData;
	if( SystemNotS0 && (PwrOnDly5Sec==0)) 
		{ return; }

	if(!bRWSMBus(SMbusChA, SMbusRB, AMD_Addr, 0x01, &BsData, 0))
	{
		PECI_Err_CNT++;  
		if( IS_MASK_CLEAR(ERR_THMSTS, b3PECITempEr) ) 
		{
			if ( PECI_Err_CNT > 3 )    
			{
				SET_MASK(ERR_THMSTS, b3PECITempEr); 
			}
		}
		else
		{
			if ( PECI_Err_CNT > 34 )   
			{

				SET_MASK(SysStatus,ERR_ShuntDownFlag);
				ProcessSID(CPUCOMMFAIL_ID);  
				PECI_Err_CNT = 0;      
#if !EN_ThermalSensorTest
				ETWCFG=EWDKEYEN;			 // enable external WDT key
				EWDKEYR=0xFF;			// external WDT reset	
				while(1);						   // Wait for watch dog time-out
#endif  // EN_PwrSeqTest
			}
		}
		ResetSMBus(SMbusChA);
	}
	else
	{
		nCpuTemp = BsData;   // Get CPU temperature.
		PECI_Err_CNT = 0;   // Clear error count.
		CLEAR_MASK(ERR_THMSTS, b3PECITempEr); // Clear bit3 CPU read temperature error.
		if ( IS_MASK_CLEAR(Fan_Debug_Temp,b0CPU_Temp) )  // Debug CPU Temperature, Engineer myself control.
		{
			TEMP_Buff_3 = TEMP_Buff_2;
			TEMP_Buff_2 = TEMP_Buff_1;
			TEMP_Buff_1 = nCpuTemp;
			TEMP_Buff_3 = (TEMP_Buff_1 + TEMP_Buff_2 + TEMP_Buff_3)/3;  // CPU average temperature.
		}

	} // PLATFORM_CHIP
#endif 
        
}

void ReadPCHTemp(void) 
{
	BYTE BsData;
	if( SystemNotS0 && (PwrOnDly5Sec==0)) 
		{ return; }

	if(!bRWSMBus(SMbusChD, SMbusRB, PCH_Temp, 0x01, &BsData, 0))
	{
		PCHErrCnt++;  
		if( IS_MASK_CLEAR(ERR_THMSTS, b4PCHTempEr) ) 
		{
			if ( PCHErrCnt > 3 )    
			{
				SET_MASK(ERR_THMSTS, b4PCHTempEr); 
			}
		}
		else
		{
			if ( PCHErrCnt > 34 )   
			{

				SET_MASK(SysStatus,ERR_ShuntDownFlag);
				ProcessSID(CPUCOMMFAIL_ID);  
				PCHErrCnt = 0;      
#if !EN_ThermalSensorTest
				ETWCFG=EWDKEYEN;			 // enable external WDT key
				EWDKEYR=0xFF;			// external WDT reset	
				while(1);						   // Wait for watch dog time-out
#endif  // EN_PwrSeqTest
			}
		}
		ResetSMBus(SMbusChD);
	}
	else
	{
		nNBTemp = BsData;   // Get PCH temperature.
		PCHErrCnt = 0;   // Clear error count.
		CLEAR_MASK(ERR_THMSTS, b4PCHTempEr); // Clear bit3 PCH read temperature error.
		if ( IS_MASK_CLEAR(Fan_Debug_Temp,b3PCH_Temp) )  // Debug PCH Temperature, Engineer myself control.
		{
			PCHTEMP_Buff_3 = PCHTEMP_Buff_2;
			PCHTEMP_Buff_2 = PCHTEMP_Buff_1;
			PCHTEMP_Buff_1 = nNBTemp;
			PCHTEMP_Buff_3 = (PCHTEMP_Buff_1 + PCHTEMP_Buff_2 + PCHTEMP_Buff_3)/3;  // PCH average temperature.
		}
	} 
}

//martin0616 add start
/*****************************************************************************/
// Procedure: Chk_FAN_RPM_Control							TimeDiv: 50mSec
// Description: Check FAN is AP control.
// GPIO:
// Referrals:
/*****************************************************************************/
void Chk_FAN_RPM_Control(void)
{
	//BYTE BRPM_Manual;
	if (nFanManual == 1)
	{

#if !FAN_TABLE_Already
		FAN_PWM_ALT;			// Set FAN_PWM Alt.
#endif	// FAN_TABLE_Already	

		if ( (FAN_PWM != FAN_PWM_Max) && (nAtmFanSpeed != ManualFanPRM) )
		{
			if( nAtmFanSpeed > ManualFanPRM )
			{
				if( FAN_PWM > 0 )
					{ FAN_PWM--; }
			}
			else
			{
				if(FAN_PWM < FAN_PWM_Max)
					{ FAN_PWM++; }
				else
					{ FAN_PWM = FAN_PWM_Max; }
			}
		}
		//REJERRY033:S+ add PWM reduce after fan speed up to max.
		if ( (FAN_PWM == FAN_PWM_Max) && (nAtmFanSpeed > ManualFanPRM) ) 
		{ 
			if( FAN_PWM > 0 ) 
				{ FAN_PWM--; } 
		}
		//REJERRY033:E+.
	}
#if !FAN_TABLE_Already
	else
	{
		//if(DebugFan1RPMT==0x00 && (FANTimeCount==0))  //THOMASY022:add 	//XITING0036: remove 30% duty at first 20 seconds boot
		if(DebugFan1RPMT==0x00)												//XITING0036: remove 30% duty at first 20 seconds boot
		{
			FAN_PWM_OUT;			// Set FAN_PWM OUTPUT.
			EC_FAN_PWM_HI();
		} 
	}	
#endif	// FAN_TABLE_Already
	
}
/*****************************************************************************/
// Procedure: Chk_FAN2_RPM_Control							TimeDiv: 50mSec
// Description: Check FAN2 is AP control.
// GPIO:
// Referrals:
/*****************************************************************************/

void Chk_FAN2_RPM_Control(void)
{
	if (b7Fan2Manual == 1)
	{

#if !FAN_TABLE_Already
		FAN2_PWM_ALT;			// Set FAN2_PWM Alt. 
#endif	// FAN_TABLE_Already	

		if ( (FAN2_PWM != FAN_PWM_Max) && (nAtmFan2Speed!= ManualFan2PRM) )  
		{

			if( nAtmFan2Speed > ManualFan2PRM ) 
			{
				if( FAN2_PWM > 0 )   
					{ FAN2_PWM--; }      
			}
			else
			{
				if(FAN2_PWM < FAN_PWM_Max)
					{ FAN2_PWM++; }
				else
				{ 
					FAN2_PWM = FAN_PWM_Max; 
				}
			}
		}
		//REJERRY033:S+ add PWM reduce after fan speed up to max.
		if ( (FAN2_PWM == FAN_PWM_Max) && (nAtmFan2Speed > ManualFan2PRM) ) 
		{ 
			if( FAN2_PWM > 0 ) 
				{ FAN2_PWM--; } 
		}
		//REJERRY033:E+.
	}

#if !FAN_TABLE_Already
	else
	{
		//if(DebugFan2RPMT==0x00 && (FANTimeCount==0))  //THOMASY022:add	//XITING0036: remove 30% duty at first 20 seconds boot
		if(DebugFan2RPMT==0x00)												//XITING0036: remove 30% duty at first 20 seconds boot
		{
			FAN2_PWM_OUT;			
			EC_FAN2_PWM_HI();	                       
		}  
	}	
#endif	// FAN_TABLE_Already
}	

//martin0616 add end
/*****************************************************************************/
// Procedure: Oem_Fan_Speed										TimeDiv: 1 Sec
// Description: Read Fan RPM
// GPIO: GPIOD6(47)
// Referrals:
/*****************************************************************************/
void Oem_Fan_Speed(void)
{
	WORD Curr_Fan1Tachometer;

	BYTE tach_H; 
	BYTE tach_L; 

	if(SystemIsS0)
	{
		tach_H = F1TMRR;  
		tach_L = F1TLRR;  
		if ( (tach_H == 0) && (tach_L == 0) )  
		{
			nAtmFanSpeed = 0;
		}
		else
		{
			Curr_Fan1Tachometer = (3750000/TACH1P/((tach_H*256) + tach_L)); 
			nAtmFanSpeed = ( Curr_Fan1Tachometer / 100 );
		}
		tach_H = F2TMRR;  
		tach_L = F2TLRR;  

		if ( (tach_H == 0) && (tach_L == 0) ) 
			{ nAtmFan2Speed = 0; }
		else
		{
			Curr_Fan1Tachometer = (3750000/TACH1P/((tach_H*256) + tach_L));  
			nAtmFan2Speed = ( Curr_Fan1Tachometer / 100 ); 
		}
	}
}

/*****************************************************************************/
// Procedure: FAN_Dust_Mode										TimeDiv: 1 Sec
// Description: EM8.0 Dust function
// GPIO:
// Referrals:
/*****************************************************************************/
void FAN_Dust_Mode(void)
{
#if Lenovo_FAN_Dust		// Dust mode
	if( (IS_MASK_SET(SYS_MISC1, ACPI_OS)) && (IS_MASK_CLEAR(LENOVOBATT, BATT_TEST_MODE))
		&& (SystemIsS0) )
	{
		if ( IS_MASK_SET(SMartNoise, b5DedustingMode) )
		{
			SET_MASK(SMartNoise, b1FanCleanStart);	//start Clean Dust
			StartFanClean = 120;
			CLEAR_MASK(SMartNoise, b5DedustingMode);
			CLEAR_MASK(SMartNoise, b2StopReason); 	// Dust mode by Completed.
		}

		if ( IS_MASK_SET(SMartNoise, b1FanCleanStart))
		{
			if ( StartFanClean == 0 )
			{	// dust mode end
				CLEAR_MASK(THERMAL_STATUS, INITOK);	// turn back fan control right to EC.
				FAN_PWM = FAN_PWM_Min;				// PWM minimum.
				FAN2_PWM = FAN_PWM_Min;	// FAN2 control setting.
				SMartNoise &= 0xEC; 				// Clear bit0,1,4.
				FanCleanFull = 0;
				FanCleanHalt = 0;
				CLEAR_MASK(SMartNoise, b2StopReason); // Dust mode by Completed.
			}
			else
			{
				StartFanClean--;
				if ( IS_MASK_CLEAR(SMartNoise, b0FanCleanOn))
				{
					if( !ChkTimeScale( &FanCleanFull,Timer_8 ) )
					{
						//SET_MASK(THERMAL_STATUS, INITOK);
						FAN_PWM = CTR2;
						FAN2_PWM = CTR2;//JERRYCR018:Add FAN2 control setting.
					}
					else
						{ SET_MASK(SMartNoise, b0FanCleanOn); }
				}
				else
				{
					if( !ChkTimeScale( &FanCleanHalt,Timer_1 ) )
					{
						//SET_MASK(THERMAL_STATUS, INITOK);
						FAN_PWM = 0;
						FAN2_PWM = 0;//JERRYCR018:Add FAN2 control setting.
					}
					else
						{ CLEAR_MASK(SMartNoise, b0FanCleanOn); }
				}
			}
		}
	}
	else
	{
		CLEAR_MASK(THERMAL_STATUS, INITOK);	// turn back fan control right to EC.
		FanCleanFull = 0;
		FanCleanHalt = 0;
		SMartNoise = 0x04;					// Stop Fan Dust mode.
	}
#endif	// Lenovo_FAN_Dust
}

//XITING0014:S modify throttling table
//REJERRY055:Modify throttling table start.
const CPUTHRstruct CPUTHRTable[]=  
{   
	//  Thr_Off      Thr_On   Turbo_Rem    Turbo_Off   Thr_Shut     Step  Throttling Table
	{	92,		 97,		75,			85,			100	},  // 0   DIS Standard mode  CPU  //REJERRY072:modify turbo off temp.//HEGANG0009:Modify fan table follow'DY520 SIT fan table_0419'.	//XITING0014:modify table by fantable_0123	//XITING0040: change Turbo_Rem from 80 to 75 by fan table 0321
	{	92,	 	 97,		90,		    94,		    100	},  // 1   DIS Standard mode  VGA																							//XITING0014:modify table by fantable_0123
	{	92,	 	 97,		65,			72,			100	},  // 2   UMA Standard mode CPU  //REJERRY072:modify turbo off temp.
	{	92,	     97,		85,		    90,		    100	},  // 3   UMA Standard mode  VGA  
};
//XITING0014:E

/*****************************************************************************/
// Procedure: ThrottlingControl								TimeDiv: 100mSec
// Description: Chekc all throttling status.
// GPIO:
// Referrals:
/*****************************************************************************/
void ThrottlingControl(void)
{
	if ( SystemIsS0 )
	{
		//REJERRY059:S-.
		/*if ( IS_MASK_CLEAR(SYS_STATUS,AC_ADP)&&(0x00==cBATTThrottling) )
		{ cBATTThrottling = 0x01; }*/
		//REJERRY059:E-.
			  
		cThrottlingSet &= 0xF0;	// Clear Throttling status.
	
		if( ( cThrottlingSet & 0x0F ) < cADPThrottling )	// Compare current and ADP Throttling
		{
			cThrottlingSet |= cADPThrottling;
		}
		if( ( cThrottlingSet & 0x0F ) < cTHERMThrottling ) // Compare current and Thermal throttling.
		{
			cThrottlingSet &= 0xF0;
			cThrottlingSet |= cTHERMThrottling;
		}
		if( ( cThrottlingSet & 0x0F ) < cBATTThrottling )	// Compare current and BAT throttling.
		{
			cThrottlingSet &= 0xF0;
			cThrottlingSet |= cBATTThrottling;
		}
		if( ( cThrottlingSet & 0x0F ) < nThrottlingAPSet ) // For AP or debug
		{
			cThrottlingSet &= 0xF0;
			cThrottlingSet |= nThrottlingAPSet;
		}
	
		if( ( cThrottlingSet & 0x0F ) != ( REAL_THROTTLING_INDEX & 0x0F ) )
		{	// Cpu throttling for power status change
			if( ( (nRealThermalPinGET) && (( cThrottlingSet & 0x0F ) >= 0x01 ))
			|| (!nRealThermalPinGET) )
			{
				SET_MASK(cThrottlingSet,cTHRM_SW); 
				RamDebug(0xA9);	   // 	
				REAL_THROTTLING_INDEX = (REAL_THROTTLING_INDEX & 0xF0) | (cThrottlingSet & 0x0F);
				RamDebug(REAL_THROTTLING_INDEX);
			}
		}
		if(IS_MASK_SET(cThrottlingSet,cTHRM_SW) ) //
		{
			CLEAR_MASK(cThrottlingSet,cTHRM_SW);
			if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )	// Check OS mode.
			{
				//XITING0035:S remove  	not send Qevent(1d) to BIOS,Using Qevent(66,67)	
				//RamDebug(0xEC);
				//RamDebug(CPU_SLOW_AD);
				//ECQEvent(CPU_SLOW_AD);	// 0x1D inform bios.
				//XITING0035:E 
			}
		}
	}
}

//REJERRY048:S+ add GPU throttling function.
void GPUThrottlingControl(void)
{
	if ( SystemIsS0 && (CPU_TYPE&0xc0) )
	{
		cGPUThrottlingSet &= 0xF0;	// Clear Throttling status.
		/*
		//XITING0002:remove S using adc get psys
		
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUPowerThrottling)	// Compare power Throttling 
		{
			cGPUThrottlingSet |= cGPUPowerThrottling;
		}*/
		//XITING0002:remove E
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUBattAlarmThrottling)	// Compare battery OCP alarm Throttling 
		{
			cGPUThrottlingSet |= cGPUBattAlarmThrottling;
		}
	
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUBattOTPThrottling)	// Compare battery OPT Throttling 
		{
			cGPUThrottlingSet &= 0xF0;
			cGPUThrottlingSet |= cGPUBattOTPThrottling;
		}
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUBattRSOCThrottling)	// Compare battery RSOC low Throttling 
		{
			cGPUThrottlingSet &= 0xF0;
			cGPUThrottlingSet |= cGPUBattRSOCThrottling;
		}
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUThermalThrottling)	// Compare current and Thermal throttling
		{
			cGPUThrottlingSet &= 0xF0;
			cGPUThrottlingSet |= cGPUThermalThrottling;
		}
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUACOVPThrottling)	// Compare current and Thermal throttling
		{
			cGPUThrottlingSet &= 0xF0;
			cGPUThrottlingSet |= cGPUACOVPThrottling;
		}
		//XITING0002:S+
		if( ( cGPUThrottlingSet & 0x0F ) < cGPUBattPsysThrottling)	// Compare current and Thermal throttling
		{
			cGPUThrottlingSet &= 0xF0;
			cGPUThrottlingSet |= cGPUBattPsysThrottling;
		}
		//XITING0002:E+
		if( ( cGPUThrottlingSet & 0x0F ) != ( GPU_REAL_THROTTLING_INDEX & 0x0F ) )
		{	// send GPU throttling event.
			GPU_REAL_THROTTLING_INDEX = (GPU_REAL_THROTTLING_INDEX & 0xF0) | (cGPUThrottlingSet & 0x0F);
			RamDebug(0xEE); 
			RamDebug(GPU_SLOW);    
			ECQEvent(GPU_SLOW); // 0x1E inform bios.
		}
	}
}
//REJERRY048:E+ add GPU throttling function.


#if OEMCPUThrottlingCtrl
#if 0
void SaveCPU1Temp(BYTE CpuTemp)
{
	CPU1tempn_2 = CPU1tempn_1;
	CPU1tempn_1 = CPU1tempCurrent;
	CPU1tempCurrent = nCpuTemp;
}

BYTE CalcCPU1tempavg(void)
{
	//BYTE avg;

	if(CPU1tempn_2!=0 && CPU1tempn_1!=0 && CPU1tempCurrent!= 0)
	{
		nCpuTemp= ((WORD)CPU1tempCurrent + (WORD)CPU1tempn_1 + (WORD)CPU1tempn_2)/3;
	}
	else
	{
		if(CPU1tempCurrent != 0)
		{
			if(CPU1tempn_2==0 && CPU1tempn_1==0)
			{
				nCpuTemp = CPU1tempCurrent;
			}
			else if(CPU1tempn_2==0 && CPU1tempn_1!=0)
			{
				nCpuTemp = ((WORD)CPU1tempCurrent + (WORD)CPU1tempn_1)/2;
			}
			else if(CPU1tempn_1==0 && CPU1tempn_2!=0)
			{
				nCpuTemp = ((WORD)CPU1tempCurrent + (WORD)CPU1tempn_2)/2;
			}
				 
		}
		else
		{
			nCpuTemp = 0;
		}
	}
	return nCpuTemp;	
}


void CPUTurboOn(void)
{
	if(IS_MASK_CLEAR(TmlCtrlFlag, CpuTubo_on))	// enable turbo
	{
		REAL_THROTTLING_INDEX &= 0xF0; 
		ECQEvent(CPU_SLOW_AD);
		RamDebug(0x1D);
		RamDebug(0x85);
		//REAL_THROTTLING_INDEX &= 0xF0; 
		SET_MASK(TmlCtrlFlag, CpuTubo_on);
	}
}


void CPUTurboOff(void)
{
	if(IS_MASK_SET(TmlCtrlFlag, CpuTubo_on))		// set turbo off
	{
		REAL_THROTTLING_INDEX &= 0xF0;	// Clear thermal throttling status.
		REAL_THROTTLING_INDEX += 0x01;	// Set P-State level.
		ECQEvent(CPU_SLOW_AD);
		RamDebug(0x1D);
		RamDebug(0x87);
		CLEAR_MASK(TmlCtrlFlag, CpuTubo_on);
	}
}

void CpuProchotHigh(void)
{
	if(IS_MASK_SET(TmlCtrlFlag, CpuProcHot_on))	// set PROCHOT high 
	{
		H_PROCHOT_HI();		// set PROCHOT high
		RamDebug(0x89);
		CLEAR_MASK(TmlCtrlFlag, CpuProcHot_on);
	}
}

void CpuProchotLow(void)
{
	if(IS_MASK_CLEAR(TmlCtrlFlag, CpuProcHot_on))		// set PROCHOT low to 
	{
		H_PROCHOT_LOW();		// set PROCHOT low to 
		RamDebug(0x8A);
		SET_MASK(TmlCtrlFlag, CpuProcHot_on);
	}
}

void CpuThrottleDisable(void)
{
	if(IS_MASK_CLEAR(TmlCtrlFlag, throttle_off))	// set throttle off 
	{	
	       REAL_THROTTLING_INDEX &= 0xF0;	// Clear thermal throttling status.
 		ECQEvent(CPU_SLOW_AD);
		RamDebug(0x6B);
		SET_MASK(TmlCtrlFlag, throttle_off);
	}
}


void CpuThrottleEnable(void)		// set throttle on
{
	if(IS_MASK_SET(TmlCtrlFlag, throttle_off))
	{
	      if(REAL_THROTTLING_INDEX !=0x0F) 
	      	{
	         REAL_THROTTLING_INDEX++;
		  REAL_THROTTLING_INDEX &=0x0F;
  		  ECQEvent(CPU_SLOW_AD);
		  RamDebug(0x6C);
	      	}
		 else{CLEAR_MASK(TmlCtrlFlag,throttle_off);}
	}
}
#endif

void ShutDownOS(void)
{
#if !EN_PwrSeqTest  //BROOKEW040
#if !EN_ThermalSensorTest      //MARTINH023:add judge
	ETWCFG=EWDKEYEN;			 // enable external WDT key
	EWDKEYR=0xFF;			// external WDT reset	
	while(1);						   // Wait for watch dog time-out
#endif  
#endif
}


void OEM_Throttling_Ctrl(void)
{
	BYTE BTbStep; 
	if( SystemNotS0 )
	{
		H_PROCHOT_LOW();
		VGA_AC_DET_HIGH(); //REJERRY070:add.
		//GPU_REAL_THROTTLING_INDEX &= 0xF0; //REJERRY070:add.		//XITING0064:remove when OS not S0 keep GPU D state
		CLEAR_MASK(TmlCtrlFlag, CpuProcHot_on);
		REAL_THROTTLING_INDEX &= 0xF0;
		CLEAR_MASK(TmlCtrlFlag, CpuTubo_on);
		NTC_V = 0xFFFF; 
		return;
	}

	//REJERRY058:S- remove UMA/DIS ready check.
	/*if(IS_MASK_CLEAR(pProject0,b7UMADISReady))
	{
		return;
	}*/
	//REJERRY058:E-.

	if(IS_MASK_SET(pProject1,b0NvGpuG1))//1050ti//REJERRY0979:Update fan table'DY512 SIT fan table_1212'.
	{	// UMA.
		BTbStep = 2;		
	}
	else//1050m
	{	// DIS.
		BTbStep = 0;	
	}
	Thro_Std_Mode(BTbStep);

}

//-----------------------------------------------------------------------------
// Throttling: Standard Mode.
//-----------------------------------------------------------------------------
void Thro_Std_Mode(BYTE BMBStep)
{
	THRTab_ToRAM((0+BMBStep));	// Throttle Standard table save to RAM.
	Thro_Shut_Status((0+BMBStep),TEMP_TYPE_CPU); 	// Check Throttle and Shutdown status.
	// Check CPU Turbo function.
	Thro_Turbo(THR_Turo_Rem,THR_Turo_OFF,TEMP_TYPE_CPU); 

	//REJERRY069:S- remove GPU table for control turbo and shutdown.
	VTHRTab_ToRAM((1+BMBStep));// VGA Throttle Standard table save to RAM. 
	Thro_Shut_Status((1+BMBStep),TEMP_TYPE_VGA); // Check Throttle and Shutdown status.  
	// Check GPU Turbo function.
	Thro_Turbo(VTHR_Turo_Rem,VTHR_Turo_OFF,TEMP_TYPE_VGA);
	//REJERRY069:E-.

	Thro_Shut_Status(0,TEMP_TYPE_remote);
	Thro_Shut_Status(0,TEMP_TYPE_NTC_V);
	
}
//-----------------------------------------------------------------------------
// Throttling: Check CPU/VGA Turbo status.
//-----------------------------------------------------------------------------
void Thro_Turbo(BYTE BTurboRem, BYTE BTurboOff, BYTE BTType)
{
	if ( IS_MASK_CLEAR(SYS_MISC1, ACPI_OS) ) 
		{ return; }

	if ( BTType == TEMP_TYPE_VGA )
	{
		//XITING0068:S remove
		/*
		// Set Internal VGA.
		if ( VGA_TBuff3 <= BTurboRem )				// Check turbo resume.
		{ 
			//CLEAR_MASK(Thro_Status, b4Turbo_VGA); 
			cGPUThermalThrottling=0;
		}
		else if ( VGA_TBuff3 >= BTurboOff ) 		// Check turbo Off.
		{ 
			//SET_MASK(Thro_Status, b4Turbo_VGA); 
			cGPUThermalThrottling=1;
		}
		*/
		//XITING0068:E

		//XITING0068:add GPU temp and PCH temp control GPU D state by board ID
		if(KeyBoardID == 0x01)										//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
		{
			if((VGA_TBuff3 <= 90) && (nPCH_Temp <= 100))
			{
				cGPUThermalThrottling = 0;
			}
			else if((VGA_TBuff3 >= 94) || (nPCH_Temp >= 108))
			{
				cGPUThermalThrottling = 2;
			}
		}
		else if(KeyBoardID == 0x02)									//XITING0068:add change fan table by board id 01 - Y530 ,02 - Y530P
		{
			//if ( VGA_TBuff3 <= 89 && nPCH_Temp <= 105 )			//XITING0070:change from 89 to 90 Y530P 1060 SIT fan table_0703		
			if ( VGA_TBuff3 <= 90 && nPCH_Temp <= 105 )				//XITING0070:change from 89 to 90 Y530P 1060 SIT fan table_0703
			{ 
				cGPUThermalThrottling=0;
			}
			else	
			{ 
				if (nPCH_Temp >= 108 )
				{
					cGPUThermalThrottling = 1;
				}
				//if ( VGA_TBuff3 >= 92 || nPCH_Temp >= 110 )			//XITING0070:change from 92 to 93 Y530P 1060 SIT fan table_0703
				if ( VGA_TBuff3 >= 93 || nPCH_Temp >= 110 )			//XITING0070:change from 92 to 93 Y530P 1060 SIT fan table_0703
				{
					cGPUThermalThrottling = 2;
				}
			}
		}	
		//XITING0068:E
		
	}
	else
	//REJERRY0979:s+Update fan table'DY512 SIT fan table_1212'.
	{	// Set Internal CPU.
		if(IS_MASK_SET(pProject1,b0NvGpuG1))
		{
			if (( TEMP_Buff_3 <= BTurboRem )&&IS_MASK_SET(Thro_Status, b3Turbo_CPU))			// Check turbo resume.
			{ 
				CLEAR_MASK(Thro_Status, b3Turbo_CPU); 
			}
			else if(TEMP_Buff_3 >= BTurboOff) 			// Check turbo Off.  //REJERRY055:remove.		//XITING0040:add
			//else if (((TEMP_Buff_3 >= BTurboOff)&&(VGA_TBuff3 >= 72)) ||(VGA_TBuff3 >= 80)||(TEMP_Buff_3 >= 88))	//REJERRY055:add. //REJERRY072:modify turbo off temp. //REJERRY075:add CPU temp condition. //REJERRY078:modify CPU condition temp.//HEGANG003:Modify fan table follow'DY520 SIT fan table_0329'.//HEGANG0009:Modify fan table follow'DY520 SIT fan table_0419'.	//XITING0040:remove
			{ 
				SET_MASK(Thro_Status, b3Turbo_CPU); 
			}
		}
		else
		{
			if (( TEMP_Buff_3 <= BTurboRem )&&IS_MASK_SET(Thro_Status, b3Turbo_CPU))			// Check turbo resume.
			{ 
				CLEAR_MASK(Thro_Status, b3Turbo_CPU);
			}
			else if(TEMP_Buff_3 >= BTurboOff) 			// Check turbo Off.  //REJERRY055:remove.			//XITING0040:add
			//else if (((TEMP_Buff_3 >= BTurboOff)&&(VGA_TBuff3 >= 70)) ||(VGA_TBuff3 >= 78)||(TEMP_Buff_3 >= 78))	//REJERRY055:add. //REJERRY072:modify turbo off temp. //REJERRY075:add CPU temp condition. //REJERRY078:modify CPU condition temp.		//XITING0040:remove
			{ 
				SET_MASK(Thro_Status, b3Turbo_CPU); 
			}	
		}
	}
	//REJERRY0979:e+Update fan table'DY512 SIT fan table_1212'.
	//REJERRY104:Update fan table'DY512 SIT fan table_1228'.
	if ( IS_MASK_CLEAR(Thro_Status, b3Turbo_CPU) )	  
	{ 
		cTHERMThrottling &= 0xF0; 
	}	// Not need throttling.
	else
	{
		cTHERMThrottling &= 0xF0;	// Clear thermal throttling status.
		cTHERMThrottling |= 0x02;	// Set P-State level. //MARTINH137:change 0x01 to 0x02
	}

	//XITING0019:S remove Turbo on and Turbo off 
	/*
	//XITING0027:S add CPU turbo control	(enable/disable)
	if ( IS_MASK_CLEAR(Thro_Status, b3Turbo_CPU ))
	{
		if ( IS_MASK_SET(uVGATurboFun,uDisCPUTurboOK) )		
		{
			CLEAR_MASK(uVGATurboFun, uDisCPUTurboOK);	
            ECQEvent(EN_CPUTURBO_67);
		}
	}
	else
	{
	 	if ( IS_MASK_CLEAR(uVGATurboFun,uDisCPUTurboOK) )
	 	{
			SET_MASK(uVGATurboFun, uDisCPUTurboOK);	
            ECQEvent(DIS_CPUTURBO_66);
	 	}
	}
	//XITING0027:E
	*/
	//XITING0019:E

	//REJERRY055:S- remove GPU turbo on/off.
	/*if ( IS_MASK_CLEAR(Thro_Status, (b4Turbo_VGA)) )
	{
		if ( IS_MASK_SET(uVGATurboFun,uDisVGATurboOK) ) 	// bit2.
		{
			CLEAR_MASK(uVGATurboFun, uDisVGATurboOK); 		// Set bit2.
			RamDebug(0x63);		
			ECQEvent(DIS_TURBO_63); 						// 0x63 VGA Disable turbo.
		}
	}
	else
	{
		if ( IS_MASK_CLEAR(uVGATurboFun,uDisVGATurboOK) )	// bit2.
		{
			SET_MASK(uVGATurboFun, uDisVGATurboOK); 		// Set bit2.
			RamDebug(0x62);		 
			ECQEvent(EN_TURBO_62);							// 0x62 VGA Enable turbo.
		}
	}*/
	//REJERRY055:E-.

}


//-----------------------------------------------------------------------------
// Throttling: Check throttling and Shutdown status.
//-----------------------------------------------------------------------------
void Thro_Shut_Status(BYTE BStep, BYTE BTType)
{
	if ( BTType == TEMP_TYPE_VGA )
	{	// Set Internal VGA.
		if( VGA_TBuff3 <= THR_PRO_OFF) 	
		{ 
			CLEAR_MASK(Thro_Status, b1ProCH_VGA); 
		}
		else if( VGA_TBuff3 >= THR_PRO_ON )
		{ 
			SET_MASK(Thro_Status, b1ProCH_VGA); 
		}
	
		if ( VGA_TBuff3 >= THR_Tab_Shut )   
		{ 
			Thro_Count_Shut(&VGA_Shut_Cnt,TEMP_TYPE_VGA); 
		}	// Check x times for shutdown protection.
		else
		{ 
			VGA_Shut_Cnt = 0; 
		}
	}
	else if( BTType == TEMP_TYPE_CPU )     
	{	// Set Internal CPU.
		if ( TEMP_Buff_3 <= THR_PRO_OFF)  
		{
			CLEAR_MASK(Thro_Status, b0ProCH_CPU); 
		}
		else if ( TEMP_Buff_3 >= THR_PRO_ON)   
		{ 
			SET_MASK(Thro_Status, b0ProCH_CPU); 
		}	
					
		if ( TEMP_Buff_3 >= THR_Tab_Shut )	 
		{ 
			Thro_Count_Shut(&CPU_Shut_Cnt,TEMP_TYPE_CPU); 
		}	// Check x times for shutdown protection.
		else
		{ 
			CPU_Shut_Cnt = 0; 
		}
	}
    else if( BTType == TEMP_TYPE_remote)	  
	{  // Set CPU thermistor.

		//REJERRY062:S- remove cpu thermal IC temp.
		/*if(IS_MASK_SET(pProject0,b4VGAType))
		{
			 if ( nVramTemp >= nRemoteOverTemp_UMA )	
			{ 
				Thro_Count_Shut(&RemoteSensor_Shut_Cnt,TEMP_TYPE_remote); 
			}   // Check x times for shutdown protection.
			else
			{ 
				RemoteSensor_Shut_Cnt = 0; 
			}
		}
		else
		{
			if ( nVramTemp >= nRemoteOverTemp_DIS )	
			{ 
				Thro_Count_Shut(&RemoteSensor_Shut_Cnt,TEMP_TYPE_remote); 
			}   // Check x times for shutdown protection.
			else
			{ 
				RemoteSensor_Shut_Cnt = 0; 
			}
		}*/
		//REJERRY062:E-.

		//REJERRY062:S+ add CPU thermistor temp.
		if ( ThermistorCPU_TEMP >= nCPUthermistoroverTemp )
		{ 
			Thro_Count_Shut(&RemoteSensor_Shut_Cnt,TEMP_TYPE_remote); 
		}   // Check x times for shutdown protection.
		else
		{ 
			RemoteSensor_Shut_Cnt = 0; 
		}
		//REJERRY062:E+.
	}
	else if( BTType == TEMP_TYPE_NTC_V)	   
	{	// Set GPU thermistor.

		//REJERRY062:S-.
		/*if ( NTC_V <= nNTC_VOverTemp )	 
		{ 
			Thro_Count_Shut(&NTC_V_Shut_Cnt,TEMP_TYPE_NTC_V); 
		}   // Check x times for shutdown protection.
		else
		{ 
			NTC_V_Shut_Cnt = 0; 
		}*/
		//REJERRY062:E-.

		//REJERRY062:S+ add GPU thermistor temp.
		if ( EXTVGA_TEMP >= nGPUthermistoroverTemp )
		{
			Thro_Count_Shut(&NTC_V_Shut_Cnt,TEMP_TYPE_NTC_V); 
		} 
		else
		{ 
			NTC_V_Shut_Cnt = 0; 
		}
		//REJERRY062:E+.
	}

	CPU_Prochot_Ctrl(); //REJERRY031:add.
			 
}
//-----------------------------------------------------------------------------
// Throttling: Shutdown count used.
//-----------------------------------------------------------------------------
void Thro_Count_Shut(BYTE *BShut_Cnt, BYTE TempType)
{
	if ( *BShut_Cnt >= Thro_Shut_Cnt )	// Read 30 times.
	{
		if ( TempType == TEMP_TYPE_VGA )
		{ 
		    ProcessSID(VGAOVERTEMP_ID); 
		}	// VGA Shutdown ID 0x12.
		else if( TempType == TEMP_TYPE_CPU ) 
	    { 
	        ProcessSID(DTSOVERTEMP_ID); 
	    }	// CPU Shutdown ID 0x11.
		else if ( TempType == TEMP_TYPE_remote )
		{ 
		    ProcessSID(CPUthermistoroverTemp_ID); 
		} 
		else if ( TempType == TEMP_TYPE_NTC_V )
		{
		    ProcessSID(GPUthermistoroverTemp_ID); 
		} 

		SET_MASK(SysStatus,ERR_ShuntDownFlag);		
		
		*BShut_Cnt = 0;
		ETWCFG=EWDKEYEN;			 // enable external WDT key
		EWDKEYR=0xFF;			// external WDT reset	
		while(1);						   // Wait for watch dog time-out
		SET_MASK(USB_Charger, b2USB_TmlDis);	// Disable USB charger.
	}
	else
	{ 
	    (*BShut_Cnt)++; 
	}
}

//REJERRY031:S+ add CPU prochot control function.
void CPU_Prochot_Ctrl(void)
{	
	if ( IS_MASK_CLEAR(Thro_Status, (b0ProCH_CPU+b1ProCH_VGA+b2ProCH_EXTVGA+b6ProCH_TURBO))
		&& IS_MASK_CLEAR(nBatteryStatH, CMBS_CRITICALLOW)
		//&& IS_MASK_CLEAR(CPUProchotFlag,b0CpuADPI+b1CpuBattPmax+b2CpuBattRSOC+b3CpuBattAlarm+b4CpuBattOTP) //REJERRY042:modify bit0 to bit5 flag. 
		&& IS_MASK_CLEAR(CPUProchotFlag,b0CpuADPI+b1CpuBattPmax+b2CpuBattRSOC+b3CpuBattAlarm+b4CpuBattOTP+b5CpuPsys) //XITING0002:add psys flag
		&&(CPUProchotONCnt == 0)&&(S0CPUProchotONCnt==0)) //REJERRY0978:update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.
	{	
		H_PROCHOT_LOW();
		//VGA_AC_DET_HIGH();  //REJERRY042:add. //REJERRY048:remove.
		nRealThermalPinDIS;
		CLEAR_MASK(pPROCHOT, b0Thermal_PRCOHOTon);	// for AP display.
		//RamDebug(0x64);
	}
	else
	{	// turn on prochot.
		H_PROCHOT_HI();
		//VGA_AC_DET_LOW();  //REJERRY042:add. //REJERRY048:remove.
		nRealThermalPinEN;
		SET_MASK(pPROCHOT, b0Thermal_PRCOHOTon);	// for AP display.
		//RamDebug(0x67);
	}
}
//REJERRY031:E+ add CPU prochot control function.

//REJERRY048:S+ add GPU prochot control function.
void GPUProchotOnControl(void)
{
	//if( CPUProchotONCnt == 0 ) //REJERRY056:remove.
	//if(IS_MASK_CLEAR(GPUProchotFlag,b0GpuAdpI+b1GpuBattAlarm+b2GpuBattOTP+b3GpuBattPmax)
	if(IS_MASK_CLEAR(GPUProchotFlag,b0GpuAdpI+b1GpuBattAlarm+b2GpuBattOTP+b3GpuBattPmax+b4GpuPsys)		//XITING0002:add psys flag
		&&( CPUProchotONCnt == 0 )
		&&(S0CPUProchotONCnt==0)) //REJERRY056:add. //REJERRY077:add battery OTP condition.//REJERRY0978:update power setting'LBG EC Parameter V2.1_for Y510IP710 20161210'.
	{
		VGA_AC_DET_HIGH();
	}
	else
	{
		VGA_AC_DET_LOW();
	}
}
//REJERRY048:E+ add GPU prochot control function.

//-----------------------------------------------------------------------------
// Throttle table save to ram.
//-----------------------------------------------------------------------------
void THRTab_ToRAM(BYTE BStep)
{ 
	THR_PRO_OFF 	= CPUTHRTable[BStep].Thr_Off;
	THR_PRO_ON		= CPUTHRTable[BStep].Thr_On;
	THR_Turo_Rem	= CPUTHRTable[BStep].Turbo_Rem;
	THR_Turo_OFF	= CPUTHRTable[BStep].Turbo_Off;
	THR_Tab_Shut	= CPUTHRTable[BStep].Thr_Shut;
}
//-----------------------------------------------------------------------------
// VGA Throttle table save to ram.
//-----------------------------------------------------------------------------
void VTHRTab_ToRAM(BYTE BStep)
{  
	VTHR_PRO_OFF 	= CPUTHRTable[BStep].Thr_Off;
	VTHR_PRO_ON		= CPUTHRTable[BStep].Thr_On;
	VTHR_Turo_Rem	= CPUTHRTable[BStep].Turbo_Rem;
	VTHR_Turo_OFF	= CPUTHRTable[BStep].Turbo_Off;
	VTHR_Tab_Shut	= CPUTHRTable[BStep].Thr_Shut;
}

#endif


//REJERRY062:S+ add switch from thermistor voltage to temp.
const SRTVTstruct RTVTTable [] =
{
	{20,0x040E},
	{21,0x0409},
	{22,0x0404},
	{23,0x03FF},
	{24,0x03F9},
	{25,0x03F4},
	{26,0x03EE},
	{27,0x03E8},
	{28,0x03E2},
	{29,0x03DB},
	{30,0x03D5},
	{31,0x03CE},
	{32,0x03C7},
	{33,0x03C0},
	{34,0x03B9},
	{35,0x03B1},
	{36,0x03AA},
	{37,0x03A2},
	{38,0x039A},
	{39,0x0392},
	{40,0x0389},
	{41,0x0381},
	{42,0x0378},
	{43,0x0370},
	{44,0x0367},
	{45,0x035E},
	{46,0x0354},
	{47,0x034B},
	{48,0x0342},
	{49,0x0338},
	{50,0x032E},
	{51,0x0324},
	{52,0x031A},
	{53,0x0310},
	{54,0x0306},
	{55,0x02FC},
	{56,0x02F2},
	{57,0x02E7},
	{58,0x02DD},
	{59,0x02D2},
	{60,0x02C8},
	{61,0x02BD},
	{62,0x02B2},
	{63,0x02A8},
	{64,0x029D},
	{65,0x0292},
	{66,0x0287},
	{67,0x027D},
	{68,0x0272},
	{69,0x0267},
	{70,0x025D},
	{71,0x0252},
	{72,0x0247},
	{73,0x023D},
	{74,0x0232},
	{75,0x0228},
	{76,0x021E},
	{77,0x0213},
	{78,0x0209},
	{79,0x01FF},
	{80,0x01F5},
	{81,0x01EB},
	{82,0x01E1},
	{83,0x01D7},
	{84,0x01CE},
	{85,0x01C4},
	{86,0x01BB},
	{87,0x01B1},
	{88,0x01A8},
	{89,0x019F},
	{90,0x0196},
	{91,0x018E},
	{92,0x0185},
	{93,0x017C},
	{94,0x0174},
	{95,0x016C},
	{96,0x0164},
	{97,0x015C},
	{98,0x0154},
	{99,0x014C},
	{100,0x0145},
	{101,0x013D},
	{102,0x0136},
	{103,0x012F},
	{104,0x0128},
	{105,0x0121},
	{106,0x011A},

};

void PollingCPURT(void)
{
	BYTE i;
	BYTE j=0;

	for (i=0;i<(sizeof(RTVTTable)/sizeof(SRTVTstruct));i++)
	{
		if(NTC_V2<RTVTTable[j].VOL)
		{
			j++;
		}
		else if(NTC_V2>=RTVTTable[j].VOL)
		{
			ThermistorCPU_TEMP=RTVTTable[j].TEM;//JERRYCRZ024:Change fan table follow thermal team.
			return;
		}	
	}
}


void PollingGPURT(void)
{
	BYTE i;
	BYTE j=0;

	for (i=0;i<(sizeof(RTVTTable)/sizeof(SRTVTstruct));i++)
	{
		if(NTC_V<RTVTTable[j].VOL)
		{
			j++;
		}
		else if(NTC_V>=RTVTTable[j].VOL)
		{
			EXTVGA_TEMP=RTVTTable[j].TEM;//JERRYCRZ024:Change fan table follow thermal team.
			return;
		}		
	}
}

//THOMASY006:S+
void PollingDIMMRT(void)
{
	BYTE i;
	BYTE j=0;

	for (i=0; i<(sizeof(RTVTTable)/sizeof(SRTVTstruct)); i++)
	{
		if(NTC_V3 < RTVTTable[j].VOL)
		{
			j++;
		}
		else if(NTC_V3 >= RTVTTable[j].VOL)
		{
			nVramTemp=RTVTTable[j].TEM;
			return;
		}
	}
}
//THOMASY006:E+

//REJERRY062:E+.

void DPTFControl(void)
{
	if(SystemNotS0)
	{
		return;
	}

	if (EXTVGA_TEMP >= DPTFtemp)
	{
		DPTF_OverTemp_Count++;
		DPTF_UnderTemp_Count = 0;
	}
	else
	{
		DPTF_OverTemp_Count = 0;
		DPTF_UnderTemp_Count++;
	}

	if(DPTF_OverTemp_Count == 5)
	{
		DPTF_OverTemp_Count = 0;
		if(DPTF_OverTemp_Flag == 0)
		{
			ECQEvent(DPTF_EVENT);
			DPTF_OverTemp_Flag = 1;
		}
	}

	if(DPTF_UnderTemp_Count == 5)
	{
		DPTF_UnderTemp_Count = 0;
		DPTF_OverTemp_Flag = 0;
	}
}


