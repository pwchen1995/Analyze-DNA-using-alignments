#ifndef TASKS_H
#define TASKS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define MAX_CHAR 14
using namespace std;

class tasks
{
public:
    tasks();
    ~tasks();

    struct node {

        int nodeId = 0;
        int suffixId = 0;
        int ParentStartIndex = 0;
        int ParentEndIndex = 0;
        int childCounter = 0;
        int color;
        int stringId;
        int stringDepth;
        bool visited= false;
        node* children[MAX_CHAR];
        node* parent;
        node* next;
        node* suffixLink;
    };
    node* root = (node*)malloc(sizeof(node));
    node* memory = NULL;
    node* top = NULL;
    //suffix Link Variables
    node* u = NULL;
    node* v = NULL;
    node* uPrime = NULL;
    node* vPrime = NULL;


    string ReportPath ="F:\\Abhyas\\WSU\\Sem 2\\Computational Genomics\\Homework\\dataCoding\\project3\\colorDump.txt";
    string LCSReportPath ="F:\\Abhyas\\WSU\\Sem 2\\Computational Genomics\\Homework\\dataCoding\\project3\\LCSDump.txt";
    string LCSPath ="F:\\Abhyas\\WSU\\Sem 2\\Computational Genomics\\Homework\\dataCoding\\project3\\LCS.txt";

    //Function Prototypes
    void inputReader(string fileName);
    void buildGST();
    void buildLCS(int a, int b);



private:

//    string s0, s1, s2, s3, s4;
//    string* addresses[5] = {&s0, &s1, &s2, &s3, &s4};
    //File Read variables
    string s0, s1, s2, s3, s4, s5, s6, s7, s8, s9;
    string *addresses[10] = {&s0, &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9};
    string cs="";
    string pLabel="";
    int countKeeper = 0;
    int ow=0;
    //Variables
    string sequence="";
    int leafColor;
    //        const int n =10;
    int sequence_len;
    int nodeCount;
    int internalNodeCount;
    int leafCount=0;
    int sufId = 0;
    int sum = 0;
    int colorCount = 0;
    int maxColor = 10;
    ofstream outfile;
    ifstream afile;
    int keeper=0;
    int coloredIntNode=0;
    int l=10;
//    int myLeaf=0;


    //function prototypes
    int getChildIndex(char c);
    int walkdown(string edgeLabel, string suffix);
    string edgeLabel(node* var);

    node* insertSuffix(node* n, string suffix);
    node* nodeHop(node* vPrime, string beta);
    node* findPath(node* n, string suffix);
    void treeCleanUp(node* r, int previous, int current, int color);
    int bwtIndex(node* r);
    void coloring(node* r);
    void color(node* curr);
    void displaySD(node* r);
    string getLCS(node* r);
    int deepestIntNode(node* r);
    void fingerPrints();



    //        bool checkDuplicateSuffix(node* r, string sequence, string suffix);
    //        void changeLeafColor(int leafColor, string sequence, string ins);
    //        node* getDuplicateSuffix(node* r, string sequence, string suffix);
    //        string getPathLabel(node* temp, string sequence);


};

#endif // TASKS_H
