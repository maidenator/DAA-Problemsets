#include <iostream>
#include "node.h"
#include "heap.h"
#include "huffman.h"

using namespace std;

// Recursive helper to find the leaves and print their codes
void printHuffmanCodes(node* root) {
    if (!root) return;
    
    // If it's a leaf node (has a character), print it
    if (root->left == nullptr && root->right == nullptr && root->character != '\0') {
        cout << "Character '" << root->character << "' (Weight " << root->weight 
             << ") -> Code: " << root->getCode() << endl;
    }
    
    printHuffmanCodes(root->left);
    printHuffmanCodes(root->right);
}

int main() {
    cout << "--- Testing Huffman Coding ---" << endl;
    
    Heap* heap = new Heap();

    // Test Data: classic Wikipedia/textbook Huffman frequencies
    heap->insert(new node('f', 5));
    heap->insert(new node('e', 9));
    heap->insert(new node('c', 12));
    heap->insert(new node('b', 13));
    heap->insert(new node('d', 16));
    heap->insert(new node('a', 45));

    cout << "Nodes inserted into Heap. Heap size: " << heap->size() << endl;

    // Build the Huffman Tree
    node* huffman_root = huffman_code(heap);

    cout << "\nHuffman Tree Generated!" << endl;
    cout << "Total Weight of Root: " << huffman_root->weight << endl;
    cout << "------------------------------" << endl;

    // Print the generated prefix codes
    printHuffmanCodes(huffman_root);

    return 0;
}