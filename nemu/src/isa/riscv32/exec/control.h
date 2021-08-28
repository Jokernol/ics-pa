static inline def_EHelper(jal) {
  rtl_add(s, ddest, &s->seq_pc, rz);

  vaddr_t pc = cpu.pc + s->src1.simm;

  rtl_j(s, pc);

  print_Dop(id_src1->str, OP_STR_SIZE, "0x%x", pc);

  print_asm_template2(jal);
}

static inline def_EHelper(jalr) {
  rtl_add(s, ddest, &s->seq_pc, rz);

  vaddr_t pc = (*dsrc1 + s->src2.simm) & ~1;

  rtl_j(s, pc);

  print_asm_template3(jalr);
}

static inline def_EHelper(beq) {
  vaddr_t pc = cpu.pc + s->dest.simm;

  rtl_jrelop(s, RELOP_EQ, dsrc1, dsrc2, pc);

  print_Dop(id_dest->str, OP_STR_SIZE, "0x%x", pc);

  print_asm_template3(beq);
}

static inline def_EHelper(bne) {
  vaddr_t pc = cpu.pc + s->dest.simm;

  rtl_jrelop(s, RELOP_NE, dsrc1, dsrc2, pc);

  print_Dop(id_dest->str, OP_STR_SIZE, "0x%x", pc);

  print_asm_template3(bne);
}

static inline def_EHelper(bge) {
  vaddr_t pc = cpu.pc + s->dest.simm;

  rtl_jrelop(s, RELOP_GE, dsrc1, dsrc2, pc);

  print_Dop(id_dest->str, OP_STR_SIZE, "0x%x", pc);

  print_asm_template3(bge);
}

static inline def_EHelper(blt) {
  vaddr_t pc = cpu.pc + s->dest.simm;

  rtl_jrelop(s, RELOP_LT, dsrc1, dsrc2, pc);

  print_Dop(id_dest->str, OP_STR_SIZE, "0x%x", pc);

  print_asm_template3(blt);
}
