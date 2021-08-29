static inline def_EHelper(mul) {
  rtl_imul_lo(s, ddest, dsrc1, dsrc2);
  print_asm_template3(mul);
}

static inline def_EHelper(mulh) {
  rtl_imul_hi(s, ddest, dsrc1, dsrc2);
  print_asm_template3(mulh);
}

static inline def_EHelper(div) {
  rtl_idiv_q(s, ddest, dsrc1, dsrc2);
  print_asm_template3(div);
}

static inline def_EHelper(rem) {
  rtl_idiv_r(s, ddest, dsrc1, dsrc2);
  print_asm_template3(rem);
}
