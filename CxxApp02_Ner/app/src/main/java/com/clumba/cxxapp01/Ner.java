package com.clumba.cxxapp01;

public class Ner {

    static{
//        System.load("/HOME/scz5862/run/java/java-invoke-cpp/src/ner.so");
        System.loadLibrary("ner");
    }

    public native void init(String rootPath);
    public native String decode(String input);
}
