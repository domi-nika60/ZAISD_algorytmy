#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

string readFile() {
    // Read from the text file
    ifstream MyReadFile("../kodowanie/codedFile.txt");

    string myText((istreambuf_iterator<char>(MyReadFile)), istreambuf_iterator<char>());

    // Close the file
    MyReadFile.close();
    return myText;
}

string decodeText(const string &text) {

    ifstream f("../kodowanie/treeCode.txt");
    map<string, char> code_char_map;
    int character;
    string code;

    while (f >> character && f >> code) {
        code_char_map[code] = char(character);
    }
    f.close();

    string decoded_text;
    int position = 0;
    int length = 2;
    string substring;
    map<string, char>::iterator it;

    while (position + length <= text.length()) {
        substring = text.substr(position, length);
        it = code_char_map.find(substring);

        if (it != code_char_map.end()) {
            decoded_text += it->second;
            position += length;
            length = 2;
        } else {
            length++;
        }
    }
    cout << "Zdekodowany tekst: \n" << decoded_text << endl;
    ofstream d("decodedFile.txt");
    d << decoded_text;
    d.close();

    return decoded_text;
}

int main() {

    string inputString = readFile();
    cout<< "Tekst do odkodowania: \n" << inputString <<endl;

    string decoded_text = decodeText(inputString);
    return 0;
}
