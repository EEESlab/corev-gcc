/* Simple test for COREV load post-modify displacement with decrement MEM extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevmem1p0 -fdump-rtl-combine" } */
/* { dg-skip-if "O0 has not combine pass" { *-corev-* } { any-opts "-O0" } } */
/* { dg-skip-if "Unrolling does not trigger the pattern" { *-corev-* } { any-opts "-funroll-loops" } } */

#define LOOP_DIM (20) /* LOOP_DIM = 20 to avoid loop unrolling */
#define IMM12_BOUND_CHAR  (2048) /* 12-bit immediate signed displacement factor */
#define IMM12_BOUND_SHORT (1024) /* 12-bit immediate signed displacement factor */
#define IMM12_BOUND_INT   (512) /* 12-bit immediate signed displacement factor */
#define ARRAY_DIM_CHAR  (LOOP_DIM+1)*(IMM12_BOUND_CHAR) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */
#define ARRAY_DIM_SHORT (LOOP_DIM+1)*(IMM12_BOUND_SHORT) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */
#define ARRAY_DIM_INT   (LOOP_DIM+1)*(IMM12_BOUND_INT) /* Must be greater than (LOOP_DIM * IMM12_BOUND) + 1 mem op */

signed char        array_0 [ARRAY_DIM_CHAR];
unsigned char      array_3 [ARRAY_DIM_CHAR];
signed short int   array_1 [ARRAY_DIM_SHORT];
unsigned short int array_4 [ARRAY_DIM_SHORT];
signed int         array_2 [ARRAY_DIM_INT];
unsigned int       array_5 [ARRAY_DIM_INT];

int char_sum      = 0;
int short_sum     = 0;
int int_sum       = 0;
int uns_char_sum  = 0;
int uns_short_sum = 0;
int uns_int_sum   = 0;

signed char        * array_0_end = &array_0[ARRAY_DIM_CHAR-1];
signed short int   * array_1_end = &array_1[ARRAY_DIM_SHORT-1];
signed int         * array_2_end = &array_2[ARRAY_DIM_INT-1];
unsigned char      * array_3_end = &array_3[ARRAY_DIM_CHAR-1];
unsigned short int * array_4_end = &array_4[ARRAY_DIM_SHORT-1];
unsigned int       * array_5_end = &array_5[ARRAY_DIM_INT-1];

void cv_loadqi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_ext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    char_sum += *((signed char *)(array_0_end-(i*IMM12_BOUND_CHAR)));
  }
}

void cv_loadqi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadqi_uext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    uns_char_sum += *((unsigned char *)(array_3_end-(i*IMM12_BOUND_CHAR)));
  }
}

void cv_loadhi_ext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_ext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    short_sum += *((signed short int *)(array_1_end-(i*IMM12_BOUND_SHORT)));
  }
}

void cv_loadhi_uext(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadhi_uext_postmod_disp" 1 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    uns_short_sum += *((unsigned short int *)(array_4_end-(i*IMM12_BOUND_SHORT)));
  }
}

void cv_loadsi(void)
{
  /* { dg-final { scan-rtl-dump-times "cv_loadsi_postmod_disp" 2 "combine" } } */
  for(int i=0; i<LOOP_DIM; i++)
  {
    int_sum     += *((signed int *)  (array_2_end-(i*IMM12_BOUND_INT)));
    uns_int_sum += *((unsigned int *)(array_5_end-(i*IMM12_BOUND_INT)));
  }
}
