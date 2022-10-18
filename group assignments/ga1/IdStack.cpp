#include "IdStack.h"

iDStack::iDStack() {                             // Default constructor initializes top and size.
    top = nullptr;
    size = 0;
}

iD* iDStack::getTop() {                          // Will be useful as we can then get store *top in a variable in main to use as a function parameter within a function call
    return top;
}

int iDStack::getSize() {
    return size;
}

bool iDStack::isEmpty() {                        // If condition is true, then top still has initial value from the constructor (nothing has been added to the stack)
    if (top == nullptr) {
        return true;
    }
    return false;
}

bool iDStack::isFull() {                         // Max size was said to be 100, so this is probably redundant
    if (size == 100) {
        return true;
    }
    return false;
}

bool iDStack::push(string idString, bool hasGuilt) {                      // Adds a new iD to the stack. 
    
    if (isFull()) {                                                       // Checks if the stack is full first.
        return false;
    }
    
    iD * temp = new iD;                                                   // Fills in given information to a temp node.
    temp->next = nullptr;
    temp->data = idString;
    temp->isGuilty = hasGuilt;

    if (isEmpty()) {                                                      // If stack is empty, temp is the original "top"
        top = temp;
        size++;
        return true;
    }

    temp->next = top;                                                     // Occurs when stack is not empty. First connects temp by pointing it to top. Then, reassigns top to temp.
    top = temp;
    size++;
    return true;
}

bool iDStack::pop(string& idString, iD * behind, iD * curr) {             // Will remove the wanted idString from the stack. Function has to be done recursively, so 2? node pointer have to be passed as well (curr = curr->next for the next call). Behind will be one place behind curr to make behind ->next = cu->next (assuming there are enough nodes).
    if (curr == nullptr) {                                                // This is when you go through the whole stack (empty or not) and you didn't find idString within any node
        return false;
    }

    if ((curr->data == idString) && (curr == top)) {                      // This branch only triggers within the first call of the function. If the iD is found, then it was found at the top where curr == behind. Simply assigns top to be the next node (or nullptr if there is exactly one node).
        top = curr->next;
        delete curr;
        size--;
        return true;
    }

    if (curr->data == idString) {                                         // Triggers when the found iD is after the top. In this case, the iD is found at curr, and behind is currently pointing to curr. Sets behind to instead point to the node after curr (or nullptr if the curr node is at the "bottom" of the stack)
        behind->next = curr->next;
        delete curr;
        size--;
        return true;
    }

    behind = curr;                                                        // Triggers when current node does not have the matching iD. Updates behind to be curr, and updates curr to point to next node. In the case that they are equal (at top), behind remains the same to allow curr to get one spot ahead (so behind is actually behind)
    curr = curr->next;

    return pop(idString, behind, curr);                                   // Recursively calls the function with updated nodes
}

int iDStack::idSearch(iD * node, string idString) {
    if (node == nullptr) {                                                // If node is nullptr, the stack is either completely empty and this is the first call to the function, or the node has reached the end of the stack.
        return 0;
    }
    if (node->data == idString) {                                         // Marks the given node as guilty. In main, if the final count is only 1, then idReset will be called as the node marked as guilty actually is innocent
        node->isGuilty = true;
        return 1 + (idSearch(node->next, idString));
    }

    return idSearch(node->next, idString);
}

void iDStack::idReset(iD * node, string idString) {
    if (node == nullptr) {                                                // If node is nullptr, the stack is either completely empty and this is the first call to the function, or the node has reached the end of the stack.
        return;
    }
    if (node->data == idString) {                                         // Will reset the target node as innocent since only one id was found with the idstring in idSearch
        node->isGuilty = false;
        return;
    }

    return idReset(node->next, idString);
}

string iDStack::removeLeadZeros(string idString) {                        // Will remove any leading zeros if they exist
    if (idString.size() == 1) {                                           // Edge case where an ID is of size 1. Will return a num string from 0-9.
        return idString;
    }
    if (idString.at(0) != '0') {
        return idString;
    }
    idString = idString.substr(1, 100);                                   // Removes 0 from front of string
    return removeLeadZeros(idString);                                     // Recursive call with updated string
}

bool iDStack::stringComparison(string behind, string curr, bool removedLeadingZeros) {
    if (behind.size() == 0) {
        return false;
    }
    if (!removedLeadingZeros) {
        behind = removeLeadZeros(behind);
        curr = removeLeadZeros(curr);
        removedLeadingZeros = true;

        if (behind.size() > curr.size()) {
            return true;
        }
        else if (behind.size() < curr.size()) {
            return false;
        }
    }

    int a = stoi(behind.substr(0, 1));
    int b = stoi(curr.substr(0, 1));
    if (a > b) {
        return true;
    }
    if (a < b) {
        return false;
    }

    if (behind.size() == 1) {
        return false;
    }

    behind = behind.substr(1, 100);
    curr = curr.substr(1, 100);
    return stringComparison(behind, curr, true);
}

void iDStack::swap(iD * upperNode, iD * lowerNode) {                      // Swaps data between two iD nodes
    iD * temp = new iD;                                                   // Creates a temp iD to hold the value of upper node
    temp->data = upperNode->data;
    temp->isGuilty = upperNode->isGuilty;
    temp->next = 0;

    upperNode->data = lowerNode->data;                                    // Updates upper node with data from lower node
    upperNode->isGuilty = lowerNode->isGuilty;

    lowerNode->data = temp->data;                                         // Updates lower node with data from temp (which has the original data of the upper node)
    lowerNode->isGuilty = temp->isGuilty;

    delete temp;
    return;
}

void iDStack::sortAsc(iD * behind, iD * curr, bool flag) {                // Works like a bubble sort. Will go through the stack and if higher value (behind) is greater than lower value (curr), then they will swap all the data between them.
    if (curr == nullptr) {                                                // When the end of the stack is reached
        if (flag) {                                                       // Checks if list is sorted correctly at this time. If so, return.
            return;
        }
        else {                                                            // If list is not sorted after going through all of it, the function is called again with reset values of behind and curr to be at the top again.
            curr = top;
            behind = top;
            flag = true;
            return sortAsc(behind, curr, flag);
        }
    }
    
    if (curr != behind) {
        if (stringComparison(behind->data, curr->data, false)) {
            flag = false;
            swap(behind, curr);
        }
    }
    behind = curr;                                                        // Updates iD nodes in preperation for the recursion call
    curr = curr->next;
    return sortAsc(behind, curr, flag);
}

void iDStack::print(iD * node, ofstream& out, bool finishedGuilty, bool guiltTag, bool innoTag) {                 // Print function with a node argument (initally the function should be called with the top as the parameter), the outfile, and a few boolean flags to correctly print out some information: "Innocent:", "Guilty:"
    if (node == nullptr) {                       // If node is nullptr, the stack is either completely empty and this is the first call to the function, or the node has reached the end of the stack and there is nothing else to print out
        if (!finishedGuilty) {
            finishedGuilty = true;
            return print(top, out, finishedGuilty, guiltTag, false);
        }
        return;
    }
    if (!finishedGuilty) {
        if (node->isGuilty) {
            if (!guiltTag) {
                //cout << "Guilty:" << endl;
                out << "Guilty:" << endl;
                guiltTag = true;
            }
            if (node->next != nullptr) {
                //cout << node->data << endl;
                out << node->data << endl;
            }
            else if (node->next == nullptr) {
                //cout << node->data;
                out << node->data;
            }
        }
        return print(node->next, out, finishedGuilty, guiltTag, innoTag);
    }

    if (!node->isGuilty) {
        if (!innoTag) {
            //cout << "Innocent:" << endl;
            out << "Innocent:" << endl;
            innoTag = true;
        }
        if (node->next != nullptr) {
            //cout << node->data << endl;
            out << node->data << endl;
        }
        else if (node->next == nullptr) {
            //cout << node->data;
            out << node->data;
        }
    }
    return print(node->next, out, finishedGuilty, guiltTag, innoTag);
}