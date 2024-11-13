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
    int begin, final, sum =0;
    std::regex r("\[0-9]|(one)|(two)|(three)|four|five|six|seven|eight|nine");
    std::smatch a;
    std::map<std::string, int> nums = {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 }
};
    // std::cout << "hello" << std::endl;
    while(getline(newfile, tp)){
        begin = -1;
        while (tp.length()>0) {
            regex_search(tp, a, r);
            // std::cout << tp <<  " " << a.position() << std::endl;
            if (a.position() < tp.length()) {
                // std::cout << a.str << a.len
                if (a.length()==1) {
                    final = std::stoi(tp.substr(a.position(),1));
                    // std::cout << a.str() << std::endl;
                }
                else{
                    std::cout << a.str() << std::endl;
                    final = nums[a.str()];
                    // std::cout << final << std::endl;
                }
                tp = tp.substr(a.position()+1);
                if (begin<0)
                {
                    begin = final;
                }
                // std::cout << a.position() << " " << final << std::endl;  
            }
            else {
                tp = "";
            }
        }
        // std::cout << begin << final <<std::endl;
        sum = sum + 10*begin+final;
    }
    std::cout << sum << std::endl;
}