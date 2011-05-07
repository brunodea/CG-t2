#ifndef _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_
#define _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_

#include "Core/Matrix.hpp"
#include "Core/Vector.hpp"

namespace Core
{
    typedef Vector<float, 4> Vector4;
    typedef Vector<float, 3> Vector3;
    typedef Vector<float, 2> Vector2;

    typedef Matrix<float, 3> Matrix3;
    typedef Matrix<float, 2> Matrix2;

    template<unsigned int M>
    const Matrix<float, M> identity()
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
    const Matrix<float, M> translate(const Vector<float, M> &vec)
    {
        Matrix<float, M> res = identity<M>();

        for(unsigned int i = 0; i < M; i++)
            res.set(vec(i, 0), i, M-1);

        return res;
    }

} //end of namespace Core.

#endif
