#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

// --------------------------------------------------------
//
// to test, execute:
// echo "nail 100 hammer 20 saw2 4 saw1 3 nail 250 saw0 45" | ./a.out
//
// --------------------------------------------------------

void readitems(map<string, int>& m)
{
    string word;
    int val=0;
    while (cin >> word >> val) m[word] =val;
}




template <class T>
void printPair(const T& p)
{
    cout << p.first << " = " << p.second << endl;
}

template <class T1, class T2>
void printMap(map<T1,T2> tbl)
{
    cout << endl;
    for_each(tbl.begin(), tbl.end(), printPair<typename map<T1,T2>::value_type>);
}




void deleteItems(map<string, int>& tbl, const string& key)
{
    map<string, int>::iterator p = tbl.begin();
    while (p!=tbl.end()) {
        cout << "looking at: " << p->first << ":" << p->second << endl;
        if (p->first.compare(0, key.size(), key)==0){
            cout << "deleting " << p->first << ":" << p->second << endl;
            tbl.erase(p++);
        }else {
            ++p;
        }
    }
}


int main (int argc, char** argv) {

    map<string, int> tbl;
    readitems(tbl);
    printMap(tbl);


    cout << "\nDeleting all saws" << endl;
    deleteItems(tbl, "saw");
    printMap(tbl);

    return !cin;
}
