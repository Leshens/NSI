/*
#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
using mojamapa_t = std::map<std::string, int>;
using mojafunkcja_t = std::function<double(std::vector<double>)>;
int main(int argc, char **argv) {
    using namespace std;
    map<string, mojafunkcja_t> formatery;
    formatery["sin"] = [](vector<double> args) {
        auto value_1 = args.at(0);
        return sin(value_1);
    };
    formatery["mod"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        return fmod(x, y); };
    formatery["add"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        return x + y; };
    try {
        vector<string> argumenty(argv, argv + argc);

        vector<double> values;
        transform(argv + 2, argv + argc,  std::back_inserter(values), [](const char* v){return std::stod(v);});

        auto selected_f = argumenty.at(1);
        auto f = formatery.at(selected_f);
        auto c = f(values);
        cout << "result is: " << c << endl;
    }
    catch (std::out_of_range aor) {
        cout << "Enter a valid argument. The available are: ";
        for (auto [k, v] : formatery) cout << " " << k;
        cout << endl;
    }
    return 0;
}
*/