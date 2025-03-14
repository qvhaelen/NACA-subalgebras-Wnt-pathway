//**************************************************************************************************
// déclaration des bibliothèques utilisées
/* contient les éléments cin et cout entre autre*/
#include <iostream>
/* fstream: stream  class to both read and write  from/to  files */
#include <fstream>
/* utilisation des chaines de caractères*/
#include <string>
/* utilisation des vecteurs*/
#include <vector>
/* utilisation des manipulateurs*/
#include<iomanip>
/*conversion nombre string et tring nombre (stringstream,  etc)*/
#include<sstream>
/*pour avoir les fonctions math de base: sqrt, pow(),  fabs,...*/
#include<cmath>
/* diff, et plein d'autres trucs, genre inner_product,...*/
#include<numeric>
/* ensemble d'algorithmes, STL algorithms, pour la manipulation des  STL containers*/
#include<algorithm>
#include<assert.h>
#include <string>

#include "test_algebra.h"
#include "set_up_matrix_Q.h"
#include "set_up_matrix_M.h"
using namespace std;

int main()
{
clock_t start, end=0; 
assert( (start = clock()) != -1); 
cout <<""<< endl; 
cout <<"                            ****************************************************                "<< endl;
cout <<"                            *                                                  *           "<< endl;
cout <<"                            *                  CODE SUBALGEBRAS                *        "<< endl;
cout <<"                            *                                                  *     "<< endl;
cout <<"                            ****************************************************           "<< endl;
cout <<"                  "<< endl;
cout <<"========================================================================================================================="<< endl;
cout <<"                                               SUMMARY:             "<< endl;
cout <<"========================================================================================================================="<< endl;
cout << "                   COMPUTATION OF THE SUBALGEBRAS " << endl;
cout <<"                 CASE DONE FOR THE WNT PATHWAY VERSION 3, 13 APRIL 2024             "<< endl;
cout <<"========================================================================================================================="<< endl;
cout << ""<< endl; 

int dim_mul_table = 33; 
int  dim_Q = 31; 
int  dim_M = 32;
int nsubalgebra = 6427;
bool bool_algebra = true; 		
bool bool_algebra_reduced = true;
int algebra_dimension;
int number_algebra = 0;

    int** matrix_Q=NULL;
   matrix_Q = new int*[dim_Q+1];
   for (int i=1;i<= dim_Q; ++i){matrix_Q[i] = new int[dim_mul_table+1];}
   
   for (int i=1;i<= dim_Q;++i){
    for (int j=1;j<= dim_mul_table;++j){
     matrix_Q[i][j] =0;
    }
   }

   int** matrix_M=NULL;
   matrix_M = new int*[dim_M+1];
   for (int i=1;i<= dim_M; ++i){matrix_M[i] = new int[dim_mul_table+1];}
   
   for (int i=1;i<= dim_M;++i){
    for (int j=1;j<= dim_mul_table;++j){
     matrix_M[i][j] =0;
    }
   }

   // matrix to list the set of nonzero elements  (1..33) taken in the multiplication table of each subalgebra
   int** nonzero_mtable=NULL;
   nonzero_mtable = new int*[nsubalgebra+1];
   for (int i=1;i<= nsubalgebra; ++i){nonzero_mtable[i] = new int[dim_mul_table+2];}
   
   for (int i=1;i<= nsubalgebra;++i){
    for (int j=1;j<= dim_mul_table+1;++j){
     nonzero_mtable[i][j] =0;
    }
   }    
   
   int*  permutation_added;
   permutation_added= new int[dim_M+1];
   for (int i=1; i<=dim_M;++i){permutation_added[i] = 0;}
   permutation_added[dim_M] = 1;
   
   
   int*  subalgebra_reduced;
   subalgebra_reduced= new int[nsubalgebra+1];
   for (int i=1; i<=nsubalgebra;++i){subalgebra_reduced[i] = 0;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// loading 
 set_up_matrix_M(matrix_M);
 set_up_matrix_Q(matrix_Q);
 string  filename = "RESULTS-LISTE-SUBALGEBRA-COMPLETE-17-04-2024.txt";
 string  filename2 = "RESULTS-LISTE-SUBALGEBRA-COMPLETE-MULTIPLICATION-TABLES-17-04-2024.txt";
 string  filename3 = "RESULTS-LISTE-SUBALGEBRA-COMPLETE-SUBALGEBRA-REDUCED-LIST-17-04-2024.txt";
 ofstream output_file(filename.c_str());
if (output_file.is_open()){
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 for (int ct1=1; ct1<= dim_Q; ++ct1)
 {
	algebra_dimension = ct1+1;   
     cout << "looking for subalgebra of dimension  "<< algebra_dimension << endl;
	std::string bitmask(ct1, 1); // K leading 1's
    bitmask.resize(dim_Q, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        for (int i = 0; i < dim_Q; ++i) // [0..N-1] integers
        { 
            if (bitmask[i]) {permutation_added[i+1] = 1;}
        }
	
		bool_algebra = true;
       	
		bool_algebra_reduced = true;
         if (permutation_added[11] == 1){test_algebra( number_algebra, nonzero_mtable,permutation_added,matrix_Q,matrix_M,bool_algebra,  bool_algebra_reduced,algebra_dimension,dim_mul_table, dim_Q );}
	     if (permutation_added[11] == 0){bool_algebra = false;}
		if (bool_algebra)
	    {
	    cout << "++++++++++++++++ >>>  A subalgebra of dimension "<< algebra_dimension <<" has been found;  Total number of subalgebra so  far = "<<  number_algebra << endl;
	  
	     for (int h1=1;h1<=dim_M; ++h1 )
	     {
	       if (permutation_added[h1] == 1){output_file<< 1 <<",";}
	       if (permutation_added[h1] == 0){output_file<< 0 <<",";} 
	     } 
		
	    output_file<<""<<endl;
	     if (bool_algebra_reduced) {subalgebra_reduced[number_algebra] =1;}
		 
	    }
		for (int i=1; i<=dim_Q;++i){permutation_added[i] = 0;}
		
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
	

} 
	

output_file.close();
}else{cout << "file can not be opened"  << endl;}	

//  we want to identify the subalgebra which share the same multiplication table we compare row of 'nonzero_mtable' which are the same
    int number_diff_class = 0;
	for (int ct0=1;ct0<=nsubalgebra-1; ++ct0 )
	{
	  if(nonzero_mtable[ct0][dim_mul_table+1] ==0)
      {		  
		number_diff_class++; 
		nonzero_mtable[ct0][dim_mul_table+1] = number_diff_class;
		for (int ct1=ct0+1;ct1<=nsubalgebra; ++ct1 )
		{
		 if(nonzero_mtable[ct1][dim_mul_table+1] ==0)	
		 {	
		   bool identical = true;
		   int ct2 =0;
      	   while(identical && ct2< dim_mul_table)
		   {
			  ct2++;
			  if (nonzero_mtable[ct0][ct2] != nonzero_mtable[ct1][ct2]){identical = false;}
		   }		
           if (identical){nonzero_mtable[ct1][dim_mul_table+1] = number_diff_class;}
         } //  if(nonzero_mtable[ct1][dim_mul_table+1] ==0)		  
		}
	  } //  if(nonzero_mtable[ct0][dim_mul_table+1] ==0)	
	}
    if (nonzero_mtable[nsubalgebra][dim_mul_table+1] ==0){number_diff_class++;nonzero_mtable[nsubalgebra][dim_mul_table+1] = number_diff_class;}
// we export the file with the datastructure 	'nonzero_mtable'
ofstream output_file2(filename2.c_str());
if (output_file2.is_open()){
	   for (int h1=1;h1<=nsubalgebra; ++h1 )
	   {
	     for(int h2=1;h2<=dim_mul_table+1; ++h2)  
		 {	  
	       output_file2<< nonzero_mtable[h1][h2] <<","; 
		 } 
         output_file2<<""<<endl;		 
	   } 
	output_file2.close();
}else{cout << "file can not be opened"  << endl;}

// we export the file with the datastructure 	'subalgebra_reduced' 
ofstream output_file3(filename3.c_str());
if (output_file3.is_open()){
	   for (int h1=1;h1<=nsubalgebra; ++h1 )
	   {
	       output_file3<< subalgebra_reduced[h1] << endl;		 
	   } 
	output_file3.close();
}else{cout << "file can not be opened"  << endl;}	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
end = clock(); 
double cpu_duration = (end-start)/CLOCKS_PER_SEC;
cout << ""<< endl;
cout <<"==================================================================================================================="<< endl;
cout <<" PROGRAM HAS COMPLETED THE TASK, PROGRAM IS BEING CLOSED, COMPLETE CPU TIME FOR COMPLETION IS: "<< cpu_duration<<" SECONDS"<< endl;
cout <<"==================================================================================================================="<< endl;
cout << ""<< endl;

for (int i=1;i<= dim_Q;++i){delete[] matrix_Q[i];}
delete [] matrix_Q;
for (int i=1;i<= dim_M;++i){delete[] matrix_M[i];}
delete [] matrix_M;
for (int i=1;i<= nsubalgebra;++i){delete[] nonzero_mtable[i];}
delete [] nonzero_mtable;
delete [] permutation_added;
delete [] subalgebra_reduced;
 

return 0;
} // end main function