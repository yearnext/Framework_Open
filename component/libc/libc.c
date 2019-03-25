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
 * @file       libc.c                                                          *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-09-17                                                      *
 * @brief      std library component source files                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.参考自uClibc开源库                                                        *
 *******************************************************************************
 */

/**
 * @defgroup std library component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "libc.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void *u_memcpy (void * /*restrict */ dest, const void * /*restrict*/ src, size_t n)
{
	char *s1 = (char *)dest;
	char *s2 = (char *)src;

	if (n)
	{
		while (n--)
		{
			*s1++ = *s2++;
		}
		
		return (void *)(s1 - 1);
	}

	return dest;
}

void *u_memccpy(void */*restrict */ dest, const void * /*restrict*/ src, int c, size_t n)
{
	char *s1 = (char *)dest;
	char *s2 = (char *)src;

	if (n)
	{
		while (n--)
		{
			if ((*s1++ = *s2++) == (char)c)
			{
				return (void *)(s1);
			}
		}
	}

	return NULL;
}

void *u_memmove (void *dest, const void *src, size_t n)
{
    char *s1 = (char *)dest;
    char *s2 = (char *)src;

    if (s2 < s1 && s1 < s2 + n)
    {
        s1 += n;
        s2 += n;

        while (n--)
        {
            *(--s1) = *(--s2);
        }
    }
    else
    {
        while (n--)
        {
            *s1++ = *s2++;
        }
    }

    return dest;
}

char *u_strcpy (char * /*restrict*/ dest, const char * /*restrict*/ src)
{
	while (*dest++ = *src++);
	return dest - 1;
}

char *u_strncpy(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n)
{
	char *s1 = dest;
	const char *s2 = src;
        
    if (n != 0)
    {
        do
        {
            if ((*s1++ = *s2++) == 0)
            {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                {
                    *s1++ = 0;
                }
                
                break;
            }
        } while (--n != 0);
    }

    return dest;
}

char *u_strcat (char * /*restrict*/ dest, const char * /*restrict*/ src)
{
	register char *s = dest;

	while (*s++);
	--s;
	
	while ((*s++ = *s2++) != 0);

	return dest;
}

char *u_strncat(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n)
{
	register char *s = dest;

	while (*s++);
	--s;
	
	while (n && ((*s = *src++) != 0)) 
	{
		--n;
		++s;
	}
	
	*s = 0;

	return src;
}

int u_memcmp (const void *s1, const void *s2, size_t n)
{
    const unsigned char *su1, *su2;
    int res = 0;

    for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
    {
        if ((res = *su1 - *su2) != 0)
        {
            break;
		}
	}
	
    return res;	
}

int u_strcmp (const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
	}
	
    return (*s1 - *s2);
}

int u_strncmp(const char *s1, const char *s2, size_t n)
{
	char temp = 0;
	
	while (n--)
    {
        if ((temp = *s1 - *s2++) != 0 || !*s1++)
        {
            break;
        }
    }

    return temp;
}

//! todo: 寰呭疄鐜?
size_t u_strxfrm(char *dest, const char *src, size_t n)
{
	return 0;	
}

void *u_memchr (const void *s, int c, size_t n)
{
	register const char *r = (const char *)s;

	while (n) 
	{
		if (*r == (char)c) 
		{
			return (void *)r;	/* silence the warning */
		}
		
		++r;
		--n;
	}

	return NULL;
}

char *u_strchr (const char *s, int c)
{
	do
	{
		if (*s == (char)c)
		{
			return s;	/* silence the warning */
		}
	}while (*s++);

	return NULL;
}

size_t u_strcspn(const char *s1, const char *s2)
{
	register const char *s;
	register const char *p;

	for (s = s1; *s; s++) 
	{
		for (p = s2; *p; p++) 
		{
			if (*p == *s)
			{
				goto done;
			}
		}
	}
	
done:
	return s - s1;
}

char *u_strpbrk(const char *s1, const char *s2)
{
	register const char *s;
	register const char *p;

	for (s = s1; *s; s++) 
	{
		for (p = s2; *p; p++) 
		{
			if (*p == *s)
			{
				return (char *) s; /* silence the warning */
			}
		}
	}
	return NULL;
}

char *u_strrchr(const char *s, int c)
{
	register const char *p = NULL;

	do 
	{
		if (*s == (char) c) 
		{
			p = s;
		}
	}while(*s++);

	return (char *) p;			/* silence the warning */
}

size_t u_strspn (const char *s1, const char *s2)
{
	register const char *s = s1;
	register const char *p = s2;

	while (*p) 
	{
		if (*p++ == *s) 
		{
			++s;
			p = s2;
		}
	}
	return s - s1;
}

char *u_strstr(const char *s1, const char *s2)
{
	register const char *s = s1;
	register const char *p = s2;

	do 
	{
		if (!*p) 
		{
			return (char *) s1;
		}
		
		if (*p == *s) 
		{
			++p;
			++s;
		} 
		else 
		{
			p = s2;
			
			if (!*s) 
			{
				return NULL;
			}
			
			s = ++s1;
		}
	}while(1);
}

char *u_strtok(char * /* restrict*/ s1, const char * /*restrict*/ s2)
{
	static char *next_start;
	
	register char *s;
	register char *p;
	
	if (((s = s1) != NULL) || ((s = *next_start) != NULL)) 
	{
		if (*(s += u_strspn(s, s2))) 
		{
			if ((p = u_strpbrk(s, s2)) != NULL) 
			{
				*p++ = 0;
			}
		} 
		else 
		{
			p = s = NULL;
		}
		
		*next_start = p;
	}
	
	return s;
}

void *u_memset(void *s, int c, size_t n)
{
    char *xs = (char *)s;

    while (n--)
    {
        *xs++ = c;
	}
	
    return s;
}

size_t u_strlen(const char *s)
{
	size_t len = 0;

	while(s[len++]);
	
	return len - 1;
}

/** @}*/     /** std library component */

/**********************************END OF FILE*********************************/
