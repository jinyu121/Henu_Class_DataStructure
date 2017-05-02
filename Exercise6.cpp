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
#include <ctime>

#define TOTAL 5

using namespace std;

int comp_time = 0;
int move_time = 0;

int a[TOTAL];
struct TreeNode {
	int data;
	TreeNode* leftChild;
	TreeNode* rightChild;
};
struct Tree {
	TreeNode* root;
};
void ShowData ( const int a[], int n ) {
	cout << "===== ===== DATA BEGIN ===== =====" << endl;

	for ( int i = 0; i < n ; i++ ) {
		cout << a[i] << " ";
	}

	cout << endl;
	cout << "===== ===== DATA  END  ===== =====" << endl;
}
void ShowResult ( const int a[], int n ) {
	ShowData ( a, n );
	cout << "Compare:" << comp_time << endl;
	cout << "Move:\t" << move_time << endl;
}
void MemaryCopy ( int dist[], const int source[], int n ) {
	for ( int i = 0; i < n ; i++ ) {
		dist[i] = source[i];
	}
}
/* Fill something */
void FillAscInt ( int a[], int n , bool show ) {
	for ( int i = 0; i < n ; i++ ) {
		a[i] = i;
	}

	if ( show ) {
		ShowData ( a, n );
	}
}
void FillDescInt ( int a[], int n , bool show ) {
	for ( int i = 0; i < n ; i++ ) {
		a[i] = n - i + 1;
	}

	if ( show ) {
		ShowData ( a, n );
	}
}
void FillRandomInt ( int a[], int n , bool show ) {
	for ( int i = 0; i < n ; i++ ) {
		a[i] = rand() % n;
	}

	if ( show ) {
		ShowData ( a, n );
	}
}
bool __binarySearchTreeOperate ( TreeNode* root , int aim, bool autoInsert = false ) {
	comp_time++;

	if ( aim == root->data ) {
		return true;
	}

	bool ok = true;

	if ( aim < root->data ) {
		if ( !root->leftChild ) {
			ok = false;

			if ( autoInsert ) {
				root->leftChild = new TreeNode();
				root->leftChild->data = aim;
				root->leftChild->leftChild = NULL;
				root->leftChild->rightChild = NULL;
			}
		} else {
			ok = __binarySearchTreeOperate ( root->leftChild, aim, autoInsert );
		}
	}

	if ( aim > root->data ) {
		if ( !root->rightChild ) {
			ok = false;

			if ( autoInsert ) {
				root->rightChild = new TreeNode();
				root->rightChild->data = aim;
				root->rightChild->leftChild = NULL;
				root->rightChild->rightChild = NULL;
			}
		} else {
			ok = __binarySearchTreeOperate ( root->rightChild, aim, autoInsert );
		}
	}

	return ok;
}
bool BinarySearchTreeFind ( Tree &tree, int aim , bool autoInsert = false ) {
	return __binarySearchTreeOperate ( tree.root, aim , autoInsert );
}
void BinarySearchTreeMake ( int a[] , int n, Tree &tree ) {
	tree.root = new TreeNode();
	tree.root->data = 2147483647;
	tree.root->leftChild = NULL;
	tree.root->rightChild = NULL;

	for ( int i = 0; i < n ; i++ ) {
		BinarySearchTreeFind ( tree,  a[i], true );
	}
}

bool BinarySearch ( int a[], int len, int aim ) {
	bool OK = false;

	for ( int mid = ( 0 + len ) / 2 , low = 0, high = len; low <= high ; mid = ( low + high ) / 2 ) {
		comp_time++;

		if ( a[mid] == aim ) {
			OK = true;
			break;
		}

		if ( aim < a[mid] ) {
			high = mid - 1;
			continue;
		}

		if ( aim > a[mid] ) {
			low = mid + 1;
			continue;
		}
	}

	return OK;
}

/* Bubble Sort  */
void Sort_Bubble ( const int original[], int n ) {
	comp_time = 0;
	move_time = 0;
	int a[n];
	MemaryCopy ( a, original, n );
	bool ok = true;

	for ( int i = 0; ( ( i < n ) && ok ) ; i++ ) {
		ok = false;

		for ( int j = 0; j < n - i - 1 ; j++ ) {
			comp_time++;

			if ( a[j] > a[j + 1] ) {
				move_time++;
				swap ( a[j], a[j + 1] );
				ok = true;
			}
		}
	}

	ShowResult ( a, n );
}
/* Select Sort */
void Sort_Select ( const int original[], int n ) {
	comp_time = 0;
	move_time = 0;
	int a[n];
	MemaryCopy ( a, original, n );
	int posi, aim;

	for ( int i = 0; i < n ; i++ ) {
		posi = i;
		aim = a[i];

		for ( int j = i + 1; j < n ; j++ ) {
			comp_time++;

			if ( a[j] < aim ) {
				aim = a[j];
				posi = j;
			}
		}

		if ( posi != i ) {
			move_time++;
			swap ( a[i], a[posi] );
		}
	}

	ShowResult ( a, n );
}
/* Insert Sort */
void Sort_Insert ( const int original[], int n ) {
	comp_time = 0;
	move_time = 0;
	int a[n];
	MemaryCopy ( a, original, n );

	for ( int i = 1; i < n ; i++ ) {
		int t = a[i];
		int posi = 0;

		for ( int j = i - 1; j >= 0 ; j-- ) {
			comp_time++;

			if ( t < a[j] ) {
				move_time++;
				a[j + 1] = a[j];
			} else {
				posi = j + 1;
				break;
			}
		}

		move_time++;
		a[posi] = t;
	}

	ShowResult ( a, n );
}
/* Quick Sort */
void __quickSort ( int a[], int l, int r ) {
	int i = l, j = r;
	int m = a[ ( r + l ) / 2];
	//int m = a[l];

	for ( ; i <= j ; ) {
		while ( a[i] < m ) {
			comp_time++;
			i++;
		}

		while ( a[j] > m ) {
			comp_time++;
			j--;
		}

		if ( i <= j ) {
			move_time++;
			swap ( a[i], a[j] );
			i++;
			j--;
		}
	}

	if ( l < j ) {
		__quickSort ( a, l, j );
	}

	if ( r > i ) {
		__quickSort ( a, i, r );
	}
}
/* Heap sort */
void __heapAdjust ( int a[], int root, int n ) {
	for ( int newRoot = root * 2; newRoot <= n ; newRoot = root * 2 ) {
		comp_time++;

		if ( ( newRoot + 1 <= n ) && ( a[newRoot + 1] > a[newRoot] ) ) {
			newRoot++;
		}

		comp_time++;

		if ( a[root] < a[newRoot] ) {
			move_time++;
			swap ( a[root ], a[newRoot] );
		} else {
			break;
		}

		root = newRoot;
	}
}
void Sort_Heap ( const int original[], int n ) {
	comp_time = 0;
	move_time = 0;
	int a[n];
	MemaryCopy ( a, original, n );

	for ( int i = n / 2; i >= 0 ; i-- ) {
		__heapAdjust ( a, i, n - 1 );
	}

	for ( int i = n - 1; i > 0 ; i-- ) {
		swap ( a[0], a[i] );
		__heapAdjust ( a, 0, i - 1 );
	}

	ShowResult ( a, n );
}
void Sort_Quick ( const int original[], int n ) {
	comp_time = 0;
	move_time = 0;
	int a[n];
	MemaryCopy ( a, original, n );
	__quickSort ( a, 0, n - 1 );
	ShowResult ( a, n );
}
int main() {
	srand ( time ( NULL ) );
	//freopen (".in", "r", stdin);
	//freopen (".out", "w", stdout);
	/*Test find a number in a random array*/
	FillRandomInt ( a, TOTAL , true );
	int aim = TOTAL * 2 / 3;
	/* Search */
	/* Dynamic search */
	Tree tree;
	BinarySearchTreeMake ( a, TOTAL, tree );
	comp_time = 0;
	cout << "Binary tree search result: " << aim << ( BinarySearchTreeFind ( tree, aim ) ? "" : " can't be" ) << " found!" << endl ;
	cout << "     [with comparing " << comp_time << " times]" << endl;
	/* Static search */
	sort ( a, a + TOTAL );
	comp_time = 0;
	cout << "Binary search result: " << aim << ( BinarySearch ( a, TOTAL, aim ) ? "" : " can't be" ) << " found!" << endl ;
	cout << "     [with comparing " << comp_time << " times]" << endl;
	/* Sort */
	// Prepare...
	FillRandomInt ( a, TOTAL , true );
	/* Bubble Sort */
	Sort_Bubble ( a, TOTAL );
	/* Select Sort */
	Sort_Select ( a, TOTAL );
	/* Insert Sort */
	Sort_Insert ( a, TOTAL );
	/* Quick Sort */
	Sort_Quick ( a, TOTAL );
	/* Heap Sort */
	Sort_Heap ( a, TOTAL );
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
