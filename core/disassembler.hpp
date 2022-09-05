#pragma once
#ifndef DISASSEMBLER_HPP
#define DISASSEMBLER_HPP

#include <string>
#include <array>
#include <format>
#include "cpu_common.hpp"

namespace disasm
{
	
	typedef struct 
	{
		const char* alias;
		std::array<Arguments, 3> args; //each instruction can have at most 3 arguments
		const std::string format;
	} instruction;

	std::string ParseInstruction(uint32 i);
	std::string BuildFormat(uint32 i);
}

#endif