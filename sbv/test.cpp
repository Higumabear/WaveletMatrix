#include <iostream>
#include <stdlib.h>
#include "succinct.h"

using namespace std;

//const int NUM = 100;

int main(int argc, char **argv){
  if(argc != 2) return 0;
  int NUM = atoi(argv[1]);
  //NUM = 1000;

/*
  SuccinctBitVector sbv(NUM);

  for(int j = 0; j < NUM; j++){
    if(j % 2 == 0) sbv.setBit(j, 1);
  }
  sbv.build();
  cout << "ans : " << NUM << " -> " << sbv.rank(NUM) << endl;
*/
  for(int s = 10000; s <= 200000000; s += 10000){
    SuccinctBitVector mysbv(s, 1);
    mysbv.build();
    if(s % 100000 == 0) cout << s << " ends." << endl;
    if(mysbv.rank(s) != s)
      cout << s << "->" << mysbv.rank(s) << endl;
  }
/*
  std::vector<int> v = sbv.getlb();
  std::vector<int> u = sbv.getsb();
  std::vector<uint64> t = sbv.getv();

  cout << "LB" << endl;
  for(int i = 0; i < v.size(); i++)
  cout << v[i] << " ";
  cout << endl << endl;

  cout << "SB" << endl;
  for(int i = 0; i < u.size(); i++)
  cout << u[i] << " ";
  cout << endl;
*/
}
