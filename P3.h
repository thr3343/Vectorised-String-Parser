#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <intrin.h>
#include <memory>

constexpr uint32_t sizeofi = 0xFFFFF; //65536//32768//16384//8196
inline FILE* file = fopen("T.txt", "rb"); //Only Perofmance if te file Size fits on the L3 cache / Otherwise parsing owthpt manual fseek Readjustments>|Relignments is Drastelly less Performant/ThorughPut; this sems to Ieter be an issue with Aligned([M])Alloc and.Or issue swith loaidng 'CHunk Sizes' greater than approx 32/65k At At Time; Which if True/Is Teh Case would Eplain why a manua;fseek is So much mro DrastciallY performant Due to only neding to Map/ALign?Load.......] 32-65K Ahead of teh current File, random Erad/Seuwnetial read position


inline char membuf[sizeofi];



struct P3
{
	constexpr inline static void readf(char &buf, FILE &file);
	
	const static void P3A();
	
};