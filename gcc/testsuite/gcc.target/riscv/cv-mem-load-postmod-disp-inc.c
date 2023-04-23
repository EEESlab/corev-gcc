/* Simple test for COREV load post-modify displacement with increment MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -fdump-rtl-combine" } */
/* { dg-skip-if "O0 has not combine pass" { *-corev-* } { any-opts "-O0" } } */
/* { dg-skip-if "Unrolling does not trigger the pattern" { *-corev-* } { any-opts "-funroll-loops" } } */

#define LOOP_DIM (20) /* LOOP_DIM = 20 to avoid loop unrolling */
#define IMM12_BOUND (2047) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM (LOOP_DIM+1)*(IMM12_BOUND) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */

signed char array_0 [ARRAY_DIM];
signed char array_1 [ARRAY_DIM];
signed char array_2 [ARRAY_DIM];
signed char array_3 [ARRAY_DIM];
signed char array_4 [ARRAY_DIM];
signed char array_5 [ARRAY_DIM];

int char_sum      = 0;
int short_sum     = 0;
int int_sum       = 0;
int uns_char_sum  = 0;
int uns_short_sum = 0;
int uns_int_sum   = 0;

void cv_loadqi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_ext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    char_sum += *((signed char *)(array_0+(i*IMM12_BOUND)));
  }
}

void cv_loadqi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_uext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    uns_char_sum += *((unsigned char *)(array_3+(i*IMM12_BOUND)));
  }
}

void cv_loadhi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_ext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    short_sum += *((signed short int *)(array_1+(i*IMM12_BOUND)));
  }
}

void cv_loadhi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_uext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    uns_short_sum += *((unsigned short int *)(array_4+(i*IMM12_BOUND)));
  }
}

void cv_loadsi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadsi_postmod_disp" 2 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    int_sum     += *((signed int *)  (array_2+(i*IMM12_BOUND)));
    uns_int_sum += *((unsigned int *)(array_5+(i*IMM12_BOUND)));
  }
}
