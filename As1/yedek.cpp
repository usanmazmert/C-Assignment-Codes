class Matrix{
    int **arr = NULL;
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
                    cout << input[j];
                    if(j == input.length() - 1){
                        str += input[j];
                        v[index] = convertStringToInteger(str);
                        str = "";
                        continue;
                    }
                    if(input[j] == ' '){
                        v[index] =convertStringToInteger(str);
                        str = "";
                        index++;
                    }else{
                        str += input[j];
                    }
                    //creating more than one decimal values
                } 
                arr[i] = v;
            }
            
            ReadStream.close();
            //printMatrix(row, column);
        }

        //destructor
        ~Matrix(){
            std::cout << "Matrix has been successfully deleted" << std::endl;
        }
        int** getMatrix(){
            return arr;
        }

        // Debugging method

        // eski versiyonda keySizeof(int)' e bölmen gerekebilir unutma bunu.
        void printMatrix(int row, int column){
            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    std::cout << arr[i][j] << " ";
                }
                cout << std::endl;
            }
        }
    
};