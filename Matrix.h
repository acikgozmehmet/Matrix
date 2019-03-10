/**
    Matrix.cpp
	@author : Mehmet Acikgoz

	Purpose: Matrix operations in a dynamically allocated memory.

	Matrix class can handle the following matrix operations with interactive and file input/output options.
    - matrix addition,
    - matrix subtraction,
    - matrix multiplication,
    - scalar product
	- determinant
	- inverse
*/

#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

class Matrix {

/**
    Returns the addition matrix of two matrices.

    @param A is an n × m matrix.
    @param B is an n × m matrix.
    @return Addition matrix of n x m.
*/
	friend Matrix operator +(const Matrix& A, const Matrix& B);

/**
    Returns the subtraction of matrix B from matrix A.

    @param A is an n × m matrix.
    @param B is an n × m matrix.
    @return The subtraction of matrices, n x m.
*/
	friend Matrix operator -(const Matrix& A, const Matrix& B);

/**
    Returns the multiplication matrix of two matrices.

    @param A is an n x m matrix.
    @param B is an m x k matrix.
    @return matrix product AB is an n x k matrix.
*/
  	friend Matrix operator *(const Matrix& A, const Matrix& B);

/**
    Returns the scalar multiplication of a matrix.

    @param A is an n x m matrix.
    @param k is a scalar .
    @return Ak is the scalar product matrix of n x m.
*/
    friend Matrix operator *(const Matrix& A, double k);

/**
    Returns the scalar multiplication of a matrix.

    @param k is a scalar .
    @param A is an n x m matrix.
    @return kA is the scalar product matrix of n x m.
*/
    friend Matrix operator *(double k, const Matrix& A);

/**
    Returns the transpose of a matrix.

    @param A is an n x m matrix.
    @return The transpose matrix of m x n.
*/
    friend Matrix transpose(const Matrix& A);

/**
    Returns the transpose of a matrix.
    (This is the operator-overloading of tranpose method.)

    @param A is an n x m matrix.
    @return The transpose matrix of m x n.
*/
    friend Matrix operator ~(const Matrix & A); // transpose

/**
    Returns the determinant of a matrix.

    @param T is an n x n matrix.
    @return The determinant of which is an also n x n matrix.
*/
    friend double det(const Matrix & T); //determinant

/**
    Returns the inverse of a matrix.

    @param A is an n x n matrix.
    @return The inverse matrix with the size of n x n.
*/
    friend Matrix inv(const Matrix& A ); // inverse

/**
    Returns the number of the words in a given string line.

    @param  string (sequences of characters)
    @return The number of words in the string.
*/
    friend int countWord(const string& line);



public:
/**
    Default constructor
*/
	Matrix();
/**
    Parameterized Constructor

	@param r is the number of rows of matrix
	@param c is the number of columns of matrix
*/

	Matrix( int r, int c );
/**
    Copy constructor

	@param other is an n x m matrix
*/
	Matrix( const Matrix& other);
/**
   Deconstructor
*/
	~Matrix();

/**
    Sets the value for the number of rows in the matrix.

    @param  r is the value for the number of rows in the matrix.
    @return None.
*/
	void setRows(int r);

/**
    Sets the value for the number of columns in the matrix.

    @param  c is the value for the number of columns in the matrix.
    @return None.
*/
	void setCols(int c);

/**
    Returns the value for the number of the rows in the matrix.
    @param  None
    @return number of rows in the matrix.
*/
	int getRows() const	;

/**
    Returns the value for the number of the columns in the matrix.
    @param  None
    @return number of columns in the matrix.
*/
	int getCols() const ;

/**
    Prints the matrix on the screen with the given precision.
    @param  prcsn is the precision of decimal places.
    @return None.
*/
	void printToScreen(int prcsn = 4);

/**
    Sets the value for the defined element in the matrix.
    @param  indr is the index value for the element at row.
    @param  indc is the index value for the element at column.
    @param  val is the value for the element defined at row indr and at column indc.
    @return None
*/
	void setValueAtElement(int indr, int indc, double val);


/**
	Returns the value for the defined element in the matrix.
	@param  indr is the index value for the element at row.
	@param  indc is the index value for the element at column.
	@return the value for the defined element in the matrix at row indr and column indc.
*/
	double getValueAtElement(int indr, int indc);


/**
    Creates an identity matrix (n x n)
    @param  n is the number of rows and columns defined in the identity matrix.
    @return None.
*/
	void identityMatrix(int n);

/**
    Assigns a matrix to another matrix.
    @param  A is the matrix to be assigned.
    @return None
*/
	void operator =(const Matrix& A);

/**
    Writes the matrix to a file in a scientific format.
    @param  filename is the output filename.
    @return none
*/
    void writeToFile(const string& filename);

/**
    Reads the matrix from a file.
    @param  filename is the input file name.
    @return none
*/
    void readFromFile(const string& filename);

private:
	int m_rows;
	int m_cols;
	double **m_data;

/**
    Allocates memory for the dynamically created matrix.
    @param  r is the number of rows in the matrix.
    @param  c is the number of column in the matrix.
    @return dynamically allocated matrix defined by pointer to pointer
*/
	double **allocateMem(int r, int c);

/**
    Deallocates memory for the dynamically created matrix.
    @return None
*/
	void deallocateMem();

/**
    Initializes the values of the of the elements in the matrix to 0.0
    @return None
*/
	void init_m_data(); // sets the Matrix elements to 0.0

/**
    Resizes the matrix
    @param  new_r is the number of rows in the matrix.
    @param  new_c is the number of columns in the matrix.
    @return None
*/

	void reSize(int new_r, int new_c);

/**
    Created a submatrix of a given matrix by deleting the row and column indices.
    @param  r is the index of row to be deleted in the matrix.
    @param  c is the index of the column to be deleted in the matrix.
    @return A new matrix created by deleting the given row and column indices.
*/
    Matrix subMatrix(int r, int c ) const;

};


#endif // !MATRIX_H

