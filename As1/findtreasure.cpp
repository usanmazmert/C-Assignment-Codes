#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <cstdio>
#include <cstdlib>

using std::vector;
using std::string;
using std::cout;


string convertIntegerToString(int i){
    bool negative = false;
    if(i < 0){
        i = -i;
        negative = true;
    }
    char ch;
    string str = "";
    do{
        int numeral = i%10;
        ch = numeral + '0';
        str = ch + str;
        i /= 10;
    }while(i);
    if(negative){
        str = '-' + str;
    }
    return str;
};




class Matrix{
    int **arr;
    public:
        Matrix(int row, int column, string inputFile): arr(new int*[row]){
            string input;
            std::ifstream ReadStream;
            ReadStream.open(inputFile.c_str());
            string str = "";
            
            for(int i= 0; i < row; i++){
                int *v = new int[column];
                std::getline(ReadStream, input);
                int index = 0;
                for(int j = 0; j < input.length(); j++){
                    if(j == input.length()-1){
                        str += input[j];
                        v[index] =std::stoi(str);
                        str = "";
                    }
                    else if(input[j] == ' '){
                        v[index] =std::stoi(str);
                        str = "";
                        index++;
                    }
                    else{
                        str += input[j];
                    }
                }
                arr[i] = v;
            }
            
            ReadStream.close();
            //printMatrix(row, column);
        }

        //destructor
        ~Matrix(){

            //Deleting the matrix
            int arraySize = sizeof(arr[0]);
            for(int i = 0; i < sizeof(arr)/arraySize; i++){
                delete[] arr[i];
            }
            delete[] arr;
            std::cout << "Matrix has been successfully deleted" << std::endl;
        }

        int** getMatrix(){
            return arr;
        }

        // Debugging method
        void printMatrix(int row, int column){
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    std::cout << arr[i][j] << " ";
                }
                cout << std::endl;
            }
        }
    
};



string play(int** matrix,const int &row, const int &column, int** key,const int &keySize, int* coordinates)
{
    int x = coordinates[1];
    int y = coordinates[0];
    int kXIndex = 0;
    int sum = 0;
    for(int i = -(keySize - 1) / 2 ; i < (keySize + 1) / 2; i++)
    {
        int kYIndex = 0;
        for(int j = -(keySize - 1) / 2; j < (keySize + 1) / 2; j++)
        {
           sum += (matrix[y + i][x + j] * key[kXIndex][kYIndex]);
           kYIndex++;
        }
        kXIndex++;
    }
    int mode = sum % 5;
    if(mode < 0){
        mode += 5;
        sum = mode;
    }
    string output = convertIntegerToString(y) + "," + convertIntegerToString(x) + ":" + convertIntegerToString(sum);
    if(mode == 0)
    {
      return output;
    }

    switch (mode)
    {
        case 1:
            coordinates[0] = y - keySize >= 0 ? y - keySize: y + keySize; 
            break;
        case 2:
            coordinates[0] = y + keySize <= row ? y + keySize : y - keySize; 
            break;
        case 3: 
            coordinates[1] = x + keySize <= column ? x + keySize : x - keySize;
            break;
        case 4:
            coordinates[1] = x - keySize >= 0 ? x - keySize : x + keySize;
            break;
    }
    output += '\n';
    return output + play(matrix,row, column, key, keySize, coordinates);
}



int main(int argc, char** argv){
    //Assigning command line arguments
    string matrixkeySize = argv[1];
    int indexOfX = matrixkeySize.find('x');
    int row = std::stoi(matrixkeySize.substr(0, indexOfX));
    int column = std::stoi(matrixkeySize.substr(indexOfX + 1));
    int size = std::stoi(argv[2]);

    Matrix* matrix = new Matrix(row, column,argv[3]);
    Matrix* keyMatrix = new Matrix(size, size, argv[4]);

    std::ofstream WriteStream;
    WriteStream.open(argv[5]);
    int* coordinates = new int[2];
    coordinates[0] = size/2;
    coordinates[1] = size/2;
    string output = play(matrix->getMatrix(), row, column, keyMatrix->getMatrix(), size ,coordinates);
    //cout << output;
    WriteStream << output;
    WriteStream.close();
    delete matrix;
    delete keyMatrix;
    delete[] coordinates;
    return -1;
}