#include<iostream>
#include<algorithm> // for sort
#include<vector> 
#include<bits/stdc++.h> // for 2D vector and sort function 
#include<random>
#include<mpi.h>

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
	//	#pragma omp parallel shared(vect,l,m)
		{
			// 1. Let's swap the vector 
	//			#pragma omp for ordered					
					for(int i=0; i<m; i++){
	//					#pragma omp odered 
						swap(vect[i][0],vect[i][1]);}				
			// 2. sort the swap vector 

			sort(vect.begin(),vect.end());
			// 3. swap again the vector
	//			#pragma omp for ordered 
				 
				for(int i=0; i<m; i++){
	//				#pragma omp ordered 
					swap(vect[i][0],vect[i][1]);}
				
		} // close pragma 
		}
		else{ // we sort according to x axis
			
			sort(vect.begin(),vect.end());
			}

		newnode->point[0]=vect[l][0];
		newnode->point[1] = vect[l][1];

		vector<vector<double>> left;
		vector<vector<double>> right; 

		//#pragma omp parellel shared (vect,l,m,left,right) 
		//{  
		
		for (int  i=0; i<l; i++)
			{
			left.push_back(vect[i]);}
		
		for(int i=l+1; i<m;i++)
			{
			right.push_back(vect[i]);}	

//		std:: cout<< " out "<< left.size()<<right.size() <<std::endl;
	//	#pragma omp parallel
		{	
	//		#pragma omp single nowait // Due to nowait claude, all the threads skip the 
			//  implied barrier at the end of single region and wait here for being assigned a task
			{
	//		#pragma  omp task
				newnode->left = kd_tree(left,!myaxis, compt);
	//	#pragma omp task
		{
		if(right.size()>0) // this condition is use to avoid dumped core because, for 2 data, right=empty
			newnode->right= kd_tree(right,!myaxis, compt);
		}
			
		}
		}
		return newnode;
		
	}

}


int main(int argc, char **argv){
	MPI_Init(&argc,&argv);
	int rank =MPI::COMM_WORLD.Get_rank();
	int nprc= MPI::COMM_WORLD.Get_size();
	MPI_Status stats[nprc];
	struct Node* root= new Node;
 
	vector<vector<double>> vect{};
	int m;
	int compt{0};
	double tab[2];
	for(int m =5 ; m<6;m++){
	int n= pow(10,m);
	
	// we want to performe  10^m iterrations 
	
//	#pragma omp parallel shared(vect,n)
//	{
//	int rank= omp_get_thread_num(); // this return the id  of the thread
//	int nthrds = omp_get_num_threads(); // return the number of thread  
	int count= n/nprc;
	int start = rank*count;
	int stop = start + count;
	
	if(rank==0){
	// Now let's perform the for loop
//			#pragma omp for  
			for(int i=0; i<n; i++){
				 	
				srand(i);
				double a = double( rand())/double(RAND_MAX);
				srand(i+10);
				double b = double( rand())/double(RAND_MAX);
//				#pragma omp critical	
//				 	{ // we used critical to allow each thread to write on the shared 
				//memory, whithout its we will ends with dump core, because all the thread
				// will try to write on the same memory at the same times. 
				// so, this imply only one thread can be at the critical region, other
				// wait their turn. 
					vect.push_back({a,b});
					}
//			}
//	}
		for(int proc=1;proc<nprc;proc++)
		{
			int start = 1*count;
			int stop = start + count;
			
			for(int i=start;i<stop;i++)
				{
			tab[0] = vect[i][0];
			tab[1] = vect[i][1];
		MPI_Send(&tab,2,MPI_DOUBLE,1,1,MPI_COMM_WORLD); // the second proc is the tag	
				}
		}
		std::vector<std::vector<double>> vet{};
		
		for(int i=0;i<count;i++)
			vet.push_back(vect[i]);
		bool myaxis=false;		
		root = kd_tree(vet,myaxis, &compt);
		cout<< " Number of leaves  " << compt<<endl;
				}

	if(rank !=0){

		for(int i= start; i<stop; i++){
			MPI_Recv(&tab,2,MPI_DOUBLE,0,rank,MPI_COMM_WORLD,&stats[rank]);
			vect.push_back({tab[0],tab[1]});
			}
		
		bool myaxis=false;
		root = kd_tree(vect,myaxis, &compt);
		std::cout<< " rank " << rank << " v size " << vect.size() << endl;
			cout<< " Number of leaves  " << compt<<endl;
		}



//	double start = omp_get_wtime(); 
//	root = kd_tree(vect,myaxis, &compt);
//	double endtime = omp_get_wtime();
}
	
	MPI::Finalize();

//	cout<< m << ";" << endtime - start<<std::endl;
	
	cout<< " Done .."<<endl;	
	return 0;
	}
