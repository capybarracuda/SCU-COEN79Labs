#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <assert.h>
#include <time.h>

using namespace std;

void countIn()
{
    int i, alpha = 0, nonalpha = 0;
    string input;
    cout << "Type something: ";
    getline(cin, input);

    for(i=0;i<(input.length());i++)// count the amount of alphanumerical and non-alphanumerical characters
    {
        if(isalpha(input[i]))
            alpha++;
        else
            nonalpha++;
    }

    cout << "\nThere are " << alpha << " alphanumeric characters and " << nonalpha << " non-alphanumeric characters.\n";
    return;
}

void numRev()
{
    int i, j;
    string digits;
    cout << "Type a string of 10 digits (0-9) without any spaces: ";
    cin >> digits;
    cout << "\n";
    assert(digits.length()==10);
    for(i=0;i<10;i++)
        assert(isdigit(digits[i]));
    for(i=0;i<5;i++)// 5 times, print the string of digits then its reverse, adding another space at the beginning of every line
    {
        for(j=0;j<i;j++)
        {
            cout << " ";
        }

        cout << digits << "    ";

        for(j=9;j>=0;j--)
        {
            cout << digits[j];
        }

        cout << "\n";
    }

}

void bigWords()
{
    int i;
    string word;
    char temp;
    ifstream file;
    file.open("lab1file.txt");
    if(file.is_open())
    {
        while(file >> word)//traverse file, saving every word
        {
            if(word.length()>=10)
            {
                for(i=0;i<(word.length());i++)//go through the word and save every alphabetical character
                {
                    if(isalpha(word[i]))
                    {
                        temp = toupper(word[i]);
                        cout << temp;
                    }
                }
                cout << "\n";
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file\n";
    }
    return;
}

void guessNumber()
{
    int i,flag = 1, guesses = 0,  num, guessedNums[20];  
    char check = 'f';   

    srand(time(NULL));

    cout << "Think of a number between 1 and 20\n";
    while(check != num)
    { 
        while(flag == 1)
        {
            flag = 0;
            num = (rand() % 20) + 1;
            for(i=0; i<guesses; i++)
            {
                if(num == guessedNums[i])
                {
                    flag == 1;
                }
            }
        }
        
        flag = 1;
        guessedNums[guesses]==num;
        
        cout << "Is your number " << num << "?\n";
        
        while ((check != 'y') && (check != 'n'))
        {
            cout << "Please guess 'y' or 'n'.\n"; 
            cin >> check;
        }

        
        guesses++;
        if(check == 'y')
        {
            cout << "I got it right in " << guesses << " guesses!\n";
            return;
        }
        else
        {
            cout << "Wrong! I'll Guess again.\n";
            check = 'f';
        }    
    }
}

int main()
{
    countIn();
    numRev();
    bigWords();
    guessNumber();
    return 0;
}