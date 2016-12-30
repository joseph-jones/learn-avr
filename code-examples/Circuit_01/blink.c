#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


ISR(TIMER1_COMPA_vect)
{
    PORTB ^= _BV(PB5);
}

int main(void)
{
    // set PORTB PIN5 for output
    DDRB |= _BV(DDB5);

    // setup 16-bit timer1
    // CTC mode
    // prescaler 64
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(WGM12);
    TIMSK1 |= _BV(OCIE1A);
    OCR1A = 15625;  // led blinks at 8Hz

    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    // Enable Interupts
    sei();
    while (1) sleep_cpu();
    sleep_disable();

}
