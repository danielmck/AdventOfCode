#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

int main() {
    fstream newfile;
    newfile.open("day5_input.txt",ios::in); // open a file to perform write operation using file object
    string tp,gain_str,lose_str;
    int setup = 1, line_len, counter, pile_ind, pile_len=0, move_num, move_st, move_end;
    vector<int> pile_lens;
    vector<string> piles;
    // char* piles = NULL;
    if(newfile.is_open()) {
        while(getline(newfile, tp)){
            line_len = tp.length();
            if (setup) {
                if (tp.at(1)=='1') setup=0;
                else {
                    counter = 1;
                    while (counter<line_len) {
                        pile_ind = (counter+3)/4;
                        if (pile_ind>pile_len) {
                            // strcat(piles, " ");
                            piles.push_back("");
                            pile_lens.push_back(0);
                            pile_len += 1;
                        }
                        if (tp.at(counter)!=' ') piles[pile_ind-1] += (tp.at(counter));
                        counter+=4;
                    }
                }
                
            }
            else {
                if (line_len>0) {
                    tp.erase(0, tp.find(" ") + 1);
                    // std::cout << tp.substr(0, tp.find(" ")) << std::endl;
                    move_num = stoi(tp.substr(0, tp.find(" ")));
                    tp.erase(0, tp.find(" ") + 1);
                    tp.erase(0, tp.find(" ") + 1);
                    // std::cout << tp.substr(0, tp.find(" ")) << std::endl;
                    move_st = stoi(tp.substr(0, tp.find(" ")));
                    tp.erase(0, tp.find(" ") + 1);
                    tp.erase(0, tp.find(" ") + 1);
                    // std::cout << tp << std::endl;
                    move_end = stoi(tp);

                    gain_str = piles[move_end-1];
                    lose_str = piles[move_st-1];
                    // for (int i=0; i<move_num; i++) {
                    gain_str = lose_str.substr(0,move_num)+gain_str;
                    lose_str.erase(0,move_num);
                    // }
                    piles[move_st-1] = lose_str;
                    piles[move_end-1] = gain_str;
                }
            }
        }
        for (int i=0; i<pile_len; i++) {
            string test = piles[i];
            std::cout << test.substr(0,1);
        }
        std::cout << std::endl;
    }
}