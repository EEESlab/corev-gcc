/* Test for COREV MEM extensions with nested loops */
/* { dg-do run { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -O1 -std=gnu11 --save-temps" } */

#include <stdlib.h>

#define N_ROW_A 10
#define N_COL_A 10
#define N_ROW_B 10
#define N_COL_B 10

#define MATRIX_A_DIM N_ROW_A*N_COL_A
#define MATRIX_B_DIM N_COL_B*N_ROW_B
#define MATRIX_C_DIM N_ROW_A*N_COL_B

int matrix_a[MATRIX_A_DIM];
int matrix_b[MATRIX_B_DIM];
int matrix_c[MATRIX_C_DIM];

int partial_sum = 0;

#pragma GCC push_options
#pragma GCC optimize ("-O0")
void matmul_init(void)
{
  for(int i=0; i<MATRIX_A_DIM; i++) matrix_a[i] = 1;
  for(int i=0; i<MATRIX_B_DIM; i++) matrix_b[i] = 1;
  for(int i=0; i<MATRIX_C_DIM; i++) matrix_c[i] = 0;
}
#pragma GCC pop_options

void matmul(void)
{
  /* { dg-final { scan-assembler-times "cv\.sw .\\d+, 4\\(.\\d+!\\)" 1 } } */
  /* { dg-final { scan-assembler-times "cv\.lw .\\d+, \\d+\\(.\\d+!\\)" 2 } } */
  int j;
  int i;
  int k;
  for(j=0; j<N_ROW_A; j++)
  {
    for(i=0; i<N_COL_B; i++)
    {
      partial_sum = 0;
      /* two loads with indexed post-incrementing */
      for(k=0; k<N_COL_A; k++)
      {
        partial_sum += matrix_a[k + j*N_COL_A] * matrix_b[k*N_COL_B + i];
      }
      /* one store with indexed post-incrementing */
      matrix_c[i + j*N_COL_B] = partial_sum;
    }
  }
}

int main(void)
{
  matmul_init();

  matmul();

  int i;
  for (i = 0; i < MATRIX_C_DIM; ++i)
  {
    if (matrix_c[i] != 10)
    {
      abort();
    }
  }

  return 0;
}
