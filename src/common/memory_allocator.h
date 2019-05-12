#ifndef WATER_MEMORY_ALLOCATOR_H
#define WATER_MEMORY_ALLOCATOR_H

namespace water
{
    template<class Allocator>
    class AllocatedObject
    {
        void* operator new(size_t size)
        {
            return Allocator::allocate(size);
        }

        void* operator new[] (size_t size)
        {
            return Allocator::allocate(size);
        }

        void operator delete(void* ptr)
        {
            Allocator::deallocate(ptr);
        }

        void operator delete[] (void* ptr)
        {
            Allocator::deallocate(ptr);
        }

    };
}

#endif