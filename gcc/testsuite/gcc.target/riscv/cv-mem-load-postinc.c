/* Simple test for COREV load post-increment MEM extensions */
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

int char_sum      = 0;
int short_sum     = 0;
int int_sum       = 0;
int uns_char_sum  = 0;
int uns_short_sum = 0;
int uns_int_sum   = 0;

void cv_loadqi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_ext_postinc" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    char_sum += array_0[i]; // You should manipulate the cost of the reg-reg load instruction
  }
}

void cv_loadqi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_uext_postinc" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    uns_char_sum += array_3[i]; // You should manipulate the cost of the reg-reg load instruction
  }
}

void cv_loadhi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_ext_postinc" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    short_sum += array_1[i];
  }
}

void cv_loadhi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_uext_postinc" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    uns_short_sum += array_4[i];
  }
}

void cv_loadsi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadsi_postinc" 2 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    int_sum     += array_2[i];
    uns_int_sum += array_5[i];
  }
}
