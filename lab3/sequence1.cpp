//Silas Kidd Myers
//COEN 79
//24 April 2020
//Lab 3: Implement a sequence class that keeps track of numbers

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <math.h>
#include "sequence1.h"

using namespace coen79_lab3;

sequence::sequence()
{
    sum = 0;
    first = new value_type[CAPACITY];
    curr = first;
    las = curr;
    used = 0;
}

//MODIFICATION
//MEMBER
//FUNCTIONS

void sequence::start()
{
    curr = first;
}

void sequence::end()
{
    curr = (las + 1);
}

void sequence::last()
{
    int i;//for loops
    curr = first;
    for(i=0; i < CAPACITY; i++)
        curr++;
}

void sequence::advance()
{
    assert(is_item());
    if(curr != (las + 1))
    {
        curr++;
    }   
    
}

void sequence::retreat()
{
    if(first != curr)
    {
        curr--;
    }
}

void sequence::insert(const value_type& entry)
{
    assert(used < CAPACITY);
    if(is_item())
    {  
        value_type* p;
        int i;
        las++;
        p = las;
        while(p != curr)//go until curr is in front of p
        {
            *p = *(p - 1);//shift every entry up one
            p--;
        }
        curr = p;
        *p = entry;//p now points to the first item, copy entry to the value pointed by the address
        used++;
    }
    else
    {
        insert_front(entry);
    }  
}

void sequence::attach(const value_type& entry)
{
    assert(used < CAPACITY);
    if(is_item())
    {
        value_type* p;
        int i;
        las++;
        p = las;
        while((p - 1) != curr)//go until curr
        {
            *(p) = *(p - 1);//shift every entry up one
            p--;
        }
        *p = entry;//p now points to the first item, copy entry to the value pointed by the address
        curr = p;
        used++;//the size has gone up by one
    } 
    else
    {
        attach_back(entry);
    }   
}

void sequence::insert_front(const value_type& entry)
{
    assert(used < CAPACITY);
    value_type* p;
    int i;//for loops
    las++;
    p = las;
    for(i = 0; i < used; i++)//runs as many times as the size is
    {
        *(p) = *(p - 1);//shift every entry up one
        p--;
    }
    *p = entry;//p now points to the first item, copy entry to the value pointed by the address
    first = p;//the first item is now here
    curr = first;//curr is now the new entry
    used++;//the size has gone up by one
}

void sequence::attach_back(const value_type& entry)
{
    assert(used < CAPACITY);
    value_type* p;
    p = las;//set the pointer to the end of the array
    if(used > 0)
        p++;
    *p = entry;//copy entry into this new spot
    used++;//the size is now 1 larger
    curr = p;//curr is now the new item
    las = curr;//the new item is also the las in the sequence
}

void sequence::remove_front()
{
    curr = first;
    assert(is_item());
    value_type* p;
    int i;//for loops
    p = first;

    for(i = 0; i < (used - 1); i++)//shift all the values in the array over
    {
        p++;
        *(p - 1) = *p;
    }
    
    las--;
    used--;
}

void sequence::remove_current()
{
    assert(is_item());
    value_type* p;
    p = curr;

    while(p != las)//traverse the sequence, shifting everything after curr over one
    {
        p++;
        *(p - 1) = *p;
    }

    las--;//the size is one smaller, las goes back one
    if(curr == NULL)//if curr was equal to las, then now it won't point to anything so set it to be the las item again
    {
        curr = las;
    }
    used--;//the size has decreased by one
}

//CONSTANT
//MEMBER
//FUNCTIONS

sequence::size_type sequence::size() const
{
    return used;
}

bool sequence::is_item( ) const
{
    return ((curr - first) < used);
}

sequence::value_type sequence::current() const
{
    assert(is_item());
    return *curr;
} 

sequence::value_type sequence::operator[](int index) const
{
    assert(index < used);
    value_type* p;
    int i;//for loops
    p = first;
    for(i=0; i < index; i++)
    {
        p++;
    }

    return *p;
}

double sequence::mean() const
{
    return sum / used;
}

double sequence::standardDeviation() const
{
    value_type* p;
    int i;//for loops
    double variance;
    p = first;
    double ave = sum / used;
    
    for(i = 0; i < used; i++)
    {
        variance += ((*p - ave) * (*p - ave));
        p++;
    }
    return sqrt(variance / used);
}

//NON-MEMBER
//FUNCTIONS

sequence operator+(const sequence& lhs, const sequence& rhs)
{
    assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
    sequence s;
    int i;
    int size_r = rhs.size();
    int size_l = lhs.size();
    for(i = 0; i < size_l; i++)
        s.attach(lhs[i]);
    for(i = 0; i < size_r; i++)
        s.attach(rhs[i]);
    return s;
}

sequence operator+=(const sequence& lhs, const sequence& rhs)
{
  sequence s = lhs + rhs;
  return s;
}

sequence::value_type summation(const sequence &s)
{
    int i, size, sum = 0;
    size = s.size();

    for(i = 0; i < size; i++)
    {
        sum += s[i];
    }

    return sum; 
}
