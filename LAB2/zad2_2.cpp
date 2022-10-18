#include <iostream>
#include <functional>
#include <vector>
#include <random>
#include <string>
double bealeF(std::vector <double> xy) {
    double x = xy[0];
    double y = xy[1];
    double first_square = (1.5 - x - x*y)*(1.5 - x - x*y);
    double second_square = (2.25 - x - x*y*y)*(2.25 - x - x*y*y);
    double third_square = (2.625 - x - x*y*y*y)*(2.625 - x - x*y*y*y);
    return first_square + second_square + third_square;
}

double matyasF(std::vector <double> xy){
    double x = xy[0];
    double y = xy[1];
    return 0.26*(x*x + y*y) - 0.48*x*y;
}

double boothF(std::vector <double> xy){
    double x = xy[0];
    double y = xy[1];
    return pow((x + 2*y + 5),2) + pow((2*x+y-5),2);
    };

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
    std::vector<std::string> argument(argv, argv + argc);
    std::string func_name = argument.at(1);

    std::vector<double> values;
    transform(argv + 2, argv + argc,  std::back_inserter(values), [](const char* v){return std::stod(v);});
    double border_low = values.at(0);
    double border_high = values.at(1);
    std::vector<double> my_result = get_result(boothF, -10.0, 10.0, 10000000);
    std::cout << my_result[0] << std::endl;
    std::cout << my_result[1] << std::endl;

    return 0;
}