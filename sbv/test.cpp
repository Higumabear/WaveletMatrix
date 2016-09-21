
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "succinct.h"

using namespace std;

int simpleselect(vector<bool> &v, int c, bool bit){
  int idx, cnt = 0;
  for(idx = 0; idx < v.size(); idx++){
    cnt += ((bit) ? v[idx] : !v[idx]);
    if(cnt == c + 1) break;
  }
  return idx;
}


int main(int argc, char **argv){
  if(argc != 2) return 0;
  int NUM = atoi(argv[1]);
  //NUM = 1000;

  /*
  SuccinctBitVector mysbv(1 << 20, 0);
  mysbv.build();

  cout << "NUM : " << NUM << endl;
  cout << "rank : " << mysbv.rank(NUM) << endl;
  for(int i = 0; i < NUM; i++)
  cout << "sele : " << i << " -> " << mysbv.select(i) << endl;
  */
  const int TEST = 1 << 20;

#define TEST1
#ifdef TEST2
  SuccinctBitVector sbv(TEST, 1);
  sbv.build();
  if(sbv.rank(1, 0) != 0) cout << "‚¦‚¦‚¦(LEƒÖEM)" << endl;
#endif
#ifdef TEST1
  int d = 10000;
  const bool bit = true;
  while(d--){
    if(d) cout << d << " cases remain." << endl;

    SuccinctBitVector sbv(TEST, 0);
    std::vector<bool> v(TEST, false);

    int ranktest;
    int selectlimit = 0;
    srand(d);
    for(int i = 0; i < TEST; i++){
      int r = rand();
      selectlimit += (r % 2 == 1);
      v[i] = (r % 2 == 1);
      if(r % 2 == 1) sbv.setBit(i, 1);
    }
    sbv.build();


    ranktest = TEST * 1.0 / RAND_MAX * rand();

    int selecttest = ranktest % selectlimit;

    int cnt = count(v.begin(), v.begin() + ranktest, bit);
    int sbvcnt = sbv.rank(ranktest, bit);
    int sel = simpleselect(v, selecttest, bit);
    int sbvsel = sbv.select(selecttest, bit);
    if(cnt != sbvcnt){
      cout << "cnt : " << cnt
      << "   sbvcnt : " << sbvcnt
      << "   rank test val : " << ranktest << endl;
    }
    if(sel != sbvsel){
      cout << "sel : " << sel
      << "   sbvsel : " << sbvsel
      << "   select test val : " << selecttest << endl;
    }
  }
#endif
}
