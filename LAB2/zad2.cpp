#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <map>
#include <string>
#include <vector>

using mojafunkcja_t = std::function<double(std::vector<double>)>;

int main(int argc, char **argv) {
    using namespace std;
    map<string, mojafunkcja_t> optfunction;
    optfunction["sphereF"] = [](vector<double> args) {
        auto value_1 = args.at(0);
        return pow(value_1,2);
    };
    optfunction["boothF"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        return pow((x + 2*y + 5),2) + pow((2*x+y-5),2);
    };
    optfunction["matyasF"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        return 0.26*(pow(x,2) + pow(x,2))-0.48*(x*y);
    };
    try {
        vector<string> argumenty(argv, argv + argc);

        vector<double> values;
        transform(argv + 2, argv + argc,  std::back_inserter(values), [](const char* v){return std::stod(v);});

        auto selected_f = argumenty.at(1);
        auto f = optfunction.at(selected_f);
        auto c = f(values);
        cout << "result is: " << c << endl;
    }
    catch (std::out_of_range aor) {
        cout << "Enter a valid argument. The available are: ";
        for (auto [k, v] : optfunction) cout << " " << k;
        cout << endl;
    }
}