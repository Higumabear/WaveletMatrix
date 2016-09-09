#include <iostream>
#include "wavelet_matrix.h"

int main(int argc, char **argv){
  string s("476532101417");
  kuma::WaveletMatrix wm(s);
  wm.build();

  int i;
  while(cin >> i) cout << wm.access(i) << endl;
}
