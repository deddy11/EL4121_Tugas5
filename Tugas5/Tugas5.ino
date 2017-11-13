#include <avr/io.h>
#include <avr/interrupt.h>
#include "fsm.h"

#define BUTTON 5
#define LED 13

int input = LOW;
int state = 0;
int counter = 0;
int output = 0;

int debounceButton(int stateButton, int pin);
void init_int(void);

ISR(TIMER1_OVF_vect) {  // interrupt membaca input
  input = debounceButton(input, BUTTON);

  fsm(input, &state, &output, &counter);
  
  TIFR1  = (1 << TOV1);
  TCNT1  = 65519;	//interrupt 1ms
}

void setup() {  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  
  init_int();
  Serial.begin(9600);
}

void loop() { // put your main code here, to run repeatedly:
  sei();
  if (output == 1) {
	digitalWrite(LED, HIGH);
  }else {
	digitalWrite(LED, LOW);
  }
}

int debounceButton(int stateButton, int pin) {
  int stateNow = digitalRead(pin);
  if(stateButton != stateNow) {
    delay(10);
    stateNow = digitalRead(pin);
  }
  return stateNow;
}

void init_int(void) {
  TIMSK1 = 0b000000;
  TIMSK1 = _BV(TOIE1);  //mengaktifkan Overflow Interrupt

  TCCR1A = 0;
  TCCR1B = 0b00001101; //prescalar 1024
  TCNT1  = 65519;	//interrupt 1ms

  sei();
}
