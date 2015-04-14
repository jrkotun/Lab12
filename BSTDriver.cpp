#include "BinarySearchTree.h"
#include "BinaryTreeIterator.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }

   delete iter;
}

int main()
{
   //the unsorted ListArray of cds
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int numItems = cds->size();
   cout << numItems << endl;
   cout << endl;

   //test the binary search tree
   //insert all of the cds
   ListArrayIterator<CD>* iter = cds->iterator();
   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;

   BinaryTreeIterator<CD>* bst_iter = bst->iterator();
   bst_iter->setInorder();  //takes a snapshot of the data
   while(bst_iter->hasNext())
   {
      CD* cd = bst_iter->next();
      cd->displayCD();
   }
   delete bst_iter;

   int height = bst->getHeight();
   bool balance = bst->isBalanced();

   if(balance == true)
   {
       cout << "The height is " << height << " and it is balanced.";
   }
   else
   {
       cout << "The height is " << height << " and it is not balanced.";
   }

   //create a minimum height binary search tree
   BinarySearchTree<CD>* min_bst = bst->minimize();
   bst_iter = min_bst->iterator();

   //make sure that an inorder traversal gives sorted order
   bst_iter->setInorder();  //takes a snapshot of the data
   while(bst_iter->hasNext())
   {
      CD* cd = bst_iter->next();
      cd->displayCD();
   }
   delete bst_iter;

   height = min_bst->getHeight();
   balance = min_bst->isBalanced();

   if(balance == true)
   {
       cout << "The minimum height is " << height << " and it is balanced.";
   }
   else
   {
       cout << "The minimum height is " << height << " and it is not balanced.";
   }

   //create a complete binary search tree
   BinarySearchTree<CD>* complete_bst = bst->minimizeComplete();
   delete bst;

   //make sure that an inorder traversal gives sorted order
   bst_iter = complete_bst->iterator();
   bst_iter->setInorder();  //takes a snapshot of the data
   while(bst_iter->hasNext())
   {
      CD* cd = bst_iter->next();
      cd->displayCD();
   }
   delete bst_iter;

   height = complete_bst->getHeight();
   balance = complete_bst->isBalanced();

   if(balance == true)
   {
       cout << "The minimum height is " << height << " and it is balanced.";
   }
   else
   {
       cout << "The minimum height is " << height << " and it is not balanced.";
   }

   delete complete_bst;

   deleteCDs(cds);
   delete cds;
   return 0;
}
