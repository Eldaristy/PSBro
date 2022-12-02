#include "R3000_cpu.hpp"

#define NULL_OP {NULL, (OpcodeType)NULL, (Operation)NULL}

uint32 CPU::R[32] = { 0 };
uint32 CPU::pc = 0;
uint32 CPU::lo = 0;
uint32 CPU::hi = 0;
CPU::F_D CPU::f_d{ 0 };
CPU::D_E CPU::d_e{ 0 };
CPU::E_M CPU::e_m{ 0 };
CPU::M_W CPU::m_w{ 0 };

void CPU::Init(CPUInitMode mode)
{
	switch (mode) {
	case CPUInitMode::NORMAL:
		//...
		break;
		
	case CPUInitMode::TEST:
		break;
	}
}
extern std::vector<Instruction> mem;
uint8 CPU::ReadByte(uint32 addr) 
{ 
	//extern std::vector<Instruction> mem;
	return mem[addr / sizeof(uint32)].all;
}
void CPU::WriteByte(uint32 addr, uint8 val) {}
uint16 CPU::ReadHalf(uint32 addr)
{
	//extern std::vector<Instruction> mem;
	return mem[addr / sizeof(uint32)].all;
}
void CPU::WriteHalf(uint32 addr, uint16 val) {}
uint32 CPU::ReadWord(uint32 addr)
{ 
	//extern std::vector<Instruction> mem;
	return mem[addr / sizeof(uint32)].all;
}
void CPU::WriteWord(uint32 addr, uint32 val) {}

void CPU::DetermineSignals()
{
	OpcodeType opcodeType = Opcode::opcodeTable[f_d.fetched_i.rType.opcode].opcodeType;
	bool is_r_type = f_d.fetched_i.rType.opcode == 0;
	if (is_r_type) { //if it's an R-type instruction 
		opcodeType = Opcode::functTable[f_d.fetched_i.rType.funct].opcodeType;
	}
	switch (opcodeType)
	{
	case OpcodeType::Load:
		d_e.jump = 0;
		d_e.link = 0;
		d_e.regWrite = 1;
		d_e.memtoReg = 1;
		d_e.branch = 0;
		d_e.memRead = 1;
		d_e.memWrite = 0;
		d_e.regDst = 1;
		d_e.ALU = 1;
		d_e.ALUsrc = 1;
		d_e.shift = 0;
		d_e.mulDiv = 0;
		break;
	case OpcodeType::Store:
		d_e.jump = 0;
		d_e.link = 0;
		d_e.regWrite = 0;
		d_e.memtoReg = 0;
		d_e.branch = 0;
		d_e.memRead = 0;
		d_e.memWrite = 1;
		d_e.regDst = 0;
		d_e.ALU = 1;
		d_e.ALUsrc = 1;
		d_e.shift = 0;
		d_e.mulDiv = 0;
		break;
	case OpcodeType::ALU:
		d_e.jump = 0;
		d_e.link = 0;
		d_e.regWrite = 1;
		d_e.memtoReg = 0;
		d_e.branch = 0;
		d_e.memRead = 0;
		d_e.memWrite = 0;
		d_e.regDst = 1;
		d_e.ALU = 1;
		d_e.ALUsrc = 0;
		d_e.shift = 0;
		d_e.mulDiv = 0;
		break;
	case OpcodeType::Shift:
		d_e.jump = 0;
		d_e.link = 0;
		d_e.regWrite = 1;
		d_e.memtoReg = 1;
		d_e.branch = 0;
		d_e.memRead = 1;
		d_e.memWrite = 0;
		d_e.regDst = 1;
		d_e.ALU = 0;
		d_e.ALUsrc = 0;
		d_e.shift = 1;
		d_e.mulDiv = 0;
		break;
	case OpcodeType::MulDiv:
		d_e.jump = 0;
		d_e.link = 0;
		d_e.regWrite = 1;
		d_e.memtoReg = 1;
		d_e.branch = 0;
		d_e.memRead = 1;
		d_e.memWrite = 0;
		d_e.regDst = 1;
		d_e.ALU = 0;
		d_e.ALUsrc = 0;
		d_e.shift = 0;
		d_e.mulDiv = 1;
		break;
	case OpcodeType::Jump:
		d_e.jump = 1;
		d_e.link = 0;
		d_e.regWrite = 0;
		d_e.memtoReg = 0;
		d_e.branch = 0;
		d_e.memRead = 0;
		d_e.memWrite = 0;
		d_e.regDst = 0;
		d_e.ALU = 0;
		d_e.ALUsrc = 0;
		d_e.shift = 0;
		d_e.mulDiv = 0;
	case OpcodeType::Link:
		d_e.link = 1;
		d_e.regDst = 1;
		break;
	case OpcodeType::Branch:
		d_e.jump = 0;
		d_e.link = 0;
		d_e.regWrite = 0;
		d_e.memtoReg = 0;
		d_e.branch = 1;
		d_e.memRead = 0;
		d_e.memWrite = 0;
		d_e.regDst = 0;
		d_e.ALU = 0;
		d_e.ALUsrc = 0;
		d_e.shift = 0;
		d_e.mulDiv = 0;
	default:
		break;
	}
}
uint32 CPU::ExecALU(uint32 op1, uint32 op2, Operation operation)
{
	uint32 result = 0;

	switch (operation) {
	case Operation::Add:
		result = op1 + op2;
		break;

	case Operation::Sub:
		op2 *= -1;
		result = op1 + op2;
		break;

	case Operation::And:
		result = op1 & op2;
		break;

	case Operation::Or:
		result = op1 | op2;
		break;

	case Operation::Xor:
		result = op1 ^ op2;
		break;

	case Operation::Slt:
		result = op1 - op2 == 0;
		break;
	}
	if (d_e.opSigned) {
		if (!((op1 >= 0) ^ (op2 >= 0)) && ((op1 >= 0) ^ (result >= 0))) {
			//trigger overflow trap
		}
	}

	return result;
}
uint32 CPU::ExecShifter(uint32 op1, uint32 op2, Operation operation)
{
	uint32 lsb = 0;
	uint32 msb = 0;

	switch (operation)
	{
	case Operation::ShiftLeftLogic:
		op1 <<= op2;
		break;

	case Operation::ShiftRightLogic:
		op1 >>= op2;
		break;

	case Operation::ShiftRightArith:
		for (uint32 i = 0; i < op2; i++) {
			op1 >>= 1;
			op1 |= (op1 & (1 << 30)) << 1;
		}
		break;

	case Operation::RotRight:
		
		for (uint32 i = 0; i < op2; i++) {
			lsb = op1 & 0x00000001;
			op1 >>= 1;
			op1 |= lsb << 31;
		}
		break;

	case Operation::RotLeft:
		
		for (uint32 i = 0; i < op2; i++) {
			msb = op1 & 0x80000000;
			op1 <<= 1;
			op1 |= msb >> 31;
		}
		break;
	}

	return op1;
}
uint32 CPU::ExecMulDiv(uint32 op1, uint32 op2, Operation operation)
{
	uint64 result = 0;
	uint64 remainder = 0;

	switch (operation)
	{
	case Operation::Mul:
		if (d_e.opSigned) {
			result = static_cast<int64>(op1) * static_cast<int64>(op2);
		}
		else {
			result = static_cast<uint64>(op1) * static_cast<uint64>(op2);
		}

		hi = static_cast<uint32>(result >> 32);
		lo = static_cast<uint32>(result);
		break;

	case Operation::Div:
		if (d_e.opSigned) {
			result = static_cast<int64>(op1) / static_cast<int64>(op2);
			remainder = static_cast<int64>(op1) - (result * static_cast<int64>(op2));
		}
		else {
			result = static_cast<uint64>(op1) / static_cast<uint64>(op2);
			remainder = static_cast<uint64>(op1) - (result * static_cast<uint64>(op2));
		}

		hi = static_cast<uint32>(result);
		lo = static_cast<uint32>(remainder);
		break;

	case Operation::ReadHi:
		return hi;
		break;

	case Operation::ReadLo:
		return lo;
		break;

	case Operation::WriteHi:
		hi = op1;
		break;

	case Operation::WriteLo:
		lo = op1;
		break;
	}

	return 0;
}

void CPU::Fetch()
{	
	f_d.fetched_i.all = CPU::ReadWord(pc);

	f_d.next_pc = pc + 4;
	bool pcSrc = e_m.branch && !e_m.result;
	if (pcSrc) { //aka "PCsrc" is off
		pc = e_m.branch_result;
	} 
	else if (d_e.jump) {
		pc = d_e.addr;
	}
	else {
		pc += 4;
	}
}

void CPU::Decode()
{
	DetermineSignals();
	d_e.next_pc = f_d.next_pc;
	d_e.opcode = f_d.fetched_i.iType.opcode;
	d_e.funct = f_d.fetched_i.rType.funct;
	d_e.reg_r_data1 = R[f_d.fetched_i.rType.rs];
	d_e.reg_r_data2 = R[f_d.fetched_i.rType.rt];
	d_e.rt = f_d.fetched_i.rType.rt;
	d_e.rd = f_d.fetched_i.rType.rd;
	d_e.imm = (uint32)f_d.fetched_i.iType.imm; //need to check if its correct
	d_e.addr = f_d.fetched_i.iType.opcode == Opcodes::R_TYPE ? d_e.reg_r_data1 : (uint32)f_d.fetched_i.jType.addr;
}

void CPU::Execute()
{
	e_m.regWrite = d_e.regWrite;
	e_m.memtoReg = d_e.memtoReg;

	e_m.branch = d_e.branch;
	e_m.memRead = d_e.memRead;
	e_m.memWrite = d_e.memWrite;

	e_m.branch_result = d_e.next_pc + (d_e.imm << 2);
	uint32 op1 = d_e.reg_r_data1;
	uint32 op2 = 0;
	Operation operation = d_e.opcode ? Opcode::opcodeTable[d_e.opcode].operation : Opcode::functTable[d_e.funct].operation;
	e_m.mem_w_data = d_e.reg_r_data2;
	
	if (d_e.ALU) {
		op2 = d_e.ALUsrc ? d_e.imm : d_e.reg_r_data2;
		e_m.result = ExecALU(op1, op2, operation);
	}
	if (d_e.shift) {
		d_e.opcode & 0xb0100 ? d_e.reg_r_data2 : ((d_e.imm >> 6) & 0b11111); //extract the "shift ammount" from imm
		e_m.result = ExecShifter(op1, op2, operation);
	}
	if (d_e.mulDiv) {
		op2 = d_e.reg_r_data2;
		e_m.result = ExecMulDiv(op1, op2, operation);
	}
	e_m.reg_w_reg = d_e.regDst ? d_e.rd : d_e.rt;
}

void CPU::Mem()
{
	m_w.regWrite = e_m.regWrite;
	m_w.memtoReg = e_m.memtoReg;

	if (e_m.branch && !e_m.result) { //the "else" appears in the beginning of Fetch()
		pc = e_m.branch_result;
	}

	if (e_m.memRead) {
		if (e_m.byteAccess[0] == 1
			&& e_m.byteAccess[1] == 1
			&& e_m.byteAccess[2] == 0
			&& e_m.byteAccess[3] == 0) {
			m_w.mem_r_data = static_cast<uint32>(CPU::ReadHalf(e_m.result));
		}
		else if (e_m.byteAccess[0] == 1
			&& e_m.byteAccess[1] == 1
			&& e_m.byteAccess[2] == 1
			&& e_m.byteAccess[3] == 1) {
			m_w.mem_r_data = CPU::ReadWord(e_m.result);
		}
		else {
			for (size_t i = 0; i < 4; i++) {
				if (e_m.byteAccess[i]) {
					*(reinterpret_cast<uint8*>(&m_w.mem_r_data) + i) = CPU::ReadByte(e_m.result + i);
				}
			}
		}
	}
	if (e_m.memWrite) {
		if (e_m.byteAccess[0] == 1
			&& e_m.byteAccess[1] == 1
			&& e_m.byteAccess[2] == 0
			&& e_m.byteAccess[3] == 0) {
			CPU::WriteHalf(e_m.result, e_m.mem_w_data);
		}
		else if (e_m.byteAccess[0] == 1
			&& e_m.byteAccess[1] == 1
			&& e_m.byteAccess[2] == 1
			&& e_m.byteAccess[3] == 1) {
			CPU::WriteWord(e_m.result, e_m.mem_w_data);
		}
		else {
			for (size_t i = 0; i < 4; i++) {
				if (e_m.byteAccess[i]) {
					CPU::WriteByte(e_m.result + i, *(reinterpret_cast<uint8*>(&e_m.mem_w_data) + i));
				}
			}
		}
	}
	m_w.reg_w_data = e_m.result;
	m_w.reg_w_reg = e_m.reg_w_reg;
}

void CPU::WriteBack()
{
	if (m_w.regWrite) {
		if (m_w.reg_w_reg != 0) { //NOT the zero register
			R[m_w.reg_w_reg] = m_w.memtoReg ? m_w.mem_r_data : m_w.reg_w_data;
		}
	}
}

void CPU::Bubble()
{
	f_d.fetched_i.all = 0;
	f_d.next_pc = 0;
}

void CPU::Cycle()
{
	WriteBack();
	Mem();
	Execute();
	Decode();
	Fetch();
}