#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <map>
#include <string>
#include <vector>

using mojafunkcja_t = std::function<double(std::vector<double>)>;

std::vector<double> get_result(std::function<double(std::vector<double>)> f, double border_1, double border_2, int iterations){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<double> distr(border_1, border_2);
    std::vector<double> closest_numbers = {distr(gen), distr(gen)};

    double result = f(closest_numbers);
    for(int u = 0; u < iterations; u++){
        std::vector<double> args = {distr(gen), distr(gen)};
        double new_result = f(args);
        if (new_result < result){
            result = new_result;
            closest_numbers = args;
        }

    }
    return closest_numbers;
}

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
        //cout << "result is: " << c << endl;
    }
    catch (std::out_of_range aor) {
        cout << "Enter a valid argument. The available are: ";
        for (auto [k, v] : optfunction) cout << " " << k;
        cout << endl;
    }
    vector<string> argumenty(argv, argv + argc);
    auto selected_f = argumenty.at(1);
    auto f = optfunction.at(selected_f);

        std::vector<std::string> argument(argv, argv + argc);
        std::string func_name = argument.at(1);

        std::vector<double> values;
        transform(argv + 2, argv + argc,  std::back_inserter(values), [](const char* v){return std::stod(v);});
        double border_low = values.at(0);
        double border_high = values.at(1);
        std::vector<double> my_result = get_result(f, -10.0, 10.0, 10000000);
        std::cout << my_result[0] << std::endl;
        std::cout << my_result[1] << std::endl;


    return 0;
}