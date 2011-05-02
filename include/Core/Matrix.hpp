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

        inline const T &operator ()(const unsigned int i, const unsigned int j) const
        {
            return m_Elements[i*MATRIX_MAX_COLS + j];
        }

        inline Matrix<T> &operator =(const Matrix<T> &m)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set(m(i,j), i, j);
            }

            return *this;
        }

        inline void operator +=(Matrix<T> &m)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set((*this)(i,j)+m(i,j), i, j);
            }
        }

        inline void operator -=(Matrix<T> &m)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set((*this)(i,j)-m(i,j), i, j);
            }
        }
        
        inline void operator *=(const T &val)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set((*this)(i,j)*val, i, j);
            }
        }

        inline void operator /=(const T &val)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set((*this)(i,j)/val, i, j);
            }
        }

        inline void clear(const T &val)
        {
            for(unsigned int i = 0; i < m_Rows; i++)
            {
                for(unsigned int j = 0; j < m_Cols; j++)
                    set(val, i, j);
            }
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
    }; //end of class Matrix.


    template<class T>
    inline Matrix<T> operator +(Matrix<T> &m1, Matrix<T> &m2)
    {
        Matrix<T> res = m1;
        res += m2;

        return res;
    }

    template<class T>
    inline Matrix<T> operator -(Matrix<T> &m1, Matrix<T> &m2)
    {
        Matrix<T> res = m1;
        res -= m2;

        return res;
    }

    template<class T>
    inline Matrix<T> &operator *(Matrix<T> &m1, Matrix<T> &m2)
    {
        unsigned int rows_1 = m1.getRows();
        unsigned int rows_2 = m2.getRows();
        unsigned int cols_2 = m2.getCols();

        Matrix<T> *res = new Matrix<T>(rows_1, cols_2);
        for(unsigned int i = 0; i < rows_1; i++)
        {
            for(unsigned int j = 0; j < cols_2; j++)
            {
                T val = 0;
                for(unsigned int k = 0; k < rows_2; k++)
                    val += m1(i, k)*m2(k, j);
                res->set(val, i, j);
            }
        }
        return *res;
    }

    template<class T>
    inline Matrix<T> operator*(Matrix<T> &m, T &val)
    {
        Matrix<T> res = m;
        res *= val;
        return res;
    }

    template<class T>
    inline Matrix<T> operator/(Matrix<T> &m, T &val)
    {
        Matrix<T> res = m;
        res /= val;
        return res;
    }

} //end of namespace Core.

#endif

