#ifndef _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_
#define _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_

#include "Core/Matrix.hpp"
#include "Core/Vector.hpp"

#include <cmath>

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
    Matrix<float, M> translate(const Vector<float, M> &vec)
    {
        Matrix<float, M> res = identity<M>();

        for(unsigned int i = 0; i < M; i++)
            res.set(vec(i, 0), i, M-1);

        return res;
    }

    inline Matrix3 rotate(float ang)
    {
        Matrix3 res = identity<3>();
        res.set(cos(ang), 0, 0);
        res.set(sin(ang), 1, 0);
        res.set(-sin(ang), 0, 1);
        res.set(cos(ang), 1, 1);

        return res;
    }

    template<unsigned int M>
    const float norm(const Vector<float, M> &vec)
    {
        float sum = 0.f;
        for(unsigned int i = 0; i < M; i++)
            sum += (vec(i,0)*vec(i,0));
        return sqrt(sum);
    }

    template<unsigned int M>
    const Core::Vector<float, M>unitary(const Vector<float, M> &vec)
    {
        Core::Vector<float, M> res;
        float n = norm(vec);
        for(unsigned int i = 0; i < M; i++)
            res.set(vec(i,0)/n, i, 0);
        return res;
    }

    template<unsigned int M>
    const Matrix<float, M, 1> toMatrix(const Vector<float, M> &vec)
    {
        Matrix<float, M, 1> res;
        for(unsigned int i = 0; i < M; i++)
            res.set(vec[i], i, 0);

        return res;
    }

    template<unsigned int M>
    const Vector<float, M> toVector(const Matrix<float, M, 1> &mat)
    {
        Vector<float, M> res;
        for(unsigned int i = 0; i < M; i++)
            res[i] = mat(i, 0);
        return res;
    }

} //end of namespace Core.


#endif
