#include "sparse_matrix.h"
using namespace std;

void sparsematrix::swap(matrixterm *a, matrixterm *b){
    matrixterm temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void sparsematrix::sort(int terms){
    int i, j, min;
    for(i = 0;i<terms-1;i++){
        min = i;
        for(j = i+1;j<terms;j++){
            if(smArray[j].row < smArray[min].row){
                min = j;
            }
        }
        swap(&smArray[i], &smArray[min]);
    }
    
}

sparsematrix sparsematrix::transpose(){
    sparsematrix B;
    B.cols = rows;
    B.rows = cols;
    B.terms = terms;
    if(terms > 0){
        int currentB = 0;/*新產生sparsematrix的指標*/
        for(int c= 0;c<cols;c++){
            for(int i = 0; i<terms; i++){
                if(smArray[i].col == c){/*檢查當前的c與輸入的矩陣是否有存在一樣的column*/
                    B.smArray[currentB].row = c;
                    B.smArray[currentB].col = smArray[i].row;
                    B.smArray[currentB].value = smArray[i].value;
                    currentB++;
                }
            }
        }
    }
    return B;
}

sparsematrix sparsematrix::fast_transpose(){
    sparsematrix B;
    int *RowSize = new int[cols];
    int *RowStart = new int[cols];
    B.cols = rows;
    B.rows = cols;
    B.terms = terms;
    int i = 0;
    if(terms > 0){
        for(i = 0; i<cols; i++){            /*O(columns)*/
            RowSize[i] = 0; 
        }
        for(i = 0; i<terms; i++){           /*O(terms)*/
            RowSize[smArray[i].col]++;
        }
        RowStart[0] = 0;
        for(i = 1; i<cols; i++){            /*O(columns-1)*/
            RowStart[i] = RowSize[i-1] + RowStart[i-1];
        }
        for(i = 0; i <terms; i++){          /*O(terms)*/
            int j = RowStart[smArray[i].col]; 
            B.smArray[j].row = smArray[i].col;
            B.smArray[j].col = smArray[i].row;
            B.smArray[j].value = smArray[i].value;
            RowStart[smArray[i].col]++;
            // int j = RowStart[4]; /*j = 6*/
            // B.smArray[6].row = 4;
            // B.smArray[6].col = 0;
            // B.smArray[6].value = 91;
            // RowStart[4]++; /*更新rowstart位置*/ 
        }
    }
    delete [] RowSize;
    delete [] RowStart;
    return B;
}

int sparsematrix::create(){
    cout<<"======================================"<<endl;
    cout<<"matrix row:";
    cin>>rows;
    cout<<"matrix column:";
    cin>>cols;
    cout<<"matrix terms:";
    cin>>terms;
    cout<<"The matrix is "<<rows<<"*"<<cols<<endl;
    char ch = 'a';
    int index = 0;
    while(ch != '#'){
        cout<<"row index:";
        cin>>smArray[index].row;
        cout<<"col index:";
        cin>>smArray[index].col;
        cout<<"value:";
        cin>>smArray[index].value;
        cout<<"continue?(press # to quit)";
        cin>>ch;
        index++;
    }
    if(terms != index){
        cout<<"wrong terms!"<<endl;
        return 0;
    }
    else{
        sort(index);
        return 1;
    }
}

void sparsematrix::print(){
    int terms_index = 0;
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){
            if(terms_index != terms){
                if(smArray[terms_index].row ==i && smArray[terms_index].col == j){
                    if(smArray[terms_index].value<10){
                        cout<<"    ";
                        cout<<smArray[terms_index].value;
                    }
                    else if(smArray[terms_index].value<100){
                        cout<<"   ";
                        cout<<smArray[terms_index].value;
                    }
                    else{
                        cout<<"  ";
                        cout<<smArray[terms_index].value;
                    }
                    terms_index++;
                }
                else{
                    cout<<"    0";
                }
            }
            else{
                cout<<"    0";
            }
        }
        cout<<endl;
    }
}