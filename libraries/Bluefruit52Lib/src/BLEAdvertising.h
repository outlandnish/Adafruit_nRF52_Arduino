/**************************************************************************/
/*!
    @file     BLEAdvertising.h
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
#ifndef BLEADVERTISING_H_
#define BLEADVERTISING_H_

#include <Arduino.h>
#include "bluefruit_common.h"
#include "BLEClientService.h"

#include "BLEUuid.h"
#include "BLEService.h"
#include "services/BLEBeacon.h"

#define BLE_ADV_INTERVAL_FAST_DFLT       32  // 20    ms (in 0.625 ms unit)
#define BLE_ADV_INTERVAL_SLOW_DFLT       244 // 152.5 ms (in 0.625 ms unit)
#define BLE_ADV_FAST_TIMEOUT_DFLT        30  // in seconds

class BLEAdvertisingData
{
protected:
  uint8_t _data[BLE_GAP_ADV_MAX_SIZE];
  uint8_t _count;

public:
  BLEAdvertisingData(void);

  /*------------- Adv Data -------------*/
  bool addData(uint8_t type, const void* data, uint8_t len);
  bool addFlags(uint8_t flags);
  bool addTxPower(void);
  bool addName(void);
  bool addAppearance(uint16_t appearance);

  bool addUuid(BLEUuid bleuuid);
  bool addService(BLEService& service);
  bool addService(BLEClientService& service);

  // Custom API
  uint8_t  count(void);
  uint8_t* getData(void);
  bool     setData(const uint8_t* data, uint8_t count);
  void     clearData(void);
};


class BLEAdvertising : public BLEAdvertisingData
{
public:
  typedef void (*stop_callback_t) (void);
  BLEAdvertising(void);

  void setType(uint8_t adv_type);
  void setFastTimeout(uint16_t sec);
  void setStopCallback(stop_callback_t fp);

  void setInterval  (uint16_t fast, uint16_t slow);
  void setIntervalMS(uint16_t fast, uint16_t slow);

  bool setBeacon(BLEBeacon& beacon);

  bool start(uint32_t stop_sec = 0);
  bool stop (void);

  /*------------------------------------------------------------------*/
  /* INTERNAL USAGE ONLY
   * Although declare as public, it is meant to be invoked by internal
   * code. User should not call these directly
   *------------------------------------------------------------------*/
  void _eventHandler(ble_evt_t* evt);

private:
  uint8_t  _type;

  uint16_t _fast_interval; // in 0.625 ms
  uint16_t _slow_interval; // in 0.625 ms

  uint16_t _fast_timeout; // in second
  uint16_t _stop_timeout; // in second

  stop_callback_t _stop_cb;

  // Internal function
  bool _start(uint16_t interval, uint16_t timeout);

};

#endif /* BLEADVERTISING_H_ */
