#ifndef _BRUNODEA_CG_T2_VECTOR3_H_
#define _BRUNODEA_CG_T2_VECTOR3_H_

/*
 * Classe vector lida com vetores. Eh apenas uma epecificacao da classe Matrix.
 */

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

        /* Produto Escalar. */
        inline float dotProduct(Vector<T, M> &vec)
        {
            float res = 0.f;
            for(unsigned int i = 0; i < M; i++)
                res += ((*this)(i, 0)*vec(i, 0));

            return res;
        }

        /* Produto vetorial. */
        inline Vector<T, 3> crossProduct(Vector<T, 3> &vec)
        {
            Vector<T, 3> res;
            res[0] = ((*this)(1,0)*vec(2,0)) - ((*this)(2,0)*vec(1,0));
            res[1] = ((*this)(2,0)*vec(0,0)) - ((*this)(0,0)*vec(2,0));
            res[2] = ((*this)(0,0)*vec(1,0)) - ((*this)(1,0)*vec(0,0));

            return res;
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
