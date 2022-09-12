#pragma once
#ifndef R3000_CPU_HPP
#define R3000_CPU_HPP

#include "cpu_common.hpp"

namespace CPU
{
	uint32 R[32]; //register file

	uint32 pc; //program counter
	uint32 lo;
	uint32 hi;

	uint8 ReadByte(uint32 addr);
	void WriteByte(uint32 addr, uint8 val);
	uint16 ReadHalf(uint32 addr);
	void WriteHalf(uint32 addr, uint16 val);
	uint32 ReadWord(uint32 addr);
	void WriteWord(uint32 addr, uint32 val);

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
};

#endif