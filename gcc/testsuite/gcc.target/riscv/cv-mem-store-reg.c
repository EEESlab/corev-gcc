/* Simple test for COREV store register MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -fdump-rtl-combine" } */
/* { dg-skip-if "O0 has not combine pass" { *-corev-* } { any-opts "-O0" } } */

#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (IMM12_BOUND + 4) /* ARRAY_DIM/2 must be >= 2048 to avoid post-mod displacement mem */

signed int array_0 [ARRAY_DIM];
signed int array_1 [ARRAY_DIM];
signed int array_2 [ARRAY_DIM];
signed int array_3 [ARRAY_DIM];
signed int array_4 [ARRAY_DIM];
signed int array_5 [ARRAY_DIM];

void cv_storeqi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storeqi_postmod_reg" 2 "combine" } } */
  *((signed char *)  (array_0 + IMM12_BOUND)) = sizeof(signed char);
  *((unsigned char *)(array_3 + IMM12_BOUND)) = sizeof(unsigned char);
}

void cv_storehi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storehi_postmod_reg" 2 "combine" } } */
  *((signed short int *)  (array_1 + IMM12_BOUND)) = sizeof(signed short int);
  *((unsigned short int *)(array_4 + IMM12_BOUND)) = sizeof(unsigned short int);
}

void cv_storesi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storesi_postmod_reg" 2 "combine" } } */
  *((signed int *)  (array_2 + IMM12_BOUND)) = sizeof(signed int);
  *((unsigned int *)(array_5 + IMM12_BOUND)) = sizeof(unsigned int);
}
