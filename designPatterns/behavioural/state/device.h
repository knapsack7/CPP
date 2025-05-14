#pragma once
#include "device_state.h"
#include <memory>

class Device{
private:
    std::unique_ptr<DeviceState> state;
public:
    Device(std::unique_ptr<DeviceState> initialState);
    void setState(std::unique_ptr<DeviceState> newState);
    void handle();
};
