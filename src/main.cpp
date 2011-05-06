#include "Core/Matrix.hpp"
#include "Core/Vector.hpp"
#include "Core/matrix_functions.hpp"

#include <cstdlib>

int main()
{
    Core::Matrix<int, 3, 3> m = Core::Matrix<int, 3, 3>();

    for(int i = 0; i < m.getRows(); i++)
    {
        for(int j = 0; j < m.getCols(); j++)
            m.set(i*m.getCols() + j, i, j);
    }
    m.print();

    Core::Matrix<int, 3, 3> m2 = Core::Matrix<int, 3, 3>();

    m2.clear(2);

    m2.print();

    Core::Matrix<int, 3, 3> m3;
    m3 = m + m2;
    m3 += (m2 * m);
    m3 *= 2;
    m3 += m - m2 + (m3*4) + (m2/3);

    m3.print();

    Core::Matrix3 m4 = Core::identity<3>();
    m4.print();

    Core::Vector3 v;
    v.clear(1);
    v[0] = 2;
    v[1] = 5;

    Core::Matrix3 m5 = Core::translate<3>(v);
    m5.print();

    system("pause");

    return 0;
}

