/* Simple test for COREV store post-increment MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -fdump-rtl-combine" } */
/* { dg-skip-if "O0 has not combine pass" { *-corev-* } { any-opts "-O0" } } */
/* { dg-skip-if "Unrolling does not trigger the pattern" { *-corev-* } { any-opts "-funroll-loops" } } */

#define ARRAY_DIM (20) /* ARRAY_DIM = 20 to avoid loop unrolling */

signed char        array_0 [ARRAY_DIM];
signed short int   array_1 [ARRAY_DIM];
signed int         array_2 [ARRAY_DIM];
unsigned char      array_3 [ARRAY_DIM];
unsigned short int array_4 [ARRAY_DIM];
unsigned int       array_5 [ARRAY_DIM];

void cv_storeqi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storeqi_postinc" 2 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    array_0[i] = sizeof(signed char)  ;
    array_3[i] = sizeof(unsigned char);
  }
}

void cv_storehi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storehi_postinc" 2 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    array_1[i] = sizeof(signed short int)  ;
    array_4[i] = sizeof(unsigned short int);
  }
}

void cv_storesi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_storesi_postinc" 2 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    array_2[i] = sizeof(signed int)  ;
    array_5[i] = sizeof(unsigned int);
  }
}
