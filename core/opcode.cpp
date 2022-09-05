#include "opcode.hpp"

Opcode::Opcode() :
	alias(""), args({ Arguments::NONE, Arguments::NONE, Arguments::NONE }),
	opcodeType(OpcodeType::NONE), operation(Operation::NONE) {};

Opcode::Opcode(const std::string alias, const std::array<Arguments, 3> args, const OpcodeType opcodeType,
	const Operation operation) : 
	alias(alias), args(args), opcodeType(opcodeType), operation(operation) {};

Opcode Opcode::opcodeTable[0x40]
{
	{"special", {Arguments::NONE, Arguments::NONE, Arguments::NONE}, OpcodeType::NONE, Operation::NONE},
	{"bcondz", {Arguments::NONE, Arguments::NONE, Arguments::NONE}, OpcodeType::Branch, Operation::Sub},
	{"j", {Arguments::imm26, Arguments::NONE, Arguments::NONE}, OpcodeType::Jump, Operation::NONE},
	{"jal", {Arguments::imm26, Arguments::NONE, Arguments::NONE}, OpcodeType::Link, Operation::NONE},
	{"beq", {Arguments::imm16, Arguments::rs, Arguments::rt}, OpcodeType::Branch, Operation::Sub},
	{"bne", {Arguments::imm16, Arguments::rs, Arguments::rt}, OpcodeType::Branch, Operation::Sub},
	{"blez", {Arguments::imm16, Arguments::rs, Arguments::NONE}, OpcodeType::Branch, Operation::Sub},
	{"bgtz", {Arguments::imm16, Arguments::rs, Arguments::NONE}, OpcodeType::Branch, Operation::Sub},

	{"addi", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::Add},
	{"addiu", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::Add},
	{"Slti", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::Slt},
	{"Sltiu", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::Slt},
	{"andi", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::And},
	{"ori", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::Or},
	{"xori", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::ALU, Operation::Xor},
	{"lui", {Arguments::imm16, Arguments::rt, Arguments::NONE}, OpcodeType::Shift, Operation::ShiftLeftLogic},

	{"cop0", {Arguments::imm26, Arguments::NONE, Arguments::NONE}, OpcodeType::Cop, Operation::NONE},
	{"cop1", {Arguments::imm26, Arguments::NONE, Arguments::NONE}, OpcodeType::Cop, Operation::NONE},
	{"cop2", {Arguments::imm26, Arguments::NONE, Arguments::NONE}, OpcodeType::Cop, Operation::NONE},
	{"cop3", {Arguments::imm26, Arguments::NONE, Arguments::NONE}, OpcodeType::Cop, Operation::NONE},
	{}, {}, {}, {},

	{}, {}, {}, {},
	{}, {}, {}, {},

	{"lb", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{"lh", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{"lwl", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{"lw", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{"lbu", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{"lhu", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{"lwr", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Load, Operation::Add},
	{},

	{"sb", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Store, Operation::Add},
	{"sh", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Store, Operation::Add},
	{"swl", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Store, Operation::Add},
	{"sw", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Store, Operation::Add},
	{},
	{},
	{"swr", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::Store, Operation::Add},
	{},

	{"lwc0", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{"lwc1", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{"lwc2", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{"lwc3", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{}, {}, {}, {},

	{"swc0", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{"swc1", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{"swc2", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{"swc3", {Arguments::rt, Arguments::imm16, Arguments::rs}, OpcodeType::NONE, Operation::NONE},
	{}, {}, {}, {},
};

Opcode Opcode::functTable[0x40]
{
	{"sll", {Arguments::rd, Arguments::rt, Arguments::imm5}, OpcodeType::Shift, Operation::ShiftLeftLogic},
	{},
	{"srl", {Arguments::rd, Arguments::rt, Arguments::imm5}, OpcodeType::Shift, Operation::ShiftRightLogic},
	{"sra", {Arguments::rd, Arguments::rt, Arguments::imm5}, OpcodeType::Shift, Operation::ShiftRightArith},
	{"sllv", {Arguments::rd, Arguments::rt, Arguments::rs}, OpcodeType::Shift, Operation::ShiftLeftLogic},
	{},
	{"srlv", {Arguments::rd, Arguments::rt, Arguments::rs}, OpcodeType::Shift, Operation::ShiftRightLogic},
	{"srav", {Arguments::rd, Arguments::rt, Arguments::rs}, OpcodeType::Shift, Operation::ShiftRightArith},

	{"jr", {Arguments::rs, Arguments::NONE, Arguments::NONE}, OpcodeType::Jump, Operation::NONE},
	{"jalr", {Arguments::rd, Arguments::rd, Arguments::NONE}, OpcodeType::Link, Operation::NONE},
	{},
	{},
	{"syscall", {Arguments::imm20, Arguments::NONE, Arguments::NONE}, OpcodeType::NONE, Operation::NONE},
	{"break", {Arguments::imm20, Arguments::NONE, Arguments::NONE}, OpcodeType::NONE, Operation::NONE},
	{},
	{},

	{"mfhi", {Arguments::rd, Arguments::NONE, Arguments::NONE}, OpcodeType::MulDiv, Operation::ReadHi},
	{"mthi", {Arguments::rs, Arguments::NONE, Arguments::NONE}, OpcodeType::MulDiv, Operation::ReadLo},
	{"mflo", {Arguments::rd, Arguments::NONE, Arguments::NONE}, OpcodeType::MulDiv, Operation::WriteHi},
	{"mtlo", {Arguments::rs, Arguments::NONE, Arguments::NONE}, OpcodeType::MulDiv, Operation::WriteLo},
	{}, {}, {}, {},

	{"mult", {Arguments::rs, Arguments::rt, Arguments::NONE}, OpcodeType::MulDiv, Operation::Mul},
	{"multu", {Arguments::rs, Arguments::rt, Arguments::NONE}, OpcodeType::MulDiv, Operation::Mul},
	{"div", {Arguments::rs, Arguments::rt, Arguments::NONE}, OpcodeType::MulDiv, Operation::Div},
	{"divu", {Arguments::rs, Arguments::rt, Arguments::NONE}, OpcodeType::MulDiv, Operation::Div},
	{}, {}, {}, {},

	{"add", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Add},
	{"addu", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Add},
	{"sub", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Sub},
	{"subu", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Sub},
	{"and", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::And},
	{"or", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Or},
	{"xor", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Xor},
	{"nor", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Nor},

	{}, {},
	{"slt", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Slt},
	{"sltu", {Arguments::rd, Arguments::rs, Arguments::rt}, OpcodeType::ALU, Operation::Slt},
	{}, {},

	{}, {}, {}, {},
	{}, {}, {}, {}
};