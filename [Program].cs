using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace _01_LMS_Activity_1
{
    public class Game
    {
        static void Main(String[] args)
        {
            //Initialization of objects
            Player player = new Player();
            Bot bot = new Bot();

            //Initialization of constants
            const int hp = 3;

            //Main Simulation
            player.hp = hp;
            bot.hp = hp;

            opening();

            inputName();
            menu();

            //Methods

            void menu()
            {
                Console.Clear();
                opening();

                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine($"Welcome @{player.name}");
                Console.WriteLine("What do you wish to do?");
                Console.WriteLine("(---------------------------------------------)");
                Console.WriteLine("(------------------Main Menu------------------)");
                Console.WriteLine("(------------------| Start |------------------)");
                Console.WriteLine("(------------------| Stats |------------------)");
                Console.WriteLine("(------------------| Exit  |------------------)");
                Console.WriteLine("(---------------------------------------------)");
                Console.WriteLine();
                string input = Console.ReadLine();
                input = input.ToLower();

                if (input == "start")
                {
                    Console.Clear();
                    simulateFight();
                }
                else if (input == "stats")
                {
                    playerStats();
                }
                else if (input == "exit")
                {
                    Console.WriteLine("The game will now close...");
                    System.Environment.Exit(0);
                }
                else
                {
                    Console.WriteLine("That is an invalid choice, please try again.");
                    Console.Write(">>> ");
                    input = Console.ReadLine();
                    input = input.ToLower();
                    menu();
                }
            }

            void simulateFight()
            {
                Console.ForegroundColor = ConsoleColor.Red;
                opening();
                Console.WriteLine("What do you wish to throw?");
                Console.WriteLine("| Rock | Paper | Scissors |");
                border();
                Console.Write(">>> ");
                string[] choices = { "rock", "paper", "scissors" };
                string choice = Console.ReadLine().ToLower();
                player.choice = choice;
                if (choices.Contains(player.choice))
                {
                    botChoice();
                    //Win Conditions
                    if (player.choice == choices[0] && bot.choice == choices[2])
                    {
                        --bot.hp;
                        Console.WriteLine($"Bot's HP: {bot.hp}/{hp}");
                        Thread.Sleep(1000);
                        Console.Clear();
                        win();
                        simulateFight();
                    }
                    else if (player.choice == choices[1] && bot.choice == choices[0])
                    {
                        --bot.hp;
                        Console.WriteLine($"Bot's HP: {bot.hp}/{hp}");
                        Thread.Sleep(1000);
                        Console.Clear();
                        win();
                        simulateFight();
                    }
                    else if (player.choice == choices[2] && bot.choice == choices[1])
                    {
                        --bot.hp;
                        Console.WriteLine($"Bot's HP: {bot.hp}/{hp}");
                        Thread.Sleep(1000);
                        Console.Clear();
                        win();
                        simulateFight();
                    }
                    //Loss Conditions
                    else if (bot.choice == choices[0] && player.choice == choices[2])
                    {
                        --player.hp;
                        Console.WriteLine($"Your HP: {player.hp}/{hp}");
                        Thread.Sleep(1000);
                        Console.Clear();
                        loss();
                        simulateFight();
                    }
                    else if (bot.choice == choices[1] && player.choice == choices[0])
                    {
                        --player.hp;
                        Console.WriteLine($"Your HP: {player.hp}/{hp}");
                        Thread.Sleep(1000);
                        Console.Clear();
                        loss();
                        simulateFight();
                    }
                    else if (bot.choice == choices[2] && player.choice == choices[1])
                    {
                        --player.hp;
                        Console.WriteLine($"Your HP: {player.hp}/{hp}");
                        Thread.Sleep(1000);
                        Console.Clear();
                        loss();
                        simulateFight();
                    }
                    else if (player.choice == bot.choice)
                    {
                        Console.WriteLine($"It's a draw.");
                        Thread.Sleep(1000);
                        Console.Clear();
                        win();
                        loss();
                        simulateFight();
                    }
                    else
                    {
                        Console.WriteLine("You have encountered an error, the game will now close...");
                        System.Environment.Exit(0);
                    }
                }
                else
                {
                    Console.Clear();
                    opening();
                    Console.WriteLine("That is an invalid choice, please try again.");
                    Thread.Sleep(1000);
                    Console.Clear();
                    simulateFight();
                }
            }
            void botChoice()
            {
                Random random = new Random();
                double randomchoice = random.NextDouble();
                Console.Clear();
                opening();
                Console.WriteLine("The bot will now throw ");
                if (randomchoice == 0.01) //Bonus Win
                {
                    ++player.wins;
                    Console.WriteLine("The bot decided not to throw anything, you win!");
                    menu();
                }
                else if (randomchoice > 0.01 && randomchoice <= 0.34) // bot will throw rock
                {
                    bot.choice = "rock";
                    Console.WriteLine($"The bot chose {bot.choice}!");
                }
                else if (randomchoice > 0.34 && randomchoice <= 0.67) // bot will throw paper
                {
                    bot.choice = "paper";
                    Console.WriteLine($"The bot chose {bot.choice}!");
                }
                else if (randomchoice > 0.67 && randomchoice <= 1.00) // bot will throw scissors
                {
                    bot.choice = "scissors";
                    Console.WriteLine($"The bot chose {bot.choice}!");
                }
            }

            void win()
            {
                if(bot.hp == 0)
                {
                    bot.hp = hp;
                    player.hp = hp;
                    Console.Clear();
                    opening();
                    Console.WriteLine($"You threw {player.choice}, while the bot threw a {bot.choice}. You Won!");
                    ++player.wins;
                    ++player.winstreak;
                    Console.WriteLine($"You have won {player.winstreak} times straight.");
                    Thread.Sleep(1000);
                    Console.WriteLine("(Go back to menu? Y/N)");
                    Console.Write(">>> ");
                    string input = Console.ReadLine().ToLower();
                    string answer = input;
                    if (answer == "yes" || answer == "y")
                    {
                        Console.Clear();
                        menu();
                    }
                    else if (answer == "no" || answer == "n")
                    {
                        Console.Clear();
                        simulateFight();
                    }
                }
            }
            void loss()
            {
                if(player.hp == 0)
                {
                    player.hp = hp;
                    bot.hp = hp;
                    opening();
                    Console.WriteLine($"You threw {player.choice}, while the bot threw a {bot.choice}. You Lost :(");
                    ++player.losses;
                    player.winstreak = 0;
                    Console.WriteLine($"You lost your winstreak.");
                    Thread.Sleep(1000);
                    Console.WriteLine("(Go back to menu? Y/N)");
                    Console.Write(">>> ");
                    string input = Console.ReadLine().ToLower();
                    string answer = input;
                    if (answer == "yes" || answer == "y")
                    {
                        Console.Clear();
                        menu();
                    }
                    else if (answer == "no" || answer == "n")
                    {
                        Console.Clear();
                        simulateFight();
                    }
                }
            }

            void inputName()
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine("What is your name?");
                border();
                Console.Write(">>> ");
                string input = Console.ReadLine();
                string name = input;
                name = char.ToUpper(name[0]) + name.Substring(1);
                player.name = name;
            }
            void playerStats()
            {
                Console.ForegroundColor = ConsoleColor.Magenta;
                Console.WriteLine("(-----------------Player Stats----------------)");
                Console.WriteLine($"(Name: {player.name})");
                Console.WriteLine($"(Wins: {player.wins})");
                Console.WriteLine($"(Losses: {player.losses})");
                if (player.winstreak == 0)
                {
                    Console.WriteLine($"Current Winstreak: none");
                }
                else
                {
                    Console.WriteLine($"(Current Winstreak: {player.winstreak})");
                }
                Console.WriteLine("(---------------------------------------------)");
                Console.WriteLine("(Go back to menu? Y/N)");
                Console.Write(">>> ");
                string input = Console.ReadLine().ToLower();
                string answer = input;
                if (answer == "yes" || answer == "y")
                {
                    Console.Clear();
                    menu();
                }
                else if (answer == "no" || answer == "n")
                {
                    Console.Clear();
                    simulateFight();
                }
            }
            static void opening()
            {
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("\r\n  _____               _      _____                             _____        _                             \r\n |  __ \\             | |    |  __ \\                           / ____|      (_)                            \r\n | |__) | ___    ___ | | __ | |__) |__ _  _ __    ___  _ __  | (___    ___  _  ___  ___   ___   _ __  ___ \r\n |  _  / / _ \\  / __|| |/ / |  ___// _` || '_ \\  / _ \\| '__|  \\___ \\  / __|| |/ __|/ __| / _ \\ | '__|/ __|\r\n | | \\ \\| (_) || (__ |   <  | |   | (_| || |_) ||  __/| |     ____) || (__ | |\\__ \\\\__ \\| (_) || |   \\__ \\\r\n |_|  \\_\\\\___/  \\___||_|\\_\\ |_|    \\__,_|| .__/  \\___||_|    |_____/  \\___||_||___/|___/ \\___/ |_|   |___/\r\n                                         | |                                                              \r\n                                         |_|                                                              \r\n");
            }
            static void border()
            {
                Console.WriteLine("(---------------------------------------------)");
            }
        }
    }
}
