#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

// file ini berisi FSM yang akan diuji
// frekuensi FSM 1000 Hz

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
      if(input == 1) {
        *state= OFF_1XAWAL;
      }
      break;
    }
    case OFF_1XAWAL: {  //S1
      if(input == 0) {
        *state = OFF_1XSTABLE;
      }
      break;
    }
    case OFF_1XSTABLE: {  //S2
      if(input == 1) {
        *state = ON_2XAWAL;
        *counter = 0;
      }
      else {
        *counter += 1;
        if(*counter >= 1000) {
          *state = OFF_STABLE;
          *counter = 0;
        }
      }
      break;
    }
    case ON_2XAWAL: { //S3
      if(input == 0) {
        *state = ON_2XSTABLE;
      }
      break;
    }
    case ON_2XSTABLE: { //S4
      if(input == 1) {
        *state = ON_INTERRUPT;
        *counter = 0;
      }
    else {
    *counter += 1;
    if(*counter >= 5000) {
      *state = OFF_STABLE;
      *counter = 0;
    }  
    }
      break;
    }
    case ON_INTERRUPT: {  //S5
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
