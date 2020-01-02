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

#include "usbd_conf.h"

#include <stm32f3xx_hal.h>
#include <usbd_core.h>

PCD_HandleTypeDef hpcd;

USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef* pdev)
{
    hpcd.Instance = USB;
    hpcd.Init.dev_endpoints = 8;
    hpcd.Init.ep0_mps = PCD_EP0MPS_64;
    hpcd.Init.phy_itface = PCD_PHY_EMBEDDED;
    hpcd.Init.speed = PCD_SPEED_FULL;
    hpcd.pData = pdev;
    pdev->pData = &hpcd;

    HAL_PCD_Init(pdev->pData);

    HAL_PCDEx_PMAConfig(pdev->pData, 0x00, PCD_SNG_BUF, 0x18);
    HAL_PCDEx_PMAConfig(pdev->pData, 0x80, PCD_SNG_BUF, 0x58);
    HAL_PCDEx_PMAConfig(pdev->pData, 0x81, PCD_SNG_BUF, 0x100);

    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef* pdev)
{
    HAL_PCD_DeInit(pdev->pData);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef* pdev)
{
    HAL_PCD_Start(pdev->pData);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef* pdev)
{
    HAL_PCD_Stop(pdev->pData);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_OpenEP(
    USBD_HandleTypeDef* pdev,
    uint8_t ep_addr,
    uint8_t ep_type,
    uint16_t ep_mps)
{
    HAL_PCD_EP_Open(pdev->pData, ep_addr, ep_mps, ep_type);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef* pdev, uint8_t ep_addr)
{
    HAL_PCD_EP_Close(pdev->pData, ep_addr);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef* pdev, uint8_t ep_addr)
{
    HAL_PCD_EP_Flush(pdev->pData, ep_addr);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef* pdev, uint8_t ep_addr)
{
    HAL_PCD_EP_SetStall(pdev->pData, ep_addr);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_ClearStallEP(
    USBD_HandleTypeDef* pdev,
    uint8_t ep_addr)
{
    HAL_PCD_EP_ClrStall(pdev->pData, ep_addr);
    return USBD_OK;
}

uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef* pdev, uint8_t ep_addr)
{
    PCD_HandleTypeDef* hpcd = (PCD_HandleTypeDef*)pdev->pData;
    if ((ep_addr & 0x80) == 0x80)
    {
        return hpcd->IN_ep[ep_addr & 0x7F].is_stall;
    }
    else
    {
        return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
    }
}

USBD_StatusTypeDef USBD_LL_SetUSBAddress(
    USBD_HandleTypeDef* pdev,
    uint8_t dev_addr)
{
    HAL_PCD_SetAddress(pdev->pData, dev_addr);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_Transmit(
    USBD_HandleTypeDef* pdev,
    uint8_t ep_addr,
    uint8_t* pbuf,
    uint16_t size)
{
    HAL_PCD_EP_Transmit(pdev->pData, ep_addr, pbuf, size);
    return USBD_OK;
}

USBD_StatusTypeDef USBD_LL_PrepareReceive(
    USBD_HandleTypeDef* pdev,
    uint8_t ep_addr,
    uint8_t* pbuf,
    uint16_t size)
{
    HAL_PCD_EP_Receive(pdev->pData, ep_addr, pbuf, size);
    return USBD_OK;
}

uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef* pdev, uint8_t ep_addr)
{
    return HAL_PCD_EP_GetRxCount(pdev->pData, ep_addr);
}

void USBD_LL_Delay(uint32_t Delay)
{
    HAL_Delay(Delay);
}

void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_SetupStage(hpcd->pData, (uint8_t*)hpcd->Setup);
}

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    USBD_LL_DataOutStage(hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    USBD_LL_DataInStage(hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

void HAL_PCD_SOFCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_SOF(hpcd->pData);
}

void HAL_PCD_ResetCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_SetSpeed(hpcd->pData, USBD_SPEED_FULL);
    USBD_LL_Reset(hpcd->pData);
}

void HAL_PCD_SuspendCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_Suspend(hpcd->pData);
}

void HAL_PCD_ResumeCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_Resume(hpcd->pData);
}

void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    USBD_LL_IsoOUTIncomplete(hpcd->pData, epnum);
}

void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef* hpcd, uint8_t epnum)
{
    USBD_LL_IsoINIncomplete(hpcd->pData, epnum);
}

void HAL_PCD_ConnectCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_DevConnected(hpcd->pData);
}

void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef* hpcd)
{
    USBD_LL_DevDisconnected(hpcd->pData);
}
