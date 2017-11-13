/* 
 * File:   main.c
 * Author: Deddy Welsan
 * NIM	 : 13214148
 * Software penguji FSM program menyalakan lampu
 * Created on November 10, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

/**
 * menguji FSM dengan input dari text file
 * @param filename
 * @return 
 */

void test_fsm(char *filename) {
    int jumlah_error = 0;
    int baris_counter = 0;
    char buffer[1024];
    FILE *f;
    f = fopen(filename, "r");
    // parameter untuk FSM
    int input = 0; 
    int state = 0;
    int led;
    int counter = 0;
            
    for (; !feof(f);) {
        char * hasil;
        hasil = fgets(buffer, 1024, f); // ambil 1 baris dari textfile
        if (hasil != NULL) {
            int kolom1;
            int kolom2;

            sscanf(buffer, "%d,%d", &kolom1, &kolom2);
            {
				input = kolom1;
				fsm(input, &state, &led, &counter);
				baris_counter++;

				printf("baris %3d %d %d %d", baris_counter, kolom1, kolom2, led);
				if (led != kolom2) {
					printf(" error");
					jumlah_error++;
				}
				printf("\n");
			}               
        }
    }
    printf("jumlah error:%d\n",jumlah_error);   // seharusnya jumlah error adalah 0
}

int main(int argc, char** argv) {
    test_fsm("test.csv"); // uji dengan file CSV dengan pola input tertentu
    return (EXIT_SUCCESS);
}

