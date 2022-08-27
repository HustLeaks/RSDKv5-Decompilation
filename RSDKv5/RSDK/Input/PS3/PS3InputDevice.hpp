
namespace SKU
{

struct InputDevicePS3 : InputDevice {
    void UpdateInput();
    void ProcessInput(int32 controllerID);
    void CloseDevice();

    //int32 buttonMasks;

    bool32 swapABXY;
};

RSDK::SKU::InputDevicePS3 *InitPS3InputDevice(uint8 controllerID);

void InitPS3InputAPI();

} // namespace SKU