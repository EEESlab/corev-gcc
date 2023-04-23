/* Simple test for COREV store register MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 --save-temps" } */
/* { dg-timeout 10 } */

#include <stdlib.h>
#include <stdio.h>

#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (IMM12_BOUND + 4) /* ARRAY_DIM/2 must be >= 2048 to avoid post-mod displacement mem */

signed int array_0 [ARRAY_DIM];
signed int array_1 [ARRAY_DIM];
signed int array_2 [ARRAY_DIM];
signed int array_3 [ARRAY_DIM];
signed int array_4 [ARRAY_DIM];
signed int array_5 [ARRAY_DIM];

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

void load_reg(void)
{
  /* { dg-final { scan-assembler-times "cv\.l" 6 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lb .\\d+, .\\d+\\(.\\d+\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lbu .\\d+, .\\d+\\(.\\d+\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lh .\\d+, .\\d+\\(.\\d+\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lhu .\\d+, .\\d+\\(.\\d+\\)" 1 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, .\\d+\\(.\\d+\\)" 2 { xfail { riscv32-corev-elf && { any-opts "-O0" } } } } } */
  char_sum      += *((signed char *)        (array_0 + IMM12_BOUND));
  short_sum     += *((signed short int *)   (array_1 + IMM12_BOUND));
  int_sum       += *((signed int *)         (array_2 + IMM12_BOUND));
  uns_char_sum  += *((unsigned char *)      (array_3 + IMM12_BOUND));
  uns_short_sum += *((unsigned short int *) (array_4 + IMM12_BOUND));
  uns_int_sum   += *((unsigned int *)       (array_5 + IMM12_BOUND));
}

int main(void)
{
  array_init();
  
  load_reg();

  printf("%d, %d, %d, %d, %d, %d\n", char_sum, short_sum, int_sum, uns_char_sum, uns_short_sum, uns_int_sum);

  if((char_sum        != sizeof(signed char))
    || (short_sum     != sizeof(signed short int))
    || (int_sum       != sizeof(signed int))
    || (uns_char_sum  != sizeof(unsigned char))
    || (uns_short_sum != sizeof(unsigned short int))
    || (uns_int_sum   != sizeof(unsigned int)))
  {
    abort();
  }
  else
  {
    return 0;
  }
}
