/* 
 * ****************************************************************************
 * oem_event.h
 * ****************************************************************************
 */

#ifndef OEM_EVENT_H
#define OEM_EVENT_H

extern void PSWPressed(void);		
extern void LanWakeLow(void);
extern void PSWReleased(void);


//extern void Enable_INTR_ACOUT(void); //REJERRY031:remove.
//extern void Disable_INTR_ACOUT(void);  //REJERRY031:remove.
//extern void Enable_INTR_ACIN(void);  //REJERRY031:remove.
extern void PAD_Lid_Process(void);
extern void EventManager(BYTE device_id);
struct sDebounce
{
	BYTE	*REG_Event;
	BYTE	Flag_Event;
	BYTE	*Cunter_Event;
	BYTE	Time_Event;
	FUNCT_PTR_V_V	press;
	FUNCT_PTR_V_V	release;
	FUNCT_PTR_V_V	nochange;	
};
#endif

