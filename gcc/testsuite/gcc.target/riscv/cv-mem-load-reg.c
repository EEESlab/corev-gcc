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

int char_sum      = 0;
int short_sum     = 0;
int int_sum       = 0;
int uns_char_sum  = 0;
int uns_short_sum = 0;
int uns_int_sum   = 0;

void cv_loadqi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_ext_postmod_reg" 1 "combine" } } */
  char_sum += *((signed char *)(array_0+IMM12_BOUND));
}

void cv_loadqi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_uext_postmod_reg" 1 "combine" } } */
  uns_char_sum += *((unsigned char *)(array_3+IMM12_BOUND));
}

void cv_loadhi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_ext_postmod_reg" 1 "combine" } } */
  short_sum += *((signed short int *)(array_1+IMM12_BOUND));
}

void cv_loadhi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_uext_postmod_reg" 1 "combine" } } */
  uns_short_sum += *((unsigned short int *)(array_4+IMM12_BOUND));
}

void cv_loadsi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadsi_postmod_reg" 2 "combine" } } */
  int_sum     += *((signed int *)  (array_2+IMM12_BOUND));
  uns_int_sum += *((unsigned int *)(array_5+IMM12_BOUND));
}
