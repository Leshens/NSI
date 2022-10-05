#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
using mojafunkcja_t = std::function<double(std::vector<double> a)>;

int main(int argc, char **argv) {
    using namespace std;
    map< string, mojafunkcja_t > formatery;
    formatery["sin"] = [](vector<double> a) {
        auto value = a.at(0);
        return sin(value);
    };
    formatery["add"] = [](vector<double> a) {
        double x = a.at(1);
        double y = a.at(2);
        return x+y;
    };
    formatery["mod"] = [](vector<double> a) {
        double x = a.at(1);
        double y = a.at(2);
        return fmod(x,y);
    };
    try {
        vector<string> argumenty(argv, argv + argc);
        vector<double> values(argc-2);
        transform(argv+1,argv+argc,values.begin(),[](const std::string &v){return stod(v);});
        auto selected_f = argumenty.at(1);
        cout << "result: "<<c<< endl;

    } catch (std::out_of_range aor) {
        cout << "podaj argument. Dostępne to: ";
        for (auto [k, v] : formatery) cout << " " << k;
        cout << endl;
    }
    return 0;
}