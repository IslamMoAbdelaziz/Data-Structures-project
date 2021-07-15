#include<string>
#include<iostream>
#include<stack>
#include<fstream>

using namespace std;

int main() {
	fstream infile;
	fstream ofile;
	string line,temp, tag, b ,open ,space1 , space2;
	int index1 ,index2,index3,current=0, old=0, comment=0;
	stack <string> st;
	infile.open("in.txt");
	while (!infile.eof())
	{
	   
		 for (int i = 0; i < st.size(); i++)
		 {
			 space1 += "    ";
		 }
		getline(infile, line);
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
					space2 += "    ";
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
		ofile.open("out.txt", fstream::app);
		ofile << line << endl;
		ofile.close();
		old=current;
		comment = 0;
	
		   
		

	}
	
	return 0;
	 
}