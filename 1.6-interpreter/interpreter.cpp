/*
 * ===========================================================================
 *
 *       Filename:  interpreter.cpp
 *
 *    Description:  PC/UVa 110106/10033
 *
 *        Version:  1.0
 *        Created:  06/19/2011 10:44:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int registers[10] = {0};
    int memory[1000] = {0};
    char line[10];
    int n;
    fgets(line, 10, stdin);
    sscanf(line, "%d", &n);
    fgets(line, 10, stdin);
    for (int i=0; i<n; ++i) {
        memset(registers, 0, sizeof(registers));
        memset(memory, 0, sizeof(memory));
        int pc = 0;
        int instruct = 0;
        while (fgets(line, 10, stdin)!=NULL) {
            if (strlen(line) < 3) break;
            sscanf(line, "%d", &instruct);
            memory[pc++] = instruct;
        }
        pc = 0;
        int counter = 0;
        int it, ri, mi;
        while (pc < 1000) {
            instruct = memory[pc];
            if (instruct == 100) { 
                ++counter; 
                break;
            }
            it = instruct / 100;
            ri = (instruct / 10) % 10;
            mi = instruct % 10;
            switch (it) {
                case 2:
                    registers[ri] = mi;
                    ++pc;
                    break;
                case 3:
                    registers[ri] += mi;
                    registers[ri] %= 1000;
                    ++pc;
                    break;
                case 4:
                    registers[ri] *= mi;
                    registers[ri] %= 1000;
                    ++pc;
                    break;
                case 5:
                    registers[ri] = registers[mi];
                    ++pc;
                    break;
                case 6:
                    registers[ri] += registers[mi];
                    registers[ri] %= 1000;
                    ++pc;
                    break;
                case 7:
                    registers[ri] *= registers[mi];
                    registers[ri] %= 1000;
                    ++pc;
                    break;
                case 8:
                    registers[ri] = memory[registers[mi]];
                    ++pc;
                    break;
                case 9:
                    memory[registers[mi]] = registers[ri];
                    ++pc;
                    break;
                case 0:
                    if (registers[mi] != 0) {
                        pc = registers[ri];
                    } else {
                        ++pc;
                    }
                    break;
                default:
                    fprintf(stderr, "error instruction: %d\n", instruct);
                    break;
            }
            ++counter;
        }
        printf("%d\n", counter);
        if (i != n-1) printf("\n");
    }
    return EXIT_SUCCESS;
}			/* ----------  end of function main  ---------- */
