#include <iostream>

template <typename T>
class Set {
private:
    T* elements;
    int size;
    int capacity;

public:
    // Конструктор
    Set(int initialCapacity) {
        size = 0;
        capacity = initialCapacity;
        elements = new T[capacity];
    }

    // Деструктор
    ~Set() {
        delete[] elements;
    }

    // Добавление элемента в множество
    void addElement(T element) {
        if (!contains(element)) {
            if (size == capacity) {
                // Увеличиваем емкость массива, если необходимо
                int newCapacity = capacity * 2;
                T* newElements = new T[newCapacity];
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
    void removeElement(T element) {
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
    bool contains(T element) const {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }

    // Объединение множеств
    Set<T> unionSets(const Set<T>& otherSet) const {
        Set<T> resultSet(size + otherSet.size);

        for (int i = 0; i < size; i++) {
            resultSet.addElement(elements[i]);
        }

        for (int i = 0; i < otherSet.size; i++) {
            resultSet.addElement(otherSet.elements[i]);
        }

        return resultSet;
    }

    // Пересечение множеств
    Set<T> intersection(const Set<T>& otherSet) const {
        Set<T> resultSet(size);

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

// Функция для ввода элементов множества
template <typename T>
void inputSetElements(Set<T>& set) {
    int numElements;
    std::cout << "Enter the number of elements: ";
    std::cin >> numElements;
    std::cout << "Enter the elements: ";
    for (int i = 0; i < numElements; i++) {
        T element;
        std::cin >> element;
        set.addElement(element);
    }
}

int main() {
    // Пример использования шаблонного класса Set
    int initialCapacity;
    std::cout << "Enter the initial capacity of the sets: ";
    std::cin >> initialCapacity;

    Set<int> intSet(initialCapacity);
    std::cout << "Enter elements for Int Set:\n";
    inputSetElements(intSet);

    Set<char> charSet(initialCapacity);
    std::cout << "Enter elements for Char Set:\n";
    inputSetElements(charSet);

    // Объединение множеств
    Set<int> unionIntSet = intSet.unionSets(intSet);
    std::cout << "Union of Int Sets: ";
    unionIntSet.printSet();

    Set<char> unionCharSet = charSet.unionSets(charSet);
    std::cout << "Union of Char Sets: ";
    unionCharSet.printSet();

    // Пересечение множеств
    Set<int> intersectionIntSet = intSet.intersection(intSet);
    std::cout << "Intersection of Int Sets: ";
    intersectionIntSet.printSet();

    Set<char> intersectionCharSet = charSet.intersection(charSet);
    std::cout << "Intersection of Char Sets: ";
    intersectionCharSet.printSet();

    return 0;
}
