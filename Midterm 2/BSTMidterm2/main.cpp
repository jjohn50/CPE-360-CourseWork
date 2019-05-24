#include <iostream>
#include <cmath>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
class TreeNode {
public:
    int value;
    TreeNode *right;
    TreeNode *left;

    TreeNode(){
        value = 0;
        right = left = NULL;
    }
};
class BST {
public:
    TreeNode *root;
    int height;
    double size;

    BST() {
        root = NULL;
    }

    //Functions that a BST must perform
    // 1. Search for a value
    TreeNode *searchBST(int key, TreeNode *start) {
        //check if start is null
        if (start == NULL) {
            cout << "could not find it" << endl;
            return NULL;
        }
            //check to see if you've found it (anchor value)
        else if (key == start->value) {
            cout << "value retrieved" << endl;
            return start;
        }
            //if you havent found it, if the key is less than the value of the node you are at go left, it it's greater, go right
        else {
            if (key > start->value)
                searchBST(key, start->right);
            else
                searchBST(key, start->left);
        }
    }


    // 2. Add new values to the tree
    void addNodeBST(int key) {
        // you can't use recursion for this
        TreeNode *slow, *fast;
        slow = fast = root;
        // want fast to fall off the tree
        // Step 1: Search for Key
        if (root == NULL) {
            root = new TreeNode;
            root->value = key;
            size++;
            return;
        } else {
            //use "fast" to go look for this 'key'
            // if "fast" falls off the tree, then this value does not exist
            //at this point, 'slow' to point to the parent of the new node
            //start by searching for this value
            //If you find it, don't add it. Just write a comment
            //If you don't find it. add it where you should have found it
            while (fast != NULL) {
                if (fast->value == key) {
                    cout << "Duplicate" << endl; //This is when you don't want duplicates
                    return;
                } else if (key > fast->value) {
                    slow = fast;
                    fast = fast->right;
                } else {
                    slow = fast;
                    fast = fast->left;
                }
            } //fast should have fallen off the tree
            //slow happens to be at the node which will become the new parent
            TreeNode *temp = new TreeNode;
            temp->value = key;

            if (key > slow->value) {
                slow->right = temp;
                size++;
            } else {
                slow->left = temp;
                size++;
            }
        }
    }

    // Step 4. Ways to display the content of the tree
    // In order trasnversal: must go to every value and print them out
    //Left->current-> right
    // Left, center, and right
    // With our example it would be 10,12,13,15,17,18,23
    void inorder(TreeNode *start) {
        if (start == NULL) {
            return;
        } else {
            inorder(start->left);
            cout << start->value << " " << endl;
            inorder(start->right);
        }
    }

    //PreOrder Transveral:
    //Current Node->Left node->Right node
    //15 12 10 13 18 17 23
    void preorder(TreeNode *start) {
        if (start == NULL) {
            return;
        } else {
            cout << start->value << " " << endl;
            preorder(start->left);
            preorder(start->right);
        }
    }

    //Post Order:
    //Left->Right->Center
    //Prefixes are with Root
    // pre->Root first
    //Post->Root last
    void postorder(TreeNode *start) {
        if (start == NULL) {
        } else {
            postorder(start->left);
            postorder(start->right);
            cout << start->value << " " << endl;
        }
    }

    /*int minValRSubTree(TreeNode *start) {
        int value;
        TreeNode *temp = start;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp->value;
    } */
    int maxValLSubTree(TreeNode *start) {
        int value;
        TreeNode *temp2 = start;
        while (temp2->right != NULL) {
            temp2 = temp2->right;
        }
        return temp2->value;
    }
    void placeBranch(TreeNode* branch)
    {
        //start everything at the root
        TreeNode* slow;
        TreeNode* fast;
        slow = fast = root;
        //if you pass the function a null pointer
        if(branch == NULL){
            //	cout<<"Null Pointer, no nodes needed to be moved"<<endl;
            return;
        }
        else{
            //use fast to go look for the key
            //if fast falls off of the tree then this value does not exist
            //at that point we want slow to point to the parent of the new node
            while(fast != NULL){
                if(branch -> value > fast -> value){
                    slow = fast;
                    fast = fast -> right;
                }
                else{
                    slow = fast;
                    fast = fast -> left;
                }
            }
            //at this point fast should have fallen off of the tree
            //slow happens to be at the parent node

            //same thing as the add function, greater -> right  less -> left
            if(branch -> value > slow -> value){
                slow -> right = branch;
            }
            else{
                slow -> left = branch;
            }
        }

    }
    //Code will print the following: 10 13 12 17 23 18 15
    // 3. Delete values from the tree
    void deleteNodeBST(int key, TreeNode* start) {
        //if empty
        if(root == NULL){
            cout<<"empty tree"<<endl;
            return;
        }
            //everything else
        else{
            TreeNode* marked;
            TreeNode* grabL;
            TreeNode* grabR;
            TreeNode* helper;

            //make a helper pointer that starts at the beginning
            helper = start;

            //grab the address of the node you want to delete, the search function was mdoified to return an address
            marked = searchBST(key, root);

            //if you are looking for something that does not exist the break out
            if (marked == NULL){
                cout<<"value does not exist in the tree"<<endl;
                return;
            }

            //if what you're looking for exists then grab the addresses of its children so you don't demolish the whole structure
            grabL = marked -> left;
            grabR = marked -> right;

            //if root is marked make the node to the right of it root (my convention) and then place the left side where it should be
            //the delete the marked node
            if(marked == root){
                root = root -> right;
                placeBranch(grabL);
                delete marked;
                size -= 1;
                return;
            }

            //if your children aren't marked for death then traverse down the structure with tree until you get to the parent of a marked node
            while(helper -> left != marked && helper -> right != marked){
                if(key > helper -> value){
                    helper = helper -> right;
                }
                else if(key < helper -> value){
                    helper = helper -> left;
                }
                    //shouldnt get here. This means that helper didn't find the value or helper ended up on the marked node, or the other NULL failsafes didn't work
                else{
                    cout<<"houston we have a probelm"<<endl;
                }
            }

            //if your child is marked then null the connection, delete the marked node, and then place its children where they should be
            //Left then Right, I just did it in that order as a convention
            if(helper -> left == marked){
                helper -> left = NULL;
                delete marked;
                size -= 1;
                placeBranch(grabL);
                placeBranch(grabR);
            }
            else if(helper -> right == marked){
                helper -> right = NULL;
                delete marked;
                size -= 1;
                placeBranch(grabL);
                placeBranch(grabR);
            }
        }
    }


    //Stuff for the Exam 2:
    //---------------------------------------------------------
    //Question 8
    void deleteTree(TreeNode *node) {
        if (node == NULL)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        cout << " Deleting node: " << endl << node->value;
        deleteNodeBST(node-> value, root);
        size =0;
        cout << endl;
    }

    //Question 9
    bool isBalanced(TreeNode* start){
        if(start == NULL){
            cout<<"The tree is empty at start"<<endl;
            return true;
        }
        else{            //height in general is root to leaf node
            int lHeight = 0;
            int rHeight = 0;
            TreeNode* hL = start;
            TreeNode* hR = start;

            while(hL != NULL){
                hL = hL -> left;
                lHeight++;
            }
            while(hR != NULL){
                hR = hR -> right;
                rHeight++;
            }

            if((lHeight == rHeight) || (lHeight == rHeight+1) || (lHeight+1 == rHeight)){
                return true;
            }
            else{
                return false;
            }
        }
    }

    //Question 10:
    int findNodeFound(TreeNode* root, int val) // Searching whether the given value is found in the BST
    {
        if(root == NULL)
            return 0;
        else if(root->value == val)
            return 1;

        else if(root->value > val)
            return findNodeFound(root->left,val);
        else
            return findNodeFound(root->right,val);
    }

    int firstCommonParent(TreeNode* root, int value1, int value2) // Finding FirstCommonParent of given values
    {
        int flag1 = 0, flag2 = 0;
        flag1 = findNodeFound(root,value1);
        flag2 = findNodeFound(root,value2);
        if(flag1==1 && flag2==1)
        {
            while(1)
            {
                if(root==NULL)
                    return 0;
                else if((root->value > value1) && (root->value > value2))
                    root = root->left;
                else if((root->value < value1) && (root->value < value2))
                    root = root->right;
                else
                    break;
            }
            return root->value;
        }
        else
        {
            cout << " Values are not found in BST" << endl;
            return 0;
        }
    }
};
//If they give you values like 1,2,3,4,5,6,7,8,9
//Use self balancing trees:
//AVL and Red Black Trees
//They use rotation to fix this problem
int main() {
    BST myTree;
    int choice, value;
    while (1) {
        cout << "Press 1 to add BST" << endl;
        cout << "Press 2 to search BST" << endl;
        cout << "Press 3 to delete" << endl;
        cout << "Press 4 to infix" << endl;
        cout << "Press 5 for prefix" << endl;
        cout << "Press 6 to postfix" << endl;
        cout << "Press 7 to delete the tree" << endl;
        cout << "Press 8 to check if its balanced" << endl;
        cout << "Press 9 to Common Parent of Two Nodes" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Add what? " << endl;
                cin >> value;
                myTree.addNodeBST(value);
                break;
            case 2:
                cout << "What are you searching for " << endl;
                cin >> value;
                myTree.searchBST(value, myTree.root);
                break;
            case 3:
                int value;
                cout << "What value would you like to delete " << endl;
                cin >> value;
                myTree.deleteNodeBST(value, myTree.root);
                break;
            case 4:
                myTree.inorder(myTree.root);
                break;
            case 5:
                myTree.preorder(myTree.root);
                break;
            case 6:
                myTree.postorder(myTree.root);
                break;
            case 7:
                myTree.deleteTree(myTree.root);
                break;
            case 8:
                if(myTree.isBalanced(myTree.root) == 1){
                    cout << "Tree is Balance " << endl;
                }
                else{
                    cout << "Tree is not Balanced" << endl;
                }
                break;
            case 9:
                int value1 = 0;
                int value2 = 0;
                cout << "Insert two numbers that have the same parent "<< endl;
                cin >> value1;
                cin >> value2;
                int flag = myTree.firstCommonParent(myTree.root,value1,value2);
                if(flag !=0){
                    cout << "The First Common Parent is " << flag << endl;
                }
                else{
                    cout << "No Common Parent found " << endl;
                }
                break;
        }
    }
}