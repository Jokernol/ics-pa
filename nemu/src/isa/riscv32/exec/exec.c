#include <cpu/exec.h>
#include "../local-include/decode.h"
#include "all-instr.h"

static inline void set_width(DecodeExecState *s, int width) {
  if (width != 0) s->width = width;
}

static inline def_EHelper(load) {
  switch (s->isa.instr.i.funct3) {
    EXW (0b010, ld, 4)
    EXW (0b101, ld, 2)
    EXW (0b100, ld, 1)
    EXW (0b001, lds, 2)
    EXW (0b000, lds, 1)
    default: exec_inv(s);
  }
}

static inline def_EHelper(store) {
  switch (s->isa.instr.s.funct3) {
    EXW (0b010, st, 4)
    EXW (0b001, st, 2)
    EXW (0b000, st, 1)
    default: exec_inv(s);
  }
}

static inline def_EHelper(sli) {
  switch (s->isa.instr.i.simm11_0 & 0xffffffe0) {
    EX(0b0000000, slli)
    default: exec_inv(s);
  }
}

static inline def_EHelper(sri) {
  switch (s->isa.instr.i.simm11_0 & 0xffffffe0) {
    EX (0b0000000, srli)
    EX (0b0100000, srai)
    default: exec_inv(s);
  }
}

static inline def_EHelper(compute) {
  switch (s->isa.instr.r.funct7 << 3 | s->isa.instr.r.funct3) {
    EX (0b0000000000, add)
    EX (0b0100000000, sub)
    EX (0b0000001000, mul)
    EX (0b0000001100, div)
    EX (0b0000001110, rem)
    EX (0b0000000111, and)
    EX (0b0000000100, xor)
    EX (0b0000000001, sll)
    EX (0b0000000101, srl)
    EX (0b0100000101, sra)
    EX (0b0000000010, slt)
    EX (0b0000000011, sltu)
    EX (0b0000000110, or)
    default: exec_inv(s);
  }
}

static inline def_EHelper(computei) {
  switch (s->isa.instr.i.funct3) {
    EX (0b000, addi)
    EX (0b100, xori)
    EX (0b001, sli)
    EX (0b101, sri)
    EX (0b010, slti)
    EX (0b011, sltiu)
    EX (0b111, andi)
    default: exec_inv(s);
  }
}

static inline def_EHelper(branch) {
  switch (s->isa.instr.b.funct3) {
    EX (0b000, beq)
    EX (0b001, bne)
    EX (0b100, blt)
    EX (0b101, bge)
    default: exec_inv(s);
  }
}

static inline void fetch_decode_exec(DecodeExecState *s) {
  s->isa.instr.val = instr_fetch(&s->seq_pc, 4);
  Assert(s->isa.instr.i.opcode1_0 == 0x3, "Invalid instruction");
  switch (s->isa.instr.i.opcode6_2) {
    IDEX (0b01100, R, compute)
    IDEX (0b00000, I, load)
    IDEX (0b00100, I, computei)
    IDEX (0b11001, I, jalr)
    IDEX (0b01000, S, store)
    IDEX (0b11000, B, branch)
    IDEX (0b01101, U, lui)
    IDEX (0b00101, U, auipc)
    IDEX (0b11011, J, jal)
    EX   (0b11010, nemu_trap)
    default: exec_inv(s);
  }
}

static inline void reset_zero() {
  reg_l(0) = 0;
}

vaddr_t isa_exec_once() {
  DecodeExecState s;
  s.is_jmp = 0;
  s.seq_pc = cpu.pc;

  fetch_decode_exec(&s);
  update_pc(&s);

  reset_zero();

  return s.seq_pc;
}
