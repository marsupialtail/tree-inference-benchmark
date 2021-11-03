#include <iostream>
#include <chrono>
#include <stdlib.h>
#define LOOP 1000
extern "C"
{
size_t get_num_feature(void);
float predict(union Entry* data, int pred_margin);
}

union Entry {
  int missing;
  float fvalue;
};

int main(void) {

  int rows = 1;
  /* number of features */
  const size_t num_feature = get_num_feature();
  std::cout << num_feature << std::endl;
  /* inst: dense vector storing feature values */
  union Entry* inst = (union Entry *) malloc(sizeof(union Entry) * num_feature * rows);
  float* out_pred = (float * )malloc(sizeof(float) * rows);

  /* clear inst with all missing */
  for (int i = 0; i < num_feature * rows; ++i) {
    inst[i].fvalue = ((float) rand() / (RAND_MAX)) ;
    std::cout << inst[i].fvalue << ",";
  }

  // out_pred[0] = predict(inst, 0);


   auto t1 = std::chrono::high_resolution_clock::now();
   for(int loop = 0; loop < LOOP; loop ++){
   for(int i = 0; i < rows; i ++)
   {
     out_pred[i] = predict(inst  + i * num_feature, 0);
   }}
   auto t2 = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::micro> us_double = t2 - t1;
   std::cout << predict(inst,0) << std::endl;

  printf (" == treelite inference at == \n== at %.5f microseconds == \n ", us_double.count()/ LOOP);
  return 0;
}
