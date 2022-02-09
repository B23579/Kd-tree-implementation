

/// KD-tree programming example 

#include<bits/stdc++.h>
#include<algorithm> // for sort()
#include<vector>

using namespace std;

const int NDIM = 2;

// A structure to represent node of kd tree
struct Node
{
	int point[NDIM]; // To store k dimensional point
	Node *left, *right;
};

// A method to create a node of K D tree
struct Node* newNode(int arr[])
{
	struct Node* temp = new Node;

	for (int i=0; i<NDIM; i++)
	temp->point[i] = arr[i];

	temp->left = temp->right = NULL;
	return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, int point[], unsigned axis)
{
	// Tree is empty?
	if (root == NULL)
	return newNode(point);

	// Calculate current dimension (cd) of comparison
	unsigned myaxis = (axis+1) % NDIM;

	// Compare the new point with root on current dimension 'cd'
	// and decide the left or right subtree
	if (point[myaxis] < (root->point[myaxis]))
		root->left = insertRec(root->left, point, myaxis);
	else
		root->right = insertRec(root->right, point, myaxis);

	return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node *root, int point[])
{
	return insertRec(root, point, 0);
}




Node *kd_tree(Node *root, std::vector<std::vector<int>> vect, int myaxis){
	
	if (vect.size()==1){
		int point[][NDIM] = {vect[0][0],vect[0][1]};
		root = insert(root,point[0]);
	}
	else{

		std::sort(vect.begin(),vect.end());

		int m=vect.size(); // number of row 

		// Let's find the median 

		 int l= m/2;  

		 myaxis= (myaxis +1)/NDIM;

		int point[][NDIM] = {vect[l][0],vect[l][1]};

		root = insert(root,point[0]);

		std::vector<std::vector<int>> left;
		std::vector<std::vector<int>> right;

		for(int i=0; i<=l; i++)
			left.push_back(vect[i]);
		for(int i=l+1;i<=m;i++)
			right.push_back(vect[i]);	
		
		kd_tree(root,left, myaxis);
		kd_tree(root,right,myaxis);
	}

	return root;
}	



int main()
{
	struct Node *root = NULL;

	vector<vector<int>> vect{{3,6},{17,15},{13,15},{6,12},
				{9,1},{2,7},{10,19}};


	int myaxis=-1; 

	root= kd_tree(root,vect,myaxis);
	return 0;
}
