/* 
 * ****************************************************************************
 * core_hostif.h
 * ****************************************************************************
 */
 
#ifndef CORE_HOSTIF_H 
#define CORE_HOSTIF_H

/* 
 * ****************************************************************************
 * function prototype
 * ****************************************************************************
 */
extern void Data_To_Host(BYTE data_byte);
extern void Data_To_Host_nWait(BYTE data_byte);
extern void Aux_Data_To_Host(BYTE data_byte);
extern void SetServiceSendFlag(void);
extern void service_send(void);
//[-start-160526-David-remove]//
//extern BYTE get_response(void);
//[-end-160526-David-remove]//
BYTE send_to_pc(BYTE data_word, BYTE break_prefix_flag);
BYTE common_send_to_pc(BYTE data_word, BYTE break_prefix_flag);
BYTE translate_to_pc(BYTE data_word, BYTE break_prefix_flag);
extern void KBC_DataPending(BYTE nPending);
extern BYTE GetKB_PendingData(void);
extern void KBC_DataToHost(BYTE nKBData);
extern void Core_InitSio(void);

#endif  

