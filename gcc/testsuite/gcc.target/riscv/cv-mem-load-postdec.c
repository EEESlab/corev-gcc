/* Simple test for COREV load post-decrement MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 --save-temps -fno-tree-forwprop" } */
/* { dg-timeout 10 } */

#include <stdlib.h>

#define ARRAY_DIM (20) /* ARRAY_DIM = 20 to avoid loop unrolling */

signed char        array_0 [ARRAY_DIM];
signed short int   array_1 [ARRAY_DIM];
signed int         array_2 [ARRAY_DIM];
unsigned char      array_3 [ARRAY_DIM];
unsigned short int array_4 [ARRAY_DIM];
unsigned int       array_5 [ARRAY_DIM];

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

void load_postdec(void)
{
  /* { dg-final { scan-assembler-times "cv\.l" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.lb .\\d+, -1\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lbu .\\d+, -1\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lh .\\d+, -2\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lhu .\\d+, -2\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, -4\\(.\\d+!\\)" 2 } } */
  signed char        * array_0_end = &array_0[ARRAY_DIM-1];
  signed short int   * array_1_end = &array_1[ARRAY_DIM-1];
  signed int         * array_2_end = &array_2[ARRAY_DIM-1];
  unsigned char      * array_3_end = &array_3[ARRAY_DIM-1];
  unsigned short int * array_4_end = &array_4[ARRAY_DIM-1];
  unsigned int       * array_5_end = &array_5[ARRAY_DIM-1];

  for(int i=0; i<ARRAY_DIM; i++)
  {
    char_sum      += *((signed char        *) (array_0_end - i));
    short_sum     += *((signed short int   *) (array_1_end - i));
    int_sum       += *((signed int         *) (array_2_end - i));
    uns_char_sum  += *((unsigned char      *) (array_3_end - i));
    uns_short_sum += *((unsigned short int *) (array_4_end - i));
    uns_int_sum   += *((unsigned int       *) (array_5_end - i));
  }
}

int main(void)
{
  array_init();

  load_postdec();

  if((char_sum        != sizeof(signed char)        * ARRAY_DIM)
    || (short_sum     != sizeof(signed short int)   * ARRAY_DIM)
    || (int_sum       != sizeof(signed int)         * ARRAY_DIM)
    || (uns_char_sum  != sizeof(unsigned char)      * ARRAY_DIM)
    || (uns_short_sum != sizeof(unsigned short int) * ARRAY_DIM)
    || (uns_int_sum   != sizeof(unsigned int)       * ARRAY_DIM))
  {
    abort();
  }
  else
  {
    return 0;
  }
}
