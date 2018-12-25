#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Card
{
    long int value;
    Card *previous;
};

struct Deck
{
    Card *top;
    unsigned short card_count;
    void create();
    void push(long int card_value);
    long int pop();
    bool is_empty();
    void destroy_cards();
};

void Deck::create()
{
    top = NULL;
    card_count = 0;
}

void Deck::push(long int card_value)
{
    Card *to_add = new Card;
    to_add->value = card_value;
    to_add->previous = top;
    top = to_add;
    card_count++;
}

long int Deck::pop()
{
    Card *temp = top;
    top = top->previous;
    long int val = temp->value;
    delete temp;
    card_count--;
    return val;
}

bool Deck::is_empty()
{
    if (top)
        return false;
    return true;
}

void Deck::destroy_cards()
{
    while (top)
    {
        pop();
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Invalid commandline argument." << endl;
        exit(1);
    }

    string filename = argv[1];
    // Opening file stream
    fstream info_file(filename);

    if (!info_file.is_open())
    {
        cerr << "File cannot be opened." << endl;
        exit(1);
    }
    else
    {
        string line;
        getline(info_file, line);

        // Values in the first line will get copied to these C-Type strings
        char nTableDeck_str[5], nPlayerDeck_str[5];

        if (line[0] == '-')
        {
            cerr << "Deck size must be between 0-1000." << endl;
            exit(1);
        }

        for (int i = 0; line[i] != '\0'; i++)
        {
            // Copy the characters before the space to table deck, rest to player decks
            if (isspace(line[i]))
            {
                strncpy(nTableDeck_str, line.c_str(), i);
                nTableDeck_str[i] = '\0';
                if (i > 4 || line[i + 1] == '-' || (line.length() - i) > 4)
                {
                    cerr << "Deck size must be between 0-1000." << endl;
                    exit(1);
                }
                strncpy(nPlayerDeck_str, &((line.c_str())[i + 1]), line.length() - i + 1);
                nPlayerDeck_str[line.length() - i] = '\0';
                break;
            }
        }

        // Turn those strings to integers
        unsigned short nTableDeck = atoi(nTableDeck_str), nPlayerDeck = atoi(nPlayerDeck_str);

        // Check the constraints again
        if (nTableDeck > 1000 || nPlayerDeck > 1000)
        {
            cerr << "Deck size must be between 0-1000." << endl;
            exit(1);
        }

        // Create the deck stacks
        Deck table, p1, p2, bin;
        table.create();
        p1.create();
        p2.create();
        bin.create();

        // Fill the decks
        for (int i = 0; i < nTableDeck; i++)
        {
            if (getline(info_file, line))
            {
                long int val = strtol(line.c_str(), NULL, 10); // STRingTOLong
                if (val > 1000000 || val < -1000000 || val == 0)
                {
                    cerr << "Card values must be between -1000000 to 1000000. (Except 0)" << endl;
                    exit(1);
                }
                else
                {
                    table.push(val);
                }
            }
            else
            {
                cerr << "Unsufficient information on the input file." << endl;
                exit(1);
            }
        }

        for (int i = nTableDeck; i < nTableDeck + nPlayerDeck; i++)
        {
            if (getline(info_file, line))
            {
                long int val = strtol(line.c_str(), NULL, 10); // STRingTOLong
                if (val > 1000000 || val < -1000000 || val == 0)
                {
                    cerr << "Card values must be between -1000000 to 1000000. (Except 0)" << endl;
                    exit(1);
                }
                else
                {
                    p1.push(val);
                }
            }
            else
            {
                cerr << "Unsufficient information on the input file." << endl;
                exit(1);
            }
        }

        for (int i = nTableDeck + nPlayerDeck; i < nTableDeck + nPlayerDeck + nPlayerDeck; i++)
        {
            if (getline(info_file, line))
            {
                long int val = strtol(line.c_str(), NULL, 10); // STRingTOLong
                if (val > 1000000 || val < -1000000 || val == 0)
                {
                    cerr << "Card values must be between -1000000 to 1000000. (Except 0)" << endl;
                    exit(1);
                }
                else
                {
                    p2.push(val);
                }
            }
            else
            {
                cerr << "Unsufficient information on the input file." << endl;
                exit(1);
            }
        }

        // Game begins
        int turn = 0;
        while (true)
        {
            // Game ends if one of the decks is empty
            if (p1.is_empty() || p2.is_empty() || table.is_empty())
            {
                break;
            }

            long int table_top_card = table.pop();

            if (turn % 2 == 0)
            {
                // Player 1's turn
                if (table_top_card > 0)
                {
                    // Player 1 takes cards
                    for (int i = 0; i < table_top_card && !p2.is_empty(); i++)
                    {
                        long int p1_card = p1.pop();
                        long int p2_card = p2.pop();
                        if (p1_card < p2_card)
                        {
                            p1.push(p1_card);
                            p1.push(p2_card);
                        }
                        else
                        {
                            p1.push(p1_card);
                            bin.push(p2_card);
                        }
                    }
                }
                else
                {
                    // Player 2 takes cards
                    table_top_card = labs(table_top_card);
                    for (int i = 0; i < table_top_card && !p1.is_empty(); i++)
                    {
                        long int p1_card = p1.pop();
                        long int p2_card = p2.pop();
                        if (p2_card < p1_card)
                        {
                            p2.push(p2_card);
                            p2.push(p1_card);
                        }
                        else
                        {
                            p2.push(p2_card);
                            bin.push(p1_card);
                        }
                    }
                }
            }
            else
            {
                // Player 2's turn
                if (table_top_card > 0)
                {
                    // Player 2 takes cards
                    for (int i = 0; i < table_top_card && !p1.is_empty(); i++)
                    {
                        long int p1_card = p1.pop();
                        long int p2_card = p2.pop();
                        if (p2_card < p1_card)
                        {
                            p2.push(p2_card);
                            p2.push(p1_card);
                        }
                        else
                        {
                            p2.push(p2_card);
                            bin.push(p1_card);
                        }
                    }
                }
                else
                {
                    // Player 1 takes cards
                    table_top_card = labs(table_top_card);
                    for (int i = 0; i < table_top_card && !p2.is_empty(); i++)
                    {
                        long int p1_card = p1.pop();
                        long int p2_card = p2.pop();
                        if (p1_card < p2_card)
                        {
                            p1.push(p1_card);
                            p1.push(p2_card);
                        }
                        else
                        {
                            p1.push(p1_card);
                            bin.push(p2_card);
                        }
                    }
                }
            }

            turn++;
        }

        cout << bin.card_count;

        // Clean up
        info_file.close();
        bin.destroy_cards();
        table.destroy_cards();
        p1.destroy_cards();
        p2.destroy_cards();
    }
    return 0;
}