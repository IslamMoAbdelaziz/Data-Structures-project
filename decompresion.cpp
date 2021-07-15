#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;


string encoding(string str)
{
    string x = "";
    int length = str.length();
    for (int i = 0; i < length; i++) {

        int count = 1;
        while (i < length - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }

           x += to_string(count)+ str[i];      // character and its count


    }

    return x ;
}
 //...........................................................................................................................................

 string decoding(string str)
{
    string x = "",e;
    int length = str.length();
    for (int i = 0; i < length; i+=2) {
           e = str[i];
         for (int j = 0; j < stoi(e); j++) {
                x +=  str[i+1]  ;
         }

    }

    return x ;
}






//............................................................................................................................................

int main () {
    int i ;
  fstream myfile, encodingfile;
  string s,val ;
  encodingfile.open ("D:\\3rd CSE ASU - 2022 2nd term\\DS\\encoding");
  myfile.open ("D:\\3rd CSE ASU - 2022 2nd term\\DS\\decoding.xml");

 while(getline(encodingfile,s))
 {
  val = decoding(s);

myfile << val << endl;
    }

  return 0;
}
