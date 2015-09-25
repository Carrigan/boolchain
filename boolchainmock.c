#include "boolchainmock.h"
#include "shift.h"
#include <string.h>

shift_t shift_registers[40];
shift_chain_t shift_chain;
bool sensor_data[40]; 
bool microcontroller_output = false;
bool clock_output = false;

bool bcm_read(bc_signal_t p_signal)
{
  switch(p_signal) {
    case BOOLSIG_RETURN: {
      return shift_chain_get_output(&shift_chain);
      break;
    }

    default:
      break;
  }

  return false;
}

void bcm_write(bc_signal_t p_signal, bool p_value)
{
  switch(p_signal) {
    case BOOLSIG_ZERO: {
      shift_chain_zero(&shift_chain);
      break;
    }

    case BOOLSIG_CLOCK: {
      if (!p_value && clock_output)
        shift_chain_pulse_clock(&shift_chain);
      clock_output = p_value;
      break;
    }

    case BOOLSIG_OUT: {
      microcontroller_output = p_value;
      shift_chain_apply_signal(&shift_chain, microcontroller_output);
      break;
    }

    case BOOLSIG_DIRECTION: {
      if (!p_value) {
        shift_chain_apply_signal(&shift_chain, microcontroller_output);
      } else {
        uint8_t i;
        for(i = 0; i < shift_chain.count; i++) {
          shift_apply_signal(&(shift_chain.shifts[i]), sensor_data[i]);
        }
      }
      break;
    }

    default:
      break;
  }
}

void bcm_init(uint8_t p_count)
{
  shift_chain_init(&shift_chain, shift_registers, p_count);
}

void bcm_set_data(bool *p_values, uint8_t p_count)
{
  memcpy(sensor_data, p_values, p_count);
}

