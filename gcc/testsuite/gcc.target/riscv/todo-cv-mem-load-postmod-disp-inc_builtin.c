/* Simple test for COREV load post-modify displacement with increment MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 --save-temps" } */

#include <stdlib.h>

#define LOOP_DIM (10) /* LOOP_DIM = 10 to avoid loop unrolling */
#define IMM12_BOUND (2047) /* 12-bit immediate signed displacement factor */
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
  for(int i=0; i<LOOP_DIM; i++)
  {
    *((signed char *)       (array_0+(i*IMM12_BOUND))) = sizeof(signed char)       ;
    *((signed short int *)  (array_1+(i*IMM12_BOUND))) = sizeof(signed short int)  ;
    *((signed int *)        (array_2+(i*IMM12_BOUND))) = sizeof(signed int)        ;
    *((unsigned char *)     (array_3+(i*IMM12_BOUND))) = sizeof(unsigned char)     ;
    *((unsigned short int *)(array_4+(i*IMM12_BOUND))) = sizeof(unsigned short int);
    *((unsigned int *)      (array_5+(i*IMM12_BOUND))) = sizeof(unsigned int)      ;
  }
}

void load_postmod_disp_inc(void)
{
  /* { dg-final { scan-assembler-times "cv\.l" 6 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lb .\\d+, 2047\\(.\\d+!\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lbu .\\d+, 2047\\(.\\d+!\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lh .\\d+, 2047\\(.\\d+!\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lhu .\\d+, 2047\\(.\\d+!\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, 2047\\(.\\d+!\\)" 2 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    char_sum      += *((signed char *)       (array_0+(i*IMM12_BOUND)));
    short_sum     += *((signed short int *)  (array_1+(i*IMM12_BOUND)));
    int_sum       += *((signed int *)        (array_2+(i*IMM12_BOUND)));
    uns_char_sum  += *((unsigned char *)     (array_3+(i*IMM12_BOUND)));
    uns_short_sum += *((unsigned short int *)(array_4+(i*IMM12_BOUND)));
    uns_int_sum   += *((unsigned int *)      (array_5+(i*IMM12_BOUND)));
  }
}
