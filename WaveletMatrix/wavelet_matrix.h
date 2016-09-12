#include "sbv/succinct.h"
#include <string.h>
#include <stdint.h>

namespace kuma {

  const int BIT_SIZE = 0x8;

  class WaveletMatrix{
  public:
    WaveletMatrix();
    WaveletMatrix(string s);

    uint32_t rank(const uint32_t idx, uint8_t c);
    uint32_t select(const uint32_t b, uint8_t c);
    uint32_t getSize(){ return length; }
    void build();

  private:
    SuccinctBitVector **sbv;
    int length;
    string text;
  };
}
