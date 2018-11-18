/*
 * Copyright (C) 2018 ETH Zurich, University of Bologna and
 * GreenWaves Technologies
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

#ifndef __HAL_VEGA_EFUSE_H__
#define __HAL_VEGA_EFUSE_H__

#include "hal/pulp.h"

#define PLP_EFUSE_PLT_OTHER   0
#define PLP_EFUSE_PLT_FPGA    1
#define PLP_EFUSE_PLT_RTL     2
#define PLP_EFUSE_PLT_VP      3
#define PLP_EFUSE_PLT_CHIP    4


#define PLP_EFUSE_BOOT_JTAG_MODE 0
#define PLP_EFUSE_BOOT_JTAG      1
#define PLP_EFUSE_BOOT_FLASH     2
#define PLP_EFUSE_BOOT_SPIS      3


#define EFUSE_INFO_REG          0
#define EFUSE_INFO2_REG         1
#define EFUSE_INFO3_REG         37
#define EFUSE_AES_KEY_FIRST_REG 2
#define EFUSE_AES_KEY_NB_REGS   16
#define EFUSE_AES_IV_FIRST_REG  18
#define EFUSE_AES_IV_NB_REGS    8

#define EFUSE_WAIT_XTAL_DELTA_REG_LSB     26
#define EFUSE_WAIT_XTAL_DELTA_REG_MSB     27

#define EFUSE_WAIT_XTAL_MIN_REG        28
#define EFUSE_WAIT_XTAL_MAX_REG        29

#define EFUSE_HYPER_RDS_DELAY          30 /* Eric: added a new efuse location for the hyper rds delay, one byte is enough */

#define EFUSE_FLL_FREQ                 31
#define EFUSE_FLL_TOLERANCE            32
#define EFUSE_FLL_ASSERT_CYCLES        33

#define EFUSE_PERIPH_DIV               34

#define EFUSE_REF_CLK_WAIT_CYCLES_LSB      35
#define EFUSE_REF_CLK_WAIT_CYCLES_MSB      36

#define EFUSE_INFO_PLT_BIT    0
#define EFUSE_INFO_PLT_WIDTH  3

#define EFUSE_INFO_BOOT_BIT    3
#define EFUSE_INFO_BOOT_WIDTH  3

#define EFUSE_INFO_ENCRYPTED_BIT     6
#define EFUSE_INFO_ENCRYPTED_WIDTH   1

#define EFUSE_INFO_WAIT_XTAL_BIT     7
#define EFUSE_INFO_WAIT_XTAL_WIDTH   1

#define EFUSE_INFO2_FLL_FREQ_SET_BIT    0
#define EFUSE_INFO2_FLL_FREQ_SET_WIDTH  1

#define EFUSE_INFO2_FLL_CONF_BIT    1
#define EFUSE_INFO2_FLL_CONF_WIDTH  1

#define EFUSE_INFO2_FLL_BYPASS_LOCK_BIT    2
#define EFUSE_INFO2_FLL_BYPASS_LOCK_WIDTH  1

#define EFUSE_INFO2_SPIM_CLKDIV_BIT    3
#define EFUSE_INFO2_SPIM_CLKDIV_WIDTH  2

#define EFUSE_INFO2_LOCK_JTAG_SPIS_BIT    5
#define EFUSE_INFO2_LOCK_JTAG_SPIS_WIDTH    1

#define EFUSE_INFO2_REF_CLK_WAIT_BIT    6
#define EFUSE_INFO2_REF_CLK_WAIT_WIDTH    1

#define EFUSE_INFO2_PAD_CONFIG_BIT      7
#define EFUSE_INFO2_PAD_CONFIG_WIDTH    1

#define EFUSE_INFO3_FLASH_TYPE_BIT      0
#define EFUSE_INFO3_FLASH_TYPE_WIDTH    1

#define EFUSE_INFO3_CLKDIV_BIT      1
#define EFUSE_INFO3_CLKDIV_WIDTH    1

static inline unsigned int plp_efuse_info_get() {
  return plp_efuse_readByte(EFUSE_INFO_REG);
}

static inline unsigned int plp_efuse_info2_get() {
  return plp_efuse_readByte(EFUSE_INFO2_REG);
}

static inline unsigned int plp_efuse_info3_get() {
  return plp_efuse_readByte(EFUSE_INFO3_REG);
}

static inline unsigned int plp_efuse_platform_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO_PLT_BIT, EFUSE_INFO_PLT_WIDTH);
}

static inline unsigned int plp_efuse_bootmode_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO_BOOT_BIT, EFUSE_INFO_BOOT_WIDTH);
}

static inline unsigned int plp_efuse_encrypted_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO_ENCRYPTED_BIT, EFUSE_INFO_ENCRYPTED_WIDTH);
}

static inline unsigned int plp_efuse_aesKey_get(int word) {
  return plp_efuse_readByte(EFUSE_AES_KEY_FIRST_REG + word);
}

static inline unsigned int plp_efuse_aesIv_get(int word) {
  return plp_efuse_readByte(EFUSE_AES_IV_FIRST_REG + word);
}

static inline unsigned int plp_efuse_wait_xtal_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO_WAIT_XTAL_BIT, EFUSE_INFO_WAIT_XTAL_WIDTH);
}

static inline unsigned int plp_efuse_wait_xtal_delta_get() {
  return plp_efuse_readByte(EFUSE_WAIT_XTAL_DELTA_REG_LSB) | (plp_efuse_readByte(EFUSE_WAIT_XTAL_DELTA_REG_MSB) << 8);
}

static inline unsigned int plp_efuse_wait_xtal_min_get() {
  return plp_efuse_readByte(EFUSE_WAIT_XTAL_MIN_REG);
}

static inline unsigned int plp_efuse_wait_xtal_max_get() {
  return plp_efuse_readByte(EFUSE_WAIT_XTAL_MAX_REG);
}

static inline unsigned int plp_efuse_hyper_rds_delay_get() {  /* Eric: added new function to read hyper rds delay */
  return plp_efuse_readByte(EFUSE_HYPER_RDS_DELAY);
}

static inline unsigned int plp_efuse_fll_set_freq_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_FLL_FREQ_SET_BIT, EFUSE_INFO2_FLL_FREQ_SET_WIDTH);
}

static inline unsigned int plp_efuse_fll_conf_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_FLL_CONF_BIT, EFUSE_INFO2_FLL_CONF_WIDTH);
}

static inline unsigned int plp_efuse_fll_bypass_lock_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_FLL_BYPASS_LOCK_BIT, EFUSE_INFO2_FLL_BYPASS_LOCK_WIDTH);
}

static inline unsigned int plp_efuse_spim_clkdiv_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_SPIM_CLKDIV_BIT, EFUSE_INFO2_SPIM_CLKDIV_WIDTH);
}

static inline unsigned int plp_efuse_fll_freq_get() {
  return plp_efuse_readByte(EFUSE_FLL_FREQ);
}

static inline unsigned int plp_efuse_fll_tolerance_get() {
  return plp_efuse_readByte(EFUSE_FLL_TOLERANCE);
}

static inline unsigned int plp_efuse_fll_assert_cycles_get() {
  return plp_efuse_readByte(EFUSE_FLL_ASSERT_CYCLES);
}

static inline unsigned int plp_efuse_lock_jtag_spis_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_LOCK_JTAG_SPIS_BIT, EFUSE_INFO2_LOCK_JTAG_SPIS_WIDTH);
}

static inline unsigned int plp_efuse_ref_clk_wait_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_REF_CLK_WAIT_BIT, EFUSE_INFO2_REF_CLK_WAIT_WIDTH);
}

static inline unsigned int plp_efuse_pad_config_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO2_PAD_CONFIG_BIT, EFUSE_INFO2_PAD_CONFIG_WIDTH);
}

static inline unsigned int plp_efuse_flash_type_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO3_FLASH_TYPE_BIT, EFUSE_INFO3_FLASH_TYPE_WIDTH);
}

static inline unsigned int plp_efuse_clkdiv_get(unsigned int infoValue) {
  return ARCHI_REG_FIELD_GET(infoValue, EFUSE_INFO3_CLKDIV_BIT, EFUSE_INFO3_CLKDIV_WIDTH);
}

static inline unsigned int plp_efuse_ref_clk_wait_cycles_get() {
  return plp_efuse_readByte(EFUSE_REF_CLK_WAIT_CYCLES_LSB) | (plp_efuse_readByte(EFUSE_REF_CLK_WAIT_CYCLES_MSB) << 8);
}

#endif
