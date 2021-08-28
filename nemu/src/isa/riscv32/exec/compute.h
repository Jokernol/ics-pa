static inline def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
  print_asm_template2(lui);
}

static inline def_EHelper(auipc) {
  rtl_addi(s, ddest, &cpu.pc, id_src1->simm);
  print_asm_template2(auipc);
}

static inline def_EHelper(add) {
  rtl_add(s, ddest, dsrc1, dsrc2);
  print_asm_template3(add);
}

static inline def_EHelper(addi) {
  rtl_addi(s, ddest, dsrc1, id_src2->simm);
  print_asm_template3(addi);
}

static inline def_EHelper(sub) {
  rtl_sub(s, ddest, dsrc1, dsrc2);
  print_asm_template3(sub);
}

static inline def_EHelper(mul) {
  rtl_imul_lo(s, ddest, dsrc1, dsrc2);
  print_asm_template3(mul);
}

static inline def_EHelper(div) {
  rtl_idiv_q(s, ddest, dsrc1, dsrc2);
  print_asm_template3(div);
}

static inline def_EHelper(rem) {
  rtl_idiv_r(s, ddest, dsrc1, dsrc2);
  print_asm_template3(rem);
}

static inline def_EHelper(and) {
  rtl_and(s, ddest, dsrc1, dsrc2);
  print_asm_template3(and);
}

static inline def_EHelper(andi) {
  rtl_andi(s, ddest, dsrc1, s->src2.simm);
  print_asm_template3(andi);
}

static inline def_EHelper(or) {
  rtl_or(s, ddest, dsrc1, dsrc2);
}

static inline def_EHelper(xor) {
  rtl_xor(s, ddest, dsrc1, dsrc2);
  print_asm_template3(xor);
}

static inline def_EHelper(slti) {
  rtl_setrelopi(s, RELOP_LT, ddest, dsrc1, id_src2->simm);
  print_asm_template3(slti);
}

static inline def_EHelper(sltiu) {
  rtl_setrelopi(s, RELOP_LTU, ddest, dsrc1, id_src2->imm);
  print_asm_template3(sltiu);
}

static inline def_EHelper(sltu) {
  rtl_setrelop(s, RELOP_LT, ddest, dsrc1, dsrc2);
  print_asm_template3(sltu);
}
