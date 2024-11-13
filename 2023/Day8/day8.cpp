#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <tuple>
#include <functional>
#include <regex>
#include <iomanip>

// using namespace std;

int main() {
    std::fstream newfile, file2;
    std::string fname = "test.txt";
    newfile.open(fname,std::ios::in); // open a file to perform write operation using file object
    std::string dirs, line1, line2, curr = "AAA", two_ways;
    std::vector<std::string> paths, all_curr;
    int line_ind = 0, count_ind = 0, inst_len, way, all_len;
    double score;
    std::map<std::string, int> ways = {{ "L", 0},{"R", 1}}, lines = {};
    bool all_z = false;


    getline(newfile, dirs);
    inst_len = dirs.length();
    getline(newfile, line1);
    while (getline(newfile, line1)) {
        paths.push_back(line1.substr(7,3)+line1.substr(12,3));
        lines[line1.substr(0,3)] = line_ind;
        if (line1.substr(2,1)=="A") {all_curr.push_back(line1.substr(0,3));}
        line_ind++;
    }
    all_len=all_curr.size();
    // while (curr != "ZZZ") {
    while (!all_z) {
        all_z = true;
        for (int i=0; i< all_len; i++){
            way = ways[dirs.substr(count_ind%inst_len,1)];
            two_ways = paths[lines[all_curr[i]]];
            all_curr[i] = two_ways.substr(3*way,3);
            if (all_curr[i].substr(2,1)!="Z") {all_z=false;}
            else {std::cout << all_curr[i] << " " <<  count_ind << std::endl;}
        }
        count_ind++;
    }
    std::cout << count_ind << std::endl;
}