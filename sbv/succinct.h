#include <vector>
//#include <stdint.h>

using namespace std;

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned char uint8;

const uint32 LARGE_BLOCK_SIZE = 256;
const uint32 SMALL_BLOCK_SIZE = 64;
const uint32 ONE_BLOCK_SIZE = SMALL_BLOCK_SIZE;

class SuccinctBitVector{

public:
  SuccinctBitVector();
  SuccinctBitVector(uint32 n, uint32 bit = 0);

  uint64 rank(uint64 idx) const {return rank(idx, 1);}
  uint64 rank(uint64 idx, const uint32 bit) const;
  uint64 select(uint32 b, uint32 bit);
  uint64 get() const { return vectorSize; }
  void setBit(uint32 target, const uint32 bit);
  void build();

  vector<uint64> getv(){return v;}
  vector<int> getlb(){return largeBlock_tab;}
  vector<int> getsb(){return smallBlock_tab;}

private:

  std::vector<uint64> v;
  std::vector<int> largeBlock_tab, smallBlock_tab;
  uint32 length;
  uint32 vectorSize;
  uint32 largeBlockSize, smallBlockSize;
};
