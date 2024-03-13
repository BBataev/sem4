#include <iostream>
#include <list>
#include <iterator>


int main() {
    std::list<int> L;

    std::cout << "Enter the number of elements in the list L (it must be divisible by 3 without remainder): ";
    
    int quantity;

    std::cin >> quantity;

    if (quantity % 3 != 0)
    {
        std::cout << "The number you entered is not devisible by 3.";
        return 1;
    }

    std::cout << "Enter numbers for list: ";
    for (int i = 0; i < quantity; ++i) 
    {
        int num;
        std::cin >> num;

        L.push_back(num);
    }

    std::list<int>::iterator start = L.begin();

    for (int i = 0; i < L.size() / 3; ++i) 
    {
        std::cout << *start << " ";
        ++start;
    }
    std::cout << std::endl;

    advance(start, L.size() / 3);

    std::list<int>::reverse_iterator rit(start);

    for (int i = 0; i < L.size() / 3; ++i) 
    {
        std::cout << *rit << " ";
        ++rit;
    }
    std::cout << std::endl;

    std::list<int>::reverse_iterator rbegin = L.rbegin();

    for (int i = 0; i < L.size() / 3; ++i) 
    {
        std::cout << *rbegin << " ";
        ++rbegin;
    }
    std::cout << std::endl;

    return 0;
}
