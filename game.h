#ifndef GAME_H
#define GAME_H

#include <string>

class Player {
private:
    std::string name;
    int damage = 0;
    int hp = 0;
    int wins = 0;
    int losses = 0;
    int win_streak = 0;
    std::string choice;

public:
    Player();
    std::string getName() const { return name; }
    int getDamage() const { return damage; }
    int getHp() const { return hp; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    int getWinStreak() const { return win_streak; }
    std::string getChoice() const { return choice; }

    void setName(const std::string n) { name = n; }
    void setDamage(const int d) { damage = d; }
    void setHp(const int h) { hp = h; }
    void setWins(const int w) { wins = w; }
    void setLosses(const int l) { losses = l; }
    void setWinStreak(const int ws) { win_streak = ws; }
    void setChoice(const std::string c) { choice = c; }
};

class Bot {
private:
    std::string name;
    int damage = 0;
    int hp = 0;
    std::string choice;

public:
    Bot();
    std::string getName() const { return name; }
    int getDamage() const { return damage; }
    int getHp() const { return hp; }
    std::string getChoice() const { return choice; }

    void setName(const std::string n) { name = n; }
    void setDamage(const int d) { damage = d; }
    void setHp(const int h) { hp = h; }
    void setChoice(const std::string c) { choice = c; }
};

class Game {
public:
    Game();

    // utilities
    static void clearConsole();
    static void inputName(Player* pl);
    static std::string readLineToLower();
    static double randomDouble();

    // gametime methods
    static void showBothHp(std::string playerName, std::string botName, int playerHp, int botHp);
    static void fight(Player* pl, Bot* bt); // TODO: implement fight logic
    static std::string botDecision();
    static std::string decideBotName();
    static int compareResults(std::string player, std::string bot, std::string botName);
    static void playerStats(Player* pl, Bot* bt, bool cls);
    static void menu(Player* pl, Bot* bt);
    static void start();

    static const int DEFAULT_HP = 3;
};

#endif