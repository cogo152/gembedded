#ifndef DEVICE_DRIVER_H
#define DEVICE_DRIVER_H

#include "com_comert_gembedded_device_nativeinterface_DeviceDriver.h"
#include "common.h"
#include "jniutil.h"
#include "mapper.h"

#include <unistd.h>

#define DEVICE_NAME ("RaspberryPi-4B")
#define CORE_CLOCK_SPEED (1500000000U)

#define MEMORY_FILE_NAME ("/dev/mem")
#define PERIPHERAL_BASE_ADDRESS (0xFE000000)
#define BLOCK_SIZE (0X1000)

#define GPIO_BASE_ADDRESS (PERIPHERAL_BASE_ADDRESS + 0x00200000)
#define CLOCK_BASE_ADDRESS (PERIPHERAL_BASE_ADDRESS + 0x00101000)
#define PWM_BASE_ADDRESS (PERIPHERAL_BASE_ADDRESS + 0x0020c000)
#define I2CMASTER_BASE_ADDRESS (PERIPHERAL_BASE_ADDRESS + 0x804000)

#ifdef __cplusplus
extern "C"
{
#endif

    void *requestGPIOOBase(void);

    void *requestClockBase(void);

    void *requestPWMBase(void);

    void *requestI2CMasterBase(void);

#ifdef __cplusplus
}
#endif

#endif
