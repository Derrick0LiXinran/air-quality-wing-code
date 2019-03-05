#ifndef CCS811_H
#define CCS811_H

#include "stdint.h"
#include "application.h"

#define CCS811_STATUS_REG     0x00
#define CCS811_MEAS_MODE_REG  0x01
#define CCS811_RESULT_REG     0x02
#define CCS811_HW_ID_REG      0x20
#define CCS811_START_APP      0xF4

#define CCS811_IDLE_MODE      0x00
#define CCS811_CONSTANT_MODE  0x20
#define CCS811_INT_EN         0x08

#define CCS811_FW_MODE_RUN    0x90

// Error codes
enum {
  CCS811_SUCCESS,
  CCS811_NULL_ERROR,
  CCS811_NO_DAT_AVAIL,
  CCS811_RUN_ERROR
};

typedef struct {
  uint16_t c02;
  uint16_t tvoc;
} ccs811_data_t;

typedef struct {
  uint8_t address;
  raw_interrupt_handler_t pin_interrupt;
  uint8_t int_pin;
  uint8_t rst_pin;
  uint8_t wake_pin;
} ccs811_init_t;

class CCS811 {
  public:
    CCS811(void);
    uint32_t setup(ccs811_init_t * init);
    uint32_t enable(void);
    uint32_t set_env(void); //TODO: set the temp and humidity variables
    uint32_t read(ccs811_data_t * p_data);
    void int_handler(void);
  protected:
    uint8_t address;
    raw_interrupt_handler_t pin_interrupt;
    uint8_t int_pin;
    uint8_t rst_pin;
    uint8_t wake_pin;
    bool    data_ready;
};

#endif