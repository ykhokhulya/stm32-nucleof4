/*******************************************************************************
 * MIT License
 *
 * Copyright (c) 2018 Yuriy Khokhulya
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

#include "usbd_gamepad_if.h"

static int8_t GamepadHID_Init(void);
static int8_t GamepadHID_DeInit(void);
static int8_t GamepadHID_OutEvent(uint8_t event_idx, uint8_t state);

static uint8_t GamepadHID_ReportDesc[USBD_CUSTOM_HID_REPORT_DESC_SIZE] = {
    0x05, 0x01, // USAGE_PAGE (Generic Desktop)
    0x09, 0x05, // USAGE (Game Pad)
    0xa1, 0x01, // COLLECTION (Application)
    0x05, 0x02, //   USAGE_PAGE (Simulation Controls)
    0x09, 0xbb, //   USAGE (Throttle)
    0x15, 0x00, //   LOGICAL_MINIMUM (0)
    0x25, 0x1f, //   LOGICAL_MAXIMUM (31)
    0x75, 0x08, //   REPORT_SIZE (8)
    0x95, 0x01, //   REPORT_COUNT (1)
    0x81, 0x02, //   INPUT (Data,Var,Abs)
    0x05, 0x02, //   USAGE_PAGE (Simulation Controls)
    0x09, 0xbb, //   USAGE (Throttle)
    0x15, 0x00, //   LOGICAL_MINIMUM (0)
    0x25, 0x1f, //   LOGICAL_MAXIMUM (31)
    0x75, 0x08, //   REPORT_SIZE (8)
    0x95, 0x01, //   REPORT_COUNT (1)
    0x81, 0x02, //   INPUT (Data,Var,Abs)
    0x05, 0x01, //   USAGE_PAGE (Generic Desktop)
    0xa1, 0x00, //   COLLECTION (Physical)
    0x09, 0x30, //     USAGE (X)
    0x09, 0x31, //     USAGE (Y)
    0x09, 0x32, //     USAGE (Z)
    0x09, 0x33, //     USAGE (Rx)
    0x15, 0x81, //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f, //     LOGICAL_MAXIMUM (127)
    0x75, 0x08, //     REPORT_SIZE (8)
    0x95, 0x04, //     REPORT_COUNT (4)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    0x05, 0x09, //     USAGE_PAGE (Button)
    0x19, 0x01, //     USAGE_MINIMUM (Button 1)
    0x29, 0x10, //     USAGE_MAXIMUM (Button 8)
    0x15, 0x00, //     LOGICAL_MINIMUM (0)
    0x25, 0x01, //     LOGICAL_MAXIMUM (1)
    0x75, 0x01, //     REPORT_SIZE (1)
    0x95, 0x10, //     REPORT_COUNT (8)
    0x81, 0x02, //     INPUT (Data,Var,Abs)
    0xc0,       //   END_COLLECTION
    0xc0        // END_COLLECTION
};

USBD_CUSTOM_HID_ItfTypeDef USBD_GamepadHID_fops = {
    GamepadHID_ReportDesc,
    GamepadHID_Init,
    GamepadHID_DeInit,
    GamepadHID_OutEvent,
};

int8_t GamepadHID_Init(void)
{
    return 0;
}

int8_t GamepadHID_DeInit(void)
{
    return 0;
}

static int8_t GamepadHID_OutEvent(uint8_t event_idx, uint8_t state)
{
    return 0;
}
