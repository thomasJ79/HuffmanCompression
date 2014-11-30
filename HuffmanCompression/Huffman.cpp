
/***************************************************************************************
*    Title: <CA1>
*    Author: <Thomas Jones X00105989 & Gary Curran X00095292  >
*    Date: <28 March 2014>
***************************************************************************************/

#include<fstream>
#include <queue>
#include<bitset>
#include <iostream>
#include"Huffman.h"

using namespace std;

Huffman::Huffman()
	:character(NULL), root(NULL), vecHuff(NULL), vecChar(NULL)
{}

Huffman::~Huffman()
{}

bool Huffman::frequency(string text)
{
	ifstream inFile;
	inFile.open(text); // open the file
	if (inFile)	{ // confirm file exists
		while (inFile.get(character)) { // get each character
			frequencyMap[character]++; // add character and number of occurances to the frequency map
			vecChar.push_back(character); // add character to vector
			bitUsed++;
		}
		inFile.close(); // close the file
		return true;
	}

	else{

		cout << "no file";
		return false;
	}
}

void Huffman::buildTree()
{
	// (maintain a priority queue of trees, removing and joining trees until only one tree remains
	// Place nodes in a priority queue
	// The lower the occurrence, the higher the priority in the queue

	priority_queue <Node > q;

	//	Dequeue node and make it left subtree
	//	Dequeue next node and make it right subtree
	//	Frequency of new node equals sum of frequency of left and right children
	//	Enqueue new node back into queue


	for (it = frequencyMap.begin(); it != frequencyMap.end(); it++)
		//Create new node and push onto queue
		q.push(Node(it->first, it->second));
	//pop off two at a time until you get one left
	while (q.size() > 1) {
		Node *child0 = new Node(q.top()); // Dequeue node and make it left subtree
		q.pop();
		Node *child1 = new Node(q.top()); // Dequeue next node and make it right subtree
		q.pop();
		root = new Node(child0, child1); // set the root node
		q.push(Node(child0, child1)); //// Enqueue new node back into queue 

	}
	//final one is the root of your encoding tree
	std::string code = "";
	cout << "FREQUENCY MAP" << endl;
	cout << "char  frequency  hoffman-code" << endl;
	getHuffmanEncoding(root, code); // call to recursive function
}


void Huffman::getHuffmanEncoding(Node* root, std::string code = "")  {

	if (root->getChild0()){  //root
		getHuffmanEncoding(root->getChild0(), code + '0');  // left
		getHuffmanEncoding(root->getChild1(), code + '1'); // right

	}
	else{
		cout << " " << root->getValue() << "      ";
		cout << root->getWeight();
		cout << "\t   " << code << endl;
		vecHuff.push_back(code); // used for string of 1's and 0's
		huffmanTable.insert(pair<char, string>(root->getValue(), code)); // add map of tree to huffmanTable
	}
}

string Huffman::encode(){

	ofstream myfile("encode.txt");
	if (myfile.is_open())
	{
		cout << "\nWRITING TO FILE....." << endl;;
		for (int i = 0; i < vecHuff.size(); i++)
		{
			myfile << vecHuff.at(i);
		}
		myfile.close();

		for (vector<char>::iterator it = vecChar.begin(); it != vecChar.end(); ++it) {
			code.append(huffmanTable[*it]);
			code.append(" ");
		}
		cout << code << endl;
		return code;
	}
	else cout << "Unable to open file";

}

/***************************************************************************************
*    Title: <An In-Depth Look At Huffman Encoding>
*    Author: <Dream.In.Code> - Knowles Y. Atchison, Jr. >
*    Date: <19 JANUARY 2011>
*    Availability: <http://www.dreamincode.net/forums/blog/324/entry-3150-an-in-depth-look-at-huffman-encoding/>
*
***************************************************************************************/
string Huffman::decode(string src){
	string info = "";
	size_t lastBlock = 0;
	for (size_t i = 0; i < src.length(); i++){
		if (src.at(i) == ' '){
			string temp = src.substr(lastBlock, i - lastBlock);
			lastBlock = i + 1;
			for (map<char, string>::iterator it = huffmanTable.begin();
				it != huffmanTable.end(); ++it){
				if (it->second == temp){
					info += (it->first);
					break;
				}
			}
		}
	}
	return info;
}
//*************************************************************************************** /


void Huffman::compress(string file)
{
	ofstream cfile("compress.txt");
	vector <char> compress;
	char v;
	int i = 0;

	ifstream inFile;
	inFile.open(file); // open the file
	cout << "\n\nCOMPRESSING FILE ........." << endl;
	cout << "Encoded string to compress: " << endl;
	if (inFile)	{ // confirm file exists
		while (inFile.get(v)) { // get each character
			compress.push_back(v); // add character to vector
			cout << compress.at(i);
			i++;
		}

		inFile.close(); // close the file
	} // end if

	else{
		cout << "no file";
	}

	int size = compress.size();
	additionalBits = (8 - (size % 8)); // size of compress vector mod 8 (tells us number of additional bits required)

	cout << "\n\nCurrent bits: " << compress.size() << endl;
	cout << "\nAddition bits required to make even blocks of 8: " << additionalBits << endl;

	if (additionalBits != 8) // if vector is not in even blocks of  8 bits
	{
		for (int j = 0; j < additionalBits; j++)
		{
			compress.push_back('0'); // add additional 0's to make even amount of 8 bit blocks
		} // end loop
	} // end if

	blocks = compress.size() / 8;
	cout << "\nTotal blocks of 8: " << blocks << endl << endl;

	// loop in blocks of 8
	for (int i = 0; i < compress.size(); i += 8)
	{
		vector<char> bitSets; // vector of chars
		string s;  // string to hold 8 bit chunk
		for (int j = i; j < i + 8; j++)
		{
			bitSets.push_back(compress.at(j)); //putting chars into int bitSets vector, 
		}

		// the STL bitset array goes from 7 - 0
		// As vector reads from 0 - 7, we need to revers characters in the string
		for (int k = 7; k >= 0; k--)
		{
			s.push_back(bitSets.at(k));  //add the 8 chars to the string s, in reverse order
		}
		unsigned int number = bitset<8>(s).to_ulong(); // convert from binary to decimal

		char c = char(number);  //cast from the decimal (number) to a char (c)

		cout << "Asci value: " << number << " char: " << c << endl;

		if (cfile.is_open())
		{
			cfile << c;

		}

	}
	cout << "\nWriting these characters to file..... ";
}


void Huffman::unCompress(string file)
{
	ifstream inFile; // stream to take in compressed file
	vector<char> unCompressVec;
	vector<string> stringVec;
	string output;
	int k = 0;
	char v;

	cout << "\n\nUN-COMPRESSING FILE ........." << endl;
	cout << "Contents of the file: " << endl;
	inFile.open(file); // open the file
	if (inFile)	{ // confirm file exists
		while (inFile.get(v)) { // get each character
			unCompressVec.push_back(v);	// add chars to vector
		}
		inFile.close(); // close the file
	}

	else{
		cout << "no file";
	}

	for (int i = 0; i < unCompressVec.size(); i++)
	{
		// cast char to int (decimal repesentation)
		k = (int)unCompressVec.at(i);

		// guard against extended ascii character problem
		if (k < 0)
		{
			k = k + 256;
		}
		cout << unCompressVec.at(i);

		bitset<8> bs = k;
		string s = bs.to_string();  // to_string returns an std::string with the binary digits ( 000...0111 )

		// re-arrange characters that have been reversed
		std::reverse(s.begin(), s.end());

		stringVec.push_back(s);


		if (i == unCompressVec.size() - 1) // last string of binary numbers in the vector
		{
			if ((additionalBits != 8)) // if vector is not in even blocks of  8 bits
			{
				string temp = stringVec.at(i);
				temp.erase(temp.begin() + (8 - additionalBits), temp.end()); // remove the additionl bits originally added
				stringVec.pop_back(); //erase last entry in the vector
				stringVec.push_back(temp); //pop on new string without the additional bits 
			}
		}
	}

	cout << "\n\nFile uncompressed back to the encoded string: " << endl;
	for (int i = 0; i < stringVec.size(); i++)
	{
		output.append(stringVec.at(i));
	}
	cout << output;
}

void Huffman::Summary()
{
	int t = 0;
	for (it = frequencyMap.begin(); it != frequencyMap.end(); it++)
	{
		t++;
	}
	cout << "\n\n\n\n*******SUMMARY OF COMPRESSION*******" << endl;
	cout << "\nSince we have " << t << " characters in the file, " << endl;
	cout << "let's assume each is stored with a three bit code." << endl;
	cout << "Total frequency of all these characters is " << bitUsed << endl;
	cout << "\nBITS USED (" << bitUsed << " * 3) " << " =  " << bitUsed * 3 << " bits" << endl;

	cout << "\nThe Huffman compression produced a file of  " << blocks << " characters" << endl;
	cout << "BITS USED (" << blocks << " * 3) " << " =  " << blocks * 3 << " bits" << endl;

	cout << "\n\nTotal saving = " << (bitUsed * 3) - (blocks * 3) << " bits" << endl;

}