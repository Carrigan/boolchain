#include "boolchain.h"

#define DIRECTION_LOAD  false
#define DIRECTION_SHIFT true
#define PULSE_CLOCK(bc) do { bc->writer(BOOLSIG_CLOCK, true); bc->writer(BOOLSIG_CLOCK, false); } while (0)
#define SET_LOAD(bc) bc->writer(BOOLSIG_DIRECTION, DIRECTION_LOAD)
#define SET_SHIFT(bc) bc->writer(BOOLSIG_DIRECTION, DIRECTION_SHIFT)

static void zero_bc(bc_t *p_bc) {
  p_bc->writer(BOOLSIG_ZERO, true);
  PULSE_CLOCK(p_bc);
  p_bc->writer(BOOLSIG_ZERO, false);
}

static bool bc_next(bc_t *p_bc) {
  PULSE_CLOCK(p_bc);
  p_bc->reader(BOOLSIG_RETURN);
}

bc_error_t boolchain_init(
  bc_t *p_boolchain, 
  const bool *p_buffer, 
  uint8_t p_buffer_size,
  bc_read_t p_read_function,
  bc_write_t p_write_function)
{
  // Initialize the structure
  if (!p_buffer)
    return BOOLCHAIN_NULL_BUFFER;

  p_boolchain->size = p_buffer_size;
  p_boolchain->buffer = (bool *)p_buffer;
  p_boolchain->writer = p_write_function;
  p_boolchain->reader = p_read_function;
  p_boolchain->count = 0;

  // Find how many there are in the chain by zeroing everything, writing a 1, and
  // seeing how many pulses it takes to get it back.
  zero_bc(p_boolchain);
  p_boolchain->writer(BOOLSIG_OUT, true);

  while(!bc_next(p_boolchain)) {
    p_boolchain->writer(BOOLSIG_OUT, false);
    p_boolchain->count++;

    if (p_boolchain->count > p_buffer_size)
      return BOOLCHAIN_TOO_MANY_NODES;
  }

  return BOOLCHAIN_OK;
}

void boolchain_capture(bc_t *p_boolchain)
{
  uint8_t i;
  SET_LOAD(p_boolchain);
  PULSE_CLOCK(p_boolchain);
  SET_SHIFT(p_boolchain);
  for(i = 0; i < p_boolchain->count; i++)
    p_boolchain->buffer[p_boolchain->count - i] = bc_next(p_boolchain);
}

uint8_t boolchain_count(bc_t *p_boolchain)
{
  return p_boolchain->count;
}

bc_error_t boolchain_get(bc_t *p_boolchain, uint8_t p_index, bool *p_out)
{
  if(p_index >= p_boolchain->count)
    return BOOLCHAIN_BAD_INDEX;

  *p_out = p_boolchain->buffer[p_index];
  return BOOLCHAIN_OK;
}
