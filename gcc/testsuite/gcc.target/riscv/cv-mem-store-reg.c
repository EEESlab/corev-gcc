/* Simple test for COREV store register MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 -std=gnu11 --save-temps" } */

#include <stdlib.h>

#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (IMM12_BOUND + 4) /* ARRAY_DIM/2 must be >= 2048 to avoid post-mod displacement mem */

signed char        char_array     [ARRAY_DIM];
signed short int   short_array    [ARRAY_DIM];
signed int         int_array      [ARRAY_DIM];
unsigned char      uns_char_array [ARRAY_DIM];
unsigned short int uns_short_array[ARRAY_DIM];
unsigned int       uns_int_array  [ARRAY_DIM];

void store_reg(void)
{
  /* { dg-final { scan-assembler-times "cv\.s" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.sb .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sh .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sw .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  char_array     [IMM12_BOUND] = sizeof(signed char);
  short_array    [IMM12_BOUND] = sizeof(signed short int);
  int_array      [IMM12_BOUND] = sizeof(signed int);
  uns_char_array [IMM12_BOUND] = sizeof(unsigned char);
  uns_short_array[IMM12_BOUND] = sizeof(unsigned short int);
  uns_int_array  [IMM12_BOUND] = sizeof(unsigned int);
}

int main(void)
{
  store_reg();

  if((char_array[IMM12_BOUND]        != sizeof(signed char))
    || (short_array[IMM12_BOUND]     != sizeof(signed short int))
    || (int_array[IMM12_BOUND]       != sizeof(signed int))
    || (uns_char_array[IMM12_BOUND]  != sizeof(unsigned char))
    || (uns_short_array[IMM12_BOUND] != sizeof(unsigned short int))
    || (uns_int_array[IMM12_BOUND]   != sizeof(unsigned int)))
  {
    abort();
  }
  else
  {
    return 0;
  }
}
