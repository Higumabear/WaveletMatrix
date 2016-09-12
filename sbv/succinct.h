#include <vector>
#include <stdint.h>

using namespace std;

const uint32_t LARGE_BLOCK_SIZE = 256;
const uint32_t SMALL_BLOCK_SIZE = 64;
const uint32_t ONE_BLOCK_SIZE = SMALL_BLOCK_SIZE;

class SuccinctBitVector{

public:
  SuccinctBitVector();
  SuccinctBitVector(uint32_t n, bool bit = false);

  uint64_t rank(uint32_t idx, const bool bit = true) const;
  uint64_t select(const uint32_t b, bool bit = true) const;
  uint64_t getSize() const { return vectorSize; }
  void setBit(const uint32_t target, const bool bit = true);
  bool getBit(const uint32_t target) const;
  void build();

  vector<uint64_t> getv(){return v;}
  vector<int> getlb(){return largeBlock_tab;}
  vector<int> getsb(){return smallBlock_tab;}

private:

  std::vector<uint64_t> v;
  std::vector<int> largeBlock_tab, smallBlock_tab;
  uint32_t length;
  uint32_t vectorSize;
  uint32_t largeBlockSize, smallBlockSize;
};
