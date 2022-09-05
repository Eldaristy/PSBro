#include "disassembler.hpp"

namespace formats
{
	const std::string I = "%s";
	const std::string I_IMM = "%s $%x";
	const std::string I_R = "%s %s";
	const std::string I_R_IMM = "%s %s,$%x";
	const std::string I_R_IMM_R = "%s %s,$%x(%s)";
	const std::string I_R_R = "%s %s,%s";
	const std::string I_R_R_R = "%s %s,%s,%s";
	
	/*const uint8 RS = 0x01;
	const uint8 RT = 0x02;
	const uint8 RD = 0x04;
	const uint8 IMM5 = 0x08;
	const uint8 IMM16 = 0x10;
	const uint8 IMM20 = 0x20;
	const uint8 IMM26 = 0x40;*/
};

//using disasm::imm26;

disasm::instruction opcodes[0x40] =
{
	{NULL, {disasm::NONE}, NULL}, //r-types
	{NULL, {disasm::NONE}, NULL}, //conditions
	{"j", {disasm::imm26}, formats::I_IMM},
	{"jal", {disasm::imm26}, formats::I_IMM},
	{"beq", {disasm::imm16, disasm::rs, disasm::rt}, formats::I},
	{"bne", {disasm::imm16, disasm::rs, disasm::rt}, formats::I},
	{"blez", {disasm::imm16, disasm::rs}, formats::I},
	{"bgtz", {disasm::imm16, disasm::rs}, formats::I},

	{"addi", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"addiu", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"slti", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"sltiu", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"andi", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"ori", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"xori", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lui", {disasm::imm16, disasm::rt}, formats::I},

	{"cop0", {disasm::imm26}, formats::I_IMM},
	{"cop1", {disasm::imm26}, formats::I_IMM},
	{"cop2", {disasm::imm26}, formats::I_IMM},
	{"cop3", {disasm::imm26}, formats::I_IMM},
	{NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL},
	
	{NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL},
	{NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL}, {NULL, {disasm::NONE}, NULL},

	{"lb", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lh", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lwl", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lw", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lbu", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lhu", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lwr", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I},

	{"sb",{disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"sh",{disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"swl",{disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"sw",{disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I},
	{NULL, {disasm::NONE}, formats::I},
	{"swr",{disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I},

	{"lwc0", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lwc1", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lwc2", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"lwc3", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I},

	{"swc0", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"swc1", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"swc2", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{"swc3", {disasm::rt, disasm::imm16, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I},
};

disasm::instruction functs[0x40] =
{
	{"sll", {disasm::rd, disasm::rt, disasm::imm5}, formats::I},
	{NULL, {disasm::NONE}, formats::I},
	{"srl", {disasm::rd, disasm::rt, disasm::imm5}, formats::I},
	{"sra", {disasm::rd, disasm::rt, disasm::imm5}, formats::I},
	{"sllv", {disasm::rd, disasm::rt, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I},
	{"srlv", {disasm::rd, disasm::rt, disasm::rs}, formats::I},
	{"srav", {disasm::rd, disasm::rt, disasm::rs}, formats::I},

	{"jr", {disasm::rs}, formats::I},
	{"jalr", {disasm::rd, disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I},
	{NULL, {disasm::NONE}, formats::I},
	{"syscall", {disasm::imm20}, formats::I_IMM},
	{"break", {disasm::imm20}, formats::I_IMM},
	{NULL, {disasm::NONE}, formats::I},
	{NULL, {disasm::NONE}, formats::I},

	{"mfhi", {disasm::rd}, formats::I},
	{"mthi", {disasm::rs}, formats::I},
	{"mflo", {disasm::rd}, formats::I},
	{"mtlo", {disasm::rs}, formats::I},
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I},

	{"mult", {disasm::rs, disasm::rt}, formats::I},
	{"multu", {disasm::rs, disasm::rt}, formats::I},
	{"div", {disasm::rs, disasm::rt}, formats::I},
	{"divu", {disasm::rs, disasm::rt}, formats::I},
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I},

	{"add", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"addu", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"sub", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"subu", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"and", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"or", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"xor", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"nor", {disasm::rd, disasm::rs, disasm::rt}, formats::I},

	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I},
	{"slt", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{"sltu", {disasm::rd, disasm::rs, disasm::rt}, formats::I},
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I},
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, 

	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, 
	{NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}, {NULL, {disasm::NONE}, formats::I}
};

std::string disasm::ParseInstruction(uint32 i)
{
	std::string result = "";
	std::array<Arguments, 3> args{NONE};
	std::array<std::string, 3> argsAliases{ "", "", ""};
	std::string rs = "";
	std::string rt = "";
	std::string rd = "";
	uint8 imm5 = 0;
	uint16 imm16 = 0;
	uint32 imm20 = 0;
	uint32 imm25 = 0;
	uint32 imm26 = 0;

	rs = regAliases[reinterpret_cast<r_instruction&>(i).rs];
	rt = regAliases[reinterpret_cast<r_instruction&>(i).rt];
	rd = regAliases[reinterpret_cast<r_instruction&>(i).rd];
	imm5 = reinterpret_cast<r_instruction&>(i).shamt;
	imm16 = reinterpret_cast<i_instruction&>(i).imm;
	imm20 = reinterpret_cast<j_instruction&>(i).addr >> 6;
	//imm25?
	imm26 = reinterpret_cast<j_instruction&>(i).addr;

	if (reinterpret_cast<i_instruction&>(i).opcode == 0) { //if it's an r-type opcode
		result = functs[reinterpret_cast<r_instruction&>(i).funct].alias;
		args = functs[reinterpret_cast<r_instruction&>(i).funct].args;
	}
	else if (opcodes[reinterpret_cast<i_instruction&>(i).opcode].alias != NULL) {
		result = opcodes[reinterpret_cast<i_instruction&>(i).opcode].alias;
		args = opcodes[reinterpret_cast<i_instruction&>(i).opcode].args;
	}

	for (uint8 i = 0; i < 3; i++) {
		switch (args[i]) {
		case Arguments::rs:
			argsAliases[i] = rs;
			break;

		case Arguments::rt:
			argsAliases[i] = rt;
			break;

		case Arguments::rd:
			argsAliases[i] = rd;
			break;

		case Arguments::imm5:
			argsAliases[i] = std::format ;
			break;
		}
	}
}