#include<iostream>
#include<algorithm> // for sort
#include<vector> 
#include<bits/stdc++.h> // for 2D vector and sort function 

using namespace std; 

const int NDIM= 2;

// a structure to represent node ok kd tree 

struct Node
{

	int point[NDIM]; // to store the dimensional point

	Node *left,*right; 
};


// A method to creat a node of Kd-tree

struct Node* newNode(int arr[])
{
	struct Node* temp = new Node;

	for (int i=0; i<NDIM; i++){
	temp->point[i] = arr[i];
	}

	temp->left = temp->right =NULL;
	return temp; 
};


// the following code will be used to sort the second column 

bool sortcol(const vector<int>& v1, const vector<int>& v2){
	return v1[1] <v2[1];
	}


Node *kd_tree( Node* root, vector<vector<int>> vect, int myaxis){
	
	if (vect.size()==1){
		root->point[0]=vect[0][0];
		root->point[1]=vect[0][0];

		//int point[][NDIM] = {vect[0][0],vect[0][1]};
		//return root=newNode(point[0]);	
		return root;
	}
	else{

		struct Node *leftNode = NULL;
		struct Node *rightNode = NULL; 

		//1. sort vect according to axis  myaxis 
		myaxis =(myaxis +1)/NDIM;
		
		if(myaxis==1){ // we sort according to y axis
	
			sort(vect[1].begin(),vect[1].end());
		}
		else{ // we sort according to x axis
			
			sort(vect.begin(),vect.end());
			}

		// let's find the median,
		int m=vect.size(); //number of row 
		int l= m/2;

		//int point[][NDIM] = {vector[l][0],vect[l][1]} // median value
		root->point[0]=vect[l][0];
		root->point[1] = vect[l][1];

		vector<vector<int>> left;
		vector<vector<int>> right; 


		for (int  i=0; i<=l; i++)
			left.push_back(vect[i]);
		for(int i=l+1; i<=m;i++)
			right.push_back(vect[i]);

		root->left = kd_tree(leftNode,left,myaxis);
		root->right= kd_tree(rightNode,left,myaxis);
		
	}

	return root;
}


int main(){

	struct Node* root= NULL;

	vector<vector<int>> vect{{3,6},{17,15},{13,15},{6,12},	
				{9,1},{2,7},{10,19}};

	int myaxis=-1;

	root = kd_tree(root,vect,myaxis);
	
	return 0;
	}
