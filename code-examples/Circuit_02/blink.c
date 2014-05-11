#include <avr/io.h>
#include <avr/interrupt.h>

// prepare ADC
void InitADC()
{
    // Select Vref=AVcc
    ADMUX |= _BV(REFS0);
    // use ADC0
    ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));

    // we want the trigger event to be the timer
    ADCSRB |= _BV(ADTS2) | _BV(ADTS0);

    // set prescaler to 128 and enable ADC
    ADCSRA |= _BV(ADATE) | _BV(ADPS2) | _BV(ADIE) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
    ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect)
{
    // update OCR1A after ADC conversion
    OCR1A = 10 + (ADC * 60);
}

ISR(TIMER1_COMPB_vect)
{
    PORTB ^= _BV(PB5);
}

int main(void)
{
    InitADC();
    // set PORTB PIN5 for output
    DDRB |= _BV(DDB5);

    // setup 16-bit timer1 / Compare B
    // CTC mode
    // prescaler 64
    TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(WGM12);
    TIMSK1 |= _BV(OCIE1B);

    // Enable Interupts
    sei();


    while(1);
}

