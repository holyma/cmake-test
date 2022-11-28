#include "include/ner.h"

int main() {
  std::string label = "O O O O O O O O O O O B-geo I-geo O";
  std::string sentence = "They marched from the Houses of Parliament to a rally in Hyde Park .";

  // 当前目录为可执行文件目录
  std::string vocabPath = "../vocab/words.txt";
  std::string tagPath = "../vocab/tags.txt";
  std::string modelPath = "../pt/export-trace.pt";

  NER ner = NER(modelPath,vocabPath,tagPath);
  std::string hypo = ner.decode(sentence);

  std::cout<< hypo <<std::endl;
}
