#pragma once

class DeviceState {
public:
    virtual void handle() = 0;
    virtual ~DeviceState() = default;
};