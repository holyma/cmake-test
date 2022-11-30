
#include "ner.h"

using namespace std;
/*
class NER{
    public:
        NER(string modelPath,string vocabPath,string tagPath);
        string decode(string input);
    private:
        map<string,int> vocab;
        map<string,int> tag;
        torch::jit::script::Module model;

        map<string,int> readFile(string filePath);
        vector<string> split(string str, string separator);
        torch::Tensor toIds(vector<string> sentences,map<string,int> vocab);

};
*/

NER::NER(string modelPath,string vocabPath,string tagPath){
    // 读取词表，加载模型
    vocabs = readFile(vocabPath);
    model = torch::jit::load(modelPath);
    tags = readFile(tagPath);

}

string NER::decode(string sentence){

    // 文本-> 分词 -> ID Tensor -> vector
    std::vector<std::string> sentences = split(sentence," ");
    torch::Tensor sentencesIds = toIds(sentences,vocabs); // {1:100}
    std::vector<torch::jit::IValue> inputVector;
    inputVector.push_back(sentencesIds);
    int sentencesLength = sentences.size();

    // 解码
    torch::Tensor result = model.forward(inputVector).toTensor(); // {100,vocab_size}
    result = torch::argmax(result,1); // {100}
    torch::Tensor realResult = result.index({torch::indexing::Slice(0,sentencesLength)}); // {实际长度}

    // 结果转换
    std::vector<std::string> textVector;
    std::string text = "";
    for(int i=0;i<sentencesLength;i++){
        for(auto it = tags.begin();it!=tags.end();it++){
            // std::cout<<realResult[i].item().toInt();
            int cur = realResult[i].item().toInt();
            if ((it->second) == cur){
                cout<< it->first;    
                textVector.push_back(it->first);
                text.append(it->first + " ");
                break;
            }
        }
        // std::cout << "输出文本" << textVector << std::endl;
    }
    // std::cout<< textVector<< std::endl;

    return text;
}

map<string,int> NER::readFile(string filePath){
    
    map<string,int> dict;

    ifstream file;
    file.open(filePath,ios_base::in);
    if(!file.is_open()){
        cout<< "file open failed"<<endl;
    }

    string s;
    int i = 0;
    while(getline(file,s)){
        dict.insert({s,i++});
    }
    file.close();


    return dict;
}

/*
    teste example:
        std::string str = "O O O O O O O O O O O B-geo I-geo O";
        std::string separator = " ";
        vector<string> splitStr = split(str, separator);
*/
vector<string> NER::split(string str, string separator){

    int pos ;
    vector<string> result;
    str += separator;
    int length = str.size();

    for (int i=0;i<length;i++){
        pos = str.find(separator,i);
        if(pos<length){
            string s = str.substr(i,pos-i); //包头不包尾,(start,length)
            i = pos + separator.size()-1;
            
            result.push_back(s); // 添加到最后
        }
    }

    return result;
}

/*
    test example:
        vector<string> splitStr = {"hello","kun","ming"};
        map<string,int> vocab= {{"O",0},{"hello",1},{"kun",2},{"ming",3}};
        torch::Tensor ids = toIds(splitStr,vocab){        
*/
torch::Tensor NER::toIds(vector<string> sentences,map<string,int> vocab){

    vector<int> sentencesIds;
    for (vector<string>::iterator it = sentences.begin();it!=sentences.end();it++){
        sentencesIds.push_back(vocab[*it]);
    }

    // std::vector<int> sentencesIds = {1,2,3};
    // id转tensor:创建长度为maxLength的0tensor
    int maxLength = 100;
    torch::Tensor sentencesTensor = torch::zeros({1,maxLength}).to(torch::kLong);
    // std::cout << "句子空ID:" << sentencesTensor << std::endl;


    for(int i=0;i<sentencesIds.size();i++){
        sentencesTensor[0][i] = sentencesIds[i];
    }

    // std::cout<< "句子ID Tensor:" << sentencesTensor << std::endl;

    return sentencesTensor; // {1:100}

}
