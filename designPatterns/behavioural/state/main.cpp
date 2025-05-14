
#include <memory>
#include "concrete_state.h"
#include "device.h"

int main(){
    Device device(std::make_unique<ActiveState>());
    device.handle(); // Output: Device is idle.

    device.setState(std::make_unique<IdleState>());
    device.handle(); // Output: Device is active.

    device.setState(std::make_unique<ErrorState>());
    device.handle(); // Output: Device is in error state!
    return 0;
}