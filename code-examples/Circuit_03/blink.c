#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

volatile uint8_t value;

ISR(TIMER1_COMPA_vect)
{
    if (value >= 0x0F)
        value = 0x00;
    else
        value = value + 0x02;
    PORTB = value;
}

int main(void)
{
    // enable portb for writing
    DDRB = 0xFF;
    value = 0xFF;

    // setup 16-bit timer1
    // CTC mode
    // prescaler 256
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= _BV(CS12) | _BV(WGM12);
    TIMSK1 |= _BV(OCIE1A);
    OCR1A = 0x5777;

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    // Enable Interupts
    sei();
    while (1) sleep_cpu();
    sleep_disable();

}
