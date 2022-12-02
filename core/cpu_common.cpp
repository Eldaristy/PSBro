#include "cpu_common.hpp"

Instruction::Instruction() 
	: all{0} {}

Instruction::Instruction(uint32 all)
	: all{all} {}

Instruction::Instruction(Functs funct, uint8 shamt, Regs rd, Regs rt, Regs rs) //rType
	: rType{ funct, shamt, rd, rt, rs} {
	true;
}

Instruction::Instruction(uint16 imm, Regs rt, Regs rs, Opcodes opcode) //iType
	: iType{imm, rt, rs, opcode} {}

Instruction::Instruction(uint32 addr, Opcodes opcode) //jType
	: jType{addr, opcode} {}

std::array<std::string, Regs::RA + 1> regAliases = {
	"zero",
	"at",
	"v0",
	"v1",
	"a0",
	"a1",
	"a2",
	"a3",
	"t0",
	"t1",
	"t2",
	"t3",
	"t4",
	"t5",
	"t6",
	"t7",
	"s0",
	"s1",
	"s2",
	"s3",
	"s4",
	"s5",
	"s6",
	"s7",
	"t8",
	"t9",
	"k0",
	"k1",
	"gp",
	"sp",
	"fp",
	"ra",
};

