#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int numFrames;
int numCount;
int* stringRef;

string Optimal(vector<int>);
    int determineRep(vector<int>, int);
string LRU(vector<int>);
    vector<int> addToRep(vector<int>, int);
string Clock(vector<int>);
    int repClock(vector<int> , int* , int*);

bool ifPresent(vector<int>, int);
bool ifPresent(vector<int> frame, int addNum)
{
        if (frame.empty())return false;
        for ( int i = 0; i < frame.size(); i++)
        {
                if (frame[i] == addNum){return true;}
        }return false;
}

int determineRep(vector<int> frame, int start)
{
    if (start==(numCount-1)){return 0;}

    int position[numFrames];
    for (int i=0; i<numFrames; i++){position[i]=0;}
    for (int i=0; i<numFrames; i++){
        for (int j=start+1; j<numCount; j++){
            int num = stringRef[j];
            if (frame[i] == num){position[i] = j-start; break;}
        }
    }
    for (int i=0; i<numFrames; i++){if (position[i] == 0)return i;}
    int j=0;
    int max = position[0];
    for (int i=1; i<numFrames; i++){
        if (position[i] > max){
           max = position[i];
           j=i;
        }
    }
    return j;
}

vector<int> addToRep(vector<int> replacement, int addNum)
{
    for (int i=0; i<replacement.size(); i++){
        if (replacement[i] == addNum){replacement.erase (replacement.begin()+i);}
    }
    replacement.push_back(addNum);
    return replacement;
}

int repClock(vector<int> frame, int* cursor, int* refBits)
{
    while (1){
        if (refBits[*cursor] == 0){return *cursor;}
        else {
            refBits[*cursor]=0;
            if (*cursor==numFrames-1){*cursor=0;}
            else{*cursor = *cursor +1;}
        }
    }
}

string Optimal(vector<int> frame)
{
        int faults = 0;
        for(int i = 0; i < numCount; i++){
                int addNum = stringRef[i];
                if (frame.size() == numFrames){
                        if(!ifPresent(frame,addNum)){int index = determineRep(frame, i);frame[index] = addNum; faults++;}
                }else{
                        if(!ifPresent(frame, addNum)){frame.push_back(addNum); faults++;}
                }
        }
        string ofFrames = " -frame:";
        string test;
        stringstream ss;
        for (int i=0; i<numFrames; i++){ss << frame[i];ss >> test; ss.clear(); ofFrames += (test + " ");}
        ss.clear();
        ss << faults;
        ss >> test;
        string numFaults = "  -page faults: " + test;
    return (ofFrames + "\n" + numFaults + "\n");
}

string LRU(vector<int> frame)
{
        int faults = 0;
        vector<int> replacement;

        for(int i = 0; i < numCount; i++){
                int addNum = stringRef[i];
                if(frame.size() == numFrames){
                        if (ifPresent(frame,addNum)){replacement = addToRep(replacement, addNum);}
                        else{
                                int value = replacement.front();
                                replacement.erase (replacement.begin());
                                for (int i = 0; i<numFrames; i++){
                                        if(frame[i] == value){frame[i] = addNum; faults ++; break;}
                                }
                                replacement = addToRep(replacement, addNum);
                        }
                }

                else{
                        if (ifPresent(frame,addNum)){replacement = addToRep(replacement, addNum);}
                        else{frame.push_back(addNum); replacement = addToRep(replacement, addNum); faults++;}
                }
        }
        string ofFrames = " -frame:";
        string test;
        stringstream ss;
        for (int i=0; i<numFrames; i++){ss << frame[i];ss >> test; ss.clear(); ofFrames += (test + " ");}
        ss.clear();
        ss << faults;
        ss >> test;
        string numFaults = "  -page faults: " + test;
    return (ofFrames + "\n" + numFaults + "\n");
}

string Clock(vector<int> frame)
{
        int faults = 0;
        int cursor = 0;
        int* refBits = new int[numFrames];
        for (int i = 0; i < numFrames; i++)
                refBits[i]=-1;
        for (int i=0; i<numCount; i++){
        int addNum = stringRef[i];
            if (frame.size() == numFrames){
                if (!ifPresent(frame, addNum)) {
                    int index = repClock(frame, &cursor, refBits);
                    frame[index] = addNum;
                    refBits[cursor]=1;
                    if (cursor==numFrames-1){cursor=0;}
                    else{cursor++;}
                    faults++;
                }
            }

            else {
               if (!ifPresent(frame, addNum)) {
                    frame.push_back(addNum);
                    refBits[frame.size()-1]=1;
                    refBits[cursor]=1;
                    if (cursor==numFrames-1){cursor=0;}
                    else{cursor++;}
                    faults++;
                }
           }
        }

        string ofFrames = " -frame:";
        string test;
        stringstream ss;
        for (int i=0; i<numFrames; i++){ss << frame[i];ss >> test; ss.clear(); ofFrames += (test + " ");}
        ss.clear();
        ss << faults;
        ss >> test;
        string numFaults = "  -page faults: " + test;
    return (ofFrames + "\n" + numFaults + "\n");
        return "\n";
}

int main( int argc, char ** argv)
{
        if (argc !=2) { cout << "Number of arguments is incorrect!"; exit(1);}

        stringRef = new int[5000];
        numCount = 0;
        int readInt;
        string aString = string(argv[1]);
        stringstream convert (aString);
        convert >> numFrames;
        vector<int> frame;

        while(1)
        {
                if(1 != scanf("%d", & readInt))break;
                stringRef[numCount] = readInt;numCount++;
        }

        string doOptimal = Optimal(frame);
        cout << "Optimal:\n" << doOptimal << "\n";

        string doLru = LRU(frame);
        cout << "\nLRU:\n" << doLru << "\n";

        string doClock = Clock(frame);
        cout << "Clock: \n" << doClock << "\n";
}
