#include<iostream>
#include<algorithm> // for sort
#include<vector> 
#include<bits/stdc++.h> // for 2D vector and sort function 
#include<random>

using namespace std; 

const int NDIM= 2;

// a structure to represent node ok kd tree 

struct Node
{

	int point[NDIM]; // to store the dimensional point

	Node *left,*right; 
};


Node *kd_tree( std::vector<std::vector<double>> vect, bool myaxis, int* compt){
	
	
		struct Node *newnode = new Node;
	if (vect.size()==1){

		newnode-> point[0] = vect[0][0];
		newnode->point[1] =vect[0][1];
		newnode->right = newnode->left=NULL;
		*compt = *compt+1;
		return newnode;
	}
	else{ 
 

			// let's find the median,
		int m=vect.size(); //number of row 
		int l= m/2;

		//1. sort vect according to axis  myaxis 
		
		if(myaxis==true){ // we sort according to y axis
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
			}

		newnode->point[0]=vect[l][0];
		newnode->point[1] = vect[l][1];

		vector<vector<double>> left;
		vector<vector<double>> right; 


		for (int  i=0; i<l; i++)
			left.push_back(vect[i]);
		for(int i=l+1; i<m;i++)
			right.push_back(vect[i]);

		newnode->left = kd_tree(left,!myaxis, compt);

		if(right.size()>0) // this condition is use to avoid dumped core because, for 2 data, right=empty
			newnode->right= kd_tree(right,!myaxis, compt);
		
		return newnode;
		
	}

}


int main(){

	struct Node* root= new Node;
 
	vector<vector<double>> vect{};
	int m;
	int compt{0};

	cin>> m;
	int n= pow(10,m);

	for(int i=0; i<n; i++){	
		srand(i);
		double a = double( rand())/double(RAND_MAX);
		srand(i+10);
		double b = double( rand())/double(RAND_MAX);
	 	vect.push_back({a,b});
	}
	cout<< " vect size " <<vect.size()<<endl;

	bool myaxis=false;

	root = kd_tree(vect,myaxis, &compt);
	cout<< " Number of leaves  " << compt<<endl;
	cout<< " Done .."<<endl;	
	return 0;
	}
