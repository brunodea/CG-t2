#include "Core/Matrix.hpp"

#include <cstdlib>

int main()
{
    Core::Matrix<int> m = Core::Matrix<int>(2, 2);

    for(int i = 0; i < m.getRows(); i++)
    {
        for(int j = 0; j < m.getCols(); j++)
            m.set(i*m.getCols() + j, i, j);
    }

    Core::Matrix<int> m2 = Core::Matrix<int>(1, 2);

    for(int i = 0; i < m2.getRows(); i++)
        for(int j = 0; j < m2.getCols(); j++)
            m2.set(2, i, j);

    Core::Matrix<int> m3(m);
    m3 += m2;
    m3 += (m2 * m);
    m3 *= 2;
    m3 += m - m2 + (m3*4) + (m2/3);

    m3.print();


    system("pause");

    return 0;
}

