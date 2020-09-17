#include "testlib.h"
#include <map>
#include <vector>
#include <iostream>
using namespace std;

vector <string> getL(string raw) {
    vector <string> res;
    res.push_back("");
    for (auto c: raw) {
        if (c == ' ') {
            res.push_back(""); }
        else if (c != '\n') {
            res.back().push_back(c); } }
    while (res.size() && res.back() == "") res.pop_back();
    return res; }

string eraseSpace(string raw) {
    string res;
    for (auto c: raw) {
        if (c != ' ' && c != '\n') {
            res.push_back(c); } }
    return res; }

bool valid(vector <string> a, vector <string> b) {
    map <string,string> mp;
    for (int i=0;i<(int)a.size();i++) {
        if (!mp.count(a[i])) {
            mp[a[i]] = b[i]; }
        else {
            if (b[i] != mp[a[i]]) {
                return 0; } } }
    return 1; }

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int split = ouf.readInt(1,100);
    ouf.readLine();
    string aRaw = ouf.readLine();
    string bRaw = ouf.readLine();
    vector <string> as = getL(aRaw);
    vector <string> bs = getL(bRaw);
    string a = inf.readString();
    string b = inf.readString();

    if ((int)as.size() != split) {
        quitf(_wa, ": Line 2 should contains %d space sperated strings, but %d found.", split, (int)as.size()); }
    if ((int)bs.size() != split) {
        quitf(_wa, ": Line 3 should contains %d space sperated strings, but %d found.", split, (int)bs.size()); }

    string aTo = eraseSpace(aRaw);
    string bTo = eraseSpace(bRaw);
    if (aTo != a) {
        quitf(_wa, ": The original A is %s, but %s found.", a.c_str(), aTo.c_str()); }
    if (bTo != b) {
        quitf(_wa, ": The original B is %s, but %s found.", b.c_str(), bTo.c_str()); }

    if (!valid(as,bs)) {
        quitf(_wa, ": Answer is not an one-to-one map"); }
    if (!valid(bs,as)) {
        quitf(_wa, ": Answer is not an one-to-one map"); }

    quitp(split / 100.0, ": You got %d points", split);
}
