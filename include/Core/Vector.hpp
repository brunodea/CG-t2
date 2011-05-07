#ifndef _BRUNODEA_CG_T2_VECTOR3_H_
#define _BRUNODEA_CG_T2_VECTOR3_H_

#include "Core/Matrix.hpp"

namespace Core
{
    template<class T, unsigned int M>
    struct Vector : public Matrix<T, M, 1>
    {
        Vector() : Matrix<T, M, 1>() {}
        Vector(T val) : Matrix<T, M, 1>()
        {
            this->clear(val);
        }

        inline T &operator [](unsigned int i)
        {
            return (*this)(i, 0);
        }

        inline Vector<T, M> &operator =(Matrix<T, M, 1> &mat)
        {
            for(unsigned int i = 0; i < M; i++)
                set(mat(i, 0), i, 0);
            return (*this);
        }

    }; //end of struct Vector.
    
} //end of namespace Core.

#endif
