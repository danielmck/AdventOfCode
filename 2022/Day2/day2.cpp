#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int get_result(char move, char oppo) {
    map<char, int>move_type;
    move_type['A'] = 0;
    move_type['B'] = 1;
    move_type['C'] = 2;
    move_type['X'] = 0;
    move_type['Y'] = 1;
    move_type['Z'] = 2;

    int move_int, oppo_int, result, score;
    move_int = move_type[move];
    oppo_int = move_type[oppo];
    if (move_int == oppo_int) {
        result = 1;
    }
    else if ((move_int - oppo_int == -1) or (move_int - oppo_int == 2)) {
        result = 0;
    }
    else if ((move_int - oppo_int == 1) or (move_int - oppo_int == -2)) {
        result = 2;
    }
    score = result*3+move_int+1;
    return(score);
}

int get_move(char res, char oppo) {
    map<char, int>move_type;
    move_type['A'] = 0;
    move_type['B'] = 1;
    move_type['C'] = 2;
    move_type['X'] = 0;
    move_type['Y'] = 1;
    move_type['Z'] = 2;

    int move_int, oppo_int, result, score;
    result = move_type[res];
    oppo_int = move_type[oppo];
    if (result == 1) {
        move_int = oppo_int;
    }
    else {
        move_int = (oppo_int+result-1+3)%3;
    }
    // std::cout << move_int << " " << 5%3 << std::endl;
    score = result*3+move_int+1;
    return(score);
}

int main() {

    fstream newfile;
    newfile.open("day2_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    int net_score = 0;
    if(newfile.is_open()) {
        while(getline(newfile, tp)){
            net_score += get_move(tp[2],tp[0]);
        }
    }
    std::cout << get_move('X','A') << std::endl;
    std::cout << get_move('X','B') << std::endl;
    std::cout << get_move('X','C') << std::endl;
    std::cout << net_score << std::endl;
}