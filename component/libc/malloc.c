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
 * @file       fw_memory.c                                                     *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-20                                                      *
 * @brief      memory component source files                                   *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. The implementation of the function "plug_holes","_heap_init","_malloc",  *
 *    "_free", "_realloc","_calloc" comes from the Internet.                   *
 *******************************************************************************
 */

/**
 * @defgroup framework memory component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "fw_core.h"

/* Private define ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        memory heap magic value
 *******************************************************************************
 */
#define HEAP_MAGIC                                                      (0x1EA0)

/**
 *******************************************************************************
 * @brief        define min memory block size 
 *******************************************************************************
 */
#define MIN_SIZE                                                            (16)
#define MIN_SIZE_ALIGNED                 __ALIGN(MIN_SIZE, FW_MEMORY_ALIGN_SIZE)

/**
 *******************************************************************************
 * @brief        define memory block size
 *******************************************************************************
 */
#define SIZEOF_STRUCT_MEM __ALIGN(sizeof(struct heap_mem), FW_MEMORY_ALIGN_SIZE)

/* Private typedef -----------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        heap memory structure
 *******************************************************************************
 */
struct heap_mem
{
    /* magic and used flag */
    uint16_t magic;
    uint16_t used;

    size_t next, prev;
};

/* Private variables ---------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        define ysf memory management vailables
 *******************************************************************************
 */
#if ENABLE_FRAMEWORK_MEMORY_MANAGEMENT
//< pointer to the heap: for alignment, heap_ptr is now a pointer instead of an array
static uint8_t *heap_ptr;

//< the last entry, always unused!
static struct heap_mem *heap_end;

//< pointer to the lowest free block
static struct heap_mem *lfree;

//< memory align size
static size_t mem_size_aligned;

#ifndef USE_HEAP_MEMORY
static uint8_t SRAM_MEMORY[FW_MEMORY_POOL_SIZE];
#endif

#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#if ENABLE_FRAMEWORK_MEMORY_MANAGEMENT
/**
 *******************************************************************************
 * @brief       plug holes
 * @param       [in/out]  *mem              memory address
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE 
void plug_holes(struct heap_mem *mem)
{
    struct heap_mem *nmem;
    struct heap_mem *pmem;

    FW_ASSERT((uint8_t *)mem >= heap_ptr);
    FW_ASSERT((uint8_t *)mem < (uint8_t *)heap_end);
    FW_ASSERT(mem->used == 0);

    /* plug hole forward */
    nmem = (struct heap_mem *)&heap_ptr[mem->next];
    
    if (mem != nmem && nmem->used == 0 && (uint8_t *)nmem != (uint8_t *)heap_end)
    {
        /* if mem->next is unused and not end of heap_ptr,
         * combine mem and mem->next
         */
        if (lfree == nmem)
        {
            lfree = mem;
        }
        
        mem->next = nmem->next;
        
        ((struct heap_mem *)&heap_ptr[nmem->next])->prev = (uint8_t *)mem - heap_ptr;
    }

    /* plug hole backward */
    pmem = (struct heap_mem *)&heap_ptr[mem->prev];
    
    if (pmem != mem && pmem->used == 0)
    {
        /* if mem->prev is unused, combine mem and mem->prev */
        if (lfree == mem)
        {
            lfree = pmem;
        }
        
        pmem->next = mem->next;
        
        ((struct heap_mem *)&heap_ptr[mem->next])->prev = (uint8_t *)pmem - heap_ptr;
    }
}

/**
 *******************************************************************************
 * @brief       memory heap init
 * @param       [in/out]  *begin_addr       heap memory begin address
 * @param       [in/out]  *end_addr         heap memory end address
 * @return      [in/out]  void*             alloc memory point
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _heap_init(void *begin_addr, void *end_addr)
{
    struct heap_mem *mem;
    uint32_t begin_align = __ALIGN((uint32_t)begin_addr, FW_MEMORY_ALIGN_SIZE);
    uint32_t end_align = __ALIGN_DOWN((uint32_t)end_addr, FW_MEMORY_ALIGN_SIZE);

    /* alignment addr */
    if ((end_align > (2 * SIZEOF_STRUCT_MEM))
        && ((end_align - 2 * SIZEOF_STRUCT_MEM) >= begin_align))
    {
        /* calculate the aligned memory size */
        mem_size_aligned = end_align - begin_align - 2 * SIZEOF_STRUCT_MEM;
    }
    else
    {
        return;
    }

    /* point to begin address of heap */
    heap_ptr = (uint8_t *)begin_align;

    /* initialize the start of the heap */
    mem        = (struct heap_mem *)heap_ptr;
    mem->magic = HEAP_MAGIC;
    mem->next  = mem_size_aligned + SIZEOF_STRUCT_MEM;
    mem->prev  = 0;
    mem->used  = 0;

    /* initialize the end of the heap */
    heap_end        = (struct heap_mem *)&heap_ptr[mem->next];
    heap_end->magic = HEAP_MAGIC;
    heap_end->used  = 1;
    heap_end->next  = mem_size_aligned + SIZEOF_STRUCT_MEM;
    heap_end->prev  = mem_size_aligned + SIZEOF_STRUCT_MEM;

    /* initialize the lowest-free pointer to the start of the heap */
    lfree = (struct heap_mem *)heap_ptr;
}

/**
 *******************************************************************************
 * @brief       alloc memory
 * @param       [in/out]  size              alloc memory size
 * @return      [in/out]  void*             alloc memory point
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void *_malloc(size_t size)
{
    size_t ptr, ptr2;
    struct heap_mem *mem, *mem2;

    if (size == 0)
        return NULL;

    /* alignment size */
    size = __ALIGN(size, FW_MEMORY_ALIGN_SIZE);

    if (size > mem_size_aligned)
    {
        return NULL;
    }

    /* every data block must be at least MIN_SIZE_ALIGNED long */
    if (size < MIN_SIZE_ALIGNED)
    {
        size = MIN_SIZE_ALIGNED;
    }

    for (ptr = (uint8_t *)lfree - heap_ptr; ptr < mem_size_aligned - size; ptr = ((struct heap_mem *)&heap_ptr[ptr])->next)
    {
        mem = (struct heap_mem *)&heap_ptr[ptr];

        if ((!mem->used) && (mem->next - (ptr + SIZEOF_STRUCT_MEM)) >= size)
        {
            /* mem is not used and at least perfect fit is possible:
             * mem->next - (ptr + SIZEOF_STRUCT_MEM) gives us the 'user data size' of mem */

            if (mem->next - (ptr + SIZEOF_STRUCT_MEM) >=
                (size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED))
            {
                /* (in addition to the above, we test if another struct heap_mem (SIZEOF_STRUCT_MEM) containing
                 * at least MIN_SIZE_ALIGNED of data also fits in the 'user data space' of 'mem')
                 * -> split large block, create empty remainder,
                 * remainder must be large enough to contain MIN_SIZE_ALIGNED data: if
                 * mem->next - (ptr + (2*SIZEOF_STRUCT_MEM)) == size,
                 * struct heap_mem would fit in but no data between mem2 and mem2->next
                 * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
                 *       region that couldn't hold data, but when mem->next gets freed,
                 *       the 2 regions would be combined, resulting in more free memory
                 */
                ptr2 = ptr + SIZEOF_STRUCT_MEM + size;

                /* create mem2 struct */
                mem2       = (struct heap_mem *)&heap_ptr[ptr2];
                mem2->magic = HEAP_MAGIC;
                mem2->used = 0;
                mem2->next = mem->next;
                mem2->prev = ptr;

                /* and insert it between mem and mem->next */
                mem->next = ptr2;
                mem->used = 1;

                if (mem2->next != mem_size_aligned + SIZEOF_STRUCT_MEM)
                {
                    ((struct heap_mem *)&heap_ptr[mem2->next])->prev = ptr2;
                }
            }
            else
            {
                /* (a mem2 struct does no fit into the user data space of mem and mem->next will always
                 * be used at this point: if not we have 2 unused structs in a row, plug_holes should have
                 * take care of this).
                 * -> near fit or excact fit: do not split, no mem2 creation
                 * also can't move mem->next directly behind mem, since mem->next
                 * will always be used at this point!
                 */
                mem->used = 1;
            }
            /* set memory block magic */
            mem->magic = HEAP_MAGIC;

            if (mem == lfree)
            {
                /* Find next free block after mem and update lowest free pointer */
                while (lfree->used && lfree != heap_end)
                {
                    lfree = (struct heap_mem *)&heap_ptr[lfree->next];
                }

                FW_ASSERT(((lfree == heap_end) || (!lfree->used)));
            }

            FW_ASSERT((uint32_t)mem + SIZEOF_STRUCT_MEM + size <= (uint32_t)heap_end);
            FW_ASSERT((uint32_t)((uint8_t *)mem + SIZEOF_STRUCT_MEM) % FW_MEMORY_ALIGN_SIZE == 0);
            FW_ASSERT((((uint32_t)mem) & (FW_MEMORY_ALIGN_SIZE-1)) == 0);

            /* return the memory data except mem struct */
            return (uint8_t *)mem + SIZEOF_STRUCT_MEM;
        }
    }
    
    return NULL;
}

/**
 *******************************************************************************
 * @brief       free memory
 * @param       [in/out]  *memory            free memory point
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__STATIC_INLINE
void _free(void *rmem)
{
    struct heap_mem *mem;

    if (rmem == NULL)
        return;
    FW_ASSERT((((uint32_t)rmem) & (FW_MEMORY_ALIGN_SIZE-1)) == 0);
    FW_ASSERT((uint8_t *)rmem >= (uint8_t *)heap_ptr &&
              (uint8_t *)rmem < (uint8_t *)heap_end);

    if ((uint8_t *)rmem < (uint8_t *)heap_ptr || (uint8_t *)rmem >= (uint8_t *)heap_end)
    {
        return;
    }

    /* Get the corresponding struct heap_mem ... */
    mem = (struct heap_mem *)((uint8_t *)rmem - SIZEOF_STRUCT_MEM);

    /* ... which has to be in a used state ... */
    FW_ASSERT(mem->used);
    FW_ASSERT(mem->magic == HEAP_MAGIC);
    
    /* ... and is now unused. */
    mem->used  = 0;
    mem->magic = HEAP_MAGIC;

    if (mem < lfree)
    {
        /* the newly freed struct is now the lowest */
        lfree = mem;
    }

    /* finally, see if prev or next are free also */
    plug_holes(mem);
}

///**
// *******************************************************************************
// * @brief       realloc memory
// * @param       [in/out]  size              realloc memory size
// * @return      [in/out]  void*             realloc memory point
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE
//void *_realloc(void *rmem, size_t newsize)
//{
//    size_t size;
//    size_t ptr, ptr2;
//    struct heap_mem *mem, *mem2;
//    void *nmem;

//    /* alignment size */
//    newsize = __ALIGN(newsize, FW_MEMORY_ALIGN_SIZE);
//    
//    if (newsize > mem_size_aligned)
//    {
//        return NULL;
//    }

//    /* allocate a new memory block */
//    if (rmem == NULL)
//    {
//        return _malloc(newsize);
//    }

//    if ((uint8_t *)rmem < (uint8_t *)heap_ptr || (uint8_t *)rmem >= (uint8_t *)heap_end)
//    {
//        return rmem;
//    }

//    mem = (struct heap_mem *)((uint8_t *)rmem - SIZEOF_STRUCT_MEM);

//    ptr = (uint8_t *)mem - heap_ptr;
//    size = mem->next - ptr - SIZEOF_STRUCT_MEM;
//    if (size == newsize)
//    {
//        return rmem;
//    }

//    if (newsize + SIZEOF_STRUCT_MEM + MIN_SIZE < size)
//    {
//        ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
//        mem2 = (struct heap_mem *)&heap_ptr[ptr2];
//        mem2->magic= HEAP_MAGIC;
//        mem2->used = 0;
//        mem2->next = mem->next;
//        mem2->prev = ptr;
//        mem->next = ptr2;
//        if (mem2->next != mem_size_aligned + SIZEOF_STRUCT_MEM)
//        {
//            ((struct heap_mem *)&heap_ptr[mem2->next])->prev = ptr2;
//        }

//        plug_holes(mem2);

//        return rmem;
//    }

//    /* expand memory */
//    nmem = _malloc(newsize);
//    
//    if (nmem != NULL) /* check memory */
//    {
//        memcpy(nmem, rmem, size < newsize ? size : newsize);
//        _free(rmem);
//    }

//    return nmem;
//}

///**
// *******************************************************************************
// * @brief       calloc memory
// * @param       [in/out]  size              calloc memory size
// * @return      [in/out]  void*             calloc memory point
// * @note        None
// *******************************************************************************
// */
//__STATIC_INLINE
//void *_calloc(size_t count, size_t size)
//{
//    void *p;

//    /* allocate 'count' objects of size 'size' */
//    p = _malloc(count * size);

//    /* zero the memory */
//    if (p)
//    {
//        memset(p, 0, count * size);
//    }

//    return p;
//}

/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       init ysf memory 
 * @param       [in/out]  void
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Mem_InitCmpt(void)
{
#ifndef USE_HEAP_MEMORY
    _heap_init((void *)&SRAM_MEMORY, (void *)MCU_SRAM_END_ADDR);
#else
    _heap_init((void *)__HEAP_HEAD_ADDR, (void *)MCU_SRAM_END_ADDR);
#endif
}

/**
 *******************************************************************************
 * @brief       allocating memory
 * @param       [in/out]  size               allocated memory size
 * @return      [in/out]  void*              return allocated memory
 * @note        None
 *******************************************************************************
 */
void *Fw_Mem_Alloc(size_t size)
{
    return _malloc(size);
}

/**
 *******************************************************************************
 * @brief       free memory
 * @param       [in/out]  *memory            free memory pointer
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
void Fw_Mem_Free(void *memory)
{
    _free(memory);
}

/**
 *******************************************************************************
 * @brief       detecting the memory is in memory pool
 * @param       [in/out]  void*             wait detect memory
 * @return      [in/out]  false             the memory not in memory pool
 * @return      [in/out]  true              the memory is in memory pool
 * @note        None
 *******************************************************************************
 */
bool Fw_Mem_IsIn(void *memory)
{
    if(IS_PTR_NULL(heap_ptr) || IS_PTR_NULL(memory))
    {
        return false;
    }
    
    if(memory > (void *)heap_ptr && memory < (void *)heap_end)
    {
        return true;
    }
    
    return false;
}

#endif

/** @}*/     /** framework memory component */

/**********************************END OF FILE*********************************/
