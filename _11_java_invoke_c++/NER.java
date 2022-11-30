public class NER{
    static{
        System.load("/HOME/scz5862/run/java/java-invoke-cpp/src/ner.so");
    }
    public native String decode(String input);
}