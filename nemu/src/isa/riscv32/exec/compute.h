static inline def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
  print_asm_template2(lui);
}

static inline def_EHelper(li) {
  rtl_li(s, ddest, *rz);
  print_asm_template2(li);
}

static inline def_EHelper(auipc) {
  rtl_addi(s, ddest, &s->seq_pc, id_src1->imm);
  print_asm_template2(auipc);
}
