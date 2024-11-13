#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

int main() {
    fstream newfile, file2;
    string fname = "day10_input.txt";
    newfile.open(fname,ios::in); // open a file to perform write operation using file object
    string tp, turn;
    map<string, int>move_type;
    int num_t, count = 0, x=1, sum_total = 0;
    move_type["noop"] = 1;
    move_type["addx"] = 2;
    vector<int> screen(240);
    while(getline(newfile, tp)){
        turn = tp.substr(0,tp.find(" "));
        num_t = move_type[turn];
        for (int  i=0;i<num_t;i++) {
            screen[count] = abs(count%40-x) < 2;
            count +=1;
            if (count%40 == 20) {
                // std::cout << count*x << std::endl;
                sum_total += count*x;
            }
        }
        if (turn == "addx") x+= stoi(tp.substr(tp.find(" ")+1));
    }
    for (int i=0; i<240;i++) {
        if (screen[i] == 0) std::cout << ".";
        if (screen[i] == 1) std::cout << "#";
        if (i%40==39) std::cout << std::endl;
    }
    
}