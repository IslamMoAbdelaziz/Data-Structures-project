//#include <iostream>
//#include <fstream>
//#include <stack>
//#include <vector>
//#include <queue>
//#define max 100
//using namespace std;
//  fstream  myjson;
//  stack<string> parentheses ;
//  // queue<int> space ;
//   int a = 1;
  
// class TreeNode {
//public:
//int level ;
//string value , key;
//int chN ;
//TreeNode* child[max] ;
////vector <TreeNode *> child ;
//TreeNode(string k , string v){value = v , key = k; chN=0 ;};

//   // friend class Tree ;
//};
////............................................................................................................................................................................................................................................
//class Tree {
//public:
//int height  ;
//TreeNode *root;
//Tree(TreeNode *p=nullptr)
//{this->root=p;       height = 0 ;};

//bool isEmpty(){return root == NULL;};
//   void printjson (TreeNode * po ){
//      // space.push(a);
//      for(int i =1; i<= po->level  ;i++){
//          myjson << "    ";
//          }
//          if((po->value == "{") || (po->value == "["))
//      { myjson <<" "<< '"'<<po->key<<'"'<<':'<<" "<<po->value<<endl;}
//       else {myjson <<" "<< '"'<<po->key<<'"'<<':'<<" "<<'"'<<po->value<<'"'<<','<<endl;}
//       //cout <<po->key<<'"'<<':'<<" "<<po->value<<"  "<<po->level<<endl;
      
//        parentheses.push(po->value);
//      // if( po->chN==0){return ;}
//          // space.front()++;
//          //space.push(space.front());
//        for(int i =1; i<= po->chN ;i++){
//         printjson(po->child[i]);
//           }
//         //  space.pop();
          
//          if(parentheses.top()=="[")
//              {
//                  for(int i =1; i<= (po->level + 3  )  ;i++){
//                       myjson << "  ";
//              }
//                  myjson<< "]"<<endl;
//              parentheses.pop();
//              }
//        else  if(parentheses.top()=="{")
//              {
//                  for(int i =1; i<= (po->level + 3 ) ;i++){
//                   myjson << "  ";
//                }
//                  myjson<< "}"<<endl;
//              parentheses.pop();}
        
//        else{parentheses.pop();}
//        if( po->chN==0){return ;}
//       };

//    friend class  TreeNode;
//};

 
//int main () {
//    int level = 0 ;
//    int i ;
//    int addval = 1 ;
//    Tree tree  ;
//    TreeNode * p ;
//  fstream myfile;
//  //fstream myjson;
//  string s="",key="",val="" ;
//  stack<TreeNode *> stack ;
//  myjson.open("D:\\3rd CSE ASU - 2022 2nd term\\DS\\myjson.json");
//  myjson << "{"<<endl;
//  myfile.open ("D:\\3rd CSE ASU - 2022 2nd term\\DS\\sample.xml");
// bool  comment = false ;
 
//  line :  while(getline(myfile,s))
// {
      
     
//     for(int j =0; j<s.length();j++) {                    //...............................  comment start
//        if(s[j]=='<' && s[j+1]=='!'){
//                   comment = true ;
//                    //goto line ;
//                    break ;
//                    }
//     }
     
//     for(int j =0;j<s.length();j++) {                                //...............................  comment end
//         if(s[j]=='-' && s[j+1]=='>'){
//         comment = false ;
//            goto line ;
//             }
//         }
     
             
//     addval=3;
// for(int j =0;j<s.length();j++) {                                   // ............................... ...............................opening tag
//      int k=0;
//    if(s[j]=='<' &&  !comment ){
//      // key = "";     val = "";
//        if(s[j+1]!='?' && s[j+1]!='!'&& s[j+1]!='/'){
//              key = "";     val = "";
//              for( k =j+1; ( (s[k]!='>')&&(s[k]!=' ') ) ;k++)  {
//                      key += s[k];
//                  }
//            for( k ;  s[k]!='>' ;k++)  ;
//                  for( int z =k+1; ( s[z]!='<')&&(z < s.length() );z++)  {
//                  val += s[z];
//                  }
                 
//              /*  while (s[k+1]!='<')
//                     {
//                      val += s[k];
//                       k++;
//                      // cout<<val;
//                  }*/
//                  if(tree.isEmpty())
//                  {
//                      tree.root = new TreeNode(key,val);
//                      stack.push(tree.root);
//                      p = stack.top() ;
        
//                      p->level = level ;
//                  }else{
//                      level++;
//                   p = stack.top() ;
                   
//                   //p->child[i]->level = level ;
//                 //  cout << p->key<< "level = "<<level<<" "<<endl;
//                   (p->chN ) +=1 ;
//                   i = p -> chN ;
//                    //cout<<i ;
//                    p->child[i] = new TreeNode(key,val);
//                    p->child[i]->level = level ;
//                    tree.height = level ;
//                   // cout<<"  " <<tree.height <<"   ";
//               //  cout << p->child[i]->key<< "level = "<<level<<" "<<endl;
//                   stack.push(p->child[i]);
//                  }
//                //  myjson << '"'<<key<<'"'<<':'<<endl;
//                   }
//                   }
//                   }
//                   //............................................................................................................
//                   for(int j =0;j<s.length();j++) {
//                        if(  s[j]=='<'  ) { addval=2;  }
//                       }
//                       //cout <<stack.top()->value <<endl;
//                       //cout <<s <<endl;
//                       if(addval !=2 &&  !comment){  p->child[i]->value +=s;  addval=3; }
                       
//                   //........................................................................................................................
//                      for(int j =0;j<s.length();j++) {                                          //.................................... closing tag
//                  if(s[j]=='<' &&  !comment){
//                   if(s[j+1]=='/'){
//                      level-- ;
//                     stack.pop();
//                     break;
//                   /* for(int k =j+2; ( (s[k]!='>')&&(s[k]!=' ') ) ;k++)  {
//                      s1 += s[k];
//                  }
//               if(stack.top()==s1){stack.pop();}
//               }
//                } */
 
//          }
//    }
//          }
// }
//// if (str.find(str2) != string::npos)

 
// while (!stack.empty()) {
//   //  cout<<stack.top()<<endl;
//        stack.pop();
//    }
//    //   m <= p->chN
    
//    p = tree.root ;
//    stack.push(p);
//    bool equal = true ;

    
      

//    while(!stack.empty()){
//        equal = true ;
      
//      for(int i =1; i<=p->chN ;i++){
//        if (p->child[1]->key !=p->child[i]->key)
//              { equal = false ;  }
//              }
//              stack.pop();
//               if(p->chN == 0);
//              else if(equal)
//                 {  p->value = "[" ;}
//                 else {p->value = "{" ;}
//                // cout <<endl<<p->key<< p->value ;
//           for(int i =1; i<=p->chN ;i++){
//           stack.push(p->child[i]);
//                              }
//                 p = stack.top();
//                }
                
//   //cout<<"  " <<tree.height <<"   ";
//  //cout<<endl<< tree.root->child[1]->child[4]->child[1]->key;
 
 
//   p = tree.root ;
//     tree.printjson(p);
// myjson << "}";
//  return 0;
//}
