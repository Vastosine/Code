
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int system(const string &s) {
    return system(s.c_str());
}

int main(int argc, char **args) {
    if (argc < 2) cerr << "Args Not found!";
    string workspace = "D:\\code\\OI\\pta\\";
    string dir = workspace + args[1] + "\\";
    string tem = workspace + "template.cpp";
    system("mkdir " + dir);
    int n = 15;
    if (argc > 2) sscanf(args[2], "%d", &n);
    for (int i = 1; i <= n; i++) {
        system("copy " + tem + " " + dir + to_string(i) + ".cpp");
    }
}