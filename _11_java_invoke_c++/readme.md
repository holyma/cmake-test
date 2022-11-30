# JAVA调用C++代码
1. 写JAVA调用类：NER.java
2. 使用 `javac  NER.java -h  .` 生成 `NER.h`
3. ` cp NER.h NER.cpp ` 填充.cpp函数实现
4. `.cpp` -> `.so/.a`
```sh
gcc -I "/HOME/scz5862/run/pkg/jdk1.8.0_333/include" -I "/HOME/scz5862/run/pkg/jdk1.8.0_333/include/linux" -shared -o ner.so NER.cpp -fPIC

```
5. 在java中 load & 使用
