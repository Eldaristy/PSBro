#pragma once
#ifndef DISASSEMBLER_HPP
#define DISASSEMBLER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <array>
#include <format>
#include "cpu_common.hpp"
#include "R3000_cpu.hpp"

namespace disasm
{
	//I might one day overload the static_cast operator from Instruction to std::string
	std::string ParseInstruction(Instruction i);
	std::string BuildFormat(std::string opcode, std::array<std::string, 3> args);
	std::string GetRegVal(Regs reg);
	void SetRegVal(Regs reg, uint32 val);
}
#endif