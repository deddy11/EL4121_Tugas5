#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

// file ini berisi FSM yang akan diuji
// frekuensi FSM 10 Hz

/**
 * FSM under test
 * @param input
 * @param state
 * @param output
 */
 
//Deklarasi State
#define OFF_STABLE		0
#define OFF_1XAWAL		1
#define OFF_1XSTABLE	2
#define ON_2XAWAL		3
#define ON_2XSTABLE		4
#define ON_INTERRUPT	5

void fsm(int input, int *state, int *output, int *counter) {
  switch(*state) {
    case OFF_STABLE: {  //S0
      printf("State: OFF_STABLE\n");
      if(input == 1) {
        *state= OFF_1XAWAL;
      }
      break;
    }
    case OFF_1XAWAL: {  //S1
      printf("State: OFF_1XAWAL\n");
      if(input == 0) {
        *state = OFF_1XSTABLE;
      }
      break;
    }
    case OFF_1XSTABLE: {  //S2
      printf("State: OFF_1XSTABLE\n");
      if(input == 1) {
        *state = ON_2XAWAL;
        *counter = 0;
      }
      else {
        *counter += 1;
        if(*counter >= 10) {
          *state = OFF_STABLE;
          *counter = 0;
        }
      }
      break;
    }
    case ON_2XAWAL: { //S3
      printf("State: ON_2XAWAL\n");
      if(input == 0) {
        *state = ON_2XSTABLE;
      }
      break;
    }
    case ON_2XSTABLE: { //S4
      printf("State: ON_2XSTABLE\n");
      if(input == 1) {
        *state = ON_INTERRUPT;
        *counter = 0;
      }
    else {
    *counter += 1;
    if(*counter >= 50) {
      *state = OFF_STABLE;
      *counter = 0;
    }  
    }
      break;
    }
    case ON_INTERRUPT: {  //S5
      printf("State: ON_INTERRUPT\n");
      if(input == 0) {
        *state = ON_2XSTABLE;
      }
      break;
    }
  }
  
  switch(*state) {
    case OFF_STABLE:	//S0
    case OFF_1XAWAL:	//S1
    case OFF_1XSTABLE:{	//S2
		*output = 0;
		break;
	}
    case ON_2XAWAL:		//S3
	case ON_2XSTABLE:	//S4
    case ON_INTERRUPT:{	//S5
		*output = 1;
		break;
	}
  }

}
