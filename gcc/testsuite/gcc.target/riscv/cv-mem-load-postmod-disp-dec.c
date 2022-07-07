/* Simple test for COREV load post-modify displacement with decrement MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32im_xcorevmem1p0 -O1 --save-temps" } */

#include <stdlib.h>

#define LOOP_DIM (15) /* LOOP_DIM = 15 to avoid loop unrolling */
#define IMM12_BOUND_CHAR  (2048) /* 12-bit immediate signed displacement factor */
#define IMM12_BOUND_SHORT (1024) /* 12-bit immediate signed displacement factor */
#define IMM12_BOUND_INT   (512) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM_CHAR  (LOOP_DIM+1)*(IMM12_BOUND_CHAR) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */
#define ARRAY_DIM_SHORT (LOOP_DIM+1)*(IMM12_BOUND_SHORT) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */
#define ARRAY_DIM_INT   (LOOP_DIM+1)*(IMM12_BOUND_INT) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */

signed char        array_0 [ARRAY_DIM_CHAR];
unsigned char      array_3 [ARRAY_DIM_CHAR];
signed short int   array_1 [ARRAY_DIM_SHORT];
unsigned short int array_4 [ARRAY_DIM_SHORT];
signed int         array_2 [ARRAY_DIM_INT];
unsigned int       array_5 [ARRAY_DIM_INT];

int char_sum      = 0;
int short_sum     = 0;
int int_sum       = 0;
int uns_char_sum  = 0;
int uns_short_sum = 0;
int uns_int_sum   = 0;

void array_init(void)
{
  for(int i=0; i<ARRAY_DIM_CHAR; i++)
  {
    array_0[i] = sizeof(signed char);
    array_3[i] = sizeof(unsigned char);
  }
  for(int i=0; i<ARRAY_DIM_SHORT; i++)
  {  
    array_1[i] = sizeof(signed short int);
    array_4[i] = sizeof(unsigned short int);
  }
  for(int i=0; i<ARRAY_DIM_INT; i++)
  {
    array_2[i] = sizeof(signed int);
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
  signed char        * array_0_end = &array_0[ARRAY_DIM_CHAR-1];
  unsigned char      * array_3_end = &array_3[ARRAY_DIM_CHAR-1];
  signed short int   * array_1_end = &array_1[ARRAY_DIM_SHORT-1];
  unsigned short int * array_4_end = &array_4[ARRAY_DIM_SHORT-1];
  signed int         * array_2_end = &array_2[ARRAY_DIM_INT-1];
  unsigned int       * array_5_end = &array_5[ARRAY_DIM_INT-1];

  for(int i=0; i<LOOP_DIM; i++)
  {
    char_sum      += *((signed char *)       (array_0_end-(i*IMM12_BOUND_CHAR)));
    uns_char_sum  += *((unsigned char *)     (array_3_end-(i*IMM12_BOUND_CHAR)));
    short_sum     += *((signed short int *)  (array_1_end-(i*IMM12_BOUND_SHORT)));
    uns_short_sum += *((unsigned short int *)(array_4_end-(i*IMM12_BOUND_SHORT)));
    int_sum       += *((signed int *)        (array_2_end-(i*IMM12_BOUND_INT)));
    uns_int_sum   += *((unsigned int *)      (array_5_end-(i*IMM12_BOUND_INT)));
  }
}

int main(void)
{
  array_init();
  
  load_postmod_disp_dec();

  if((char_sum        != sizeof(signed char)        * LOOP_DIM)
    || (short_sum     != sizeof(signed short int)   * LOOP_DIM)
    || (int_sum       != sizeof(signed int)         * LOOP_DIM)
    || (uns_char_sum  != sizeof(unsigned char)      * LOOP_DIM)
    || (uns_short_sum != sizeof(unsigned short int) * LOOP_DIM)
    || (uns_int_sum   != sizeof(unsigned int)       * LOOP_DIM))
  {
    abort();
  }
  else
  {
    return 0;
  }
}
