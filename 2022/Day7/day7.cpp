#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>

using namespace std;

void add_dir(map<string, int> & ds, map<string, string> & dc, string cwd, string newdir) {
    int flag = 0;
    for (auto it = ds.begin(); it != ds.end(); it++) {
        if (newdir == it->first) {
            flag=1;
            string past_child = dc[it->first];
            if (cwd != past_child.substr(0,past_child.find("-"))) std::cout << "Aaah" << std::endl;
        }
    }
    if (!flag) {
        ds[newdir] = 0;
        dc[newdir] = cwd+"-";
        dc[cwd] = dc[cwd]+' '+newdir;
    }  
}

void add_file(map<string, int> & ds, map<string, string> & dc, string cwd, int fs) {
    string dir_now = cwd, st_now;
    while (dir_now != "/") {
        ds[dir_now] += fs;
        st_now =  dc[dir_now];
        dir_now = st_now.substr(0,st_now.find("-"));
    }
    ds[dir_now] += fs;
}

int main() {
    fstream newfile;
    newfile.open("day7_input.txt",ios::in); // open a file to perform write operation using file object
    string tp;
    map<string, int>dir_size;
    map<string, string>dir_child;
    dir_size["/"] = 0;
    dir_child["/"] = "/-";
    string pwd = "/", next_dir, first_bit, child;
    int in_ls = 0, run_tot=0, size_lim=100000;
    while(getline(newfile, tp)){
        if (tp.substr(0,1) == "$") {
            in_ls = 0;
            if (tp.substr(2,2) == "cd") {
                next_dir = tp.substr(tp.find(" ",4)+1);
                if (next_dir == "..") {
                    child = dir_child[pwd];
                    pwd = child.substr(0,child.find("-"));
                }
                else if (next_dir == "/") pwd = "/";
                else {
                    add_dir(dir_size, dir_child, pwd, pwd+"/"+next_dir);
                    pwd = pwd+"/"+next_dir;
                }
            }
            else if (tp.substr(2,2) == "ls") {
                in_ls = 1;
            }
        }
        else {
            if (in_ls) {
                first_bit = tp.substr(0,tp.find(" "));
                if (first_bit == "dir") {
                    add_dir(dir_size, dir_child, pwd, pwd+"/"+tp.substr(tp.find(" ")+1));
                }
                else{
                    add_file(dir_size, dir_child, pwd, stoi(first_bit));
                }
            }
        }
        
    }
    for (auto it = dir_size.begin(); it != dir_size.end(); it++) {
        // std::cout << it->first << std::endl;
        if (it->second < size_lim) run_tot+=it->second;
    }
    std::cout << run_tot << std::endl;

    int max_space = 40000000, clear_up = dir_size["/"]-max_space, min_dict = dir_size["/"];
    for (auto it = dir_size.begin(); it != dir_size.end(); it++) {
        // std::cout << it->first << std::endl;
        if (it->second > clear_up) {
            if (it->second < min_dict) min_dict = it->second;
        }
    }
    std::cout << min_dict << std::endl;

}