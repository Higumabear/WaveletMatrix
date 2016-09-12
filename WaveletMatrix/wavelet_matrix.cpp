#include <iostream>
#include "wavelet_matrix.h"

namespace kuma {

  inline uint8_t* str2uint8_t(uint8_t* dest, const std::string& src, size_t num) {
    memcpy(dest, src.c_str(), sizeof(uint8_t) * num);
    return dest;
  }

  WaveletMatrix::WaveletMatrix(){}

  WaveletMatrix::WaveletMatrix(string s) : text(s) {
    length = text.length();

    sbv = new SuccinctBitVector*[BIT_SIZE];
    for(int i = 0; i < BIT_SIZE; i++)
    sbv[i] = new SuccinctBitVector(length, 0);
  }

  void WaveletMatrix::build(){
    uint8_t *cur = new uint8_t[length];
    uint8_t *next = new uint8_t[length];
    str2uint8_t(cur, text, length);

    for(int i = BIT_SIZE - 1; i >= 0; i--){//construct bit vectors
      for(int l = 0; l < length; l++){
        if(cur[l] >> i & 1)
	  sbv[i]->setBit(l, 1);
      }
      cout << cur << endl;
      uint32_t pos0 = 0;

      /*ここ直せ*/
      uint32_t pos1 = length - sbv[i]->rank(length, 1);
      cout << "rank : " << pos1 << endl;
      for(int l = 0; l < length; l++){//radix sort
        if(cur[l] >> i & 1) next[pos1++] = cur[l];
	else next[pos0++] = cur[l];
      }
      cout << "pos0 : " << pos0 << "  pos1 : " << pos1 << endl;
      swap(cur, next);
    }

    delete [] cur;
    delete [] next;
  }

  uint32_t WaveletMatrix::access(const uint32_t idx){
    uint32_t k = idx;
    uint32_t ans = 0;
    for(int i = BIT_SIZE - 1; i >= 0; i--){
<<<<<<< HEAD
      cout << i << " " << k << " ";
      if(sbv[i]->getBit(k)){
	cout << "1だ" << endl;
	ans |= 1 << i;
	k = sbv[i]->rank(k, 1) + sbv[i]->rank(length, 1);
      }else{
	cout << "0だ" << endl;
=======
      if(sbv[i]->getBit(k)){
	ans |= 1 << i;
	k = sbv[i]->rank(k, 1) + length - sbv[i]->rank(length, 1);/*ここ直せ*/
      }else{
>>>>>>> 4588db699992e08b12d8010826253239b34b4593
	k = length - sbv[i]->rank(k, 1); /*ここも直せ*/
      }
    }
    return ans;
  }
}
