/*
ID: jinyu121
PROG:
LANG: C++
EDIT: 1.0
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

#define Status      int
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1

using namespace std;

struct BinaryTreeNode {
	char data;
	BinaryTreeNode *leftChild, *rightChild;
};

struct Tree {
	BinaryTreeNode* root;
};

struct HuffmanTreeNode {
	char data ;
	int value;
	HuffmanTreeNode* leftChild, *rightChild;
};

struct HuffmanTree {
	int totalChar;
	HuffmanTreeNode* root;
	map<char, string> codeMap;
};

struct HuffmanTreeStructCompare {
	bool operator() ( const HuffmanTreeNode *a , const HuffmanTreeNode *b ) const {
		return a->value > b->value ;
	}
};

/* Make a empty tree */
Status BinaryTreeInit ( Tree &BT ) {
	BT.root = NULL;
	return OK;
}

/* Destroy a tree (delete all the items while deleting the tree) */
Status BinaryTreeDestroy ( Tree &BT ) {
	queue<BinaryTreeNode*> tQueue;
	tQueue.push ( BT.root );

	while ( !tQueue.empty() ) {
		BinaryTreeNode* temp;
		temp = tQueue.front();
		tQueue.pop();

		if ( temp->leftChild != NULL ) {
			tQueue.push ( temp->leftChild );
		}

		if ( temp->rightChild != NULL ) {
			tQueue.push ( temp->rightChild );
		}

		delete temp;
	}

	BinaryTreeInit ( BT );
	return OK;
}

/* A sub-function to create the tree
    (I have tried a night,  but i can not write a solution to
    create a tree by provideing a string) */
void __makeTree ( BinaryTreeNode* &root ) {
	char data;
	scanf ( "%c", &data );

	if ( data == ' ' ) {
		root = NULL;
		return;
	}

	root->data = data;
	root->leftChild = new BinaryTreeNode;
	root->rightChild = new BinaryTreeNode;
	__makeTree ( root->leftChild );
	__makeTree ( root->rightChild );
}

/*Create a binary tree using "first order trading result" */
Status BinaryTreeCreate ( Tree &BT ) {
	/* Open file */
	freopen ( "BinaryTree.in", "r", stdin );
	BT.root = new BinaryTreeNode;
	__makeTree ( BT.root );
	/* Close file */
	fclose ( stdin );
	return OK;
}

/* see if the tree is an empty tree (So simple ~~~ I like..)*/
bool BinaryTreeEmpty ( Tree &BT ) {
	return BT.root == NULL;
}

/* The depth of the tree */
int BinaryTreeDepth ( Tree &BT ) {
	queue< pair<int, BinaryTreeNode*> > tQueue;
	pair<int, BinaryTreeNode*> queueTemp;
	int depth = 1;
	queueTemp.first = 1;
	queueTemp.second = BT.root;
	tQueue.push ( queueTemp );

	while ( !tQueue.empty() ) {
		depth = max ( depth, tQueue.front().first );
		queueTemp.first = tQueue.front().first + 1;
		queueTemp.second = tQueue.front().second->leftChild;

		if ( queueTemp.second != NULL ) {
			tQueue.push ( queueTemp );
		}

		queueTemp.second = tQueue.front().second->rightChild;

		if ( queueTemp.second != NULL ) {
			tQueue.push ( queueTemp );
		}

		tQueue.pop();
	}

	return depth;
}

int __countLeaf ( BinaryTreeNode* root ) {
	if ( root == NULL ) {
		return 0;
	}

	if ( root->leftChild == NULL && root->rightChild == NULL ) {
		return 1;
	}

	return __countLeaf ( root->leftChild ) + __countLeaf ( root->rightChild );
}

int BinaryTreeCountLeaf ( Tree &BT ) {
	return __countLeaf ( BT.root );
}

void BinaryTreePreOrderTraverse ( BinaryTreeNode* root ) {
	cout << root->data << " ";

	if ( root->leftChild ) {
		BinaryTreePreOrderTraverse ( root->leftChild );
	}

	if ( root->rightChild ) {
		BinaryTreePreOrderTraverse ( root->rightChild );
	}
}

void BinaryTreeInOrderTraverse ( BinaryTreeNode* root ) {
	if ( root->leftChild ) {
		BinaryTreeInOrderTraverse ( root->leftChild );
	}

	cout << root->data << " ";

	if ( root->rightChild ) {
		BinaryTreeInOrderTraverse ( root->rightChild );
	}
}

void BinaryTreePostOrderTraverse ( BinaryTreeNode* root ) {
	if ( root->leftChild ) {
		BinaryTreePostOrderTraverse ( root->leftChild );
	}

	if ( root->rightChild ) {
		BinaryTreePostOrderTraverse ( root->rightChild );
	}

	cout << root->data << " ";
}

void BinaryTreeLevelOrderTraverse ( BinaryTreeNode* root ) {
	queue<BinaryTreeNode*> tQueue;
	tQueue.push ( root );

	while ( !tQueue.empty() ) {
		if ( tQueue.front()->leftChild != NULL ) {
			tQueue.push ( tQueue.front()->leftChild );
		}

		if ( tQueue.front()->rightChild != NULL ) {
			tQueue.push ( tQueue.front()->rightChild );
		}

		cout << tQueue.front()->data << " ";
		tQueue.pop();
	}
}


void BinaryTreeFirstOrderTraverseNoRecursion ( BinaryTreeNode* root ) {
	stack<BinaryTreeNode*> tStack;
	BinaryTreeNode* tTop;
	tStack.push ( root );

	while ( !tStack.empty() ) {
		for ( tTop = tStack.top(); tTop; tTop = tStack.top() ) {
			cout << tTop->data << " ";
			tStack.push ( tTop->leftChild );
		}

		tStack.pop();

		/* OK... if there is empty, it means that the tree has been fully traversed  */
		if ( tStack.empty() ) {
			return;
		}

		tTop = tStack.top();
		tStack.pop();
		tStack.push ( tTop->rightChild );
	}
}

void BinaryTreeInOrderTraverseNoRecursion ( BinaryTreeNode* root ) {
	stack<BinaryTreeNode*> tStack;
	BinaryTreeNode* tTop;
	tStack.push ( root );

	while ( !tStack.empty() ) {
		for ( tTop = tStack.top(); tTop; tTop = tStack.top() ) {
			tStack.push ( tTop->leftChild );
		}

		tStack.pop();

		/* OK... if there is empty, it means that the tree has been fully traversed  */
		if ( tStack.empty() ) {
			return;
		}

		tTop = tStack.top();
		cout << tTop->data << " ";
		tStack.pop();
		tStack.push ( tTop->rightChild );
	}
}

void BinaryTreePostOrderTraverseNoRecursion ( BinaryTreeNode* root ) {
	stack<BinaryTreeNode*> tStack;
	stack<int> rem;
	BinaryTreeNode* tTop;
	tStack.push ( root );
	rem.push ( 2 );

	while ( !tStack.empty() ) {
		tTop = tStack.top();

		switch ( rem.top() ) {
			case 2: {
					rem.top()--;

					if ( tTop->leftChild ) {
						rem.push ( 2 );
						tStack.push ( tTop->leftChild );
					}
				};

				break;
			case 1: {
					rem.top()--;

					if ( tTop->rightChild ) {
						rem.push ( 2 );
						tStack.push ( tTop->rightChild );
					}
				}
				break;

			default: {
					while ( !tStack.empty() ) {
						if ( rem.top() != 0 ) {
							break;
						}

						cout << tStack.top()->data << " ";
						tStack.pop();
						rem.pop();
					}
				}
		}
	}
}

void __huffmanTreeTraverse ( HuffmanTreeNode* root, string code, map<char, string>&codeMap ) {
	/* a node having value must be a leaf node */
	if ( root->data ) {
		codeMap.insert ( pair<char, string> ( root->data , code ) );
		return;
	}

	if ( root->leftChild ) {
		__huffmanTreeTraverse ( root->leftChild, code + "0", codeMap );
	}

	if ( root->rightChild ) {
		__huffmanTreeTraverse ( root->rightChild, code + "1", codeMap );
	}
};

void HuffmanTreeMake ( HuffmanTree &hurffmanTree ) {
	/* OpenFile */
	freopen ( "HuffmanDictionary.in", "r", stdin );
	/* Ok... a user-defined compare function is used in this priority queue  */
	priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, HuffmanTreeStructCompare> iQueue;
	int n;
	HuffmanTreeNode *oneNode, *x, *y;
	/* read data from file */
	scanf ( "%d", &n );
	cin.get();
	cin.get();

	for ( int i = 0; i < n; i++ ) {
		oneNode = new HuffmanTreeNode();
		scanf ( "%c %d\n", &oneNode->data, &oneNode->value );
		iQueue.push ( oneNode );
	}

	/* make the tree */
	for ( int i = 1; i < n ; i++ ) {
		oneNode = new HuffmanTreeNode();
		x = iQueue.top();
		iQueue.pop();
		y = iQueue.top();
		iQueue.pop();

		if ( x->value <= y->value ) {
			oneNode->leftChild = x;
			oneNode->rightChild = y;
		} else {
			oneNode->leftChild = y;
			oneNode->rightChild = x;
		}

		oneNode->value = x->value + y->value;
		iQueue.push ( oneNode );
	}

	/* get some data from the tree */
	hurffmanTree.totalChar = n;
	hurffmanTree.root = iQueue.top();
	__huffmanTreeTraverse ( hurffmanTree.root, "", hurffmanTree.codeMap );
	/* Close file */
	fclose ( stdin );
}

void HuffmanTreeEncode ( HuffmanTree huffmanTree ) {
	/* OpenFile */
	freopen ( "HuffmanOriginal.in", "r", stdin );
	char ch;
	map<char , string> iMap = huffmanTree.codeMap;
	map<char , string >::iterator it;

	while ( scanf ( "%c", &ch ) != EOF ) {
		it = iMap.find ( ch );

		if ( it == iMap.end() ) {
			cout << "Encoding Error: The char '" << ch << "' is not in the encoding map!" << endl;
			fclose ( stdin );
			return;
		} else {
			cout << it->second;
		}
	}

	/* Close file */
	fclose ( stdin );
}

char __huffmanTreeDecode ( char ch, HuffmanTreeNode *root ) {
	HuffmanTreeNode *nextRoot;
	nextRoot = ( ch == '0' ) ?  root->leftChild : root->rightChild;

	if ( !nextRoot ) {
		return '\0';
	}

	if ( nextRoot->data ) {
		return nextRoot->data;
	}

	cin >> ch;
	return __huffmanTreeDecode ( ch, nextRoot );
}

void HuffmanTreeDecode ( HuffmanTree huffmanTree ) {
	/* OpenFile */
	freopen ( "HuffmanEncoded.in", "r", stdin );
	char t;

	while ( cin >> t ) {
		cout << __huffmanTreeDecode ( t, huffmanTree.root );
	}

	/* Close file */
	fclose ( stdin );
}

void HuffmanTreeShow ( HuffmanTree huffmanTree ) {
	cout << endl;
	cout << "Huffman Encoding" << endl;
	cout << "Total chars: " << huffmanTree.totalChar << endl;
	cout << "Code map:" << endl;

	for ( map<char, string>::iterator it = huffmanTree.codeMap.begin(); it != huffmanTree.codeMap.end() ; it++ ) {
		cout << "'" << it->first << "'" << " => " << it->second << endl;
	}
}

int main() {
	//freopen (".out", "w", stdout);
	Tree iTree;
	BinaryTreeInit ( iTree );
	/* Create the tree */
	BinaryTreeCreate ( iTree );
	/* Depth of the tree */
	cout << "Depth: \t" ;
	cout << BinaryTreeDepth ( iTree ) << endl;
	cout << "Leafs: \t" ;
	cout << BinaryTreeCountLeaf ( iTree ) << endl;
	/* Traverse */
	/* ======== */
	cout << endl << "Recursion:" << endl;
	cout << "Pre order: \t";
	BinaryTreePreOrderTraverse ( iTree.root );
	cout << endl;
	cout << "In order: \t" ;
	BinaryTreeInOrderTraverse ( iTree.root );
	cout << endl;
	cout << "Post order: \t";
	BinaryTreePostOrderTraverse ( iTree.root );
	cout << endl;
	cout << "Level order: \t";
	BinaryTreeLevelOrderTraverse ( iTree.root );
	cout << endl;
	/* ======== */
	cout << endl << "NoRecursion:" << endl;
	cout << "Pre order: \t";
	BinaryTreeFirstOrderTraverseNoRecursion ( iTree.root );
	cout << endl;
	cout << "In order: \t" ;
	BinaryTreeInOrderTraverseNoRecursion ( iTree.root );
	cout << endl;
	cout << "Post order: \t";
	BinaryTreePostOrderTraverseNoRecursion ( iTree.root );
	cout << endl;
	/* Huffman Encoding */
	HuffmanTree huffmanTree;
	HuffmanTreeMake ( huffmanTree );
	HuffmanTreeShow ( huffmanTree );
	cout << endl;
	HuffmanTreeEncode ( huffmanTree );
	cout << endl;
	HuffmanTreeDecode ( huffmanTree );
	//fclose(stdout);
	return 0;
}
