#include "mapper.h"

MAPPER_STATUS
mapBaseRegister(const char *const fileName, size_t const length, off_t const offset, void **const pointer)
{

    if (fileName == NULL)
    {
        return MAPPER_FILE_NAME_ERROR;
    }

    if (length < 1)
    {
        return MAPPER_LENGTH_ERROR;
    }

    if (pointer == NULL)
    {
        return MAPPER_POINTER_ERROR;
    }

    int const memoryFileDescriptor = open(fileName, FILE_FLAG);

    if (memoryFileDescriptor < 0)
    {
        close(memoryFileDescriptor);
        return MAPPER_FILE_OPEN_ERROR;
    }

    void *const ptr = mmap(NULL, length, PROT_FLAG, MAP_FLAG, memoryFileDescriptor, offset);
    if (ptr == MAP_FAILED)
    {
        close(memoryFileDescriptor);
        *pointer = NULL;
        return MAPPER_MAP_ERROR;
    }
    else
    {
        *pointer = ptr;
    }

    close(memoryFileDescriptor);

    return MAPPER_SUCCESS;
}

MAPPER_STATUS unmapBaseRegister(void **const pointer, size_t const length)
{

    if (pointer == NULL)
    {
        return MAPPER_POINTER_ERROR;
    }

    if (*pointer == NULL)
    {
        return MAPPER_POINTER_ERROR;
    }

    if (length < 1)
    {
        return MAPPER_LENGTH_ERROR;
    }

    int const memoryUnmapResult = munmap(*pointer, length);

    if (memoryUnmapResult < 0)
    {
        return MAPPER_UNMAP_ERROR;
    }
    else
    {
        *pointer = NULL;
    }

    return MAPPER_SUCCESS;
}