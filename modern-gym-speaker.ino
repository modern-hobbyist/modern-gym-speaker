#include <Arduino.h>

#include <IRremote.hpp>
#include "command-definitions.h"
#include "pitches.h"
#define DECODE_SAMSUNG

#define IR_RECEIVE_PIN 9
#define DECODE
#define NOTE_LENGTH 500
#define BUZZER 3
#define COUNT_DOWN_TIMER 3000

int lastNoteChange;
bool buzzOn = false;

int clockStartedMillis;
bool countDown = false;

void setup() {
    Serial.begin(115200);

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    tone(BUZZER, NOTE_C6, NOTE_LENGTH);
    delay(NOTE_LENGTH);
    noTone(BUZZER);
}

void loop() {
    if (IrReceiver.decode()) {
      /* 
       *  Ignore repeated commands using the flags
       */
      if(!(IrReceiver.decodedIRData.flags & (IRDATA_FLAGS_IS_AUTO_REPEAT | IRDATA_FLAGS_IS_REPEAT)) && IrReceiver.decodedIRData.command != NULL) {
        // Print a short summary of received data
        #if defined(DECODE)
          IrReceiver.printIRResultShort(&Serial);
        #endif
        
        if (IrReceiver.decodedIRData.command == POWER_BTN) {
            // do something
        } else if (IrReceiver.decodedIRData.command == INPUT_BTN) {
            // do something else
        } else if (IrReceiver.decodedIRData.command == UP_BTN) {
          Serial.println("Up!");
        } else if (IrReceiver.decodedIRData.command == OK_BTN) {
          Serial.println("OK!");
          clockStartedMillis = millis();
          countDown = true;
        }
      }
                    
      /*
       * !!!Important!!!
       */
      IrReceiver.resume(); // Enable receiving of the next value
    }

    if(countDown && millis() - clockStartedMillis < COUNT_DOWN_TIMER){
      if(millis() - lastNoteChange > NOTE_LENGTH){
        lastNoteChange = millis();
        if(buzzOn){
          noTone(BUZZER);
          buzzOn = false;
        } else {
          tone(BUZZER, NOTE_C6, NOTE_LENGTH);
          buzzOn = true;
        }
//        Serial.println("Here1");
      }
//      Serial.println("Here2");
    } else {
      countDown = false;
      buzzOn = false;
//      Serial.println("Here3");
    }
}
