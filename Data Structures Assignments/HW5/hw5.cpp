/*
** @Author
** Student Name: Uğur Ali Kaplan
** Student ID: 150170042
** Date: 20.12.2018
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct node
{
    unsigned int data;
    node *left;
    node *right;

    node()
    {
        left = NULL;
        right = NULL;
        data = 0;
    }
};

struct st_node
{
    unsigned int data;
    st_node *previous;
};

// Will hold the contents of the path
struct sumStack
{
    st_node *top;
    sumStack() { top = NULL; }
    void push(unsigned int data);
    unsigned int pop();
    bool is_empty();
    void clear();
};

struct BT
{
    node *root;
    ifstream input_file;
    unsigned int *input_arr;
    unsigned int input_count;
    unsigned int sum;
    sumStack *sum_st;
    bool found;
    BT()
    {
        root = NULL;
        input_arr = NULL;
        sum = 0;
        sum_st = new sumStack;
        found = false;
    }
    void read_file(char *filename);           // reads the file
    void arr_clean();                         // release the memory allocated for input array
    node *new_node(unsigned int data);        // creates new nodes for the tree
    node *fill_tree(node *r, unsigned int i); // fills the tree according to given specifications
    void find_sum(node *r, unsigned int s);   // finds different paths
    void print_sum_stack();                   // prints out the sum stack in reverse order
};

void sumStack::push(unsigned int data)
{
    if (!top)
    {
        top = new st_node;
        top->previous = NULL;
        top->data = data;
        return;
    }

    st_node *n = new st_node;
    n->previous = top;
    n->data = data;
    top = n;
}

unsigned int sumStack::pop()
{
    st_node *to_delete = top;
    unsigned int to_return = to_delete->data;
    top = top->previous;
    delete to_delete;
    return to_return;
}

bool sumStack::is_empty()
{
    if (top == NULL)
    {
        return true;
    }
    return false;
}

void sumStack::clear()
{
    while (!is_empty())
    {
        pop();
    }
}

void BT::read_file(char *filename)
{
    input_file.open(filename);

    // Create an array of input elements and wanted sum
    // input_arr[input_count] is the wanted sum for the second part of the program
    int *a = new int;
    input_count = 0;
    while (input_file >> *a)
    {
        input_count++;
    }
    delete a;

    input_arr = new unsigned int[input_count];
    input_file.clear();
    input_file.seekg(0);

    for (int i = 0; input_file >> input_arr[i]; i++)
    {
        // Here for debug purposes can be uncommented to see the contents of the array
        // cout << input_arr[i] << endl;
    }

    input_file.close();
}

void BT::arr_clean()
{
    if (input_arr)
    {
        delete[] input_arr;
        input_arr = NULL;
    }
}

node *BT::new_node(unsigned int data)
{
    node *nnode = new node;
    nnode->data = data;
    return nnode;
}

node *BT::fill_tree(node *r, unsigned int i)
{
    if (i < input_count)
    {
        node *t = new_node(input_arr[i - 1]);
        r = t;
        r->left = fill_tree(r->left, 2 * i);

        r->right = fill_tree(r->right, (2 * i) + 1);
    }
    return r;
}

void BT::print_sum_stack()
{
    cout << root->data;
    if (!sum_st->is_empty())
    {
        cout << " ";
    }
    else
    {
        cout << endl;
    }
    sumStack *reverse_st = new sumStack;
    int i = 0;
    while (!(sum_st->is_empty()))
    {
        i++;
        reverse_st->push(sum_st->pop());
    }

    while (i > 0)
    {
        cout << reverse_st->pop();
        i--;
        if (i == 0)
        {
            cout << endl;
        }
        else
        {
            cout << " ";
        }
    }
    delete reverse_st;
}

void BT::find_sum(node *r, unsigned int s)
{
    // cout << "node: " << r->data << endl;
    if (r == NULL)
    {
        cout << "No path found" << endl;
        return;
    }

    if (s >= r->data)
    {
        s -= r->data;
        sum_st->push(r->data);
        // cout << s << endl;

        if (s == 0)
        {
            found = true;
            cout << "Path Found: ";
            print_sum_stack();
            // cout << "root data: " << root->data << endl;
            return;
        }

        if (r->left && found == false)
        {
            find_sum(r->left, s);
        }
        if (r->right && found == false)
        {
            find_sum(r->right, s);
        }

        if (!sum_st->is_empty())
        {
            sum_st->pop();
        }
    }
}

int main(int argc, char **argv)
{
    // Check the number of provided arguments
    if (argc != 2)
    {
        cerr << "Check your parameters" << endl;
        exit(EXIT_FAILURE);
    }

    // Create the tree
    BT *tree = new BT;
    tree->read_file(argv[1]);

    // Fill the binary tree.
    tree->root = tree->fill_tree(tree->root, 1);

    // Compares the sum and root data, if they are same there are two paths and paths are root data
    if (tree->root->data == tree->input_arr[tree->input_count - 1])
    {
        cout << "Path Found: " << tree->root->data << endl;
        cout << "Path Found: " << tree->root->data << endl;
    }
    else
    {
        // Find and print the paths.
        // First we check if there are subtrees in the left and right node
        // Then we will calculate sum while not going less than 0 for sum(sum is unsigned integer)
        if (tree->root->left)
        {
            if (tree->input_arr[tree->input_count - 1] >= (tree->root->data))
            {
                tree->find_sum(tree->root->left, tree->input_arr[tree->input_count - 1] - (tree->root->data));
            }
        }
        if (!tree->found)
        {
            cout << "No Path Found" << endl;
        }

        tree->found = false;

        if (tree->root->right)
        {
            if (tree->input_arr[tree->input_count - 1] >= (tree->root->data))
            {
                tree->find_sum(tree->root->right, tree->input_arr[tree->input_count - 1] - (tree->root->data));
            }
        }

        if (!tree->found)
        {
            cout << "No Path Found" << endl;
        }

        tree->found = false;
    }

    // Clean up
    tree->arr_clean();
    delete tree;

    return EXIT_SUCCESS;
}