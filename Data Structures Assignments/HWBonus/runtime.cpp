/*
 * runtime.cpp
 *
 *      Author: Uğur Ali Kaplan
 *      Number: 150170042
 */

#include "runtime.h"
#include <iostream>
#include <string>

AddressValue executeStatement(const Statement &statement,
                              const AddressValue currentAddress,
                              ScalarValue variables[5],
                              Stack<ScalarValue> &callStack,
                              const AddressValue addressOfCalleeIfCall,
                              bool &isDone)
{
    (void)variables;
    (void)callStack;
    (void)isDone;
    (void)addressOfCalleeIfCall;

    //std::cout << currentAddress << " - " << addressOfCalleeIfCall << std::endl;
    //std::cout << "[";
    
    /*for (int i = 0; i < 5; i++)
    {
        std::cout << variables[i];
        if (i != 4)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;*/

    // Your entry point is here

    // std::cout << "Executing " << statement.type << " at line " << currentAddress << std::endl;

    if (!statement.type.compare("inc"))
    {
        char index = (statement.arg1.c_str()[0] - 97);
        // check if the second argument is a member of the alphabet
        if (isalpha(statement.arg2[0]))
        {
            // Member of alphabet
            char second_index = (statement.arg2.c_str()[0] - 97);
            variables[(int)index] += variables[(int)second_index];
        }
        else
        {
            // Is a number
            ScalarValue num = stoi(statement.arg2);
            variables[(int)index] += num;
        }
    }
    else if (!statement.type.compare("dec"))
    {
        char index = (statement.arg1.c_str()[0] - 97);
        // check if the second argument is a member of the alphabet
        if (isalpha(statement.arg2[0]))
        {
            // Member of alphabet
            char second_index = (statement.arg2.c_str()[0] - 97);
            variables[(int)index] -= variables[(int)second_index];
        }
        else
        {
            // Is a number
            ScalarValue num = stoi(statement.arg2);
            variables[(int)index] -= num;
        }
    }
    else if (!statement.type.compare("mul"))
    {
        char index = (statement.arg1.c_str()[0] - 97);
        // check if the second argument is a member of the alphabet
        if (isalpha(statement.arg2[0]))
        {
            // Member of alphabet
            char second_index = (statement.arg2.c_str()[0] - 97);
            variables[(int)index] *= variables[(int)second_index];
        }
        else
        {
            // Is a number
            ScalarValue num = stoi(statement.arg2);
            variables[(int)index] *= num;
        }
    }
    else if (!statement.type.compare("div"))
    {
        char index = (statement.arg1.c_str()[0] - 97);
        // check if the second argument is a member of the alphabet
        if (isalpha(statement.arg2[0]))
        {
            // Member of alphabet
            char second_index = (statement.arg2.c_str()[0] - 97);
            variables[(int)index] /= variables[(int)second_index];
        }
        else
        {
            // Is a number
            ScalarValue num = stoi(statement.arg2);
            variables[(int)index] /= num;
        }
    }
    else if (!statement.type.compare("call"))
    {
        char index = statement.arg2[0] - 97;
        // push a, b, c, d, e, currentAddress
        for (int i = 0; i < 5; i++)
        {
            callStack.push(variables[i]);
            if (i != (int)index)
            {
                variables[i] = 0;
            }
        }

        callStack.push(currentAddress);
        return addressOfCalleeIfCall + 1;
    }
    else if (!statement.type.compare("return"))
    {
        // pop return address
        if (!callStack.is_empty())
        {
            AddressValue callerAddress = callStack.pop();
            char index = statement.arg1[0] - 97;
            for (int i = 4; i > -1; i--)
            {
                if (i != (int)index)
                {
                    variables[i] = callStack.pop();
                }
                else
                {
                    callStack.pop();
                }
            }

            return callerAddress + 1;
        }
        else
        {
            isDone = true;
            char index = statement.arg1[0] - 97;
            std::cout << variables[(int)index] << std::endl;
        }
    }

    //Return what address you want to go next
    return currentAddress + 1;
}
