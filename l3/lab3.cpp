#include <iostream>
#include <functional>
#include <vector>
#include <random>
#include <string>
double beale_function(std::vector <double> xy) {
//    -4.5, 4.5
    double x = xy[0];
    double y = xy[1];
    double first_square = (1.5 - x + x*y)*(1.5 - x + x*y);
    double second_square = (2.25 - x + x*y*y)*(2.25 - x + x*y*y);
    double third_square = (2.625 - x + x*y*y*y)*(2.625 - x + x*y*y*y);
    return first_square + second_square + third_square;
}

double restrigin_function(std::vector <double> xy){
    double x = xy[0];
    double y = xy[1];
    double A = 10.0;
    return A*2.0 + x*x - A*cos(2*M_PI*x) + y*y - A*cos(2*M_PI*y);
}

double matyas_function(std::vector <double> xy){
//    -10 , 10
    double x = xy[0];
    double y = xy[1];
    return 0.26*(x*x + y*y) - 0.48*x*y;
}

double him_function(std::vector <double> xy){
//    -5 ,5
    double x = xy[0];
    double y = xy[1];
    return (x*x + y - 11.0)*(x*x + y - 11.0) + (x + y*y - 7.0)*(x + y*y - 7.0);
}

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

std::vector<double> get_hill_neighbor(std::vector<double> ar) {
    double a = ar[0];
    double b = ar[1];
    std::random_device rd;
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<double> distance(-0.005, 0.005);
    a = a + distance(gen);
    b = b + distance(gen);
    return {a, b};
}

std::vector<double> hill_climbing(std::function<double(std::vector<double>)> f, double border_1, double border_2, int iterations){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<double> distr(border_1, border_2);
    std::vector<double> closest_numbers = {distr(gen), distr(gen)};

    double result = f(closest_numbers);
    for(int u = 0; u < iterations; u++){
        std::vector<double> args = get_hill_neighbor(closest_numbers);
        if (args[0] > border_2 or args[0] < border_1 or args[1] > border_2 or args[1] < border_1){
            continue;
        }
        double new_result = f(args);
        if (new_result < result){
            result = new_result;
            closest_numbers = args;
        }

    }
    return closest_numbers;
}


std::vector<double> generate_neighbour(std::vector<double> current_point){
    double a = current_point[0];
    double b = current_point[1];
    std::random_device rd;
    std::mt19937 gen(rd()); // seed the generator
    std::normal_distribution<double> distance;
    a = a + 0.01*distance(gen);
    b = b + 0.01*distance(gen);
    return {a, b};
}

std::vector<double> simulate_annealing(std::function<double(std::vector<double>)> f, double border_1, double border_2, int iterations){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<double> distr(border_1, border_2);
    std::vector<double> closest_numbers = {distr(gen), distr(gen)};
    std::vector<double> args = {distr(gen), distr(gen)};
    double result = f(closest_numbers);
    std::vector<std::vector<double>> visited_points = {};

    for (int k = 0; k < iterations; k++){
        std::vector<double> neighbour = generate_neighbour(closest_numbers);
        double new_result = f(neighbour);
        if (new_result < result){
            result = new_result;
            closest_numbers = neighbour;
        }
        else {
            std::uniform_real_distribution<double> rand(0, 1);
            double temp = new_result-result;
            if (temp < 0){
                temp = temp * -1;
            }
            double Tk = 10000.0/k;
            if (rand(gen) < exp(-1*temp)/Tk) {
                closest_numbers = neighbour;
            }

        }

    }


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
    std::vector<double> my_result = get_result(matyas_function, -5.12, 5.12, 1000000);
    std::cout << "stochastic: " << std::endl;
    std::cout << my_result[0] << std::endl;
    std::cout << my_result[1] << std::endl;
    std::vector<double> annealing_result = simulate_annealing(matyas_function, -5.12, 5.12, 1000000);
    std::cout << "annealing result: " << std::endl;
    std::cout << annealing_result[0] << std::endl;
    std::cout << annealing_result[1] << std::endl;
    std::vector<double> hill_climb_result = hill_climbing(matyas_function, -5.12, 5.12, 1000000);
    std::cout << "hill climb result: " << std::endl;
    std::cout << hill_climb_result[0] << std::endl;
    std::cout << hill_climb_result[1] << std::endl;
    return 0;
}