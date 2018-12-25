/*
 * runtime.h
 *
 *      Author: Uğur Ali Kaplan
 *      Number: 150170042
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include <string>

struct Statement
{
    std::string type;
    std::string arg1;
    std::string arg2;
};

typedef unsigned AddressValue;
typedef int ScalarValue;

struct Frame
{
    unsigned int value;
    Frame *previous;
};

template <typename T>
struct Stack
{
    Frame *top;

    Stack() { top = NULL; }
    void push(T val);
    T pop();
    bool is_empty();
};

template <typename T>
void Stack<T>::push(T val)
{
    Frame *new_data = new Frame;
    new_data->value = (long)val;
    new_data->previous = top;
    top = new_data;
}

template <typename T>
T Stack<T>::pop()
{
    Frame *to_destroy = top;
    top = top->previous;
    T to_ret = (T)to_destroy->value;
    delete to_destroy;
    return to_ret;
}

template <typename T>
bool Stack<T>::is_empty()
{
    if (!top)
        return true;
    return false;
}

AddressValue executeStatement(const Statement &statement, const AddressValue currentAddress, ScalarValue variables[5], Stack<ScalarValue> &callStack, const AddressValue addressOfCalleeIfCall, bool &isDone);

#endif /* RUNTIME_H_ */
