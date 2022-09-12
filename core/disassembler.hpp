#pragma once
#ifndef DISASSEMBLER_HPP
#define DISASSEMBLER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <array>
#include <format>
#include "cpu_common.hpp"

namespace disasm
{
	std::string ParseInstruction(uint32 i);
	std::string BuildFormat(std::string opcode, std::array<std::string, 3> args);

}
#endif