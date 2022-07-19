#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Aibot
{
public:
    Aibot();                                                                  // standard contstructor
    int bid();                                                                // return max starting bid
    void cardClear(vector<pair<string, int>> &deck);                          // clear hand from deck
    void cardClear(vector<pair<string, int>> &deck, pair<string, int> card);  // clear card from deck
    int highest();                                                            // return highest card from held hands
    bool hasHighest(vector<pair<string, int>> deck, pair<string, int> &card); // return if held hand has a highest card
    bool bestCard(vector<pair<string, int>> deck, pair<string, int> card);    // return if card is highest of deck
    int lowest();                                                             // return lowest card from held hand
    bool inputHand(string input);                                             // input held hand
    void print();                                                             // print held hand
    void marriage();                                                          // calculate marriages
    void clearmarriage();                                                     // clear marriages
    void discardCards();                                                      // cards to discard after prikup

    vector<pair<string, int>> ai_deck;       // held deck
    vector<pair<string, int>> marriage_deck; // deck of marriages held
    vector<pair<string, int>> won_deck;      // deck of won hands
    int marriages;                           // amount of marriages held
    int score;                               // keeping total score
};

Aibot::Aibot()
{
    marriages = 0;
    score = 0;
    marriage_deck.push_back(pair<string, int>("H", 0));
    marriage_deck.push_back(pair<string, int>("D", 0));
    marriage_deck.push_back(pair<string, int>("C", 0));
    marriage_deck.push_back(pair<string, int>("S", 0));
}

int Aibot::bid()
{
    for (size_t i = 0; i < marriage_deck.size(); i++)
    {
        if (marriage_deck[i].second == 2)
            return (30 + (100 - i * 20));
    }
    return 30; // average score based on experiments
}

void Aibot::print()
{
    cout << "------------------\n";
    for (auto x : ai_deck)
        cout << x.first << ", " << x.second << endl;
    cout << "++++++++++++++++++\n";
    for (auto y : marriage_deck)
        cout << y.first << ", " << y.second << endl;
    cout << "------------------\n";
}

void Aibot::cardClear(vector<pair<string, int>> &deck) // clear hand from deck
{
    for (size_t i = 0; i < ai_deck.size(); i++)
    {
        for (auto j = deck.begin(); j != deck.end(); j++)
        {
            if (j->first == ai_deck[i].first && j->second == ai_deck[i].second)
            {
                deck.erase(j);
                j--;
                break;
            }
        }
    }
}

void Aibot::cardClear(vector<pair<string, int>> &deck, pair<string, int> card) // clear card from deck
{
    for (auto j = deck.begin(); j != deck.end(); j++)
    {
        if (j->first == card.first && j->second == card.second)
        {
            deck.erase(j);
            break;
        }
    }
}

int Aibot::highest()
{
    int index = 0, highest = 0;
    for (size_t i = 0; i < ai_deck.size(); i++)
    {
        if (ai_deck[i].second > highest)
        {
            highest = ai_deck[i].second;
            index = i;
        }
    }
    return index;
}

bool Aibot::hasHighest(vector<pair<string, int>> deck, pair<string, int> &card)
{
    bool isHighest = false;
    for (size_t i = 0; i < ai_deck.size(); i++)
    {
        isHighest = true;
        for (size_t j = 0; j < deck.size(); j++)
        {
            if (deck[j].first == ai_deck[i].first && deck[j].second > ai_deck[i].second)
            {
                isHighest = false;
                break;
            }
        }
        if (isHighest)
        {
            card = ai_deck[i];
            return true;
        }
    }
    return false;
}

bool Aibot::bestCard(vector<pair<string, int>> deck, pair<string, int> card)
{
    for (size_t i = 0; i < deck.size(); i++)
    {
        if (deck[i].first == card.first && deck[i].second > card.second)
            return false;
    }
    return true;
}

int Aibot::lowest()
{
    int index = 0, lowest = 12;
    for (size_t i = 0; i < ai_deck.size(); i++)
    {
        if (ai_deck[i].second < lowest)
        {
            lowest = ai_deck[i].second;
            index = i;
        }
    }
    return index;
}

bool Aibot::inputHand(string input)
{
    string suit;
    suit = input[0];
    switch (input[1])
    {
    case '9':
        // cout << "Negen\n";
        ai_deck.push_back(pair<string, int>(suit, 0));
        break;
    case 'b':
        // cout << "Boer\n";
        ai_deck.push_back(pair<string, int>(suit, 2));
        break;
    case 'v':
        // cout << "Vrouw\n";
        ai_deck.push_back(pair<string, int>(suit, 3));
        break;
    case 'h':
        // cout << "Heer\n";
        ai_deck.push_back(pair<string, int>(suit, 4));
        break;
    case '1':
        // cout << "Tien\n";
        ai_deck.push_back(pair<string, int>(suit, 10));
        break;
    case 'a':
        // cout << "Aas\n";
        ai_deck.push_back(pair<string, int>(suit, 11));
        break;
    default:
        cout << "Invalid input\n";
        return false;
    }
    return true;
}

void Aibot::marriage()
{
    for (auto x : ai_deck)
    {
        switch (x.first[0])
        {
        case 'H':
            if (x.second == 3 || x.second == 4)
                marriage_deck[0].second += 1;
            break;
        case 'D':
            if (x.second == 3 || x.second == 4)
                marriage_deck[1].second += 1;
            break;
        case 'C':
            if (x.second == 3 || x.second == 4)
                marriage_deck[2].second += 1;
            break;
        case 'S':
            if (x.second == 3 || x.second == 4)
                marriage_deck[3].second += 1;
            break;
        }
    }
    for (auto y : marriage_deck)
    {
        if (y.second == 2)
        {
            marriages++;
        }
    }
}

void Aibot::clearmarriage()
{
    for (size_t i = 0; i < marriage_deck.size(); i++)
        marriage_deck[i].second = 0;
}

void Aibot::discardCards()
{
    clearmarriage();
    marriage();
    vector<pair<string, int>> temp_marriages;
    for (auto x : marriage_deck) // don't throw away marriages
    {
        if (x.second == 2)
        {
            temp_marriages.push_back(pair<string, int>(x.first, 3));
            temp_marriages.push_back(pair<string, int>(x.first, 4));
            for (size_t i = 0; i < ai_deck.size(); i++)
            {
                if (x.first == ai_deck[i].first && (ai_deck[i].second == 3 || ai_deck[i].second == 4))
                {
                    ai_deck.erase(ai_deck.begin() + i);
                    i--;
                }
            }
        }
    }
    cout << "Cards to discard to other two players are: \n"
         << ai_deck[lowest()].first << ", " << ai_deck[lowest()].second << endl;
    ai_deck.erase(ai_deck.begin() + lowest());
    cout << "and: \n"
         << ai_deck[lowest()].first << ", " << ai_deck[lowest()].second << endl;
    ai_deck.erase(ai_deck.begin() + lowest());

    for (auto y : temp_marriages)
        ai_deck.push_back(y);
}

bool manualInput(vector<pair<string, int>> &deck, string input) // manually fill a deck
{
    string suit;
    suit = input[0];
    if (suit != "D" && suit != "S" && suit != "H" && suit != "C")
        return false;
    switch (input[1])
    {
    case '9':
        // cout << "Negen\n";
        deck.push_back(pair<string, int>(suit, 0));
        break;
    case 'b':
        // cout << "Boer\n";
        deck.push_back(pair<string, int>(suit, 2));
        break;
    case 'v':
        // cout << "Vrouw\n";
        deck.push_back(pair<string, int>(suit, 3));
        break;
    case 'h':
        // cout << "Heer\n";
        deck.push_back(pair<string, int>(suit, 4));
        break;
    case '1':
        // cout << "Tien\n";
        deck.push_back(pair<string, int>(suit, 10));
        break;
    case 'a':
        // cout << "Aas\n";
        deck.push_back(pair<string, int>(suit, 11));
        break;
    default:
        cout << "Invalid input\n";
        return false;
    }
    return true;
}

int main()
{
    vector<pair<string, int>> deck;
    Aibot aibot;

    deck.push_back(pair<string, int>("D", 0));
    deck.push_back(pair<string, int>("D", 2));
    deck.push_back(pair<string, int>("D", 3));
    deck.push_back(pair<string, int>("D", 4));
    deck.push_back(pair<string, int>("D", 10));
    deck.push_back(pair<string, int>("D", 11));
    deck.push_back(pair<string, int>("S", 0));
    deck.push_back(pair<string, int>("S", 2));
    deck.push_back(pair<string, int>("S", 3));
    deck.push_back(pair<string, int>("S", 4));
    deck.push_back(pair<string, int>("S", 10));
    deck.push_back(pair<string, int>("S", 11));
    deck.push_back(pair<string, int>("H", 0));
    deck.push_back(pair<string, int>("H", 2));
    deck.push_back(pair<string, int>("H", 3));
    deck.push_back(pair<string, int>("H", 4));
    deck.push_back(pair<string, int>("H", 10));
    deck.push_back(pair<string, int>("H", 11));
    deck.push_back(pair<string, int>("C", 0));
    deck.push_back(pair<string, int>("C", 2));
    deck.push_back(pair<string, int>("C", 3));
    deck.push_back(pair<string, int>("C", 4));
    deck.push_back(pair<string, int>("C", 10));
    deck.push_back(pair<string, int>("C", 11));

    cout << "Input options: (D,S,H,C)(9,b,v,h,10,a)\n";
    string input;
    for (int i = 0; i < 7; i++)
    {
        cout << "Input held hand card " << i + 1 << ": ";
        cin >> input;
        if (!aibot.inputHand(input))
            i--;
    }

    aibot.clearmarriage();
    aibot.marriage();
    aibot.print();

    cout << "Current score of bot: ";
    cin >> aibot.score;

    if (aibot.score >= 900 && aibot.bid() == 90)
        cout << "Max bid for ai: 100\n";
    else
        cout << "Max bid for ai: " << aibot.bid() << ", (bid in increments of 10)" << endl;

    bool complete = false;
    vector<pair<string, int>> prikup;
    pair<string, int> tempCard;

    while (!complete)
    {
        cout << "Is the ai the highest bidder (y/n)?\n";
        cin >> input;
        switch (input[0])
        {
        case 'y':
            for (int i = 0; i < 3; i++)
            {
                cout << "Input card " << i + 1 << " of the prikup: ";
                cin >> input;
                if (!manualInput(prikup, input))
                    i--;
            }
            for (auto x : prikup)
                aibot.ai_deck.push_back(x);
            aibot.discardCards();
            complete = true;
            break;
        case 'n':
            cout << "Input gotten card: ";
            cin >> input;
            if (!aibot.inputHand(input))
                complete = false;
            else
                complete = true;
            break;
        default:
            cout << "Invalid input\n";
            break;
        }
    }

    aibot.clearmarriage();
    aibot.marriage();
    aibot.print();
    aibot.cardClear(deck);

    // for (auto x : deck)
    //{
    //     cout << x.first << ", " << x.second << endl;
    //}

    pair<string, int> card;
    bool finished = false, won = false;
    while (!finished)
    {
        won = false;
        prikup.clear();
        cout << "Bot in turn (y/n): ";
        cin >> input;
        switch (input[0])
        {
        case 'y':
            card = aibot.ai_deck[aibot.highest()];
            if (aibot.bestCard(deck, card))
            {
                cout << "Card to choose: " << card.first << card.second;
                for (size_t i = 0; i < aibot.marriage_deck.size(); i++)
                {
                    if (aibot.marriage_deck[i].first == card.first && aibot.marriage_deck[i].second == 2 && (card.second == 3 || card.second == 4))
                    {
                        cout << ", and announce marriage of: " << card.first;
                        aibot.marriage_deck[i].second -= 1;
                        break;
                    }
                }
                cout << endl;
            }
            else if (aibot.hasHighest(deck, card))
            {
                cout << "Card to choose: " << card.first << card.second;
                for (size_t i = 0; i < aibot.marriage_deck.size(); i++)
                {
                    if (aibot.marriage_deck[i].first == card.first && aibot.marriage_deck[i].second == 2 && (card.second == 3 || card.second == 4))
                    {
                        cout << ", and announce marriage of: " << card.first;
                        aibot.marriage_deck[i].second -= 1;
                        break;
                    }
                }
                cout << endl;
            }
            else if (aibot.marriages != 0)
            {
                for (size_t i = 0; i < aibot.marriage_deck.size(); i++)
                {
                    if (aibot.marriage_deck[i].second == 2)
                    {
                        card.first = aibot.marriage_deck[i].first;
                        card.second = 3;
                        cout << "Card to choose: " << card.first << card.second
                             << ", and announce marriage of: " << card.first << endl;
                        aibot.marriage_deck[i].second -= 1;
                        break;
                    }
                }
            }
            else
            {
                card = aibot.ai_deck[aibot.lowest()];
                cout << "Card to choose: " << card.first << card.second << endl;
            }
            break;
        case 'n':
            cout << "Input suit (H,D,C,S): ";
            cin >> input;
            card.second = 12;
            for (size_t i = 0; i < aibot.ai_deck.size(); i++)
            {
                if (aibot.ai_deck[i].first == input)
                {
                    if (aibot.bestCard(deck, aibot.ai_deck[i]))
                    {
                        card = aibot.ai_deck[i];
                        break;
                    }
                    if (aibot.ai_deck[i].second < card.second)
                        card = aibot.ai_deck[i];
                }
            }
            if (card.second == 12)
                card = aibot.ai_deck[aibot.lowest()];
            cout << "Card to choose: " << card.first << card.second << endl;
            break;
        default:
            cout << "Invalid input\n";
            continue;
        }
        aibot.cardClear(deck, card);
        aibot.cardClear(aibot.ai_deck, card);
        aibot.clearmarriage();
        aibot.marriage();
        for (int i = 0; i < 3; i++)
        {
            cout << "(" << card.first << card.second << ") Input card " << i + 1 << " of the round: ";
            cin >> input;
            if (!manualInput(prikup, input))
                i--;
        }
        cout << "Did the ai win with " << card.first << "," << card.second << " ;(y/n): ";
        cin >> input;
        if (input == "y")
            won = true;
        for (auto x : prikup)
        {
            if (won)
                aibot.won_deck.push_back(x);
            aibot.cardClear(deck, x);
        }
        if (aibot.ai_deck.size() <= 0)
            finished = true;
    }
    for (auto x : aibot.won_deck)
    {
        cout << x.first << ", " << x.second << endl;
    }
    return 0;
}