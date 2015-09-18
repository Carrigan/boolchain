#include "shift.h"

void shift_apply_signal(shift_t *shift, bool p_signal)
{
  shift->input = p_signal;
}

void shift_pulse_clock(shift_t *shift)
{
  shift->output = shift->input;
}

bool shift_get_output(shift_t *shift)
{
  return shift->output;
}

void shift_zero(shift_t *shift)
{
  shift->output = false;
}

void shift_chain_init(shift_chain_t *shift, shift_t *buffer, uint8_t count)
{
  shift->shifts = buffer;
  shift->count = count;
  shift_chain_zero(shift);
}

void shift_chain_apply_signal(shift_chain_t *shift, bool p_signal)
{
  shift_apply_signal(&shift->shifts[0], p_signal);
}

void shift_chain_pulse_clock(shift_chain_t *shift)
{
  uint8_t i;
  for(i = 0; i < shift->count; i++) {
    shift_pulse_clock(&shift->shifts[shift->count - 1 - i]);
  }
}

bool shift_chain_get_output(shift_chain_t *shift)
{
  return shift_get_output(&shift->shifts[shift->count - 1]);
}

void shift_chain_zero(shift_chain_t *shift)
{
  uint8_t i;
  for(i = 0; i < shift->count; i++) {
    shift_zero(&shift->shifts[i]); 
  }
}
