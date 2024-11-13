#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

int calc_view(vector<vector<int> > & trees, int row, int col) {
    int height = trees[row][col], prod=1, width = trees[1].size(), depth = trees.size();
    for (int i=0; i<row; i++){
        if (trees[row-1-i][col] >= height) {
            prod *= (i+1);
            break;
        }
        if (i==row-1) prod *= (i+1);
    }
    for (int i=0; i<(depth-row-1); i++){
        if (trees[row+1+i][col] >= height) {
            prod *= (i+1);
            break;
        }
        if (i==depth-row-2) prod *= (i+1);
    }
    for (int i=0; i<col; i++){
        if (trees[row][col-1-i] >= height) {
            prod *= (i+1);
            break;
        }
        if (i==col-1) prod *= (i+1);
    }
    for (int i=0; i<width-col-1; i++){
        if (trees[row][col+1+i] >= height) {
            prod *= (i+1);
            break;
        }
        if (i==width-col-2) prod *= (i+1);
    }
    return(prod);
}

int main() {
    fstream newfile, file2;
    newfile.open("day8_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    int width = 0, height = 0;
    while(getline(newfile, tp)){
        height +=1;
        if (height == 1) width = tp.length();
    }
    vector<vector<int> > trees(height, vector<int>(width));
    vector<vector<int> > seen(height, vector<int>(width));
    int count = 0, largest, tree_h;
    file2.open("day8_input.txt",ios::in);
    while(getline(file2, tp)){
        largest=-1;
        for (int i=0; i<width; i++) {
            tree_h = stoi(tp.substr(i,1));
            trees[count][i] = tree_h;
            seen[count][i] = tree_h > largest;
            largest = max(largest,tree_h);
            
        }
        count += 1;
    }
    
    for (int j = 0; j<height; j++) {
        largest = -1;
        for (int k = 0; k<width; k++) {
            tree_h = trees[j][width-1-k];
            seen[j][width-1-k] = seen[j][width-1-k] || (tree_h > largest);
            largest = max(largest,tree_h);
        }
    }
    int largest_up, largest_down, tree_up, tree_down;
    for (int j = 0; j<width; j++) {
        largest_up = -1;
        largest_down = -1;
        for (int k = 0; k<height; k++) {
            tree_up = trees[k][j];
            seen[k][j] = seen[k][j] || (tree_up > largest_up);
            largest_up = max(largest_up,tree_up);

            tree_down = trees[height-1-k][j];
            seen[height-1-k][j] = seen[height-1-k][j] || (tree_down > largest_down);
            largest_down = max(largest_down,tree_down);
        }
    }
    int sum_curr = 0, max_view = 0;
    for (int j = 0; j<height; j++) {
        for (int k = 0; k<width; k++) {
            sum_curr += seen[k][j];
        }
    }
    for (int j = 1; j<height-1; j++) {
        for (int k = 1; k<width-1; k++) {
            max_view = max(max_view,calc_view(trees,j,k));
        }
    }
    std::cout << sum_curr << std::endl;
    std::cout << max_view << std::endl;
}