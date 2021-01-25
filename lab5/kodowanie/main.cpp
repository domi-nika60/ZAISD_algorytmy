#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>

using namespace std;

class HuffmanNode {
public:
    char character;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(const char &character, const int &frequency)
            : character(character), frequency(frequency), left(nullptr), right(nullptr) {}

    HuffmanNode(const char &character, const int &frequency, HuffmanNode *left, HuffmanNode *right)
            : character(character), frequency(frequency), left(left), right(right) {}
};

struct CompareNodesFrequencies {
    bool operator()(HuffmanNode const *a, HuffmanNode const *b) const {
        return a->frequency > b->frequency;
    }
};

string readFile() {
    // Read from the text file
    ifstream MyReadFile("test.txt");

    string myText((istreambuf_iterator<char>(MyReadFile)), istreambuf_iterator<char>());
    // cout << "Odczytany tekst: " << myText <<endl;

    // Close the file
    MyReadFile.close();
    return myText;
}

//create dictionary with number of occurances
map<char, int> checkFrequency(const string &stringInput) {
    map<char, int> mapping;
    for (char it : stringInput) {
        mapping[it]++;
    }
    cout << "Mapa czestotliwosci: " << endl;
    map<char, int>::iterator it;
    for(it=mapping.begin(); it!=mapping.end(); ++it){
      cout << it->first << " => " << it->second << '\n';
   }
    return mapping;
}

//create queue for comparing with huffamnNodes without pointing to each other
priority_queue <HuffmanNode *, vector<HuffmanNode *>, CompareNodesFrequencies> createNodeQueue (const string &inputString) {

    priority_queue <HuffmanNode *, vector<HuffmanNode *>, CompareNodesFrequencies> nodes_queue;
    map<char, int> frequency_map = checkFrequency(inputString);

    for (auto pair: frequency_map) {
        nodes_queue.push(new HuffmanNode(pair.first, pair.second));
    }

    return nodes_queue;
}

//cretae huffman tree from queue
HuffmanNode* createHuffmanTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodesFrequencies> nodes_queue) {

    while (nodes_queue.size() != 1) {
        HuffmanNode *left = nodes_queue.top();
        nodes_queue.pop();
        HuffmanNode *right = nodes_queue.top();
        nodes_queue.pop();

        nodes_queue.push(new HuffmanNode(0, left->frequency + right->frequency, left, right));
    }

    return nodes_queue.top();
}

void goThroughHuffmanTree(HuffmanNode *node, const string &char_code, map<char, string> &encodedMap) {
    if (node->left && node->right) {
        goThroughHuffmanTree(node->left, char_code + "0", encodedMap);
        goThroughHuffmanTree(node->right, char_code + "1", encodedMap);
    } else {
        encodedMap[node->character] = char_code;
    }
}

map<char, string> encodeCharactersAndPrintToFile(HuffmanNode *treeRoot_ptr) {

    map<char, string> encodedMap;
    goThroughHuffmanTree(treeRoot_ptr, "", encodedMap);

    ofstream treeFile;
	treeFile.open ("treeCode.txt");

    cout << "Mapa kodow: " << endl;
    map<char, string>::iterator it;
    for(it=encodedMap.begin(); it!=encodedMap.end(); ++it){
      cout << it->first << " => " << it->second << '\n';
      treeFile << (int)it->first << " " << it->second.c_str() << endl;
   }
    treeFile.close();
    return encodedMap;
}

string encodeText(const string &text, map<char, string> &encodedMap) {
    
    string encoded_text;
    for (char c : text) {
        encoded_text += encodedMap[c];
    }

    cout << "Zakodowany tekst \n" << encoded_text << endl;

    ofstream outputFile;
	outputFile.open ("codedFile.txt");
	outputFile << encoded_text;
	outputFile.close();

    return encoded_text;
}


int main() {
    // czytanie tekstu z pliku
    string inputString = readFile();

    cout<< "Tekst do zakodowania: \n" << inputString <<endl;

    //tworzenie kolejki ze zmapowanymi znakami
    priority_queue <HuffmanNode *, vector<HuffmanNode *>, CompareNodesFrequencies> nodeQueue = createNodeQueue(inputString);

    // tworzenie drzewa
    HuffmanNode *treeRoot_ptr = createHuffmanTree(nodeQueue);

    // tworzenie unikalnego kodu dla kazdego znaku
    map<char, string> encodedMap = encodeCharactersAndPrintToFile(treeRoot_ptr);

    // kodowanie tekstu
    string encoded_text = encodeText(inputString, encodedMap);

    return 0;
}
