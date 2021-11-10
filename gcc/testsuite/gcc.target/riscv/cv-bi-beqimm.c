/* Test for COREV branching immediate beq BI extensions */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevbi1p0 -std=gnu11 --save-temps" } */

#include <stdlib.h>

#define ARRAY_DIM (20) /* ARRAY_DIM = 20 to avoid loop unrolling */

int array1[ARRAY_DIM];
int array2[ARRAY_DIM];

void array_init(void)
{
  for(int i=0; i<ARRAY_DIM; i++)
  {
    array1[i] = sizeof(signed int);
    array2[i] = sizeof(unsigned int);
  }
}

/* The compiler tends to switch from NE to EQ for a reason of cost */
void beqimm()
{
  for(int i=0; i<ARRAY_DIM; i++)
  {
    if(i != 15) array1[i] = i;
  }

  for(int i=0; i>-ARRAY_DIM; i--)
  {
    if(i != -16) array2[-i] = i;
  }
}

int main(void)
{
  array_init();
  
  beqimm();

  for(int i=0; i<ARRAY_DIM; i++)
  {
    if(i != 15)
    {
      if(array1[i] != i) abort();
    }
    else
    {
      if(array1[i] != sizeof(signed int)) abort();
    }
  }

  for(int i=0; i<ARRAY_DIM; i++)
  {
    if(i != 16)
    {
      if(array2[i] != -i) abort();
    }
    else
    {
      if(array2[i] != sizeof(unsigned int)) abort();
    }
  }

  return 0;

}
