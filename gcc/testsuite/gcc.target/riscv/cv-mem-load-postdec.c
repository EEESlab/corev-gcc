/* Simple test for COREV load post-decrement MEM extensions */
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
    char_array[i]      = sizeof(signed char);
    short_array[i]     = sizeof(signed short int);
    int_array[i]       = sizeof(signed int);
    uns_char_array[i]  = sizeof(unsigned char);
    uns_short_array[i] = sizeof(unsigned short int);
    uns_int_array[i]   = sizeof(unsigned int);
  }
}

void load_postdec(void)
{
  /* { dg-final { scan-assembler-times "cv\.l" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.lb .\\d+, -1\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lbu .\\d+, -1\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lh .\\d+, -2\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lhu .\\d+, -2\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, -4\\(.\\d+!\\)" 2 } } */
  for(int i=1; i<ARRAY_DIM+1; i++)
  {
    char_sum      += char_array[ARRAY_DIM-i];
    short_sum     += short_array[ARRAY_DIM-i];
    int_sum       += int_array[ARRAY_DIM-i];
    uns_char_sum  += uns_char_array[ARRAY_DIM-i];
    uns_short_sum += uns_short_array[ARRAY_DIM-i];
    uns_int_sum   += uns_int_array[ARRAY_DIM-i];
  }
}

int main(void)
{
  array_init();
  
  load_postdec();

  if((char_sum        != sizeof(signed char)*ARRAY_DIM)
    || (short_sum     != sizeof(signed short int)*ARRAY_DIM)
    || (int_sum       != sizeof(signed int)*ARRAY_DIM)
    || (uns_char_sum  != sizeof(unsigned char)*ARRAY_DIM)
    || (uns_short_sum != sizeof(unsigned short int)*ARRAY_DIM)
    || (uns_int_sum   != sizeof(unsigned int)*ARRAY_DIM))
  {
    abort();
  }
  else
  {
    return 0;
  }
}
