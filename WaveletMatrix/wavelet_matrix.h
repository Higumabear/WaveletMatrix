#include "../sbv/succinct.h"
#include <string.h>
#include <vector>
#include <stdint.h>

namespace kuma {

  const int BIT_SIZE = 0x8;

  class WaveletMatrix{
  public:
    WaveletMatrix();
    WaveletMatrix(string s);
    ~WaveletMatrix(){}

    uint32_t access(const uint32_t idx);
    uint32_t rankRange(const uint32_t l, const uint32_t r, uint8_t c);
    uint32_t rank(const uint32_t idx, uint8_t c);
    uint32_t select(const uint32_t b, uint8_t c);
    uint32_t getSize(){ return length; }
    void build();

  private:
    vector<SuccinctBitVector> sbv;
    int length;
    string text;
  };
}
