
/***************************************************************************************
*    Title: <CA1>
*    Author: <Thomas Jones X00105989 & Gary Curran X00095292  >
*    Date: <28 March 2014>
***************************************************************************************/


#include<iostream>
#include<fstream>
#include<string>
#include"Huffman.h"
using namespace std;

int main()

{
	Huffman h;

	// call to the Huffman frequency method
	// exit if unable to located the file
	if (h.frequency("Text.txt") == false)
	{
		cout << "ERROR -- Unable to locate file for decoding";
		system("pause");
		exit(1);
	}

	else
	{
		h.buildTree(); // Build an optimal Huffman tree to represent these characters with these frequencies

		// Encode the file with string of 0's and 1's and 
		// - store in local string c
		// - wite to file encode.txt
		string c = h.encode();

		cout << "\nDECODED TEXT:" << endl;

		// call to the decode function, passing the decoded string c!!
		cout << h.decode(c);

		// compress the encode file into 8 bit chunks
		// store in file compress.txt
		h.compress("encode.Txt");

		//Un-Compress the file compress.txt
		h.unCompress("compress.txt");
	}

	h.Summary(); // print summary details of the huffman compression
	system("pause");
	return 0;
}