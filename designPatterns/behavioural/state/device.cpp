#include "device.h"

Device::Device(std::unique_ptr<DeviceState> initialState)
    : state(std::move(initialState)) {}

void Device::setState(std::unique_ptr<DeviceState> newState) {
    state = std::move(newState);
}

void Device::handle() {
    state->handle();
}