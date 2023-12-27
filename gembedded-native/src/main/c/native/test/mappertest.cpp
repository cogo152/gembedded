#include "mapper.h"

#include "commontest.hpp"

#define FILE_NAME ("/dev/gpiomem")
#define LENGTH (0xF4)
#define OFFSET (0)

#define INVALID_FILE_NAME ("/dev/invalidFile")
#define INVALID_LENGTH (0)

static void *pointer = NULL;

GCTEST_CASE(testMapBaseRegister)
{
    gctest_case_config_default(testMapBaseRegister);

    gctest_case_now
    {
        MAPPER_STATUS status;

        // MAPPER_FILE_NAME_ERROR : if the fileName is NULL.
        status = mapBaseRegister(NULL, LENGTH, OFFSET, &pointer);
        assert_equal(status, MAPPER_FILE_NAME_ERROR);

        // MAPPER_LENGTH_ERROR : if the length is less than 1.
        status = mapBaseRegister(FILE_NAME, INVALID_LENGTH, OFFSET, &pointer);
        assert_equal(status, MAPPER_LENGTH_ERROR);

        // MAPPER_POINTER_ERROR : if the pointer is NULL.
        status = mapBaseRegister(FILE_NAME, LENGTH, OFFSET, NULL);
        assert_equal(status, MAPPER_POINTER_ERROR);

        // MAPPER_FILE_OPEN_ERROR : if the fileName is invalid.
        status = mapBaseRegister(INVALID_FILE_NAME, LENGTH, OFFSET, &pointer);
        assert_equal(status, MAPPER_FILE_OPEN_ERROR);

        // MAPPER_MAP_ERROR : if the mapping fails.
        status = mapBaseRegister(FILE_NAME, LENGTH, 1, &pointer);
        assert_equal(status, MAPPER_MAP_ERROR);

        status = mapBaseRegister(FILE_NAME, LENGTH, OFFSET, &pointer);
        assert_equal(status, MAPPER_SUCCESS);
    }
};

GCTEST_CASE(testUnmapBaseRegister)
{
    gctest_case_config_default(testUnmapBaseRegister);

    gctest_case_now
    {
        MAPPER_STATUS status;

        void *nullPointer = NULL;

        void *invalidPointer = (void *)1;

        // MAPPER_POINTER_ERROR : if the **pointer is NULL.
        status = unmapBaseRegister(NULL, LENGTH);
        assert_equal(status, MAPPER_POINTER_ERROR);

        // MAPPER_POINTER_ERROR : if the *pointer is NULL.
        status = unmapBaseRegister(&nullPointer, LENGTH);
        assert_equal(status, MAPPER_POINTER_ERROR);

        // MAPPER_LENGTH_ERROR : if the length is less than 1.
        status = unmapBaseRegister(&pointer, INVALID_LENGTH);
        assert_equal(status, MAPPER_LENGTH_ERROR);

        // MAPPER_UNMAP_ERROR : if the unmapping fails.
        status = unmapBaseRegister(&invalidPointer, LENGTH);
        assert_equal(status, MAPPER_UNMAP_ERROR);

        status = unmapBaseRegister(&pointer, LENGTH);
        assert_equal(status, MAPPER_SUCCESS);
        // assert_equal(pointer, nullptr);
    }
};