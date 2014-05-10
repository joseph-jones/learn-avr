#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  /* set PORTB of output */
  DDRB |= _BV(DDB5);

  while(1)
  {
    _delay_ms(50);
    PORTB ^= _BV(PORTB5);
  }
}
