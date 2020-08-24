#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include <math.h>
#include "keyed_bag.h"

using namespace coen79_lab4;


//CONSTRUCTOR
keyed_bag::keyed_bag( )
{
    num = 0;
}

//MODIFICATION 
//MEMBER 
//FUNCTIONS
void keyed_bag::erase()
{
    num = 0;
}

bool keyed_bag::erase(const key_type& key)
{
    int i;
    for(i=0;i<num;i++)
    {
        if(keys[i] == key)//if key is found
        {
            for(i;i<num;i++)//go though rest of array, writing the data over the erased bag
            {
                keys[i] = keys[i+1];
                data[i] = data[i+1];
            }
            num--;//decrement size tracker
            return true;
        }
    }
    return false;
}

void keyed_bag::insert(const value_type& entry, const key_type& key)
{
    assert(has_key(key) == false);
    assert(num < CAPACITY);

    keys[num] = key;//put in new key
    data[num] = entry;//new data

    num++;
}

void keyed_bag::operator+=(const keyed_bag& addend)
{
    assert(num + addend.size() <= CAPACITY);
    assert(hasDuplicateKey(addend) == false);
    int i;
    for(i=0;i<addend.size();i++)
        insert(addend.data[i], addend.keys[i]);//add all of the keys to the end
}

//CONSTANT 
//MEMBER 
//FUNCTIONS
bool keyed_bag::has_key(const key_type& key) const
{
    int i;

    for(i=0;i<num;i++)
    {
        if(keys[i] == key)//tretrun true if key found
            return true;
    }
    return false;
}

keyed_bag::value_type keyed_bag::get(const key_type& key) const
{
    assert(has_key(key));
    int i;
    for(i=0;i<num;i++)//find key and return data assigned to that key
        if(keys[i] == key)
            return data[i];
}

keyed_bag::size_type keyed_bag::size( ) const
{
    return num;
}

keyed_bag::size_type keyed_bag::count(const value_type& target) const
{
    int i;
    size_type tgt_count = 0;
    for(i=0;i<num;i++)
    {
        if(data[i] == target)
            tgt_count++;//increment every time target is found
    }
    return tgt_count;
}

bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const
{
    int i;
    for(i=0;i<num;i++)//for every key in bag
        if(otherBag.has_key(keys[i]))// if key is found in other bag return true
            return true;
    return false;            
}

keyed_bag coen79_lab4::operator+(const keyed_bag& b1, const keyed_bag& b2)
{
    keyed_bag new_bag;
    new_bag += b1;//add contents of bag 1 and 2 together.
    new_bag += b2;
    return new_bag;
}