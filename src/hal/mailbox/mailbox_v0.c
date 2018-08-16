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

#include "hal/mailbox/mailbox_v0.h"

/** Wait for 'iter' iterations.

  \param   iter  The number of iterations to wait for. Each iteration is approximately clock 10 cycles.
 */
static void __sleep(volatile int iter)
{
  while(iter--);
}

int mailbox_read(unsigned int *ptr)
{
  uint32_t status;

  if ( mailbox_status_read() & 0x1 )
  {
    status = 1;
    // wait for not empty
    while ( status )
    {
      __sleep(50);
      status = mailbox_status_read() & 0x1;
    }
  }

  *ptr = mailbox_data_read();
  return MAILBOX_VALID;
}

int mailbox_read_timed(unsigned int *ptr, unsigned int t)
{
  uint32_t status;

  if ( mailbox_status_read() & 0x1 )
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

int mailbox_write(unsigned int value)
{
  uint32_t status;

  if ( mailbox_status_read() & 0x2 )
  {
    status = 1;
    // wait for not full
    while ( status ) {
      __sleep(50);
      status = mailbox_status_read() & 0x2;
    }
    if ( status )
      return MAILBOX_FAIL;
  }

  mailbox_data_write(value);
  return MAILBOX_VALID;
}
