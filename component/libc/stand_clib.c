/**
 *******************************************************************************
 * @file       stand_clib.c                                                    *
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
 * 2.参考自RT-Thread                                                           *
 *******************************************************************************
 */

/**
 * @defgroup std library component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "stand_clib.h"

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        内存操作API
 *******************************************************************************
 */
void *memset(void *s, int c, size_t n)
{
    char *xs = (char *)s;

    while (n--)
    {
        *xs++ = c;
	}
	
    return s;
}

void *memcpy(void * /*restrict */ dest, const void * /*restrict*/ src, size_t n)
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

void *memccpy(void */*restrict */ dest, const void * /*restrict*/ src, int c, size_t n)
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

void *memmove(void *dest, const void *src, size_t n)
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

int memcmp(const void *s1, const void *s2, size_t n)
{
    const char *su1 = (const char *)s1;
    const char *su2 = (const char *)s2;
    
    int res = 0;

    while (n--)
    {
        res = *su1 - *su2;
        
        if (res != 0)
        {
            return res;
		}
        
        su1 ++;
        su2 ++;
	}
	
    return 0;	
}

void *memchr(const void *s, int c, size_t n)
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

/**
 *******************************************************************************
 * @brief        字符串API
 *******************************************************************************
 */
char *strcpy(char * /*restrict*/ dest, const char * /*restrict*/ src)
{
	while (*dest++ = *src++);
	return dest - 1;
}

char *strncpy(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n)
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

char *strcat(char * /*restrict*/ dest, const char * /*restrict*/ src)
{
	register char *s  = dest;
    register const char *s2 = src;
    
	while (*s++);
	--s;
	
	while ((*s++ = *s2++) != 0);

	return dest;
}

char *strncat(char * /*restrict*/ dest, const char * /*restrict*/ src, size_t n)
{
	register char *s = dest;
    register const char *s2 = src;
    
	while (*s++);
	--s;
	
	while (n && ((*s = *s2++) != 0)) 
	{
		--n;
		++s;
	}
	
	*s = 0;

	return s;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
	}
	
    return (*s1 - *s2);
}

int strncmp(const char *s1, const char *s2, size_t n)
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

char *strchr(const char *s, int c)
{
	do
	{
		if (*s == (char)c)
		{
			return (char *)s;	/* silence the warning */
		}
	}while (*s++);

	return NULL;
}

size_t strcspn(const char *s1, const char *s2)
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

char *strpbrk(const char *s1, const char *s2)
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

char *strrchr(const char *s, int c)
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

size_t strspn (const char *s1, const char *s2)
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

char *strstr(const char *s1, const char *s2)
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

size_t strlen(const char *s)
{
	size_t len = 0;

	while(s[len++]);
	
	return len - 1;
}

//size_t u_strxfrm(char *dest, const char *src, size_t n)
//{
//	return 0;	
//}

//
//char *strtok(char * /* restrict*/ s1, const char * /*restrict*/ s2)
//{
//	return NULL;
//}

/**
 *******************************************************************************
 * @brief        标准输入输出API
 *******************************************************************************
 */
#define isdigit(c)  ((unsigned)((c) - '0') < 10)

__INLINE
int32_t divide(int32_t *n, int32_t base)
{
    int32_t res;

    /* optimized for processor which does not support divide instructions. */
    if (base == 10)
    {
        res = ((uint32_t) * n) % 10U;
        *n = ((uint32_t) * n) / 10U;
    }
    else
    {
        res = ((uint32_t) * n) % 16U;
        *n = ((uint32_t) * n) / 16U;
    }

    return res;
}

__INLINE
int skip_atoi(const char **s)
{
    register int i = 0;
    while (isdigit(**s))
        i = i * 10 + *((*s)++) - '0';

    return i;
}

#define ZEROPAD     (1 << 0)    /* pad with zero */
#define SIGN        (1 << 1)    /* unsigned/signed long */
#define PLUS        (1 << 2)    /* show plus */
#define SPACE       (1 << 3)    /* space if plus */
#define LEFT        (1 << 4)    /* left justified */
#define SPECIAL     (1 << 5)    /* 0x */
#define LARGE       (1 << 6)    /* use 'ABCDEF' instead of 'abcdef' */

#ifdef RT_PRINTF_PRECISION
static char *print_number(char *buf,
                          char *end,
                          long  num,
                          int   base,
                          int   s,
                          int   precision,
                          int   type)
#else
static char *print_number(char *buf,
                          char *end,
                          long  num,
                          int   base,
                          int   s,
                          int   type)
#endif
{
    char c, sign;
#ifdef RT_PRINTF_LONGLONG
    char tmp[32];
#else
    char tmp[16];
#endif
    const char *digits;
    static const char small_digits[] = "0123456789abcdef";
    static const char large_digits[] = "0123456789ABCDEF";
    register int i;
    register int size;

    size = s;

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
        type &= ~ZEROPAD;

    c = (type & ZEROPAD) ? '0' : ' ';

    /* get sign */
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
        }
        else if (type & PLUS)
            sign = '+';
        else if (type & SPACE)
            sign = ' ';
    }

#ifdef RT_PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
#endif

    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
    {
        while (num != 0)
            tmp[i++] = digits[divide(&num, base)];
    }

#ifdef RT_PRINTF_PRECISION
    if (i > precision)
        precision = i;
    size -= precision;
#else
    size -= i;
#endif

    if (!(type & (ZEROPAD | LEFT)))
    {
        if ((sign) && (size > 0))
            size--;

        while (size-- > 0)
        {
            if (buf <= end)
                *buf = ' ';
            ++ buf;
        }
    }

    if (sign)
    {
        if (buf <= end)
        {
            *buf = sign;
            -- size;
        }
        ++ buf;
    }

#ifdef RT_PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 8)
        {
            if (buf <= end)
                *buf = '0';
            ++ buf;
        }
        else if (base == 16)
        {
            if (buf <= end)
                *buf = '0';
            ++ buf;
            if (buf <= end)
            {
                *buf = type & LARGE ? 'X' : 'x';
            }
            ++ buf;
        }
    }
#endif

    /* no align to the left */
    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            if (buf <= end)
                *buf = c;
            ++ buf;
        }
    }

#ifdef RT_PRINTF_PRECISION
    while (i < precision--)
    {
        if (buf <= end)
            *buf = '0';
        ++ buf;
    }
#endif

    /* put number in the temporary buffer */
    while (i-- > 0)
    {
        if (buf <= end)
            *buf = tmp[i];
        ++ buf;
    }

    while (size-- > 0)
    {
        if (buf <= end)
            *buf = ' ';
        ++ buf;
    }

    return buf;
}

int32_t vsnprintf(char       *buf,
                  size_t   size,
                  const char *fmt,
                  va_list     args)
{
#ifdef RT_PRINTF_LONGLONG
    unsigned long long num;
#else
    uint32_t num;
#endif
    int i, len;
    char *str, *end, c;
    const char *s;

    uint8_t base;            /* the base of number */
    uint8_t flags;           /* flags to print number */
    uint8_t qualifier;       /* 'h', 'l', or 'L' for integer fields */
    int32_t field_width;     /* width of output field */

#ifdef RT_PRINTF_PRECISION
    int precision;      /* min. # of digits for integers and max for a string */
#endif

    str = buf;
    end = buf + size - 1;

    /* Make sure end is always >= buf */
    if (end < buf)
    {
        end  = ((char *) - 1);
        size = end - buf;
    }

    for (; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            if (str <= end)
                *str = *fmt;
            ++ str;
            continue;
        }

        /* process flags */
        flags = 0;

        while (1)
        {
            /* skips the first '%' also */
            ++ fmt;
            if (*fmt == '-') flags |= LEFT;
            else if (*fmt == '+') flags |= PLUS;
            else if (*fmt == ' ') flags |= SPACE;
            else if (*fmt == '#') flags |= SPECIAL;
            else if (*fmt == '0') flags |= ZEROPAD;
            else break;
        }

        /* get field width */
        field_width = -1;
        if (isdigit(*fmt)) field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++ fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

#ifdef RT_PRINTF_PRECISION
        /* get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++ fmt;
            if (isdigit(*fmt)) precision = skip_atoi(&fmt);
            else if (*fmt == '*')
            {
                ++ fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0) precision = 0;
        }
#endif
        /* get the conversion qualifier */
        qualifier = 0;
#ifdef RT_PRINTF_LONGLONG
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
#else
        if (*fmt == 'h' || *fmt == 'l')
#endif
        {
            qualifier = *fmt;
            ++ fmt;
#ifdef RT_PRINTF_LONGLONG
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++ fmt;
            }
#endif
        }

        /* the default base */
        base = 10;

        switch (*fmt)
        {
        case 'c':
            if (!(flags & LEFT))
            {
                while (--field_width > 0)
                {
                    if (str <= end) *str = ' ';
                    ++ str;
                }
            }

            /* get character */
            c = (uint8_t)va_arg(args, int);
            if (str <= end) *str = c;
            ++ str;

            /* put width */
            while (--field_width > 0)
            {
                if (str <= end) *str = ' ';
                ++ str;
            }
            continue;

        case 's':
            s = va_arg(args, char *);
            if (!s) s = "(NULL)";

            len = strlen(s);
#ifdef RT_PRINTF_PRECISION
            if (precision > 0 && len > precision) len = precision;
#endif

            if (!(flags & LEFT))
            {
                while (len < field_width--)
                {
                    if (str <= end) *str = ' ';
                    ++ str;
                }
            }

            for (i = 0; i < len; ++i)
            {
                if (str <= end) *str = *s;
                ++ str;
                ++ s;
            }

            while (len < field_width--)
            {
                if (str <= end) *str = ' ';
                ++ str;
            }
            continue;

        case 'p':
            if (field_width == -1)
            {
                field_width = sizeof(void *) << 1;
                flags |= ZEROPAD;
            }
#ifdef RT_PRINTF_PRECISION
            str = print_number(str, end,
                               (long)va_arg(args, void *),
                               16, field_width, precision, flags);
#else
            str = print_number(str, end,
                               (long)va_arg(args, void *),
                               16, field_width, flags);
#endif
            continue;

        case '%':
            if (str <= end) *str = '%';
            ++ str;
            continue;

        /* integer number formats - set up the flags and "break" */
        case 'o':
            base = 8;
            break;

        case 'X':
            flags |= LARGE;
        case 'x':
            base = 16;
            break;

        case 'd':
        case 'i':
            flags |= SIGN;
        case 'u':
            break;

        default:
            if (str <= end) *str = '%';
            ++ str;

            if (*fmt)
            {
                if (str <= end) *str = *fmt;
                ++ str;
            }
            else
            {
                -- fmt;
            }
            continue;
        }

#ifdef RT_PRINTF_LONGLONG
        if (qualifier == 'L') num = va_arg(args, long long);
        else if (qualifier == 'l')
#else
        if (qualifier == 'l')
#endif
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN) num = (int32_t)num;
        }
        else if (qualifier == 'h')
        {
            num = (uint16_t)va_arg(args, int32_t);
            if (flags & SIGN) num = (int16_t)num;
        }
        else
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN) num = (int32_t)num;
        }
#ifdef RT_PRINTF_PRECISION
        str = print_number(str, end, num, base, field_width, precision, flags);
#else
        str = print_number(str, end, num, base, field_width, flags);
#endif
    }

    if (str <= end) *str = '\0';
    else *end = '\0';

    /* the trailing null byte doesn't count towards the total
    * ++str;
    */
    return str - buf;
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param size the size of buffer
 * @param fmt the format
 */
int32_t snprintf(char *buf, size_t size, const char *fmt, ...)
{
    int32_t n;
    va_list args;

    va_start(args, fmt);
    n = vsnprintf(buf, size, fmt, args);
    va_end(args);

    return n;
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param arg_ptr the arg_ptr
 * @param format the format
 */
int32_t vsprintf(char *buf, const char *format, va_list arg_ptr)
{
    return vsnprintf(buf, (size_t) - 1, format, arg_ptr);
}

/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param format the format
 */
int32_t sprintf(char *buf, const char *format, ...)
{
    int32_t n;
    va_list arg_ptr;

    va_start(arg_ptr, format);
    n = vsprintf(buf, format, arg_ptr);
    va_end(arg_ptr);

    return n;
}

/** @}*/     /** std library component */

/**********************************END OF FILE*********************************/
