




#include "P3.h"


using std::cout;
constexpr void P3::readf(char &buf, FILE &file)
{
	//fseek(&file, (abs*16), SEEK_SET);
	// fseek(&file, (0), SEEK_SET);
	fread(&buf,8, sizeofi/8, &file);
}






const void P3::P3A()

{
	
	//char* P3 = std::assume_aligned<char*>(&membuf)
	fseek(file, 0, SEEK_END);
	uint64_t asize= ftell(file);
	// uint64_t asize2= 0xfffff;
	// char membuf[asize2];
	//uint8_t membuf2[asize2];
	rewind(file);
	cout << "Size: " << asize  << "\n";
	setbuf(file, membuf);
	for (int ii =0; ii< 0xFFFFFF; ii++)
	{
		rewind(file);
		//cout << ii  << "\n";
		for(uint64_t a =0; a< (asize/sizeofi); a++)
		{
			readf(*membuf, *file);
			//readf(*membuf2, (asize2), *file);
			//cout << a  << "\n";
			//for (uint32_t ax =0; ax< 16; ax++)
			{
				//cout << membuf << "\n";
				//cout << "------------------>" << "\n";
			}
			
		}
	}
	int aa;
	std::cout << "Finished/Done Parsing!";
	std::cin >> aa;
	
}