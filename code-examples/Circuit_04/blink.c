#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


int ledPins[] = { PD2, PD3, PD4, PD5, PD6, PD7, PB0, PB1 };

int idx = 0;

ISR(TIMER1_COMPA_vect)
{
    if (idx%8 < 6) {
        PORTD ^= _BV(ledPins[idx%8]);
    }
    else {
        PORTB ^= _BV(ledPins[idx%8]);
    }
    idx += 1;
}

int main(void)
{
    // set PORTB PIN0 and PIN1 for output
    DDRB |= _BV(DDB0) | _BV(DDB1);
    // set PORTD PIN2 thru PIN7 for output
    DDRD |= _BV(DDD2) 
         | _BV(DDD3) 
         | _BV(DDD4)
         | _BV(DDD5)
         | _BV(DDD6)
         | _BV(DDD7);

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
