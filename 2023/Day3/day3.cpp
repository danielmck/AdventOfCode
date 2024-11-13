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

int find_num(std::string l1, int ind, int &prod) {
    std::string temp = l1;
    std::regex rn("(\[0-9]+)");
    std::smatch an;
    int inst = 0, pos = 0, st, end;
    while(regex_search(temp, an, rn)) {
        st = pos + an.position();
        end = st + an.length()-1;
        if ((st>=ind-1&st<=ind+1)|(end>=ind-1&end<=ind+1)|(st<ind-1 & end >ind+1)) {
            inst = inst+1;
            prod = prod*std::stoi(an.str());
        }
        if (end-pos < temp.length()) {
            temp = temp.substr(end-pos+1);
            pos = end+1;
        }
        else {temp="";}
    }
    return(inst);
}

int find_ast(std::string l1, std::string l2, std::string l3) {
    std::string temp = l2;
    std::regex ra("[*]");
    std::smatch a;
    int sum = 0, prod = 1, pos = 0, inst = 0;
    while(regex_search(temp, a, ra)) {
        prod = 1;
        inst = 0;
        inst = inst + find_num(l1,pos+a.position(),prod);
        inst = inst + find_num(l2,pos+a.position(),prod);
        inst = inst + find_num(l3,pos+a.position(),prod);
        if (inst == 2) {sum = sum +prod;}
        if (a.position()+1 < temp.length()-1) {
            temp = temp.substr(a.position()+1);
            pos = pos + a.position()+1;
        }
    }
    return(sum);
}

int get_part_sum(std::string l1, std::string l2, std::string l3) {
    std::string temp = l2, t1, t3, tf, tb;
    std::regex rn("\[0-9]+");
    std::regex rs("(\[^0-9.])");
    std::smatch an, as1, as3, asf, asb;
    int sum =0, count=0, pos, len = l2.length(), mlen;

    while(regex_search(temp, an, rn)) {
        // std::cout << an.str() << std::endl;
        pos = count+an.position();
        mlen = an.length();
        if (l1.length() > 0) {t1 = l1.substr(max(pos-1,0),min(mlen+2,len-pos));}
        else {t1=l1;}
        if (l3.length() > 0) {t3 = l3.substr(max(pos-1,0),min(mlen+2,len-pos));}
        else {t3=l3;}
        tf = l2.substr(max(pos-1,0),min(pos,1));
        tb = l2.substr(min(pos+mlen,len-1),min(len-pos-1,1));
        // std::cout << an.str() << " " << tb << std::endl;
        if (regex_search(t1, as1, rs) | regex_search(t3, as3, rs) | regex_search(tf, asf, rs) | regex_search(tb, asb, rs)) {
            sum = sum + std::stoi(an.str());
            // std::cout << std::stoi(an.str()) << std::endl;
        }
        if (an.position()+mlen < temp.length()-1) {
            temp = temp.substr(an.position()+mlen);
            count = count + an.position()+mlen;
        }
    }
    return(sum);
}

int main() {
    std::fstream newfile, file2;
    std::string fname = "test.txt";
    newfile.open(fname,std::ios::in); // open a file to perform write operation using file object
    std::string l1, l2, l3 = "";
    int ind, val, sum =0, rnum = 12, bnum=14, gnum=13;
    // std::cout << "hello" << std::endl;
    getline(newfile, l2);
    getline(newfile, l1);
    sum = sum + find_ast(l1,l2,"");
    l3=l2;
    l2=l1;
    while(getline(newfile, l1)){
        sum = sum + find_ast(l1,l2,l3);
        l3=l2;
        l2=l1;
    }
    sum = sum + find_ast("",l2,l3);
    std::cout << sum << std::endl;
}