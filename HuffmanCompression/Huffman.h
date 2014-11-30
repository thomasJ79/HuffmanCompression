
/***************************************************************************************
*    Title: <CA1>
*    Author: <Thomas Jones X00105989 & Gary Curran X00095292  >
*    Date: <28 March 2014>
***************************************************************************************/

/***************************************************************************************
*    Title: <Huffman Coding>
*    Author: <Dream.In.Code> Knowles Y. Atchison, Jr. >
*    Date: <11 February 2011 - 02:20 PM>
*    Availability: <http://www.dreamincode.net/forums/topic/17915-huffman-coding/>
*
***************************************************************************************/
#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include<string>
#include<iostream>
#include<map>
#include<vector>
#include"Node.h" 
class Huffman
{
public:
	Huffman(); // constructor
	~Huffman(); // destructor

	// 1. Given a text file, determine the frequency of each character 
	//in the text(map of character and frequency)
	bool frequency(std::string);  // reads characters from .txt file & add to frequency map( counting occurance of each character)


	// 2. Build an optimal Huffman tree to represent these characters with these frequencies
	void buildTree();


	// 3. Use the tree to map each character to the string of 0's and 1's needed to encode it 
	// (preorder	traversal of tree, store results in a map of character and string)
	void getHuffmanEncoding(Node*, std::string);


	// 4. Use the map to encode the text to a string of 0's and 1's and write to an encoded file
	string encode();


	// 5. Use the Huffman Tree to decode the text and write to another file.
	string Huffman::decode(string src);

	// 6. To compress : break up the string of 0's and 1's into 8 bit chunks, and write the character
	//	represented by each chunk to the compressed file.
	void compress(string);


	// 7. Decode by replacing each character with the 8 bits needed to represent it.
	void unCompress(string);

	// Summary printout method
	void Summary();

private:
	int additionalBits; //additional bits required to store equal 8 bit chunks
	char character; // store each character
	map<char, int>::const_iterator it; /// *ittetrator over value and weight
	map<char, int>frequencyMap; // takes in value and weight i.e (e 4)
	map<char, string> huffmanTable; // takes in value and huffman code i.e (e 0001)
	vector<std::string> vecHuff; // hold the huffman code i.e (001,11,0001.....)
	vector<char> vecChar; // hold all of the letters from the file 
	Node *root; // Create a new root node for the combined tree, and attach the present roots as the left and right children
	string code; //hold all the huffman codes i.e (0011 11 1000)
	int bitUsed;
	int blocks;
};
#endif


