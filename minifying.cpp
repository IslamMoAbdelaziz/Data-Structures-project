#include <iostream>
#include <string>
#include <fstream>
#include <stack>


using namespace std;

string minifying(fstream& myfile)
{
    string input;
    getline(myfile, input);
    string output="";

    for(int i=0; i<input.length(); i++)
    {
        if(input[i-1]==' ' && input[i]==' ')
            continue;
        else if (input[i-1]=='\n' && input [i]=='\n')
            continue;
        else
            output.push_back(input[i]);
    }
    return output;
}
