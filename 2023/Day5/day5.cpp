#include <iostream>
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
    std::string tp, line1;
    int ind, val, sum =0, nseed = 0, i=0;
    double score, dest, src, len;
    std::regex rn("\[0-9]+");
    std::smatch an;
    getline(newfile, tp);
    // std::cout << tp << std::endl;
    line1=tp;
    bool in_nums = false;
    while (regex_search(line1, an, rn)) {
        nseed++;
        line1=line1.substr(an.position()+an.length());
    }
    std::vector<double> seeds(nseed,0), after(nseed,0);
    // std::vector<int> flags(nseed,0);
    while (regex_search(tp, an, rn)) {
        if (i%2==0) {seeds[i] = std::stod(an.str());}
        else {seeds[i] = seeds[i-1]+std::stod(an.str());}
        tp=tp.substr(an.position()+an.length());
        i++;
    }
    after=seeds;
    while(getline(newfile, tp)){
        if (regex_search(tp, an, rn)) {
            in_nums = true;
            dest = std::stod(an.str());
            tp=tp.substr(an.position()+an.length());
            regex_search(tp, an, rn);
            src = std::stod(an.str());
            tp=tp.substr(an.position()+an.length());
            regex_search(tp, an, rn);
            len = std::stod(an.str());
            nseed = seeds.size();
            for (int j=0; j<nseed; j=j+2) {
                // if (flags[j] == 0){
                    if ((seeds[j] >= src) & (seeds[j+1] < src+len)) {
                        after[j] = dest + seeds[j] - src;
                        after[j+1] = dest + seeds[j+1] - src;
                        // flags[j] = 1;
                    } else if ((seeds[j] >= src) & (seeds[j] < src+len) & (seeds[j+1] >= src+len)) {
                        // std::cout << seeds[j] << " " << src << " " << seeds[j+1] << " " << src+len << std::endl;
                        seeds.push_back(src+len);
                        seeds.push_back(seeds[j+1]);
                        after.push_back(after[j+1] -seeds[j+1]+src+len);
                        after.push_back(after[j+1]);
                        seeds[j+1] = src+len-1;
                        after[j] = dest + seeds[j] - src;
                        after[j+1] = dest + seeds[j+1] - src;

                    }
                    else if ((seeds[j] < src) & (seeds[j+1] >= src) & (seeds[j+1] < src+len)) {
                        seeds.push_back(src);
                        seeds.push_back(seeds[j+1]);
                        after.push_back(dest);
                        after.push_back(dest + seeds[j+1]-src);

                        seeds[j+1] = src-1;
                        after[j+1] = after[j] + src-1-seeds[j];
                    }
                    else if ((seeds[j] < src) & (seeds[j+1] >= src+len)) {
                        seeds.push_back(src);
                        seeds.push_back(src+len-1);
                        after.push_back(dest);
                        after.push_back(dest + len-1);

                        seeds.push_back(src+len);
                        seeds.push_back(seeds[j+1]);
                        after.push_back(after[j+1]-seeds[j+1]+src+len);
                        after.push_back(after[j+1]);
                        
                        seeds[j+1] = src-1;
                        after[j+1] = after[j] + src-1-seeds[j];
                    }
                // }
            }
        }
        else {
            // if (in_nums) {std::fill(flags.begin(), flags.end(), 0);}
            if (in_nums) {seeds = after;}
            in_nums = false;
        }
    }
    nseed = seeds.size();
    score = after[0];
    for (int k=0; k<nseed; k++) {score = std::min(score,after[k]);}
    std::cout << std::setprecision(15) << score << std::endl;
}