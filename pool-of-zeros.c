/*	Eusebius Ngemera
 * 	Created 1 Feb 2016
 *	Single pool of zeros surrounded by ones, in a matrix
 *
 *	For example,
 *	1111
 *	1101
 *	1001
 * 	1111
 */

#include <stdio.h>
#include <assert.h>

/* Global variables */
const int Rows = 2;
const int Cols = 3;
int matrix[Rows][Cols] = {{1,1,1},{1,0,1}};//,{1,1,1},{1,1,1}};

/* int is used a substitute for bool 
 * single_pool_matrix(...) returns 1 if the matrix (with global size parameters) has a single pool of zeros surrounded by ones
 *	and 0 otherwise
 */
int single_pool_matrix(int matrix[Rows][Cols]);
int all_ones(int line[Cols]);
int single_pool_line(int line[Cols]);

int main(){
	printf("Matrix has a single pool of zeros surrounded by ones:\n%s\n",
	 (single_pool_matrix(matrix)? "YES": "NO"));
	
	return 0;
}

/* Pool has all ones in all the lines above and below */
int single_pool_matrix(int matrix[Rows][Cols]){
	int i = 0;
	
	if(Rows < 3 || Cols < 3){
		printf("...ERROR: Matrix should be at least a 3x3, this is %dx%d\n", Rows, Cols);
		return 0;
	}

	if(! all_ones(matrix[i]))		// ensure first line is all ones
		return 0;
	for(i = 1; i < (Rows-2); i++)
		if(! all_ones(matrix[i]))		// this line is not all ones, now check lines for pool
			break;
	if(! single_pool_line(matrix[i]))	// this line has no pools either, fail
		return 0;
	
	for(i++; i < (Rows-1); i++)
		if(! single_pool_line(matrix[i]))	// this line has no pools, now check for all ones
			break;
	if(! all_ones(matrix[i]))				// this line is not all ones either, fail
		return 0;
	
	for(i++; i < Rows; i++)
		if(! all_ones(matrix[i]))	// ensure rest of the lines have all ones
			return 0;
	return 1;
}

int all_ones(int line[Cols]){
	int i;
	for(i = 0; i < Cols; i++)
		if(! line[i])
			return 0;
	return 1;
}

/* Valid lines part of a single pool
 *		101
 *		11..1100..0011..11
 *		1(1..1)0(0..0)1(1..1)
 */
int single_pool_line(int line[Cols]){
	int i = 0;
	if(! line[i])		// ensure first element is a 1
		return 0;
	for(i = 1; i < (Cols-2); i++){
		if(! line[i])	// series of ones broken by a 0
			break;
	}
	
	if(line[i])			// ensure at least a single 1
		return 0;
	for(i++; i < (Cols-1); i++){
		if(line[i])		// series of zeros broken by a 1
			break;
	}

	if(! line[i])		// ensure at least a single 0
		return 0;	
	for(i++; i < Cols; i++){
		if(! line[i])	// series of ones broken by a 0, invalid
			return 0;
	}

	return 1;
}
