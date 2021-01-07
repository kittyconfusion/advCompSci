#include "slist.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
/*
Class Library File
*/


// Constructor
  sList::sList() {
    headPtr = nullptr;
  }
// Destructor    
  sList::~sList() {
    clear();
  }

// add(value)				//Adds a new value to the end of this list.
  void sList::add(void *value) {
    Node *n = new Node{nullptr, value};
    if(!headPtr) {
      headPtr = n;
    }
    else {
      Node *currentNode = headPtr;
      while(currentNode->nextNode != nullptr) {
        currentNode = currentNode->nextNode;
      }
      currentNode->nextNode = n;
    }
  }
// clear()					//Removes all elements from this list.
  void sList::clear() {
    Node *currentNode = headPtr;
    while(currentNode->nextNode != nullptr) {
        Node *nextNode = currentNode->nextNode;
        delete(currentNode);
        currentNode = nextNode;
    }
    headPtr = nullptr;
  }

// equals(list)				//Returns true if the two lists contain the same elements in the same order.
  bool sList::equals(sList *otherList) {
    Node *currentNode = headPtr;
    Node *otherCurrentNode = otherList->headPtr;
    
    while(currentNode->nextNode != nullptr && otherCurrentNode->nextNode != nullptr) {
      if(currentNode->dataptr != otherCurrentNode->dataptr) {
        return false;
      }
      currentNode = currentNode->nextNode;
      otherCurrentNode = otherCurrentNode->nextNode;
    }

    return true;
  }
//get(index)				//Returns the element at the specified index in this list. Starts counting at 0.
  void* sList::get(int index) {
    if(index < size() - 1) {
      int currentIndex = 0;
      Node *currentNode = headPtr;
      
      while(currentNode->nextNode != nullptr) {
        if(index == currentIndex) {
          return currentNode->dataptr;
        }
        currentNode = currentNode->nextNode;
        currentIndex++;
      }
      return nullptr;
    }
    else {
      cout << "Get index out of bounds. Requested " << index << " but less than " << size() - 1 << " is allowed. Returning nullptr." << endl;
      return nullptr;
    }
  }
//insert(index, value)		//Inserts the element into this list before the specified index.
  void sList::insert(int index, void *value) {
    if(index >= size()) { //Put value at end
      add(value);
    }
    else {
      Node *n = new Node{nullptr, value};
      int currentIndex = 0;
      Node *currentNode = headPtr;
      
      while(currentNode->nextNode != nullptr) {
        Node *tempPtr;
        tempPtr = currentNode->nextNode;
        if(index == currentIndex + 1) {
          tempPtr = currentNode->nextNode; 
          currentNode->nextNode = n;
          n->nextNode = tempPtr;
        }
        currentNode = tempPtr;
        currentIndex++;
      }
    }
  }
//exchg(index1, index2)		//Switches the payload data of specified indexex.
  void sList::exchg(int index1, int index2) {
    if(index1 < size() && index2 < size()) {
      Node *indexOneNode = headPtr;
      int currentIndex = 0;
      
      while(currentIndex != index1) {
        indexOneNode = indexOneNode->nextNode;
        currentIndex++;
      }
      Node *indexTwoNode = headPtr;
      currentIndex = 0;
      
      while(currentIndex != index2) {
        indexTwoNode = indexTwoNode->nextNode;
        currentIndex++;
      }
      void *tempdata = indexOneNode->dataptr;
      indexOneNode->dataptr = indexTwoNode->dataptr;
      indexTwoNode->dataptr = tempdata;
    }
    else {
      cout << "Exchange index out of bounds. Requested " << index1 << " and " << index2 << " but only up to " << size() - 1 << " is allowed." << endl;
    }
    
  }
//swap(index1,index2)		//Swaps node located at index1 with node at index2
  void sList::swap(int index1, int index2) {
    if(index1 < size() && index2 < size()) {
      Node **nodeOnePtr = &headPtr;
      int currentIndex = 0;
      
      while(currentIndex != index1) {
        nodeOnePtr = &((*nodeOnePtr)->nextNode);
        currentIndex++;
      }
      Node **nodeTwoPtr = &headPtr;
      currentIndex = 0;
      
      while(currentIndex != index2) {
        nodeTwoPtr = &((*nodeTwoPtr)->nextNode);
        currentIndex++;
      }
      
      //A lot of pseudo-code was written and tested in order to get this figured out and working.
      Node* nodeOneBackup = *(nodeOnePtr);
      *(nodeOnePtr) = *(nodeTwoPtr);
      *(nodeTwoPtr) = nodeOneBackup;
      Node* n1 = *(nodeTwoPtr);
      Node* n2 = *(nodeOnePtr);
      Node* n1NextNodeBackup = n1->nextNode;
      n1->nextNode = n2->nextNode;
      n2->nextNode = n1NextNodeBackup;
      
      /* 
      //Original and incorrect code
      Node* tempOne = indexOneNode;
      indexOneNode = indexTwoNode;
      Node* tempTwo = indexTwoNode->nextNode;
      indexTwoNode->nextNode = tempOne->nextNode;
      tempOne->nextNode = tempTwo->nextNode;
      indexTwoNode = tempOne;
      */
      
    }
    else {
      cout << "Swap index out of bounds. Requested " << index1 << " and " << index2 << " but only up to " << size() - 1 << " is allowed." << endl;
    }
    
  }
// isEmpty()				//Returns true if this list contains no elements.
  bool sList::isEmpty() {
    if(headPtr == nullptr) {
      return true;
    }
    return false;
  }
// remove(index)			//Removes the element at the specified index from this list.
  void sList::remove(int index) {
    if(index < size()) {
      Node **ptrToNode = &headPtr;
      int currentIndex = 0;
      
      while(currentIndex != index) {
        ptrToNode = &((*ptrToNode)->nextNode);
        currentIndex++;
      }
      Node* nodeToRemove = *(ptrToNode);
      *(ptrToNode) = (*ptrToNode)->nextNode;
      delete(nodeToRemove);
    }
    else {
      cout << "Notice: Requested remove index out of bounds. Requested " << index << " but only up to " << size() - 1 << " is allowed." << endl;
    }
  }
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
  void sList::set(int index, void* value) {
    int currentIndex = 0;
    Node *currentNode = headPtr;
    while(currentNode->nextNode != nullptr) {
      if(index == currentIndex) {
        currentNode->dataptr = value;
      }
      currentNode = currentNode->nextNode;
      currentIndex++;
    }
  }
// size()					//Returns the number of elements in this list.
  int sList::size() {
    int c = 0;
    Node* n = headPtr;

    while(n != nullptr) {
      c++;
      n = n->nextNode;
    }

    return c;
  }
// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
  sList* sList::subList(int startIndex, int length) {
    if(startIndex >= 0 && length < size() - startIndex) {
      sList* subL = new sList();
      int currentIndex = 0;
      Node *currentNode = headPtr;
      
      while(currentNode->nextNode != nullptr) {
        if(currentIndex >= startIndex && currentIndex <= startIndex + length) {
          subL->add(currentNode->dataptr);
        }
        currentNode = currentNode->nextNode;
        currentIndex++;
      }
      
      return subL;
      
    }
    else {
      cout << "Notice: Requested sublist index out of bounds. Requested start of " << startIndex << " and length of " << length << " but only a lenght up to " << size() - startIndex  << " is allowed for the specified start index. Returning nullptr." << endl;
      return nullptr;
    }
  }
  
// toString()				//Converts the list to a printable string representation.
  string
  
  
  sList::toString() {
    stringstream s;
    Node *currentNode = headPtr;
    bool firstElement = true;
    
    if(headPtr != nullptr) {
      while(currentNode->nextNode != nullptr) {
        if(firstElement) {
          s << "[" << currentNode->nextNode->dataptr;
          firstElement = false;
        }
        else {
          s << ", " << currentNode->nextNode->dataptr;
        }
        currentNode = currentNode->nextNode;
        //s << "\n" << currentNode;
      }
    }
    s << "]";
    return s.str();
  }
