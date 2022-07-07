/* Simple test for COREV store post-increment MEM extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 --save-temps" } */

#include <stdlib.h>

#define ARRAY_DIM (20) /* ARRAY_DIM = 20 to avoid loop unrolling */

signed char        array_0 [ARRAY_DIM];
signed short int   array_1 [ARRAY_DIM];
signed int         array_2 [ARRAY_DIM];
unsigned char      array_3 [ARRAY_DIM];
unsigned short int array_4 [ARRAY_DIM];
unsigned int       array_5 [ARRAY_DIM];

void store_postinc(void)
{
  /* { dg-final { scan-assembler-times "cv\.s" 6 } } */
  /* { dg-final { scan-assembler-times "cv\.sb .\\d+, 1\\(.\\d+!\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sh .\\d+, 2\\(.\\d+!\\)" 2 } } */
  /* { dg-final { scan-assembler-times "cv\.sw .\\d+, 4\\(.\\d+!\\)" 2 } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
     array_0[i] =  sizeof(signed char)       ;
     array_1[i] =  sizeof(signed short int)  ;
     array_2[i] =  sizeof(signed int)        ;
     array_3[i] =  sizeof(unsigned char)     ;
     array_4[i] =  sizeof(unsigned short int);
     array_5[i] =  sizeof(unsigned int)      ;
  }
}

int main(void)
{
  store_postinc();

  for(int i=0; i<ARRAY_DIM; i++)
  {
    if(  (array_0[i] != (sizeof(signed char)       ))
      || (array_1[i] != (sizeof(signed short int)  ))
      || (array_2[i] != (sizeof(signed int)        ))
      || (array_3[i] != (sizeof(unsigned char)     ))
      || (array_4[i] != (sizeof(unsigned short int)))
      || (array_5[i] != (sizeof(unsigned int)      )))
    {
      abort();
    }
  }

  return 0;
}

