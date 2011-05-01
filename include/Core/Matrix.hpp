#ifndef _BRUNODEA_CG_T2_CORE_MATRIX_H_
#define _BRUNODEA_CG_T2_CORE_MATRIX_H_

namespace Core
{
    template<class T>
    class Matrix
    {
    public:
        Matrix(const int rows, const int cols)
            :
        {
            m_Matrix = new T*[rows];
            for(int i = 0; i < rows; i++)
                m_Matrix[i] = new T[cols];
        }
        ~Matrix()
        {
            for(int i = 0; i < m_Rows; i++)
                delete []m_ppMatrix[i];
            delete []m_ppMatrix;
        }
    private:
        T **m_ppMatrix;
        int m_Rows;
        int m_Cols;
    };
}

#endif

