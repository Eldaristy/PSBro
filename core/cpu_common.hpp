#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdint.h>
#include <array>
#include <string>
#include "opcode.hpp"

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

enum class CPUInitMode
{
	NORMAL,
	TEST
};

enum Regs : uint32 
{
	ZERO,
	AT,
	V0,
	V1,
	A0,
	A1,
	A2,
	A3,
	T0,
	T1,
	T2,
	T3,
	T4,
	T5,
	T6,
	T7,
	S0,
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	T8,
	T9,
	K0,
	K1,
	GP,
	SP,
	FP,
	RA,
};

extern std::array<std::string, Regs::RA + 1> regAliases;

enum Opcodes : uint32
{
	R_TYPE = 0,
	BCONDZ = 1,
	J = 2,
	JAL = 3,
	BEQ = 4,
	BNE = 5,
	BLEZ = 6,
	BGTZ = 7,
	ADDI = 8,
	ADDIU = 9,
	SLTI = 10,
	SLTIU = 11,
	ANDI = 12,
	ORI = 13,
	XORI = 14,
	LUI = 15,
	COP0 = 16,
	COP1 = 17,
	COP2 = 18,
	COP3 = 19,
	/* 23 - 31*/
	LB = 32,
	LH = 33,
	LWL = 34,
	LW = 35,
	LBU = 36,
	LHU = 37,
	LWR = 38,
	/* 39 */
	SB = 40,
	SH = 41,
	SWL = 42,
	SW = 43,
	/* 44 */
	/* 45 */
	SWR = 46,
	/* 47 */
	LWC0 = 48,
	LWC1 = 49,
	LWC2 = 50,
	LWC3 = 51,
	/* 52-55 */
	SWC0 = 56,
	SWC1 = 57,
	SWC2 = 58,
	SWC3 = 59,
	/* 60 - 63 */
};

enum Functs : uint32
{
	SLL = 0,
	/* 1 */
	SRL = 2,
	SRA = 3,
	SLLV = 4,
	/* 5 */
	SRLV = 6,
	SRAV = 7,
	JR = 8,
	JALR = 9,
	/* 10 */
	/* 11 */
	SYSCALL = 12,
	BREAK = 13,
	/* 14 */
	/* 15 */
	MFHI = 16,
	MTHI = 17,
	MFLO = 18,
	MTLO = 19,
	/* 20-23 */
	MULT = 24,
	MULTU = 25,
	DIV = 26,
	DIVU = 27,
	/* 28-31 */
	ADD = 32,
	ADDU = 33,
	SUB = 34,
	SUBU = 35,
	AND = 36,
	OR = 37,
	XOR = 38,
	NOR = 39,
	/* 40 */
	/* 41 */
	SLT = 42,
	SLTU = 43,
	/* 45 */
	/* 46 */
	/* 47-63 */
};

struct Instruction
{
	union
	{
		uint32 all;

		struct
		{
			Functs funct : 6;
			uint32 shamt : 5;
			Regs rd : 5;
			Regs rt : 5;
			Regs rs : 5;
			Opcodes opcode : 6;
		} rType;

		struct
		{
			uint32 imm : 16;
			Regs rt : 5;
			Regs rs : 5;
			Opcodes opcode : 6;
		} iType;

		struct
		{
			uint32 addr : 26;
			Opcodes opcode : 6;
		} jType;

		
	};
	Instruction();
	Instruction(uint32 all);
	Instruction(Functs funct, uint8 shamt, Regs rd, Regs rt, Regs rs); //rType
	Instruction(uint16 imm, Regs rt, Regs rs, Opcodes opcode); //iType
	Instruction(uint32 addr, Opcodes opcode); //jType
};

#endif