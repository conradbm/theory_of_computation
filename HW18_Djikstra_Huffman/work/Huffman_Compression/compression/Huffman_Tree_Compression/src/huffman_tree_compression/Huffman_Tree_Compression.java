package huffman_tree_compression;
import javax.swing.JTree;
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.function.Consumer;

public class Huffman_Tree_Compression {
    public static Node root;
    public static Node tempRoot;
    
    public static ArrayList<Node> nodeList = new ArrayList<Node>();
    public static ArrayList<Character> charList = new ArrayList<Character>();
    public static ArrayList<Integer> freqList = new ArrayList<Integer>();
    public static void main(String[] args) throws IOException {
        
        Node n = new Node("a","33");
        //Tree<Node> tree1 = new Tree<Node>(n);
        Node n2 = new Node("b","44");
        
        CharacterHandler charHandler = new CharacterHandler("input.txt");
        String fileString = charHandler.sb.toString();
        System.out.println(fileString);
        //int count = fileString.length() - fileString.replace("a", "").length();
        for(int i = 0; i < fileString.length(); i++){
            if(!charList.contains(fileString.charAt(i))){
               charList.add(fileString.charAt(i));
               int count = fileString.length() - fileString.replace(Character.toString(fileString.charAt(i)), "").length();
               freqList.add(count);

            }
        }
        
        // Set up all the correct nodes
        for(int i = 0; i < charList.size(); i++){
            System.out.println(charList.get(i)+":"+freqList.get(i));
            Node temp = new Node(Character.toString(charList.get(i)),
                                 Integer.toString(freqList.get(i)));
            nodeList.add(temp);
        }
        

        //You can use Collections.swap(List<?> list, int i, int j);

        System.out.println("BEFORE SWAPPING: ");
        for(Node temp : nodeList){
            System.out.println(temp.key+"->"+temp.getFreq());
        }
        
        
        sortNodes();
        
        System.out.println("AFTER SWAPPING: ");
        for(Node temp : nodeList){
            System.out.println(temp.key+"->"+temp.getFreq());
        }
        
        // voodoo loop
        for(int i = 0; i < nodeList.size()-1; i++){
            // Sort Nodes
            //sortNodes();
            
            // Create the new 1st Node
            String temp_root_key = nodeList.get(0).key + nodeList.get(i+1).key;
            int temp_root_freq = nodeList.get(0).getFreq() + nodeList.get(i+1).getFreq();
            Node temp_root = new Node();
            temp_root.key = temp_root_key;
            temp_root.freq = Integer.toString(temp_root_freq);
            tempRoot = temp_root;

            if(i==0){
                // Set up first index
                tempRoot.left = nodeList.get(0);
                tempRoot.right = nodeList.get(i+1);

            }
            else{
                if(nodeList.get(0).getFreq() > nodeList.get(i+1).getFreq()){
                    // add i+1 to left
                    // add 0 to the right
                    tempRoot.left = nodeList.get(i+1);
                    tempRoot.right = nodeList.get(0);
                    
                }
                else if(nodeList.get(0).getFreq() < nodeList.get(i+1).getFreq()){
                    // add i+1 to right
                    // add 0 to the left
                    tempRoot.right = nodeList.get(i+1);
                    tempRoot.left = nodeList.get(0);
                    
                }
            }
            
            // Either way add that new tempRoot as element 0
            nodeList.add(0, tempRoot);
            nodeList.remove(1);
            
            // Insert onto main root
            //root = insertNode(tempRoot, root);
            System.out.println(nodeList.get(0).key + "--" + nodeList.get(0).getFreq());
            System.out.println(nodeList.get(0).left.key + "<-" + nodeList.get(0).left.getFreq());
            System.out.println(nodeList.get(0).right.key + "->" + nodeList.get(0).right.getFreq());
        
        } // end for
        
        // Set root
        root = nodeList.get(0);
        
        // Print root
        printTree(root, "root");
        
       
        // Assign codes
        assignCodes(root,"");
        
        // Search for codes
        tempRoot = new Node();
        Node found = searchKey(root, "1111");
        Node found2 = searchCode(root, "d");
        System.out.println("Found: " + found.key);
        System.out.println("Found: " + found2.code);
        
        // Set up an output file to put our codes
        System.out.println("\n\n");
        System.out.println("YOUR ENCODED FILE INPUT.TXT:");
        String encodedText = encode(root, fileString);
        System.out.println(encodedText);
        
        System.out.println("YOUR DECODED FILE OF INPUT.TXT:");
        String decodeText = decode(root, encodedText);
        System.out.println(decodeText);
        
    }

    public static String encode(Node r, String fileString){
        
        String cypherText="";
        for(int i = 0; i < fileString.length(); i++){
            Node found = searchCode(r, Character.toString(fileString.charAt(i))); 
            if(found != null){
                cypherText+=found.code;
            }
        }
        return cypherText;
        
    }
    public static String decode(Node r, String codedText){
        String plainText="";
        String holder="";
        for(int i = 0; i < codedText.length(); i++){
            holder+=Character.toString(codedText.charAt(i));
            Node found = searchKey(r, holder); 
            if(found != null){
                plainText+=found.key;
                holder="";
            }
        }
        return plainText;
        
    }
    public static Node searchKey(Node node, String code){
        if(node != null){
            if(node.code.equals(code)){
            return node;
            } else {
                Node foundNode = searchKey(node.left,code);
                if(foundNode == null) {
                    foundNode = searchKey(node.right,code);
                }
                return foundNode;
            }
        } else {
            return null;
        }
    }
    public static Node searchCode(Node node, String key){
        if(node != null){
            if(node.key.equals(key)){
            return node;
            } else {
                Node foundNode = searchCode(node.left,key);
                if(foundNode == null) {
                    foundNode = searchCode(node.right,key);
                }
                return foundNode;
            }
        } else {
            return null;
        }
    }
    public static void assignCodes(Node r, String codeString){
        if(r.left == null && r.right == null){
            r.code = codeString;
            System.out.println("key:"+r.key+"\ncode:"+r.code);
            return;
        }
        assignCodes(r.left, codeString + "0");
        assignCodes(r.right, codeString + "1");
    }
    
    public static void printTree(Node r, String moveC){
        Node temp_root = r;
        if(temp_root != null){
            System.out.println(moveC + " " + temp_root.key+","+temp_root.freq);
            printTree(r.left, "left ");
            printTree(r.right, "right ");
        }
    }
    public static void sortNodes(){
        for(int i = 0; i < nodeList.size()-1; i++){
            if(nodeList.get(i).getFreq() > nodeList.get(i+1).getFreq()){
                Collections.swap(nodeList, i, i+1);
            }
        }
    }

}

