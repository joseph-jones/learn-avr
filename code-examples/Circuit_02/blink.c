#include <avr/io.h>
#include <util/delay.h>

#define POT 10000

// prepare ADC
void InitADC()
{
  // Select Vref=AVcc
  ADMUX |= _BV(REFS0);

  // set prescaller to 128 and enable ADC
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
}

// read ADC
uint16_t ReadADC(uint8_t ADCchannel)
{
  // Select ADCchannel with safety mask
  ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);

  // single conversion mode
  ADCSRA |= _BV(ADSC);

  // wait until ADC conversion is complete
  while( ADCSRA & _BV(ADSC) );

  return ADC;
}

int main(void)
{
  double potval;
  int i;
  // set PORTB PIN5 to output
  DDRB |= _BV(DDB5);

  InitADC();

  while(1)
  {
    potval = (double)ReadADC(0);

    for (i = 0; i < potval; ++i)
    {
    _delay_ms(1);
    }
    PORTB ^= _BV(PORTB5);
  }
}

