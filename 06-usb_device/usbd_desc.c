/*******************************************************************************
 * MIT License
 *
 * Copyright (c) 2017 Yuriy Khokhulya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

#include "usbd_desc.h"

#include <usbd_core.h>
#include "usbd_conf.h"

#define USBD_SPEC 0x0200
#define USBD_VID 0x0483
#define USBD_PID 0x5750
#define USBD_REL 0x0100
#define USBD_LANGID_STRING 0x409
#define USBD_MANUFACTURER_STRING "STMicroelectronics"
#define USBD_PRODUCT_STRING "YK Gamepad"
#define USBD_CONFIGURATION_STRING "HID Config"
#define USBD_INTERFACE_STRING "HID Interface"
#define USBD_SERIAL_STRING "1.0.0"

// clang-format off
static uint8_t* USBD_GetDeviceDesc(USBD_SpeedTypeDef speed, uint16_t* length);
static uint8_t* USBD_GetLangIDStrDesc(USBD_SpeedTypeDef speed, uint16_t* length);
static uint8_t* USBD_GetManufacturerStrDesc(USBD_SpeedTypeDef speed, uint16_t* length);
static uint8_t* USBD_GetProductStrDesc(USBD_SpeedTypeDef speed, uint16_t* length);
static uint8_t* USBD_GetSerialStrDesc(USBD_SpeedTypeDef speed, uint16_t* length);
static uint8_t* USBD_GetConfigStrDesc(USBD_SpeedTypeDef speed, uint16_t* length);
static uint8_t* USBD_GetInterfaceStrDesc(USBD_SpeedTypeDef speed, uint16_t* length);
// clang-format on

USBD_DescriptorsTypeDef USBD_Desc = {
    USBD_GetDeviceDesc,
    USBD_GetLangIDStrDesc,
    USBD_GetManufacturerStrDesc,
    USBD_GetProductStrDesc,
    USBD_GetSerialStrDesc,
    USBD_GetConfigStrDesc,
    USBD_GetInterfaceStrDesc,
};

uint8_t USBD_DeviceDesc[USB_LEN_DEV_DESC] = {
    USB_LEN_DEV_DESC,           // bLength
    USB_DESC_TYPE_DEVICE,       // bDescType
    LOBYTE(USBD_SPEC),          // bcdUSB
    HIBYTE(USBD_SPEC),          // bcdUSB
    0x00,                       // bDeviceClass
    0x00,                       // bDeviceSubClass
    0x00,                       // bDeviceProtocol
    USB_MAX_EP0_SIZE,           // bMaxPacketSize
    LOBYTE(USBD_VID),           // idVendor
    HIBYTE(USBD_VID),           // idVendor
    LOBYTE(USBD_PID),           // idProduct
    HIBYTE(USBD_PID),           // idProduct
    LOBYTE(USBD_REL),           // bcdDevice
    LOBYTE(USBD_REL),           // bcdDevice
    USBD_IDX_MFC_STR,           // Index of manufacturer string
    USBD_IDX_PRODUCT_STR,       // Index of product string
    USBD_IDX_SERIAL_STR,        // Index of serial number string
    USBD_MAX_NUM_CONFIGURATION, // bNumConfigurations
};

uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] = {
    USB_LEN_LANGID_STR_DESC,
    USB_DESC_TYPE_STRING,
    LOBYTE(USBD_LANGID_STRING),
    HIBYTE(USBD_LANGID_STRING),
};

uint8_t USBD_StrDesc[USBD_MAX_STR_DESC_SIZ] = {};

uint8_t* USBD_GetDeviceDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    *length = sizeof(USBD_DeviceDesc);
    return (uint8_t*)USBD_DeviceDesc;
}

uint8_t* USBD_GetLangIDStrDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    *length = sizeof(USBD_LangIDDesc);
    return (uint8_t*)USBD_LangIDDesc;
}

uint8_t* USBD_GetProductStrDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    USBD_GetString((uint8_t*)USBD_PRODUCT_STRING, USBD_StrDesc, length);
    return USBD_StrDesc;
}

uint8_t* USBD_GetManufacturerStrDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    USBD_GetString((uint8_t*)USBD_MANUFACTURER_STRING, USBD_StrDesc, length);
    return USBD_StrDesc;
}

uint8_t* USBD_GetSerialStrDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    USBD_GetString((uint8_t*)USBD_SERIAL_STRING, USBD_StrDesc, length);
    return USBD_StrDesc;
}

uint8_t* USBD_GetConfigStrDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    USBD_GetString((uint8_t*)USBD_CONFIGURATION_STRING, USBD_StrDesc, length);
    return USBD_StrDesc;
}

uint8_t* USBD_GetInterfaceStrDesc(USBD_SpeedTypeDef speed, uint16_t* length)
{
    USBD_GetString((uint8_t*)USBD_INTERFACE_STRING, USBD_StrDesc, length);
    return USBD_StrDesc;
}
