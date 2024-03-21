#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#if defined(HAVE_HWSERIAL0) || defined(HAVE_HWSERIAL1) || defined(HAVE_HWSERIAL2) || defined(HAVE_HWSERIAL3)


#if defined(HAVE_HWSERIAL0)
void serialEvent() __attribute__((weak));
bool Serial0_available() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL1)
void serialEvent1() __attribute__((weak));
bool Serial1_available() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL2)
void serialEvent2() __attribute__((weak));
bool Serial2_available() __attribute__((weak));
#endif

#if defined(HAVE_HWSERIAL3)
void serialEvent3() __attribute__((weak));
bool Serial3_available() __attribute__((weak));
#endif

#endif


void serialEventRun(void)
{
#if defined(HAVE_HWSERIAL0)
  if (Serial0_available && serialEvent && Serial0_available()) serialEvent();
#endif
#if defined(HAVE_HWSERIAL1)
  if (Serial1_available && serialEvent1 && Serial1_available()) serialEvent1();
#endif
#if defined(HAVE_HWSERIAL2)
  if (Serial2_available && serialEvent2 && Serial2_available()) serialEvent2();
#endif
#if defined(HAVE_HWSERIAL3)
  if (Serial3_available && serialEvent3 && Serial3_available()) serialEvent3();
#endif
}

// Macro definition to guard critical sections when needed for large TX buffer sizes
#if (SERIAL_TX_BUFFER_SIZE > 256)
#define TX_BUFFER_ATOMIC ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define TX_BUFFER_ATOMIC
#endif


void HardwareSerial__tx_udr_empty_irq(void)
{
  // If interrupts are enabled, there must be more data in the output
  // buffer. Send the next byte
  unsigned char c = _tx_buffer[_tx_buffer_tail];
  _tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;

  *_udr = c;

  // Clear the TXC bit -- "can be cleared by writing a one to its bit
  // location". This makes sure flush() won't return until the bytes
  // actually got written. Other r/w bits are preserved, and zeroes
  // written to the rest.

#ifdef MPCM0
  *_ucsra = ((*_ucsra) & ((1 << U2X0) | (1 << MPCM0))) | (1 << TXC0);
#else
  *_ucsra = ((*_ucsra) & ((1 << U2X0) | (1 << TXC0)));
#endif

  if (_tx_buffer_head == _tx_buffer_tail) {
    // Buffer empty, so disable interrupts
    cbi(*_ucsrb, UDRIE0);
  }
}

void HardwareSerial_begin(unsigned long baud, byte config, volatile uint8_t *ucsra, volatile uint8_t *ucsrb, volatile uint8_t *ucsrc, volatile uint8_t *ubrrh, volatile uint8_t *ubrrl)
{
  // Try u2x mode first
  uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
  *ucsra = 1 << U2X0;

  // hardcoded exception for 57600 for compatibility with the bootloader
  // shipped with the Duemilanove and previous boards and the firmware
  // on the 8U2 on the Uno and Mega 2560. Also, The baud_setting cannot
  // be > 4095, so switch back to non-u2x mode if the baud rate is too
  // low.
  if (((F_CPU == 16000000UL) && (baud == 57600)) || (baud_setting > 4095))
  {
    *ucsra = 0;
    baud_setting = (F_CPU / 8 / baud - 1) / 2;
  }

  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  *ubrrh = baud_setting >> 8;
  *ubrrl = baud_setting;

  _written = false;

  //set the data bits, parity, and stop bits
#if defined(__AVR_ATmega8__)
  config |= 0x80; // select UCSRC register (shared with UBRRH)
#endif
  *ucsrc = config;
  
  sbi(*ucsrb, RXEN0);
  sbi(*ucsrb, TXEN0);
  sbi(*ucsrb, RXCIE0);
  cbi(*ucsrb, UDRIE0);
}

void HardwareSerial_end(volatile uint8_t *ucsrb)
{
  // wait for transmission of outgoing data
  flush();

  cbi(*ucsrb, RXEN0);
  cbi(*ucsrb, TXEN0);
  cbi(*ucsrb, RXCIE0);
  cbi(*ucsrb, UDRIE0);
  
  // clear any received data
  _rx_buffer_head = _rx_buffer_tail;
}

int HardwareSerial_available(uint8_t rx_buffer_head, uint8_t rx_buffer_tail)
{
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + rx_buffer_head - rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}
int HardwareSerial_peek(uint8_t rx_buffer_head, uint8_t rx_buffer_tail, volatile uint8_t *rx_buffer)
{
  if (rx_buffer_head == rx_buffer_tail) {
    return -1;
  } else {
    return rx_buffer[rx_buffer_tail];
  }
}

int HardwareSerial_read(uint8_t *rx_buffer, uint8_t *rx_buffer_head, uint8_t *rx_buffer_tail)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (*rx_buffer_head == *rx_buffer_tail) {
    return -1;
  } else {
    unsigned char c = rx_buffer[*rx_buffer_tail];
    *rx_buffer_tail = (*rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}

int HardwareSerial_availableForWrite(uint8_t tx_buffer_head, uint8_t tx_buffer_tail)
{
  tx_buffer_index_t head;
  tx_buffer_index_t tail;

  TX_BUFFER_ATOMIC {
    head = tx_buffer_head;
    tail = tx_buffer_tail;
  }
  if (head >= tail) return SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

void HardwareSerial_flush(uint8_t *ucsrb, uint8_t *ucsra, uint8_t *sreg, volatile uint8_t *udr, volatile uint8_t *ucsra)
{
  // If we have never written a byte, no need to flush. This special
  // case is needed since there is no way to force the TXC (transmit
  // complete) bit to 1 during initialization
  if (!_written)
    return;

  while (bit_is_set(*ucsrb, UDRIE0) || bit_is_clear(*ucsra, TXC0)) {
    if (bit_is_clear(*sreg, SREG_I) && bit_is_set(*ucsrb, UDRIE0))
    // Interrupts are globally disabled, but the DR empty
    // interrupt should be enabled, so poll the DR empty flag to
    // prevent deadlock
    if (bit_is_set(*ucsra, UDRE0))
      HardwareSerial__tx_udr_empty_irq(ucsra, udr);
  }
  // If we get here, nothing is queued anymore (DRIE is disabled) and
  // the hardware finished transmission (TXC is set).
}

size_t HardwareSerial_write(uint8_t c, uint8_t *ucsra, volatile uint8_t *udr, volatile uint8_t *ucsrb, tx_buffer_index_t *tx_buffer_head, tx_buffer_index_t *tx_buffer_tail, volatile uint8_t *tx_buffer, uint8_t sreg)
{
  _written = true;
  // If the buffer and the data register is empty, just write the byte
  // to the data register and be done. This shortcut helps
  // significantly improve the effective datarate at high (>
  // 500kbit/s) bitrates, where interrupt overhead becomes a slowdown.
  if (*tx_buffer_head == *tx_buffer_tail && bit_is_set(*ucsra, UDRE0)) {
    // If TXC is cleared before writing UDR and the previous byte
    // completes before writing to UDR, TXC will be set but a byte
    // is still being transmitted causing flush() to return too soon.
    // So writing UDR must happen first.
    // Writing UDR and clearing TC must be done atomically, otherwise
    // interrupts might delay the TXC clear so the byte written to UDR
    // is transmitted (setting TXC) before clearing TXC. Then TXC will
    // be cleared when no bytes are left, causing flush() to hang
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      *udr = c;
#ifdef MPCM0
      *ucsra = ((*ucsra) & ((1 << U2X0) | (1 << MPCM0))) | (1 << TXC0);
#else
      *ucsra = ((*ucsra) & ((1 << U2X0) | (1 << TXC0)));
#endif
    }
    return 1;
  }
  tx_buffer_index_t i = (*tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;
  
  // If the output buffer is full, there's nothing for it other than to 
  // wait for the interrupt handler to empty it a bit
  while (i == *tx_buffer_tail) {
    if (bit_is_clear(*sreg, SREG_I)) {
      // Interrupts are disabled, so we'll have to poll the data
      // register empty flag ourselves. If it is set, pretend an
      // interrupt has happened and call the handler to free up
      // space for us.
      if(bit_is_set(*ucsra, UDRE0))
        HardwareSerial__tx_udr_empty_irq(ucsra, udr);
    } else {
      // nop, the interrupt handler will free up space for us
    }
  }

  tx_buffer[*tx_buffer_head] = c;

  // make atomic to prevent execution of ISR between setting the
  // head pointer and setting the interrupt flag resulting in buffer
  // retransmission
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    *tx_buffer_head = i;
    sbi(*ucsrb, UDRIE0);
  }
  
  return 1;
}
