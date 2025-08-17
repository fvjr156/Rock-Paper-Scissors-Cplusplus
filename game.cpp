#include "game.h"
#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

Player::Player() : name(""), damage(0), hp(0), wins(0), losses(0), win_streak(0), choice("") {}
Bot::Bot() : name(""), damage(0), hp(0), choice("") {}

void Game::clearConsole()
{
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

void Game::inputName(Player* pl) 
{
    if (pl == nullptr) { std::cerr << "ERROR: Player is null." << std::endl; return; }
    std::string name;
    std::cout << "\n\n\n\nWhat's your name?" << "\n>>> ";
    
    while(true) {
        std::getline(std::cin, name);
        if (name.empty()) { std::cout << "Name cannot be empty. Please enter your name:\n>>> "; continue; }
        break;
    }

    pl->setName(name);
}

std::string Game::readLineToLower() 
{
    std::string in;
    while(true) {
        std::getline(std::cin, in);
        if (in.empty()) { std::cout << "Input cannot be empty. Please enter again:\n>>> "; continue; }
        break;
    }
    std::transform(in.begin(), in.end(), in.begin(), ::tolower);
    return in;
}

double Game::randomDouble()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

void Game::showBothHp(std::string playerName, std::string botName, int playerHp, int botHp)
{
    std::cout << "\n------------------------------------------------\n     " << playerName << ":\t";
    for(int i = 0; i < playerHp; i++) std::cout << "♥ ";
    
    std::cout << "\n     " << botName << ":\t";
    for(int i = 0; i < botHp; i++) std::cout << "♥ ";

    std::cout << "\n------------------------------------------------";
}

std::string Game::botDecision()
{
    double val = Game::randomDouble();
    std::string pick;
    if (val > 0 && val <= 0.05) {
        return "None";
    }
    if (val > 0.05 && val <= 0.31) {
        return "Rock";
    }
    if (val > 0.31 && val <= 0.63) {
        return "Paper";
    }
    if (val > 0.63 && val <= 1) {
        return "Scissors";
    }
    return "";
}

std::string Game::decideBotName()
{
    std::vector<std::string> names = {
        "Levy", "Magnus", "Hikaru", "Ian", "Ding", "Gukesh", "Fabiano"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, names.size() -1);
    
    int index = dis(gen);
    return names[index];
}

int Game::compareResults(std::string player, std::string bot, std::string botName)
{
   std::transform(bot.begin(), bot.end(), bot.begin(), ::tolower);
   std::transform(player.begin(), player.end(), player.begin(), ::tolower);

   if (bot == "none")
   {
        std::cout << "\n" << botName <<" did not pick anything. You win!\n" << std::endl;
        return 1;
   }
   if ((bot == "scissors" && player == "scissors") || (bot == "paper" && player == "paper") || (bot == "rock" && player == "rock"))
   {
        std::cout << "\nNobody won!\n" << std::endl;
        return 0;
   }
   if ((player == "paper" && bot == "rock") || (player == "scissors" && bot == "paper") || (player == "rock" && bot == "scissors"))
   {
        std::cout << "\nYou won!\n" << std::endl;
        return 1;
   }
   if ((player == "rock" && bot == "paper") || (player == "paper" && bot == "scissors") || (player == "scissors" && bot == "rock"))
   {
        std::cout << "\nYou lost!\n" << std::endl;
        return 2;
   }
   return 0;
}

void Game::fight(Player* pl, Bot* bt) 
{
    bt->setName(Game::decideBotName());

    Game::clearConsole();
    bool showHp = true;
    bool inputError = false;
    while (true) 
    {
        if (pl->getHp() < 1)
        {
            pl->setLosses(pl->getLosses() +1);
            pl->setWinStreak(0);
            std::cout <<
                "\n\n------------------------------------------------" <<
                "\n     You have been defeated." <<
                "\n------------------------------------------------\n\n";
                Game::playerStats(pl, bt, false);
            break;
        }
        if (bt->getHp() < 1)
        {
            pl->setWins(pl->getWins() +1);
            pl->setWinStreak(pl->getWinStreak() +1);
            std::cout <<
                "\n\n------------------------------------------------" <<
                "\n     You defeated " << bt->getName() << "!" <<
                "\n------------------------------------------------\n\n";
                Game::playerStats(pl, bt, false);
            break;
        }

        if (inputError) { std::cout << "That's an invalid choice. Try again." << std::endl; }
        if (showHp) { showBothHp(pl->getName(), bt->getName(), pl->getHp(), bt->getHp()); }
        std::cout <<
            "\n\n------------------------------------------------" <<
            "\n     What do you wish to throw?" <<
            "\n     Rock     Paper     Scissors"
            "\n------------------------------------------------\n>>> ";

        std::string input = readLineToLower();
        std::string botInput = Game::botDecision();

        std::string choices[] = {"rock", "paper", "scissors"};
        int choicessize = sizeof(choices) / sizeof(choices[0]);

        if (std::find(choices, choices + choicessize, input) != choices + choicessize)
        {
            std::cout << "You picked: " << input << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << bt->getName() << " picks: " << botInput << std::endl;
            int res = Game::compareResults(input, botInput, bt->getName());
            if (res == 1)
            {
                bt->setHp(bt->getHp() -1);
            }
            if (res == 2)
            {
                pl->setHp(pl->getHp() -1);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            inputError = false;
            showHp = true;
            Game::clearConsole();
            continue;
        }
        else
        {
            showHp = false;
            inputError = true;
            Game::clearConsole();
            continue;
        }
    }
}

void Game::playerStats(Player* pl, Bot* bt, bool cls)
{
    if (cls) { Game::clearConsole(); }
    bool inputError = false;

    while(true)
    {
        if (inputError) { std::cout << "That's an invalid choice. Try again." << std::endl; }
        int ws = pl->getWinStreak();
        std::cout <<
            "----------------- Player Stats -----------------" <<
            "\n\tName: " << pl->getName() <<
            "\n\tWins: " << pl->getWins() <<
            "\n\tLosses: " << pl->getLosses() <<
            "\n\tCurrent winstreak: " << ((ws > 0) ? std::to_string(ws) : "None") <<
            "\n------------------------------------------------\nGo back to menu? [Y/N]\n>>> ";

        std::string input = readLineToLower();

        if (input == "yes" || input == "y")
        {
            Game::menu(pl, bt);
            break;
        }
        else if (input == "no" || input == "n")
        {
            bt->setHp(Game::DEFAULT_HP);
            pl->setHp(Game::DEFAULT_HP);
            Game::fight(pl, bt);
            break;
        }
        else
        {
            inputError = true;
            Game::clearConsole();
            continue;
        }        
    }
}

void Game::menu(Player* pl, Bot* bt) 
{
    Game::clearConsole();
    std::cout << "Welcome, " << pl->getName() << "!\n";
    bool inputError = false;

    while (true)
    {
        if (inputError) { std::cout << "That's an invalid choice. Try again." << std::endl; }
        std::cout << "What do you wish to do?\n";
        std::cout <<
            "(---------------------------------------------)\n" <<
            "(------------------Main Menu------------------)\n" <<
            "(------------------| Start |------------------)\n" <<
            "(------------------| Stats |------------------)\n" <<
            "(------------------| Exit  |------------------)\n" <<
            "(---------------------------------------------)\n>>> ";
        std::string input = readLineToLower();

        if (input == "start")
        {
            Game::fight(pl, bt);
            break;
        }
        else if (input == "stats")
        {
            Game::playerStats(pl, bt, true);
            break;
        }
        else if (input == "exit")
        {
            std::cout << "The game will now close." << std::endl;
            break;
            exit(0);
        }
        else
        {
            inputError = true;
            Game::clearConsole();
            continue;
        }
    }
}

void Game::start() 
{
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif

    Player* player = new Player();
    Bot* bot = new Bot();

    inputName(player);

    player->setHp(Game::DEFAULT_HP);
    bot->setHp(Game::DEFAULT_HP);

    menu(player, bot);

    delete player;
    delete bot;
}