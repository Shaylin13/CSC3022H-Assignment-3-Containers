//main.cpp
#include "HuffmanTree.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>


using namespace std;
using namespace PDYSHA009;

HuffmanTree::HuffmanTree()//default constructor
{
    cout<<"HuffmanTree() default constructor"<<endl;
}
HuffmanTree::~HuffmanTree()//default destructor
{
    cout<<"HuffmanTree() destructor"<<endl;
    this->root = nullptr;
}

void HuffmanTree::buildFrequencyTable(string inputFile)
{
    
    unordered_map<char,int> m;
    
    //read file/create ifstream
    ifstream inFile(inputFile);//Tries to open file user specified
    if(inFile.fail())//if there is a problem opening the file
    {
        cout<<"Failed to open file"<<endl;
        return;
    }
    else//if the file is opened successfully
    {
        cout<<"successfully opened file :"<<inputFile<<"\n"<<endl;
        
        //store all text in buffer to be analysed as one input instead of line by line, take into consideration \n as char
        stringstream buffer;
        buffer<<inFile.rdbuf();
        string line(buffer.str());
            
        //counting the occurances of chars and adding to unordered_map
        int i=0;
        unordered_map<char,int>::iterator it;
            while(line[i]!='\0')
            {
                it=m.find(line[i]);
                if(it==m.end()/*&&line[i]!='\n'*/)
                {
                    int c=count(line.begin(),line.end(),line[i]);//returns the occurances of line[i] in the range
                    m.insert(pair<char,int>(line[i],c));//adds the key and count of occurance to the unordered_map
                }
                /*if(line[i]=='\n')//this is if you want to represent "\n"/space with @, not neccessary
                    m['@']+=1; //for \n*/
                i++;
            }
        
        inFile.close();//when finished with file reader to prevent memory leaks
        HuffmanTree::FrequencyTable = m;//assigning value to the FrequencyTable member variable
    }
}

HuffmanNode::HuffmanNode(char data, int freq)//default constructor
{
    cout<<"HuffmanNode() default constructor"<<endl;
    this->data = data;
    this->freq = freq;
}
HuffmanNode::~HuffmanNode()//default destructor
{
    cout<<"HuffmanNode() destructor "<<this->data<<endl;
}


int main(int argc, char* argv[])
{

//test block
//===================================================
cout<<"\n"<<endl;
shared_ptr<HuffmanNode> test(new HuffmanNode('a',0));

HuffmanTree newHuffmanTree;
newHuffmanTree.root = test;

//cout<<newHuffmanTree.root->data<<endl;
newHuffmanTree.buildFrequencyTable(argv[1]);
//===================================================

//test that FrequencyTable is correct================
    cout<<"Frequency Table:\n"<<endl;
    cout<<"char : Frequency\n"<<endl;
        unordered_map<char,int> u_map = newHuffmanTree.HuffmanTree::FrequencyTable;
        unordered_map<char,int>::iterator it;
        for(it=u_map.begin();it!=u_map.end();++it)
            {
                if((it->first)!='\n')
                    cout<<it->first<<" :"<<it->second<<endl;
                else
                    cout<<"\\n"<<":"<<it->second<<endl;
            }
            cout<<"\n"<<endl;
//===================================================

return 0;
}
