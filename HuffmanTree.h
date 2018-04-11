//HuffmanTree.h
#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>

namespace PDYSHA009
{
    class HuffmanTree
    {
        public:
    
        //pointer to store root node of built tree when this is lost whole tree should destruct
        //important to tell class of HuffmanNode
        std::shared_ptr<class HuffmanNode> root;
        
        std::unordered_map<char, int> FrequencyTable;
        std::map<char,std::string> CodeTable;

        HuffmanTree();//default constructor
        
        ~HuffmanTree();//destructor
        
        void buildFrequencyTable(std::string inputFile);
        void generateTree(std::unordered_map<char,int> u_map);
        void outputData(std::string outputFile,std::string inputFile);
        
        
    };
    
    class HuffmanNode
    {
        public:
        
        char data;
        int freq;
        
        std::shared_ptr<HuffmanNode> left;
        std::shared_ptr<HuffmanNode> right;
        
        //constructor
        HuffmanNode(char data, int freq);
        
        //default constructor
        HuffmanNode();
        
        //destructor
        ~HuffmanNode();
        
        //copy constructor
        HuffmanNode(const HuffmanNode& other);
        
        //move constructor
        HuffmanNode(HuffmanNode&& other);
        
        //assignment operator
        HuffmanNode& operator=(const HuffmanNode& other);
        
        
        
        
        
    };

}

#endif
