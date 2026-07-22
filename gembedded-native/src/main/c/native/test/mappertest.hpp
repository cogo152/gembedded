#pragma once

#include <gctest/core/core.hpp>

#include "mapper.h"

#define FILE_NAME ("/dev/gpiomem")
#define LENGTH (0xF4)
#define OFFSET (0)

#define INVALID_FILE_NAME ("/dev/invalidFile")
#define INVALID_LENGTH (0)

static void *pointer = NULL;

Gctest_Case(testMapBaseRegister)
{
    Gctest_Case_Ctor(testMapBaseRegister);

    Gctest_Case_Assert()
    {
        MAPPER_STATUS status;

        // MAPPER_FILE_NAME_ERROR : if the fileName is NULL.
        status = mapBaseRegister(NULL, LENGTH, OFFSET, &pointer);
        gctest_case_assert_equal(status, MAPPER_FILE_NAME_ERROR);

        // MAPPER_LENGTH_ERROR : if the length is less than 1.
        status = mapBaseRegister(FILE_NAME, INVALID_LENGTH, OFFSET, &pointer);
        gctest_case_assert_equal(status, MAPPER_LENGTH_ERROR);

        // MAPPER_POINTER_ERROR : if the pointer is NULL.
        status = mapBaseRegister(FILE_NAME, LENGTH, OFFSET, NULL);
        gctest_case_assert_equal(status, MAPPER_POINTER_ERROR);

        // MAPPER_FILE_OPEN_ERROR : if the fileName is invalid.
        status = mapBaseRegister(INVALID_FILE_NAME, LENGTH, OFFSET, &pointer);
        gctest_case_assert_equal(status, MAPPER_FILE_OPEN_ERROR);

        // MAPPER_MAP_ERROR : if the mapping fails.
        status = mapBaseRegister(FILE_NAME, LENGTH, 1, &pointer);
        gctest_case_assert_equal(status, MAPPER_MAP_ERROR);

        status = mapBaseRegister(FILE_NAME, LENGTH, OFFSET, &pointer);
        gctest_case_assert_equal(status, MAPPER_SUCCESS);
    }
};

Gctest_Case(testUnmapBaseRegister)
{
    Gctest_Case_Ctor(testUnmapBaseRegister);

    Gctest_Case_Assert()
    {
        MAPPER_STATUS status;

        void *nullPointer = NULL;

        void *invalidPointer = (void *)1;

        // MAPPER_POINTER_ERROR : if the **pointer is NULL.
        status = unmapBaseRegister(NULL, LENGTH);
        gctest_case_assert_equal(status, MAPPER_POINTER_ERROR);

        // MAPPER_POINTER_ERROR : if the *pointer is NULL.
        status = unmapBaseRegister(&nullPointer, LENGTH);
        gctest_case_assert_equal(status, MAPPER_POINTER_ERROR);

        // MAPPER_LENGTH_ERROR : if the length is less than 1.
        status = unmapBaseRegister(&pointer, INVALID_LENGTH);
        gctest_case_assert_equal(status, MAPPER_LENGTH_ERROR);

        // MAPPER_UNMAP_ERROR : if the unmapping fails.
        status = unmapBaseRegister(&invalidPointer, LENGTH);
        gctest_case_assert_equal(status, MAPPER_UNMAP_ERROR);

        status = unmapBaseRegister(&pointer, LENGTH);
        gctest_case_assert_equal(status, MAPPER_SUCCESS);
        // assert_equal(pointer, nullptr);
    }
};