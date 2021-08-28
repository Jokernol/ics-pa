#include <cpu/exec.h>
#include "../local-include/decode.h"
#include "all-instr.h"

static inline void set_width(DecodeExecState *s, int width) {
  if (width != 0) s->width = width;
}

static inline def_EHelper(load) {
  switch (s->isa.instr.i.funct3) {
    EXW  (2, ld, 4)
    default: exec_inv(s);
  }
}

static inline def_EHelper(store) {
  switch (s->isa.instr.s.funct3) {
    EXW  (2, st, 4)
    default: exec_inv(s);
  }
}

static inline def_EHelper(compute) {
  switch (s->isa.instr.r.funct7 << 3 | s->isa.instr.r.funct3) {
    EX (0b0000000000, add)
    EX (0b0100000000, sub)
    EX (0b0000000100, xor)
    default: exec_inv(s);
  }
}

static inline def_EHelper(computei) {
  switch (s->isa.instr.i.funct3) {
    EX (0b000, addi)
    EX (0b010, slti)
    EX (0b011, sltiu)
    default: exec_inv(s);
  }
}

static inline def_EHelper(branch) {
  switch (s->isa.instr.b.funct3) {
    EX (0b000, beq)
    EX (0b001, bne)
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
