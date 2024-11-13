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
    std::string tp, turn;
    int ind, val, sum =0, rnum = 12, bnum=14, gnum=13;
    std::regex rn("\[0-9]+");
    std::regex rt("\[a-z]+");
    std::smatch a, an, at;
    std::map<std::string, int> nums = {
    { "red", 0 },
    { "green", 0 },
    { "blue", 0 },
};
    // std::cout << "hello" << std::endl;
    while(getline(newfile, tp)){
        regex_search(tp, a, rn);
        ind = std::stoi(a.str());
        tp = tp.substr(a.position()+a.length()+1);
        while (tp.length()>0) {
            // std::cout << tp <<  " " << a.position() << std::endl;
            regex_search(tp, an, rn);
            regex_search(tp, at, rt);
            val = std::stoi(an.str());
            nums[at.str()] = std::max(val,nums[at.str()]);
            if (at.position()+at.length() < tp.length()-1) {
                tp = tp.substr(at.position()+at.length()+1);
            }
            else {
                tp = "";
            }
        }
        std::cout << nums["green"] << " " << nums["blue"] << " " << nums["red"] << std::endl;
        // if ((nums["green"]<=gnum) & (nums["blue"]<=bnum) & (nums["red"]<=rnum)) {
        //     sum = sum + ind;
        // }
        sum = sum + nums["green"]*nums["blue"]*nums["red"];
        nums["green"]=0;
        nums["blue"]=0;
        nums["red"]=0;
    }
    std::cout << sum << std::endl;
}