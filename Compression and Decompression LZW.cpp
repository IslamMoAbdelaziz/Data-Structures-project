#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

string Compression(string s1)
{
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    output_code.push_back(table[p]);

    string output="";

    for(int i=0;output_code.size();i++)
    {
        output += to_string(output_code[i])+" ";
    }
    return output;
}

string Decompression(string input)
{
    vector<int> op;
    string temp="";
    for(int i=0;i<input.size();i++)
    {
        if(input[i]==" ")
        {
            op.push_back( stoi(temp) );
            temp="";
            continue;
        }
        temp.push_back(input[i]);
    }

    string output="";

    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    output += s;
    int count = 256;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        output += s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    return output;
}

int main()
{
    fstream myfile;
	myfile.open("test.xml");
    string s;
    getline(myfile, s);

    string Compressed = Compression(s);
    string Decompressed = Decompression(Compressed);
}
