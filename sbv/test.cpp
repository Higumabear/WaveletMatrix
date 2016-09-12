
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "succinct.h"

using namespace std;

int simpleselect(vector<bool> &v, int c){
  int idx, cnt = 0;
  for(idx = 0; idx < v.size(); idx++){
    cnt += v[idx];
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

  int d = 10000;
  while(d--){
    if(d) cout << d << " cases remain." << endl;

    SuccinctBitVector sbv(TEST, 0);
    std::vector<bool> v(TEST, false);

    int ranktest;
    int selectlimit = 0;
    srand(ranktest);
    for(int i = 0; i < TEST; i++){
      int r = rand();
      selectlimit += (r % 2 == 1);
      v[i] = (r % 2 == 1);
      if(r % 2 == 1) sbv.setBit(i, 1);
    }
    sbv.build();


    ranktest = TEST / RAND_MAX * rand();

    int selecttest = ranktest % selectlimit;

    int cnt = count(v.begin(), v.begin() + ranktest, true);
    int sbvcnt = sbv.rank(ranktest);
    int sel = simpleselect(v, selecttest);
    int sbvsel = sbv.select(selecttest);
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
}
