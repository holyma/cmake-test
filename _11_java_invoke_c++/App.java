public class App {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
        NER ner = new NER();
        ner.decode("hello");
    }
}
