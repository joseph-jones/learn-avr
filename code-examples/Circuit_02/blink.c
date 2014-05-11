#include <avr/io.h>
#include <avr/interrupt.h>

// prepare ADC
void InitADC()
{
    // Select Vref=AVcc
    ADMUX |= _BV(REFS0);
    // use ADC0
    ADMUX &= ~(_BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0));

    // set prescaler to 128 and enable ADC
    ADCSRA |= _BV(ADATE) | _BV(ADPS2) | _BV(ADIE) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
    ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect)
{
    // update OCR1A after ADC conversion
    OCR1A = 10 + (ADC * 60);
}

ISR(TIMER1_COMPA_vect)
{
    PORTB ^= _BV(PB5);
}

int main(void)
{
    InitADC();
    // set PORTB PIN5 for output
    DDRB |= _BV(DDB5);

    // setup 16-bit timer1
    // CTC mode
    // prescaler 64
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= _BV(CS10) | _BV(CS11) | _BV(WGM12);
    TIMSK1 |= _BV(OCIE1A);

    // Enable Interupts
    sei();


    while(1);
}

