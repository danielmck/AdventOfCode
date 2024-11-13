#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

int main() {
    fstream newfile;
    newfile.open("day6_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    int flag, line_len, counter = 3, text_len = 14;
    // char* piles = NULL;
    if(newfile.is_open()) {
        while(getline(newfile, tp)){
            line_len = tp.length();
            for (int i=text_len-1; i<line_len; i++) {
                flag=0;
                for (int j = 0; j<text_len-1; j++) {
                    for (int k = 1; k<text_len-j; k++) {
                        if (tp[i-j] == tp[i-j-k]) flag=1;
                    } 
                }
                if (flag == 0) {
                    std::cout << i+1 << std::endl;
                    break;
                }
            }
        }
    }
}