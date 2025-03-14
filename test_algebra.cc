/* contient les éléments cin et cout entre autre*/
#include <iostream>
/* fstream: stream  class to both read and write  from/to  files */
#include <fstream>
/* utilisation des chaines de caractères*/
#include <string>
/* utilisation des manipulateurs*/
#include<iomanip>
/*conversion nombre string et tring nombre (stringstream,  etc)*/
#include<sstream>
#include"test_algebra.h"
using namespace std;
void  test_algebra(int&  number_algebra, int** nonzero_mtable, int* permutation_added, int** matrix_Q, int** matrix_M,bool& bool_algebra,bool& bool_algebra_reduced, int& algebra_dimension,int& dim_mul_table, int& dim_Q)
{
int ct0 =0; 	
int ct1 =0;	
int ct2 =0;
int ct3 =0;
int multientry =0;

   int*    vector_internal;
   vector_internal= new int[dim_mul_table+1];
   for (int i=1; i<=dim_mul_table;++i){vector_internal[i] = 0;}

   
  while (ct1<algebra_dimension)
  {
	  ct2++; 
	
	  if (permutation_added[ct2] == 1)
	   {
		 ct1++; 
	
		 for (int j=1;j<=dim_mul_table; ++j )
         {
			if (matrix_M[ct2][j] ==1){vector_internal[j] = vector_internal[j]+1;}
			if (matrix_M[ct2][j] ==2){vector_internal[j] = vector_internal[j]+2;} 
		 } 	
		 
	   }
  }	  
  
   while (bool_algebra && ct0 < dim_mul_table)
   {
	    ct0++; 
	    if ( vector_internal[ct0] == 2)
		{
			for (int k=1;k<=dim_Q; ++k )
			{
				if (matrix_Q[k][ct0] == 1 && permutation_added[k] == 0)
				{
				  bool_algebra=false;
				}
			}	  
		}	 
   }
  

   if (bool_algebra_reduced && bool_algebra)
   {
	 for (int k=1;k<=dim_Q; ++k )
	 {
	   if( permutation_added[k] == 1 && bool_algebra)
       {
		    multientry =0;
		    for (int k2=1;k2<=dim_mul_table; ++k2)
			{
			 if ( vector_internal[k2] == 2 && multientry ==0)
		     {	 
				
				if (matrix_M[k][k2] > 0){multientry++;}
				
				if (matrix_Q[k][k2] > 0){multientry++;}
			 }
			}	//   for (int k2=1;k2<=dim_mul_table; ++k2)				
	      if (multientry==0){bool_algebra_reduced=false;}
	   }		   
	 }				
   } 	
   
  //  saving the multiplication table of the subalgebra. 
   if (bool_algebra)
   {
	   number_algebra++;  
	  for (int k=1;k<=dim_mul_table; ++k )
	  {
		if(vector_internal[k] == 2){  nonzero_mtable[number_algebra][k] =1;}
	  }
   }
  
delete [] vector_internal;

return;}





