#pragma once
#ifndef OPCODE_HPP
#define OPCODE_HPP

#include <array>
#include <string>

enum class OpcodeType {
	NONE = 0,
	Load,
	Store,
	ALU,
	Shift,
	MulDiv,
	Jump,
	Link,
	Branch,
	Cop
};

enum class Operation {
	NONE = 0,
	//ALU operations:
	And,
	Or,
	Add,
	Xor,
	Nor,
	Sub,
	Slt,
	//shifter operations:
	ShiftLeftLogic,
	ShiftRightLogic,
	ShiftRightArith,
	RotRight,
	RotLeft,
	//multiply unit operations:
	Mul,
	Div,
	ReadHi,
	ReadLo,
	WriteHi,
	WriteLo
};

enum Arguments
{
	NONE = 0,
	rs,
	rt,
	rd,
	imm5,
	imm16,
	imm20,
	imm25,
	imm26
};

class Opcode
{
private:
	const std::string alias;
	const std::array<Arguments, 3> args;

public:
	const OpcodeType opcodeType;
	const Operation operation;

	static Opcode opcodeTable[0x40];
	static Opcode functTable[0x40];

	Opcode();
	Opcode(const std::string alias, const std::array<Arguments, 3> args, const OpcodeType opcodeType,
		const Operation operation);
};

#endif