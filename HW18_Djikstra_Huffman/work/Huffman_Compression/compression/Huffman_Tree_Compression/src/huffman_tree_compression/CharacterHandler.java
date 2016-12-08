/*
 * Get File Input
 */
package huffman_tree_compression;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.Charset;
import java.util.ArrayList;

public class CharacterHandler {
    //Java 7 source level
    Charset encoding = Charset.defaultCharset();
    public static StringBuilder sb = new StringBuilder();
    public CharacterHandler(String filename) throws IOException{
        File file = new File(filename);
        handleFile(file, encoding);
    }

    private static void handleFile(File file, Charset encoding)
            throws IOException {
        try (InputStream in = new FileInputStream(file);
             Reader reader = new InputStreamReader(in, encoding);
             // buffer for efficiency
             Reader buffer = new BufferedReader(reader)) {
            handleCharacters(buffer);
        }
    }

    private static void handleCharacters(Reader reader)
            throws IOException {
        int r;
        while ((r = reader.read()) != -1) {
            char ch = (char) r;
            String s = Character.toString(ch);
            sb.append(s);
            //System.out.println("Do something with " + ch);
        }
    }
}
