#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdint.h>
#include <array>
#include <string>

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

enum Regs {
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
	fp,
	ra,
};

const std::array<std::string, ra + 1> regAliases;

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

#endif