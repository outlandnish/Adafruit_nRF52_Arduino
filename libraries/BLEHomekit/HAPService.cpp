/**************************************************************************/
/*!
    @file     HAPService.cpp
    @author   hathach

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2017, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include <Arduino.h>
#include <bluefruit.h>
#include "BLEHomekit.h"
#include "HAPService.h"

// Starting from 1 for Accessory Info
uint16_t HAPService::_g_svc_id = 1;

err_t HAPService::begin(void)
{
  VERIFY_STATUS( BLEService::begin() );

  return _addSvcID();
}

err_t HAPService::_addSvcID(void)
{
  BLECharacteristic chr(HAP_UUID_CHR_SERVICE_ID);
  chr.setTempMemory();

  chr.setProperties(CHR_PROPS_READ);
  chr.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  chr.setFixedLen(2);
  VERIFY_STATUS( chr.begin() );

  _sid = _g_svc_id++;
  chr.write( _sid );

  return ERROR_NONE;
}


