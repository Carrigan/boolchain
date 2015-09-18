#ifndef BOOLCHAINMOCK_H
#define BOOLCHAINMOCK_H
#include "boolchain.h"

bool bcm_read(bc_signal_t p_signal);
void bcm_write(bc_signal_t p_signal, bool p_value);
void bcm_init(uint8_t p_count);
void bcm_set_data(bool *p_values, uint8_t p_count);

#endif
