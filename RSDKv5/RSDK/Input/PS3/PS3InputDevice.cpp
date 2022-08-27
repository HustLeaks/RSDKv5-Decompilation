#include <io/pad.h>

padInfo padinfo;
padData paddata;

padData oldpaddata;

// contains a workaround, similar to the one found 
// in saturn's 3ds port.
#define CheckPS3Button( btn, key ) \
	if( paddata.btn != oldpaddata.btn) {\
		if( paddata.btn == 0) {\
		    controller[CONT_P1].key.press = false; \
		    controller[CONT_ANY].key.press = false; \
		} else {\
		    controller[CONT_P1].key.press = true; \
		    controller[CONT_ANY].key.press = true; \
        } \
	} else { \
		if( paddata.btn == 0) {\
		    controller[CONT_P1].key.press = false; \
		    controller[CONT_ANY].key.press = false; \
		} else {\
		    controller[CONT_P1].key.press = true; \
		    controller[CONT_ANY].key.press = true; \
        } \
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

    CheckPS3Button(BTN_UP, keyUp);
    CheckPS3Button(BTN_DOWN, keyDown);
    CheckPS3Button(BTN_LEFT, keyLeft);
    CheckPS3Button(BTN_RIGHT, keyRight);
    CheckPS3Button(BTN_CROSS, keyA);
    CheckPS3Button(BTN_CIRCLE, keyB);
    CheckPS3Button(BTN_SQUARE, keyX);
    CheckPS3Button(BTN_TRIANGLE, keyY);
    CheckPS3Button(BTN_START, keyStart);
    CheckPS3Button(BTN_SELECT, keySelect);
}

void InputDevicePS3::CloseDevice()
{
    this->active     = false;
    this->isAssigned = false;
    ioPadEnd();
}

RSDK::SKU::InputDevicePS3 *RSDK::SKU::InitPS3InputDevice(uint8 controllerID)
{
    if (inputDeviceCount == INPUTDEVICE_COUNT)
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
    device->id          = controllerID;

    for (int32 i = 0; i < PLAYER_COUNT; ++i) {
        if (inputSlots[i] == controllerID) {
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
    SKU::InitPS3InputDevice(CONT_ANY);
}