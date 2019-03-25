/**
 *******************************************************************************
 * @file       stand_clib.h                                                    *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      std library component head files                                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.参考自uClibc开源库                                                        *
 * 2.参考自RT-Thread                                                           *
 *******************************************************************************
 */
 
/**
 * @defgroup std library component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STDAND_C_LIBRARY_H__
#define __STDAND_C_LIBRARY_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        内存操作API
 *******************************************************************************
 */
extern void   *memset(void *s, int c, size_t n);
extern void   *memcpy(void * /*restrict */ dest, const void * /*restrict*/ src, size_t n);
extern void   *memccpy(void */*restrict */ dest, const void * /*restrict*/ src, int c, size_t n);
extern void   *memmove(void *dest, const void *src, size_t n);
extern int     memcmp(const void *s1, const void *s2, size_t n);
extern void   *memchr(const void *s, int c, size_t n);

/**
 *******************************************************************************
 * @brief        字符串API
 *******************************************************************************
 */
extern char   *strcpy(char * /*restrict*/ dest, const char * /*restrict*/ src);
extern char   *strncpy(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n);
extern char   *strcat(char * /*restrict*/ dest, const char * /*restrict*/ src);
extern char   *strncat(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n);
extern int     strcmp(const char *s1, const char *s2);
extern int     strncmp(const char *s1, const char *s2, size_t n);
extern char   *strchr(const char *s, int c);
extern size_t  strcspn(const char *s1, const char *s2);
extern char   *strpbrk(const char *s1, const char *s2);
extern char   *strrchr(const char *s, int c);
extern size_t  strspn (const char *s1, const char *s2);
extern char   *strstr(const char *s1, const char *s2);
extern size_t  strlen(const char *s);

/**
 *******************************************************************************
 * @brief        标准输入输出API
 *******************************************************************************
 */
extern int32_t vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
extern int32_t snprintf(char *buf, size_t size, const char *fmt, ...);
extern int32_t vsprintf(char *buf, const char *format, va_list arg_ptr);
extern int32_t sprintf(char *buf, const char *format, ...);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** std library component */

/**********************************END OF FILE*********************************/
