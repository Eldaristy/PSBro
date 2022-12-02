#include "tests.hpp"

std::vector<Instruction> mem = {
	{Functs::ADD, 2, Regs::A1, Regs::A2, Regs::A1},
	{}, {}, {}, {},
	{Functs::ADD, 2, Regs::A1, Regs::A2, Regs::A1},
	{}, {}, {}, {},
	{Functs::ADD, 2, Regs::A1, Regs::A2, Regs::A1},
	{}, {}, {}, {},

	{}, {}, {}, {},

	{}, {}, {}, {},

	{}, {}, {}, {},
};

inline void print_reg(Regs reg)
{
	std::cout << disasm::GetRegVal(reg) << std::endl;
}

int cpu_instructions_test_main()
{
	disasm::SetRegVal(Regs::A1, 0);
	disasm::SetRegVal(Regs::A2, 1);
	disasm::SetRegVal(Regs::A3, 1);

	for (uint32 i = 0; i < mem.size() - 1; i++)
	{
		CPU::Cycle();
		print_reg(Regs::A1);
		print_reg(Regs::A2);
		print_reg(Regs::A3);
		std::cout << "--------------" << std::endl;
	}

	return 0;
}

