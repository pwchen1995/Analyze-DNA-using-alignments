#include "tasks.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <iterator>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

tasks::tasks()
{
    sufId = 0;
    internalNodeCount = 0;
    leafCount=0;
    root->nodeId = 1;
    root->ParentStartIndex = 0;
    root->ParentEndIndex = 0;
    root->childCounter =0;
    root->color=-1;
    for (int i = 0; i < MAX_CHAR; i++)
    {
        root->children[i] = NULL;
    }
    root->parent = NULL;
    root->suffixLink = root;
}

tasks::~tasks()
{
    delete root;
//    delete addresses;
}

void tasks::inputReader(string fileName) {

    string virus;

    ifstream file(fileName.c_str());
    if (!file.good()) {
        cerr << "Error opening '" << fileName << endl;
        //return -1;
    }

    string line, name, content;
    while (getline(file, line).good())
    {
        if (line.empty() || line[0] == '>')
        {
            if (!name.empty()) {
                virus += content;
                name.clear();
            }
            if (!line.empty()) {
                name = line.substr(1);
            }
            content.clear();

        }
        else if (!name.empty())
        {

            if (line.find(' ') != string::npos) {
                name.clear();
                content.clear();
            }
            else {
                content += line;
            }
        }
    }
    if (!name.empty())
    {
        virus += content;
    }


    //file.close();
    //char e = '$';
    //virus += e;

    virus += to_string(countKeeper);
    *addresses[countKeeper]= virus;
    string virusFile= *addresses[countKeeper];
    sequence_len = virusFile.length();
    cout<<"file name is: "<<addresses[countKeeper]<<endl;
    cout<<"sequence_len: "<<sequence_len<<endl;
    cout<<"\n";
    cout<<"*******************************"<<endl;
    countKeeper++;
}


int tasks::getChildIndex(char c)
{
//    char childList[4]= {'A','C','G','T'};
    char childList[MAX_CHAR]= {'A','C','G','T','0','1','2','3','4','5','6','7','8','9'};
    int index=99;
    for(int i=0; i<MAX_CHAR;i++)
    {
        if(childList[i]==c)
        {
            index=i;
        }
    }
//    if(index==99)
//    {
//        index=5;
//    }
    return index;
}

int tasks::walkdown(string edgeLabel, string suffix)
{
    int x = 0;
    while (edgeLabel[x] == suffix[x])
    {
        x++;
    }
    return x;
}

string tasks::edgeLabel(node* var) {
    int st, ed;

    st = var->ParentStartIndex;
    ed = var->ParentEndIndex;

    return sequence.substr(st, (ed - st) + 1);
}


void tasks::buildGST()
{

        node* T = NULL;
        int number= sizeof(addresses)/sizeof(addresses[0]);

        for(int n=0; n<number;n++)
        {
            sequence+= *addresses[n];
        }
        sequence_len = sequence.length();
        cout<<"sequence_len: "<<sequence_len<<endl;
        T=root;
        for (int v = 0; v < sequence.length(); v++)
        {
            string ins = sequence.substr(v, sequence.length());
            T = insertSuffix(T, ins);
            //T = findPath(T, ins, n);
        }

        cout<<"GST is ready."<<endl;
        cout<<"looping leafCount "<<leafCount<<endl;
        cout<<"Number of internal Nodes: "<<internalNodeCount<<endl;

        int previous=0;
        int current=0;
        for(int n=0; n<number;n++)
        {
            string str= *addresses[n];
            int strLen = str.length();
            if(n==0)
            {
                previous=0;
                current= previous+strLen;
                treeCleanUp(root,previous, current, n);
            }
            else
            {

                previous=current;
                current= previous+strLen;
                treeCleanUp(root,previous, current, n);
            }
            cout<<"cleaned up: "<<n<<endl;
        }
        outfile.open(ReportPath.c_str(), ios::out);
        coloring(root);
        outfile.close();
        int pinak= bwtIndex(root);
        cout<<"twos: "<<pinak<<endl;
}

void tasks::buildLCS(int a, int b)
{
        node* T = NULL;
        int number= sizeof(addresses)/sizeof(addresses[0]);

        for(int n=0; n<number;n++)
        {
            if(n==a || n==b)
            {
                sequence+= *addresses[n];
                sequence_len = sequence.length();
            }
        }
        cout<<"sequence_len: "<<sequence_len<<endl;
        T=root;
        for (int v = 0; v < sequence.length(); v++)
        {
            string ins = sequence.substr(v, sequence.length());
            T = insertSuffix(T, ins);
            //T = findPath(T, ins, n);
        }

        cout<<"GST is ready."<<endl;
        cout<<"looping leafCount "<<leafCount<<endl;
        cout<<"Number of internal Nodes: "<<internalNodeCount<<endl;

        int previous=0;
        int current=0;
        int checker=0;
        for(int n=0; n<number;n++)
        {


            if(n==a)
            {
                string str= *addresses[n];
                int strLen = str.length();
                checker=0;
                if(checker==0)
                {
                    previous=0;
                    current= previous+strLen;
                    treeCleanUp(root,previous, current, n);
                }
                cout<<"cleaned up: "<<n<<endl;
            }
            else if(n==b)
            {
                string str= *addresses[n];
                int strLen = str.length();
                checker=1;
                if(checker==1)
                {
                    previous=current;
                    current= previous+strLen;
                    treeCleanUp(root,previous, current, n);
                }
                cout<<"cleaned up: "<<n<<endl;

            }
        }
        string alpha="";
        outfile.open(LCSReportPath.c_str(), ios::out);
        coloring(root);
        outfile.close();

        outfile.open(LCSReportPath.c_str(), ios::out);
        alpha= getLCS(root);
        outfile<<"\n"<<endl;
        outfile<<"\n"<<endl;
        outfile<<"\n"<<endl;
        outfile<<alpha<<endl;
        cout<<"LCS complete"<<endl;
        outfile.close();

}

tasks::node* tasks::insertSuffix(node* n, string suffix)
{
    node* curr = n;

    if(curr->suffixLink!=NULL and curr->nodeId ==1) //Case I-B
    {
        u = curr;
        v = u->suffixLink;
        curr= findPath(v, suffix);
    }
    else if(curr->suffixLink!=NULL and curr->nodeId !=1) //Case I-A
    {
        u = curr;
        v = u->suffixLink;
        string vlabel = edgeLabel(v);
        int commonStringCount = vlabel.length();
        string remainingString = sequence.substr(commonStringCount, (suffix.length() - commonStringCount));
        curr = findPath(v, remainingString);
    }
    else if(curr->suffixLink == NULL and curr->nodeId ==1) //Case II-B
    {
        u = curr;
        string beta = edgeLabel(curr);
        string betaPrime;
        if(beta.length()==1)
        {
            betaPrime = "";
        }
        else
        {
            betaPrime = beta.substr(1,(beta.length()-1));
        }

        uPrime = u->parent;
        vPrime = uPrime->suffixLink;
        //NodeHop Step
        if(betaPrime =="")
        {
            v = vPrime;
        }
        else
        {
            v = nodeHop(vPrime, betaPrime);
        }
        //End of NodeHop Step. Creation of Suffix Link
        u->suffixLink =v;
        int commonStringCount = walkdown(suffix, betaPrime);
        string remainingString = sequence.substr(commonStringCount, (suffix.length() - commonStringCount));
        curr = findPath(v, remainingString);
    }
    else if(curr->suffixLink == NULL and curr->nodeId !=1) //Case II-A
    {
        u = curr;
        string beta = edgeLabel(u);
        uPrime = u->parent;
        vPrime = uPrime->suffixLink;
        string vPrimeLabel = edgeLabel(vPrime);
        int matchingSuffixAtVPrime =walkdown(suffix, vPrimeLabel);
        string remainingStringAtVPrime = sequence.substr(matchingSuffixAtVPrime, (suffix.length() - matchingSuffixAtVPrime));
        //NOdeHop Step
        v = nodeHop(vPrime, beta);
        //End of NodeHop Step. Creation of Suffix Link
        u->suffixLink = v;
        string vLabel = edgeLabel(v);
        int matchingSuffixAtV = walkdown(remainingStringAtVPrime, vLabel);
        string remainingStringAtV= remainingStringAtVPrime.substr(matchingSuffixAtV, (remainingStringAtVPrime.length()-matchingSuffixAtV));
        curr= findPath(v, remainingStringAtV);
    }
    return curr;
}

tasks::node* tasks::nodeHop(node* vPrime, string beta)
{
    node* ptr = vPrime;
    node* tempPtr = NULL;

    for(int i=0; i<MAX_CHAR; i++)
    {
        if(ptr->children[i]==NULL)
        {
            continue;
        }
        else
        {
            tempPtr = ptr->children[i];
            string label = edgeLabel(tempPtr);
            if (label[0] != beta[0])
            {
                    continue;
            }
            else
            {
                //Check 3 conditions.
                //1) label < Beta. 2) label > Beta 3) Beta = Label
                if(label.length()== beta.length())
                {
                    ptr = tempPtr;
                }
                else if(label.length() > beta.length())
                {
                    int commonStringLength = walkdown(label, beta);
                    node* internalNode = (node*)malloc(sizeof(node));
                    internalNode->childCounter =0; //Setting new internal Nodes child counter to 0 by default.
                    for(int p =0; p<MAX_CHAR; p++) // Clearinig garbage of pointers before using them further
                    {
                        internalNode->children[p] = NULL;
                    }
                    internalNodeCount++;
                    internalNode->nodeId = (internalNodeCount+sequence_len);
                    internalNode->suffixId=0;
                    internalNode->ParentStartIndex = tempPtr->ParentStartIndex;
                    internalNode->ParentEndIndex = (internalNode->ParentStartIndex + commonStringLength - 1);
                    tempPtr->ParentStartIndex = (internalNode->ParentEndIndex + 1);
                    string tempEdgeLabel = edgeLabel(tempPtr);
                    int index1 = getChildIndex(tempEdgeLabel[0]);
                    internalNode->children[index1] = tempPtr;
                    internalNode->childCounter +=1;
                    tempPtr->parent = internalNode;
                    string internalNodeEdgeLabel = edgeLabel(internalNode);
                    int index2 = getChildIndex(internalNodeEdgeLabel[0]);
                    ptr->children[index2] = internalNode;
                    internalNode->color= -1;
                    internalNode->visited=false;
                    node* frontTracer = internalNode;
                    node* backTracer= internalNode;
                    string pathLabel="";
                    while(frontTracer->parent !=NULL)
                    {
                        backTracer=frontTracer;
                        frontTracer= frontTracer->parent;
                        string pl= edgeLabel(backTracer);
                        reverse(pl.begin(), pl.end());
                        pathLabel += pl;
                    }
                    internalNode->stringDepth= pathLabel.length();
                    //logs
//                    cout<<"for internalNode "<<internalNode->nodeId<<endl;
//                    cout<<"stringDepth: "<<internalNode->stringDepth<<endl;
//                    cout<<"for tempPtr "<<tempPtr->nodeId<<endl;
//                    cout<<"stringDepth: "<<tempPtr->stringDepth<<endl;
//                    cout<<"************************************"<<endl;
                    //end of logs
                    internalNode->parent = ptr;
                    goto RET;
                }
                else //label.length() < beta.length()
                {
                    ptr = tempPtr;
                    int commonStringLength = walkdown(label, beta);
                    string remainingString= beta.substr(commonStringLength, (beta.length()-commonStringLength));
                    ptr= nodeHop(ptr,remainingString);
                    goto RET;
                }

            }//end of inner else
        } //end of outer else
    } //End of For
RET:
    return ptr;
}


tasks::node* tasks::findPath(node* n, string suffix)
{
    node* curr = NULL;
    node* temp = NULL;
    curr = n;

    if(curr->childCounter == 0)
    {
        curr->childCounter += 1;
        node* leaf = (node*)malloc(sizeof(node));
        char c = suffix[0];
		int index= getChildIndex(c);
        curr->children[index] = leaf;
        leaf->parent = curr;
        leaf->ParentStartIndex = (sequence_len - suffix.length());
        leaf->ParentEndIndex = sequence_len - 1;
        sufId += 1;
        leaf->suffixId = sufId;
        leafCount++;
        leaf->nodeId = 0;
        leaf->next = NULL;
        leaf->parent = curr;
        leaf->color=-2;
        curr = leaf->parent;
        leaf->visited=false;
        goto RET;
    }
    else if(curr->childCounter > 0)
    {
        for(int i=0; i<MAX_CHAR; i++)
        {
            if(curr->children[i]==NULL && (i != MAX_CHAR-1))
            {
                continue;
            }
            else if(curr->children[i]==NULL && (i == MAX_CHAR-1) && (curr->childCounter >0))
            {
             INS:
                curr->childCounter += 1;
                node* leaf = (node*)malloc(sizeof(node));
                char c = suffix[0];
                int index = getChildIndex(c);
                curr->children[index] = leaf;
                leaf->parent = curr;
                leaf->ParentStartIndex = (sequence_len - suffix.length());
                leaf->ParentEndIndex = sequence_len - 1;
                sufId += 1;
                leaf->suffixId = sufId;
                leafCount++;
                leaf->nodeId = 0;
                leaf->next = NULL;
                leaf->parent = curr;
                curr = leaf->parent;
                leaf->color = -2;
                leaf->visited=false;
                goto RET;
            }
            else
            {

                temp = curr->children[i];
                string label = edgeLabel(temp);

                if (label[0] != suffix[0])
                {
                    if(i == MAX_CHAR-1) //children array exhausted and Match not found.
                    {
                        goto INS;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    //Checking two scenarios.
                    //1) label > suffix. 2) suffix > label
                    if(label.length() > suffix.length())
                    {
                        //1) label > suffix
                        int commonStringLength = walkdown(label, suffix);
                        node* internalNode = (node*)malloc(sizeof(node));
                        internalNode->childCounter =0; //Setting new internal Nodes child counter to 0 by default.
                        for(int p =0; p<MAX_CHAR; p++) // Clearinig garbage of pointers before using them further
                        {
                            internalNode->children[p] = NULL;
                        }
                        internalNodeCount++;
                        internalNode->nodeId = (internalNodeCount+sequence_len);
                        internalNode->suffixId=0;
                        internalNode->ParentStartIndex = temp->ParentStartIndex;
                        internalNode->ParentEndIndex = (internalNode->ParentStartIndex + commonStringLength - 1);
                        temp->ParentStartIndex = (internalNode->ParentEndIndex + 1);
                        string tempEdgeLabel = edgeLabel(temp);
                        int index1 = getChildIndex(tempEdgeLabel[0]);
                        internalNode->children[index1] = temp;
                        internalNode->childCounter +=1;
                        temp->parent = internalNode;
                        string internalNodeEdgeLabel = edgeLabel(internalNode);
                        int index2 = getChildIndex(internalNodeEdgeLabel[0]);
                        curr->children[index2] = internalNode;
                        internalNode->parent = curr;
                        internalNode->color= -1;
                        internalNode->visited=false;
                        node* frontTracer = internalNode;
                        node* backTracer= internalNode;
                        string pathLabel="";
                        while(frontTracer->parent !=NULL)
                        {
                            backTracer=frontTracer;
                            frontTracer= frontTracer->parent;
                            string pl= edgeLabel(backTracer);
                            reverse(pl.begin(), pl.end());
                            pathLabel += pl;
                        }
                        internalNode->stringDepth= pathLabel.length();

                        //logs
//                        cout<<"for internalNode "<<internalNode->nodeId<<endl;
//                        cout<<"stringDepth: "<<internalNode->stringDepth<<endl;
//                        cout<<"for temp "<<temp->nodeId<<endl;
//                        cout<<"stringDepth: "<<temp->stringDepth<<endl;
//                        cout<<"************************************"<<endl;
                        //end of logs
                        string remainingString = suffix.substr(commonStringLength, (suffix.length() - commonStringLength));
                        findPath(internalNode, remainingString);
                    }
                    else
                    {
                        //2) suffix > label
                        //check two scenarios here.
                        //A) commonStringLength >= label length. B) label length > commonStringLength

                        int commonStringLength = walkdown(label, suffix);
                        if (commonStringLength >= label.length())
                        {
                            string remainingSuffix = suffix.substr(commonStringLength, (suffix.length() - commonStringLength));
                            findPath(temp, remainingSuffix);
                        }
                        else
                        {
                            int commonStringLength = walkdown(label, suffix);
                            node* internalNode = (node*)malloc(sizeof(node));
                            internalNode->childCounter =0; //Setting new internal Nodes child counter to 0 by default.
                            for(int p =0; p<MAX_CHAR; p++) // Clearinig garbage of pointers before using them further
                            {
                                internalNode->children[p] = NULL;
                            }
                            internalNodeCount++;
                            internalNode->nodeId = (internalNodeCount+sequence_len);
                            internalNode->suffixId=0;
                            internalNode->ParentStartIndex = temp->ParentStartIndex;
                            internalNode->ParentEndIndex = (internalNode->ParentStartIndex + commonStringLength - 1);
                            temp->ParentStartIndex = (internalNode->ParentEndIndex + 1);
                            string tempEdgeLabel = edgeLabel(temp);
                            int index1 = getChildIndex(tempEdgeLabel[0]);
                            internalNode->children[index1] = temp;
                            internalNode->childCounter +=1;
                            temp->parent = internalNode;
                            string internalNodeEdgeLabel = edgeLabel(internalNode);
                            int index2 = getChildIndex(internalNodeEdgeLabel[0]);
                            curr->children[index2] = internalNode;
                            internalNode->parent = curr;
                            internalNode->color= -1;
                            internalNode->visited= false;
                            node* frontTracer = internalNode;
                            node* backTracer= internalNode;
                            string pathLabel="";
                            while(frontTracer->parent !=NULL)
                            {
                                backTracer=frontTracer;
                                frontTracer= frontTracer->parent;
                                string pl= edgeLabel(backTracer);
                                reverse(pl.begin(), pl.end());
                                pathLabel += pl;
                            }
                            internalNode->stringDepth= pathLabel.length();
                            //logs
//                            cout<<"for internalNode "<<internalNode->nodeId<<endl;
//                            cout<<"stringDepth: "<<internalNode->stringDepth<<endl;
//                            cout<<"for temp "<<temp->nodeId<<endl;
//                            cout<<"stringDepth: "<<temp->stringDepth<<endl;
//                            cout<<"************************************"<<endl;
                            //end of logs
                            string remainingString = suffix.substr(commonStringLength, (suffix.length() - commonStringLength));
                            findPath(internalNode, remainingString);
                        }
                    }
                    goto RET;
                }
			}
		} //end of For
	} //if(curr->childCounter > 0)
RET:
    return curr;
}

void tasks::treeCleanUp(node* r, int previous, int current, int color)
{
    node* curr = r;
    node* temp = NULL;

    for(int z =0; z<MAX_CHAR; z++)
    {
        if(curr->children[z] !=NULL)
        {
            temp = curr->children[z];
            //string elabel= edgeLabel(temp);
            if(temp->suffixId !=0)
            {
                if( previous <= temp->ParentStartIndex && temp->ParentStartIndex < current)
                {
                    temp->ParentEndIndex = (current-1);
                    temp->color= color;
                    temp->visited=true;
                }
            }
            else
            {
                treeCleanUp(temp, previous, current,color);
            }
        }
        else
        {
            continue;
        }
    }
}

void tasks::coloring(node* r)
{
    node* curr = r;
    node* temp= NULL;

    static int zero =0;
    int dummy=0;
    for(int i=0; i<MAX_CHAR; i++)
    {
        if(curr->children[i]==NULL)
        {
            dummy++;
        }
        else
        {
            temp= curr->children[i];
            if(temp->color == -1)
            {
                coloring(temp);

            }
            else
            {
                outfile<<"Temp color: "<<temp->color<<endl;
                dummy++;
            }
        }
    }
    color(curr);
    outfile<<"colored nodeId: "<<curr->nodeId<<"colored Suf id: "<<curr->suffixId<<" color: "<<curr->color<<endl;
    outfile<<"curr Label: "<<edgeLabel(curr);
}

void tasks::color(node* curr)
{
    set<int> colors;
    int col;
    for(int z=0; z<MAX_CHAR; z++)
    {
        if(curr->children[z]==NULL)
        {
            continue;
        }
        else
        {
            col = curr->children[z]->color;
            outfile<<"Color Inserted to set: "<<col<<endl;
            colors.insert(col);
        }
    }
    int getSize = colors.size();
    if(getSize > 1)
    {
        curr->color = maxColor;
    }
    else
    {
        int getColor;
        set<int>::iterator itr;
        for(itr= colors.begin(); itr!=colors.end();++itr)
        {
            getColor = *itr;
        }
        curr->color = getColor;
    }
}

int tasks::bwtIndex(node* r)
{
    node* curr = r;
    node* temp = NULL;
    static int myLeaf =0;
    static int mis=0;
    for(int z =0; z<MAX_CHAR; z++)
    {
        if(curr->children[z] !=NULL)
        {
            temp = curr->children[z];
            string elabel= edgeLabel(temp);
            if(temp->suffixId !=0)
            {
                if(temp->color==2)
                {
                    mis++;
                }

                myLeaf++;
            }
            else
            {
                bwtIndex(temp);
            }
        }
        else
        {
            continue;
        }
    }
return mis;
}


void tasks::displaySD(node* r)
{
    node* curr = r;
    node* temp = NULL;
    static int counter =0;
    for(int z= 0; z < MAX_CHAR; z++)
    {
        if(curr->children[z]!=NULL)
        {
            temp= curr->children[z];
            if(temp->suffixId != 0)
            {
                continue;
            }
            else
            {

                if(temp->color==2)
                {
                    counter++;
                    if(counter%l ==0 && counter!=0)
                        cout<<"\n";
                    cout<<temp->stringDepth<<"\t";
                    displaySD(temp);
                }

            }

        }
        else
        {
            continue;
        }
    }
}

int tasks:: deepestIntNode(node* r)
{
    node* curr = r;
    node* temp = NULL;
    static int MAX=0;
    static int nID=0;
    for(int z= 0; z < MAX_CHAR; z++)
    {
        if(curr->children[z]!=NULL)
        {
            temp= curr->children[z];
            if(temp->suffixId == 0)
            {
                if(temp->color == maxColor)
                {
                    int s_Depth = temp->stringDepth;
                    if(s_Depth>MAX)
                    {
                        MAX=s_Depth;
                        nID= temp->nodeId;
                    }
                }
                deepestIntNode(temp);
            }
            else
            {
                continue;
            }

        }
        else
        {
            continue;
        }
    }

return nID;
}

string tasks::getLCS(node* r)
{
    node* curr = r;
    node* temp= NULL;
    int nID= deepestIntNode(curr);

    for(int z= 0; z < MAX_CHAR; z++)
    {
        if(curr->children[z]!=NULL)
        {
            temp= curr->children[z];
            if(temp->suffixId != 0)
            {
                continue;
            }
            else
            {
                if(temp->nodeId == nID)
                {
                    cout<<"deepest Node ID: "<<nID<<endl;
                    node* frontTracer = temp;
                    node* backTracer= temp;
                    pLabel="";
                    while(frontTracer->parent != NULL)
                    {
                        backTracer = frontTracer;
                        frontTracer = frontTracer->parent;
                        string pl= edgeLabel(backTracer);
                        reverse(pl.begin(), pl.end());
                        pLabel += pl;
                    }
                    reverse(pLabel.begin(), pLabel.end());
                    outfile<<pLabel<<endl;
                }
                else
                {
                    getLCS(temp);
                }

            }

        }
        else
        {
            continue;
        }
    }
    return pLabel;
}

void tasks::fingerPrints()
{

}







