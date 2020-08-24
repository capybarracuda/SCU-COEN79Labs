// FILE: random.cpp
#include <iostream>
#include <cassert>
#include "random.h"

using namespace std;
using namespace coen79_lab2;

rand_gen::rand_gen(int seed_init, int multiplier_init, int increment_init, int modulus_init)
{
    seed = seed_init;
    multiplier = multiplier_init;
    increment = increment_init;
    modulus = modulus_init;
}

void rand_gen::set_seed(int newSeed)
{
    seed = newSeed;
}

int rand_gen::next()
{
    set_seed(((multiplier * seed) + increment) % modulus);//set the new seed to be the result of the algorithm
    return seed;
}

void rand_gen::print_info() const
{
    cout << "\nSeed = " << seed << "\nMultiplier = " << multiplier << "\nIncrement = " << increment << "\nModulus = " << modulus << "\n";//print all of the variables
}
