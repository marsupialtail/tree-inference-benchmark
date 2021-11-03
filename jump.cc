#include <x86intrin.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <cnpy.h>
#include <cstdint>
#include <cstring>
#include <math.h>

#define NUM_TREES 1000
#define NUM_FEATS 200
#define LOOP 300
const int lengths[NUM_TREES] = {129,131,134,126,130,128,124,125,132,128,128,132,132,127,127,134,130,132,126,121,139,123,127,124,118,124,134,126,123,136,124,120,126,125,132,125,124,129,121,130,127,120,122,129,130,131,129,130,131,131,123,132,122,131,123,131,132,130,127,130,120,132,128,129,127,126,130,140,130,124,137,124,124,118,122,124,128,136,128,125,134,118,121,126,123,135,133,123,128,121,124,126,130,125,128,126,128,125,125,124,125,135,123,127,130,136,131,124,123,129,133,132,132,132,123,129,133,130,126,129,125,130,129,124,117,129,122,126,132,123,129,126,135,130,126,121,130,125,130,128,135,129,129,128,125,135,128,133,122,128,126,128,131,133,131,122,126,123,127,129,129,128,126,133,123,129,136,130,124,135,131,124,134,124,129,129,131,121,130,127,127,130,132,127,127,136,126,125,128,126,130,131,124,130,136,125,135,137,128,124,126,129,128,123,126,124,133,123,123,132,133,127,125,123,121,142,133,130,129,130,121,130,127,125,128,131,132,128,126,125,128,138,126,122,130,128,131,124,130,134,123,129,128,129,134,126,128,134,130,134,129,134,123,132,135,130,126,128,131,130,134,127,133,133,126,139,131,137,130,132,131,134,129,139,132,126,138,139,131,135,128,128,129,135,129,136,129,138,134,128,125,130,125,125,135,135,124,136,125,134,134,134,126,128,127,129,128,128,132,125,134,127,129,126,133,127,126,126,128,129,124,128,123,139,123,130,125,123,124,132,133,127,132,129,117,129,134,130,129,129,121,131,133,126,125,132,128,130,128,127,125,129,123,125,133,127,139,135,129,126,139,131,125,132,128,130,122,137,122,127,127,130,121,112,128,129,132,128,132,133,111,127,132,130,121,117,129,127,131,111,120,131,133,125,126,134,122,126,131,130,126,129,131,118,136,123,96,136,129,125,116,118,125,125,133,135,124,125,105,127,125,122,130,133,131,139,128,130,132,133,136,110,123,125,131,132,134,130,127,133,102,135,120,128,124,134,125,120,128,136,113,128,121,125,107,130,126,121,124,119,98,120,128,131,128,127,134,123,131,132,130,130,129,129,122,128,122,101,127,127,122,125,129,121,140,125,120,122,135,128,132,128,96,121,114,130,128,124,128,122,130,134,105,125,130,114,128,126,130,104,134,123,128,129,120,128,123,120,122,115,121,114,130,110,134,93,110,101,127,129,126,125,138,128,92,132,137,126,128,110,106,126,118,131,124,135,128,89,124,128,96,125,128,111,90,110,117,114,116,123,104,127,118,133,126,131,123,89,135,84,86,126,122,92,88,132,132,97,128,116,97,103,93,96,126,124,123,128,119,123,90,95,123,127,105,136,89,100,78,124,132,118,89,93,97,105,125,121,129,121,100,135,88,110,87,131,127,128,129,124,129,117,107,131,108,119,93,100,118,127,129,129,132,77,98,100,84,132,82,103,92,125,114,93,129,129,116,87,91,128,101,109,119,124,76,110,132,100,136,131,122,128,121,115,125,121,127,110,124,100,102,125,103,91,100,131,119,128,125,114,111,102,123,110,130,83,88,121,73,90,81,109,127,121,99,137,115,127,123,79,115,126,93,125,130,120,125,88,130,125,125,119,79,91,122,108,130,119,127,94,97,126,95,108,123,97,112,130,77,98,129,102,106,128,121,110,125,127,111,77,117,77,124,117,100,89,122,130,114,93,130,94,96,112,127,108,128,94,130,128,128,118,91,111,138,128,128,102,127,130,131,86,124,120,126,125,124,93,128,102,87,125,104,126,127,126,90,122,113,123,112,126,130,126,89,136,113,131,130,99,130,121,132,108,121,118,124,128,114,126,118,100,135,109,92,101,118,126,118,130,123,106,110,96,117,126,126,125,126,96,131,122,123,133,93,114,123,133,128,114,117,125,123,120,127,120,130,122,123,128,128,137,125,125,130,120,111,108,127,125,120,129,125,135,130,128,123,137,102,131,122,124,116,137,128,109,118,126,118,130,129,128,124,121,131,106,130,126,136,124,135,132,132,126,130,129,124,100,127,121,125,129,116,122,137,115,114,130,123,134,109,123,125,129,135,129,118,136,126,131,124,123,126,133,122,118,127,127,108,132,127,128,135,126,131,117,113,107,122,136,131,128,125,101,129,127,113,131,114,131,129,126,122,128,116,97,104,103,120,118,132,122,125,131,121,100,122,113,126,126,127,127,98,129,124,127,129,126,139,122,130,125,138,132,132,122,130,132,134,124,117,123,121,120,105,92,124,126,134,122};
const int starts[NUM_TREES] = {0,129,260,394,520,650,778,902,1027,1159,1287,1415,1547,1679,1806,1933,2067,2197,2329,2455,2576,2715,2838,2965,3089,3207,3331,3465,3591,3714,3850,3974,4094,4220,4345,4477,4602,4726,4855,4976,5106,5233,5353,5475,5604,5734,5865,5994,6124,6255,6386,6509,6641,6763,6894,7017,7148,7280,7410,7537,7667,7787,7919,8047,8176,8303,8429,8559,8699,8829,8953,9090,9214,9338,9456,9578,9702,9830,9966,10094,10219,10353,10471,10592,10718,10841,10976,11109,11232,11360,11481,11605,11731,11861,11986,12114,12240,12368,12493,12618,12742,12867,13002,13125,13252,13382,13518,13649,13773,13896,14025,14158,14290,14422,14554,14677,14806,14939,15069,15195,15324,15449,15579,15708,15832,15949,16078,16200,16326,16458,16581,16710,16836,16971,17101,17227,17348,17478,17603,17733,17861,17996,18125,18254,18382,18507,18642,18770,18903,19025,19153,19279,19407,19538,19671,19802,19924,20050,20173,20300,20429,20558,20686,20812,20945,21068,21197,21333,21463,21587,21722,21853,21977,22111,22235,22364,22493,22624,22745,22875,23002,23129,23259,23391,23518,23645,23781,23907,24032,24160,24286,24416,24547,24671,24801,24937,25062,25197,25334,25462,25586,25712,25841,25969,26092,26218,26342,26475,26598,26721,26853,26986,27113,27238,27361,27482,27624,27757,27887,28016,28146,28267,28397,28524,28649,28777,28908,29040,29168,29294,29419,29547,29685,29811,29933,30063,30191,30322,30446,30576,30710,30833,30962,31090,31219,31353,31479,31607,31741,31871,32005,32134,32268,32391,32523,32658,32788,32914,33042,33173,33303,33437,33564,33697,33830,33956,34095,34226,34363,34493,34625,34756,34890,35019,35158,35290,35416,35554,35693,35824,35959,36087,36215,36344,36479,36608,36744,36873,37011,37145,37273,37398,37528,37653,37778,37913,38048,38172,38308,38433,38567,38701,38835,38961,39089,39216,39345,39473,39601,39733,39858,39992,40119,40248,40374,40507,40634,40760,40886,41014,41143,41267,41395,41518,41657,41780,41910,42035,42158,42282,42414,42547,42674,42806,42935,43052,43181,43315,43445,43574,43703,43824,43955,44088,44214,44339,44471,44599,44729,44857,44984,45109,45238,45361,45486,45619,45746,45885,46020,46149,46275,46414,46545,46670,46802,46930,47060,47182,47319,47441,47568,47695,47825,47946,48058,48186,48315,48447,48575,48707,48840,48951,49078,49210,49340,49461,49578,49707,49834,49965,50076,50196,50327,50460,50585,50711,50845,50967,51093,51224,51354,51480,51609,51740,51858,51994,52117,52213,52349,52478,52603,52719,52837,52962,53087,53220,53355,53479,53604,53709,53836,53961,54083,54213,54346,54477,54616,54744,54874,55006,55139,55275,55385,55508,55633,55764,55896,56030,56160,56287,56420,56522,56657,56777,56905,57029,57163,57288,57408,57536,57672,57785,57913,58034,58159,58266,58396,58522,58643,58767,58886,58984,59104,59232,59363,59491,59618,59752,59875,60006,60138,60268,60398,60527,60656,60778,60906,61028,61129,61256,61383,61505,61630,61759,61880,62020,62145,62265,62387,62522,62650,62782,62910,63006,63127,63241,63371,63499,63623,63751,63873,64003,64137,64242,64367,64497,64611,64739,64865,64995,65099,65233,65356,65484,65613,65733,65861,65984,66104,66226,66341,66462,66576,66706,66816,66950,67043,67153,67254,67381,67510,67636,67761,67899,68027,68119,68251,68388,68514,68642,68752,68858,68984,69102,69233,69357,69492,69620,69709,69833,69961,70057,70182,70310,70421,70511,70621,70738,70852,70968,71091,71195,71322,71440,71573,71699,71830,71953,72042,72177,72261,72347,72473,72595,72687,72775,72907,73039,73136,73264,73380,73477,73580,73673,73769,73895,74019,74142,74270,74389,74512,74602,74697,74820,74947,75052,75188,75277,75377,75455,75579,75711,75829,75918,76011,76108,76213,76338,76459,76588,76709,76809,76944,77032,77142,77229,77360,77487,77615,77744,77868,77997,78114,78221,78352,78460,78579,78672,78772,78890,79017,79146,79275,79407,79484,79582,79682,79766,79898,79980,80083,80175,80300,80414,80507,80636,80765,80881,80968,81059,81187,81288,81397,81516,81640,81716,81826,81958,82058,82194,82325,82447,82575,82696,82811,82936,83057,83184,83294,83418,83518,83620,83745,83848,83939,84039,84170,84289,84417,84542,84656,84767,84869,84992,85102,85232,85315,85403,85524,85597,85687,85768,85877,86004,86125,86224,86361,86476,86603,86726,86805,86920,87046,87139,87264,87394,87514,87639,87727,87857,87982,88107,88226,88305,88396,88518,88626,88756,88875,89002,89096,89193,89319,89414,89522,89645,89742,89854,89984,90061,90159,90288,90390,90496,90624,90745,90855,90980,91107,91218,91295,91412,91489,91613,91730,91830,91919,92041,92171,92285,92378,92508,92602,92698,92810,92937,93045,93173,93267,93397,93525,93653,93771,93862,93973,94111,94239,94367,94469,94596,94726,94857,94943,95067,95187,95313,95438,95562,95655,95783,95885,95972,96097,96201,96327,96454,96580,96670,96792,96905,97028,97140,97266,97396,97522,97611,97747,97860,97991,98121,98220,98350,98471,98603,98711,98832,98950,99074,99202,99316,99442,99560,99660,99795,99904,99996,100097,100215,100341,100459,100589,100712,100818,100928,101024,101141,101267,101393,101518,101644,101740,101871,101993,102116,102249,102342,102456,102579,102712,102840,102954,103071,103196,103319,103439,103566,103686,103816,103938,104061,104189,104317,104454,104579,104704,104834,104954,105065,105173,105300,105425,105545,105674,105799,105934,106064,106192,106315,106452,106554,106685,106807,106931,107047,107184,107312,107421,107539,107665,107783,107913,108042,108170,108294,108415,108546,108652,108782,108908,109044,109168,109303,109435,109567,109693,109823,109952,110076,110176,110303,110424,110549,110678,110794,110916,111053,111168,111282,111412,111535,111669,111778,111901,112026,112155,112290,112419,112537,112673,112799,112930,113054,113177,113303,113436,113558,113676,113803,113930,114038,114170,114297,114425,114560,114686,114817,114934,115047,115154,115276,115412,115543,115671,115796,115897,116026,116153,116266,116397,116511,116642,116771,116897,117019,117147,117263,117360,117464,117567,117687,117805,117937,118059,118184,118315,118436,118536,118658,118771,118897,119023,119150,119277,119375,119504,119628,119755,119884,120010,120149,120271,120401,120526,120664,120796,120928,121050,121180,121312,121446,121570,121687,121810,121931,122051,122156,122248,122372,122498,122632};
int * arrange_data(const int * attributes , const float * thresholds, const float * leaves, const char * is_leaves, const int * length, int num_trees);
float optimized(const float * features, const float * data);

int main()
{
   using std::chrono::high_resolution_clock;
   using std::chrono::duration_cast;
   using std::chrono::duration;
   using std::chrono::milliseconds;

   float features[NUM_FEATS + 1] = {0};
   for(int i = 1; i < NUM_FEATS + 1; i ++)
   {
      features[i] = ((float) rand() / (RAND_MAX)) ;
      //std::cout << features[i] << ",";
   }
   std::cout << std::endl;
   cnpy::NpyArray arr = cnpy::npz_load("sample.npz","attributes");
   const int * attributes = arr.data<int>();
   cnpy::NpyArray arr1 = cnpy::npz_load("sample.npz", "thresholds");
   const float * thresholds = arr1.data<float>();
   cnpy::NpyArray arr2 = cnpy::npz_load("sample.npz", "is_leaves");
   const char * is_leaves = arr2.data<char>();
   cnpy::NpyArray arr3 = cnpy::npz_load("sample.npz", "leaves");
   const float * leaves = arr3.data<float>();

   int * data = arrange_data(attributes , thresholds, leaves, is_leaves, lengths, NUM_TREES) ;
    
   float results[NUM_TREES];
#pragma omp parallel for    
   for(int i = 0; i < NUM_TREES; i ++)
   {
	     results[i] = 0;
   }

   auto t1 = high_resolution_clock::now();
    
   float total = 0;
   for(int j = 0; j < LOOP; j ++){
   total = 0;

   #pragma omp parallel for    
      for(int i = 0; i < NUM_TREES; i ++)
      {
         // the first element of the features array will always be 0 
         results[i] = optimized(features + 1, (const float *) (data + 26 * starts[i]));
      }
      for(int i = 0; i < NUM_TREES; i ++)
      {
         total += results[i];
      }
      //total = 1 - 1 / ( 1 + expf(total));
   }
   auto t2 = high_resolution_clock::now();
   duration<double, std::micro> us_double = t2 - t1;
   printf (" == Load shared library == \n== at %.5f microseconds == \n ", us_double.count() /LOOP);
   std::cout << total << std::endl;

   //  for(int i = 0; i < NUM_TREES ; i ++)
   //  {
   //     std::cout << results[i] << " ";
   //  }

}
