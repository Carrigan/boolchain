#ifndef SHIFT_H_
#define SHIFT_H_
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  bool input;
  bool output;
} shift_t;

void shift_apply_signal(shift_t *shift, bool p_signal);
void shift_pulse_clock(shift_t *shift);
bool shift_get_output(shift_t *shift);
void shift_zero(shift_t *shift);

typedef struct {
  shift_t *shifts;
  uint8_t count;
} shift_chain_t;

void shift_chain_init(shift_chain_t *shift, shift_t *buffer, uint8_t count);
void shift_chain_apply_signal(shift_chain_t *shift, bool p_signal);
void shift_chain_pulse_clock(shift_chain_t *shift);
bool shift_chain_get_output(shift_chain_t *shift);
void shift_chain_zero(shift_chain_t *shift);

#endif

