//#include <iostream>
//#include <string>
//#include <fstream>
//#include <stack>


//using namespace std;

//int isBalanced(fstream& myfile) {
//    stack<string> seq;
//    string tag = "";
//    int tag_parse = 0;
//    int tag_closing = 0;
//    string line;

//    while (getline(myfile, line)) {
//        for (int i = 0; i < line.size(); i++) {
//            char a = line[i];

//            if (a == '<') {
//                if (line[i + 1] == '/') {
//                    i++;
//                    tag_closing = 1;
//                }
//                tag_parse = 1;
//            }

//            else if (a == '>') {
//                //stop parsing and check matching
//                if (tag != "") {
//                    string s = "";
//                    if (!seq.empty()) {
//                        s = seq.top();
//                        if (tag == s && tag_closing) seq.pop();
//                        else seq.push(tag);
//                    }
//                    else {
//                        seq.push(tag);
//                    }
//                }
//                tag_parse = 0;
//                tag_closing = 0;
//                tag = "";
//            }

//            else {
//                //parsing
//                if (a == '/' && line[i + 1] == '>') {
//                    tag_parse = 0;
//                    tag = "";
//                }
//                else if (tag_parse == 1) {
//                    if (a == ' ') tag_parse = 0;
//                    else {
//                        tag.push_back(a);
//                    }
//                }

//            }
//        }
//    }

//    if (seq.empty()) return 1;
//    return 0;
//}

//int main() {
//    fstream myfile;
//    myfile.open("test.xml");

//    string result = "";
//    if (isBalanced(myfile)) result += ("Yes\n"); else { result += ("No\n"); }

//    result = result.substr(0, result.size() - 1);
//    cout << result;
//    return 0;
//}
