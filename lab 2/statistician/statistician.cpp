// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

statistician::statistician(int len_init, double min_init, double max_init, double total_init)
{
    len = len_init;
    min = min_init;
    max = max_init;
    total = total_init;
}

void statistician::next(double r)
{
    if(min > r) //set the new min and max based off of the new double
        min = r;
    if(max < r)
        max = r;
    total += r;
    len++;
}

void statistician::reset( )
{
    len = 0;
    min = 9999;
    max = -9999;
    total = 0;
}

int statistician::length( ) const
{
    return len;
}

double statistician::sum() const
{
    return total;
}

double statistician::mean() const
{
    assert(len > 0);
    return total / len;
}

double statistician::minimum() const
{
    assert(len > 0);
    return min;
}

double statistician::maximum() const
{
    assert(len > 0);
    return max;
}

statistician coen79_lab2::operator+(const statistician &s1, const statistician &s2)//I had to add the coen79_lab2 in order for it to compile
{
    int new_len;
    double new_min, new_max, new_sum;
    
    new_len = s1.length() + s2.length(); //add the two lengths
    new_min = (s1.minimum() < s2.minimum()) ? s1.minimum() : s2.minimum(); //take the min of the two sequences
    new_max = (s1.maximum() > s2.maximum()) ? s1.maximum() : s2.maximum(); //take the max of the two sequences
    new_sum = s1.sum() + s2.sum(); //add the sums
   
    statistician new_s(new_len, new_min, new_max, new_sum);

    return new_s;
}

statistician coen79_lab2::operator*(double scale, const statistician &s)//I had to add the coen79_lab2 in order for it to compile
{
    int new_len;
    double new_min, new_max, new_sum;
    
    new_len = s.length();
    new_min = s.minimum() * scale;
    new_max = s.maximum() * scale;
    new_sum = s.sum() * scale;
    
    statistician new_s(new_len, new_min, new_max, new_sum); // multiply the min, max and sum of the sequence by the scale

    return new_s;
}

bool coen79_lab2::operator==(const statistician &s1, const statistician &s2)//I had to add the coen79_lab2 in order for it to compile
{
    bool flag;

    if((s1.length() == 0) && (s2.length() == 0))
        flag = true;
    else if(
        (s1.minimum() == s2.minimum()) && 
        (s1.maximum() == s2.maximum()) && 
        (s1.length() == s2.length()) && 
        (s1.sum() == s2.sum()) && 
        (s1.mean() == s2.mean())
    )
        flag = true;
    else
        flag = false;
    
    return flag;   
}
