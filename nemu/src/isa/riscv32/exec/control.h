static inline def_EHelper(jal) {
  rtl_add(s, ddest, &s->seq_pc, rz);
  rtl_addi(s, &s->is_jmp, rz, 1);
  rtl_addi(s, &s->jmp_pc, &cpu.pc, s->src1.simm);

  print_Dop(id_src1->str, OP_STR_SIZE, "0x%x", s->src1.simm);

  print_asm_template2(jal);
}
