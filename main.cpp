#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>


int xor_binary(int a, int b){
    if(a !=b){
        return 1;
    }
    return 0;
}

std::vector<int> gray_to_binary(std::vector<int> gray){
    std::vector<int> result = {};
    int b = gray[0];
    int g = b;
    result.push_back(b);
    b = xor_binary(g, gray[1]);
    result.push_back(b);
    for(int i = 2; i < gray.size(); i++){
        b = xor_binary(b, gray[i]);
        result.push_back(b);
    }
    return result;
}

double binary_to_decimal(std::vector<int> binary, double starting_power){
    int result = 0;

    std::vector<int> binary_copy = binary;
    std::reverse(binary_copy.begin(), binary_copy.end());
    for (int number : binary_copy){
        result += number * pow(2.0, starting_power);
        starting_power += 1;
    }
    return result;
}

double gray_to_decimal(std::vector<int> binary, double starting_power){

    double result = 0.0;

    std::vector<int> binary_copy = gray_to_binary(binary);
    std::reverse(binary_copy.begin(), binary_copy.end());
    for (int number : binary_copy){
        result += double(number) * pow(2.0, starting_power);
        starting_power += 1.0;
    }
    return result;
}

std::vector<double> binary_get_all_args_to_vector(std::vector<int> binary, int number_of_arguments, double starting_power){
    std::vector<double> result = {};
    int one_arg_size = binary.size() / number_of_arguments;
    std::vector<int>::iterator start = binary.begin();
    for(int i = 0; i < number_of_arguments; i++){
        std::vector<int> partial(start, start + one_arg_size);
        int dec = binary_to_decimal(partial, starting_power);

        result.push_back(dec);
        start += one_arg_size;
    }


    return result;
}

std::vector<double> gray_get_all_args_to_vector(std::vector<int> binary, int number_of_arguments, double starting_power){
    std::vector<double> result = {};
    int one_arg_size = binary.size() / number_of_arguments;
    std::vector<int>::iterator start = binary.begin();
    for(int i = 0; i < number_of_arguments; i++){
        std::vector<int> partial(start, start + one_arg_size);
        double dec = gray_to_decimal(partial, starting_power);

        result.push_back(dec);
        start += one_arg_size;
    }


    return result;
}

double restrigin_function(std::vector <double> xy){
    double x = xy[0];
    double y = xy[1];
    double A = 10.0;
    return A*2.0 + x*x - A*cos(2*M_PI*x) + y*y - A*cos(2*M_PI*y);
}

double restrigin_function_from_gray(std::vector <int> gray, double start_power){
    std::vector<double> args = gray_get_all_args_to_vector(gray, 2, start_power);
    double x = args[0];
    double y = args[1];
    double A = 10.0;
    return A*2.0 + x*x - A*cos(2*M_PI*x) + y*y - A*cos(2*M_PI*y);
}

double restrigin_function_from_binary(std::vector <int> binary, double start_power){
    std::vector<double> args = binary_get_all_args_to_vector(binary, 2, start_power);
    double x = args[0];
    double y = args[1];
    double A = 10.0;
    return A*2.0 + x*x - A*cos(2*M_PI*x) + y*y - A*cos(2*M_PI*y);
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr (0,1);
    std::vector<int>my_numbers;
    for (int i = 0; i < 111; ++i) {
        my_numbers.push_back(distr(gen));
    }
    double a = restrigin_function_from_gray({1,0,0,1,1,1,1,0,0,1,1,1}, 0.0);
    double c = restrigin_function_from_gray(my_numbers, -50.0);
    double b = restrigin_function({58,58});
//    std::vector<double> r = gray_get_all_args_to_vector({1,0,0,1,1,1,1,0,0,1,1,1}, 2, -3.0);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}