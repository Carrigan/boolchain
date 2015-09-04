#ifndef BOOLCHAIN_H_
#define BOOLCHAIN_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  BOOLCHAIN_OK,
  BOOLCHAIN_NULL_BUFFER,
  BOOLCHAIN_TOO_MANY_NODES,
  BOOLCHAIN_BAD_INDEX
} bc_error_t;

typedef enum {
  BOOLSIG_ZERO,
  BOOLSIG_CLOCK,
  BOOLSIG_OUT,
  BOOLSIG_RETURN,
  BOOLSIG_DIRECTION
} bc_signal_t;

typedef bool (*bc_read_t)(bc_signal_t);
typedef void (*bc_write_t)(bc_signal_t, bool);

typedef struct {
  bool *buffer;
  uint8_t size;
  uint8_t count;
  bc_read_t reader;
  bc_write_t writer;
} bc_t;

bc_error_t boolchain_init(
  bc_t *p_boolchain, 
  const bool *p_buffer, 
  uint8_t p_buffer_size,
  bc_read_t p_read_function,
  bc_write_t p_write_function);

void boolchain_capture(bc_t *p_boolchain);
uint8_t boolchain_count(bc_t *p_boolchain);
bc_error_t boolchain_get(bc_t *p_boolchain, uint8_t p_index, bool *p_out);

#endif
