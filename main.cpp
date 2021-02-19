#include <iostream>
#include <string>
#include "sparse_matrix.h"
using namespace std;
int main()
{
    int rc;
    sparsematrix A;
    rc = A.create();
    if(rc == 1){
        cout<<"----MATRIX----"<<endl;
        A.print();
        sparsematrix A_t;
        // A_t = A.transpose();
        A_t = A.fast_transpose();
        cout<<"----MATRIX TRANSPORT----"<<endl;
        A_t.print();
    }
    else{
        cout<<"----FAIL----"<<endl;
    }
    system("pause");
    return 0;
}