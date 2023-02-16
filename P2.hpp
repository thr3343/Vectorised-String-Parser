#pragma once
#define _CRT_SECURE_NO_WARNINGS

//#define _CHAR_UNSIGNED

//#include <cstdio>
#include <iostream>
//#include <fstream>
// #include <immintrin.h>
#include <intrin.h>
#include <memory>
//#define SuBCacheAlignSuBincr 65536
	
	constexpr uint8_t VEC_LEN = 32ul;
	constexpr uint64_t XScaleFactor = 1048576;//*256;
	constexpr uint64_t SUbCacheFactor = 128;
	// constexpr uint64_t Iterations = XScaleFactor / VEC_LEN;
	// constexpr size_t SuBCacheAlignSuBincr = (1048576*8);
	

	constexpr char subA[] = { "barbershop" };
	constexpr char filename[] = {"opendata-2021-04-25-064055+0000.jsonl"};
	// inline uint32_t readBuf2[SuBCacheAlignSuBincr];//={alignof(alignas(XScaleFactor) uint8_t[XScaleFactor]);

		
	//inline uint64_t OffsetCache[0]; 	//Temp Offset buffer to store all Positional offsets (from the beginning of the File) of positive Fuzzy matches
	//inline char readBuf[XScaleFactor]; //read Char buffer to handle reads extracted from the file
	inline __m256i readBuf[XScaleFactor*2];
	//inline const void* readBuf=(uint8_t*)malloc(sizeof(uint8_t)*XScaleFactor);
	
	//static uint64_t slice;
	static uint64_t subSlice;
	static uint64_t sizeDeriv;
	static uint64_t posA;
	



	//static std::ifstream s(filename, std::ios::binary);
struct P2
{
private:
	 static inline  void load2(const __m256i&a, __m256i &v);
	 static inline constexpr void read(__m256i& buf, uint64_t &posA, FILE& file);
	 static inline constexpr void memcpy2(const void *dest, const void *src, const size_t &n);


public:
	static void P2A();

	
	
};