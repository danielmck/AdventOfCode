#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    fstream newfile;
    newfile.open("day4_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    int final_score;
    if(newfile.is_open()) {
        string tp;
        int net_score = 0, line_len, let_val, count = 0, rem;
        size_t d_pos, c_pos;
        while(getline(newfile, tp)){
            d_pos = tp.find("-");
            int st1 = stoi(tp.substr(0, d_pos));
            tp.erase(0, d_pos + 1);

            d_pos = tp.find(",");
            int end1 = stoi(tp.substr(0, d_pos));
            tp.erase(0, d_pos + 1);

            d_pos = tp.find("-");
            int st2 = stoi(tp.substr(0, d_pos));
            tp.erase(0, d_pos + 1);

            int end2 = stoi(tp);
            int overlap = 0;
            // std::cout << st1 << " " << end1 << " " << st2 << " " << end2 <<  " " << 1-((st2>=st1) ^ (end2<=end1)) << std::endl;
            if (st1==st2) {
                net_score += 1;
            }
            else if (st1<st2) {
                // net_score += (end2<=end1);
                net_score += (st2<=end1);
            }
            else {
                // net_score += (end1<=end2);
                net_score += (st1<=end2);
            }
        }
        std::cout << net_score << std::endl;
    }
}