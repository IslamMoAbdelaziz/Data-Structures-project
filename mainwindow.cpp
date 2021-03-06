#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <queue>
#define max 100
//#include <unordered_map>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

    // Global referencing the current file that we are clearing
        currentFile.clear();

        // Clear the textEdit widget buffer
        ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the currentFile name
    currentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the textEdit widget
    ui->textEdit->setText(text);

    // Close the file
    file.close();

}


void MainWindow::on_actionSave_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    // Opens a dialog for saving a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    currentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Copy text in the textEdit widget and convert to plain text
    QString text = ui->textEdit->toPlainText();

    // Output to file
    out << text;

    // Close the file
    file.close();

}


void MainWindow::on_actionExit_triggered()
{

    QApplication::quit();

}


void MainWindow::on_actionCut_triggered()
{
        ui->textEdit->cut();

}


void MainWindow::on_actionCopy_triggered()
{

        ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
        ui->textEdit->paste();

}


void MainWindow::on_actionUndo_triggered()
{

        ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{

        ui->textEdit->redo();
}




void MainWindow::on_actionCheck_Consistency_triggered()
{
    QString qin = ui->textEdit->toPlainText();
    string in = qin.toLocal8Bit().constData();
    string out;

    QTextCharFormat fmt;
    fmt.setBackground(Qt::darkRed);

    QTextCursor cursor = ui->textEdit->textCursor();

    char c, a, b;
    int hold = 0, start = 0, cut_length = 0, flag = 0;

    int begin = 0;
    int end = 0;

    for(int j = 0; j < in.length(); j++){
        c = in[j];
        out.push_back(c);

        flag = 0;

        if(c=='>'){
            hold = j;
            start = 1;
        }
        if(c=='<'&& in[j+1]!='/' && start == 1 ){
            cut_length = j - hold;
            if (out.substr(out.length()-cut_length, 1)=="\n") a = 1; else a = 0;
            if (out.substr(out.length(), 1)=="\n") {if (a == 1) b = 0; else b = 1;} else b = 0;
            if (out.length()-cut_length +a - (out.length() -1 -b) > 0){
                begin = out.length()-cut_length +a;
                end =  out.length() -1 -b;

                flag=0;
                for(int h = begin; h<end; h++){
                    if (in[h] != ' ') {
                        flag = 1;
                        break;
                    }
                }
                int count = 0;
                for(int h = end-1; h>= begin; h--){
                    if (in[h] != ' ') {
                        break;
                    }else {
                        count++;
                    }
                }
                end -= count;

                if (flag){
                    cursor.setPosition(begin, QTextCursor::MoveAnchor);
                    cursor.setPosition(end, QTextCursor::KeepAnchor);
                    cursor.setCharFormat(fmt);
                }


            }
            if (out.substr(out.length()-1, 1)!="<") { out.push_back('\n'); out.push_back(c);}

            start = 0;
        }else if(c=='<'&& in[j+1]=='/'){
            start = 0;
        }
    }


    /////////////////////////////////////////////////////

    QString str = ui->textEdit->toPlainText();
    string ostr = "";
    QTextStream myfile(&str);
//    QTextStream out(&ostr);

    begin = 0;
    end = 0;

    cursor.setPosition(begin, QTextCursor::MoveAnchor);
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);

    stack<string> seq;
    string tag = "";
    int tag_parse = 0;
    int tag_closing = 0;
    string line;
    int line_counter = -1;
    int counter = 0;

    while (!myfile.atEnd()) {

        line_counter++;
//        cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, line_counter);
//        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
//        ui->textEdit->setTextCursor(cursor); // The line to add


        QString qline = myfile.readLine();
        string line = qline.toLocal8Bit().constData();
//        begin = 0;
//        end = 0;


        for (int i = 0; i < line.size(); i++) {
            char a = line[i];
            if (!tag_parse){
                ostr.push_back(a);
            }

            if (a == '<') {
                if (line[i + 1] != '?' && line[i + 1] != '-'){
                    if (line[i + 1] == '/') {
                        i++;
                        counter++;
                        tag_closing = 1;
                    }
                    tag_parse = 1;
                }else{
                    tag_parse = 0;
//                    ostr.erase (0, 1);
//                    ostr.push_back(line[i]);
                }

            }

            else if (a == '>') {
                //stop parsing and check matching
                if (tag != "") {
                    string s = "";
                    if (!seq.empty()) {
                        s = seq.top();
                        if (tag == s && tag_closing) {
                            seq.pop();
//                            ostr+= tag.substr(1,tag.length()) + "/>\n";
                            begin = 0;
                            end = 0;
                        }
                        else if (tag != s && tag_closing) {
//                            ostr.erase (ostr.length()-1, ostr.length());
//                            ostr+= s.substr(0,s.length()) + "/>\n";
                            seq.pop();
                            end = counter +3 + tag.length();
                            begin = counter + 2;
//                            cursor.movePosition(QTextCursor::, QTextCursor::MoveAnchor, begin);
//                            cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, end);
//                            cursor.setCharFormat(fmt);
                        }
                        else {
                            seq.push(tag);
//                            ostr+= tag + ">";
                        }
                    }
                    else {
                        seq.push(tag);
//                        ostr+= tag + ">";
                    }
                }
                tag_parse = 0;
                tag_closing = 0;
                tag = "";
            }

            else {
                //parsing
                if (a == '/' && line[i + 1] == '>') {
                    tag_parse = 0;
                    tag = "";
                }
                else if (tag_parse == 1) {
                    if (a == ' ') tag_parse = 0;
                    else {
                        tag.push_back(a);

                    }
                }

            }
            counter ++;
        }
        cursor.setPosition(begin, QTextCursor::MoveAnchor);
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);

    }

}


void MainWindow::on_actionSolve_Errors_triggered()
{

    QString qin = ui->textEdit->toPlainText();
    string in = qin.toLocal8Bit().constData();
    string out;

    QTextCharFormat fmt;
    fmt.setBackground(QColor(35,38,41,255));

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(in.length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);

    char c, a, b;
    int hold = 0, start = 0, cut_length = 0;
    for(int j = 0; j < in.length(); j++){
        c = in[j];
        out.push_back(c);

        if(c=='>'){
            hold = j;
            start = 1;
        }
        if(c=='<'&& in[j+1]!='/' && start == 1 ){
            cut_length = j - hold;
            if (out.substr(out.length()-cut_length, 1)=="\n") a = 1; else a = 0;
            if (out.substr(out.length(), 1)=="\n") {if (a == 1) b = 0; else b = 1;} else b = 0;
            if (out.length()-cut_length +a - (out.length() -1 -b) > 0)
                out.erase (out.length()-cut_length +a, out.length() -1 -b);
            if (out.substr(out.length()-1, 1)!="<") { out.push_back('\n'); out.push_back(c);}

            start = 0;
        }else if(c=='<'&& in[j+1]=='/'){
            start = 0;
        }
    }
    QString qout = QString::fromStdString(out);
    ui->textEdit->setText(qout);


    /////////////////////////////////////

    QString str = ui->textEdit->toPlainText();
    string ostr = "";
    QTextStream myfile(&str);
//    QTextStream out(&ostr);



    stack<string> seq;
    string tag = "";
    int tag_parse = 0;
    int tag_closing = 0;
    string line;
    int counter = 0;

    while (!myfile.atEnd()) {
        QString qline = myfile.readLine();
        string line = qline.toLocal8Bit().constData();

        for (int i = 0; i < line.size(); i++) {
            char a = line[i];
            if (!tag_parse){
                ostr.push_back(a);
                counter ++;
            }

            if (a == '<') {
                if (line[i + 1] != '?' && line[i + 1] != '-'){
                    if (line[i + 1] == '/') {
                        i++;
                        counter ++;
                        ostr.push_back('/');ostr.push_back(line[i + 1]);
                        tag_closing = 1;
                    }
                    tag_parse = 1;
                }else{
                    tag_parse = 0;
                    ostr.erase (0, 1);
                    ostr.push_back(line[i]);
                }

            }

            else if (a == '>') {
//                hold = past_hold;
//                past_hold = counter;
                //stop parsing and check matching
                if (tag != "") {
                    string s = "";
                    if (!seq.empty()) {
                        s = seq.top();
                        if (tag == s && tag_closing) {
                            seq.pop();
                            ostr+= tag.substr(1,tag.length()) + ">\n";

                        }
                        else if (tag != s && tag_closing) {
                            ostr.erase (ostr.length()-1, ostr.length());
                            ostr+= s.substr(0,s.length()) + ">\n";
                            seq.pop();
                        }
                        else {
                            seq.push(tag);
                            ostr+= tag + ">";
                        }
                    }
                    else {
                        seq.push(tag);
                        ostr+= tag + ">";
                    }
                }
                tag_parse = 0;
                tag_closing = 0;
                tag = "";
//                if ( line[i + 1] != '\n') ostr+= "\n";
            }

            else {
                //parsing
                if (a == '/' && line[i + 1] == '>') {
                    tag_parse = 0;
                    tag = "";
                }
                else if (tag_parse == 1) {
                    if (a == ' ') tag_parse = 0;
                    else {
                        tag.push_back(a);
                    }
                }

            }
            counter ++;
        }
    }

    while (!seq.empty()) {
        ostr+= "</"+seq.top() + ">\n";
        seq.pop();
    }

         QString qstr = QString::fromStdString(ostr);
         ui->textEdit->setText(qstr);
      //   seq.erase

}


void MainWindow::on_actionFormat_Prettify_triggered()
{

////    QFile file("infile");

    QString text = ui->textEdit->toPlainText();
    QString out = "";
    QTextStream str(&text);
    QTextStream ostr(&out);

    string line,temp, tag, b ,open;
    string space="       ";
    string space1 = "";
    string space2 = "";
    int index1 ,index2,index3,current=0, old=0, comment=0;
    stack <string> st;
    while (!str.atEnd())
    {

         for (int i = 0; i < st.size(); i++)
         {
             space1 = space1 + space;
         }
        QString qline = str.readLine();
        string line = qline.toLocal8Bit().constData();
        temp = line;
        while (1)
        {
            index1 = temp.find("<");

            if (index1 == -1)
                break;

            index2 = temp.find(">");
            tag = temp.substr(index1+1, index2 - index1-1 );
            index3 = temp.find('/');
            if (index3 + 1 == index2)
            {
                comment = 1;
                break;
            }
            index3 = temp.find(" ");
            if ((index3 != -1) && (index3<index2))
            {
                tag = temp.substr(index1 + 1, index3 - index1 - 1);
            }
            index1 = tag.find("?");
            if (index1 != -1)
            {
                comment = 1;
                break;
            }
            index1 = tag.find("!");
            if (index1 != -1)
            {
                comment = 1;
                break;
            }
            index1 = tag.find("/");
            if (index1 != -1)
            {
                //pop code
                tag = tag.substr(1, tag.size() - 1);
                open = st.top();
                /*if (0!=tag.compare(open))
                {
                    break;
                }*/
                st.pop();

            }
            else if (index1 == -1)
            {
                st.push(tag);

            }
            temp.erase(0, index2 + 1);
        }

        current = st.size();
        if (comment != 1)
        {

            if (old > current)
            {
                for (int i = 0; i < st.size(); i++)
                {
                    space2 = space2 + space;
                }
                line = space2 + line;
            }
            else
            {
                line = space1 + line;
            }
        }
        else
            line = space1 + line;
        space2 = "";
        space1 = "";

        // Interface for reading text
        qline = QString::fromStdString(line);
        ostr << qline << "\n";

        old=current;
        comment = 0;




    }


    // Put the text in the textEdit widget
    ui->textEdit->setText(out);

}



//Converting to JSON

QString out = "{";
QTextStream myjson(&out);
stack<string> parentheses ;

QString qkey;
QString qvalue;
// queue<int> space ;
 int a = 1;

class TreeNode {
public:
int level ;
string value , key;
int chN ;
TreeNode* child[max] ;
//vector <TreeNode *> child ;
TreeNode(string k , string v){value = v , key = k; chN=0 ;};

 // friend class Tree ;
};
//............................................................................................................................................................................................................................................
class Tree {
public:
int height  ;
TreeNode *root;
Tree(TreeNode *p=nullptr)
{this->root=p;       height = 0 ;};

bool isEmpty(){return root == NULL;};
 void printjson (TreeNode * po ){
    // space.push(a);
    for(int i =1; i<= po->level  ;i++){
        myjson << "    ";
        }
        if((po->value == "{") || (po->value == "["))
    {       qkey = QString::fromStdString(po->key);
            qvalue = QString::fromStdString(po->value);
            myjson <<" "<< '"'<<qkey<<'"'<<':'<<" "<<qvalue<<"\n";}
     else {  qkey = QString::fromStdString(po->key);
            qvalue = QString::fromStdString(po->value);
            myjson <<" "<< '"'<<qkey<<'"'<<':'<<" "<<'"'<<qvalue<<'"'<<','<<"\n";}
     //cout <<po->key<<'"'<<':'<<" "<<po->value<<"  "<<po->level<<endl;

      parentheses.push(po->value);
    // if( po->chN==0){return ;}
        // space.front()++;
        //space.push(space.front());
      for(int i =1; i<= po->chN ;i++){
       printjson(po->child[i]);
         }
       //  space.pop();

        if(parentheses.top()=="[")
            {
                for(int i =1; i<= (po->level + 3  )  ;i++){
                     myjson << "  ";
            }
                myjson<< "]"<<"\n";
            parentheses.pop();
            }
      else  if(parentheses.top()=="{")
            {
                for(int i =1; i<= (po->level + 3 ) ;i++){
                 myjson << "  ";
              }
                myjson<< "}"<<"\n";
            parentheses.pop();}

      else{parentheses.pop();}
      if( po->chN==0){return ;}
     };

  friend class  TreeNode;
};




void MainWindow::on_actionConvert_to_JSON_triggered()
{

    int level = 0 ;
    int i ;
    int addval = 1 ;
    Tree tree  ;
    TreeNode * p ;

    QString text = ui->textEdit->toPlainText();
    QTextStream myfile(&text);


//  fstream myfile;
  //fstream myjson;
  string s="",key="",val="" ;
  stack<TreeNode *> stack ;
//  myjson.open("D:\\3rd CSE ASU - 2022 2nd term\\DS\\myjson.json");
//  myjson << "{"<<endl;
//  myfile.open ("D:\\3rd CSE ASU - 2022 2nd term\\DS\\sample.xml");
 bool  comment = false ;


 QString qline;
 string line;
  xline :  while(!myfile.atEnd())
 {
     qline = myfile.readLine();
     line = qline.toLocal8Bit().constData();
     s = line;


     for(int j =0; j<s.length();j++) {                    //...............................  comment start
        if(s[j]=='<' && s[j+1]=='!'){
                   comment = true ;
                    //goto line ;
                    break ;
                    }
     }

     for(int j =0;j<s.length();j++) {                                //...............................  comment end
         if(s[j]=='-' && s[j+1]=='>'){
         comment = false ;
            goto xline ;
             }
         }


     addval=3;
 for(int j =0;j<s.length();j++) {                                   // ............................... ...............................opening tag
      int k=0;
    if(s[j]=='<' &&  !comment ){
      // key = "";     val = "";
        if(s[j+1]!='?' && s[j+1]!='!'&& s[j+1]!='/'){
              key = "";     val = "";
              for( k =j+1; ( (s[k]!='>')&&(s[k]!=' ') ) ;k++)  {
                      key += s[k];
                  }
            for( k ;  s[k]!='>' ;k++);
                  for( int z =k+1; ( s[z]!='<')&&(z < s.length() );z++)  {
                  val += s[z];
                  }

              /*  while (s[k+1]!='<')
                     {
                      val += s[k];
                       k++;
                      // cout<<val;
                  }*/
                  if(tree.isEmpty())
                  {
                      tree.root = new TreeNode(key,val);
                      stack.push(tree.root);
                      p = stack.top() ;

                      p->level = level ;
                  }else{
                      level++;
                   p = stack.top() ;

                   //p->child[i]->level = level ;
                 //  cout << p->key<< "level = "<<level<<" "<<endl;
                   (p->chN ) +=1 ;
                   i = p -> chN ;
                    //cout<<i ;
                    p->child[i] = new TreeNode(key,val);
                    p->child[i]->level = level ;
                    tree.height = level ;
                   // cout<<"  " <<tree.height <<"   ";
               //  cout << p->child[i]->key<< "level = "<<level<<" "<<endl;
                   stack.push(p->child[i]);
                  }
                //  myjson << '"'<<key<<'"'<<':'<<endl;
                   }
                   }
                   }
                   //............................................................................................................
                   for(int j =0;j<s.length();j++) {
                        if(  s[j]=='<'  ) { addval=2;  }
                       }
                       //cout <<stack.top()->value <<endl;
                       //cout <<s <<endl;
                       if(addval !=2 &&  !comment){  p->child[i]->value +=s;  addval=3; }

                   //........................................................................................................................
                      for(int j =0;j<s.length();j++) {                                          //.................................... closing tag
                  if(s[j]=='<' &&  !comment){
                   if(s[j+1]=='/'){
                      level-- ;
                     stack.pop();
                     break;
                   /* for(int k =j+2; ( (s[k]!='>')&&(s[k]!=' ') ) ;k++)  {
                      s1 += s[k];
                  }
               if(stack.top()==s1){stack.pop();}
               }
                } */

          }
    }
          }
 }
// if (str.find(str2) != string::npos)


 while (!stack.empty()) {
   //  cout<<stack.top()<<endl;
        stack.pop();
    }
    //   m <= p->chN

    p = tree.root ;
    stack.push(p);
    bool equal = true ;




    while(!stack.empty()){
            equal = true ;

          for(int i =1; i<= p->chN ;i++){

            if (p->child[1]->key != p->child[i]->key)
                  { equal = false ;  }
                  }
                  stack.pop();
                  for(int i =1; i<= p->chN ;i++){
               stack.push(p->child[i]);
                                  }

                   if(p->chN == 0);
                  else if(!equal || p->chN == 1)
                     {  p->value = "{" ;}
                     else {p->value = "[" ;}


                   if(!stack.empty()){  p = stack.top();}else{break ;}

                    }

   //cout<<"  " <<tree.height <<"   ";
  //cout<<endl<< tree.root->child[1]->child[4]->child[1]->key;


     out = "";
   p = tree.root ;
     tree.printjson(p);
 myjson << "}";
 ui->textEdit->setText(out);

}


void MainWindow::on_actionMinify_triggered()
{

    QString input = ui->textEdit->toPlainText();
    QString output = "";
//    QTextStream myfile(&input);
//    QTextStream ostr(&out);


        for(int i=0; i<input.length(); i++)
        {
            if(input[i]==' ' | (input[i]=='\n' && input[i+1]=='\n' && i+1<input.length()))
                continue;
            else
                output.push_back(input[i]);
        }

         ui->textEdit->setText(output);
}


void MainWindow::on_actionCompress_triggered()
{

    QString qstr = ui->textEdit->toPlainText();
    string s1 = qstr.toLocal8Bit().constData();
    string output = "";

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


    for(int i=0;i<output_code.size();i++)
    {
        output+= to_string(output_code[i])+" ";
    }

    QString qout = QString::fromStdString(output);

    ui->textEdit->setText(qout);



}


void MainWindow::on_actionDe_Compress_triggered()
{
    QString qstr = ui->textEdit->toPlainText();
    string input = qstr.toLocal8Bit().constData();
    string output = "";

    vector<int> op;
    string temp="";

    for(int i=0;i<input.size();i++)
    {
    if(input[i]==' ')
    {
    op.push_back( stoi(temp) );
    temp="";
    continue;
    }
    temp.push_back(input[i]);
    }
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
    output+= s;
    c = "";
    c += s[0];
    table[count] = table[old] + c;
    count++;
    old = n;
    }

    QString qout = QString::fromStdString(output);

    ui->textEdit->setText(qout);

}

