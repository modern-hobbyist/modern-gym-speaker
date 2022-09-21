# Modern Gym Timer

# Setup
* Note: Both the Tone library and the IRRemote library use the Timer2 
library which means, as soon as I output a tone from the buzzer, it 
freezes the IR receiver. To fix this, I had to go into the IRRemote 
library and change the default timer from Timer2 to Timer1

`IRremote/src/private/IRTimer.hpp` on line 72
```
// Arduino Duemilanove, Diecimila, LilyPad, Mini, Fio, Nano, etc
// ATmega328 and ATmega88
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328PB__) || 
defined(__AVR_ATmega168__) || defined(__AVR_ATmega88P__) || 
defined(__AVR_ATmega88PB__)
#  if !defined(IR_USE_AVR_TIMER1) && !defined(IR_USE_AVR_TIMER2)
#define IR_USE_AVR_TIMER1   // Uncomment this line
//#define IR_USE_AVR_TIMER2     // Comment this line OUT
#  endif 
```
