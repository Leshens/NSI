#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <assert.h>

const int nBits = 6;
const int halfPopulSize = 5;
double ThrM = 0.4,ThrF = 0.6;

class Individual {
public:
    bool bits[nBits];
    double fitness;
    void compFitness()
    {
        int x = decode();
        fitness = x*x;
    }
    void initRandom()
    {
        for (int i=0; i<nBits; i++)
            if (rand() % 2==0)
                bits[i] = 0;
            else
                bits[i] = 1;
    }

    void crossOver(Individual &a, Individual &b)
    {
        int pos = rand() % (nBits-1);
        for (int i=0; i<=pos; i++)
            bits[i] = b.bits[i];
        for (int i = pos+1; i < nBits; i++)
            bits[i] = a.bits[i];
        printf("CO: %d %d,%d->%d\n",pos, a.decode(), b.decode(), decode());
    }

    int decode()
    {
        //Decode string as unsigned binary integer - true = 1, false = 0
        int accum = 0; int powerof2 = 1;
        for (int j = 0; j < nBits; j++)
        {
            if (bits[j])accum += powerof2;
            powerof2 *= 2;
        }
        return accum;
    }
};


std::vector<Individual> males;
std::vector<Individual> females;
std::vector<Individual> newMales;
std::vector<Individual> newFemales;

void initialize()
{
    for (int i=0; i<halfPopulSize; i++)
    {
        Individual ind;
        ind.initRandom();
        males.push_back(ind);
        ind.initRandom();
        females.push_back(ind);
    }
}

bool compare(const Individual &a, const Individual &b)
{
    return a.fitness > b.fitness;
}


void generate()
{
    for (int i = 0; i<halfPopulSize; i++)
        males[i].compFitness();
    sort(males.begin(), males.end(), compare);
    for (int i = 0; i<halfPopulSize; i++)
        females[i].compFitness();
    sort(females.begin(), females.end(), compare);
    int hM = (int)(halfPopulSize * ThrM);
    int hF = (int)(halfPopulSize * ThrF);
    for (int i = 0; i<halfPopulSize; i++)
    {
        int indexM = rand() % hM;
        int indexF = rand() % hF;
        Individual ind;
        ind.crossOver(males[indexM], females[indexF]);
        newMales.push_back(ind);
        indexM = rand() % hM;
        indexF = rand() % hF;
        ind.crossOver(males[indexM], females[indexF]);
        newFemales.push_back(ind);
    }
    males = move(newMales);
    females = move(newFemales);
}

void print()
{
    for (int i = 0; i<halfPopulSize; i++)
        printf("%d ",males[i].decode());
    printf("|");
    for (int i = 0; i<halfPopulSize; i++)
        printf("%d ", females[i].decode());
    printf("\n");
}

int main()
{
    initialize();
    for (int i=0; i<10; i++)
    {
        generate();
        print();
    }
    return 0;
}