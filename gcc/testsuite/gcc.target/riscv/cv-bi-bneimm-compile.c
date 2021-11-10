/* Test for COREV branching immediate bne BI extensions */
/* { dg-do compile { target { riscv32-corev-elf } } } */
/* { dg-options "-march=rv32i_xcorevbi1p0 -std=gnu11 --save-temps" } */

/* The compiler tends to switch from NE to EQ for a reason of cost */
void bneimm_upperbound(int *arg)
{
  if (*arg == 15)
    goto JUMP;
  else
    return;
JUMP:
  *arg = 15;
  return;
}

void bneimm_lowerbound(int *arg)
{
  if (*arg == -16)
    goto JUMP;
  else
    return;
JUMP:
  *arg = -16;
  return;
}

/* { dg-final { scan-assembler-times "cv\.bneimm\t.\\d+,15," 1 } } */
/* { dg-final { scan-assembler-times "cv\.bneimm\t.\\d+,-16," 1 } } */
