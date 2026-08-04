#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::sort;

const string POSITION[] = {
    "BangZhu",
    "FuBangZhu",
    "HuFa",
    "ZhangLao",
    "TangZhu",
    "JingYing",
    "BangZhong"
};

int get_pos(const string &position) {
    for (int i = 0; i < 7; i++) {
        if (POSITION[i] == position) return i;
    }
    return -1;
}

struct Member {
    string name;
    int position;
    int contribution;
    int level;
    int id;
};

bool compare_reserve(const Member &a, const Member &b) {
    return a.contribution > b.contribution ||
        (a.contribution == b.contribution && a.id < b.id);
}

bool compare_list(const Member &a, const Member &b) {
    return a.position < b.position ||
        (a.position == b.position && (a.level > b.level || 
            (a.level == b.level && a.id < b.id)));
}

const string NAME = "absi2011";

int main() {
    int n;
    cin >> n;
    vector<Member> a;
    int positions[7] = {0, 0, 2, 4, 7, 25, 69};
    for (int i = 0; i < n; i++) {
        string name, position;
        int contribution, level;
        cin >> name >> position >> contribution >> level;
        int pos = get_pos(position);
        a.push_back({name, pos, contribution, level, i});
        if (name == NAME) positions[pos]--;
    }
    sort(a.begin(), a.end(), compare_reserve);
    // for (const Member &i : a) {
    //     cout << i.name << " " << POSITION[i.position] << " " << i.contribution << " " << i.level << "\n";
    // }
    int p = 2;
    for (Member &i : a) {
        if (i.position < 2 || i.name == NAME) continue;
        while (!positions[p]) p++;
        i.position = p;
        positions[p]--;
    }
    sort(a.begin(), a.end(), compare_list);
    for (const Member &i : a) {
        cout << i.name << " " << POSITION[i.position] << " " << i.level << "\n";
    }
}
