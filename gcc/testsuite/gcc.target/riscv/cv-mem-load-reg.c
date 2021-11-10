/* Simple test for COREV store register MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 -std=gnu11 --save-temps" } */

#include <stdlib.h>

#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (IMM12_BOUND + 4) /* ARRAY_DIM/2 must be >= 2048 to avoid post-mod displacement mem */

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

void load_reg(void)
{
  /* { dg-final { scan-assembler-times "cv\.l" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.lb .\\d+, .\\d+\\(.\\d+\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lbu .\\d+, .\\d+\\(.\\d+\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lh .\\d+, .\\d+\\(.\\d+\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lhu .\\d+, .\\d+\\(.\\d+\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  char_sum      += array_0     [IMM12_BOUND];
  short_sum     += array_1    [IMM12_BOUND];
  int_sum       += array_2      [IMM12_BOUND];
  uns_char_sum  += array_3 [IMM12_BOUND];
  uns_short_sum += array_4[IMM12_BOUND];
  uns_int_sum   += array_5  [IMM12_BOUND];
}

int main(void)
{
  array_init();
  
  load_reg();

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
