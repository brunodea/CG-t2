#ifndef _BRUNODEA_CG_T2_CORE_MATRIX_H_
#define _BRUNODEA_CG_T2_CORE_MATRIX_H_

#include "macros.h"
#include <iostream>

namespace Core
{
    template<class T>
    class Matrix
    {
    public:
        Matrix(const unsigned int rows, const unsigned int cols)
            : m_Rows(rows), m_Cols(cols)
        {
            if(rows > MATRIX_MAX_ROWS)
                m_Rows = MATRIX_MAX_ROWS;
            if(cols > MATRIX_MAX_COLS)
                m_Cols = MATRIX_MAX_COLS;
        }
        ~Matrix()
        {
        }

        inline void set(const T &value, const unsigned int row, const unsigned int col)
        {
            m_Elements[row*MATRIX_MAX_COLS + col] = value;
        }

        inline T &operator ()(const unsigned int i, const unsigned int j)
        {
            return m_Elements[i*MATRIX_MAX_COLS + j];
        }

        inline Matrix<T> &operator =(const Matrix<T> &mat)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set(mat(i,j), i, j);
            }

            return *this;
        }
        
        inline Matrix<T> &operator +(Matrix<T> &m1)
        {
            Matrix<T> *res = new Matrix<T>(m_Rows, m_Cols);
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    res->set((*this)(i,j)+m1(i,j), i, j);
            }
            return *res;
        }

        inline Matrix<T> &operator *(Matrix<T> &m)
        {
            unsigned int rows_2 = m.getRows();

            Matrix<T> *res = new Matrix<T>(m_Rows, m.getCols());
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                {
                    T val = 0;
                    for(unsigned int k = 0; k < rows_2; k++)
                    {
                        val += (*this)(i,k)*m(k,j);
                    }
                    res->set(val, i, j);
                }
            }
            return *res;
        }
        
        inline int getRows() { return m_Rows; }
        inline int getCols() { return m_Cols; }

    private:
        T m_Elements[MATRIX_MAX_ROWS*MATRIX_MAX_COLS];
        unsigned int m_Rows;
        unsigned int m_Cols;

    private:
        bool is_valid(const unsigned int i, const unsigned int j)
        {
            if(i < 0 || i >= m_Rows || j < 0 || j >= m_Cols)
                return false;
            return true;
        }
    };
}

#endif

