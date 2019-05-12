#ifndef WATER_MEMORY_ALLOCATOR_CONFIG_H
#define WATER_MEMORY_ALLOCATOR_CONFIG_H
#include "common/memory_allocate_policy.h"
#include "common/memory_allocator.h"

namespace water
{
    typedef AlignedMemoryAllocatePolicy<16> Aligned16MemoryAllocatePolicy;

    typedef AllocatedObject<Aligned16MemoryAllocatePolicy> Aligned16AllocatedObject;
}

#endif
