/**
* @file        UnitTest.cpp
* @author    TuanPM3
* @date        12/Nov/2018
* @brief    Binary Search Tree UnitTest
*/

//#include "stdafx.h"
#include "BST.h"
#include <iostream>
#include <assert.h> 
#include <vector>

using namespace std;

template<typename T>
bool compareVector(vector<T> v1, vector<T> v2)
{
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

/*================ UT for add() method ====================*/
void TEST1()
{
    cout << __FUNCTION__ << ": ";
    Bst<int> bt;
    bt.add(6);
    bt.add(4);
    bt.add(8);
    bt.add(2);
    bt.add(5);
    bt.add(7);
    bt.add(9);
    TreeNode<int> *root = bt.getroot();
    assert(root->key == 6);
    assert(root->left->key == 4);
    assert(root->right->key == 8);
    assert(root->left->left->key == 2);
    assert(root->left->right->key == 5);
    assert(root->right->left->key == 7);
    assert(root->right->right->key == 9);
    cout << "OK" << endl;
}

void TEST2()
{
    cout << __FUNCTION__ << ": ";
    Bst<float> bt;
    bt.add(5.0);    
    bt.add(4.0);
    bt.add(2.0);
    bt.add(6.0);
    bt.add(8.0);
    bt.add(7.0);    
    bt.add(9.0);
    TreeNode<float> *root = bt.getroot();
    assert(root->key == 5.0);
    assert(root->left->key == 4.0);
    assert(root->right->key == 6.0);
    assert(root->left->left->key == 2.0);
    assert(root->right->right->key == 8.0);
    assert(root->right->right->left->key == 7.0);
    assert(root->right->right->right->key == 9.0);
    cout << "OK" << endl;
}

void TEST3()
{
    cout << __FUNCTION__ << ": ";
    Bst<string> bt;
    bt.add("March");
    bt.add("January");
    bt.add("October");
    bt.add("August");
    bt.add("June");
    bt.add("May");
    bt.add("September");
    TreeNode<string> *root = bt.getroot();
    assert(root->key == "March");
    assert(root->left->key == "January");
    assert(root->right->key == "October");
    assert(root->left->left->key == "August");
    assert(root->left->right->key == "June");
    assert(root->right->left->key == "May");
    assert(root->right->right->key == "September");
    cout << "OK" << endl;
}

/*================ UT for search() method ====================*/
void TEST4()
{
    cout << __FUNCTION__ << ": ";
    Bst<int> bt;
    bt.add(6);
    bt.add(4);
    bt.add(8);
    bt.add(2);
    bt.add(5);
    bt.add(7);
    bt.add(9);

    int arr[] = { 2,4,5,6,7,8,9 };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        assert(bt.search(arr[i])->key == arr[i]);
    }    
    assert(bt.search(10) == NULL);
    cout << "OK" << endl;
}

void TEST5()
{
    cout << __FUNCTION__ << ": ";
    Bst<float> bt;
    bt.add(5.0);
    bt.add(4.0);
    bt.add(2.0);
    bt.add(6.0);
    bt.add(8.0);
    bt.add(7.0);
    bt.add(9.0);
    float arr[] = { 2.0,4.0,5.0,6.0,7.0,8.0,9.0 };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        assert(bt.search(arr[i])->key == arr[i]);
    }
    assert(bt.search(10.0) == NULL);
    cout << "OK" << endl;
}

void TEST6()
{
    cout << __FUNCTION__ << ": ";
    Bst<string> bt;
    bt.add("March");
    bt.add("January");
    bt.add("October");
    bt.add("August");
    bt.add("June");
    bt.add("May");
    bt.add("September");
    string arr[] = { 
        "March",
        "January",
        "October",
        "August",
        "June",
        "May",
        "September"
    };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        assert(bt.search(arr[i])->key == arr[i]);
    }
    assert(bt.search("Not Found") == NULL);
    cout << "OK" << endl;
}

/*================ UT for preorder iterator ====================*/
void TEST7()
{
    cout << __FUNCTION__ << ": ";
    Bst<int> bt;
    bt.add(6);
    bt.add(4);
    bt.add(8);
    bt.add(2);
    bt.add(5);
    bt.add(7);
    bt.add(9);
    vector<int> actual;
    auto itPre = bt.beginPreorder();
    for (; itPre != bt.endPreorder(); itPre++) {
        actual.push_back(*itPre);
    }
    vector<int> expect = { 6, 4, 2, 5, 8, 7, 9 };
    assert(compareVector(actual, expect));
    cout << "OK" << endl;
}

void TEST8()
{
    cout << __FUNCTION__ << ": ";
    Bst<int> bt;
    bt.add(6);
    bt.add(4);
    bt.add(8);
    bt.add(2);
    bt.add(5);
    bt.add(7);
    bt.add(9);
    vector<int> actual;
    auto itIn = bt.beginInorder();
    for (; itIn != bt.endInorder(); itIn++) {
        actual.push_back(*itIn);
    }
    vector<int> expect = { 2, 4, 5, 6, 7, 8, 9 };
    assert(compareVector(actual, expect));
    cout << "OK" << endl;
}

void TEST9()
{
    cout << __FUNCTION__ << ": ";
    Bst<int> bt;
    bt.add(6);
    bt.add(4);
    bt.add(8);
    bt.add(2);
    bt.add(5);
    bt.add(7);
    bt.add(9);
    vector<int> actual;
    auto itPost = bt.beginPostorder();
    for (; itPost != bt.endPostorder(); itPost++) {
        actual.push_back(*itPost);
    }
    vector<int> expect = { 2, 5, 4, 7, 9, 8, 6 };
    assert(compareVector(actual, expect));
    cout << "OK" << endl;
}

int main()
{
    /*
    * I write this UT for demo how to UT without UT Framework
    * These are not full UT testcase
    */
    cout << "================ UT for add() method ====================" << endl;
    TEST1();
    TEST2();
    TEST3();
    cout << "================ UT for search() method ====================" << endl;
    TEST4();
    TEST5();
    TEST6();
    cout << "/*================ UT for preorder iterator ====================*/" << endl;
    TEST7();
    cout << "/*================ UT for inorder iterator ====================*/" << endl;
    TEST8();
    cout << "/*================ UT for postorder iterator ====================*/" << endl;
    TEST9();
    return 0;
}

