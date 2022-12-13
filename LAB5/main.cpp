#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>

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
    double result = 0;

    std::vector<int> binary_copy = binary;
    std::reverse(binary_copy.begin(), binary_copy.end());
    for(int i = 1; i < binary_copy.size(); i++){
        result += binary_copy[i] * pow(2.0, starting_power);
        starting_power += 1;
    }
    if(binary_copy[0] == 0){
        return -result;
    }
    return result;
}

double gray_to_decimal(std::vector<int> binary, double starting_power){

    double result = 0.0;

    std::vector<int> binary_copy = gray_to_binary(binary);
    std::reverse(binary_copy.begin(), binary_copy.end());
    for(int i = 1; i < binary_copy.size(); i++){
        result += binary_copy[i] * pow(2.0, starting_power);
        starting_power += 1;
    }
    if(binary_copy[0] == 0){
        return -result;
    }
    return result;
}

std::vector<double> binary_get_all_args_to_vector(std::vector<int> binary, int number_of_arguments, double starting_power){
    std::vector<double> result = {};
    int one_arg_size = binary.size() / number_of_arguments;
    std::vector<int>::iterator start = binary.begin();
    for(int i = 0; i < number_of_arguments; i++){
        std::vector<int> partial(start, start + one_arg_size);
        double dec = binary_to_decimal(partial, starting_power);

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



std::vector<int> generate_arguments(int size){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 1); // define the range
    std::vector<int> arguments = {};
    for(int i=0; i<size; i++){
        arguments.push_back(distr(gen));
    }
    return arguments;
}

std::vector<std::vector<int>> generate_population(int population_size, int size){
    std::vector<std::vector<int>> population = {};
    for(int i=0; i<population_size; i++){
        population.push_back(generate_arguments(size));
    }
    return population;
}

void mutate(std::vector<int> &population_element, int probability){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 100); // define the range
    for(int & i : population_element){
        if (distr(gen) < probability){
            if(i== 1){
                i = 0;
            }
            else{
                i = 1;
            }
        }
    }
}

void perform_mutations_on_population(std::vector<std::vector<int>> &population, int probability){
    for(std::vector<int> & i : population){
        mutate(i, probability);
    }
}

void make_children(std::vector<int> parent_1, std::vector<int> parent_2, std::vector<std::vector<int>> &children){
    if(parent_1.size() != parent_2.size()){
        throw std::invalid_argument( "one of parent is retarded!" );
    }
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, parent_2.size() - 1); // define the range
    int pivot = distr(gen);

    std::vector<int> children_1 = {};
    for(int i = 0; i<pivot; i++){
        children_1.push_back(parent_1[i]);
    }
    for(int i = pivot; i<parent_1.size(); i++){
        children_1.push_back(parent_2[i]);
    }
    std::vector<int> children_2 = {};
    for(int i = 0; i<pivot; i++){
        children_2.push_back(parent_2[i]);
    }
    for(int i = pivot; i<parent_1.size(); i++){
        children_2.push_back(parent_1[i]);
    }

    children.push_back(children_1);
    children.push_back(children_2);
}

std::vector<std::vector<int>> crossover(std::vector<std::vector<int>> population, int population_size){
    std::vector<std::vector<int>> children = {};
    std::vector<std::vector<int>> population_copy = population;
    // make babies
    for(int y=0; y<population_size/2; y++){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, population_copy.size() - 1); // define the range
        int parent_id = distr(gen);
        std::vector<int> parent_1 = population_copy[parent_id];
        population.erase(population_copy.begin()+parent_id);
        std::uniform_int_distribution<> distr2(0, population_copy.size() - 1); // define the range
        int parent2_id = distr2(gen);
        std::vector<int> parent_2 = population_copy[parent2_id];
        population.erase(population_copy.begin()+parent2_id);
        make_children(parent_1, parent_2, children);

    }
    return children;
}

std::vector<int> genetic_algorithm(int size, double starting_power, int population_size, int mutation_chance, int iterations){
    std::vector<std::vector<int>> population = generate_population(population_size, 2*size);

    for(int i=0; i<iterations; i++){
        std::vector<std::vector<int>> children = crossover(population, population_size);
        perform_mutations_on_population(children, mutation_chance);
        for(std::vector<int> new_member: children){
            population.push_back(new_member);
        }
        std::sort(population.begin(), population.end(),
                  [&starting_power](std::vector<int> const& obj1, std::vector<int> const& obj2) -> bool
              {
                  return restrigin_function_from_gray(obj1, starting_power) < restrigin_function_from_gray(obj2, starting_power);
              });
        std::vector<std::vector<int>> new_population = {};
        // weaker result deletion
        for(int o=0; o<population_size; o++){
            new_population.push_back(population[o]);
        }
        std::cout << restrigin_function_from_gray(new_population[0], starting_power) << std::endl;
        population = new_population;
        std::vector<double> pop_result = {};
        for(std::vector<int> solution: population){
            pop_result.push_back(restrigin_function_from_gray(solution, starting_power));
        }
        std::cout << "iter end" << std::endl;

    }
    return population[0];

}



int main() {
    std::cout << "Hello, World!" << std::endl;

//    std::vector<double> args = binary_get_all_args_to_vector({1,1,1,1,1,1,1, 1,1,1,1,0,1,0}, 2, -3.0);
    std::vector<int> result = genetic_algorithm(7, -3.0, 6, 20, 100);
//    std::vector<std::vector<int>> population = generate_population(10, 10);
//
//    perform_mutations_on_population(population, 100);
    std::cout << std::endl;
//    std::vector<std::vector<int>> children = make_children(population[0], population[1]);
    return 0;
}