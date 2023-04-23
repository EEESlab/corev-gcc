/* Test for COREV MEM extensions with nested loops */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -fdump-rtl-combine" } */
/* { dg-skip-if "O0 has not combine pass" { *-corev-* } { any-opts "-O0" } } */
/* { dg-skip-if "Unrolling does not trigger the pattern" { *-corev-* } { any-opts "-funroll-loops" } } */

#define N_ROW_A 32
#define N_COL_A 32
#define N_ROW_B 32
#define N_COL_B 32

#define MATRIX_A_DIM N_ROW_A*N_COL_A
#define MATRIX_B_DIM N_COL_B*N_ROW_B
#define MATRIX_C_DIM N_ROW_A*N_COL_B

int matrix_a[MATRIX_A_DIM];
int matrix_b[MATRIX_B_DIM];
int matrix_c[MATRIX_C_DIM];

int partial_sum = 0;

void matmul(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadsi" 2 "combine" } } */
  /* { dg-final { scan-rtl-dump-times "cv_storesi" 1 "combine" } } */
  for(int j=0; j<N_ROW_A; j++)
  {
    for(int i=0; i<N_COL_B; i++)
    {
      partial_sum = 0;
      /* two loads with indexed post-incrementing */
      for(int k=0; k<N_COL_A; k++)
      {
        partial_sum += matrix_a[k + j*N_COL_A] * matrix_b[k*N_COL_B + i];
      }
      /* one store with indexed post-incrementing */
      matrix_c[i + j*N_COL_B] = partial_sum;
    }
  }
}
