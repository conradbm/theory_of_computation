/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package huffman_tree_compression;


public class Node implements Comparable<Node> {
    public String key;
    public String freq;
    public String code;
    Node left;
    Node right;
    public Node(){
        left = null;
        right = null;
        key="";
        freq="";
        code="";
    }
    public Node(String k, String f){
        key = k;
        freq = f;
        code="";
    }

    public int getFreq(){
        return Integer.parseInt(freq);
    }
    @Override
    public int compareTo(Node o) {
        return Integer.parseInt(o.freq);
    }
}
