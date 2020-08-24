//Silas Kidd Myers
//COEN79 Lab 5
//14 May 2020
//Implement a class for strings

#include "mystring.h"
#include <cassert>
#include <cstring>

using namespace coen79_lab5;


// CONSTRUCTOR, COPY CONSTRUCTOR, and DESTRUCTOR
string::string(const char str[ ])
{
    current_length = strlen(str);//new length is the length of the new string
    allocated = current_length;
    characters = new char[allocated];// set new char* to size of string
    strncpy(characters, str, allocated);//copy string
    characters[current_length] = '\0';//add a null
}

string::string(char c)// NEW FUNCTION 1
{
    current_length = 1;//only 1 char
    allocated = 2;//need space for null
    characters = new char[allocated];
    characters[0] = c;
    characters[1] = '\0';
}  

string::string(const string& source)
{
    current_length = source.current_length;
    allocated = source.current_length + 1;
    characters = new char[allocated];
    strncpy(characters, source.characters, allocated);//copy new string
}

string::~string( )
{
    allocated = 0;//reset allocated and current length, must delete array of characters to avoid memory leak
    current_length = 0;
    delete[] characters;
}

// MODIFICATION MEMBER FUNCTIONS
void string::operator+=(const string& addend)
{
    reserve(current_length + addend.current_length);
    strncat(characters, addend.characters, allocated);//add new string
    current_length += addend.current_length;//add the 2 lengths
}

void string::operator+=(const char addend[ ])
{
    reserve(current_length + strlen(addend));//reserve memory for new string
    strncat(characters, addend, allocated);//add new string
    current_length += strlen(addend);//add 2 lengths 
}

void string::operator+=(char addend)
{
    reserve(current_length);
    characters[current_length] = addend;
    current_length++;
    characters[current_length] = '\0';//need null at end
}

void string::reserve(size_t n)
{
    char *temp = new char[n + allocated];
    strncpy(temp, characters, allocated);//add memory equal to the size of the two strings
    delete[] characters;//clear the current characters
    characters = temp;//temp is characters w/ proper amopunt of memory
    allocated += n;//update allocated
}

string& string::operator=(const string& source)
{
    reserve(source.current_length);//reserve the memory
    current_length = source.current_length;
    strncpy(characters, source.characters, current_length);//copy the string
    return *this;//return pointer to string
}

void string::insert(const string& source, unsigned int position)
{
    assert(position <= current_length);
    reserve(source.current_length + current_length);
    char buffer[current_length - position];//create buffer
    strncpy(buffer, characters + position, current_length - position);
    strncpy(characters + position + source.current_length, buffer, current_length - position);
    strncpy(characters + position, source.characters, source.current_length);
    current_length += source.current_length;//update current length
}

void string::dlt(unsigned int position, unsigned int num)
{
    assert(position + num <= current_length);
    size_t i;
    for(i = position; i <= (current_length - num); i++) 
    {
        characters[i] = characters[i + num];//shift all of the characters over to replace
    }
    characters[current_length] = '\0';// add null
    current_length -= num;//update current length
}

void string::replace(char c, unsigned int position)
{
    assert(position < current_length);
    characters[position] = c;
}

void string::replace(const string& source, unsigned int position)
{
    assert(position + source.current_length <= current_length);
    strncpy(&characters[position], source.characters, source.current_length);
}

// CONSTANT MEMBER FUNCTIONS
char string::operator[ ](size_t position) const
{
    assert(position < current_length);
    return characters[position];//use position as index
}

int string::search(char c) const
{
    int i;
    for(i = 0; i < current_length; i++) 
    {
        if(characters[i] == c) 
        {
            return i;//find character, then return index
        }
    }
    return -1;
}

int string::search(const string& substring) const
{
    int i;
    for(i = 0; i < (current_length - substring.current_length) + 1; i++) 
    {
        if(strncmp(&characters[i], substring.characters, substring.current_length) == 0) 
        {
            return i;//find string, then return index of first char
        }
    }
    return -1;
}

unsigned int string::count(char c) const
{
    unsigned int x = 0, i;
    for(i = 0; i < current_length; i++) 
    {
        if(characters[i] == c) 
        {
            x++;//add 1 every time character is found in string
        }
    }
    return x;
}

// FRIEND FUNCTIONS
namespace coen79_lab5//for some reason using namespace did not work here
{
    std::ostream& operator<<(std::ostream& outs, const string& source)
    {
        outs << source.characters;//print string
        return outs;
    }

    bool operator==(const string& s1, const string& s2)
    {
        return (strncmp(s1.characters, s2.characters, s1.current_length) == 0);//see if 2 strings are identical
    }

    bool operator!=(const string& s1, const string& s2)
    {
        if(s1 == s2) 
        {
            return false;//uses == operator to test
        }
        else return true;
    }

    bool operator>(const string& s1, const string& s2)
    {
        return (strncmp(s1.characters, s2.characters, s1.current_length) > 0);
    }

    bool operator<(const string& s1, const string& s2)
    {
        return (strncmp(s1.characters, s2.characters, s1.current_length) < 0);
    }

    bool operator>=(const string& s1, const string& s2)
    {
        return (((string)s1 == (string)s2) || ((string)s1 > (string)s2));
    }

    bool operator<=(const string& s1, const string& s2)
    {
        return (((string)s1 == (string)s2) || (s1 < s2));
    }
}
// NON-MEMBER FUNCTIONS for the string class
string coen79_lab5::operator+(const string& s1, const string& s2)
{
    string temp(s1);
    temp += s2;
    return temp;
}

string coen79_lab5::operator+(const string& s1, const char addend[ ])
{
    string temp(s1);
    temp += addend;
    return temp;
}

std::istream& coen79_lab5::operator>>(std::istream& ins, string& target)
{
    char buff[100] = {'\0'};//declare variable fir inout
    ins >> buff;
    target = string(buff);//set target to input
    return ins;
}
