public class NER{
    static{
        System.load("/HOME/scz5862/run/java/java-invoke-cpp/src/ner.so");
    }
    public native void init(String modelPath,String vocabPath,String tagPath);
    public native String decode(String input);

}