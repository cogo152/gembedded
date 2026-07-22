#include <gctest/core/core.hpp>

#include "jvm.hpp"
#include "devicedrivertest.hpp"

int main()
{
    GCTEST_SUIT_BEGIN(test suit, 1, 9, 1);
    GCTEST_SUIT_ADD_START_COMMAND(createJVM);
    GCTEST_SUIT_ADD_TEST_CASE(testInitDriverSuite);
    GCTEST_SUIT_ADD_TEST_CASE(testSetupDeviceDriver);
    GCTEST_SUIT_ADD_TEST_CASE(testGetDeviceName);
    GCTEST_SUIT_ADD_TEST_CASE(testRequestGPIOOBase);
    GCTEST_SUIT_ADD_TEST_CASE(testRequestClockBase);
    GCTEST_SUIT_ADD_TEST_CASE(testRequestPWMBase);
    GCTEST_SUIT_ADD_TEST_CASE(testRequestI2CMasterBase);
    GCTEST_SUIT_ADD_TEST_CASE(testShutdownDeviceDriver);
    GCTEST_SUIT_ADD_TEST_CASE(testCleanupDeviceDriverSuite);
    GCTEST_SUIT_ADD_STOP_COMMAND(destroyJVM);
    GCTEST_SUIT_ENABLE_PRINT();
    GCTEST_SUIT_EXECUTE();
    GCTEST_SUIT_END();
}