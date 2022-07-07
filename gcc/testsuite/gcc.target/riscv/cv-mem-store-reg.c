/* Simple test for COREV store register MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 --save-temps" } */

#include <stdlib.h>

#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (IMM12_BOUND + 4) /* ARRAY_DIM/2 must be >= 2048 to avoid post-mod displacement mem */

signed int array_0 [ARRAY_DIM];
signed int array_1 [ARRAY_DIM];
signed int array_2 [ARRAY_DIM];
signed int array_3 [ARRAY_DIM];
signed int array_4 [ARRAY_DIM];
signed int array_5 [ARRAY_DIM];

void store_reg(void)
{
  /* { dg-final { scan-assembler-times "cv\.s" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.sb .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sh .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sw .\\d+, .\\d+\\(.\\d+\\)" 2 } } */
  *((signed char *)        (array_0 + IMM12_BOUND)) = sizeof(signed char);
  *((signed short int *)   (array_1 + IMM12_BOUND)) = sizeof(signed short int);
  *((signed int *)         (array_2 + IMM12_BOUND)) = sizeof(signed int);
  *((unsigned char *)      (array_3 + IMM12_BOUND)) = sizeof(unsigned char);
  *((unsigned short int *) (array_4 + IMM12_BOUND)) = sizeof(unsigned short int);
  *((unsigned int *)       (array_5 + IMM12_BOUND)) = sizeof(unsigned int);
}

int main(void)
{
  store_reg();

  if(  (array_0[IMM12_BOUND] != sizeof(signed char))
    || (array_1[IMM12_BOUND] != sizeof(signed short int))
    || (array_2[IMM12_BOUND] != sizeof(signed int))
    || (array_3[IMM12_BOUND] != sizeof(unsigned char))
    || (array_4[IMM12_BOUND] != sizeof(unsigned short int))
    || (array_5[IMM12_BOUND] != sizeof(unsigned int)))
  {
    abort();
  }
  else
  {
    return 0;
  }
}
