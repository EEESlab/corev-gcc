/* Simple test for COREV load post-decrement MEM extensions */
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

signed char        * array_0_end = &array_0[ARRAY_DIM-1];
signed short int   * array_1_end = &array_1[ARRAY_DIM-1];
signed int         * array_2_end = &array_2[ARRAY_DIM-1];
unsigned char      * array_3_end = &array_3[ARRAY_DIM-1];
unsigned short int * array_4_end = &array_4[ARRAY_DIM-1];
unsigned int       * array_5_end = &array_5[ARRAY_DIM-1];

void cv_loadqi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_ext_postdec" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    char_sum += *((signed char *) (array_0_end - i));
  }
}

void cv_loadqi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_uext_postdec" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    uns_char_sum += *((unsigned char *) (array_3_end - i));
  }
}

void cv_loadhi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_ext_postdec" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    short_sum += *((signed short int *) (array_1_end - i));
  }
}

void cv_loadhi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_uext_postdec" 1 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    uns_short_sum += *((unsigned short int *) (array_4_end - i));
  }
}

void cv_loadsi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadsi_postdec" 2 "combine" } } */
  for(int i=0; i<ARRAY_DIM; i++)
  {
    int_sum     += *((signed int   *) (array_2_end - i));
    uns_int_sum += *((unsigned int *) (array_5_end - i));
  }
}
