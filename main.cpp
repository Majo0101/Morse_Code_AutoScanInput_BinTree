#include <bits/stdc++.h>

#define CODE 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,32
#define DECODE 45,46,32
#define OR ||
#define subor "data.txt"

using namespace std;

struct Node {                                 // BinTree
    char data;
    Node*dash;
    Node*dot;
};

Node*root = NULL;
Node*whereIam = NULL;

string scan(bool &type);                      // AutoScan input , return bool of type
void giveMeTree();                            // Creates tree from input data
void coder(Node*leaf,const string& str);      // Code algebra to Morse
void decoder(Node*leaf,string str);           // Decode Recursion
void functionCoder(const string& str);        // Decode Morse to Algebra Recursion

string catchData;
string recordData;                            // important for coder
char wantedChar;


int main(){

    bool inputType = false;
    string inputString;
    char game = '0';

    giveMeTree();

    while(game != 'n') {

        inputString = scan(inputType);

        (inputType) ? cout << "Morse code --> alphabet: " : cout << "Alphabet --> Morse code: ";

        if (inputType) {
            decoder(root, inputString);
        } else {
            functionCoder(inputString);
        }

        fflush(stdin);

        while (game != 'y' OR game != 'n'){
            cout << endl << "Do you want to continue? (y/n)" << endl;
            cin >> game;
            if (game == 'y' OR game == 'n'){break;}
            cout << "Bad choice !!" << endl;
        }
    }
}

string scan(bool &type){

    again:
    string in;
    in.clear();
    cout << "Enter your massage:" << endl;

    while (getline(cin, in)) {
        if (!in.empty()) { break; }
    }

    if (!in.empty()) {
        for (int i = 0,arr[]={DECODE}; i < in.size(); i++) {
            for (int j = 0, m = 0; j < 3; j++) {
                if(in[i] != arr[j]){m++;}
                if (m > 2){goto text;}
            }
        }
    }
    goto morseCode;
    text:{
    for (int i = 0, arr2[]={CODE}; i < in.size(); i++) {
        for (int j = 0, m = 0; j < 27; j++) {
            if (in[i] != arr2[j]){m++;}
            if (m > 26){goto again;}
        }
    }
    type = false;
    return in;
}
    morseCode:{ type = true; return in;}
}

void giveMeTree(){

    char character;
    string code;

    ifstream input(subor);

    if (input.is_open()){
        cout << "File found..."<< endl;
    }else{
        cout << "Somethings went wrong..." << endl;
        exit(100);
    }

    Node*tmp = new Node;
    tmp->data = ' ';
    tmp->dash = tmp->dot = NULL;
    root = tmp;
    whereIam = root;

    while(input >> character >> code){

        int len = (int)code.size();

        for (int i = 0; i < len; i++) {

            if (code[i] == '.'){
                if(whereIam->dot == NULL){
                    Node*leaf = new Node;
                    leaf->dot = leaf->dash = NULL;
                    whereIam->dot = leaf;
                    Node*temp;
                    temp = whereIam->dot;
                    whereIam = temp;
                }else{
                    Node*temp;
                    temp = whereIam->dot;
                    whereIam = temp;
                }
            }

            if (code[i] == '-'){
                if(whereIam->dash == NULL){
                    Node*leaf = new Node;
                    leaf->dot = leaf->dash = NULL;
                    whereIam->dash = leaf;
                    Node*temp;
                    temp = whereIam->dash;
                    whereIam = temp;
                }else{
                    Node*temp;
                    temp = whereIam->dash;
                    whereIam = temp;
                }
            }
        }

        whereIam->data = character;
        whereIam = root;

    }
    cout << "Tree was created..." << endl << endl;
    cout << "Allowed are A-Z + space characters OR Morse code with space between characters" << endl;
}

void coder(Node*leaf,const string& str){

    recordData = recordData + str;

    if(!leaf){}
    else{
        if(leaf->data != wantedChar){
            coder(leaf->dot,".");
            recordData = recordData.substr(0, recordData.size() - 1);
            coder(leaf->dash,"-");
            recordData = recordData.substr(0, recordData.size() - 1);
        }else{
            catchData = recordData;
        }
    }
}

void decoder(Node*leaf,string morse){

    int len = (int)morse.size();

    for (int i = 0; i < len; i++) {

        if(morse[i]=='-'){
            if (whereIam->dash != NULL){
                Node*temp;
                temp = whereIam->dash;
                whereIam = temp;
            }
        }

        if(morse[i]=='.'){
            if (whereIam->dot != NULL){
                Node*temp;
                temp = whereIam->dot;
                whereIam = temp;
            }
        }

        if(morse[i] == ' ' OR (i+1) == len) {
            cout << whereIam->data;
            whereIam = root;
        }
    }
}

void functionCoder(const string& str){

    const string& input = str;

    int len = (int)input.size();

    for (int i = 0; i < len; ++i) {
        wantedChar = input[i];
        if (wantedChar == ' '){
            cout << " ";
            goto jump;
        }
        coder(root,"");
        cout << catchData;
        jump:
        cout << " ";
    }
}