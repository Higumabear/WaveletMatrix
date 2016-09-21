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

    uint32_t access	( uint32_t idx) const;
    uint32_t rankRange	( uint8_t c, uint32_t l,  uint32_t r) const;
    uint32_t rank	( uint8_t c, uint32_t idx) const;
    uint32_t select	( uint8_t c, uint32_t b) const;
    uint32_t quantile	( uint32_t l,  uint32_t r, uint8_t c) const;
    uint32_t topk	( uint32_t l,  uint32_t r, uint8_t k) const;
    uint32_t rangefreq	( uint32_t l,  uint32_t r,  uint32_t x,  uint32_t y) const;
    uint32_t rangelist	( uint32_t l,  uint32_t r,  uint32_t x,  uint32_t y) const;
    uint32_t getSize	() const { return length; }
    uint32_t rangemaxk	( uint32_t l,  uint32_t r, uint8_t k) const;
    uint32_t rangemink	( uint32_t l,  uint32_t r, uint8_t k) const;
    uint32_t prevvalue	( uint32_t l,  uint32_t r,  uint32_t x,  uint32_t y) const;
    uint32_t nextvalue	( uint32_t l,  uint32_t r,  uint32_t x,  uint32_t y) const;  
    uint32_t intersect	( uint32_t l,  uint32_t r,  uint32_t u,  uint32_t v) const;
    void build();

  private:
    vector<SuccinctBitVector> sbv;
    int length;
    string text;
  };
}
