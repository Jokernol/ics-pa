static inline def_EHelper(jal) {
  rtl_add(s, ddest, &s->seq_pc, rz);
  s->is_jmp = 1;
  s->jmp_pc = cpu.pc + s->src1.imm;
  print_asm_template2(jal);
}
