#include <iostream>
#include "wavelet_matrix.h"

int main(){
  kuma::WaveletMatrix wm("0123456789");

  cout << wm.getSize() << endl;
  wm.build();
}
