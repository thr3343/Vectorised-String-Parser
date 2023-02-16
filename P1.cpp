

#include "P1.h"
using  std::cout;
using  std::endl;

//lazy hack to fix variable type/aliasing isues with MSVC accpeted argument types for some specific intrinsics




/*BUGS:
    * fix issue where the Temp ref Offset Matches array is wortten to out of budns which c=cayses an Acess Violation if the numebr of Fuzzy psotives excess the Char buffer Size
    * The Binary will stall or crash with an access Violation in some isnteaes if the number of fuzzy positive matches is too great:
    * this is especially common with  happen with high ferauency ocurencies as a result of usinh common shorter words such as "Hello" or "However"
        * this can't be  mitigated with dynamic containers such as std::vetcors or STD::stakc due to the perfoamnce imptc beign too gerat compaired to static Arrays

    * Due to an oversight with the fizzy serahc algorythm only pos offsets diviable by 2 are wirtten to the OffsetCache.
        * this causes the 2nd pass/more precise search to be highly flawed due to the alignment issues and false positives/megatives with some word matches
*/

//#define SecondPassPrintOutput
//#define NoSecondPass
//#define BenchMode
/*todo: assumes MSVC for now. so some marcos may not work /+ other assumptions
    * intrinsics will likely not comoule on compilers other than MSVC and ICC (due to differening header file names as GCC/Clang use x86intrin.h while msvc and ICC use immintrin.h or intrin.h and teher are no advaltive names availble to adtract header comaptiblities between the two
        */

        //  -> OffStack vraiables delcaired outisde of main to avoid Stack Overflow/Capacity Limitaions
           //static  char filename[] = "opendata-2021-02-11-063811+0000.jsonl";


/*64_bit unigned integers must be used in this case due to the 32-Bit integer limit
    *which would othersie limit the maximum filesize to 4GB without chunking strategies
*/

//llfio_v2_74e71064::mapped_file_handle s2();



inline const void P1::read(char& buf, uint64_t& pos)
{
    s1.seekg((pos));
    s1.read(&buf, XScaleFactorAlt);
}



void P1::P1A()
{

    Matches1 = 0;
    subOffset1 = 0;
    slice1 = 0;
    subSlice1 = 0;
    s1.seekg(0, s1.end);  // first argument is starting pos of the char to beigin
                        // parsing from/to
    uint64_t size =
        s1.tellg();



    // -> Vector Variables


    const __m128i sub = _mm_loadu_epi16(subA1);


    //Lazy method to shift the Sub vetcor by one Byte(! Char) to allow the 2nd.3rd Char pair Offset mask to be aligned correctly to allow trople CharSet Pattern matching e.g.
    __m128i sub1 = _mm_bsrli_si128(sub, 1);


    //load Triple word maitch setup to handle offsets as well as Truncation

    //Offset mask DWord Pairs
    __m128i subM1 = _mm_set1_epi16(_mm_extract_epi16(sub, 0));
    __m128i subM2 = _mm_set1_epi16(_mm_extract_epi16(sub1, 0));

    //input 

    __m128i Vin;


    //intermediate Masks

    __m128i ItrM1;
    __m128i ItrM2;
    __m128i X3;


    // -> positonal Offset varibles for Tzbnt/Leading Zeros

    bool k;

    unsigned long l;



    char *P3 = &readBuf1[0];
    sizeDeriv1 = size / XScaleFactorAlt;
    std::cout << "ScaleFactor: " << XScaleFactorAlt << std::endl;

    std::cout << "Size: " << size << std::endl;
    std::cout << "Size2: " << (size / VEC_LEN_ALT) << std::endl;
    std::cout << "Iterations: " << sizeDeriv1 << std::endl;
    std::cout << "Iterations Per slice: " << (IterationsAlt) << std::endl;
    std::cout << "Total Iterations: " << sizeDeriv1 * (IterationsAlt) << std::endl;



    P3 = new char[XScaleFactorAlt]; //Don't sem to need to dyna,ically allcoate and sclar delet the ppinter anymroe in the loo, which should help to reduce overhead slightly

    long Init = clock(); //get current time in Millseconds: is extremely bugged and sill become highly unreliable if the CPU clock rate is inconsitent and changes during runtime
    for (; slice1 <= sizeDeriv1; slice1++)
    {
        l = k = 0;
        posA1 = (slice1 * XScaleFactorAlt);
        read(*P3, posA1);
        for (subSlice1 = 0; subSlice1 < XScaleFactorAlt; subSlice1 += VEC_LEN_ALT) //must be reset in loop to aovid the read Buffer Offet Bug as otherwise it resets to zeo otside the loop at the wrong.incorerct interval, which cases teh erad Bufefr to read at teh wrong location/offset that is Outside th current Slice, CHunk[er] range
        {

            //Load current postional offset Vector aligned to 128/256 Bits
            Vin = _mm_load_si128(reinterpret_cast<__m128i*>(&P3[subSlice1]));

            //Mask the current input vector 
           
            /*compress L and R masks into One to simplify mask handling and overhead
                *(due to not having to deal with multiple masks anymore)
            */

            X3 = _mm_xor_si128(_mm_cmpeq_epi16(Vin, subM1), _mm_cmpeq_epi16(Vin, subM2));

            //Extra all leftmopst MSB from the Intermediate Xor mask and count teh left-most leaidng zeros from the resultimg integer
            Matches1 += k = _BitScanForward64(&l, (_mm_movemask_epi8(X3)));

            /*Calculate the positonal offset by multiplying the
                current interation by the buffer size constexpr
                and adding the current sclie position and the exact
                pos offset derived from the prior step
            */

            subOffset1 = (slice1 * XScaleFactorAlt) + (subSlice1 + l);


            /*Store the current fuzzy match positional offset into the Positional offset Array,
                *and ensure it is contingous to avoid unnessacery fragmentation
                * this is also mutiplied by the boolean assigedn easiler to cause the index to equal Zero
                * to allow false negative offsets to always be overwritten at the 0th index of the Array
            */

            OffsetCache1[Matches1 * k] = subOffset1;
        }
    }

    /*if (Init == 0)
    {
        Init = 1;
    }*/

    Init = clock() - Init;
    double I2 = Init;
    std::cout << (I2 / 1000) << " Seconds" << std::endl;
    std::cout << (size / Init) << " KiloBytes Per second" << std::endl;
    s1.clear();
    s1.seekg(0, s1.end);



    std::cout << "Ovrela Matching Predicates     " << Matches1 << std::endl;



    unsigned long v; 
    //Start at index 1 to avoid the dummy 0th index dump pos and t avodi seekg from reahcing. gping out of boudns with the file
    //Very lazy sclar loop to filter the reminader of the losse fuzzy matches from the firts pass: is highly inefficnet and is dtartcially les sperfomant due to the contant adjustment of the File read offset through seekg which adds additional copy latency 

       //cant currenttee alignment to 16/32 due to char buffer sizes not always aligning!



    __m128i vtest;
    __m128i vtestR;

    __m128i vXorMaskA;
    __m128i vXorMaskB;
  

    uint64_t tz = 0;
    int Abs = 0;
    int Abs1 = 0;

    int Abs2 = 0;
    int Abs3 = 0;
    bool Ext = 0;
    bool Ext1 = 0;

    //Very lazy  loop to filter the reminader of the losse fuzzy matches from the firts pass: 
    //is highly inefficnet and is drastcially less performant due to the contant adjustment of 
    //the File read offset through seekg which adds additional copy latency 

    int AbsMatches = 0; static char P4[VEC_LEN_ALT];  static char P5[VEC_LEN_ALT]; int k2 = 0;// sizeof(c) - 2;
    for (v = 1; v <= Matches1; v++)
    {

        s1.seekg(OffsetCache1[v]);
        s1.read(P4, sizeof(subA1) - 1);
        s1.seekg(OffsetCache1[v] - 1);
        s1.read(P5, sizeof(subA1) - 1);
        vtest = _mm_lddqu_si128(reinterpret_cast<__m128i*>(P4));
        vtestR = _mm_lddqu_si128(reinterpret_cast<__m128i*>(P5));

        vXorMaskA = _mm_xor_si128(vtest, _mm_setzero_si128());
        vXorMaskB = _mm_xor_si128(vtestR, _mm_setzero_si128());
        
        /*testc seems to have issues with carrying out AND and not setting the CF / Specific register flag to 1:
                       *This occurs if specific queries such as "RTX 3070" are used with the specific test File used
                       *but not with other queries such as "barbershop", which do not seem to exhibit this particular issue*/        
        Abs2 += Ext = _mm_testc_si128(sub, vtest);
        Abs3 += Ext1 = _mm_testc_si128(sub, vtestR);
    }

    cout << Abs2 + Abs3 << endl;
    Init = clock() - Init;
    double I3 = Init;
    cout << (I3 / 1000) << " Seconds for 2nd Pass" << endl;

    cout << AbsMatches << endl;



}