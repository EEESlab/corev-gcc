/* Simple test for COREV store post-increment MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 -std=gnu11 --save-temps" } */

#include <stdlib.h>

#define ARRAY_DIM (20) /* ARRAY_DIM = 20 to avoid loop unrolling */

signed char        char_array     [ARRAY_DIM];
signed short int   short_array    [ARRAY_DIM];
signed int         int_array      [ARRAY_DIM];
unsigned char      uns_char_array [ARRAY_DIM];
unsigned short int uns_short_array[ARRAY_DIM];
unsigned int       uns_int_array  [ARRAY_DIM];

void store_postinc(void)
{
  /* { dg-final { scan-assembler-times "cv\.s" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.sb .\\d+, 1\\(.\\d+!\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sh .\\d+, 2\\(.\\d+!\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sw .\\d+, 4\\(.\\d+!\\)" 2 } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    char_array[i]      = sizeof(signed char)       +i;
    short_array[i]     = sizeof(signed short int)  +i;
    int_array[i]       = sizeof(signed int)        +i;
    uns_char_array[i]  = sizeof(unsigned char)     +i;
    uns_short_array[i] = sizeof(unsigned short int)+i;
    uns_int_array[i]   = sizeof(unsigned int)      +i;
  }
}

int main(void)
{
  store_postinc();

  for(int i=0; i<ARRAY_DIM; i++)
  {
    if((char_array[i]        != (sizeof(signed char)       +i))
      || (short_array[i]     != (sizeof(signed short int)  +i))
      || (int_array[i]       != (sizeof(signed int)        +i))
      || (uns_char_array[i]  != (sizeof(unsigned char)     +i))
      || (uns_short_array[i] != (sizeof(unsigned short int)+i))
      || (uns_int_array[i]   != (sizeof(unsigned int)      +i)))
    {
      abort();
    }
  }

  return 0;
}

