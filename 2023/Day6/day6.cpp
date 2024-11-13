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
    std::string line1, line2;
    int ind, prod =1;
    double score, min, time=0, dist=0;
    std::regex rn("\[0-9]+");
    std::smatch an;
    getline(newfile, line1);
    getline(newfile, line2);
    while (regex_search(line1, an, rn)) {
        time = time*std::pow(10,an.length()) + std::stod(an.str());
        line1=line1.substr(an.position()+an.length());
        regex_search(line2, an, rn);
        dist = dist*std::pow(10,an.length()) + std::stod(an.str());
        line2=line2.substr(an.position()+an.length());
        // if (dist < time - 1) {prod = prod*(dist-1);}
        // else {
        //     min = (time-std::sqrt(time*time-4*dist))/2;
        //     // std::cout << ceil(min) << std::endl;
        //     prod = prod*(time-1-2*floor(min));
        //     // std::cout << time-1-2*floor(min) << std::endl;
        }
        min = (time-std::sqrt(time*time-4*dist))/2;
        //     // std::cout << ceil(min) << std::endl;
        prod = prod*(time-1-2*floor(min));
        //     // std::cout << time-1-2*floor(min) << std::endl;
    // }
    std::cout << prod << std::endl;
}