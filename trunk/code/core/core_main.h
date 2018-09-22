/* 
 * ****************************************************************************
 * core_main.h
 * ****************************************************************************
 */
 
#ifndef CORE_MAIN_H
#define CORE_MAIN_H 

/* 
 * ****************************************************************************
 * definition
 * ****************************************************************************
 */
#define Only_Timer1msEvent  0x01
#define All_TimerEvent      0x00
#define Normal_MainService  0xFF
 
/* 
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
int main(void);
extern void main_service(void);
void service_unlock(void);
void service_Low_LVEvent(void);
void service_1mS(void); 
void ISR_Timer1msEvent(void);
void ISR_Timer5msEvent(void);
void ISR_Timer10msEvent(void);
void Timer1msEvent(void);
void Timer5msEvent(void);
void Timer10msEventA(void);
void Timer10msEventB(void);
void Timer50msEventA(void);
void Timer50msEventB(void);
void Timer50msEventC(void);
void Timer100msEventA(void);
void Timer100msEventB(void);
void Timer100msEventC(void);
void Timer500msEventA(void);
void Timer500msEventB(void);
void Timer500msEventC(void);
void Timer1SecEventA(void);
void Timer1SecEventB(void);
void Timer1SecEventC(void);
void Timer1MinEvent(void);
extern BYTE CheckEventPending(void);
extern void service_extend_task(void);

#endif  

