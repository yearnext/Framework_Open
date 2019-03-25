/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2018  Accumulate Team                  *
 *                                                                             *
 *      Licensed under the Apache License, Version 2.0 (the "License");        *
 *      you may not use this file except in compliance with the License.       *
 *      You may obtain a copy of the License at                                *
 *                 http://www.apache.org/licenses/LICENSE-2.0                  *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************
 * @file       libc.h                                                          *
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
 * 1.部分内容参考uClibc实现      						                       *
 *******************************************************************************
 */
 
/**
 * @defgroup std library component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UTILITY_STD_LIBRARY_H__
#define __UTILITY_STD_LIBRARY_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "..\compiler\compiler.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/ 
/* Exported functions --------------------------------------------------------*/
extern void *u_memcpy (void * /*restrict */ dest, const void * /*restrict*/ src, size_t n);
extern void *u_memccpy(void */*restrict */ dest, const void * /*restrict*/ src, int c, size_t n);
extern void *u_memmove (void *dest, const void *src, size_t n);
extern char *u_strcpy (char * /*restrict*/ dest, const char * /*restrict*/ src);
extern char *u_strncpy(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n);
extern char *u_strcat (char * /*restrict*/ dest, const char * /*restrict*/ src);
extern char *u_strncat(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n);
extern int u_memcmp (const void *s1, const void *s2, size_t n);
extern int u_strcmp (const char *s1, const char *s2);
extern int u_strncmp(const char *s1, const char *s2, size_t n);
//! todo: 待实�?
extern size_t u_strxfrm(char *dest, const char *src, size_t n);
extern void *u_memchr (const void *s, int c, size_t n);
extern char *u_strchr (const char *s, int c);
extern size_t u_strcspn(const char *s1, const char *s2);
extern char *u_strpbrk(const char *s1, const char *s2);
extern char *u_strrchr(const char *s, int c);
extern size_t u_strspn (const char *s1, const char *s2);
extern char *u_strstr(const char *s1, const char *s2);
extern char *u_strtok(char * /* restrict*/ s1, const char * /*restrict*/ s2);
extern void *u_memset(void *s, int c, size_t n);
extern size_t u_strlen(const char *s);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** std library component */

/**********************************END OF FILE*********************************/
