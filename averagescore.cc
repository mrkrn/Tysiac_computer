#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Aibot
{
public:
    Aibot(vector<pair<string, int>> &deck); // constructor
    void print();                           // print held deck
    int highestCard();                      // returns index of highest card from held deck
    int highestCard(string suit);           // returns index of highest card from held deck given a suit
    int lowestCard();                       // returns index of lowest card from held deck
    int lowestCard(string suit);            // returns index of lowest card from held deck given a suit
    bool checkTrump(string suit);           // check whether held deck contains card of suit

    vector<pair<string, int>> ai_deck;  // held deck
    vector<pair<string, int>> won_deck; // cards won
    bool wonPrev;                       // check if previous trick is won
};

Aibot::Aibot(vector<pair<string, int>> &deck)
{
    wonPrev = false;
    int index;
    for (size_t i = 0; i < 7; i++) // filling the held deck with random cards
    {
        index = rand() % deck.size();
        ai_deck.push_back(make_pair(deck[index].first, deck[index].second));
        deck.erase(deck.begin() + index);
    }
}

void Aibot::print()
{
    for (auto x : ai_deck)
    {
        cout << x.first << ", " << x.second << endl;
    }
}

int Aibot::highestCard()
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

int Aibot::highestCard(string suit)
{
    int index = 0, highest = -1;
    for (size_t i = 0; i < ai_deck.size(); i++)
    {
        if (ai_deck[i].second > highest && ai_deck[i].first == suit)
        {
            highest = ai_deck[i].second;
            index = i;
        }
    }
    return index;
}

int Aibot::lowestCard()
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

int Aibot::lowestCard(string suit)
{
    int index = 0, lowest = 15;
    for (size_t i = 0; i < ai_deck.size(); i++)
    {
        if (ai_deck[i].second < lowest && ai_deck[i].first == suit)
        {
            lowest = ai_deck[i].second;
            index = i;
        }
    }
    return index;
}

bool Aibot::checkTrump(string suit)
{
    for (auto x : ai_deck)
        if (x.first == suit)
            return true;
    return false;
}

int main()
{
    srand(time(NULL));
    int experiments = 0, totalScore = 0;
    cout << "Enter amount of experiments: ";
    cin >> experiments;
    int total = experiments;
    while (experiments > 0)
    {

        vector<pair<string, int>> deck;

        deck.push_back(pair<string, int>("D", 0));
        deck.push_back(pair<string, int>("S", 0));
        deck.push_back(pair<string, int>("H", 0));
        deck.push_back(pair<string, int>("C", 0));
        deck.push_back(pair<string, int>("D", 2));
        deck.push_back(pair<string, int>("S", 2));
        deck.push_back(pair<string, int>("H", 2));
        deck.push_back(pair<string, int>("C", 2));
        deck.push_back(pair<string, int>("D", 3));
        deck.push_back(pair<string, int>("S", 3));
        deck.push_back(pair<string, int>("H", 3));
        deck.push_back(pair<string, int>("C", 3));
        deck.push_back(pair<string, int>("D", 4));
        deck.push_back(pair<string, int>("S", 4));
        deck.push_back(pair<string, int>("H", 4));
        deck.push_back(pair<string, int>("C", 4));
        deck.push_back(pair<string, int>("D", 10));
        deck.push_back(pair<string, int>("S", 10));
        deck.push_back(pair<string, int>("H", 10));
        deck.push_back(pair<string, int>("C", 10));
        deck.push_back(pair<string, int>("D", 11));
        deck.push_back(pair<string, int>("S", 11));
        deck.push_back(pair<string, int>("H", 11));
        deck.push_back(pair<string, int>("C", 11));

        Aibot bot1(deck);
        Aibot bot2(deck);
        Aibot bot3(deck);
        // bot1.print();
        // cout << "-------------\n";
        //  bot2.print();
        //  cout << "-------------\n";
        //  bot3.print();
        //  cout << "-------------\n";

        // for (auto x : deck)
        //{
        //     cout << "Deck: " << x.first << ", " << x.second << endl;
        // }

        if (deck[0].second >= deck[1].second && deck[0].second >= deck[2].second)
        {
            bot1.ai_deck.push_back(make_pair(deck[0].first, deck[0].second));
            bot2.ai_deck.push_back(make_pair(deck[1].first, deck[1].second));
            bot3.ai_deck.push_back(make_pair(deck[2].first, deck[2].second));
        }
        else if (deck[1].second >= deck[0].second && deck[1].second >= deck[2].second)
        {
            bot1.ai_deck.push_back(make_pair(deck[1].first, deck[1].second));
            bot2.ai_deck.push_back(make_pair(deck[0].first, deck[0].second));
            bot3.ai_deck.push_back(make_pair(deck[2].first, deck[2].second));
        }
        else
        {
            bot1.ai_deck.push_back(make_pair(deck[2].first, deck[2].second));
            bot2.ai_deck.push_back(make_pair(deck[1].first, deck[1].second));
            bot3.ai_deck.push_back(make_pair(deck[0].first, deck[0].second));
        }

        deck.clear();
        // cout << "-------------\n";
        // bot1.print();
        // cout << "-------------\n";
        // bot2.print();
        // cout << "-------------\n";
        // bot3.print();
        // cout << "-------------\n";

        /*
        cout << "Highest card: " << bot1.ai_deck[bot1.highestCard()].first << ", " << bot1.ai_deck[bot1.highestCard()].second << endl;
        cout << "Highest card: " << bot2.ai_deck[bot2.highestCard()].first << ", " << bot2.ai_deck[bot2.highestCard()].second << endl;
        cout << "Highest card: " << bot3.ai_deck[bot3.highestCard()].first << ", " << bot3.ai_deck[bot3.highestCard()].second << endl;
        cout << "Lowest card: " << bot1.ai_deck[bot1.lowestCard()].first << ", " << bot1.ai_deck[bot1.lowestCard()].second << endl;
        cout << "Lowest card: " << bot2.ai_deck[bot2.lowestCard()].first << ", " << bot2.ai_deck[bot2.lowestCard()].second << endl;
        cout << "Lowest card: " << bot3.ai_deck[bot3.lowestCard()].first << ", " << bot3.ai_deck[bot3.lowestCard()].second << endl;

        cout << "Highest D card: " << bot1.highestCard("D") << ", " << bot1.highestCard("D") << endl;
        cout << "Highest D card: " << bot2.highestCard("D") << ", " << bot2.highestCard("D") << endl;
        cout << "Highest D card: " << bot3.highestCard("D") << ", " << bot3.highestCard("D") << endl;
        cout << "Lowest D card: " << bot1.lowestCard("D") << ", " << bot1.lowestCard("D") << endl;
        cout << "Lowest D card: " << bot2.lowestCard("D") << ", " << bot2.lowestCard("D") << endl;
        cout << "Lowest D card: " << bot3.lowestCard("D") << ", " << bot3.lowestCard("D") << endl;
        */

        // cout << "-----------------------------------------------\n";
        vector<pair<string, int>> trick; // deck that contains the current trick
        // one round
        bot1.wonPrev = true;
        int toRemove; // card to remove from held hand

        for (int i = 0; i < 8; i++)
        {
            if (bot1.wonPrev)
            {
                bot1.wonPrev = true;
                toRemove = bot1.highestCard();
                trick.push_back(bot1.ai_deck[toRemove]);
                bot1.ai_deck.erase(bot1.ai_deck.begin() + toRemove);
                if (bot2.checkTrump(trick[0].first)) // can bot2 follow suit
                {
                    if (bot2.ai_deck[bot2.highestCard(trick[0].first)].second > trick[0].second) // does bot2 have a higher trump card
                    {
                        toRemove = bot2.highestCard(trick[0].first);
                        bot1.wonPrev = false;
                        bot2.wonPrev = true;
                        bot3.wonPrev = false;
                    }
                    else // no higher trump card but must follow suit
                    {
                        toRemove = bot2.lowestCard(trick[0].first);
                    }
                }
                else // cannot follow suit
                {
                    toRemove = bot2.lowestCard();
                }
                trick.push_back(bot2.ai_deck[toRemove]);
                bot2.ai_deck.erase(bot2.ai_deck.begin() + toRemove);

                if (bot3.checkTrump(trick[0].first)) // can bot3 follow suit
                {
                    if (bot3.ai_deck[bot3.highestCard(trick[0].first)].second > trick[0].second &&
                        bot3.ai_deck[bot3.highestCard(trick[0].first)].second > trick[1].second) // does bot3 have the highest trump card
                    {
                        toRemove = bot3.highestCard(trick[0].first);
                        bot1.wonPrev = false;
                        bot2.wonPrev = false;
                        bot3.wonPrev = true;
                    }
                    else // no higher trump card but must follow suit
                    {
                        toRemove = bot3.lowestCard(trick[0].first);
                    }
                }
                else // cannot follow suit
                {
                    toRemove = bot3.lowestCard();
                }
                trick.push_back(bot3.ai_deck[toRemove]);
                bot3.ai_deck.erase(bot3.ai_deck.begin() + toRemove);
            }
            else if (bot2.wonPrev)
            {
                bot2.wonPrev = true;
                toRemove = bot2.highestCard();
                trick.push_back(bot2.ai_deck[toRemove]);
                bot2.ai_deck.erase(bot2.ai_deck.begin() + toRemove);
                if (bot3.checkTrump(trick[0].first)) // can bot3 follow suit
                {
                    if (bot3.ai_deck[bot3.highestCard(trick[0].first)].second > trick[0].second) // does bot3 have a higher trump card
                    {
                        toRemove = bot3.highestCard(trick[0].first);
                        bot2.wonPrev = false;
                        bot3.wonPrev = true;
                        bot1.wonPrev = false;
                    }
                    else // no higher trump card but must follow suit
                    {
                        toRemove = bot3.lowestCard(trick[0].first);
                    }
                }
                else // cannot follow suit
                {
                    toRemove = bot3.lowestCard();
                }
                trick.push_back(bot3.ai_deck[toRemove]);
                bot3.ai_deck.erase(bot3.ai_deck.begin() + toRemove);

                if (bot1.checkTrump(trick[0].first)) // can bot1 follow suit
                {
                    if (bot1.ai_deck[bot1.highestCard(trick[0].first)].second > trick[0].second &&
                        bot1.ai_deck[bot1.highestCard(trick[0].first)].second > trick[1].second) // does bot1 have the highest trump card
                    {
                        toRemove = bot1.highestCard(trick[0].first);
                        bot2.wonPrev = false;
                        bot3.wonPrev = false;
                        bot1.wonPrev = true;
                    }
                    else // no higher trump card but must follow suit
                    {
                        toRemove = bot1.lowestCard(trick[0].first);
                    }
                }
                else // cannot follow suit
                {
                    toRemove = bot1.lowestCard();
                }
                trick.push_back(bot1.ai_deck[toRemove]);
                bot1.ai_deck.erase(bot1.ai_deck.begin() + toRemove);
            }
            else if (bot3.wonPrev)
            {
                bot3.wonPrev = true;
                toRemove = bot3.highestCard();
                trick.push_back(bot3.ai_deck[toRemove]);
                bot3.ai_deck.erase(bot3.ai_deck.begin() + toRemove);
                if (bot1.checkTrump(trick[0].first)) // can bot1 follow suit
                {
                    if (bot1.ai_deck[bot1.highestCard(trick[0].first)].second > trick[0].second) // does bot1 have a higher trump card
                    {
                        toRemove = bot1.highestCard(trick[0].first);
                        bot3.wonPrev = false;
                        bot1.wonPrev = true;
                        bot2.wonPrev = false;
                    }
                    else // no higher trump card but must follow suit
                    {
                        toRemove = bot1.lowestCard(trick[0].first);
                    }
                }
                else // cannot follow suit
                {
                    toRemove = bot1.lowestCard();
                }
                trick.push_back(bot1.ai_deck[toRemove]);
                bot1.ai_deck.erase(bot1.ai_deck.begin() + toRemove);

                if (bot2.checkTrump(trick[0].first)) // can bot2 follow suit
                {
                    if (bot2.ai_deck[bot2.highestCard(trick[0].first)].second > trick[0].second &&
                        bot2.ai_deck[bot2.highestCard(trick[0].first)].second > trick[1].second) // does bot2 have the highest trump card
                    {
                        toRemove = bot2.highestCard(trick[0].first);
                        bot3.wonPrev = false;
                        bot1.wonPrev = false;
                        bot2.wonPrev = true;
                    }
                    else // no higher trump card but must follow suit
                    {
                        toRemove = bot2.lowestCard(trick[0].first);
                    }
                }
                else // cannot follow suit
                {
                    toRemove = bot2.lowestCard();
                }
                trick.push_back(bot2.ai_deck[toRemove]);
                bot2.ai_deck.erase(bot2.ai_deck.begin() + toRemove);
            }

            if (bot1.wonPrev)
            {
                bot1.won_deck.push_back(trick[0]);
                bot1.won_deck.push_back(trick[1]);
                bot1.won_deck.push_back(trick[2]);
            }
            else if (bot2.wonPrev)
            {
                bot2.won_deck.push_back(trick[0]);
                bot2.won_deck.push_back(trick[1]);
                bot2.won_deck.push_back(trick[2]);
            }
            else if (bot3.wonPrev)
            {
                bot3.won_deck.push_back(trick[0]);
                bot3.won_deck.push_back(trick[1]);
                bot3.won_deck.push_back(trick[2]);
            }
            trick.clear();
        }

        bot1.wonPrev = false;
        bot2.wonPrev = false;
        bot3.wonPrev = false;

        int score = 0;
        for (auto x : bot1.won_deck)
        {
            score += x.second;
        }
        totalScore += score;
        cout << "Bot1 score: " << score << ", " << totalScore << endl;

        experiments--;
    }

    cout << "Experiment average: " << double(totalScore / total) << endl;

    return 0;
}