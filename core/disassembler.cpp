#include "disassembler.hpp"

namespace formats
{
	const char* I = "%s";
	const char* I_IMM = "%s $%x";
	const char* I_R = "%s %s";
	const char* I_R_IMM = "%s %s,$%x";
	const char* I_R_IMM_R = "%s %s,$%x(%s)";
	const char* I_R_R = "%s %s,%s";
	const char* I_R_R_R = "%s %s,%s,%s";
};

//using disasm::imm26;

std::string disasm::ParseInstruction(uint32 i)
{
	std::string result = "";
	std::array<Arguments, 3> args{NONE};
	std::array<std::string, 3> argsAliases{"", "", ""};
	std::string rs = "";
	std::string rt = "";
	std::string rd = "";
	uint8 imm5 = 0;
	uint16 imm16 = 0;
	uint32 imm20 = 0;
	uint32 imm25 = 0;
	uint32 imm26 = 0;

	rs = regAliases[reinterpret_cast<RInstruction&>(i).rs];
	rt = regAliases[reinterpret_cast<RInstruction&>(i).rt];
	rd = regAliases[reinterpret_cast<RInstruction&>(i).rd];
	imm5 = reinterpret_cast<RInstruction&>(i).shamt;
	imm16 = reinterpret_cast<IInstruction&>(i).imm;
	imm20 = reinterpret_cast<JInstruction&>(i).addr >> 6;
	//imm25?
	imm26 = reinterpret_cast<JInstruction&>(i).addr;

	if (reinterpret_cast<IInstruction&>(i).opcode == 0) { //if it's an r-type opcode
		result = Opcode::functTable[reinterpret_cast<RInstruction&>(i).funct].alias;
		args = Opcode::functTable[reinterpret_cast<RInstruction&>(i).funct].args;
	}
	else if (Opcode::opcodeTable[reinterpret_cast<IInstruction&>(i).opcode].alias != "") {
		result = Opcode::opcodeTable[reinterpret_cast<IInstruction&>(i).opcode].alias;
		args = Opcode::opcodeTable[reinterpret_cast<IInstruction&>(i).opcode].args;
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
			argsAliases[i] = std::to_string(imm5);
			break;

		case Arguments::imm16:
			argsAliases[i] = std::to_string(imm16);
			break;

		case Arguments::imm20:
			argsAliases[i] = std::to_string(imm20);
			break;

		case Arguments::imm26:
			argsAliases[i] = std::to_string(imm26);
			break;

		default:
			argsAliases[i] = "";
			break;
		}
	}

	result = BuildFormat(result, argsAliases);

	return result;
}

std::string disasm::BuildFormat(std::string opcode, std::array<std::string, 3> argsAliases)
{
	char buf[50] = { 0 };
	std::string format = "";
	std::sprintf(buf, formats::I_R_R_R,
		opcode.c_str(), argsAliases[0].c_str(), argsAliases[1].c_str(), argsAliases[2].c_str());
	format = buf;

	return format;
}