
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


Node *kd_tree( std::vector<std::vector<double>> X,std::vector<std::vector<double>> Y, bool myaxis, int* compt){
	
	
	struct Node *newnode = new Node;
	if ((X.size()==1)&& (Y.size()==1)){
		std::cout<< " stop "<<std::endl;
		newnode-> point[0] = X[0][0];
		newnode->point[1] =X[0][1];
		newnode->right = newnode->left=NULL;
		*compt = *compt+1;
		return newnode;
	}
	else{ 
 

			// let's find the median,
		int m=X.size(); //number of row 
		int l= m/2;

		vector<vector<double>> Xleft;
		vector<vector<double>> Xright; 

		vector<vector<double>> Yleft;
		vector<vector<double>> Yright; 

		if(myaxis==false){
			std::cout<<" false " << std::endl;
		newnode->point[0]=X[l][0];
		newnode->point[1] =X[l][1];

			for(int i=0; i<m; i++){
				if( Y[i][0]<X[l][0]){
					Yleft.push_back(Y[i]);}
				else{
					Yright.push_back(Y[i]);}
			}

			for(int i=0; i<l;i++){
				Xleft.push_back(X[i]);}
			
			for(int i=l+1;i<m;i++){
				Xright.push_back(X[i]);}
				
		}
		else{	
		std::cout<<" True " << std::endl;
		newnode->point[0]=Y[l][0];
		newnode->point[1] =Y[l][1];

			for( int i=0;i<m;i++){
				if(X[i][1] < Y[l][1])
					Xleft.push_back(X[i]);
				else
					Xright.push_back(X[i]);
			}
			for(int i=0; i<l;i++)
				Yleft.push_back(Y[i]);
			
			for(int i=l+1;i<m;i++)
				Yright.push_back(Y[i]);
			}

			std::cout<< " there Xleft  Yleft " <<Xleft.size() << " " << Yleft.size()<< std::endl;
		        std::cout<< " there Xright  Yright " <<Xright.size() << " " << Yright.size()<< std::endl;
		
		if((Xleft.size())>0 && (Yleft.size()>0))
			
			newnode->left = kd_tree(Xleft,Yleft,!myaxis, compt);

		if((Xright.size()>0)&&(Yright.size()>0)) // this condition is use to avoid dumped core because, for 2 data, right=empty
			newnode->right= kd_tree(Xright,Yright,!myaxis, compt);
		
		return newnode;
		
	}

}


int main(){

	struct Node* root= new Node;
	vector<vector<double>> vect{};
	vector<vector<double>> X{}; 
	vector<vector<double>> Y{};

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
	
	X= vect;
	Y=vect;
		//1. sort vect according to axis  myaxis 
		
	 // we sort according to y axis
		// 1. Let's swap the vector 
			for(int i=0; i<m; i++)
				swap(Y[i][0],Y[i][1]);
			// 2. sort the swap vector 

			sort(vect.begin(),vect.end());
			// 3. swap again the vector 
			for(int i=0; i<m; i++)
				swap(Y[i][0],Y[i][1]);
		
		// we sort according to x axis
			
		sort(X.begin(),X.end());
	

	bool myaxis=false;

	root = kd_tree(X,Y,myaxis, &compt);
	cout<< " Number of leaves  " << compt<<endl;
	cout<< " Done .."<<endl;	
	return 0;
	}
