// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T14L
// Names: KAWSAR | CHENG FU LIN | LAU JUN XING
// IDs: 1211310827 | 1221301545 | 1201102941
// Emails: mdrisveyhasan1@gmail.com | fulincheng1018@gmail.com | xinglau92@gmail.com
// Phones: +601169727851 | +60163864848 | +60164074733
// *********************************************************

#include <array>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <map>
#include "boardsetting.h"
using namespace std;

// Define a random number generator from 0 to a certain limit
int random(int limit)
{
    return rand() % limit;
};

// Define the board generator class
class Gameboard
{
public:
    int columns;
    int rows;
    int total_cols;
    int total_rows;
    char **board;

    // Gameboard initializer
    Gameboard(int set_rows, int set_cols)
    {

        columns = set_cols;
        rows = set_rows;
        total_cols = (columns * 2) + 1;
        total_rows = (rows * 2) + 1;

        board = new char *[total_rows];

        for (int row = 0; row < total_rows; row++)
        {
            board[row] = new char[total_cols];
            for (int col = 0; col < total_cols; col++)
            {
                if (row == 0 || row == total_rows || row % 2 == 0)
                {
                    board[row][col] = '-';
                }

                else if (col == 0 || col == total_cols || col % 2 == 0)
                {
                    board[row][col] = '|';
                }

                else
                {
                    board[row][col] = ' ';
                };
            };
        };
    };

    // Display the gameboard
    void showGameboard()
    {

        for (int row = 0; row < total_rows; row++)
        {
            for (int col = 0; col < total_cols + 1; col++)
            {
                if (col == total_cols && row != 0 && row % 2 != 0)
                {
                    cout << int(row / 2) + 1;
                }
                else if (col == total_cols && row % 2 == 0)
                {
                    cout << ' ';
                }
                else
                {
                    cout << board[row][col];
                }
            };
            cout << endl;
        };

        // Show the navigation row
        int nav_row = 1;
        if (columns > 9)
            nav_row = 2;
        for (int row = 0; row < nav_row; row++)
        {
            int col_count = 0;
            for (int col = 0; col < total_cols; col++)
            {
                if (col % 2 != 0 && row == 0)
                {
                    if (int(col / 2) < 9)
                    {
                        cout << int(col / 2) + 1;
                    }
                    else
                    {
                        cout << (int((col + 1) / 2) / 10);
                    }
                }
                else if (row > 0 && col / 2 >= 9 && col % 2 != 0)
                {
                    cout << ((col / 2) - ceil(col_count / 10) * 10 + 1) - 10;
                    col_count++;
                }

                else
                {
                    cout << ' ';
                }
            }
            cout << endl;
        }
    };
};

// Define general object class with the common characteristics and behaviour of all the game characters
class Character
{
public:
    char name;
    int life = 0;
    int impact = 0;
    int x_pos = 0, y_pos = 0;
    bool alive = true;

    // Change position to one column right
    void move_right()
    {
        y_pos += 2;
    };

    // Change position to one column left
    void move_left()
    {
        y_pos -= 2;
    };

    // Change position to one row up
    void move_up()
    {
        x_pos -= 2;
    };

    // Change position to one row down
    void move_down()
    {
        x_pos += 2;
    };

    // Define character got hit behavious
    void gotHit(int impact)
    {
        life = life - impact;
        if (life <= 0)
        {
            alive = false;
        };
    };
};

// Create an alien class by inheriting the Character class
class Alien : public Character
{
public:
    int maxLife;
    int attacks = 0;
    // Alien initializer
    Alien(int set_maxLife, int set_impact)
    {
        name = 'A';
        maxLife = set_maxLife;
        impact = set_impact;
        life = set_maxLife;
    };

    // Alien life increment
    void addLife(int increment)
    {
        if (life < maxLife)
        {
            life = life + increment;
        };
    };

    // Alien attack increment
    void attacked()
    {
        attacks++;
    };
};

// Create a zombie class by inheriting the Character class
class Zombie : public Character
{
public:
    /*Initiate a zombie object with name provided and set the life depending on the alien life.
    A zombie cannot have more life than the alien does */
    Zombie(char set_name, int alienLife)
    {
        name = set_name;

        int lifeScope[(alienLife / 10) - 3];
        int totalLifeScopes = sizeof(lifeScope) / sizeof(lifeScope[0]);
        for (int i = 1; i < totalLifeScopes; i++)
        {
            lifeScope[i - 1] = i * 10;
        }

        life = lifeScope[random(totalLifeScopes)];
        if (life < 20)
        {
            life = 20;
        };

        // Zombie cannot have an attack impact more than a quarter of the alien life.
        int impactScope[((alienLife / 10) / 4)];
        int totalImpactScopes = sizeof(impactScope) / sizeof(impactScope[0]);
        for (int i = 1; i <= totalImpactScopes; i++)
        {
            impactScope[i - 1] = i * 10;
        }

        impact = impactScope[random(totalImpactScopes)];
    };
};

// Create a rock class by inheriting the Character class
class Rock : public Character
{
public:
    // Initialize a rock depending on the alien impact and set a hidden item for the rock
    Rock(int alienImpact)
    {
        // Set the initial characteristics of a rock
        name = 'r';

        // Set the lifespan of a rock
        // Rock can have life value more than the attack impact of the alien
        int lifeScope[2 + (alienImpact / 10)];
        int totalLifeScopes = sizeof(lifeScope) / sizeof(lifeScope[0]);
        for (int i = 1; i <= totalLifeScopes; i++)
        {
            lifeScope[i - 1] = i * 10;
        }
        life = lifeScope[random(totalLifeScopes)];
    };

    // Reveal the hidden item of a rock
    char reveal()
    {
        char items[] = {'P', 'H', 'V', '^', '>', '<', ' '};
        return items[random(6)];
    };
};

// Create a pod class by inheriting the Chaaracter class
class Pod : public Character
{
public:
    int attack_radius;
    int impact = 10;

    // Pod initializer
    Pod(int set_attact_radius)
    {
        name = 'p';
        attack_radius = set_attact_radius;
    };
};

// Create a class for the arrows
class Arrow : public Character
{
public:
    Arrow()
    {
        char arrows[4] = {'^', 'v', '>', '<'};
        int pick = random(3);
        name = arrows[pick];
    }
};

// Create the health class
class Health : public Character
{
public:
    Health()
    {
        name = 'h';
    }
};


void place_character(Gameboard gm, Character C)
{
    char **board = gm.board;
    int x_pos = C.x_pos;
    vector<std::array<int, 2>> empty_space;
    for (int row = 0; row < gm.total_rows; row++)
    {
        for (int col = 0; col < gm.total_cols; col++)
        {
            if (board[row][col] == ' ')
            {
                array<int, 2> a{{row, col}};
                empty_space.push_back(a);
            }
        }
    }
    empty_space.shrink_to_fit();
    int picker = random(empty_space.size());
    board[empty_space[picker][0]][empty_space[picker][1]] = C.name;
    C.x_pos = empty_space[picker][0];
    C.alive = empty_space[picker][1];
}

//Find out the next item on the board depending on the movement direction
char next_item(Gameboard gm, Character C, char direction, vector<Character> characters)
{
    char **board = gm.board;
    switch (direction)
    {
    case 'u':
        return board[C.x_pos - 2][C.y_pos];
        break;
    case 'd':
        return board[C.x_pos + 2][C.y_pos];
        break;
    case 'l':
        return board[C.x_pos][C.y_pos - 2];
        break;
    case 'r':
        return board[C.x_pos][C.y_pos + 2];
        break;

    default:
        return board[C.x_pos][C.y_pos];
        break;
    }
}

// Check if character reached the border
bool stop(Character C, Gameboard gm, char movement)
{
    int total_rows = gm.total_rows;
    int total_cols = gm.total_cols;

    int x_pos = C.x_pos;
    int y_pos = C.y_pos;
    switch (movement)
    {
    case 'r':
        if (C.y_pos == total_cols - 2)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;

    case 'l':
        if (C.y_pos == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;

    case 'u':
        if (C.x_pos == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 'd':
        if (C.x_pos == total_rows - 2)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;

    default:
        return false;
        break;
    }
}

// Make a colission witht object


void Game_Control(vector<Character> all_characters, Gameboard gameboard, char turn)
{
    char **g_board = gameboard.board;
    int a_ctrl = 0;
    Character character;
    for(int i = 0; i < all_characters.size(); i++){
        if(all_characters[i].name == turn){
            character = all_characters[i];
        }
    }

    string command;
    cout << "command > ";
    cin >> command;

    while(character.name == 'A'){
        g_board[character.x_pos][character.y_pos] = '.';

        if(command == "up"){
            if(!stop(character, gameboard, 'u')){
                char next = next_item(gameboard, character, 'u', all_characters);
                if(next == ' '){
                    character.move_up();
                }
                else if (next >= 48 && next <= 58 )
                {
                    //Alien hits a zombie
                    Character victim;
                    for(int i = 0; i < all_characters.size(); i++){
                        if(all_characters[i].name == next){
                            victim = all_characters[i];
                            victim.gotHit(character.impact);
                            if(victim.alive){
                                cout << victim.name << " Got hit and survived!" << endl;
                                break;
                            }else{
                                cout << victim.name << " was attacked and killed!" << endl;
                                character.move_up();
                            }
                        }
                    }
                }
                else if (next == '^')
                {
                    character.move_up();
                    command = 'up';
                }else if (next == 'v')
                {
                    character.move_up();
                    command = 'down';
                }else if (next == '>')
                {
                    character.move_up();
                    command = 'right';
                }
                else if (next == '<')
                {
                    character.move_up();
                    command = 'left';
                }
                
                
            }
        }
        
    }


    
    while (a_ctrl == 0)
    {
        if (turn == 'a')
        {
            g_board[character.x_pos][character.y_pos] = '.';
        }
        else
        {
            g_board[character.x_pos][character.y_pos] = ' ';
        }

        string a_control;
        cout << "command > ";
        cin >> a_control;
        if (a_control == "up")
        {
            if (stop(character, gameboard, 'u'))
            {
                cout << "You cannot move up anymore!" << endl;
            }
            else
            {
                char next = next_item(gameboard, character, 'u', );
                if (int(next) >= 48 || int(next) <= 58)
                {

                }

                character.move_up();
                g_board[character.x_pos][character.y_pos] = character.name;
                system("CLS");
                gameboard.showGameboard();
            }
        }
        else if (a_control == "down")
        {
            if (stop(character, gameboard, 'd'))
            {
                cout << "You cannot move down anymore!" << endl;
            }
            else
            {
                character.move_down();
                g_board[character.x_pos][character.y_pos] = character.name;
                system("CLS");
                gameboard.showGameboard();
            }
        }
        else if (a_control == "left")
        {
            if (stop(character, gameboard, 'l'))
            {
                cout << "You cannot move left anymore!" << endl;
            }
            else
            {
                character.move_left();
                g_board[character.x_pos][character.y_pos] = character.name;
                system("CLS");
                gameboard.showGameboard();
            }
        }
        else if (a_control == "right")
        {
            if (stop(character, gameboard, 'r'))
            {
                cout << "you cannot move right anymore!" << endl;
            }
            else
            {
                character.move_right();
                g_board[character.x_pos][character.y_pos] = character.name;
                system("CLS");
                gameboard.showGameboard();
            }
        }
        else if (a_control == "help")
        {
            cout << "\nCommands" << endl;
            cout << "1. up    - Move up.\n"
                    "2. down  - Move down.\n"
                    "3. left  - Move left.\n"
                    "4. right - Move right.\n"
                    "5. arrow - Change the direction of arrow.\n"
                    "6. help  - Display all the user commands.\n"
                    "7. save  - Save game.\n"
                    "8. load  - Load a game.\n"
                    "9. quit  - Quit game.\n";
            system("pause");
            cout << "\n";
        }
        else if (a_control == "save")
        {
            // save
        }
        else if (a_control == "load")
        {
            // load
        }
        else if (a_control == "quit")
        {
            a_ctrl = a_ctrl + 1;
        }
        else
        {
            cout << "Invalid input. Please try again." << endl;
            
        }
    }
}


std::vector<Character> generate_characters(Gameboard gm, int zombies_count){
    int x_dim = gm.rows;
    int y_dim = gm.columns;
    int total_zombies = zombies_count;
    // Determine the other character quantities according to the board size
    int total_health = random(int(x_dim * y_dim * 0.08));
    if (total_health < int(x_dim * y_dim * 0.05))
        total_health = int(x_dim * y_dim * 0.05);

    int total_arrows = random(int(x_dim * y_dim * 0.4));
    if (total_arrows < int(x_dim * y_dim * 0.3))
        total_arrows = int(x_dim * y_dim * 0.3);

    int total_rocks = random(int(x_dim * y_dim * 0.15));
    if (total_rocks < int(x_dim * y_dim * 0.1))
        total_rocks = int(x_dim * y_dim * 0.1);

    int total_pods = random(int(x_dim * y_dim * 0.2));
    if (total_pods < int(x_dim * y_dim * 0.10))
        total_pods = int(x_dim * y_dim * 0.10);

    // Create the zombies character list and put them on the board
    Character zombies[total_zombies];
    for (int i = 0; i < total_zombies; i++)
    {
        Zombie z = Zombie(i + 48, 200);
        zombies[i] = z;
        place_character(gm, z);
    };

    // Create arrows and place them on the board
    Character arrows[total_arrows];
    for (int i = 0; i < total_arrows; i++)
    {
        Arrow ar = Arrow();
        arrows[i] = ar;
        place_character(gm, ar);
    }

    // Create healths and place them on the board
    Character healts[total_health];
    for (int i = 0; i < total_health; i++)
    {
        Health h = Health();
        healts[i] = h;
        place_character(gm, h);
    }

    // Create rocks and place on the board
    Character rocks[total_rocks];
    for (int i = 0; i < total_rocks; i++)
    {
        Rock r = Rock(20);
        rocks[i] = r;
        place_character(gm, r);
    }

    // Create pods and place on the board
    Character pods[total_pods];
    for (int i = 0; i < total_pods; i++)
    {
        Pod p = Pod(random(4));
        pods[i] = p;
        place_character(gm, p);
    }

    // Create a vector for all the game characters
    vector< Character > all_characters;

    // Put in all the zombies in the list
    for(int  i = 0; i < total_zombies;  i++){
    all_characters.push_back(zombies[i]);}

    // Put all the arrows in the vector
    for(int i = 0; i < total_arrows; i++){
        all_characters.push_back(arrows[i]);
    }

    //Put all the healths in the vector
    for(int i = 0; i < total_health; i++){
        all_characters.push_back(healts[i]);
    }

    // Put all the pods in the vector
    for(int i = 0; i< total_pods; i++){
        all_characters.push_back(pods[i]);
    }

    //Put all the rocks in the vector
    for(int i = 0; i < total_rocks; i++){
        all_characters.push_back(rocks[i]);
    }

    return all_characters;
}

main()
{
    srand(time(0));

    // Create default setting for game
    int alien_life = 200;
    int alien_impact = 20;
    int total_zombies = 5;
    int x_dim = 17;
    int y_dim = 5;

    std::string answer;

    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows     : " << y_dim << endl;
    cout << "Board Columns  : " << x_dim << endl;
    cout << "Zombie Count   : " << total_zombies << endl;

    // create loop for user to repeat input if the user enters wrongly.
    while (true)
    {
        cout << "\nDo you wish to change the game settings (y/n)? => ";
        cin >> answer;
        // redirect to new screen
        system("CLS");
        if (answer == "y")
        // redirect to user to create own setting
        {
            // Get the user inputs from boardsetting.h
            int *new_settings = Board_Setting();
            x_dim = new_settings[0];
            y_dim = new_settings[1];
            total_zombies = new_settings[2];
        }
        // generate gameboard using default setting
        else if (answer == "n")
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    // Determine the middle point of the game board
    int alien_row_pos = ((y_dim * 2) + 1) / 2;
    int alien_col_pos = ((x_dim * 2) + 1) / 2;

    // Create the alien object and set it's positions to the middle of the board
    Alien alien = Alien(alien_life, alien_impact);
    alien.x_pos = alien_row_pos;
    alien.y_pos = alien_col_pos;

        // Generate the gameboard depending on the users input and Gameboard class
    Gameboard gm = Gameboard(y_dim, x_dim);
    char **g_board = gm.board;

    // place the alien on the board
    g_board[alien.x_pos][alien.y_pos] = alien.name;

    vector<Character> all_characters = generate_characters(gm, total_zombies);
    all_characters.insert(all_characters.begin(), alien);

    for(int i = 0; i < all_characters.size(); i++){
        cout << all_characters[i].name << ": " << all_characters[i].life << endl;
    }


    gm.showGameboard();
}
