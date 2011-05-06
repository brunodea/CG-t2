#include "Core/Matrix.hpp"

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


    system("pause");

    return 0;
}

