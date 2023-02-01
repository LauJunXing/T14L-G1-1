// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: T14L 
// Names: KAWSAR | MEMBER_NAME_2 | MEMBER_NAME_3 
// IDs: 1211310827 | MEMBER_ID_2 | MEMBER_ID_3 
// Emails: mdrisveyhasan1@gmail.com | MEMBER_EMAIL_2 | MEMBER_EMAIL_3 
// Phones: +601169727851 | MEMBER_PHONE_2 | MEMBER_PHONE_3 
// ********************************************************* 


/* --HOW TO USE--
Gameboard:
The gameboard class would create an empty gameboard with the provided dimantions to the class constructor.
Create a gameboard: Gameboard board_name = Gamaboard(int number_of_rows, int number_of_cols);
The gameboard has 5 different properties respectively columns, rows, total_cols, total_rows and the pointer to the 2D array of the actual gameboard namely "board".
The board will have 2*provided_rows + 1 rows and 2*provided_cols + 1 columns in total.
Within these rows and columns only the odd places would be empty for game characters.

Example: Let's say you want to put a zombie in the first top right corner of the board, you can access the top right corner with board[1][1] selector and you can set it to whatever you want.

Showing the gameboard: The Gameboard object will have a default showGameboard() method that will allow you to show the gameboard as it is.
Example: board_name.showGameboard();

Characters:
All the characters will have some common characteristics as below:
char name: name of the character
int life: total life of the character
int impact: hit impact of the character
int x_pos: character position on the x dimension
int y_pos: character position on the y dimension
bool alive: if the character is alive after getting hit

Also they will have the common movement method.
Movement methods:
move_up();
move_down();
move_right();
move_left();
Note: Every time you move the charater, it will move by 2 rows or columns as the board itself has it's own elements occopying certain places on the board.

Beside movements they will have a gotHit method calling which would change the life of the character according to the hit impact and set the "alive" property as "false" if the life becomes < 0.

Alien:
Beside the common characteristics, alien would have its "int max_life" and "int attacs".
The name is set to 'A' as default.
methods:
Beside the common methods described earlier it would have the below methods:
addLife(): This method will increase the life of the alien till max_life with the provided increment.
attacked(): This will increase the "attacks" number by one.

Example:
Create the alien object:- Alien alien_name = Alien(int set_maxLife, int set_impact, int set_x, int set_y);
Get name:- alien_name.name;
Get x position:- alien_name.x_pos;
Add life:- alien_name.addLife();
Increase attakcs number:- alien_name.attacked();
Got hit:- alien_name.gotHit();
Move:- alien_name.move_up();

Zombie:
It would have all the common characteristics and methods described in the Characters section.
Example:
Create a zombie object:- Zombie zombie_name = Zombie(char set_name, int alienLife, int set_x, int set_y);
Get x position:- zombie_name.x_pos;
Get name:- zombie_name.name;
Got hit:- zombie_name.gotHit();


Rock:
It will have all the common characteristics.
Beside common methods it will have reveal() method to reveal its hidden item. The hidden item would be picked up randomly and returned as a char value. You will have to create a new game object based on the returned char value and put it back to the gaemboard on the same place as the rock holds.
Example:
You cna create and access the properties of the object following previous examples.

Pod:
Beside common characteristics it would have an attack_radius, you will have to set the radious as you create the object.
The name is set to 'P' as default.
The impact is set to 10 as default.
Example:
You cna create and access the properties of the object following previous examples.
*/

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Define a random number generator from 0 to a certain limit
int random(int limit)
{
    srand(time(0));
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

        board = new char*[total_rows];

        for (int row = 0; row < total_rows; row++)
        {
            board[row] = new char[total_cols];
            for (int col = 0; col < total_cols; col++)
            {
                if(row == 0 || row == total_rows || row % 2 == 0)
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
                if(col == total_cols && row != 0 && row % 2 != 0){
                    cout << int(row / 2) + 1;
                }else if (col == total_cols && row % 2 ==0)
                {
                    cout <<' ';
                }
                else{
                cout << board[row][col];
                }
            };
            cout << endl;
        };

        // Show the navigation row
        int nav_row = 1;
        if (columns > 9)
        nav_row = 2;
        for(int row = 0; row < nav_row; row++){
            int col_count = 0;
            for(int col = 0; col < total_cols; col++){
                if(col % 2 != 0 && row == 0){
                    if(int(col / 2) < 9){
                        cout << int(col / 2) + 1;
                    }else{
                        cout<<(int((col + 1) / 2) / 10);
                    }
                }else if (row > 0 && col / 2 >= 9 && col % 2 != 0)
                {   
                    cout << ((col / 2) - ceil(col_count / 10) * 10 + 1) - 10;
                    col_count ++;
                }
                
                else
                {
                    cout<<' ';
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
    int life;
    int impact;
    int x_pos, y_pos;
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
    Alien(int set_maxLife, int set_impact, int set_x, int set_y)
    {
        name = 'A';
        maxLife = set_maxLife;
        impact = set_impact;
        life = set_maxLife;
        x_pos = set_x;
        y_pos = set_y;
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
    Zombie(char set_name, int alienLife, int set_x, int set_y)
    {
        name = set_name;
        x_pos = set_x;
        y_pos = set_y;

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
    Rock(int alienImpact, int set_x, int set_y)
    {
        // Set the initial characteristics of a rock
        name = 'R';
        x_pos = set_x;
        y_pos = set_y;

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
class Pod : public Character{
    public:
        int attack_radius;
        int impact = 10;

        // Pod initializer
        Pod(int set_attact_radius, int set_x, int set_y){
            name = 'P';
            attack_radius = set_attact_radius;
            x_pos = set_x;
            y_pos = set_y;
        };
        

};


main()
{
    // Test above classes here
    int life = 200;
    int impact = 20;
    int total_zombies = 5;
    int total_health = 5;
    int total_arrows = 10;
    int x_dim = 19;
    int y_dim = 5;

    Alien alien = Alien(life, impact, 5, 17);


    Gameboard gm = Gameboard(y_dim, x_dim);
    char **g_board = gm.board;
    g_board[alien.x_pos][alien.y_pos] = alien.name;
    gm.showGameboard();
    cout << endl;
    g_board[alien.x_pos][alien.y_pos] = '.';
    alien.move_down();
    g_board[alien.x_pos][alien.y_pos] = alien.name;
    gm.showGameboard();
}
