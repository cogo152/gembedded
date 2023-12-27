#include "commontest.hpp"
#include "jvm_test.h"

GCTEST_SUIT_NAME("gembedded-native test");

GCTEST_SUIT_MULTITHREADED(GCTEST_FALSE);

GCTEST_SUIT_ADD_START_COMMAND(CreateJVM, 1)
{
    createJVM();
}

GCTEST_SUIT_ADD_STOP_COMMAND(DestroyJVM, 2)
{
    destroyJVM();
}