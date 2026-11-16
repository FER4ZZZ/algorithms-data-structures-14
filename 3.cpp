#include <iostream>
#include <stack>
#include <stdexcept>
using namespace std;

class MinStack {
    stack<int> data;  // основной стек — хранит все элементы
    stack<int> mins;  // вспомогательный стек — на вершине всегда текущий минимум

public:
    // Добавление элемента в вершину стека
    void push(int x) {
        data.push(x);  // всегда кладём в основной стек

        // Во вспомогательный стек кладём новый минимум:
        // либо сам x (если он меньше/равен текущему минимуму),
        // либо повторяем текущий минимум (чтобы при pop вершины mins
        // автоматически "восстанавливался" предыдущий минимум)
        if (mins.empty() || x <= mins.top())
            mins.push(x);
        else
            mins.push(mins.top());
    }

    // Извлечение элемента из вершины
    void pop() {
        if (data.empty()) throw runtime_error("stack is empty");
        data.pop();  // убираем из основного стека
        mins.pop();  // синхронно убираем из стека минимумов
    }

    // Просмотр верхнего элемента (без извлечения)
    int top() const {
        if (data.empty()) throw runtime_error("stack is empty");
        return data.top();
    }

    // Минимальный элемент — всегда на вершине mins, поэтому O(1)
    int getMin() const {
        if (mins.empty()) throw runtime_error("stack is empty");
        return mins.top();
    }

    // Проверка на пустоту
    bool empty() const {
        return data.empty();
    }
};

int main() {
    MinStack st;

    // Демонстрация работы
    st.push(5);   // data: [5],          mins: [5]
    st.push(2);   // data: [5,2],        mins: [5,2]
    st.push(7);   // data: [5,2,7],      mins: [5,2,2]
    st.push(1);   // data: [5,2,7,1],    mins: [5,2,2,1]

    cout << "min = " << st.getMin() << "\n";  // 1
    st.pop();                                  // убрали 1
    cout << "min = " << st.getMin() << "\n";  // 2
    st.pop();                                  // убрали 7
    cout << "min = " << st.getMin() << "\n";  // 2
    st.pop();                                  // убрали 2
    cout << "min = " << st.getMin() << "\n";  // 5
    st.pop();                                  // убрали 5

    // Проверяем, что стек пуст
    cout << "empty = " << (st.empty() ? "yes" : "no") << "\n";  // yes
    return 0;
}