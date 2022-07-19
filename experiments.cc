#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

class Aibot
{
public:
    Aibot();                                                                  // standard contstructor
    int bid();                                                                // return max starting bid
    int score();                                                              // return won score
    void cardClear(vector<pair<string, int>> &deck);                          // clear hand from deck
    void cardClear(vector<pair<string, int>> &deck, pair<string, int> card);  // clear card from deck
    int highest();                                                            // return highest card from held hand
    bool hasHighest(vector<pair<string, int>> deck, pair<string, int> &card); // return if held hand has a highest card
    bool bestCard(vector<pair<string, int>> deck, pair<string, int> card);    // return if card is highest of deck
    int lowest();                                                             // return lowest card from held hand
    bool inputHand(string input);                                             // input held hand
    void print();                                                             // print held hand
    void marriage();                                                          // calculate marriages
    void clearmarriage();                                                     // clear marriages
    void discardCards(vector<pair<string, int>> &temp);                       // cards to discard after prikup
    int RHchoose(string suit);                                                // RandomHighest bot card to choose

    vector<pair<string, int>> ai_deck;       // held deck
    vector<pair<string, int>> marriage_deck; // deck of marriages held
    vector<pair<string, int>> won_deck;      // deck of won hands
    int marriages;                           // amount of marriages held
    int announched;                          // announched marriages score
    bool wonPrev;                            // won previous hand
    int overalscore;                         // overal score, game won if score >= 1000
    int bode;                                // bode score
    bool type;                               // true if random bot, false if highest bot
};

Aibot::Aibot()
{
    marriages = 0;
    marriage_deck.push_back(pair<string, int>("H", 0));
    marriage_deck.push_back(pair<string, int>("D", 0));
    marriage_deck.push_back(pair<string, int>("C", 0));
    marriage_deck.push_back(pair<string, int>("S", 0));
    wonPrev = false;
    announched = 0;
    overalscore = 0;
    bode = 0;
    type = false;
}

int Aibot::score()
{
    int score = 0;
    for (auto x : won_deck)
        score += x.second;
    return score + announched;
}

int Aibot::RHchoose(string suit)
{
    vector<int> temp;
    if (suit == "X")
        return (rand() % ai_deck.size());
    else
    {
        for (size_t i = 0; i < ai_deck.size(); i++)
        {
            if (ai_deck[i].first == suit)
                temp.push_back(i);
        }

        if (temp.size() > 0)
            return (temp[rand() % temp.size()]);
        else
            return (rand() % ai_deck.size());
    }
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
                // cout << "Card found, clearing " << j->first << ", " << j->second << endl;
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
            // cout << "Card found, clearing " << j->first << ", " << j->second << endl;
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

void Aibot::discardCards(vector<pair<string, int>> &temp)
{
    clearmarriage();
    marriage();
    vector<pair<string, int>> temp_marriages;
    for (auto x : marriage_deck)
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
    temp.push_back(ai_deck[lowest()]);
    ai_deck.erase(ai_deck.begin() + lowest());
    temp.push_back(ai_deck[lowest()]);
    ai_deck.erase(ai_deck.begin() + lowest());

    for (auto y : temp_marriages)
        ai_deck.push_back(y);
}

bool manualInput(vector<pair<string, int>> &deck, string input) // manually fill a deck
{
    string suit;
    suit = input[0];
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

int winner(vector<pair<pair<string, int>, int>> hand, string suit, string marriage, int trickleader) // returns winner of a hand
{
    int highest = -1;
    int winner = trickleader;
    for (int i = 0; i < 3; i++)
    {
        if (marriage == "X")
        {
            if (hand[i].first.first == suit && hand[i].first.second > highest)
            {
                highest = hand[i].first.second;
                winner = hand[i].second;
            }
        }
        else
        {
            if (suit != marriage && hand[i].first.first == marriage)
            {
                suit = marriage;
                highest = hand[i].first.second;
                winner = hand[i].second;
            }
            else if (suit == marriage && hand[i].first.first == suit && hand[i].first.second > highest)
            {
                highest = hand[i].first.second;
                winner = hand[i].second;
            }
            else if (suit != marriage && hand[i].first.first == suit && hand[i].first.second > highest)
            {
                highest = hand[i].first.second;
                winner = hand[i].second;
            }
        }
    }

    return winner;
}

int nearestTen(int score) // returns nearest 10, equals to score when not highest bidder
{
    if (score % 10 <= 4)
        return (score - (score % 10));
    return (score + (10 - (score % 10)));
}

int main()
{
    vector<pair<int, int>> graph;
    graph.push_back(pair<int, int>(0, 0));
    graph.push_back(pair<int, int>(1, 0));
    graph.push_back(pair<int, int>(2, 0));

    vector<pair<string, int>> deck;
    vector<pair<string, int>> backup;
    vector<pair<string, int>> tempdeck;
    vector<int> botwins;
    Aibot bots[3];
    srand(time(NULL));

    botwins.push_back(0);
    botwins.push_back(0);
    botwins.push_back(0);

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

    backup = deck;
    int index;

    string input;
    string bottypes;
    string writeOut;
    bool toWrite = false;
    int amount = 1;

    while (true)
    {
        cout << "Input bot choice consisting of (R)andom/(H)ighest or (B)ot vs bot: ";
        cin >> input;
        if (input == "R" || input == "H" || input == "B")
            break;
        cout << "Invalid input\n";
    }

    cout << "Input amount of experiments: ";
    cin >> amount;

    if (input == "B")
    {
        cout << "Input bot types in form 0/1 0/1 0/1 (valid input would be 010).\n"
             << "Random bot = 0, Highest bot = 1\n";
        cin >> bottypes;
    }

    for (int i = 0; i < 3; i++)
        bottypes[i] == '0' ? bots[i].type = true : bots[i].type = false;

    cout << "\nWrite out the duration of the experiments? (y/n): ";
    cin >> writeOut;
    if (writeOut == "y")
        toWrite = true;

    while (amount > 0)
    {
        bool gameDone = false;
        int round = 1;
        int starter;
        bots[0].overalscore = 0;
        bots[1].overalscore = 0;
        bots[2].overalscore = 0;

        while (gameDone == false)
        {
            int aibid = 0;
            for (int i = 0; i < 3; i++)
            {
                bots[i].ai_deck.clear();
                bots[i].won_deck.clear();
                bots[i].marriage_deck.clear();
                bots[i].marriages = 0;
                bots[i].marriage_deck.push_back(pair<string, int>("H", 0));
                bots[i].marriage_deck.push_back(pair<string, int>("D", 0));
                bots[i].marriage_deck.push_back(pair<string, int>("C", 0));
                bots[i].marriage_deck.push_back(pair<string, int>("S", 0));
                bots[i].wonPrev = false;
                bots[i].announched = 0;
                bots[i].bode = 0;
            }
            deck = backup;
            tempdeck = deck;

            for (int i = 0; i < 7; i++) // give cards randomly
            {
                for (int j = 0; j < 3; j++)
                {
                    index = rand() % tempdeck.size();
                    bots[j].ai_deck.push_back(tempdeck[index]);
                    tempdeck.erase(tempdeck.begin() + index);
                }
            }

            vector<pair<string, int>> trick;
            vector<pair<pair<string, int>, int>> toWintrick;
            pair<string, int> toChoose;
            pair<string, int> botcard1;
            pair<string, int> botcard2;
            string currentMarriage = "X";
            int winindex, tempbotindex;

            switch (input[0])
            {
            case 'R':
                bots[0].clearmarriage();
                bots[0].marriage();
                aibid = bots[0].bid();
                if (aibid == 90 && bots[0].overalscore >= 900)
                {
                    bots[0].wonPrev = true;
                    bots[0].bode = 100;
                    bots[1].bode = 0;
                    bots[2].bode = 0;
                    starter = 0;
                }
                else if (aibid >= 100)
                {
                    bots[0].wonPrev = true;
                    bots[0].bode = aibid;
                    bots[1].bode = 0;
                    bots[2].bode = 0;
                    starter = 0;
                }
                else
                {
                    bots[(round - 1) % 3].wonPrev = true;
                    bots[(round - 1) % 3].bode = 100;
                    starter = (round - 1) % 3;
                }
                if (starter == 0)
                {
                    for (auto x : tempdeck) // give prikup to ai
                        bots[0].ai_deck.push_back(x);
                    tempdeck.clear();
                    bots[0].discardCards(tempdeck);
                    bots[1].ai_deck.push_back(tempdeck[0]);
                    bots[2].ai_deck.push_back(tempdeck[1]);
                }
                else
                {
                    for (auto x : tempdeck) // give prikup to starter
                        bots[starter].ai_deck.push_back(x);
                    index = bots[starter].RHchoose("X");
                    bots[(starter + 1) % 3].ai_deck.push_back(bots[starter].ai_deck[index]);
                    bots[starter].ai_deck.erase(bots[starter].ai_deck.begin() + index);
                    index = bots[starter].RHchoose("X");
                    bots[(starter + 2) % 3].ai_deck.push_back(bots[starter].ai_deck[index]);
                    bots[starter].ai_deck.erase(bots[starter].ai_deck.begin() + index);
                }

                bots[0].clearmarriage();
                bots[0].marriage();
                bots[0].cardClear(deck);

                for (int i = 0; i < 8; i++)
                {
                    trick.clear();
                    toWintrick.clear();
                    if (bots[0].wonPrev)
                    {
                        toChoose = bots[0].ai_deck[bots[0].highest()];
                        if (bots[0].bestCard(deck, toChoose))
                        {
                            for (size_t i = 0; i < bots[0].marriage_deck.size(); i++)
                            {
                                if (bots[0].marriage_deck[i].first == toChoose.first && bots[0].marriage_deck[i].second == 2 && (toChoose.second == 3 || toChoose.second == 4))
                                {
                                    currentMarriage = toChoose.first;
                                    bots[0].announched += (100 - i * 20);
                                    // cout << "Marriage of: " << toChoose.first << endl;
                                    bots[0].marriage_deck[i].second -= 1;
                                    break;
                                }
                            }
                        }
                        else if (bots[0].hasHighest(deck, toChoose))
                        {
                            for (size_t i = 0; i < bots[0].marriage_deck.size(); i++)
                            {
                                if (bots[0].marriage_deck[i].first == toChoose.first && bots[0].marriage_deck[i].second == 2 && (toChoose.second == 3 || toChoose.second == 4))
                                {
                                    currentMarriage = toChoose.first;
                                    bots[0].announched += (100 - i * 20);
                                    // cout << "Marriage of: " << toChoose.first << endl;
                                    bots[0].marriage_deck[i].second -= 1;
                                    break;
                                }
                            }
                        }
                        else if (bots[0].marriages != 0)
                        {
                            for (size_t i = 0; i < bots[0].marriage_deck.size(); i++)
                            {
                                if (bots[0].marriage_deck[i].second == 2)
                                {
                                    toChoose.first = bots[0].marriage_deck[i].first;
                                    toChoose.second = 3;
                                    currentMarriage = toChoose.first;
                                    bots[0].announched += (100 - i * 20);
                                    // cout << "Marriage of: " << toChoose.first << endl;
                                    bots[0].marriage_deck[i].second -= 1;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            toChoose = bots[0].ai_deck[bots[0].lowest()];
                        }
                        // cout << "Ai: " << toChoose.first << toChoose.second << endl;
                        trick.push_back(toChoose);
                        bots[0].cardClear(bots[0].ai_deck, toChoose);
                        index = bots[1].RHchoose(toChoose.first);
                        // cout << "Bot 1: " << bots[1].ai_deck[index].first << bots[1].ai_deck[index].second << endl;
                        trick.push_back(bots[1].ai_deck[index]);
                        bots[0].cardClear(deck, bots[1].ai_deck[index]);
                        bots[1].cardClear(bots[1].ai_deck, bots[1].ai_deck[index]);
                        index = bots[2].RHchoose(toChoose.first);
                        // cout << "Bot 2: " << bots[2].ai_deck[index].first << bots[2].ai_deck[index].second << endl;
                        trick.push_back(bots[2].ai_deck[index]);
                        bots[0].cardClear(deck, bots[2].ai_deck[index]);
                        bots[2].cardClear(bots[2].ai_deck, bots[2].ai_deck[index]);
                        toWintrick.push_back(make_pair(make_pair(trick[0].first, trick[0].second), 0));
                        toWintrick.push_back(make_pair(make_pair(trick[1].first, trick[1].second), 1));
                        toWintrick.push_back(make_pair(make_pair(trick[2].first, trick[2].second), 2));
                        winindex = winner(toWintrick, trick[0].first, currentMarriage, 0);
                        // cout << "Winner of trick: " << toWintrick[winindex].first.first << toWintrick[winindex].first.second << ", " << toWintrick[winindex].second << endl;
                    }
                    else if (bots[1].wonPrev)
                    {
                        index = bots[1].RHchoose("X");
                        tempbotindex = bots[2].RHchoose(bots[1].ai_deck[index].first);
                        toChoose.second = 12;
                        for (size_t i = 0; i < bots[0].ai_deck.size(); i++)
                        {
                            if (bots[0].ai_deck[i].first == bots[1].ai_deck[index].first)
                            {
                                if (bots[0].bestCard(deck, bots[0].ai_deck[i]))
                                {
                                    toChoose = bots[0].ai_deck[i];
                                    break;
                                }
                                if (bots[0].ai_deck[i].second < toChoose.second)
                                    toChoose = bots[0].ai_deck[i];
                            }
                        }
                        if (toChoose.second == 12)
                            toChoose = bots[0].ai_deck[bots[0].lowest()];

                        // cout << "Ai: " << toChoose.first << toChoose.second << endl;
                        trick.push_back(toChoose);
                        bots[0].cardClear(bots[0].ai_deck, toChoose);
                        // cout << "Bot 1: " << bots[1].ai_deck[index].first << bots[1].ai_deck[index].second << endl;
                        trick.push_back(bots[1].ai_deck[index]);
                        bots[0].cardClear(deck, bots[1].ai_deck[index]);
                        bots[1].cardClear(bots[1].ai_deck, bots[1].ai_deck[index]);
                        // cout << "Bot 2: " << bots[2].ai_deck[tempbotindex].first << bots[2].ai_deck[tempbotindex].second << endl;
                        trick.push_back(bots[2].ai_deck[tempbotindex]);
                        bots[0].cardClear(deck, bots[2].ai_deck[tempbotindex]);
                        bots[2].cardClear(bots[2].ai_deck, bots[2].ai_deck[tempbotindex]);
                        toWintrick.push_back(make_pair(make_pair(trick[0].first, trick[0].second), 0));
                        toWintrick.push_back(make_pair(make_pair(trick[1].first, trick[1].second), 1));
                        toWintrick.push_back(make_pair(make_pair(trick[2].first, trick[2].second), 2));
                        winindex = winner(toWintrick, trick[1].first, currentMarriage, 1);
                        // cout << "Winner of trick: " << toWintrick[winindex].first.first << toWintrick[winindex].first.second << ", " << toWintrick[winindex].second << endl;
                    }
                    else if (bots[2].wonPrev)
                    {
                        tempbotindex = bots[2].RHchoose("X");
                        index = bots[1].RHchoose(bots[2].ai_deck[tempbotindex].first);
                        toChoose.second = 12;
                        for (size_t i = 0; i < bots[0].ai_deck.size(); i++)
                        {
                            if (bots[0].ai_deck[i].first == bots[2].ai_deck[tempbotindex].first)
                            {
                                if (bots[0].bestCard(deck, bots[0].ai_deck[i]))
                                {
                                    toChoose = bots[0].ai_deck[i];
                                    break;
                                }
                                if (bots[0].ai_deck[i].second < toChoose.second)
                                    toChoose = bots[0].ai_deck[i];
                            }
                        }
                        if (toChoose.second == 12)
                            toChoose = bots[0].ai_deck[bots[0].lowest()];

                        // cout << "Ai: " << toChoose.first << toChoose.second << endl;
                        trick.push_back(toChoose);
                        bots[0].cardClear(bots[0].ai_deck, toChoose);
                        // cout << "Bot 1: " << bots[1].ai_deck[index].first << bots[1].ai_deck[index].second << endl;
                        trick.push_back(bots[1].ai_deck[index]);
                        bots[0].cardClear(deck, bots[1].ai_deck[index]);
                        bots[1].cardClear(bots[1].ai_deck, bots[1].ai_deck[index]);
                        // cout << "Bot 2: " << bots[2].ai_deck[tempbotindex].first << bots[2].ai_deck[tempbotindex].second << endl;
                        trick.push_back(bots[2].ai_deck[tempbotindex]);
                        bots[0].cardClear(deck, bots[2].ai_deck[tempbotindex]);
                        bots[2].cardClear(bots[2].ai_deck, bots[2].ai_deck[tempbotindex]);
                        toWintrick.push_back(make_pair(make_pair(trick[0].first, trick[0].second), 0));
                        toWintrick.push_back(make_pair(make_pair(trick[1].first, trick[1].second), 1));
                        toWintrick.push_back(make_pair(make_pair(trick[2].first, trick[2].second), 2));
                        winindex = winner(toWintrick, trick[2].first, currentMarriage, 2);
                        // cout << "Winner of trick: " << toWintrick[winindex].first.first << toWintrick[winindex].first.second << ", " << toWintrick[winindex].second << endl;
                    }

                    for (int i = 0; i < 3; i++)
                    {
                        bots[i].wonPrev = false;
                        // cout << "Pushing " << trick[i].second << ", to: " << toWintrick[winindex].second << endl;
                        bots[winindex].won_deck.push_back(trick[i]);
                    }
                    bots[winindex].wonPrev = true;
                    bots[0].clearmarriage();
                    bots[0].marriage();
                }
                break;
            case 'H':
                bots[0].clearmarriage();
                bots[0].marriage();
                aibid = bots[0].bid();
                if (aibid == 90 && bots[0].overalscore >= 900)
                {
                    bots[0].wonPrev = true;
                    bots[0].bode = 100;
                    bots[1].bode = 0;
                    bots[2].bode = 0;
                    starter = 0;
                }
                else if (aibid >= 100)
                {
                    bots[0].wonPrev = true;
                    bots[0].bode = aibid;
                    bots[1].bode = 0;
                    bots[2].bode = 0;
                    starter = 0;
                }
                else
                {
                    bots[(round - 1) % 3].wonPrev = true;
                    bots[(round - 1) % 3].bode = 100;
                    starter = (round - 1) % 3;
                }
                if (starter == 0)
                {
                    for (auto x : tempdeck) // give prikup to ai
                        bots[0].ai_deck.push_back(x);
                    tempdeck.clear();
                    bots[0].discardCards(tempdeck);
                    bots[1].ai_deck.push_back(tempdeck[0]);
                    bots[2].ai_deck.push_back(tempdeck[1]);
                }
                else
                {
                    for (auto x : tempdeck) // give prikup to starter
                        bots[starter].ai_deck.push_back(x);
                    index = bots[starter].RHchoose("X");
                    bots[(starter + 1) % 3].ai_deck.push_back(bots[starter].ai_deck[index]);
                    bots[starter].ai_deck.erase(bots[starter].ai_deck.begin() + index);
                    index = bots[starter].RHchoose("X");
                    bots[(starter + 2) % 3].ai_deck.push_back(bots[starter].ai_deck[index]);
                    bots[starter].ai_deck.erase(bots[starter].ai_deck.begin() + index);
                }

                // cout << "Bot to start is: " << starter << endl;

                bots[0].clearmarriage();
                bots[0].marriage();
                bots[0].cardClear(deck);

                for (int i = 0; i < 8; i++)
                {
                    trick.clear();
                    toWintrick.clear();
                    if (bots[0].wonPrev)
                    {
                        toChoose = bots[0].ai_deck[bots[0].highest()];
                        if (bots[0].bestCard(deck, toChoose))
                        {
                            for (size_t i = 0; i < bots[0].marriage_deck.size(); i++)
                            {
                                if (bots[0].marriage_deck[i].first == toChoose.first && bots[0].marriage_deck[i].second == 2 && (toChoose.second == 3 || toChoose.second == 4))
                                {
                                    currentMarriage = toChoose.first;
                                    bots[0].announched += (100 - i * 20);
                                    // cout << "Marriage of: " << toChoose.first << endl;
                                    bots[0].marriage_deck[i].second -= 1;
                                    break;
                                }
                            }
                        }
                        else if (bots[0].hasHighest(deck, toChoose))
                        {
                            for (size_t i = 0; i < bots[0].marriage_deck.size(); i++)
                            {
                                if (bots[0].marriage_deck[i].first == toChoose.first && bots[0].marriage_deck[i].second == 2 && (toChoose.second == 3 || toChoose.second == 4))
                                {
                                    currentMarriage = toChoose.first;
                                    bots[0].announched += (100 - i * 20);
                                    // cout << "Marriage of: " << toChoose.first << endl;
                                    bots[0].marriage_deck[i].second -= 1;
                                    break;
                                }
                            }
                        }
                        else if (bots[0].marriages != 0)
                        {
                            for (size_t i = 0; i < bots[0].marriage_deck.size(); i++)
                            {
                                if (bots[0].marriage_deck[i].second == 2)
                                {
                                    toChoose.first = bots[0].marriage_deck[i].first;
                                    toChoose.second = 3;
                                    currentMarriage = toChoose.first;
                                    bots[0].announched += (100 - i * 20);
                                    // cout << "Marriage of: " << toChoose.first << endl;
                                    bots[0].marriage_deck[i].second -= 1;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            toChoose = bots[0].ai_deck[bots[0].lowest()];
                        }
                        // cout << "Ai: " << toChoose.first << toChoose.second << endl;
                        trick.push_back(toChoose);
                        bots[0].cardClear(bots[0].ai_deck, toChoose);
                        index = bots[1].RHchoose(toChoose.first);
                        // cout << "Bot 1: " << bots[1].ai_deck[index].first << bots[1].ai_deck[index].second << endl;
                        trick.push_back(bots[1].ai_deck[index]);
                        bots[0].cardClear(deck, bots[1].ai_deck[index]);
                        bots[1].cardClear(bots[1].ai_deck, bots[1].ai_deck[index]);
                        index = bots[2].RHchoose(toChoose.first);
                        // cout << "Bot 2: " << bots[2].ai_deck[index].first << bots[2].ai_deck[index].second << endl;
                        trick.push_back(bots[2].ai_deck[index]);
                        bots[0].cardClear(deck, bots[2].ai_deck[index]);
                        bots[2].cardClear(bots[2].ai_deck, bots[2].ai_deck[index]);
                        toWintrick.push_back(make_pair(make_pair(trick[0].first, trick[0].second), 0));
                        toWintrick.push_back(make_pair(make_pair(trick[1].first, trick[1].second), 1));
                        toWintrick.push_back(make_pair(make_pair(trick[2].first, trick[2].second), 2));
                        winindex = winner(toWintrick, trick[0].first, currentMarriage, 0);
                        // cout << "Winner of trick: " << toWintrick[winindex].first.first << toWintrick[winindex].first.second << ", " << toWintrick[winindex].second << endl;
                    }
                    else if (bots[1].wonPrev)
                    {
                        index = bots[1].highest();
                        tempbotindex = bots[2].RHchoose(bots[1].ai_deck[index].first);
                        toChoose.second = 12;
                        for (size_t i = 0; i < bots[0].ai_deck.size(); i++)
                        {
                            if (bots[0].ai_deck[i].first == bots[1].ai_deck[index].first)
                            {
                                if (bots[0].bestCard(deck, bots[0].ai_deck[i]))
                                {
                                    toChoose = bots[0].ai_deck[i];
                                    break;
                                }
                                if (bots[0].ai_deck[i].second < toChoose.second)
                                    toChoose = bots[0].ai_deck[i];
                            }
                        }
                        if (toChoose.second == 12)
                            toChoose = bots[0].ai_deck[bots[0].lowest()];

                        // cout << "Ai: " << toChoose.first << toChoose.second << endl;
                        trick.push_back(toChoose);
                        bots[0].cardClear(bots[0].ai_deck, toChoose);
                        // cout << "Bot 1: " << bots[1].ai_deck[index].first << bots[1].ai_deck[index].second << endl;
                        trick.push_back(bots[1].ai_deck[index]);
                        bots[0].cardClear(deck, bots[1].ai_deck[index]);
                        bots[1].cardClear(bots[1].ai_deck, bots[1].ai_deck[index]);
                        // cout << "Bot 2: " << bots[2].ai_deck[tempbotindex].first << bots[2].ai_deck[tempbotindex].second << endl;
                        trick.push_back(bots[2].ai_deck[tempbotindex]);
                        bots[0].cardClear(deck, bots[2].ai_deck[tempbotindex]);
                        bots[2].cardClear(bots[2].ai_deck, bots[2].ai_deck[tempbotindex]);
                        toWintrick.push_back(make_pair(make_pair(trick[0].first, trick[0].second), 0));
                        toWintrick.push_back(make_pair(make_pair(trick[1].first, trick[1].second), 1));
                        toWintrick.push_back(make_pair(make_pair(trick[2].first, trick[2].second), 2));
                        winindex = winner(toWintrick, trick[1].first, currentMarriage, 1);
                        // cout << "Winner of trick: " << toWintrick[winindex].first.first << toWintrick[winindex].first.second << ", " << toWintrick[winindex].second << endl;
                    }
                    else if (bots[2].wonPrev)
                    {
                        tempbotindex = bots[2].highest();
                        index = bots[1].RHchoose(bots[2].ai_deck[tempbotindex].first);
                        toChoose.second = 12;
                        for (size_t i = 0; i < bots[0].ai_deck.size(); i++)
                        {
                            if (bots[0].ai_deck[i].first == bots[2].ai_deck[tempbotindex].first)
                            {
                                if (bots[0].bestCard(deck, bots[0].ai_deck[i]))
                                {
                                    toChoose = bots[0].ai_deck[i];
                                    break;
                                }
                                if (bots[0].ai_deck[i].second < toChoose.second)
                                    toChoose = bots[0].ai_deck[i];
                            }
                        }
                        if (toChoose.second == 12)
                            toChoose = bots[0].ai_deck[bots[0].lowest()];

                        // cout << "Ai: " << toChoose.first << toChoose.second << endl;
                        trick.push_back(toChoose);
                        bots[0].cardClear(bots[0].ai_deck, toChoose);
                        // cout << "Bot 1: " << bots[1].ai_deck[index].first << bots[1].ai_deck[index].second << endl;
                        trick.push_back(bots[1].ai_deck[index]);
                        bots[0].cardClear(deck, bots[1].ai_deck[index]);
                        bots[1].cardClear(bots[1].ai_deck, bots[1].ai_deck[index]);
                        // cout << "Bot 2: " << bots[2].ai_deck[tempbotindex].first << bots[2].ai_deck[tempbotindex].second << endl;
                        trick.push_back(bots[2].ai_deck[tempbotindex]);
                        bots[0].cardClear(deck, bots[2].ai_deck[tempbotindex]);
                        bots[2].cardClear(bots[2].ai_deck, bots[2].ai_deck[tempbotindex]);
                        toWintrick.push_back(make_pair(make_pair(trick[0].first, trick[0].second), 0));
                        toWintrick.push_back(make_pair(make_pair(trick[1].first, trick[1].second), 1));
                        toWintrick.push_back(make_pair(make_pair(trick[2].first, trick[2].second), 2));
                        winindex = winner(toWintrick, trick[2].first, currentMarriage, 2);
                        // cout << "Winner of trick: " << toWintrick[winindex].first.first << toWintrick[winindex].first.second << ", " << toWintrick[winindex].second << endl;
                    }

                    for (int i = 0; i < 3; i++)
                    {
                        bots[i].wonPrev = false;
                        // cout << "Pushing " << trick[i].second << ", to: " << toWintrick[winindex].second << endl;
                        bots[winindex].won_deck.push_back(trick[i]);
                    }
                    bots[winindex].wonPrev = true;
                    bots[0].clearmarriage();
                    bots[0].marriage();
                }
                break;
            case 'B':
                // cout << "Implementing bot function\n";
                bots[(round - 1) % 3].wonPrev = true;
                bots[(round - 1) % 3].bode = 100;
                starter = (round - 1) % 3;
                for (auto x : tempdeck) // give prikup to starter
                    bots[starter].ai_deck.push_back(x);
                index = bots[starter].RHchoose("X");
                bots[(starter + 1) % 3].ai_deck.push_back(bots[starter].ai_deck[index]);
                bots[starter].ai_deck.erase(bots[starter].ai_deck.begin() + index);
                index = bots[starter].RHchoose("X");
                bots[(starter + 2) % 3].ai_deck.push_back(bots[starter].ai_deck[index]);
                bots[starter].ai_deck.erase(bots[starter].ai_deck.begin() + index);
                // bots[0].print();
                // cout << "-------------" << bots[0].type << "-------------------\n";
                // bots[1].print();
                // cout << "-------------" << bots[1].type << "-------------------\n";
                // bots[2].print();
                // cout << "-------------" << bots[2].type << "-------------------\n";

                for (int j = 0; j < 8; j++)
                {
                    // cout << "Round " << j << endl;
                    trick.clear();
                    toWintrick.clear();
                    for (int i = 0; i < 3; i++)
                    {
                        if (bots[i].wonPrev)
                        {
                            // cout << "Bot " << i << " won prev\n";
                            if (bots[i].type)
                            {
                                index = bots[i].RHchoose("X");
                                trick.push_back(bots[i].ai_deck[index]);
                                // cout << "Chosen index + card: " << index << "+" << bots[i].ai_deck[index].first << "," << bots[i].ai_deck[index].second << endl;
                                bots[i].cardClear(bots[i].ai_deck, bots[i].ai_deck[index]);
                                index = bots[(i + 1) % 3].RHchoose(trick[0].first);
                                trick.push_back(bots[(i + 1) % 3].ai_deck[index]);
                                bots[(i + 1) % 3].cardClear(bots[(i + 1) % 3].ai_deck, bots[(i + 1) % 3].ai_deck[index]);
                                index = bots[(i + 2) % 3].RHchoose(trick[0].first);
                                trick.push_back(bots[(i + 2) % 3].ai_deck[index]);
                                bots[(i + 1) % 3].cardClear(bots[(i + 2) % 3].ai_deck, bots[(i + 2) % 3].ai_deck[index]);
                            }
                            else
                            {
                                index = bots[i].highest();
                                trick.push_back(bots[i].ai_deck[index]);
                                // cout << "Chosen index + card: " << index << "+" << bots[i].ai_deck[index].first << "," << bots[i].ai_deck[index].second << endl;
                                bots[i].cardClear(bots[i].ai_deck, bots[i].ai_deck[index]);
                                index = bots[(i + 1) % 3].RHchoose(trick[0].first);
                                trick.push_back(bots[(i + 1) % 3].ai_deck[index]);
                                bots[(i + 1) % 3].cardClear(bots[(i + 1) % 3].ai_deck, bots[(i + 1) % 3].ai_deck[index]);
                                index = bots[(i + 2) % 3].RHchoose(trick[0].first);
                                trick.push_back(bots[(i + 2) % 3].ai_deck[index]);
                                bots[(i + 1) % 3].cardClear(bots[(i + 2) % 3].ai_deck, bots[(i + 2) % 3].ai_deck[index]);
                            }
                            toWintrick.push_back(make_pair(make_pair(trick[(3 - i) % 3].first, trick[(3 - i) % 3].second), 0));
                            toWintrick.push_back(make_pair(make_pair(trick[(4 - i) % 3].first, trick[(4 - i) % 3].second), 1));
                            toWintrick.push_back(make_pair(make_pair(trick[(5 - i) % 3].first, trick[(5 - i) % 3].second), 2));
                            winindex = winner(toWintrick, trick[0].first, currentMarriage, i);
                            // cout << "Winner is: " << winindex << ", with: \n";
                            // for (auto x : toWintrick)
                            //     cout << x.first.first << ", " << x.first.second << ", " << x.second << endl;
                            break;
                        }
                    }
                    for (int i = 0; i < 3; i++)
                    {
                        bots[i].wonPrev = false;
                        // cout << "Pushing " << trick[i].second << ", to: " << toWintrick[winindex].second << endl;
                        bots[winindex].won_deck.push_back(trick[i]);
                    }
                    bots[winindex].wonPrev = true;
                }
                break;
            }

            for (int k = 0; k < 3; k++)
            {
                if (bots[k].overalscore >= 900) // if a bot is in the barrel
                {
                    if (k == starter && bots[starter].score() >= bots[starter].bode)
                    {
                        bots[k].overalscore += bots[k].bode;
                    }
                    else if (k == starter)
                    {
                        bots[k].overalscore -= bots[k].bode;
                    }
                }
                else
                {
                    if (k == starter && bots[starter].score() >= bots[starter].bode)
                    {
                        bots[k].overalscore += bots[k].bode;
                    }
                    else if (k == starter)
                    {
                        bots[k].overalscore -= bots[k].bode;
                    }
                    else
                    {
                        bots[k].overalscore += nearestTen(bots[k].score());
                    }
                }
            }

            for (int j = 0; j < 3; j++)
            {
                // cout << "Bot " << j << " overalscore: " << bots[j].overalscore << endl;
                if (bots[j].overalscore >= 1000)
                {
                    gameDone = true;
                    botwins[j] += 1;
                    break;
                }
            }
            if (toWrite)
            {
                graph.push_back(pair<int, int>(0, bots[0].overalscore));
                graph.push_back(pair<int, int>(1, bots[1].overalscore));
                graph.push_back(pair<int, int>(2, bots[2].overalscore));
                // cout << "CP bode: " << bots[0].bode << ", and got: " << bots[0].score();
                // if (starter == 0)
                //{
                //     if (bots[0].bode != 100)
                //         cout << " <=Was the starter voluntarily=>";
                //     else
                //         cout << " <=Was the starter involuntarily=>";
                // }
                // cout << endl;
            }

            round++;

            // for (int i = 0; i < 3; i++)
            //     bots[i].print();
        }
        // cout << round << "-------------------------------------------\n"
        //      << "Final scores: \n"
        //      << bots[0].overalscore << endl
        //      << bots[1].overalscore << endl
        //      << bots[2].overalscore << endl;

        cout << "Experiment " << amount << " done\n";
        amount--;
        if (toWrite)
        {
            string filename = to_string((graph.size() / 3) - 1);
            filename.append(".txt");
            ofstream file;

            file.open(filename, ios::app);
            for (int j = 0; j < 3; j++)
            {
                for (size_t i = 0; i < graph.size() / 3; i++)
                {
                    file << graph[j + (i * 3)].second;
                    if (i != (graph.size() / 3 - 1))
                        file << ",";
                }
                file << "\n";
            }
            file << "#\n";
            file.close();
            graph.clear();
            graph.push_back(pair<int, int>(0, 0));
            graph.push_back(pair<int, int>(1, 0));
            graph.push_back(pair<int, int>(2, 0));
        }
    }
    cout << "---------------------\n|Experiment outcomes|\n---------------------\n"
         << "Computerprogram won: " << botwins[0] << endl
         << "Bot 1 won: " << botwins[1] << endl
         << "Bot 2 won: " << botwins[2] << endl;

    if (toWrite)
    {

        cout << "---------------------\n|Duration of last game|\n---------------------\n";
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (i % 3 == 0)
                cout << "Round " << i / 3 + 1 << endl;
            cout << "Bot " << graph[i].first << " score: " << graph[i].second << endl;
        }
    }

    return 0;
}