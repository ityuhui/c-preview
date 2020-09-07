#ifndef _WATCH_UTIL_H
#define _WATCH_UTIL_H

#ifdef  __cplusplus
extern "C" {
#endif

void kubernets_watch_handler(void** pData, long* pDataLen, void (*event_hander)(const char*));

#ifdef  __cplusplus
}
#endif
#endif                          /* _WATCH_UTIL_H */
