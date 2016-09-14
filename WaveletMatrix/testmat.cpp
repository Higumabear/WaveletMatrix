#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <string>
#include <algorithm>
#include "wavelet_matrix.h"

int main(int argc, char **argv){
  string s("Lorem ipsum dolor sit amet, pri ut probatus reprimique definitiones, ceteros insolens mediocrem quo et, ea quo ridens atomorum sententiae. Feugiat vulputate ius id, adhuc reque epicurei ei mel. Ne his dicta sententiae scripserit. His in amet ullum, vivendo accusamus mel an.Soluta graecis eu sed! Has aperiri feugiat cu, ei ius soleat sapientem, ea dolores convenire qui? At quo posse vulputate assueverit. Probo porro comprehensam at sed, id nam impedit accusamus, eu est legere vivendum? Ferri pertinax mandamus eu ius, utamur detraxit constituam te sed!Cu adipisci dissentias usu, te sea veri reprimique. Ut essent vivendo fastidii per, sit quem harum suscipit et. Ea nam sint summo liber. Sit falli perpetua theophrastus ex!Vivendo offendit eu cum, usu quodsi vivendo sapientem et, possim phaedrum singulis sea ut. Qui mollis aliquando percipitur in, ad aeterno aliquid usu, eos ut epicuri volutpat. Eam ad munere dictas impedit, exerci nostrud consetetur et nam. Vis no quidam percipit inciderint, in pri veniam graeco insolens.Per ipsum appellantur ut, pri fugit utinam necessitatibus at. Ex nullam ridens duo, id ius movet clita adolescens. Vis ut ludus partem voluptaria! Oratio soluta fuisset vis an?Vix eu facer iudico singulis! Ne eum amet duis. Ex odio elit percipitur vix, eros mollis dissentias vix an. Ex per nullam referrentur, quo ex inciderint concludaturque. Zril nostrum consectetuer nam te, forensibus reformidans sed et, ut vis dolor vitae dissentiet. Ex nec feugait oporteat eloquentiam, ei cum elitr officiis vulputate.Mollis quaestio dissentiunt sea in? Ut vidit illud est, pri ad aliquip omnesque theophrastus, harum adipiscing contentiones mei ad? Primis commodo veritus ea sea, mea cu habeo causae laboramus! Nam ei vidit invidunt pericula? Est te malis persius rationibus. Ne pro veri referrentur, nam in explicari abhorreant, ludus lobortis liberavisse pri ne.No nec unum meis euismod, ut modus feugiat pro! Melius legimus probatus mea ei, ut consul mollis eos. Libris timeam iisque vis no, ei utinam omnesque corrumpit quo? Qui an graecis conclusionemque. Duo omnes ridens platonem et? Prima scaevola vix ea, illum placerat ponderum eos et!Cu nam augue dicta vitae! Cu qui fierent referrentur, omnium civibus corrumpit ad has. Sit no utamur impedit voluptua! Ne cum option patrioque accommodare? Et mel partem theophrastus!Labore theophrastus mei id, torquatos mnesarchum id duo. Illum aliquam intellegam eum no. Eu eligendi expetenda elaboraret pro, mea an solet malorum comprehensam? Impetus legimus apeirian per ea, probo scribentur mel cu?");
  kuma::WaveletMatrix wm(s);
  wm.build();

#ifdef ACCESS  
  int c;
  srand((unsigned)time(NULL));
  for(int k = 0; k < 1000000000; k++){
    int idx = rand() % s.length();
    char ret = wm.access(idx);
    if(ret != s[idx]){
      cout << "������(�L�E�ցE�M) " << idx << " " 
	   << s[idx]<< " " << (char)ret << endl;
    }
    if(k % 1000000 == 0){
      srand((unsigned)time(NULL));
      cout << k << " cases done.(�L�E�ցE�M)" << endl;
    }
  }
#endif

#define RANK
#ifdef RANK
  std::set<char> alp(s.begin(), s.end());
  for(auto u : alp){
    cout << u << " is being tested....";
    if(count(s.begin(), s.end(), u) != wm.rank(s.length(), u)){
      cout << "wrong";
    }
    cout << endl;
  }
#endif
}
