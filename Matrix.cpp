#include "Matrix.h"

Matrix::Matrix() : Matrix(1, 1) { }

Matrix::Matrix(int r, int c) {
	setRows(r);
	setCols(c);
	m_data = allocateMem(m_rows, m_cols);
	init_m_data();
}

Matrix::Matrix(const Matrix& other) : Matrix(other.getRows(), other.getCols()){
    for (int i = 0; i < other.getRows(); i++) {
		for (int j = 0; j < other.getCols(); j++) {
			this->m_data[i][j] = other.m_data[i][j];
		}
	}
}

Matrix::~Matrix() {
	deallocateMem();
	m_data = nullptr;
}

void Matrix::setRows(int r) { m_rows = r; }
void Matrix::setCols(int c) { m_cols = c; }

int Matrix::getRows() const { return m_rows; }
int Matrix::getCols() const { return m_cols; }



double **Matrix::allocateMem(int r, int c) {

	setRows(r);
	setCols(c);

	double **new_matrix = new double *[m_rows];

	for (int i = 0; i < m_rows; i++) {
		new_matrix[i] = new double[m_cols];
	}

	return new_matrix;
}


void Matrix::deallocateMem() {
	for (int i = 0; i < m_rows; i++) {
		delete[] m_data[i];
	}
	delete [] m_data;
}

void Matrix::printToScreen(int prcsn) {
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {

			cout << fixed << setprecision(prcsn) << m_data[i][j] << "  ";
		}
		cout << endl;
	}
}

void Matrix::setValueAtElement(int indr, int indc, double val) {
	if ( (indr < m_rows) && (indr >= 0) && (indc < m_cols) && (indc >= 0) )
		m_data[indr][indc] = val;
	else {
		try {
			throw runtime_error("Out of index");
		}
		catch (runtime_error& ex) {
			cout << endl << "Error in Matrix::setValueAtElement()! : " << ex.what() << endl;
			cin.get();
			exit(1);
		}
	}
		

}

double  Matrix::getValueAtElement(int indr, int indc) { 
	try {

		if (indr >= m_rows || indc >= m_cols || indr < 0 || indc < 0)
			throw runtime_error("Out of index");
	}
	catch (runtime_error& ex) {
		cout << endl << "Error in Matrix::getValueAtElement()! : " << ex.what() << endl;
		cin.get();
		exit(1);
	}

	return m_data[indr][indc];
}




void Matrix::identityMatrix(int n){
	reSize(n,n);
	for (int i = 0; i < this->getRows(); i++)
		m_data[i][i] = 1.0;
}



void Matrix::init_m_data() {
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			m_data[i][j] = 0.0;
		}
	}
}

void Matrix::reSize(int new_r, int new_c) {
 //This works
	this->deallocateMem();
	setRows(new_r);
	setCols(new_c);
	m_data = allocateMem(new_r, new_c);
	init_m_data();
}


Matrix operator +(const Matrix& A, const Matrix& B) {
	try {

        if ( (B.getRows() != A.getRows())  || ( B.getCols() != A.getCols() ))
			throw runtime_error("The dimensions of the matrices do not match, Matrix Addition/Subtraction");
	}
	catch (runtime_error& ex){
			cout << endl << "Error ! : " << ex.what() << endl;
			exit (1);
	}

	Matrix T(A.getRows(), A.getCols());

	for (int i = 0; i < A.getRows(); i++)
		for (int j = 0; j < A.getCols(); j++)
			T.m_data[i][j] = A.m_data[i][j] + B.m_data[i][j];

	return T;
}

void Matrix::operator =(const Matrix& A) {

    // create a new matrix with the same dimension
	this->reSize(A.getRows(),A.getCols());

	for (int i = 0; i < A.getRows(); i++)
		for (int j = 0; j < A.getCols(); j++)
			m_data[i][j] = A.m_data[i][j];

}


// C m u = A m n * B n u
Matrix operator *(const Matrix& A, const Matrix& B){
    try {
        if (A.getCols() != B.getRows())
            throw runtime_error("The dimensions of the matrices do not match , Matrix Multiplication");
    }
    catch(runtime_error& ex){
        cout << endl << "Error !: " << ex.what() << endl;
		cin.get();
        exit (1);
    }


    int m = A.getRows();
    int n = A.getCols();
    int u = B.getCols();
    Matrix T(m,u);

    for (int i = 0; i < m ; i ++) {
        for (int k = 0; k < u; k++) {
            double sum = 0;
            for (int j = 0; j < n; j++ ) {
                sum += A.m_data[i][j] * B.m_data[j][k];
            }
            T.m_data[i][k] = sum;
        }
    }
    return T;
}





// Cmn = k * Amn
Matrix operator *(const Matrix& A, double k){

    int m = A.getRows();
    int n = A.getCols();
    Matrix T(m,n);
    for (int i = 0; i < m; i++){
        for (int j=0; j < n; j++){
            T.m_data[i][j] = k * A.m_data[i][j];
        }
    }

    return T;
}



Matrix operator *(double k, const Matrix& A){
    Matrix T;
    T = A*k;

    return T;
}


Matrix operator -(const Matrix& A, const Matrix& B){
    Matrix T;
    T = A+(-1.0*B);
    return T;
}




Matrix transpose(const Matrix& A){
	int m = A.getRows();
	int n = A.getCols();
	Matrix T(n,m);

	 for (int i = 0; i < n; i++)
		 for (int j = 0; j < m; j++)
			 T.m_data[i][j] = A.m_data[j][i];

	 return T;
 }

// Transpose
Matrix operator ~(const Matrix& A){
    Matrix T;
    T = transpose(A);
    return T;
}



// - 0- Determinant
double det(const Matrix& T)
{
    try {
        if ( T.getRows() != T.getCols() )
            throw runtime_error("The size of the matrix must be n x n for the Determinant");

    }
    catch (runtime_error& ex){
        cout <<"Error :" << ex.what();
        exit (1);
    }

    double d = 0.0;
    int n = T.getRows();

    if ( n == 2 )
    {
        d = T.m_data[0][0] * T.m_data[1][1] - T.m_data[0][1] * T.m_data[1][0];
        return d;
    }
    else if ( n == 3 )
    {
        d =     T.m_data[0][0] * ( T.m_data[1][1] * T.m_data[2][2] - T.m_data[2][1] * T.m_data[1][2]);
        d = d - T.m_data[0][1] * ( T.m_data[1][0] * T.m_data[2][2] - T.m_data[2][0] * T.m_data[1][2]);
        d = d + T.m_data[0][2] * ( T.m_data[1][0] * T.m_data[2][1] - T.m_data[2][0] * T.m_data[1][1]);
        return d;
    }
    else
    {
        for (int i = 0; i < n ; i++)
        {
            if ( n > 3)
            {
                Matrix B(n-1, n-1);
                B = T.subMatrix(0,i);
                d = d + pow( -1.0, i ) * T.m_data[0][i] * det(B); 
            }
        }
        return d;
    }// end of if block
} // end of det method



// r is the index of row, c is the index of column it is NOT the element!
Matrix  Matrix:: subMatrix(int r, int c ) const {

    int n = this->getRows()-1;
    int m = this->getCols()-1;
    Matrix T(n,m); // Tnm: T is a matrix of n rows and m columns

    bool rowFound = false;

    for (int i = 0; i < n; i++ ){

        if (i == r) rowFound = true;
        bool colFound = false;

        for (int j = 0 ; j < m; j++){

            if (j == c) colFound = true;

            if ( (!rowFound) && (!colFound) )

                T.m_data[i][j] = this->m_data[i][j] ;

            else if ( (rowFound) && (!colFound) )

                T.m_data[i][j] = this->m_data[i+1][j];

            else if ( (!rowFound) && (colFound) )

                T.m_data[i][j] = this->m_data[i][j+1];

            else

                T.m_data[i][j] = this->m_data[i+1][j+1];
         }

    }

    return T;

}




// A nm
Matrix inv(const Matrix & A){

    const double EPS = 1e-9;

    int n = A.getRows();
    int m = A.getCols();

    Matrix T(n,m);

	try {

	    if (n != m)
            throw runtime_error("The size of the matrix must be n x n for matrix inversion");

        if (  fabs( det(A) )  < EPS )
			throw runtime_error("The matrix is ill-conditioned (singular)");
	}
	catch (runtime_error& ex){
			cout << endl << "Error ! : " << ex.what() << endl;
			cin.get();
			exit (1);
	}

	Matrix C(n,m); // Cofactor matrix
    for (int i = 0; i < n; i++ ){
        for (int j = 0; j < m; j++){
            C.m_data[i][j] = pow( -1, i+j ) * det( A.subMatrix(i,j) ) ; 
        }
    }

    Matrix Adj = transpose(C); //transpose
    T = (1.0/det(A)) * Adj;

    return T;
}


// WriteToFile() function writes the matrix to a file
void Matrix::writeToFile(const string& filename){
    ofstream outFile(filename);
    outFile << scientific;
    for (int i = 0; i < m_rows; i++){
        for (int j = 0; j < m_cols; j++ ){
			outFile << right << setw(15) << m_data[i][j] ;
        }
        outFile << endl;
    }
    outFile.close();
}



// countWord() function counts the words in a given line
int countWord(const string& line) {
        int cnt = 0;

        int columnStart = 0;

        for (unsigned int i = 0; i < line.size(); i++){

                if ( (line[i]==' ') && (line[i+1]==' ') )

                    continue;

                else if (line[i]==' ')

                        columnStart = i+1;

                else if (  (line[i] !=' ') && ( (line[i+1]==' ') || (line[i+1] == '\0') ) ) {

                        int length = i-columnStart+1;

                        string substring = line.substr( columnStart, length );

                        columnStart = i+1;

                        cnt++;
                }
        }

    return cnt;

}


void Matrix::readFromFile(const string& filename){
    ifstream inFile( filename );

    try {
        if (!inFile)
            throw runtime_error("No file exist!");
    }
    catch ( runtime_error& ex ){
        cout <<"Error : " << ex.what() << endl;
		cin.ignore();
        exit (1);
    }


    string line;


    int prevCountWord = 0;
    int curCountWord = 0;
    int n_row = 0;
    int n_col;

    while ( getline( inFile, line ) ){
            if (line.size() > 0){
                curCountWord = countWord(line);
                if (curCountWord > 0) {
                        n_row++;
                        //cout << curCountWord << endl;

                    if (n_row ==  1)
                        prevCountWord = curCountWord;

                    if (prevCountWord != curCountWord){
                        cout <<"Error in reading the input file: Invalid input format" << endl;
						cin.get();
                        exit(1);
                    }
                    prevCountWord = curCountWord;
                }
                n_col = prevCountWord;
            }
    }

    this->reSize(n_row,n_col);

    //rewind(inFile);
    inFile.clear() ;
    inFile.seekg(0, ios::beg) ;

     //double val;
     for (int i = 0; i < m_rows; i++){
        for (int j = 0; j < m_cols; j++){
            inFile >> m_data[i][j];
        }
     }

    inFile.close();
}


