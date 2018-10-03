/*
 * Copyright (C) 2018 GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HAL_LNT_CSI2_V1_H__
#define __HAL_LNT_CSI2_V1_H__

#include <hal/pulp.h>
#include <stdint.h>
#include "archi/vendors/lnt/csi2_v1.h"

#if CSI2_VERSION != 1
#error This file must be included only with quiddikey version 1
#endif

// CSI2 HAL Registers Structure
struct halCsi2_struct_t {
    uint32_t cfg;
    uint32_t err_msb1;
    uint32_t err_msb;
    uint32_t err_lsb;
    uint32_t hs_rx_timeout_msb2;
    uint32_t hs_rx_timeout_msb1;
    uint32_t hs_rx_timeout_lsb;
    uint32_t vccfg;
    uint32_t polarity;
    uint32_t cci_addr;
    uint32_t cci_wr_data;
    uint32_t cci_rd_data;
    uint32_t cci_read_write;
    uint32_t cci_status;
    uint32_t cci_device_addr;
    uint32_t ulps_status;
};
typedef volatile struct halCsi2_struct_t halCsi2Handle_t;

// DPHY HAL Registers Structure
struct halDphy_struct_t {
    uint32_t lane_enable;
    uint32_t reset_dig_logic;
    uint32_t lane_ck_hs_countdown;
    uint32_t lane_ck_cont_mode;
    uint32_t lane_ck_rx_calib_enable;
    uint32_t lane_0_hs_countdown;
    uint32_t lane_0_rx_calib_enable;
    uint32_t lane_1_hs_countdown;
    uint32_t lane_1_rx_calib_enable;
};
typedef volatile struct halDphy_struct_t halDphyHandle_t;

// CSI2 HAL Handle
// located in "archi/chip/x/memory_map.h"

// DPHY HAL Handle
// located in "archi/chip/x/memory_map.h"


// CSI2 HAL functions prototype
static inline uint32_t halCsi2BaseAddrGet   (halCsi2Handle_t * handle);
static inline void     halCsi2CfgSet        (halCsi2Handle_t * handle,  uint32_t data);
static inline uint32_t halCsi2CfgGet        (halCsi2Handle_t * handle);

//     DPHY   HAL      functions            prototype
static inline uint32_t halDphyBaseAddrGet   (halDphyHandle_t * handle);
static inline void     halDphyLaneEnableSet (halDphyHandle_t * handle,  uint32_t data);
static inline uint32_t halDphyLaneEnableGet (halDphyHandle_t * handle);


// CSI2 HAL functions definition
static inline uint32_t halCsi2BaseAddrGet 			 (halCsi2Handle_t * handle) {
	return (uint32_t) (handle);
}

static inline void halCsi2CfgSet (halCsi2Handle_t * handle, uint32_t data) {
    handle->cfg = data;
}

static inline uint32_t halCsi2CfgGet (halCsi2Handle_t * handle) {
    return handle->cfg;
}



// DPHY HAL functions definition
static inline uint32_t halDphyBaseAddrGet            (halDphyHandle_t * handle) {
    return (uint32_t) (handle);
}

static inline void     halDphyLaneEnableSet                (halDphyHandle_t * handle,  uint32_t data) {
    handle->lane_enable = data;
}

static inline uint32_t halDphyLaneEnableGet                (halDphyHandle_t * handle) {
    return handle->lane_enable;
}

// CSI2 HAL Register Fields Structure
// typedef struct {
//     uint32_t zeroize       : 1;
//     uint32_t enroll        : 1;
//     uint32_t start         : 1;
//     uint32_t unused        : 2;
//     uint32_t stop          : 1;
//     uint32_t get_key       : 1;
//     uint32_t unwrap        : 1;
//     uint32_t wrap_gen_rand : 1;
//     uint32_t wrap          : 1;
//     uint32_t unused1       : 5;
//     uint32_t gen_rand      : 1;
//     uint32_t unused2       : 16;
// } __attribute__ ((packed)) halQuiddikeyCfg_t;

// CSI2 HAL Register Union definition
// typedef union {
//     halQuiddikeyCfg_t             config;
//     halQuiddikeyStatus_t          status;
//     halQuiddikeyAllow_t           allow;
//     halQuiddikeyInterruptEnable_t int_enable;
//     halQuiddikeyInterruptMask_t   int_mask;
//     halQuiddikeyInterruptStatus_t int_status;
//     halQuiddikeyKeyDest_t         key_dest;
//     halQuiddikeyDataInput_t       data_in;
//     halQuiddikeyDataOutput_t      data_out;
//     halQuiddikeyEndianness_t      endianness;
//     halQuiddikeyInterfaceStatus_t apb_itf_status;
//     halQuiddikeyTest_t            test_cfg;
//     halQuiddikeyHwRUC0_t          hw_ruc0;
//     halQuiddikeyHwRUC1_t          hw_ruc1;
//     halQuiddikeyHwSettings_t      hw_settings;
//     halQuiddikeyInfo_t            info;
//     halQuiddikeyID_t              id;
//     halQuiddikeyVersion_t         version;
//     uint32_t raw;
// } __attribute__ ((packed)) halQuiddikey_u;


#endif