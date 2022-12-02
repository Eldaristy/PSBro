#include "tests.hpp"

int disasm_test_main()
{
	Instruction i = { 0 };
	i.rType.funct = Functs::SRA;
	i.rType.rd = Regs::A1;
	i.rType.rs = Regs::A2;
	i.rType.rt = Regs::A3;
	i.rType.shamt = 4;

	for (uint8 fn = 0; fn < 64; fn++) {
		i.rType.funct = static_cast<Functs>(fn);
		std::cout << "R-type: " << disasm::ParseInstruction(i) << std::endl;
	}
	std::cout << "====================" << std::endl;
	
	for (uint8 op = 0; op < 64; op++) {
		i.iType.opcode = static_cast<Opcodes>(op);
		std::cout << "I-type: " << disasm::ParseInstruction(i) << std::endl;
	}
	std::cout << "====================" << std::endl;
	i.iType.opcode = Opcodes::R_TYPE;
	i.rType.funct = Functs::SLL;

	for (uint8 reg = 0; reg < 32; reg++) {
		i.rType.rd = static_cast<Regs>(reg);
		i.rType.rs = static_cast<Regs>(reg);
		i.rType.rt = static_cast<Regs>(reg);
		std::cout << "Regs: " << disasm::ParseInstruction(i) << std::endl;
	}
	
	std::cout << "====================" << std::endl;
	for (uint8 reg = 0; reg < 32; reg++) {
		std::cout << disasm::GetRegVal(static_cast<Regs>(reg)) << std::endl;
	}

	return 0;
}