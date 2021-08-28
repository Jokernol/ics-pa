static inline def_EHelper(jal) {
  rtl_add(s, ddest, &s->seq_pc, rz);
  rtl_addi(s, &s->is_jmp, rz, 1);
  rtl_addi(s, &s->jmp_pc, &cpu.pc, s->src1.simm);

  print_Dop(id_src1->str, OP_STR_SIZE, "0x%x", s->jmp_pc);

  print_asm_template2(jal);
}

static inline def_EHelper(jalr) {
  rtl_addi(s, ddest, &s->seq_pc, 4);
  rtl_addi(s, &s->is_jmp, rz, 1);

  s->jmp_pc = (*dsrc1 + s->src2.simm) & ~1;

  print_asm_template3(jalr);
}

static inline def_EHelper(beq) {
  if (*ddest == *dsrc1) {
    rtl_addi(s, &s->is_jmp, rz, 1);
    rtl_addi(s, &s->jmp_pc, &cpu.pc, s->src2.simm);
  }

  print_Dop(id_src2->str, OP_STR_SIZE, "0x%x", cpu.pc + s->src2.simm);

  print_asm_template3(beq);
}

static inline def_EHelper(bne) {
  //if (*ddest != *dsrc1) {
  //  rtl_addi(s, &s->is_jmp, rz, 1);
  //  rtl_addi(s, &s->jmp_pc, &cpu.pc, s->src2.simm);
  //}

  rtl_jrelop(s, RELOP_NE, dsrc1, ddest, cpu.pc + s->src2.simm);

  print_Dop(id_src2->str, OP_STR_SIZE, "0x%x", cpu.pc + s->src2.simm);

  print_asm_template3(bne);
}

static inline def_EHelper(bge) {
  rtl_jrelop(s, RELOP_GE, dsrc1, ddest, cpu.pc + s->src2.simm);

  print_Dop(id_src2->str, OP_STR_SIZE, "0x%x", cpu.pc + s->src2.simm);

  print_asm_template3(bge);
}
