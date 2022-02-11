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



Node *kd_tree( Node* root, std::vector<std::vector<int>> vect, bool myaxis){
	
	if (vect.size()==1){
		cout<< " last node " << endl;
		//int point[][NDIM] = {vect[0][0],vect[0][1]};
		//return root=newNode(point[0]);
		root-> point[0] = vect[0][0];
		root->point[1] =vect[0][1];
		root->right = root->left=NULL;
		return root;
	}
	else{

		struct Node *leftNode = new Node;
		struct Node *rightNode = new Node; 

			// let's find the median,
		int m=vect.size(); //number of row 
		int l= m/2;

		//1. sort vect according to axis  myaxis 
		
		if(myaxis==true){ // we sort according to y axis
			cout<< " y sort" <<endl; 
			// 1. Let's swap the vector 
				for(int i=0; i<m; i++)
					swap(vect[i][0],vect[i][1]);
			// 2. sort the swap vector 

			sort(vect.begin(),vect.end());
			// 3. swap again the vector 
				for(int i=0; i<m; i++)
					swap(vect[i][0],vect[i][1]);
		}
		else{ // we sort according to x axis
			
			sort(vect.begin(),vect.end());
			cout<< " x sort " <<endl;
			}

		root->point[0]=vect[l][0];
		root->point[1] = vect[l][1];

		vector<vector<int>> left;
		vector<vector<int>> right; 


		for (int  i=0; i<l; i++)
			left.push_back(vect[i]);
		for(int i=l+1; i<m;i++)
			right.push_back(vect[i]);

		root->left = kd_tree(leftNode,left,!myaxis);

		if(right.size()>0) // this condition is use to avoid dumped core because, for 2 data, right=empty
			root->right= kd_tree(rightNode,right,!myaxis);
		
		return root;
		
	}

}


int main(){

	struct Node* root= new Node;

	vector<vector<int>> vect{{3,6},{17,15},{13,15},{6,12},	
				{9,1},{2,7},{10,19},{45,34},{34,4},{23,45}};

	bool myaxis=false;

	root = kd_tree(root,vect,myaxis);
	
	return 0;
	}
