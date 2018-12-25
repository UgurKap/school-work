/* @Uğur Ali Kaplan
* Student Name: Uğur Ali Kaplan
* Student ID : 150170042
* Date: 08.11.2018 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

struct occur_node
{
    char character;
    occur_node *next;
    int occurence;
};

struct vocab_node
{
    char character;
    vocab_node *next;
    occur_node *list;
};

struct vocab_list
{
    vocab_node *head;
    void create();                       // DONE Creates vocab_list
    void print();                        // DONE Prints entire language model
    void add_char(char);                 // DONE Reads unique characters from input, adds them to vocab_list in alphabetical order
    void add_occurence(char, char);      // DONE When sees "ar", searches for "a" in vocab_list and adds "r" to it(either new node or oc+1)
    int get_occurence(char);             // DONE Returns the total occurence count of a given character
    int get_union_occurence(char, char); // DONE Gives total co-occurence of two characters
};

struct language_model
{
    vocab_list vocabularyList;
    void readData(const char *);             /* DONE Reads input file, calls create(), add_char() and add_occurence()
    and fills entire language model */
    double calculateProbability(char, char); // DONE Returns calculated probability of two chars
};

void vocab_list::create()
{
    head = NULL;
}

void vocab_list::add_char(char c)
{
    c = tolower(c);
    if (c == 'I')
    {
        c = 'i';
    }
    if (c == '\n' || c == EOF || c == '\r')
    {
        return;
    }
    if (ispunct(c) || c == ' ')
    {
        vocab_node *tr = head;
        while (tr)
        {
            if (tr->character == c)
            {
                break;
            }
            if (tr->next == NULL)
            {
                tr->next = new vocab_node;
                tr->next->next = NULL;
                tr->next->character = c;
                tr->next->list = NULL;
            }
            tr = tr->next;
        }
        return;
    }

    vocab_node *current = head;
    bool found = false;
    while (current != NULL)
    {

        if (current->character == c)
        {
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found)
    {
        vocab_node *traverser = head;
        vocab_node *previous = head;
        while (traverser)
        {
            if (c > (traverser->character))
            {
                previous = traverser;
            }
            else
            {
                previous->next = new vocab_node;
                previous->next->list = NULL;
                previous->next->next = traverser;
                previous->next->character = c;
                break;
            }
            traverser = traverser->next;
        }
        if (traverser == NULL)
        {
            previous->next = new vocab_node;
            previous->next->list = NULL;
            previous->next->character = c;
            previous->next->next = NULL;
        }
    }
}

void vocab_list::add_occurence(char first, char second)
{
    vocab_node *traverser = head;
    first = tolower(first);
    second = tolower(second);
    if (first == 'I')
    {
        first = 'i';
    }
    if (second == 'I')
    {
        second = 'i';
    }

    if (first == '\n' || first == EOF || first == '\r')
    {
        return;
    }
    if (second == EOF || second == '\n')
    {
        return;
    }

    if(second == '\r'){
        second = ' ';
    }

    while (traverser)
    {
        bool found = false;
        if (traverser->character == first)
        {
            occur_node *current = traverser->list;
            if (current == NULL)
            {
                traverser->list = new occur_node;
                traverser->list->character = second;
                traverser->list->next = NULL;
                traverser->list->occurence = 1;
                break;
            }

            while (current)
            {
                if (current->character == second)
                {
                    current->occurence += 1;
                    found = true;
                    break;
                }
                current = current->next;
            }
            if (found)
            {
                break;
            }

            current = traverser->list;

            while (current)
            {
                if (current->next == NULL)
                {
                    current->next = new occur_node;
                    current->next->character = second;
                    current->next->next = NULL;
                    current->next->occurence = 1;
                    break;
                }
                current = current->next;
            }
        }
        traverser = traverser->next;
    }
}

void vocab_list::print()
{
    vocab_node *traverser = head;
    while (traverser)
    {
        occur_node *oc_traverser = traverser->list;
        cout << traverser->character << ":" << endl;
        while (oc_traverser)
        {
            cout << "\t<" << oc_traverser->character << ", " << oc_traverser->occurence << ">" << endl;
            oc_traverser = oc_traverser->next;
        }
        traverser = traverser->next;
    }
}

int vocab_list::get_union_occurence(char first, char second)
{
    vocab_node *traverser = head;
    int to_return = 0;
    while (traverser)
    {
        if (traverser->character == first)
        {
            occur_node *oc_traverser = traverser->list;
            while (oc_traverser)
            {
                if (oc_traverser->character == second)
                {
                    to_return = oc_traverser->occurence;
                    break;
                }
                oc_traverser = oc_traverser->next;
            }
            break;
        }
        traverser = traverser->next;
    }
    return to_return;
}

int vocab_list::get_occurence(char ch)
{
    int total_occurence = 0;
    vocab_node *traverser = head;
    while (traverser)
    {
        if (traverser->character == ch)
        {
            occur_node *oc_traverser = traverser->list;
            while (oc_traverser)
            {
                total_occurence += oc_traverser->occurence;
                oc_traverser = oc_traverser->next;
            }
            break;
        }
        traverser = traverser->next;
    }
    return total_occurence;
}

void language_model::readData(const char *filename)
{
    ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        cerr << "Unable to open the input file." << endl;
        exit(1);
    }

    vocabularyList.create(); // create
    vocabularyList.head = new vocab_node;
    vocabularyList.head->next = NULL;
    vocabularyList.head->list = NULL;

    // Set the first character in the list according to alphabet
    char c;
    char lowest = 'z';
    lowest++;
    while (inFile.get(c))
    {
        c = tolower(c);
        if (c < lowest)
        {
            lowest = c;
            if (lowest == 'a')
            {
                break;
            }
        }
    }

    vocabularyList.head->character = lowest;

    // Go to the beginning of the input file
    inFile.clear();
    inFile.seekg(0);

    // Iterating through the input file, add each unique character to the list considering the alphabetical order as well
    while (inFile.get(c))
    {
        if(!ispunct(c) && c != ' ')
            vocabularyList.add_char(c); // adding characters
    }

    // come for special chars later
    inFile.clear();
    inFile.seekg(0);

    while (inFile.get(c))
    {
        if(ispunct(c) || c == ' ')
            vocabularyList.add_char(c); // adding characters
    }


    vocab_node *traverser = vocabularyList.head;

    while (traverser)
    {
        // Go to the beginning of the input file
        inFile.clear();
        inFile.seekg(0);
        char a;
        while (inFile.get(a))
        {
            a = tolower(a);
            if (a == 'I')
            {
                a = 'i';
            }
            if (a == (traverser->character))
            {
                char b;
                inFile.get(b);
                b = tolower(b);
                if (b == 'I')
                {
                    b = 'i';
                }
                vocabularyList.add_occurence(a, b);
                inFile.seekg(-1, inFile.cur);
            }
            else
            {
                continue;
            }
        }
        traverser = traverser->next;
    }
}

double language_model::calculateProbability(char first, char second)
{
    double top = vocabularyList.get_union_occurence(first, second);
    double below = vocabularyList.get_occurence(first);
    double calculation = top / below;
    return calculation;
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");

    language_model model;
    const char *fn = argv[1];
    model.readData(fn);

    if (argc > 2)
    {
        char f = argv[2][0];
        char s = argv[3][0];
        cout << model.calculateProbability(f, s) << endl;
    }
    else
    {
        model.vocabularyList.print();
    }

    return 0;
}