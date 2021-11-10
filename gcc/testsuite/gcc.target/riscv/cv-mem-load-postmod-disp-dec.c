/* Simple test for COREV load post-modify displacement with decrement MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 -std=gnu11 --save-temps" } */

#include <stdlib.h>

#define LOOP_DIM (5) /* LOOP_DIM = 5 to avoid loop unrolling */
#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (LOOP_DIM+1)*(IMM12_BOUND) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */

signed char array_0 [ARRAY_DIM];
signed char array_1 [ARRAY_DIM];
signed char array_2 [ARRAY_DIM];
signed char array_3 [ARRAY_DIM];
signed char array_4 [ARRAY_DIM];
signed char array_5 [ARRAY_DIM];

int char_sum      = 0;
int short_sum     = 0;
int int_sum       = 0;
int uns_char_sum  = 0;
int uns_short_sum = 0;
int uns_int_sum   = 0;

void array_init(void)
{
  for(int i=0; i<ARRAY_DIM; i++)
  {
    array_0[i] = sizeof(signed char);
    array_1[i] = sizeof(signed short int);
    array_2[i] = sizeof(signed int);
    array_3[i] = sizeof(unsigned char);
    array_4[i] = sizeof(unsigned short int);
    array_5[i] = sizeof(unsigned int);
  }
}

void load_postmod_disp_dec(void)
{
  /* { dg-final { scan-assembler-times "cv\.l" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.lb .\\d+, -2048\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lbu .\\d+, -2048\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lh .\\d+, -2048\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lhu .\\d+, -2048\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, -2048\\(.\\d+!\\)" 2 } } */
  for(int i=1; i<LOOP_DIM+1; i++)
  {
    char_sum      += *((signed char *)       (array_0+((LOOP_DIM-i)*IMM12_BOUND)));
    short_sum     += *((signed short int *)  (array_1+((LOOP_DIM-i)*IMM12_BOUND)));
    int_sum       += *((signed int *)        (array_2+((LOOP_DIM-i)*IMM12_BOUND)));
    uns_char_sum  += *((unsigned char *)     (array_3+((LOOP_DIM-i)*IMM12_BOUND)));
    uns_short_sum += *((unsigned short int *)(array_4+((LOOP_DIM-i)*IMM12_BOUND)));
    uns_int_sum   += *((unsigned int *)      (array_5+((LOOP_DIM-i)*IMM12_BOUND)));
  }
}
