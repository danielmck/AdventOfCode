#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <tuple>
#include <functional>
#include <regex>

using namespace std;

int main() {
    std::fstream newfile, file2;
    std::string fname = "test.txt";
    newfile.open(fname,std::ios::in); // open a file to perform write operation using file object
    std::string tp, win;
    int ind, val, sum =0, nwin = 0, score, nline=0, line_num=0;
    std::regex rn("\[0-9]+");
    std::regex rc("\[:]");
    std::regex rp("\[|]");
    std::smatch an, ac, ap;
    while(getline(newfile, tp)){
        nline++;
    }
    std::vector<int> card_num(nline,1);
    ind = 0;
    newfile.close();
    file2.open(fname,std::ios::in);

    while(getline(file2, tp)){
        regex_search(tp, ac, rc);
        tp = tp.substr(ac.position());
        regex_search(tp, ap, rp);
        win = tp.substr(0,ap.position()+1);
        while (regex_search(win, an, rn)) {
            nwin++;
            win = win.substr(an.position()+an.length());
        }
        std::vector<int> win_num(nwin);
        win = tp.substr(0,ap.position()+1);
        ind = 0;
        while (regex_search(win, an, rn)) {
            win_num[ind] = std::stoi(an.str());
            ind++;
            win = win.substr(an.position()+an.length());
        }
        tp = tp.substr(ap.position()+1);
        score=0;
        while (regex_search(tp, an, rn)) {
            val = std::stoi(an.str());
            for (int i=0; i<nwin; i++) {
                if (val == win_num[i]) {
                //     if (score==0) {score=1;}
                //     else {score = score*2;}
                    score = score+1;
                }
                
            }
            tp = tp.substr(an.position()+an.length());

        }
        // // sum = sum+score;
        for (int j=1;j<=score;j++) {card_num[line_num+j]=card_num[line_num+j]+card_num[line_num];}
        line_num++;
    }
    for (int k=0;k<nline;k++) {score = score+card_num[k];}
    std::cout << score << std::endl;
    file2.close();
}