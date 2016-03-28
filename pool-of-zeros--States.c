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
const int Rows = 4;
const int Cols = 4;
int matrix[Rows][Cols] = {{1,1,1,1},{1,0,0,1},{1,1,1,1},{1,1,1,1}};
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
	int state = 0;
	
	if(Rows < 3 || Cols < 3){
		printf("...ERROR: Matrix should be at least a 3x3, this is %dx%d\n", Rows, Cols);
		return 0;
	}

	for (i = 0; i < Rows; i++){
		switch (state){
			// ensure first line is all ones
			case 0:
				if(! all_ones(matrix[i]))
					return 0;
				state++;
				break;

			// continous loop for all ones
			case 1:
				// if this line does not have all ones, check for single pool
				if(! all_ones(matrix[i])){
					// if this line has no pools either, fail
					if(! single_pool_line(matrix[i]))
						return 0;
					// else, now check for single-pool
					state++;
				}
				break;

			// continous loop for single-pool line
			case 2:
				// if this line has no pools, check for all ones
				if(! single_pool_line(matrix[i])){
					// if this line is not all ones either, fail
					if(! all_ones(matrix[i]))
						return 0;
					// else, now check for all ones
					state++;
				}
				break;

			// final continous loop for all ones
			case 3:
				// if this line does not have all ones, fail
				if(! all_ones(matrix[i])){
					return 0;
				}
				break;

			default:
				return 0;

		}
	}

	if (state == 3)
		return 1;
	else
		return 0;
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
	int state = 0;

	for (i = 0; i < Cols; i++){
		switch(state){
			// ensure first element is a 1
			case 0:
				if(! line[i])
					return 0;
				state++;
				break;

			// continous loop for all ones
			case 1:
				// if series of ones broken by a 0
				if(! line[i]){
					// now loop for zeros
					state++;
				}
				break;

			// continous loop for all zeros
			case 2:
				// if series of zeros broken by a 1
				if(line[i]){
					// now loop for ones
					state++;
				}
				break;

			// final continous loop for all ones
			case 3:
				// if series of ones broken by a 0, fail
				if(! line[i]){
					return 0;
				}
				break;

			default:
				return 0;
		}
	}

	if (state == 3)
		return 1;
	else
		return 0;
}
