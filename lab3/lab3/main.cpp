#include <iostream>

class Set {
private:
    int* elements;
    int size;
    int capacity;

public:
    // Конструктор
    Set(int initialCapacity) {
        size = 0;
        capacity = initialCapacity;
        elements = new int[capacity];
    }

    // Деструктор
    ~Set() {
        delete[] elements;
    }

    // Добавление элемента в множество
    void addElement(int element) {
        if (!contains(element)) {
            if (size == capacity) {
                // Увеличиваем емкость массива, если необходимо
                int newCapacity = capacity * 2;
                int* newElements = new int[newCapacity];
                for (int i = 0; i < size; i++) {
                    newElements[i] = elements[i];
                }
                delete[] elements;
                elements = newElements;
                capacity = newCapacity;
            }
            elements[size] = element;
            size++;
        }
    }

    // Удаление элемента из множества
    void removeElement(int element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                for (int j = i; j < size - 1; j++) {
                    elements[j] = elements[j + 1];
                }
                size--;
                return;
            }
        }
    }

    // Проверка вхождения элемента в множество
    bool contains(int element) const {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }

    // Объединение множеств
    Set unionSets(const Set& otherSet) const {
        Set resultSet(size + otherSet.size);

        for (int i = 0; i < size; i++) {
            resultSet.addElement(elements[i]);
        }

        for (int i = 0; i < otherSet.size; i++) {
            resultSet.addElement(otherSet.elements[i]);
        }

        return resultSet;
    }

    // Пересечение множеств
    Set intersection(const Set& otherSet) const {
        Set resultSet(size);

        for (int i = 0; i < size; i++) {
            if (otherSet.contains(elements[i])) {
                resultSet.addElement(elements[i]);
            }
        }

        return resultSet;
    }

    // Вывод множества
    void printSet() const {
        std::cout << "{ ";
        for (int i = 0; i < size; i++) {
            std::cout << elements[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }" << std::endl;
    }
};

int main() {
    int initialCapacity;
    std::cout << "Enter the initial capacity of the sets: ";
    std::cin >> initialCapacity;

    Set set1(initialCapacity);
    Set set2(initialCapacity);

    int numElements;

    std::cout << "Enter the number of elements for Set 1: ";
    std::cin >> numElements;
    std::cout << "Enter the elements for Set 1: ";
    for (int i = 0; i < numElements; i++) {
        int element;
        std::cin >> element;
        set1.addElement(element);
    }

    std::cout << "Enter the number of elements for Set 2: ";
    std::cin >> numElements;
    std::cout << "Enter the elements for Set 2: ";
    for (int i = 0; i < numElements; i++) {
        int element;
        std::cin >> element;
        set2.addElement(element);
    }

    // Пример использования класса Set
    std::cout << "Set 1: ";
    set1.printSet();

    std::cout << "Set 2: ";
    set2.printSet();

    // Объединение множеств
    Set unionSet = set1.unionSets(set2);
    std::cout << "Union: ";
    unionSet.printSet();

    // Пересечение множеств
    Set intersectionSet = set1.intersection(set2);
    std::cout << "Intersection: ";
    intersectionSet.printSet();

    return 0;
}
