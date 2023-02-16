//#define LLFIO_EXPERIMENTAL_STATUS_CODE 0
//#define LLFIO_HEADERS_ONLY 0
//#define NTKERNEL_ERROR_CATEGORY_INLINE 0
//#define LLFIO_STATIC_LINK 1


#define _CRT_SECURE_NO_WARNINGS

//#include "InstructionSet.h"

//#include "ma.h"
#include "P2.hpp"
//#include "P1.h"






int main()
{
   
    //is.checkSupportedSets();
    
    //ma aa;
    //aa.StrTSr();

    //if (InstructionSet::AVX2())
    {
        //AVX2Alt.P2A();
        P2::P2A();
        //P3::P3A();
    }
   /* else
    {
        P1::P1();
    }*/
    
    
    
    return 0;
}
