

#ifndef NER_H
#define NER_H

#include <torch/torch.h>
#include <torch/script.h>
#include <map>
#include <vector>
#include <string>

using namespace std;

class NER{
    public:
        NER(string modelPath,string vocabPath,string tagPath);
        string decode(string input);
    private:
        map<string,int> vocabs;
        map<string,int> tags;
        torch::jit::script::Module model;

        map<string,int> readFile(string filePath);
        vector<string> split(string str, string separator);
        torch::Tensor toIds(vector<string> sentences,map<string,int> vocab);

};


#endif