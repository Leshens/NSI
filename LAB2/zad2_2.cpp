#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <map>
#include <string>

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
    optfunction["bealeF"] = [](vector<double> args) {
        double x = args.at(0);
        double y = args.at(1);
        double first_square = (1.5 - x - x*y)*(1.5 - x - x*y);
        double second_square = (2.25 - x - x*y*y)*(2.25 - x - x*y*y);
        double third_square = (2.625 - x - x*y*y*y)*(2.625 - x - x*y*y*y);
        return first_square + second_square + third_square;

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
    vector<string> argumenty(argv, argv + argc);
    auto selected_f = argumenty.at(1);
    auto f = optfunction.at(selected_f);

        std::vector<std::string> argument(argv, argv + argc);
        std::string func_name = argument.at(1);
        double low = atof(argv[2]);
        double high = atof(argv[3]);
        vector<double> output = get_result(optfunction[func_name], low, high, 1000000);
        cout << "x = " << output[0] << ", y = " << output[1] << endl;
        return 0;
    }
