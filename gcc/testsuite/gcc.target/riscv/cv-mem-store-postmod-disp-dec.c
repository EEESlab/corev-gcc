/* Simple test for COREV store post-modify displacement with decrement MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 --save-temps" } */

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

void store_postmod_disp_dec(void)
{
  /* { dg-final { scan-assembler-times "cv\.s" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.sb .\\d+, -2048\\(.\\d+!\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sh .\\d+, -2048\\(.\\d+!\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sw .\\d+, -2048\\(.\\d+!\\)" 2 } } */
  for(int i=1; i<LOOP_DIM+1; i++)
  {
    *((signed char *)       (array_0+((LOOP_DIM-i)*IMM12_BOUND))) = sizeof(signed char)       +i;
    *((signed short int *)  (array_1+((LOOP_DIM-i)*IMM12_BOUND))) = sizeof(signed short int)  +i;
    *((signed int *)        (array_2+((LOOP_DIM-i)*IMM12_BOUND))) = sizeof(signed int)        +i;
    *((unsigned char *)     (array_3+((LOOP_DIM-i)*IMM12_BOUND))) = sizeof(unsigned char)     +i;
    *((unsigned short int *)(array_4+((LOOP_DIM-i)*IMM12_BOUND))) = sizeof(unsigned short int)+i;
    *((unsigned int *)      (array_5+((LOOP_DIM-i)*IMM12_BOUND))) = sizeof(unsigned int)      +i;
  }
}

int main(void)
{
  store_postmod_disp_dec();

  for(int i=1; i<LOOP_DIM+1; i++)
  {
    if((*((signed char *)           (array_0+((LOOP_DIM-i)*IMM12_BOUND))) != sizeof(signed char)       +i)
        || (*((signed short int *)  (array_1+((LOOP_DIM-i)*IMM12_BOUND))) != sizeof(signed short int)  +i)
        || (*((signed int *)        (array_2+((LOOP_DIM-i)*IMM12_BOUND))) != sizeof(signed int)        +i)
        || (*((unsigned char *)     (array_3+((LOOP_DIM-i)*IMM12_BOUND))) != sizeof(unsigned char)     +i)
        || (*((unsigned short int *)(array_4+((LOOP_DIM-i)*IMM12_BOUND))) != sizeof(unsigned short int)+i)
        || (*((unsigned int *)      (array_5+((LOOP_DIM-i)*IMM12_BOUND))) != sizeof(unsigned int)      +i))
    {
      abort();
    }
  }

  return 0;
}
