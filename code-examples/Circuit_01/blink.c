#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER1_OVF_vect)
{
    PORTB ^= _BV(PB5);
}

int main(void)
{
    // set PORTB PIN5 for output
    DDRB |= _BV(DDB5);

    // setup timer1 with prescaler 64
    TCCR1B |= _BV(CS10) | _BV(CS11);
    TIMSK1 |= _BV(TOIE1);

    // Enable Interupts
    sei();


    while(1);
}
