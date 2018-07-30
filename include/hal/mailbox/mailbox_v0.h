/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
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

#ifndef __HAL_MAILBOX_V0_H__
#define __HAL_MAILBOX_V0_H__

#include "hal/pulp.h"
#include "archi/mailbox/mailbox_v0.h"

#define MAILBOX_VALID   (0)
#define MAILBOX_FAIL    (-1)

static inline unsigned int hal_mailbox_status_read()
{
  return pulp_read32(MAILBOX_REG_STATUS);
}

static inline unsigned int hal_mailbox_data_read()
{
  return pulp_read32(MAILBOX_REG_RDDATA);
}

static inline void hal_mailbox_data_write(unsigned int value)
{
  pulp_write32(MAILBOX_REG_WRDATA, value);
}

static inline void __sleep(volatile int iter)
{ 
  while(iter--);
}

static inline int hal_mailbox_read(unsigned int *ptr)
{
  uint32_t status;

  if ( hal_mailbox_data_read() & 0x1 )
  {
    volatile uint32_t timeout = 1000000000;
    status = 1;
    // wait for not empty or timeout
    while ( status && (timeout > 0) )
    {
      __sleep(50);
      timeout--;
      status = hal_mailbox_status_read() & 0x1;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  *ptr = hal_mailbox_data_read();  
  return MAILBOX_VALID;
}

static inline int hal_mailbox_read_timed(unsigned int *ptr, unsigned int t)
{
  uint32_t status;

  if ( hal_mailbox_data_read() & 0x1 )
  {
    volatile uint32_t timeout = t;
    status = 1;
    // wait for not empty or timeout
    while ( status && (timeout > 0) )
    {
      __sleep(50);
      timeout--;
      status = hal_mailbox_status_read() & 0x1;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  *ptr = hal_mailbox_data_read();  
  return MAILBOX_VALID;
}

int hal_mailbox_write(unsigned int value) 
{
  uint32_t status;

  if ( hal_mailbox_status_read() & 0x2 )
  {
    volatile uint32_t timeout = 1000000000;
    status = 1;
    // wait for not full or timeout
    while ( status && (timeout > 0) ) {
      __sleep(50);
      timeout--;
      status = hal_mailbox_status_read() & 0x2;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  hal_mailbox_data_write(value);
  return MAILBOX_VALID;
}

#endif
