#pragma once
#include "device_state.h"

// Forward declarations of state classes
class IdleState : public DeviceState {
public:
    void handle() override;
};

class ActiveState : public DeviceState {
public:
    void handle() override;
};

class ErrorState : public DeviceState {
public:
    void handle() override;
};