#pragma once
#include "succinct.h"
#include <iostream>


// the number of bits in x
inline uint64_t popcount64(uint64_t x){
  x = ((x & 0xaaaaaaaaaaaaaaaaULL) >> 1)
  +  (x & 0x5555555555555555ULL);
  x = ((x & 0xccccccccccccccccULL) >> 2)
  +  (x & 0x3333333333333333ULL);
  x = ((x & 0xf0f0f0f0f0f0f0f0ULL) >> 4)
  +  (x & 0x0f0f0f0f0f0f0f0fULL);
  x = ((x & 0xff00ff00ff00ff00ULL) >> 8)
  +  (x & 0x00ff00ff00ff00ffULL);
  x = ((x & 0xffff0000ffff0000ULL) >> 16)
  +  (x & 0x0000ffff0000ffffULL);
  x = ((x & 0xffffffff00000000ULL) >> 32)
  +  (x & 0x00000000ffffffffULL);
  return x;
}

// b-th (1-indexed) bit position in x (NOTICE : NOT b+1 th)
inline uint64_t select64(uint64_t x, uint32_t b, uint32_t bit){
  if (!bit) { x = ~x; }
  uint64_t x1 = ((x  & 0xaaaaaaaaaaaaaaaaULL) >>  1)
  +  (x  & 0x5555555555555555ULL);
  uint64_t x2 = ((x1 & 0xccccccccccccccccULL) >>  2)
  +  (x1 & 0x3333333333333333ULL);
  uint64_t x3 = ((x2 & 0xf0f0f0f0f0f0f0f0ULL) >>  4)
  +  (x2 & 0x0f0f0f0f0f0f0f0fULL);
  uint64_t x4 = ((x3 & 0xff00ff00ff00ff00ULL) >>  8)
  +  (x3 & 0x00ff00ff00ff00ffULL);
  uint64_t x5 = ((x4 & 0xffff0000ffff0000ULL) >> 16)
  +  (x4 & 0x0000ffff0000ffffULL);

  //b++;
  uint64_t pos = 0;
  uint64_t v5 = x5 & 0xffffffffULL;
  if (b > v5) { b -= v5; pos += 32; }
  uint64_t v4 = (x4 >> pos) & 0x0000ffffULL;
  if (b > v4) { b -= v4; pos += 16; }
  uint64_t v3 = (x3 >> pos) & 0x000000ffULL;
  if (b > v3) { b -= v3; pos +=  8; }
  uint64_t v2 = (x2 >> pos) & 0x0000000fULL;
  if (b > v2) { b -= v2; pos +=  4; }
  uint64_t v1 = (x1 >> pos) & 0x00000003ULL;
  if (b > v1) { b -= v1; pos +=  2; }
  uint64_t v0 = (x  >> pos) & 0x00000001ULL;
  if (b > v0) { b -= v0; pos +=  1; }
  return pos;
}


SuccinctBitVector::SuccinctBitVector(){

}

SuccinctBitVector::SuccinctBitVector(uint32_t n, bool bit) : length(n) {
  vectorSize      = (length + (ONE_BLOCK_SIZE - 1)) / ONE_BLOCK_SIZE;
  smallBlockSize = (length + (SMALL_BLOCK_SIZE - 1)) / SMALL_BLOCK_SIZE;
  largeBlockSize = (length + (LARGE_BLOCK_SIZE - 1)) / LARGE_BLOCK_SIZE;
  v.assign(vectorSize, bit ? 0xffffffffffffffffULL : 0);
}

//[0,idx)までのbit数
uint64_t SuccinctBitVector::rank(uint32_t idx, const bool bit) const {
  //if(idx > getSize()) { throw "SuccinctBitVector::rank()"; }
  
#ifdef NAIVE
  uint64_t r = 0;
  for(int i = 0; i < idx; i++){
    uint32_t wordPos = i / ONE_BLOCK_SIZE;
    uint32_t pos = (uint32_t)i % ONE_BLOCK_SIZE;
    if(this.v[wordPos] >> pos & 1) r++;
  }
  return r;
  #else
  if(idx <= 0LL) return 0LL;
  uint64_t pos = idx - 1;
  uint64_t lblock = (pos < LARGE_BLOCK_SIZE) ? 0 : largeBlock_tab[pos / LARGE_BLOCK_SIZE - 1];
  uint64_t sblock = (pos % LARGE_BLOCK_SIZE < SMALL_BLOCK_SIZE) ?
  0 : smallBlock_tab[pos / SMALL_BLOCK_SIZE - 1];
  uint64_t remain = popcount64(v[pos / ONE_BLOCK_SIZE] << (ONE_BLOCK_SIZE - idx % ONE_BLOCK_SIZE));

  return lblock + sblock + remain;
  #endif
}

//b+1回目のbitが発生する場所
uint64_t SuccinctBitVector::select(uint32_t b, bool bit) const {
  long long num = b + 1;// num can be negative.
  uint32_t ub = largeBlockSize - 1;
  uint32_t lb = 0;

  //LBの二分探索 O(log(N / LARGE_BLOCK_SIZE))
  if(ub != 0){
    while(lb < ub){
      uint32_t mid = (ub + lb) / 2;
      if(largeBlock_tab[mid] >= num) ub = mid;
      else lb = mid + 1;
    }
  }
  uint32_t Lindex = lb;

  num -= rank(Lindex * LARGE_BLOCK_SIZE, bit);
  uint32_t Sindex = Lindex * LARGE_BLOCK_SIZE / SMALL_BLOCK_SIZE;

  //#define DEBUG
  #ifdef DEBUG
  std::cout << "Lindex : " << Lindex
  << "  size : " << largeBlock_tab[Lindex]
  << " remain : " << num << endl;

  cout << "Small block index first : " << Sindex << endl;
  #endif

  //SBの線形探索 O(LARGE_BLOCK_SIZE / SMALL_BLOCK_SIZE) = O(1)
  while(1){
    #ifdef DEBUG
    cout << Sindex << " -> " << num - smallBlock_tab[Sindex] << endl;
    #endif
    if(num <= smallBlock_tab[Sindex]) break;
    Sindex++;
  }
  #ifdef DEBUG
  cout << "Small block index last : " << Sindex << endl;
  #endif
  num -= ((Sindex % (LARGE_BLOCK_SIZE / SMALL_BLOCK_SIZE) == 0) ? 0 : smallBlock_tab[Sindex - 1]);
  return Sindex * SMALL_BLOCK_SIZE + select64(v[Sindex], num, bit);
}

void SuccinctBitVector::setBit(uint32_t target, const bool bit){
  v[target / ONE_BLOCK_SIZE] |= 1LL << (target % ONE_BLOCK_SIZE);
}

bool SuccinctBitVector::getBit(const uint32_t target) const {
  return (v[target / ONE_BLOCK_SIZE] >> (target % ONE_BLOCK_SIZE)) & 1LL;
}

void SuccinctBitVector::build(){
  largeBlock_tab.assign(largeBlockSize, 0);
  smallBlock_tab.assign(smallBlockSize, 0);

  int smallbit = 0, largebit = 0;
  int block_ratio = LARGE_BLOCK_SIZE / SMALL_BLOCK_SIZE;
  for(int i = 0; i < vectorSize; i++){
    int blockbit = popcount64(v[i]);
    smallbit += blockbit;
    largebit += blockbit;
    smallBlock_tab[i] = smallbit;
    if((i + 1) % block_ratio == 0){
      largeBlock_tab[i / block_ratio] = largebit;
      smallbit = 0;
    }
  }
  //境界処理いらないのか。。。
  largeBlock_tab[largeBlockSize - 1] = largebit;
}
