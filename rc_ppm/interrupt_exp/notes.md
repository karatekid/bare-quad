## My experience setting this up.

I started this off by attempting an example found
[here](http://playground.arduino.cc/Main/PinChangeInterrupt), but since my
Arduino UNO and Arduino duemilanove inexplicably stopped communicating with my
computer I switched over to my Mega. It wasn't exactly cooperating. My interrupt
vector was never getting hit. I wasn't quite sure what was going on, I thought
there was a small chance that it might be because I was using the Mega board.
So, I checked out the docs for the
[328P](http://www.atmel.com/Images/doc8161.pdf) & the
[2560](http://www.atmel.com/images/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf).
After looking around awhile I found the specs for the pin change interrupts or
PCINT's for short. I found that the ADC0-5 pins on the mega don't have a PCINT,
that duty is relegated to ADC8-15 and it is no longer PCINT1_vect, but
PCINT2_vect. This makes our code not very transferrable inbetween MEGA and UNO
code.

I found a good `avr-libc` manual
[here](http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html).
