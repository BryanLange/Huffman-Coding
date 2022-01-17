#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class listNode {
public:
    string chStr;
    int prob;
    listNode* next;
public:
    listNode(string, int, listNode*);
};

class linkedList {
private:
    listNode* listHead;
public:
    linkedList(ifstream&, ofstream&);
    void insertNewNode(listNode*);
    listNode* findSpot(listNode*);
    void printList(ofstream&);
    void flush();
};

int main(int argc, char** argv) {
    if(argc == 3) {

        // open input and output files
        ifstream inFile;
        inFile.open(argv[1]);
        ofstream outFile;
        outFile.open(argv[2]);

        // read input file, construct huffman linked list
        linkedList x(inFile, outFile);

        // close input and output files
        inFile.close();
        outFile.close();

        // delete list from memory
        x.flush();
    }
    else {
        cout << "Invalid number of arguments.\n";
    }
} // end main


// listNode constructor
listNode::listNode(string s, int p, listNode* n) {
    chStr = s;
    prob = p;
    next = n;
} // end listNode constructor


// linkedList constructor
linkedList::linkedList(ifstream& inFile, ofstream& outFile) {
    // set dummy node
    listHead = new listNode("dummy", 0, nullptr);

    // read character and its probability
    // create node for each char and insert into linked list
    // print list to outFile
    while(true) {
        string chr;
        int prob;
        inFile >> chr >> prob;
        if(inFile.eof()) break;

        listNode* newNode = new listNode(chr, prob, nullptr);

        insertNewNode(newNode);

        printList(outFile);
    }
} // end linkedList constructor


// inserts given node into linked list after the returned spot
void linkedList::insertNewNode(listNode* newNode) {
    listNode* spot = findSpot(newNode);
    newNode->next = spot->next;
    spot->next = newNode;
} // end insertNewNode()


// returns pointer where newNode will be added
listNode* linkedList::findSpot(listNode* newNode) {
    listNode* spot = listHead;
    // while not at end of list, and prob of current node is less than newNode
    while(spot->next != nullptr && spot->next->prob < newNode->prob) {
        spot = spot->next;
    }
    return spot;
} // end findSpot()


// prints linked list to outFile starting at head
void linkedList::printList(ofstream& outFile) {
    // list navigation pointer
    listNode* nav = listHead;

    outFile << "listHead--> ";
    while(nav->next != nullptr) {
        outFile << "(\"" << nav->chStr << "\", " << nav->prob << ", \"" <<
            nav->next->chStr << "\")--> ";

        nav = nav->next;
    }
    outFile << "(\"" << nav->chStr << "\", " << nav->prob << ", NULL)--> NULL\n";
} // end printList()


// delete linked list from memory
void linkedList::flush() {
    listNode* nav = listHead;
    listNode* next;
    while(nav != nullptr) {
        next = nav->next;
        free(nav);
        nav = next;
    }
} // end flush
