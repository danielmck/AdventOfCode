#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

std::tuple<int,int> get_move(string mv) {
    map<string, int>move_type;
    move_type["U"] = 2;
    move_type["R"] = 1;
    move_type["L"] = -1;
    move_type["D"] = -2;
    int mv_tp = move_type[mv.substr(0,1)];
    std::tuple<int,int> move = std::make_tuple(mv_tp,stoi(mv.substr(mv.find(" ")+1)));
    return(move);
}

std::tuple<int,int> t_move(int h_x, int h_y, int t_x, int t_y) {
    int x_diff = h_x-t_x, y_diff = h_y-t_y;
    tuple<int, int> new_t;
    if (abs(x_diff)>1) {
        new_t = std::make_tuple(t_x+(abs(x_diff)>1)*sgn(x_diff),t_y+(abs(y_diff)>0)*sgn(y_diff));
    }
    else if (abs(y_diff)>1) {
        new_t = std::make_tuple(t_x+(abs(x_diff)>0)*sgn(x_diff),t_y+(abs(y_diff)>1)*sgn(y_diff));
    }
    else {
        new_t = std::make_tuple(t_x,t_y);
    }
    return(new_t);
}

int main() {
    fstream newfile, file2;
    string fname = "day9_input.txt";
    newfile.open(fname,ios::in); // open a file to perform write operation using file object
    string tp;
    int minx = 0, miny=0, maxx=0, maxy = 0, countx=0, county=0, dir, len, rope_len=10;
    while(getline(newfile, tp)){
        tie(dir,len) = get_move(tp);
        if (abs(dir) == 2) {
            county += sgn(dir)*len;
            maxy = max(maxy,county);
            miny = min(miny,county);
        }
        else if (abs(dir) == 1) {
            countx += sgn(dir)*len;
            maxx = max(maxx,countx);
            minx = min(minx,countx);
        }
    }
    int xspan = maxx-minx, yspan = maxy-miny;
    std::tuple<int,int> t_pos = std::make_tuple(xspan+3-maxx,yspan+3-maxy), h_pos = std::make_tuple(xspan+3-maxx,yspan+3-maxy);
    vector<vector<int> > board(xspan+6, vector<int>(yspan+6));
    vector<int> x_pos(rope_len), y_pos(rope_len);
    for (int i=0; i<xspan+6; i++) {
        for (int j=0; j<yspan+6; j++) {
            board[i][j] = 0;
        }
    }
    for (int i=0; i<rope_len; i++) {
        x_pos[i] = xspan+3-maxx;
        y_pos[i] = yspan+3-maxy;
    }
    board[xspan+3-maxx][yspan+3-maxy] = 1;
    file2.open(fname,ios::in);

    while(getline(file2, tp)){
        tie(dir,len) = get_move(tp);
        for (int i=0; i<len; i++) {
            if (abs(dir)==2) y_pos[0] += sgn(dir);
            else x_pos[0] += sgn(dir);
            for (int k=1; k<rope_len; k++) {
                t_pos = t_move(x_pos[k-1],y_pos[k-1],x_pos[k],y_pos[k]);
                x_pos[k] = get<0>(t_pos);
                y_pos[k] = get<1>(t_pos);
            }
            std::cout << get<0>(t_pos) << " " << get<1>(t_pos) << std::endl;
            board[get<0>(t_pos)][get<1>(t_pos)] = 1;
        }  
    }
    int visit_count = 0; 
    for (int i=0; i<xspan+6; i++) {
        for (int j=0; j<yspan+6; j++) {
            visit_count += board[i][j];
        }
    }
    std::cout << visit_count << std::endl;
}