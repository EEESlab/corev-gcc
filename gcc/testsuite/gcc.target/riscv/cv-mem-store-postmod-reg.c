/* Simple test for COREV store post-modify register MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -fdump-rtl-combine" } */
/* { dg-skip-if "O0 has not combine pass" { *-corev-* } { any-opts "-O0" } } */
/* { dg-skip-if "Unrolling does not trigger the pattern" { *-corev-* } { any-opts "-funroll-loops" } } */

#define LOOP_DIM (20) /* LOOP_DIM = 20 to avoid loop unrolling */
#define IMM12_BOUND (2048) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (LOOP_DIM+1)*(IMM12_BOUND) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */

signed char array_0 [ARRAY_DIM];
signed char array_1 [ARRAY_DIM];
signed char array_2 [ARRAY_DIM];
signed char array_3 [ARRAY_DIM];
signed char array_4 [ARRAY_DIM];
signed char array_5 [ARRAY_DIM];

void cv_storeqi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storeqi_postmod_disp" 2 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  { 
    *((signed char *)  (array_0+(i*IMM12_BOUND))) = sizeof(signed char)  +i;
    *((unsigned char *)(array_3+(i*IMM12_BOUND))) = sizeof(unsigned char)+i;
  }
}

void cv_storehi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storehi_postmod_disp" 2 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    *((signed short int *)  (array_1+(i*IMM12_BOUND))) = sizeof(signed short int)  +i;
    *((unsigned short int *)(array_4+(i*IMM12_BOUND))) = sizeof(unsigned short int)+i;
  }
}

void cv_storesi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storesi_postmod_disp" 2 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    *((signed int *)  (array_2+(i*IMM12_BOUND))) = sizeof(signed int)  +i;
    *((unsigned int *)(array_5+(i*IMM12_BOUND))) = sizeof(unsigned int)+i;
  }
}
