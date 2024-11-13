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
typedef tuple<function<int(int, int)>,int,int> op;

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y;}
int multiply(int x, int y) { return x * y; }
 
// Function that accepts an object of
// type std::function<> as a parameter
// as well
int invoke(int x, int y, function<int(int, int)> func)
{
    return func(x, y);
}

int main() {
    fstream newfile, file2;
    string fname = "test.txt";
    newfile.open(fname,ios::in); // open a file to perform write operation using file object
    string tp, turn;
    map<string, function<int(int, int)>>move_type;
    move_type["+"] = add;
    move_type["-"] = subtract;
    move_type["*"] = multiply;
    int num_t, count = 0, x=1, sum_total = 0, monk_num=0, turn_num=1000;
    
    vector<vector<int>> monk_item(0,vector<int>(0));
    vector<int> divisor(0),t_monkey(0), f_monkey(0), hold_list;
    vector<op> operations;
    regex r("\[0-9]+");
    smatch a3;

    while(getline(newfile, tp)){
        if (count == 0) monk_num +=1;
        if (count == 1) {
            vector<int> item_vec(0);
            string items = tp.substr(tp.find(":"));
            while (items.length()>0) {
                if (items.find(",") != string::npos) {
                    item_vec.push_back(stoi(items.substr(1,items.find(","))));
                    items = items.substr(items.find(",")+1);
                }
                else {
                    item_vec.push_back(stoi(items.substr(1)));
                    break;
                }
            }
        monk_item.push_back(item_vec);
        }
        else if (count == 2) {
            int a,b;
            string eq = tp.substr(tp.find("=")+2), oper;
            if (eq.substr(0,eq.find(" "))== "old") a=0;
            else a=stoi(eq.substr(0,eq.find(" ")));
            eq=eq.substr(eq.find(" ")+1);
            oper = eq.substr(0,eq.find(" "));
            eq=eq.substr(eq.find(" ")+1);
            if (eq=="old") b=0;
            else b=stoi(eq);
            operations.push_back(make_tuple(move_type[oper],a,b));
        }
        else if (count == 3) {
            
            
            regex_search(tp, a3, r);
            // string a1 = tp.substr(tp.find('\[0-9]'));
            divisor.push_back(stoi(tp.substr(a3.position())));
        }
        else if (count == 4) {
            regex_search(tp, a3, r);
            // string a1 = tp.substr(tp.find('\[0-9]'));
            t_monkey.push_back(stoi(tp.substr(a3.position())));
            // t_monkey.push_back(stoi(tp.substr(tp.find("\[0-9]"))));
        }
        else if (count == 5) {
            regex_search(tp, a3, r);
            // string a1 = tp.substr(tp.find('\[0-9]'));
            f_monkey.push_back(stoi(tp.substr(a3.position())));
            // f_monkey.push_back(stoi(tp.substr(tp.find("\[0-9]"))));
        }
        count += 1;
        count = count%7;
    }
    int item, in1, in2, mod_val=1;
    op curr_op;
    for (int j=0; j<monk_num; j++) mod_val*=divisor[j];
    vector<int> inspect_count(monk_num,0);
    for (int i=0; i<turn_num; i++) {
        for (int j=0; j<monk_num; j++) {
            hold_list = monk_item[j];
            while (hold_list.size() > 0) {
                item = hold_list[hold_list.size()-1];
                hold_list.pop_back();
                monk_item[j].pop_back();

                curr_op = operations[j];
                if (get<1>(curr_op) == 0) in1=item;
                else in1 = get<1>(curr_op);
                if (get<2>(curr_op) == 0) in2=item;
                else in2 = get<2>(curr_op);
                item = get<0>(curr_op)(in1,in2);
                // item/=3;
                item %=mod_val;
                if (item%divisor[j] == 0) monk_item[t_monkey[j]].push_back(item);
                else monk_item[f_monkey[j]].push_back(item);
                inspect_count[j]+=1;
            }
        }   
    }
    for (int i=0; i<monk_num; i++) std::cout << i << " " << inspect_count[i] << std::endl;
}