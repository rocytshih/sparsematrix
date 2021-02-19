#ifndef SPARSE_H_MATRIX
#define SPARSE_H_MATRIX
    #include <iostream>
    #include <vector>
    #include <string>
    #define Maxterms (5)
    class matrixterm{
        friend class sparsematrix;
        private :
            int row, col, value;
    };

    class sparsematrix{
        private:
            int rows, cols, terms;/*terms 代表非0的數目*/
            matrixterm smArray[Maxterms];
        public:
            sparsematrix transpose();
            sparsematrix fast_transpose();
            int create();
            void sort(int terms);
            void swap(matrixterm *a, matrixterm *b);
            void print();
    };
#endif