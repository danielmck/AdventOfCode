#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int get_val(char let) {
    char lc_let;
    int u_case;
    if (let>='A' && let<='Z') u_case = 1;
    else if(let>='a' && let<='z') u_case = 0;
    else cout<<"ERROR";
    lc_let = tolower(let);
    
    return (int)lc_let - 97 + 26*u_case;
}

int both_pockets(fstream nfile) {
    string tp;
    int net_score = 0, line_len, let_val, count = 0;
    while(getline(nfile, tp)){
            std::vector<int> vector1(52, 0);
            line_len = tp.length();
            count+=1;
            for (int i = 0; i < line_len; i++) {
                let_val = get_val(tp[i]);
                if (i < line_len/2) {
                    vector1[let_val] = 1;
                }
                else {
                    net_score += (let_val+1)*vector1[let_val];
                    vector1[let_val] = 0;
                }
            }
            // std::cout << net_score << std::endl;
    }
    return(net_score);
}

int group_badge(fstream nfile) {
    string tp;
    int net_score = 0, line_len, let_val, count = 0, rem;
    while(getline(nfile, tp)){
            std::vector<int> vector1(52, 0);
            line_len = tp.length();
            count+=1;
            rem = count%3;
            for (int i = 0; i < line_len; i++) {
                let_val = get_val(tp[i]);
                if (rem > 0) {
                    vector1[let_val] = min(vector1[let_val]+1,rem);
                }
                else {
                    if (vector1[let_val] == 2) {
                        net_score += (let_val+1);
                        vector1[let_val] = 0;
                    } 
                }
            }
            // std::cout << net_score << std::endl;
    }
    return(net_score);
}

int main() {

    fstream newfile;
    newfile.open("day3_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    int final_score;
    if(newfile.is_open()) {
        string tp;
        int net_score = 0, line_len, let_val, count = 0, rem;
        std::vector<int> vector1(52, 0);
        while(getline(newfile, tp)){
                line_len = tp.length();
                count+=1;
                rem = count%3;
                if (rem == 1) {
                    for (int j = 0; j < 52; j++) {
                        vector1[j] = 0;
                    }
                }
                for (int i = 0; i < line_len; i++) {
                    let_val = get_val(tp[i]);
                    if (rem > 0) {
                        if (vector1[let_val] < rem) vector1[let_val]+=rem;
                    }
                    else {
                        if (vector1[let_val] == 3) {
                            // std::cout << tp[i] << " " << count << std::endl;
                            net_score += (let_val+1);
                            vector1[let_val] = 0;
                        } 
                    }
                }
                // std::cout << net_score << std::endl;
        }
        std::cout << net_score << std::endl;
    }
    // std::cout << get_val('a') << " " << get_val('z') << " " << get_val('A') << " " << get_val('Z') << std::endl;
    // std::cout << count << std::endl;
    
}