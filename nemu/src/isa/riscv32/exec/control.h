static inline def_EHelper(jal) {
  rtl_add(s, ddest, &s->seq_pc, rz);
  rtl_addi(s, &s->is_jmp, rz, 1);
  rtl_addi(s, &s->jmp_pc, &cpu.pc, s->src1.simm);

  print_Dop(id_src1->str, OP_STR_SIZE, "0x%x", s->jmp_pc);

  print_asm_template2(jal);
}

static inline def_EHelper(jalr) {
  rtl_addi(s, ddest, &s->seq_pc, 4);
  rtl_addi(s, &s->jmp_pc, rz, 1);
  s->jmp_pc = *dsrc1 + s->src2.simm;

  print_asm_template3(jalr);
}
