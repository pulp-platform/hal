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

#include "hal/tryx/tryx_v1.h"

#include "pulp.h"             // pulp_read32(), eu_evt_mask()
#include "stdio.h"            // printf()

/** Go to sleep and wait for wake-up event.
 */
static void pulp_tryx_slowpath()
{
  int coreid = get_core_id();
  unsigned int mask;

  // save event mask
  mask = pulp_read32(ARCHI_EU_DEMUX_ADDR + EU_CORE_MASK);

  // only listen to wake-up event
  eu_evt_mask(EVTMASK_RAB_WAKEUP);

  // go to sleep, wait and clear
  evt_read32(ARCHI_EU_DEMUX_ADDR, EU_CORE_EVENT_WAIT_CLEAR);

  // restore the event mask
  eu_evt_mask(mask);

  return;
}

unsigned int pulp_tryread(const unsigned int* const addr)
{
  unsigned int val;

  int miss = pulp_tryread_noblock(addr, &val);
  while (miss) {
    pulp_tryx_slowpath();
    miss = pulp_tryread_noblock(addr, &val);
  }

  return val;
}

int pulp_tryread_prefetch(const unsigned int* const addr)
{
  #if DEBUG_TRYX == 1
    printf("read-prefetch of address 0x%X\n",(unsigned)addr);
  #endif

  pulp_tryx_set_prefetch();

  // Issue a read through RAB.
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    const volatile unsigned int dummy = *(volatile unsigned int*)addr;
  #pragma GCC diagnostic pop

  if (pulp_tryx_has_slverr()) {
    #if DEBUG_TRYX == 1
      printf("miss on address 0x%X\n",(unsigned)addr);
    #endif
    return 1;
  }

  return 0;
}

void pulp_trywrite(unsigned int* const addr, const unsigned int val)
{
  int miss = pulp_trywrite_noblock(addr, val);
  while (miss) {
    pulp_tryx_slowpath();
    miss = pulp_trywrite_noblock(addr, val);
  }

  return;
}

int pulp_trywrite_prefetch(unsigned int* const addr)
{
  #if DEBUG_TRYX == 1
    printf("write-prefetch of address 0x%X\n",(unsigned)addr);
  #endif

  pulp_tryx_set_prefetch();

  // Issue a write through RAB (to be discarded).
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    *(volatile unsigned int*)addr = 0x5000BAD1;
  #pragma GCC diagnostic pop

  if (pulp_tryx_has_slverr()) {
    #if DEBUG_TRYX == 1
      printf("miss on address 0x%X\n",(unsigned)addr);
    #endif
    return 1;
  }

  return 0;
}
