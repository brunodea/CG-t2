#include "Core/Matrix.hpp"

#include <cstdlib>

int main()
{
    Core::Matrix<int> m = Core::Matrix<int>(4, 4);

    for(int i = 0; i < 4; i++)
    {
       for(int j = 0; j < 4; j++)
           m.set(0, i, j);
    }
    

    Core::Matrix<int> m2 = Core::Matrix<int>(2, 4);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m2.set(2, i, j);

    Core::Matrix<int> m3 = m * m2;
    for(int i = 0; i < 4; i++)
    {
       int v;
       for(int j = 0; j < 4; j++)
       {
           v = m3(i, j);
           std::cout << v << ' ';
       }
       std::cout << std::endl;
    }


    system("pause");

    return 0;
}

