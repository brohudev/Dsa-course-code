#include "IdStack.h"
#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
using namespace std;

bool isEncoded(string iD) {                         // Takes an ID and sees if there is a '(' within the string (we don't have to check for ')' since we know they are matched)
    if (iD.find('(') == string::npos) {
        return false;
    }
    return true;
}

string strReverse(string numStr) {
    int i = numStr.size() - 1;                      // Size is the highest index + 1 because of 0th index (unless empty). In the case that string is empty, will just return the same string
    string reversed = "";

    for (i; i >= 0; i--) {
        reversed += numStr.at(i);
    }
    return reversed;
}

string idDecoder(string iD) {
    if (!isEncoded(iD)) {return iD;}

    int innerPar = iD.rfind('(');                                         // Reverse finds '(' (inner parenthesis)
    int outerPar = iD.substr(innerPar, iD.size()).find(')') + innerPar;   // Finds ')' (outer parenthesis) starting from last inner parenthesis; must add inner par as the .find() operation returns the index of character found where 0 == start of the last inner parenthesis 
    int numStrSize = outerPar - innerPar - 1;                             // Everything within a matching pair of parenthesis (xxxxxxx)
    int parStrSize = numStrSize + 2;                                      // Length within the matching parenthesis pair including parenthesis (needed for myStr.replace(x,Y,z) Y parameter)
    string parString = iD.substr(innerPar + 1, numStrSize);               // Starts substring after opening parenthesis until right before closing parenthesis
    string replaceStr = strReverse(parString);
    iD.replace(innerPar, parStrSize, replaceStr);

    return (idDecoder(iD));
}

int main(int argc, char * argv[]) {
    ArgumentManager am(argc, argv);
    string inFile = am.get("input");
    string outFile = am.get("output");
    ifstream input(inFile);
    ofstream output(outFile);
    iDStack firstBar;
    iDStack secondBar;
    iD * topFirstBar;
    iD * topSecondBar;
    iD * cu;
    string finalId;
    string currentLine = "";
    int dupeCount;
    bool isFirstBar = false;
    bool isSecondBar = false;

        while (getline(input, currentLine))
    {
        currentLine.erase(remove(currentLine.begin(), currentLine.end(), '\n'), currentLine.end());         // Removes unwanted characters
        currentLine.erase(remove(currentLine.begin(), currentLine.end(), '\r'), currentLine.end());         // Removes unwanted characters
        currentLine.erase(remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());          // Removes unwanted characters
        if (currentLine == "Bar1") {                       // Allows us to keep track if the bar switches to the other
            isFirstBar = true;
            isSecondBar = false;
            continue;
        }
        else if (currentLine == "Bar2") {                  // Allows us to keep track if the bar switches to the other
            isFirstBar = false;
            isSecondBar = true;
            continue;
        }
        if (currentLine.size() == 0) {
            continue;
        }
        
        finalId = idDecoder(currentLine);
        if (isFirstBar) {                                  // Pushes to firstBar
            firstBar.push(finalId, false);
            continue;
        }
        if (isSecondBar) {                                 // Pushes to secondBar
            secondBar.push(finalId, false);
            continue;
        }
    }

    topFirstBar = firstBar.getTop();                       // Gets top of both the first and second bars
    topSecondBar = secondBar.getTop();
    
    if (firstBar.getSize() == 0) {                         // Case where one bar has no ID information
        if (secondBar.getSize() == 0) {return 0;}
        else {
            secondBar.print(topSecondBar, output, false, false, false);
            return 0;
        }
    }
    if (secondBar.getSize() == 0) {
        firstBar.print(topFirstBar, output, false, false, false);
        return 0;
    }

    while (!secondBar.isEmpty()) {                         // Pushes all of the second bar into the first bar
        firstBar.push(topSecondBar->data, false);
        secondBar.pop(topSecondBar->data, topSecondBar, topSecondBar);
        if (!secondBar.isEmpty()) {
            topSecondBar = secondBar.getTop();
        }
    }
    
    topFirstBar = firstBar.getTop();                       // Resets topFirstBar to the firstBar's new top
    firstBar.sortAsc(topFirstBar, topFirstBar, firstBar.getSize());

    cu = topFirstBar;                                      // Used to iterate through the whole stack and find duplicated values
    while (cu != nullptr) {
        if (!cu->isGuilty) {                               // All ID's are default false for having guilt
            dupeCount = firstBar.idSearch(cu, cu->data);   // Returns either 1 (only one ID has the given idString), or 2 (where the IDs are duplicates of each other)
            if (dupeCount == 1) {                          // idSearch(...) sets all ID's it takes in to be guilty, so if only one of that ID was found, this resets that ID back to !guilty
                firstBar.idReset(cu, cu->data);
            }
        }
        else if (cu->isGuilty) {                           // If the current ID is guilty, it was set to guilty above, and will be removed from the list (it's a dupe)
            firstBar.pop(cu->data, topFirstBar, topFirstBar);
            topFirstBar = firstBar.getTop();
        }
        cu = cu->next;
    }

    topFirstBar = firstBar.getTop();
    firstBar.sortAsc(topFirstBar, topFirstBar, true);
    topFirstBar = firstBar.getTop();
    firstBar.print(topFirstBar, output, false, false, false);

    return 0;
}