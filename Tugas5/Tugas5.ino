#include <avr/io.h>
#include <avr/interrupt.h>

#define OFF_STABLE     0
#define OFF_1XAWAL    1
#define OFF_1XSTABLE  2
#define ON_2XAWAL     3
#define ON_2XSTABLE   4

#define BUTTON 5
#define LED 13

int input = LOW;
int state = OFF_STABLE;
int counter = 0;

int debounceButton(int stateButton, int pin);
void init_int(void);

ISR(TIMER1_OVF_vect) {  // interrupt membaca input
  input = debounceButton(input, BUTTON);

  fsm(input, &state);
  
  TIFR1  = (1 << TOV1);
  TCNT1  = 65379; //interrupt 10ms
}

void setup() {  // put your setup code here, to run once:
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  
  init_int();
  Serial.begin(9600);
}

void loop() { // put your main code here, to run repeatedly:
  sei();
}

void fsm(int input, int *state) {
  switch(*state) {
    case OFF_STABLE: {  //S0
      Serial.println(OFF_STABLE);
      counter = 0;
      if(input == 1) {
        *state= OFF_1XAWAL;
      }
      break;
    }
    case OFF_1XAWAL: {  //S1
      Serial.println(OFF_1XAWAL);
      if(input == 0) {
        *state = OFF_1XSTABLE;
      }
      break;
    }
    case OFF_1XSTABLE: {  //S2
      Serial.println(OFF_1XSTABLE);
      if(input == 1) {
        *state = ON_2XAWAL;
      }
      else {
        counter++;
        if(counter >= 100) {
          *state = OFF_STABLE;
        }
      }
      break;
    }
    case ON_2XAWAL: { //S3
      Serial.println(ON_2XAWAL);
      counter = 0;
      if(input == 0) {
        *state = ON_2XSTABLE;
      }
      break;
    }
    case ON_2XSTABLE: { //S4
      Serial.println(ON_2XSTABLE);
      if(input == 1) {
        *state = ON_2XAWAL;
      }
      else {
        counter++;
        if(counter >= 500) {
          *state = OFF_STABLE;
        }  
      }
      break;
    }
  }
  
  switch(*state) {
    case OFF_STABLE:
    case OFF_1XAWAL:
    case OFF_1XSTABLE: {
      digitalWrite(LED, LOW);
      break;
    }
    case ON_2XAWAL:
    case ON_2XSTABLE: {
    digitalWrite(LED, HIGH);  
      break;
    }
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
  TCNT1  = 65379; //interrupt 10ms

  sei();
}
