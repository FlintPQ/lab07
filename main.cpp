#include <iostream>
#include <algorithm>
#include "ultracoolcycledbufferallrightsreserved.h"
int main() {
    std::cout << "Hello, World!" << std::endl;

    UltraCoolCycledBufferAllRightsReserved<int> a;

    a.push_back(5);
    a.push_back(3);
    a.push_back(6);
    a.push_back(1);



    std::cout << *(a[1]);
    std::cout << *std::max_element(a.begin(), a.end());


}
