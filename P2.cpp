#include "P2.hpp"


//#define X reinterpret_cast<__m256i*>
#define X (__m256i*)


/*BUGS:
    * fix issue where the Temp ref Offset Matches array is wortten to out of budns which c=cayses an Acess Violation if the numebr of Fuzzy psotives excess the Char buffer Size
    * The Binary will stall or crash with an access Violation in some isnteaes if the number of fuzzy positive matches is too great:
    * this is especially common with  happen with high ferauency ocurencies as a result of usinh common shorter words such as "Hello" or "However"
        * this can't be  mitigated with dynamic containers such as std::vetcors or STD::stakc due to the perfoamnce imptc beign too gerat compaired to static Arrays

    * Due to an oversight with the fizzy serahc algorythm only pos offsets diviable by 2 are wirtten to the OffsetCache.
        * this causes the 2nd pass/more precise search to be highly flawed due to the alignment issues and false positives/megatives with some word matches
*/
//llfio_v2_74e71064::mapped_file_handle s2();
//constexpr bool k = 1;
//constexpr bool k1 = k!=k;
 void P2::load2(const __m256i&a, __m256i &v)
{
    // auto vv = (__m256i*)(a);
     //__m256i v = _mm256_load_si256(reinterpret_cast<__m256i*>(a));
    v= _mm256_load_si256(&a);
}

 //void P2::read(__m256i& buf, uint64_t &posA, FILE &file)
constexpr inline void reset(FILE &file)
{
	rewind(&file);
}
constexpr void P2::read(__m256i &buf, uint64_t &posA, FILE &file)
{
    //fsetpos(&file, &pos);
    
       fread(&buf, 16, XScaleFactor/16, &file);fseek(&file, (XScaleFactor/16), SEEK_SET);
       // posA+=fread(&buf, 1, sizeof(buf), &file);
}
	constexpr void P2::memcpy2(const void *dest, const void *src, const size_t &n)
{
    for ( uint64_t i; i < n/64 ; i-- )
        ((__m512i*)dest)[i] = ((__m512i *)src)[i];
    //return dest;
}

/*corrected odd stack relatd isue wit agnent
 *whetehr this is rleated to stakc aligment or cacheline and//or port-presure r;eated isuse sis ot curently confirmed.
*/
void P2::P2A()
{
	
	

    //Matches = 0;
    //subOffset = 0;
    //slice = 0;
    //subSlice = 0;
    uint64_t size = 0;
    FILE* file = fopen("opendata-2021-04-25-064055+0000.jsonl", "rb");
    //fpos_t pos = 0;
    if (file == NULL)
    {
        exit(1);
  }
    

    //s.seekg(0, s.end);  // first argument is starting pos of the char to beigin parsing from/to
    //uint64_t size =
    //    s.tellg();


// -> Vector Variables

     __m256i sub = _mm256_load_si256(X(subA));


    //Lazy method to shift the Sub vetcor by one Byte(! Char) to allow the 2nd.3rd Char pair Offset mask to be aligned correctly to allow trople CharSet Pattern matching e.g.
    __m256i sub1 = _mm256_bsrli_epi128(sub, 1);


    //load Triple word maitch setup to handle offsets as well as Truncation

    //Offset mask DWord Pairs
    __m256i subM1 = _mm256_set1_epi16(_mm256_extract_epi16(sub, 0));
    __m256i subM2 = _mm256_set1_epi16(_mm256_extract_epi16(sub1, 0));

    //input 

    __m256i Vin;


    //intermediate Masks

    //__m256i ItrM1;
    //__m256i ItrM2;
    __m256i X3;
	
	__int128_t xl= 0xFFFFFFFF;

 bool k;

    unsigned long l;
/*pos = */fseek(file, 0, SEEK_END);
 
    //fgetpos(file, &pos);
    size = ftell(file);
  sizeDeriv = size / XScaleFactor;  // -> positonal Offset varibles for Tzbnt/Leading Zeros
   long Init = clock();  
   //__m256i *P3= std::assume_aligned<XScaleFactor>((__m256i*)readBuf);
   
   setbuf(file, NULL);
for(int i=0; i<2560;i++)
{
  
	reset(*file);
    //fgetpos(file, &pos);

   
    



    // if (P3==nullptr)
    // {
        // exit(0);
    // }
    /*get current time in Millseconds:
    * this timing function highly unreliable if the CPU clock rate is inconsitent and changes during runtime
    * this is due to the inconsistent fereqncies of the CPu which occur in any cases that change the Clock Rate,
        such as that of Turbo Bootsing implemtaions, which will cause the rate of time measured to vary as the lcok rate differed during runtime

        Ideally a more optimal acucrate and rlaible timing mechanism is with implementing timing function that utilse the Wall time instead of teh CPu time,
        which unlike the latter actually reflects real-world time insted of timing deived from the CPU frequency
    */

    //uint8_t switch_on = 2;
    /*switch (switch_on)
    {*/
    //case 1:
    //{
    //    {//VariableAdaptiveOffSet:
    //        while(subSlice < XScaleFactor)
    //        {
    //            load2(P3[subSlice], Vin);
    //            X3 = _mm256_xor_si256(_mm256_cmpeq_epi16(Vin, subM1), _mm256_cmpeq_epi16(Vin, subM2));
    //            Matches += k1 = _BitScanForward64(&l, (_mm256_movemask_epi8(/*_mm256_andnot_si256*/(X3))));
    //            
    //            subSlice += (VEC_LEN &l);
    //        }

    //    }
    //    break;
    //}
	
   // case 2:

   

    
        for (uint64_t slice = 0; slice <= size / XScaleFactor<<0; slice++)
        {
            //l = k = 0;
            //posA = (slice * XScaleFactor);
            //fsetpos(file, posA);
            //fread(P3, 1, size, file);

           read(*readBuf, slice, *file);
		   //std::cout << posA << std::endl;
		    uint64_t Matches;
		   //for (uint64_t a=0; a<XScaleFactor; a+=SuBCacheAlignSuBincr)
		   {
		   //
			//memcpy2(readBuf2, readBuf+a, SuBCacheAlignSuBincr);
            // for (subSlice=0; subSlice < SuBCacheAlignSuBincr; subSlice += VEC_LEN) //must be reset in loop to aovid the read Buffer Offet Bug as otherwise it resets to zeo otside the loop at the wrong.incorerct interval, which cases teh erad Bufefr to read at teh wrong location/offset that is Outside th current Slice, CHunk[er] range
            for (subSlice=0; subSlice < XScaleFactor; subSlice += VEC_LEN) //must be reset in loop to aovid the read Buffer Offet Bug as otherwise it resets to zeo otside the loop at the wrong.incorerct interval, which cases teh erad Bufefr to read at teh wrong location/offset that is Outside th current Slice, CHunk[er] range
            {

                //Load current postional offset Vector aligned to 128/256 Bits
                Vin = _mm256_load_si256((readBuf+subSlice));
                //load2(P3[subSlice], Vin);
				//Vin=P3[subSlice];

                //Mask the current input vector 

                /*compress L and R masks into One to simplify mask handling and overhead
                    *(due to not having to deal with multiple masks anymore)
                */

                X3 = _mm256_xor_si256(_mm256_cmpeq_epi16(Vin, subM1), _mm256_cmpeq_epi16(Vin, subM2));

                //Extra all leftmost MSB from the Intermediate Xor mask and count teh left-most leaidng zeros from the resultimg integer
				//OverWrite,nOt incrememnt Uint64_t as is gerately reudced Port pressure/nlning.FusedOpts e.g./And.oR delcar in loop, Out Outisde/external/Scope to it! and.or not as statc/inline/const/impl/ed varable in teh struct/extenral/StackPorbelmMaybe......./Perahpes/Hypthetical e.g..etc.i.e..Misc.Verf..Conf.Abs.Actualisationalizationalizationalzmentaabalismenatleversiabelsnaies
					//was actually due to tcunt/_bitscaforward64 eing optimised out so may stll be a issue
				/*Edit: Was actualy due to Incrementing theX£ VEtcor incrretcly and Increming a varuble/Matche/X3 curing the loop/reucirosna d not outside it to reduce excesisve Frequency.Writes
					* In otherwors, teh exatc Layout and handling of varbels curing regsiter.move.trhotuut Ops/Cahcelins>prtpresure ops is extremely Important ad a Single unesscarey read/wirte can lead to ecessuve Stalog/I te @PipeLIne' e..g et.c ile. .MSic.labs	
						*e.g  It was discovered taht due to * in fact A *Alowing for |Ful perfrmance to be estored Completely With NoA dditonal Disadvategs or Drawbacks Or COmpromises.subaptima,ostaonalsisato, Limitiaons.Overeheads.Oupsolinesinary.Inherteeydntlende.ActualistaonalisatioalIsationalIsaionalisationale..g e.tc i.e..Misc.l.e.Verf.Conf.Abs.Gots.Ortuth.Dtes.QUatsAnima.
					*/
                Matches = _tzcnt_u64((_mm256_movemask_epi8(X3)));

                /*Calculate the positonal offset by multiplying the
                    current interation by the buffer size constexpr
                    and adding the current sclie position and the exact
                    pos offset derived from the prior step
                */

                /*Might be poisbel to instead accecs sthe array again whlst it sia ctive/Initialsied
                at the partcou\lr offset of the current fuzzy Serach.match and store/copy teh array portip
                equal to the Charset size/wodth.elngth into a temp buffer array, preventing the need at leats in ethory to carry out the 2nd Pass


            this has the promary darwback of requiring a direct load again and/or storeu to copy to teh arraybuf which may icnurr too much CPI/Thouput/cache latency problems,
                    however L1 chache+DDR Acces for approx less than 512 Bytes/8KB of mem is less than 1 Ns .Approx and may still be faster than a memcpy,
                    which at 4Ghz iz only approx 4 clocks lost per iteration and may alsom hold inereht potnetial for Microfused StorOps/Preemptive execution of
                   wivia simply using a seperate cache line to concurrent read and write at the same time

            May even be poisble to compair the offste dierctly with the Charset vetcor via AND and */

            //subOffset = (slice * XScaleFactor) + (subSlice + l);


            /*Store the current fuzzy match positional offset into the Positional offset Array,
                *and ensure it is contingous to avoid unnessacery fragmentation
                * this is also mutiplied by the boolean assigedn easiler to cause the index to equal Zero
                * to allow false negative offsets to always be overwritten at the 0th index of the Array
            */

                //OffsetCache[Matches * k] = (posA + subSlice + l);
            }xl+=Matches;
		   } 
        }
        //break;
    
    
        fseek(file, 0, SEEK_END);
   //c= clock();
 
 
}//delete(P3);

fclose(file);
 Init = clock() - Init;
    double I2 = Init;
	
    std::cout << (Init) << " Clock Cycles" << std::endl;
    std::cout << (I2 / 1000) << " Seconds" << std::endl;
    std::cout << (size * 127/ (I2 / 1000)) << " Avg KiloBytes Per second" << std::endl;
    std::cout << ((uint64_t)(xl)) << "Fuzzy Matches" << std::endl;
    //std::cout << (Matches) << "Fuzzy Matches" << std::endl;
	std::cin >>I2;

    //s.clear();
    //s.seekg(0, s.end);
//}
    //delete[] P3;

    /*if (Init == 0)
    {
        Init = 1;
    }*/
 
    
    //s.clear();
    //s.seekg(0, s.end);

  




    //unsigned long v; //Start at index 1 to avoid the dummy 0th index dump pos and t avodi seekg from reahcing. gping out of boudns with the file

    //   //cant currenttee alignment to 16/32 due to char buffer sizes not always aligning!



    __m256i vtest;
    __m256i vtestR;

    //__m256i vXorMaskA;
    //__m256i vXorMaskB;


    int Abs2 = 0;
    int Abs3 = 0;
    bool Ext = 0;
    bool Ext1 = 0;
   
    //Very lazy  loop to filter the reminader of the losse fuzzy matches from the first pass: 
    //is highly inefficnet and is drastcially less performant due to the constant adjustment of 
    //the File read offset through seekg which adds additional copy latency 

    static uint8_t P4[VEC_LEN];  static uint8_t P5[VEC_LEN];// int k2 = 0;// sizeof(c) - 2;
    // for (uint64_t v = 1; v <= Matches; v++)
    // {

       // fseek(file, OffsetCache[v], SEEK_SET);
       // fread(P4, 1, sizeof(subA) - 1, file);
       // fseek(file, OffsetCache[v] - 1, SEEK_SET);
       // fread(P5, 1, sizeof(subA) - 1, file);

       // vtest = _mm256_lddqu_si256(X(P4));
       // vtestR = _mm256_lddqu_si256(X(P5));

       // //vXorMaskA = _mm256_xor_si256(vtest, _mm256_setzero_si256());
       // //vXorMaskB = _mm256_xor_si256(vtestR, _mm256_setzero_si256());

       // /*testc seems to have issues with carrying out AND and not setting the CF / Specific register flag to 1:
               // *This occurs if specific queries such as "RTX 3070" are used with the specific test File used 
               // *but not with other queries such as "barbershop", which do not seem to exhibit this particular issue*/

       // Abs2 += Ext = _mm256_testc_si256(sub, vtest);
       // Abs3 += Ext1 = _mm256_testc_si256(sub, vtestR);

    // }
   
  


}