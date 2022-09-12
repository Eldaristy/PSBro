#include <iostream>
#include "tests.hpp"
#include "../core/disassembler.hpp"

int disasm_test_main()
{
	Instruction r = { 0 };
	r.rType.funct = Functs::SRA;
	r.rType.rd = Regs::A3;
	r.rType.rs = Regs::RA;
	r.rType.rt = Regs::T2;
	r.rType.shamt = 4;

	Instruction i = { 0 };
	i.iType.opcode = Opcodes::ANDI;
	i.iType.rs = Regs::S1;
	i.iType.rt = Regs::A1;
	i.iType.imm = 4;

	uint32 var = 0;

	/*while (true) {
		std::cout << var << ": " << disasm::ParseInstruction(var++) << '\n';
	}*/
	std::cout << "r-type: " << disasm::ParseInstruction(reinterpret_cast<uint32&>(r)) << '\n';
	std::cout << "i-type: " << disasm::ParseInstruction(reinterpret_cast<uint32&>(i)) << '\n';

	return 0;
}