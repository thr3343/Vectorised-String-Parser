#pragma once

#define _CHAR_UNSIGNED

#include <iostream>
#include <fstream>
#include <immintrin.h>
#include <intrin.h>

	constexpr uint8_t VEC_LEN_ALT = 16;
	constexpr uint64_t XScaleFactorAlt = 0xFFFFF;
	constexpr uint64_t IterationsAlt = XScaleFactorAlt / VEC_LEN_ALT;

	constexpr char subA1[] = { "barbershop" };
	constexpr char filename1[] = "opendata-2021-04-25-064055+0000.jsonl";

	static uint64_t OffsetCache1[XScaleFactorAlt]; 	//Temp Offset buffer to store all Positional offsets (from the beginning of the File) of positive Fuzzy matches
	static char readBuf1[XScaleFactorAlt]; //read Char buffer to handle reads extracted from the file
	
	static uint64_t Matches1;
	static uint64_t subOffset1;
	static uint64_t slice1;
	static uint64_t subSlice1;
	static uint64_t sizeDeriv1;
	static uint64_t posA1;

	static std::ifstream s1(filename1, std::ios::binary);

	

class P1
{
private:
	static inline const void read(char& buf, uint64_t& pos);
	static void P1A();
	
public:

	explicit P1() { std::iostream::sync_with_stdio(false);P1A(); }


};