#ifndef WEAVE_PLATFORM_INTERNAL_H
#define WEAVE_PLATFORM_INTERNAL_H

#include <WeavePlatform.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/tcpip.h"
#include "arch/sys_arch.h"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"


using namespace ::nl::Weave;

namespace WeavePlatform {
namespace Internal {

struct WeavePlatformEvent
{
    enum
    {
        kEventType_WeaveSystemLayerEvent                = 0,
        kEventType_ESPSystemEvent                       = 1,
        kEventType_CallWorkFunct                        = 2,
    };

    union
    {
        struct
        {
            nl::Weave::System::EventType Type;
            nl::Weave::System::Object * Target;
            uintptr_t Argument;
        } WeaveSystemLayerEvent;
        system_event_t ESPSystemEvent;
        struct
        {
            PlatformManager::AsyncWorkFunct WorkFunct;
            intptr_t Arg;
        } CallWorkFunct;
    };
    uint8_t Type;
};

extern const char * const TAG;

#if WEAVE_PLATFORM_CONFIG_ENABLE_TEST_DEVICE_IDENTITY
extern const uint64_t TestDeviceId;
extern const uint8_t TestDeviceCert[];
extern const uint8_t TestDevicePrivateKey[];
extern const uint16_t TestDeviceCertLength;
extern const uint16_t TestDevicePrivateKeyLength;
#endif // WEAVE_PLATFORM_CONFIG_ENABLE_TEST_DEVICE_IDENTITY

} // namespace Internal
} // namespace WeavePlatform

#endif // WEAVE_PLATFORM_ESP32_INTERNAL_H
