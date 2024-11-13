#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    fstream newfile;
    newfile.open("day1_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    int num_elf=1;
    int sum_curr=0, sum_max = 0, sum_max2 = 0, sum_max3 = 0, max_ind = 0;
    if(newfile.is_open()) {
        while(getline(newfile, tp)){  //read data from file object and put it into string.
            
            // std::cout << tp << std::endl;
            if(tp == "") {
                if (sum_curr>sum_max) {
                    sum_max2 = sum_max;
                    sum_max3 = sum_max2;
                    sum_max = sum_curr;
                    max_ind = num_elf;
                }
                else if (sum_curr > sum_max2){
                    sum_max3 = sum_max2;
                    sum_max2 = sum_curr;
                }
                else if (sum_curr > sum_max3){
                    sum_max3 = sum_curr;
                }
                num_elf+=1;
                sum_curr = 0;
            }
            else {
                sum_curr+= stoi(tp);
            }
        }
        std::cout << num_elf << std::endl;
        std::cout << sum_max << " " << sum_max2 << " " << sum_max3 << std::endl;
        std::cout << sum_max + sum_max2 + sum_max3 << std::endl;

    }
}