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

/** Read the status register of the mailbox.

  \return  The value of the status register of the mailbox.
 */
static inline unsigned int mailbox_status_read()
{
  return pulp_read32(MAILBOX_REG_STATUS);
}

/** Read one word from the mailbox.

  \return  The value read from the mailbox.
 */
static inline unsigned int mailbox_data_read()
{
  return pulp_read32(MAILBOX_REG_RDDATA);
}

/** Write one word to the mailbox.

  \param   value  The value to be written to the mailbox.
 */
static inline void mailbox_data_write(unsigned int value)
{
  pulp_write32(MAILBOX_REG_WRDATA, value);
}

/** Wait for 'iter' iterations.

  \param   iter  The number of iterations to wait for. Each iteration is approximately clock 10 cycles.
 */
static inline void __sleep(volatile int iter)
{
  while(iter--);
}

/** Try to read one word from the mailbox.

  \param   ptr  The address to which the value read from the mailbox shall be written.

  \return  MAILBOX_VALID if a value could be read successfully, MAILBOX_FAIL otherwise.
 */
static inline int mailbox_read(unsigned int *ptr)
{
  uint32_t status;

  if ( mailbox_data_read() & 0x1 )
  {
    volatile uint32_t timeout = 1000000000;
    status = 1;
    // wait for not empty or timeout
    while ( status && (timeout > 0) )
    {
      __sleep(50);
      timeout--;
      status = mailbox_status_read() & 0x1;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  *ptr = mailbox_data_read();
  return MAILBOX_VALID;
}

/** Try to read one word from the mailbox. Poll at most t times.

  \param   ptr  The address to which the value read from the mailbox shall be written.
  \param   t    The maximum number of polling iterations.

  \return  MAILBOX_VALID if a value could be read successfully, MAILBOX_FAIL otherwise.
 */
static inline int mailbox_read_timed(unsigned int *ptr, unsigned int t)
{
  uint32_t status;

  if ( mailbox_data_read() & 0x1 )
  {
    volatile uint32_t timeout = t;
    status = 1;
    // wait for not empty or timeout
    while ( status && (timeout > 0) )
    {
      __sleep(50);
      timeout--;
      status = mailbox_status_read() & 0x1;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  *ptr = mailbox_data_read();
  return MAILBOX_VALID;
}

/** Try to write one word to the mailbox.

  \param   value  The value to be written to the mailbox.

  \return  MAILBOX_VALID if a value could be written successfully, MAILBOX_FAIL otherwise.
 */
static inline int mailbox_write(unsigned int value)
{
  uint32_t status;

  if ( mailbox_status_read() & 0x2 )
  {
    volatile uint32_t timeout = 1000000000;
    status = 1;
    // wait for not full or timeout
    while ( status && (timeout > 0) ) {
      __sleep(50);
      timeout--;
      status = mailbox_status_read() & 0x2;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  mailbox_data_write(value);
  return MAILBOX_VALID;
}

#endif
