/* @Author
**
** Student Name: Uğur Ali Kaplan
** Student ID : 150170042
** Date:  12.12.2018
**
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// Structs

struct Ant
{
    unsigned int num;
    Ant *next;
};

struct stackAnt
{
    Ant *top_ant;
    unsigned int limit;
    stackAnt() { top_ant = NULL; }
    void push(unsigned int num); // return false if limit is exceeded
    unsigned int pop();
    bool is_empty();
};

struct queueAnt
{
    Ant *front_ant;
    queueAnt() { front_ant = NULL; }
    void enqueue(unsigned int val);
    unsigned int dequeue();
    bool is_empty();
    void print();
};

struct Ants
{
    queueAnt ants;
    queueAnt holeDepths;
    stackAnt hole;
    void ReadFile(char *);   // Reads the file and creates ant and hole queues
    void ShowContents(bool); // Prints the contents of either ant sequence or holeDepths
    void CrossRoad();        // Ant queue marches forward!
};

// Struct functions

void queueAnt::enqueue(unsigned int val)
{
    Ant *a = new Ant;
    a->num = val;
    a->next = NULL;

    if (!front_ant)
    {
        front_ant = a;
        return;
    }

    Ant *traverser = front_ant;

    while (traverser->next)
    {
        traverser = traverser->next;
    }

    traverser->next = a;
    return;
}

unsigned int queueAnt::dequeue()
{
    unsigned int val = front_ant->num;
    Ant *to_delete = front_ant;
    front_ant = front_ant->next;
    delete to_delete;
    return val;
}

bool queueAnt::is_empty()
{
    if (!front_ant)
        return true;
    return false;
}

void queueAnt::print()
{
    Ant *traverser = front_ant;
    while (traverser)
    {
        cout << traverser->num << " ";
        if (!traverser->next)
            cout << endl;
        traverser = traverser->next;
    }
}

void stackAnt::push(unsigned int val)
{
    Ant *a = new Ant;
    a->num = val;
    a->next = top_ant;
    top_ant = a;
}

unsigned int stackAnt::pop()
{
    unsigned int val = top_ant->num;
    Ant *to_delete = top_ant;
    top_ant = top_ant->next;
    delete to_delete;
    return val;
}

bool stackAnt::is_empty()
{
    if (!top_ant)
        return true;
    return false;
}

void Ants::ReadFile(char *file_arg)
{
    // Open the file
    ifstream input_file;
    input_file.open(file_arg);

    // Get the number of ants
    unsigned int num_of_ants;
    input_file >> num_of_ants;

    // Create the ant queue
    for (unsigned int i = 1; i <= num_of_ants; i++)
    {
        ants.enqueue(i);
    }

    // Get the number of holes and their depth and create the hole queue
    unsigned int depth;
    while (input_file >> depth)
    {
        holeDepths.enqueue(depth);
    }

    // Close the file

    input_file.close();
}

void Ants::ShowContents(bool indicator)
{
    if (indicator)
    {
        ants.print();
    }
    else
    {
        holeDepths.print();
    }
}

void Ants::CrossRoad()
{
    // If there are holes ant queue will continue to follow the road
    while (!holeDepths.is_empty())
    {
        // Set the size of hole stack
        hole.limit = holeDepths.dequeue();

        // Dequeue the ants and push it to hole stack
        for (unsigned int i = 0; i < hole.limit; i++)
        {
            hole.push(ants.dequeue());
        }

        // Enqueue the contents of hole stack
        while (!hole.is_empty())
        {
            ants.enqueue(hole.pop());
        }
    }
}

// Program

int main(int argc, char **argv)
{
    Ants a;
    a.ReadFile(argv[1]); // store the number of ants and depths of holes
    cout << "The initial Ant sequence is: ";
    a.ShowContents(1); // list ant sequence ( initially : 1 , 2 , ... , N )
    cout << "The depth of holes are: ";
    a.ShowContents(0); // list depth of holes
    a.CrossRoad();
    cout << "The final Ant sequence is: ";
    a.ShowContents(1);

    return 0;
}