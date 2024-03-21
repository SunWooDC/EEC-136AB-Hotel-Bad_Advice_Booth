#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>

#include "Adafruit_Thermal.h"

// Define constants and variables for buffering incoming serial data.
#if !defined(SERIAL_TX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_TX_BUFFER_SIZE 16
#else
#define SERIAL_TX_BUFFER_SIZE 64
#endif
#endif
#if !defined(SERIAL_RX_BUFFER_SIZE)
#if ((RAMEND - RAMSTART) < 1023)
#define SERIAL_RX_BUFFER_SIZE 16
#else
#define SERIAL_RX_BUFFER_SIZE 64
#endif
#endif
#if (SERIAL_TX_BUFFER_SIZE>256)
typedef uint16_t tx_buffer_index_t;
#else
typedef uint8_t tx_buffer_index_t;
#endif
#if  (SERIAL_RX_BUFFER_SIZE>256)
typedef uint16_t rx_buffer_index_t;
#else
typedef uint8_t rx_buffer_index_t;
#endif

#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E

void HardwareSerial_begin(volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
                          volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
                          volatile uint8_t *ucsrc, volatile uint8_t *udr, unsigned long baud, uint8_t config);
void HardwareSerial_end(volatile uint8_t *ucsrb);
int HardwareSerial_available(volatile uint8_t *ucsra, volatile uint8_t *ucsrb, volatile uint8_t *ucsrc,
                             rx_buffer_index_t rx_buffer_head, rx_buffer_index_t rx_buffer_tail);
int HardwareSerial_peek(rx_buffer_index_t rx_buffer_head, rx_buffer_index_t rx_buffer_tail, volatile uint8_t *rx_buffer);
int HardwareSerial_read(volatile uint8_t *ucsra, volatile uint8_t *ucsrb, volatile uint8_t *ucsrc,
                        rx_buffer_index_t *rx_buffer_head, rx_buffer_index_t *rx_buffer_tail, volatile uint8_t *rx_buffer);
int HardwareSerial_availableForWrite(tx_buffer_index_t tx_buffer_head, tx_buffer_index_t tx_buffer_tail);
void HardwareSerial_flush(volatile uint8_t *ucsrb, volatile uint8_t *ucsra, volatile uint8_t *sreg, volatile uint8_t *udr, volatile uint8_t *ucsra);
size_t HardwareSerial_write(uint8_t c, volatile uint8_t *ucsra, volatile uint8_t *udr, volatile uint8_t *ucsrb,
                            tx_buffer_index_t *tx_buffer_head, tx_buffer_index_t *tx_buffer_tail, volatile uint8_t *tx_buffer, uint8_t sreg);

#endif
