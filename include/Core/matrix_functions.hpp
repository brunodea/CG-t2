#ifndef _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_
#define _BRUNODEA_CG_T2_MATRIX_FUNCTIONS_HPP_

#include "Core/Matrix.hpp"
#include "Core/Vector3.hpp"

namespace Core
{
    typedef Matrix<float> MatrixF;

    inline MatrixF indentity(unsigned int mat_rows, unsigned int mat_cols)
    {
        MatrixF res(mat_rows, mat_cols);
        for(unsigned int i = 0; i < mat_rows, i++)
        {
            for(unsigned int j = 0; j < mat_cols; j++)
            {
                if(i == j)
                    res.set(1.f, i, j);
                else
                    res.set(0.f, i, j);
            }
        }

        return res;
    }

    inline MatrixF translate(const Vector3 &v, unsigned int mat_rows)
    {
        MatrixF res = identity(mat_rows, v.getCols());

        res.set(v(0,0), 0, 0);


        return res;
    }

} //end of namespace Core.

#endif
