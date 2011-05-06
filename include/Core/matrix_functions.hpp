#ifndef _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_
#define _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_

#include "Core/Matrix.hpp"

namespace Core
{
    typedef Matrix<float, 3, 1> Vector3;
    typedef Matrix<float, 3> Matrix3;
    typedef Matrix<float, 2> Matrix2;

    template<unsigned int M>
    const Matrix<float, M> indentity()
    {
        Matrix<float, M> res;
        for(unsigned int i = 0; i < M; i++)
        {
            for(unsigned int j = 0; j < M; j++)
            {
                if(i == j)
                    res.set(1.f, i, j);
                else
                    res.set(0.f, i, j);
            }
        }

        return res;
    }

    template<unsigned int M>
    const Matrix<float, M> translate(const Matrix<float, M, 1> &vec)
    {
        Matrix<float, M> res = indentity<M>();

        for(unsigned int i = 0; i < M; i++)
            res.set(vec(i, 0), i, M-1);

        return res;
    }

} //end of namespace Core.

#endif
