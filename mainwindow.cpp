#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "format.cpp"
#include <string>
#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <queue>
#define max 100
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

}


void MainWindow::on_actionSolve_Errors_triggered()
{
    QString str = ui->textEdit->toPlainText();
    string ostr = "";
    QTextStream myfile(&str);
//    QTextStream out(&ostr);



    stack<string> seq;
    string tag = "";
    int tag_parse = 0;
    int tag_closing = 0;
    string line;

    while (!myfile.atEnd()) {
        QString qline = myfile.readLine();
        string line = qline.toLocal8Bit().constData();

        for (int i = 0; i < line.size(); i++) {
            char a = line[i];
            if (!tag_parse){
                ostr.push_back(a);
            }

            if (a == '<') {
                if (line[i + 1] != '?' && line[i + 1] != '-'){
                    if (line[i + 1] == '/') {
                        i++;
                        ostr.push_back(line[i + 1]);
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
                //stop parsing and check matching
                if (tag != "") {
                    string s = "";
                    if (!seq.empty()) {
                        s = seq.top();
                        if (tag == s && tag_closing) {
                            seq.pop();
                            ostr+= tag.substr(1,tag.length()) + "/>\n";
                        }
                        else if (tag != s && tag_closing) {
                            ostr.erase (ostr.length()-1, ostr.length());
                            ostr+= s.substr(0,s.length()) + "/>\n";
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
        }
    }

    while (!seq.empty()) {
        ostr+= "<"+seq.top() + "/>\n";
        seq.pop();
    }

         QString qstr = QString::fromStdString(ostr);
         ui->textEdit->setText(qstr);

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

      for(int i =1; i<=p->chN ;i++){
        if (p->child[1]->key !=p->child[i]->key)
              { equal = false ;  }
              }
              stack.pop();
               if(p->chN == 0);
              else if(equal)
                 {  p->value = "[" ;}
                 else {p->value = "{" ;}
                // cout <<endl<<p->key<< p->value ;
           for(int i =1; i<=p->chN ;i++){
           stack.push(p->child[i]);
                              }
                 p = stack.top();
                }

   //cout<<"  " <<tree.height <<"   ";
  //cout<<endl<< tree.root->child[1]->child[4]->child[1]->key;


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
    string str = qstr.toLocal8Bit().constData();
    QString output = "";
    string x = "";
    int length = str.length();
    for (int i = 0; i < length; i++) {

        int count = 1;
        while (i < length - 1 && str[i] == str[i + 1]) {
            count++;
            i++;
        }

           x += to_string(count);
           x.push_back(str[i]);      // character and its count


    }

             QString q = QString::fromStdString(x);

             ui->textEdit->setText(q);


}

