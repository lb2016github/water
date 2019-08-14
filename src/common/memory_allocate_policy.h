#ifndef WATER_MEMORY_ALLOCATE_POLICY_H
#define WATER_MEMORY_ALLOCATE_POLICY_H

#include <stdlib.h>

namespace water
{

    class MemoryAllocatePolicy
    {
	public:
        static void* allocate(size_t size)
        {
            void* ptr = malloc(size);
            return ptr;
        }

        static void deallocate(void* ptr)
        {
            free(ptr);
        }
    };

    template<size_t alignment = 0>
    class AlignedMemoryAllocatePolicy
    {
	public:
        static void* allocate(size_t size)
        {
            // allocate memory with additional Aligh bytes
            size_t new_size = size + alignment;
            void* ptr = malloc(new_size);

            // do alignment
            size_t offset = Align - (((size_t)ptr) & (alignment - 1));
            void* aligned_ptr = ptr + offset;

            // save meta data
            *(char*)(aligned_ptr - 1) = offset;

            return aligned_ptr;
        }
        static void deallocate(void* ptr)
        {
            size_t offset = *((char*)ptr - 1);
            void* ori_ptr = (char*)ptr - offset;
            free(ori_ptr);
        }
    };
}

#endif