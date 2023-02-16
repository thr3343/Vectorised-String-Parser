#include "ma.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

constexpr uint64_t CharLen = 0x1FFFF; //0x1FFF


char ma::StrTSr()
{

	//const uint32_t CharLen = 32683; //May use variable size single line only method for now for simplicities sake and to highlight teh potnetial for perhapes unaligned memeory/unalignedregsiters/intrincis and/or potentital perf implcitaions of unaligned.varaible memory alloc sizes......................... e.g.
	uint32_t CurrentCharIdx = 0;
	uint32_t al = 0;
	uint32_t al2 = 0;
	static uint32_t al3 = 0;

	//std::ifstream s("Blah.txt");
	std::ifstream s("opendata-2021-04-25-064055+0000.jsonl");

	s.seekg(0, s.end); //first argument is starting pos of the char to beigin parsing from/to
	double size = s.tellg(); //needs to be float to represent non-divisive divisiosn corerctly to ensure that the iteration variable is ceils proerplya nd to avoid automatic rounding.flooring of the resulting division/outcome.output/prudtc
	s.seekg(0);

	double itr = size / CharLen;

	printf("%s %f %s \n", "File is", size, "Bytes");

	printf("%f %s\n", itr, "Unfloored");

	itr = std::ceilf(itr);
	uint32_t ai = 0;
	int ii;
	cout << "Shoudl need " << itr << " Iterations" << "With " << a << "empty chars" << endl;

	unsigned char buff[CharLen] = ""; //adding empty/null char seems to help with peeventing invaid/incorrect chars from being printed

	char* buff2;
	int i;
	
	long Init = std::clock();

	buff2 = new char[CharLen];
	int iii = 0;
	for (; iii < itr; iii++)
	{

		//read block of chars  and allocate memory block size equal to the pointe buffer array size
		//offsetting the allocated memeory size by one seems to help with preventing invalid chars from being generated/printed
		s.read(buff2, sizeof(buff) - 1);

		ai++;
		al += CharLen;
		
		for (i = 0; i < CharLen; i++)
		{
			ii = 0;

			
				while (buff2[i] == ax[ii])
				{
					ii++;
					i++;
					al2++;
				}
				if (al2 == sizeof(ax)-1)
					al3++;
				
			
			al2 = 0;
		}

	}
	
	Init = std::clock() - Init;
	double I2 = Init;
	std::cout << (I2 / 1000) << " Seconds" << std::endl;
	std::cout << (size / Init) << " KiloBytes Per second" << std::endl;
	
	printf("\n");
	
	std::cout << "\n";
	std::cout << ai << " Iterations" << std::endl;
	std::cout << al3 << " Chars/valid Words Found from "<< al << " Chars Total " << std::endl;
	cout << (al -= size) << " Excess Chars/Line Terminations e.g." << endl<<endl;

	s.close();
	

	

	return 0;
}
