#pragma once
#ifndef R3000_CPU_HPP
#define R3000_CPU_HPP

#include <stdint.h>

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;


enum Reg {
	zero,
	at,
	v0,
	v1,
	a0,
	a1,
	a2,
	a3,
	t0,
	t1,
	t2,
	t3,
	t4,
	t5,
	t6,
	t7,
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	t8,
	t9,
	k0,
	k1,
	gp,
	sp,
	fp, s8 = fp,
	ra,
};

uint32 R[32]; //register file

uint32 pc; //program counter
uint32 lo;
uint32 hi;

typedef struct
{
	uint32 funct : 6;
	uint32 shamt : 5;
	uint32 rd : 5;
	uint32 rt : 5;
	uint32 rs : 5;
	uint32 opcode : 6;

} r_instruction;

typedef struct
{
	uint32 imm : 16;
	uint32 rt : 5;
	uint32 rs : 5;
	uint32 opcode : 6;

} i_instruction;

typedef struct
{
	uint32 addr : 26;
	uint32 opcode : 6;

} j_instruction;

namespace CPU
{
	uint8 ReadByte(uint32 addr);
	void WriteByte(uint32 addr, uint8 val);
	uint16 ReadHalf(uint32 addr);
	void WriteHalf(uint32 addr, uint16 val);
	uint32 ReadWord(uint32 addr);
	void WriteWord(uint32 addr, uint32 val);

	enum OpcodeType {
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

	enum Operation {
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
	
	typedef struct {
		const char* alias;
		OpcodeType opcode_type;
		Operation operation;
	} opcode;

	opcode opcodeTable[0x40];
	opcode functTable[0x40];

	//inter-stage buffers:
	//fetch-decode
	struct {
		uint32 next_pc;
		uint32 fetched_i;
	} f_d;

	//decode-execute
	struct {
		bool jump;
		bool link;
		//write-back stage signals
		bool regWrite;
		bool memtoReg;
		//mem stage signals
		bool branch;
		bool memRead;
		bool memWrite;
		bool byteAccess[4];
		//execute stage signals
		bool opSigned;
		bool regDst;
		bool ALU; //does it use the ALU?
		bool ALUsrc;
		bool shift; //does it use the shifter?
		bool mulDiv; //does it use the multiply/division unit?

		uint32 next_pc;
		uint8 opcode;
		uint32 reg_r_data1;
		uint32 reg_r_data2;
		uint32 imm;
		uint8 rt;
		uint8 rd;
	} d_e;

	//execute-mem
	struct {
		//write-back stage signals
		bool regWrite;
		bool memtoReg;
		//mem stage signals
		bool branch;
		bool memRead;
		bool memWrite;
		bool byteAccess[4];

		uint32 branch_result;
		uint32 result;
		uint32 mem_w_data;
		uint8 reg_w_reg;
	} e_m;

	//mem-writeBack
	struct {
		//write-back stage signals
		bool regWrite;
		bool memtoReg;

		uint32 mem_r_data;
		uint32 reg_w_data;
		uint32 reg_w_reg;
	} m_w;

	void DetermineSignals();
	uint32 ExecALU(uint32 op1, uint32 op2, Operation operation);
	uint32 ExecShifter(uint32 op1, uint32 op2, Operation operation);
	uint32 ExecMulDiv(uint32 op1, uint32 op2, Operation operation);

	inline void Fetch();
	inline void Decode();
	inline void Execute();
	inline void Mem();
	inline void WriteBack();

	inline void Bubble();

	void Cycle();
}

#endif