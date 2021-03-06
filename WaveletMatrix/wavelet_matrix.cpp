#include <iostream>
#include "wavelet_matrix.h"

namespace kuma {

  inline uint8_t* str2uint8_t(uint8_t* dest, const std::string& src, size_t num) {
    memcpy(dest, src.c_str(), sizeof(uint8_t) * num);
    return dest;
  }

  WaveletMatrix::WaveletMatrix(){}

  WaveletMatrix::WaveletMatrix(string s) : text(s) {
    length = s.length();
    sbv.assign(BIT_SIZE, SuccinctBitVector(length, false));
  }

  void WaveletMatrix::build(){
    uint8_t *cur = new uint8_t[length];
    uint8_t *next = new uint8_t[length];
    str2uint8_t(cur, text, length);

    for(int i = BIT_SIZE - 1; i >= 0; i--){//construct bit vectors
      for(int l = 0; l < length; l++)
        if(cur[l] >> i & 1)
	  sbv[i].setBit(l, 1);

      sbv[i].build();

      uint32_t pos0 = 0;
      uint32_t pos1 = sbv[i].rank(length, 0);
      for(int l = 0; l < length; l++){//radix sort
        if(cur[l] >> i & 1) next[pos1++] = cur[l];
	else next[pos0++] = cur[l];
      }
      swap(cur, next);
    }

    delete [] cur;
    delete [] next;
  }

  uint32_t WaveletMatrix::access(uint32_t idx) const {
    uint32_t k = idx;
    uint32_t ans = 0;
    for(int i = BIT_SIZE - 1; i >= 0; i--){
      bool bit = sbv[i].getBit(k);
      k = sbv[i].rank(k, bit);
      if(bit){
	ans |= 1 << i;
	k += sbv[i].rank(length, 0);
      }
    }
    return ans;
  }
  // [s,e)
  uint32_t WaveletMatrix::rankRange(uint8_t c, uint32_t s, uint32_t e) const {
    uint32_t l = s, r = e;
    for(int i = BIT_SIZE - 1; i >= 0; i--){
      bool bit = c >> i & 1;
      l = sbv[i].rank(l, bit), r = sbv[i].rank(r, bit);
      if(bit) l += sbv[i].rank(length, 0), r += sbv[i].rank(length, 0);
    }
    return r - l;
  }

  uint32_t WaveletMatrix::rank(uint8_t c, uint32_t idx) const {
    return rankRange(c, 0, idx);
  }

  uint32_t WaveletMatrix::select(uint8_t c, uint32_t b) const {
    uint32_t pos = 0;
    for(uint8_t i = 0; i < BIT_SIZE; i++){
      bool bit = (c >> i) & 1;
      if(bit) pos = sbv[i].rank(pos, bit) + sbv[i].rank(length, 0);
      else    pos = sbv[i].rank(pos, bit);
    }
    pos += b;
    for(uint8_t i = BIT_SIZE - 1; i >= 0; i--){
      bool bit = (c >> i) & 1;
      if(bit) pos = sbv[i].select(pos - sbv[i].rank(length, 0), bit);
      else pos = sbv[i].select(pos, bit);
    }
    return pos;
  }
}
