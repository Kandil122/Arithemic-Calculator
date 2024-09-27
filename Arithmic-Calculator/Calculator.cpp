#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int splitByDelimiter(string str, char delimiter, string* words);
void checkInputValues(string* words, int size);
bool isExist(char* arr, int size, char character);
bool isMissingInput(char character);
void replace(string* words, int size, char var, char value);

int calculateLogicRes(string* circuit, int idx, int* gatescount);
int isDigit(char character);
bool isCorrectGate(string gate);
int doLogicOperation(string operation, int first, int second);

void printOutput(int res, int* gatescount);
int returnIndex(string gate);

int main() {
    string circuit;
    getline(cin, circuit);

    string* circuitParts = new string[circuit.length()];            // new dynamic memory allocation in runtime
    int arrayLength = splitByDelimiter(circuit, ' ', circuitParts);

    checkInputValues(circuitParts, arrayLength);

    int gates[6] = { 0 };

    int res = calculateLogicRes(circuitParts, 0, gates);

    printOutput(res, gates);

    delete[] circuitParts;                                         // dynamic , b delete b3d ma a5ls
}

// deh function bdal el tokenization 3l4qn t split the variables
int splitByDelimiter(string str, char delimiter, string* words) {
    int stringLen = str.length();
    int wordidx = 0;
    int startidx = 0;

    for (int i = 0; i < stringLen; i++) {
        if (str[i] == delimiter) {
            words[wordidx] = str.substr(startidx, i - startidx);
            startidx = i + 1;
            wordidx++;
        }
        if (i == stringLen - 1) {
            words[wordidx] = str.substr(startidx, i - startidx + 1); 
            wordidx++;
        }
    }

    return wordidx;
}
// bt2kd law input kan variables w b4of law homa zay b3d
void checkInputValues(string* words, int size) {
    char* missinginputs = new char[size];
    int missingInputCount = 0;
    for (int i = 0; i < size; i++) {
        if (words[i].length() == 1) {
            if (!isExist(missinginputs, missingInputCount, words[i][0]) && isMissingInput(words[i][0])) {
                missinginputs[missingInputCount] = words[i][0];
                missingInputCount++;
            }
        }
    }

   
    if (missingInputCount > 0) {
        cout << missingInputCount << " varaibles are missing please enter them in separate lines" << endl;
        for (int i = 0; i < missingInputCount; i++) {
            string missingInput;
            cin >> missingInput;
            replace(words, size, missingInput[0], missingInput[2]);
        }
    }
}

bool isExist(char* arr, int size, char character) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == character) {
            return true;
        }
    }
    return false;
}

// w dah 3l4an y2r2a el variales inputs, w y5ly balo my5od4 el 'e' 3la enha input variable
bool isMissingInput(char character) {
    if (character == 'e') {
        return false;
    }
    return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

// dah fe 7alet el inputs kanet variables b7ot el value mkan el variable
void replace(string* words, int size, char var, char value) {
    for (int i = 0; i < size; i++) {
        if (words[i].length() == 1) {
            if (words[i][0] == var) {
                words[i][0] = value;
            }
        }
    }
}
// dah 3l4an ageeb el first w el second w el main gate w awdeha lel function do opeeration
int calculateLogicRes(string* circuit, int idx, int* gatescount) {
    if (isDigit(circuit[idx][0])) {
        return stoi(circuit[idx]);
    }

    int first = -1;
    int second = -1;
    int eIndex = idx;

    if (isDigit(circuit[idx + 1][0])) {
        first = stoi(circuit[idx + 1]);
        eIndex = idx + 1;
    }
    else if (circuit[idx + 1] == "e") {
        cout << "result : BAD input : missing input number" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        while (circuit[eIndex] != "e") {
            eIndex++;
        }
        first = calculateLogicRes(circuit, idx + 1, gatescount);
    }

    if (isDigit(circuit[eIndex + 1][0])) {
        second = stoi(circuit[eIndex + 1]);
    }
    else if (circuit[eIndex + 1] == "e" && circuit[idx] == "NOT") {
        second = -1;
    }
    else if (circuit[eIndex + 1] == "e") {
        cout << "result : BAD input : missing input number" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        second = calculateLogicRes(circuit, eIndex + 1, gatescount);
    }

    if (!isCorrectGate(circuit[idx])) {
        cout << "Wrong Logic Circuit Description" << endl;
        exit(EXIT_FAILURE);
    }

    gatescount[returnIndex(circuit[idx])] += 1;

    return doLogicOperation(circuit[idx], first, second);
}

// 3l4an 2taked en el rkm 0 or 1 
int isDigit(char character) {
    return (character == '0' || character == '1');
}

// 3l4an 2tkd en el gates el mawgooda s7
bool isCorrectGate(string gate) {
    return (gate == "AND") || (gate == "OR") || (gate == "NOT") || (gate == "NAND") || (gate == "NOR") || (gate == "XOR");
}

// dah by3ml el function bta3et el operator
int doLogicOperation(string operation, int first, int second) {
    if (operation == "AND")
        return (first && second);

    if (operation == "OR")
        return (first || second);

    if (operation == "NAND")
        return !(first && second);

    if (operation == "NOR")
        return !(first || second);

    if (operation == "XOR") {
        return (first != second);
    }

    if (operation == "NOT") {
        return !first;
    }

    return 0;
}

// 3l4an a print el outpputs
void printOutput(int res, int* gatescount) {
    cout << "AND gates : " << gatescount[returnIndex("AND")] << endl;
    cout << "OR gates : " << gatescount[returnIndex("OR")] << endl;
    cout << "NOT gates : " << gatescount[returnIndex("NOT")] << endl;
    cout << "XOR gates : " << gatescount[returnIndex("XOR")] << endl;
    cout << "NAND gates : " << gatescount[returnIndex("NAND")] << endl;
    cout << "NOR gates : " << gatescount[returnIndex("NOR")] << endl;
    cout << "result : " << res << endl;
}

// 3l4an a5zn mkan el array , b index w o3ed a increment feeh
int returnIndex(string gate) {   
    if (gate == "AND")
        return 0;

    if (gate == "OR")
        return 1;

    if (gate == "NAND")
        return 2;

    if (gate == "NOR")
        return 3;

    if (gate == "XOR")
        return 4;

    if (gate == "NOT")
        return 5;

    return -1;
}