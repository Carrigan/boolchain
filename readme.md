# The Boolchain Project

The boolchain project was founded out of the need for a scalable IO module that can read in boolean logic. The resultant circuit board implements a serial interface that can be loaded simultaneously and shifted into a host one bit at a time.

# Requirements

In order to keep this library platform independent, it requires the implementor to write two IO functions that take the following format:

```
typedef bool (*bc_read_t)(bc_signal_t);
typedef void (*bc_write_t)(bc_signal_t, bool);
```

In this block, `bc_signal_t` is an enumeration that tells the user implemented function which pin to read or write to. The pins will always use the same direction, and should be set to the following:

| SIGNAL NAME       | DIRECTION |
|-------------------|-----------|
| BOOLSIG_ZERO      | OUTPUT    |
| BOOLSIG_CLOCK     | OUTPUT    |
| BOOLSIG_OUT       | OUTPUT    |
| BOOLSIG_DIRECTION | OUTPUT    |
| BOOLSIG_RETURN    | INPUT     |

# Sample Code

```
#define NODES_SUPPORTED 20
bc_t my_boolchain;
bool bc_buffer[NODES_SUPPORTED];
bc_error_t result = boolchain_init(&my_boolchain, bc_buffer, NODES_SUPPORTED, read_func, write_func);

if (result != BOOLCHAIN_OK) {
  // handle error here...
}

boolchain_capture(&my_boolchain);
for (i = 0; i < boolchain_count(&my_boolchain); i++) {
  bool sensor_data;
  bc_error_t read_result = boolchain_get(&my_boolchain, i, &sensor_data);
  if (read_result != BOOLCHAIN_OK) {
    // handle out of bounds error...
  }

  // do something with sensor_data...
}
```