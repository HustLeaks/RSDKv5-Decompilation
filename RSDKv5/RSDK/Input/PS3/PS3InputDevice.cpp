#include <io/pad.h>

padInfo padinfo;
padData paddata;

padData oldpaddata;

#define CheckPS3Button( btn, key, controllernum) \
	if( paddata.btn != oldpaddata.btn) {\
		if( paddata.btn == 0) \
		controller[controllernum].key.press = false; \
		else \
		controller[controllernum].key.press = true; \
	} \
	oldpaddata.btn = paddata.btn;

using namespace RSDK::SKU;

void InputDevicePS3::UpdateInput()
{
    ProcessInput(CONT_ANY);
}


void InputDevicePS3::ProcessInput(int32 controllerID)
{
    ioPadGetInfo(&padinfo);
    ioPadGetData(0, &paddata);

    CheckPS3Button(BTN_UP, keyUp, controllerID);
    CheckPS3Button(BTN_DOWN, keyDown, controllerID);
    CheckPS3Button(BTN_LEFT, keyLeft, controllerID);
    CheckPS3Button(BTN_RIGHT, keyRight, controllerID);
    CheckPS3Button(BTN_CROSS, keyA, controllerID);
    CheckPS3Button(BTN_CIRCLE, keyB, controllerID);
    CheckPS3Button(BTN_SQUARE, keyX, controllerID);
    CheckPS3Button(BTN_TRIANGLE, keyY, controllerID);
    CheckPS3Button(BTN_START, keyStart, controllerID);
    CheckPS3Button(BTN_SELECT, keySelect, controllerID);
}

void InputDevicePS3::CloseDevice()
{
    this->active     = false;
    this->isAssigned = false;
    ioPadEnd();
}

RSDK::SKU::InputDevicePS3 *RSDK::SKU::InitPS3InputDevice(uint8 controllerID)
{
    uint32 id = 1;

    if (inputDeviceCount >= INPUTDEVICE_COUNT)
        return NULL;

    if (inputDeviceList[inputDeviceCount] && inputDeviceList[inputDeviceCount]->active)
        return NULL;

    if (inputDeviceList[inputDeviceCount])
        delete inputDeviceList[inputDeviceCount];

    inputDeviceList[inputDeviceCount] = new InputDevicePS3();

    InputDevicePS3 *device = (InputDevicePS3 *)inputDeviceList[inputDeviceCount];

    uint8 controllerType = DEVICE_PS4;

    device->active      = true;
    device->disabled    = false;
    device->gamepadType = (DEVICE_API_PS3 << 16) | (DEVICE_TYPE_CONTROLLER << 8) | (controllerType << 0);
    device->id          = id;

    for (int32 i = 0; i < PLAYER_COUNT; ++i) {
        if (inputSlots[i] == id) {
            inputSlotDevices[i] = device;
            device->isAssigned  = true;
        }
    }

    inputDeviceCount++;
    return device;
}

void RSDK::SKU::InitPS3InputAPI()
{
    ioPadInit(7);
}