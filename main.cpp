//main.cpp
#include "HuffmanTree.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include <queue>


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

void HuffmanTree::outputData(std::string outputFile)
{
    
    ofstream outFile;
    outFile.open(outputFile+".hdr");
    //write header
        map<char,string> n_map = this->CodeTable;
        map<char,string>::iterator it2;
        outFile<<"Field count: "<<n_map.size()<<"\n"<<endl;
        for(it2=n_map.begin();it2!=n_map.end();++it2)
            {
                if((it2->first)!='\n')
                    outFile<<it2->first<<" :"<<it2->second<<endl;
                else
                    outFile<<"\\n"<<":"<<it2->second<<endl;
            }
    outFile.close();
    cout<<outputFile<<".hdr Header file created"<<endl;
    //make binary file
}

//---------------------------------------------------------------------------------------{
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
                if(it==m.end())
                {
                    int c=count(line.begin(),line.end(),line[i]);//returns the occurances of line[i] in the range
                    m.insert(pair<char,int>(line[i],c));//adds the key and count of occurance to the unordered_map
                }
                i++;
            }
        
        inFile.close();//when finished with file reader to prevent memory leaks
        HuffmanTree::FrequencyTable = m;//assigning value to the FrequencyTable member variable
    }
}
//---------------------------------------------------------------------------------------}

//======================================================================================={

struct compare {
 
        bool operator()(const HuffmanNode& l, const HuffmanNode& r)
        {
            return (l.freq > r.freq);
        }
    };
    
void getCodes(const HuffmanNode& root, string str, class HuffmanTree *h)
{
    
    if(!root.left && !root.right)
    {
        h->CodeTable.insert(pair<char,string>(root.data,str));
    }
 
    else
    {    
        if(root.left)
            {getCodes(*root.left, str + "0",h);}
        if(root.right)
        {getCodes(*root.right, str + "1",h);}
    }
    
}//end of printCodes()

void HuffmanTree::generateTree(unordered_map<char,int> u_map)
{
    cout<<"generateTree"<<endl;
    
    class HuffmamnNode;
    /*shared_ptr<HuffmanNode> left = nullptr;
    shared_ptr<HuffmanNode> right = nullptr;
    shared_ptr<HuffmanNode> top;*/
 
    // Create a min heap & inserts all characters of data[]
    priority_queue<HuffmanNode, vector<HuffmanNode>, compare> minHeap;
 
        unordered_map<char,int>::iterator it;
        for(it=u_map.begin();it!=u_map.end();++it)
            {
                HuffmanNode temp (it->first, it->second);
                minHeap.push(temp);//pushing values from map onto priority queue
            }
            //cout<<"Number of distinct characters: "<<minHeap.size()<<endl;
            
        while(minHeap.size() >1)
        {
            HuffmanNode left = minHeap.top();
            minHeap.pop();
            
            HuffmanNode right = minHeap.top();
            minHeap.pop();
            
            HuffmanNode top('$',(left.freq + right.freq));
            //top.left = shared_ptr<HuffmanNode>(new HuffmanNode(left.data,left.freq));
            //top.right = shared_ptr<HuffmanNode>(new HuffmanNode(right.data,right.freq));
            
            top.left = shared_ptr<HuffmanNode>(new HuffmanNode(left));
            top.right = shared_ptr<HuffmanNode>(new HuffmanNode(right));
            
            minHeap.push(top);
        }
        
        HuffmanNode root = minHeap.top();
        this->root = shared_ptr<HuffmanNode>(new HuffmanNode(root));
 
    
    // add huffman codes to CodeTable using
    // the Huffman tree built above
    //rootNode = minHeap.top();
    //cout<<"Root Node"<<rootNode->data<<endl;
    getCodes(root, "",this);
    
}

//=======================================================================================}

HuffmanNode::HuffmanNode(char data, int freq)//default constructor
{
    //cout<<"HuffmanNode() default constructor"<<endl;
    this->data = data;
    this->freq = freq;
    this->left=nullptr;
    this->right=nullptr;
}

HuffmanNode::~HuffmanNode()//default destructor
{
    //cout<<"HuffmanNode() destructor "<<this->data<<endl;
}


int main(int argc, char* argv[])
{

//test block
//===================================================
cout<<"\n"<<endl;
//shared_ptr<HuffmanNode> test(new HuffmanNode('a',0));

HuffmanTree newHuffmanTree;
//newHuffmanTree.root = test;

//cout<<newHuffmanTree.root->data<<endl;
newHuffmanTree.buildFrequencyTable(argv[1]);
newHuffmanTree.HuffmanTree::generateTree(newHuffmanTree.HuffmanTree::FrequencyTable);
newHuffmanTree.HuffmanTree::outputData(argv[2]);
//===================================================

//test that FrequencyTable is correct
    cout<<"\nFrequency Table:\n"<<endl;
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
            
//test that CodeTable is correct
    cout<<"char : Huffman Code\n"<<endl;
        map<char,string> n_map = newHuffmanTree.HuffmanTree::CodeTable;
        map<char,string>::iterator it2;
        for(it2=n_map.begin();it2!=n_map.end();++it2)
            {
                if((it2->first)!='\n')
                    cout<<it2->first<<" :"<<it2->second<<endl;
                else
                    cout<<"\\n"<<":"<<it2->second<<endl;
            }
            cout<<"\n"<<endl;          
//===================================================

return 0;
}
