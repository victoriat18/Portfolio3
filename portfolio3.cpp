//Final Portfolio, Spy Game
//Portfolio, Spy Game
#include <iostream>
#include <string>
#include <cctype>
#include <vector> //added
#include <fstream>
using namespace std;

// LEVEL 1 : A New Enemy, Basic Beginner level (One door & one switch)
//standard flip & still guard
void loadLevel1() 
{
    //HOW TO...
    cout << "   Level 1 loaded - Beginner Level    " << endl;
    cout << "   -----  Directions  -----    " << endl;
    cout << "Reach the $ without being seen, Move using WASD." << endl;
    cout << "Type 'inspect' to check what is on a tile (doesn't use a turn)." << endl;
    cout << "Walk onto switches (S) to toggle doors (D)." << endl;
    cout << "Watch out for both patrolling and stationary guards." << endl;
    cout << "Guards only watch where they're facing." << endl;
    cout << "----------------------------------------------" << endl;

    string map[5] =
    {
    "########",
    "#      #",
    "#  #   #",
    "# S  D$#",
    "########"
    };
    int playerX = 1;
    int playerY = 1;
    // Guard starts here
    int guardX = 2;
    int guardY = 6;
    // Guard moving left
    int guardDX = 0;
    int guardDY = -1;
    //STILL GUARD (stays still)
    int stillGuardX = 2;
    int stillGuardY = 5;
    char stillGuardSymbol = '>';

    char guardSymbol = '<';
//~ DOOR FEATURE
    bool doorOpen = false;
    //bool door2Open = false;

    string input;
    while (true)
    {
// PRINT MAP
for (int i = 0; i < 5; i++)
    {
    for (int j = 0; j < 8; j++)
    {
       if (i == playerX && j == playerY)
    {
    cout << '@';
    }
    else if (i == stillGuardX && j == stillGuardY)
    {
    cout << stillGuardSymbol;
    }   
    else if (i == guardX && j == guardY)
    {
    cout << guardSymbol;
    }   
        else if (map[i][j] == 'D' && doorOpen)
        {
            cout << ' ';
        }
        else
        {
            cout << map[i][j];
        }
    }
    cout << endl;
}

        cout << "Move (WASD) or type 'inspect': ";
        cin >> input;

        // INSPECT FEATURE
        if (input == "inspect")
        {
            int row;
            int col;


            cout << "Enter row: ";
            cin >> row;

            cout << "Enter column: ";
            cin >> col;

            if(row < 0 || row >= 5 || col < 0 || col >= 8)
            {
                cout << "Invalid location.\n";
                continue;
            }
    if (row == stillGuardX && col == stillGuardY)
{
    cout << "Stationary guard facing " << stillGuardSymbol << endl;
}
else if (row == guardX && col == guardY)
{
    cout << "Patrolling guard facing " << guardSymbol << endl;
}
else if(map[row][col] == '#')
{
    cout << "Wall." << endl;
}
else if(map[row][col] == 'D')
{
    if (doorOpen)
    {
        cout << "Open door." << endl;
    }
    else
    {
        cout << "Closed door." << endl;
    }
}
else if(map[row][col] == 'S')
{
    cout << "Switch." << endl;
}
else if(map[row][col] == '$')
{
    cout << "Goal." << endl;
}
else
{
    cout << "Empty tile." << endl;
}
    continue;
        }
        int newX = playerX;
        int newY = playerY;

        if(input != "w" && input != "a" &&
           input != "s" && input != "d")
        {
            cout << "Invalid input.\n";
            continue;
        }
        if(input == "w") newX--;
        if(input == "s") newX++;
        if(input == "a") newY--;
        if(input == "d") newY++;
        //PLAYER WALKS INTO GUARD
        if ((newX == guardX && newY == guardY) || (newX == stillGuardX && newY == stillGuardY))
{
    cout << "YOU WERE CAUGHT!" << endl;
    return;
}
        //WIN
        if(map[newX][newY] == '$')
        {
            cout << "YOU WIN LEVEL 1!" << endl;
            return;
        }
   //MOVE PLAYER
    if (map[newX][newY] != '#' &&
    (map[newX][newY] != 'D' || doorOpen))
{
    playerX = newX;
    playerY = newY;
    //Switch
   if (map[playerX][playerY] == 'S')
{
    doorOpen = !doorOpen;
    cout << "Door toggled!" << endl;
    }
}
else
{
    cout << "You hit a wall or a closed door." << endl;
    continue;
}

    //GUARD PATROL & boundaries
    int nextX = guardX + guardDX;
    int nextY = guardY + guardDY;
    bool outOfBounds = (nextX < 0 || nextX >= 5 || nextY < 0 || nextY >= 8);

if (outOfBounds || map[nextX][nextY] == '#' || (map[nextX][nextY] == 'D' && !doorOpen) ||(nextX == stillGuardX && nextY == stillGuardY))
{
    // Left -> Up
    if (guardDX == 0 && guardDY == -1)
    {
        guardDX = -1;
        guardDY = 0;
        guardSymbol = '^';
    }
    // Up -> Right
    else if (guardDX == -1 && guardDY == 0)
    {
        guardDX = 0;
        guardDY = 1;
        guardSymbol = '>';
    }
    // Right -> Down
    else if (guardDX == 0 && guardDY == 1)
    {
        guardDX = 1;
        guardDY = 0;
        guardSymbol = 'V';
    }
    // Down -> Left
    else
    {
        guardDX = 0;
        guardDY = -1;
        guardSymbol = '<';
    }
}
else
{
    guardX = nextX;
    guardY = nextY;
}
        // Guard activates switch
    if (map[guardX][guardY] == 'S')
{
    doorOpen = !doorOpen;
    cout << "Guard toggled the door!" << endl;
}
        // GUARD WALKS INTO PLAYER
        if(playerX == guardX && playerY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }

// GUARD VISION
if (guardSymbol == '<')
{
    // Look left
    for (int y = guardY - 1; y >= 0; y--)
    {
        if (map[guardX][y] == '#' ||
            (map[guardX][y] == 'D' && !doorOpen))
            break;

        if (guardX == playerX && y == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
else if (guardSymbol == '>')
{
    // Look right
    for (int y = guardY + 1; y < 8; y++)
    {
        if (map[guardX][y] == '#' ||
            (map[guardX][y] == 'D' && !doorOpen))
            break;

        if (guardX == playerX && y == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
else if (guardSymbol == '^')
{
    // Look up
    for (int x = guardX - 1; x >= 0; x--)
    {
        if (map[x][guardY] == '#' ||
            (map[x][guardY] == 'D' && !doorOpen))
            break;

        if (x == playerX && guardY == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
else if (guardSymbol == 'V')
{
    // Look down
    for (int x = guardX + 1; x < 5; x++)
    {
        if (map[x][guardY] == '#' ||
            (map[x][guardY] == 'D' && !doorOpen))
            break;

        if (x == playerX && guardY == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
// STATIONARY GUARD VISION (faces right)
for (int y = stillGuardY + 1; y < 8; y++)
{
    if (map[stillGuardX][y] == '#' ||
        (map[stillGuardX][y] == 'D' && !doorOpen))
    {
        break;
    }

    if (stillGuardX == playerX && y == playerY)
    {
        cout << "YOU WERE CAUGHT!" << endl;
        return;
    }
}
    } 
}

// LEVEL 2: The Truth of the Weapon, DIFFERENT MAP! (Multiple Doors)
void loadLevel2() 
{
    //map loaded
    cout << "   Level 2 loaded - Simple Level  " << endl;
    cout << "   -----   Directions  -----   " << endl;
    cout << "This mission has multiple doors. One switch controls multiple Doors." << endl;
    cout << "Reach the $ without being seen by the guard." << endl;
    cout << "Inspect tiles if you need more information." << endl;
    cout << "Walk onto switches (S) to open doors (D)." << endl;
    cout << "----------------------------------------------" << endl;
string map[5] =
{
    "########",
    "# D    #",
    "# ## # #",
    "# S  D$#",
    "########"
};
    int playerX = 1;
    int playerY = 1;
    // Guard starts here
    int guardX = 1;
    int guardY = 5;
    // Guard moving left
    int guardDX = 0;
    int guardDY = -1;
    char guardSymbol = '<';
//DOOR FEATURE
    bool doorOpen = false;

    string input;

    while (true)
    {
// PRINT MAP
for (int i = 0; i < 5; i++)
    {
    for (int j = 0; j < 8; j++)
    {
        if (i == playerX && j == playerY)
        {
            cout << '@';
        }
        else if (i == guardX && j == guardY)
        {
            cout << guardSymbol;
        }
        else if (map[i][j] == 'D' && doorOpen)
        {
            cout << ' ';
        }
        else
        {
            cout << map[i][j];
        }
    }
    cout << endl;
}

        cout << "Move (WASD) or type'inspect': ";
        cin >> input;

        //INSPECT FEATURE
        if (input == "inspect")
        {
            int row;
            int col;

            cout << "Enter row: ";
            cin >> row;

            cout << "Enter column: ";
            cin >> col;

            if(row < 0 || row >= 5 || col < 0 || col >= 8)
            {
                cout << "Invalid location.\n";
                continue;
            }


if(row == guardX && col == guardY)
{
    cout << "Guard facing " << guardSymbol << endl;
}
else if(map[row][col] == '#')
{
    cout << "Wall." << endl;
}
else if(map[row][col] == 'D')
{
    if (doorOpen)
    {
        cout << "Open door." << endl;
    }
    else
    {
        cout << "Closed door." << endl;
    }
}
else if(map[row][col] == 'S')
{
    cout << "Switch." << endl;
}
else if(map[row][col] == '$')
{
    cout << "Goal." << endl;
}
else
{
    cout << "Empty tile." << endl;
}
continue;
        }
        int newX = playerX;
        int newY = playerY;


        if(input != "w" && input != "a" &&
           input != "s" && input != "d")
        {
            cout << "Invalid input.\n";
            continue;
        }
        if(input == "w") newX--;
        if(input == "s") newX++;
        if(input == "a") newY--;
        if(input == "d") newY++;
        //PLAYER WALKS INTO GUARD
        if(newX == guardX && newY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
        //WIN
        if(map[newX][newY] == '$')
        {
            cout << "YOU WIN LEVEL 2!" << endl;
            return;
        }
        //MOVE PLAYER
      if (map[newX][newY] != '#' && (map[newX][newY] != 'D' || doorOpen))
        {
        playerX = newX;
        playerY = newY;

    if (map[playerX][playerY] == 'S')
{
    if (!doorOpen)
    {
        doorOpen = true;
        cout << "Door toggled!" << endl;
        }
    }
}
else 
{
    cout << "You hit a wall or a closed door!" << endl;
    continue;
}
// Checking Out of Bounds
int nextX = guardX + guardDX;
int nextY = guardY + guardDY;

bool outOfBounds =
    (nextX < 0 || nextX >= 5 ||
     nextY < 0 || nextY >= 8);

// Hit wall, closed door, or edge = turn clockwise
// Hit wall, closed door, or edge = turn clockwise
if (outOfBounds ||
    map[nextX][nextY] == '#' ||
    (map[nextX][nextY] == 'D' && !doorOpen))
{
    // Left -> Up
    if (guardDX == 0 && guardDY == -1)
    {
        guardDX = -1;
        guardDY = 0;
        guardSymbol = '^';
    }
    // Up -> Right
    else if (guardDX == -1 && guardDY == 0)
    {
        guardDX = 0;
        guardDY = 1;
        guardSymbol = '>';
    }
    // Right -> Down
    else if (guardDX == 0 && guardDY == 1)
    {
        guardDX = 1;
        guardDY = 0;
        guardSymbol = 'V';
    }
    // Down -> Left
    else
    {
        guardDX = 0;
        guardDY = -1;
        guardSymbol = '<';
    }
}
else
{
    guardX = nextX;
    guardY = nextY;
}

        //GUARD WALKS INTO PLAYER
        if(playerX == guardX && playerY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
        //Guard vision
if (guardSymbol == '<')
{
    //look left
    for (int y = guardY - 1; y >= 0; y--)
    {
        if (map[guardX][y] == '#' || (map[guardX][y] == 'D' && !doorOpen))
            break;
        if (guardX == playerX && y == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
else if (guardSymbol == '>')
{
    //look right
    for (int y = guardY + 1; y < 8; y++)
    {
        if (map[guardX][y] == '#' || (map[guardX][y] == 'D' && !doorOpen))
        {
        break;     
        }
        if (guardX == playerX && y == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
else if (guardSymbol == '^')
{
    //look up
    for (int x = guardX - 1; x >= 0; x--)
    {
        if (map[x][guardY] == '#' ||
    (map[x][guardY] == 'D' && !doorOpen))
{
    break;
}
        if (x == playerX && guardY == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
    }
}
else if (guardSymbol == 'V')    
    {
    //look down
    for (int x = guardX + 1; x < 5; x++)
    {
        if (map[x][guardY] == '#' ||
    (map[x][guardY] == 'D' && !doorOpen))
    {
    break;
    }
        if (x == playerX && guardY == playerY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
                }
            }
        }   
    }
}

// LEVEL 3: Revenge of the General, DIFFERENT MAP! (Guard walks over switch & multiple doors/switch)
void loadLevel3() 
{
    cout << "   Level 3 loaded - Medium Level  " << endl;
    cout << "   -----  Directions  -----    " << endl;
    cout << "Watch the guard carefully!" << endl;
    cout << "Guards can activate switches just like you." << endl;
    cout << "Doors may open or close during the mission." << endl;
    cout << "Plan your route and reach '$' safely." << endl;
    cout << "----------------------------------------------" << endl;

    string map[5] =
{
    "########",
    "#   D S#",
    "# ## # #",
    "#    D$#",
    "########"
};

    // Variables for guard and player
    int playerX = 1;
    int playerY = 1;
    
    // Guard starts here
    int guardX = 2;
    int guardY = 6;
    
    // Guard moving left initially
    int guardDX = 0;
    int guardDY = -1;
    char guardSymbol = '<';

    // DOOR FEATURE
    bool doorOpen = false;
    string input;

    while (true)
    {
        // PRINT MAP
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (i == playerX && j == playerY)
                {
                    cout << '@';
                }
                else if (i == guardX && j == guardY)
                {
                    cout << guardSymbol;
                }
                else if (map[i][j] == 'D' && doorOpen)
                {
                    cout << ' ';
                }
                else
                {
                    cout << map[i][j];
                }
            }
            cout << endl;
        }

        cout << "Move (WASD) or type 'inspect': ";
        cin >> input;

        // INSPECT FEATURE
        if (input == "inspect")
        {
            int row;
            int col;

            cout << "Enter row: ";
            cin >> row;

            cout << "Enter column: ";
            cin >> col;

            if (row < 0 || row >= 5 || col < 0 || col >= 8)
            {
                cout << "Invalid location.\n";
                continue;
            }
            
            if (row == guardX && col == guardY)
            {
                cout << "Guard facing " << guardSymbol << ". Turns clockwise when hits obstacle" << endl;
            }
            else if (map[row][col] == '#')
            {
                cout << "Wall." << endl;
            }
            else if (map[row][col] == 'D')
            {
                if (doorOpen)
                {
                    cout << "Open door." << endl;
                }
                else
                {
                    cout << "Closed door." << endl;
                }
            }
            else if (map[row][col] == 'S')
            {
                cout << "Switch controlling door group 1." << endl;
            }
            else if (map[row][col] == '$')
            {
                cout << "Goal." << endl;
            }
            else
            {
                cout << "Empty tile." << endl;
            }
            continue;
        }

        int newX = playerX;
        int newY = playerY;

        if (input != "w" && input != "a" && input != "s" && input != "d")
        {
            cout << "Invalid input.\n";
            continue;
        }

        if (input == "w") newX--;
        if (input == "s") newX++;
        if (input == "a") newY--;
        if (input == "d") newY++;

        // PLAYER WALKS INTO GUARD
        if (newX == guardX && newY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }

        // WIN
        if (map[newX][newY] == '$')
        {
            cout << "YOU WIN LEVEL 3!" << endl;
            return;
        }

        // MOVE PLAYER
        if (map[newX][newY] != '#' && (map[newX][newY] != 'D' || doorOpen))
        {
            playerX = newX;
            playerY = newY;

    if (map[playerX][playerY] == 'S')
    {
        doorOpen = !doorOpen;
        cout << "You stepped on the switch! Door toggled!" << endl;
            }
        }
        else
        {
            cout << "You hit a wall or a closed door!" << endl;
            continue;
        }

        // GUARD PATROL
        int nextX = guardX + guardDX;
        int nextY = guardY + guardDY;

        // Check if next step would leave map bounds
        bool outOfBounds = (nextX < 0 || nextX >= 5 || nextY < 0 || nextY >= 8);

        // Hit wall, closed door, or out-of-bounds = turn clockwise
        if (outOfBounds || map[nextX][nextY] == '#' || (map[nextX][nextY] == 'D' && !doorOpen))
        {
            // Left -> Up
            if (guardDX == 0 && guardDY == -1)
            {
                guardDX = -1;
                guardDY = 0;
                guardSymbol = '^';
            }
            // Up -> Right
            else if (guardDX == -1 && guardDY == 0)
            {
                guardDX = 0;
                guardDY = 1;
                guardSymbol = '>';
            }
            // Right -> Down
            else if (guardDX == 0 && guardDY == 1)
            {
                guardDX = 1;
                guardDY = 0;
                guardSymbol = 'V';
            }
            // Down -> Left
            else
            {
                guardDX = 0;
                guardDY = -1;
                guardSymbol = '<';
            }
        }
        else 
        {
            // Only step forward if the path was clear and the guard didn't turn
            guardX = nextX;
            guardY = nextY;
        }
    // Guard activates the switch
    if (map[guardX][guardY] == 'S')
    {
    doorOpen = !doorOpen;
    cout << "Guard stepped on the switch! Door toggled!" << endl;
}
        // GUARD WALKS INTO PLAYER
        if (playerX == guardX && playerY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
        // GUARD VISION
        if (guardSymbol == '<')
        {
            // Look left
            for (int y = guardY - 1; y >= 0; y--)
            {
                if (map[guardX][y] == '#' || (map[guardX][y] == 'D' && !doorOpen))
                    break;
                if (guardX == playerX && y == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }
        else if (guardSymbol == '>')
        {
            // Look right
            for (int y = guardY + 1; y < 8; y++)
            {
                if (map[guardX][y] == '#' || (map[guardX][y] == 'D' && !doorOpen))
                    break; 
                if (guardX == playerX && y == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }
        else if (guardSymbol == '^')
        {
            // Look up
            for (int x = guardX - 1; x >= 0; x--)
            {
                if (map[x][guardY] == '#' || (map[x][guardY] == 'D' && !doorOpen))
                    break;
                if (x == playerX && guardY == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }
        else if (guardSymbol == 'V')    
        {
            // Look down
            for (int x = guardX + 1; x < 5; x++)
            {
                if (map[x][guardY] == '#' || (map[x][guardY] == 'D' && !doorOpen))
                    break;
                if (x == playerX && guardY == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }   
    }
}
//LEVEL 4: Guard Colored Doors, Different requirement (Complex one)
//This level has multi-color doors
void loadLevel4(){
    cout << "   Level 4 loaded - Hard    " << endl;
    cout << "   -----   Directions  -----   " << endl;
    cout << "This Mission features multiple switch groups." << endl;
    cout << "Red switches (r) control Red doors (R)." << endl;
    cout << "Blue Switches (b) control Blue doors (B)." << endl;
    cout << "Guards can also activate colored switches." << endl;
    cout << "Think ahead, avoid detection, and reach the '$'." << endl;
    cout << "----------------------------------------------" << endl;

    string map[5] = {
        "########",
        "# r R  #",
        "#   #  #",
        "# b B$ #",
        "########"
    };
    
    int playerX = 1;
    int playerY = 1;
    
    // Guard starts here
    int guardX = 2;
    int guardY = 6;
    // Guard moving left initially
    int guardDX = 0;
    int guardDY = -1;
    char guardSymbol = '<';

    //DOOR FEATURE, COLORS IMPLIMENTED
    bool redDoorOpen = false;
    bool blueDoorOpen = false;

    string input;
    while (true)
    {
        // PRINT MAP
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == playerX && j == playerY) {
                    cout << '@';
                }
                else if (i == guardX && j == guardY) {
                    cout << guardSymbol;
                }
                else if (map[i][j] == 'R' && redDoorOpen) {
                    cout << ' ';
                }
                else if (map[i][j] == 'B' && blueDoorOpen) {
                    cout << ' ';
                }
                else {
                    cout << map[i][j];
                }
            }
            cout << endl;
        }

        cout << "Move (WASD) or type 'inspect': ";
        cin >> input;

        // INSPECT FEATURE
        if (input == "inspect") {
            int row, col;
            cout << "Enter row: ";
            cin >> row;
            cout << "Enter column: ";
            cin >> col;

            if(row < 0 || row >= 5 || col < 0 || col >= 8) {
                cout << "Invalid location.\n";
                continue;
            }

            if(row == guardX && col == guardY) {
                cout << "Guard facing " << guardSymbol << " (Patrols Clockwise)." << endl;
            }
            else if(map[row][col] == '#') {
                cout << "Wall." << endl;
            }
            else if(map[row][col] == 'R') {
                cout << "Red Door (" << (redDoorOpen ? "Open" : "Closed") << ")." << endl;
            }
            else if(map[row][col] == 'B') {
                cout << "Blue Door (" << (blueDoorOpen ? "Open" : "Closed") << ")." << endl;
            }
            else if(map[row][col] == 'r') {
                cout << "Red Switch." << endl;
            }
            else if(map[row][col] == 'b') {
                cout << "Blue Switch." << endl;
            }
            else if(map[row][col] == '$') {
                cout << "Goal." << endl;
            }
            else {
                cout << "Empty tile." << endl;
            }
            continue; // Turn is not used
        }
        // MOVEMENT PROCESSING
        int newX = playerX;
        int newY = playerY;

        if(input != "w" && input != "a" && input != "s" && input != "d") {
            cout << "Invalid input.\n";
            continue;
        }
        if(input == "w") newX--;
        if(input == "s") newX++;
        if(input == "a") newY--;
        if(input == "d") newY++;
        // PLAYER WALKS INTO GUARD
        if(newX == guardX && newY == guardY) {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }
        // WIN CONDITION
        if(map[newX][newY] == '$') {
            cout << "YOU WIN LEVEL 4!" << endl;
            return;
        }
        // CHECK WALLS AND CLOSED DOORS FOR PLAYER
        bool isRedDoorClosed = (map[newX][newY] == 'R' && !redDoorOpen);
        bool isBlueDoorClosed = (map[newX][newY] == 'B' && !blueDoorOpen);

        if (map[newX][newY] != '#' && !isRedDoorClosed && !isBlueDoorClosed) {
            playerX = newX;
            playerY = newY;

            // Player Toggles Switches
            if (map[playerX][playerY] == 'r') {
                redDoorOpen = !redDoorOpen;
                cout << "Red door toggled!\n";
            }
            if (map[playerX][playerY] == 'b') {
                blueDoorOpen = !blueDoorOpen;
                cout << "Blue door toggled!\n";
            }
        }
        else {
            cout << "You hit a wall or a closed door." << endl;
            continue;
        }

        // GUARD PATROL LOGIC
        int nextX = guardX + guardDX;
        int nextY = guardY + guardDY;
        
        bool guardHitRedDoor = (map[nextX][nextY] == 'R' && !redDoorOpen);
        bool guardHitBlueDoor = (map[nextX][nextY] == 'B' && !blueDoorOpen);

        // Hit wall or closed door = turn clockwise
        if(map[nextX][nextY] == '#' || guardHitRedDoor || guardHitBlueDoor) {
            // Left -> Up
            if(guardDX == 0 && guardDY == -1) {
                guardDX = -1; guardDY = 0; guardSymbol = '^';
            }
            // Up -> Right
            else if(guardDX == -1 && guardDY == 0) {
                guardDX = 0; guardDY = 1; guardSymbol = '>';
            }
            // Right -> Down
            else if(guardDX == 0 && guardDY == 1) {
                guardDX = 1; guardDY = 0; guardSymbol = 'V';
            }
            // Down -> Left
            else {
                guardDX = 0; guardDY = -1; guardSymbol = '<';
            }
        }

        // Move guard forward after potentially turning
        guardX += guardDX;
        guardY += guardDY;

        // Guard Toggles Switches if they step on them
        if (map[guardX][guardY] == 'r') {
            redDoorOpen = !redDoorOpen;
            cout << "Guard stepped on Red Switch! Red door toggled!\n";
        }
        if (map[guardX][guardY] == 'b') {
            blueDoorOpen = !blueDoorOpen;
            cout << "Guard stepped on Blue Switch! Blue door toggled!\n";
        }

        // GUARD WALKS INTO PLAYER
        if(playerX == guardX && playerY == guardY) {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }

        // GUARD VISION SYSTEM
        if (guardSymbol == '<') {
            for (int y = guardY - 1; y >= 0; y--) {
                if (map[guardX][y] == '#' || (map[guardX][y] == 'R' && !redDoorOpen) || (map[guardX][y] == 'B' && !blueDoorOpen)) break;
                if (guardX == playerX && y == playerY) { cout << "YOU WERE CAUGHT!" << endl; return; }
            }
        }
        else if (guardSymbol == '>') {
            for (int y = guardY + 1; y < 8; y++) {
                if (map[guardX][y] == '#' || (map[guardX][y] == 'R' && !redDoorOpen) || (map[guardX][y] == 'B' && !blueDoorOpen)) break;
                if (guardX == playerX && y == playerY) { cout << "YOU WERE CAUGHT!" << endl; return; }
            }
        }
        else if (guardSymbol == '^') {
            for (int x = guardX - 1; x >= 0; x--) {
                if (map[x][guardY] == '#' || (map[x][guardY] == 'R' && !redDoorOpen) || (map[x][guardY] == 'B' && !blueDoorOpen)) break;
                if (x == playerX && guardY == playerY) { cout << "YOU WERE CAUGHT!" << endl; return; }
            }
        }
        else if (guardSymbol == 'V') {
            for (int x = guardX + 1; x < 5; x++) {
                if (map[x][guardY] == '#' || (map[x][guardY] == 'R' && !redDoorOpen) || (map[x][guardY] == 'B' && !blueDoorOpen)) break;
                if (x == playerX && guardY == playerY) { cout << "YOU WERE CAUGHT!" << endl; return; }
            }
        }  
    }
}
//LEVEL 5: Rectangle Guard, map is more complex
void loadLevel5()
{
    // WHAT TO DO! directions for player
    cout << "   Level 5 loaded - Rectangle Patrol" << endl;
    cout << "   ----- Directions -----" << endl;
    cout << "Observe the guard patrol in a rectangle" << endl;
    cout << "Wait for an opening, then reach the '$'." << endl;
    cout << "--------------------------------------" << endl;

    // Map updated to bigger size, with pillar. also doors/switches
string map[7] =
{
    "##########",
    "#   S    #",
    "#  ###   #",
    "#  ### $ #",
    "#  ###   #",
    "#   D    #",
    "##########"
};

    int playerX = 1;
    int playerY = 1;
    
    // Guard starts at the top, next to player. But the guard can't see the player!
    int guardX = 1;
    int guardY = 2;
    
    //Guard moving right, looking right
    int guardDX = 0;
    int guardDY = 1;
    char guardSymbol = '>';

    // DOOR FEATURE
    bool doorOpen = false;
    string input;

    while (true)
    {
        // PRINT MAP, boundaries match 7 map
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (i == playerX && j == playerY)
                {
                    cout << '@';
                }
                else if (i == guardX && j == guardY)
                {
                    cout << guardSymbol;
                }
                else if (map[i][j] == 'D' && doorOpen)
                {
                    cout << ' ';
                }
                else
                {
                    cout << map[i][j];
                }
            }
            cout << endl;
        }

        cout << "Move (WASD) or type 'inspect': ";
        cin >> input;

        // INSPECT FEATURE
        if (input == "inspect")
        {
            int row;
            int col;

            cout << "Enter row: ";
            cin >> row;

            cout << "Enter column: ";
            cin >> col;

            if (row < 0 || row >= 7 || col < 0 || col >= 10)
            {
                cout << "Invalid location.\n";
                continue;
            }
            
            if (row == guardX && col == guardY)
            {
                cout << "Guard facing " << guardSymbol << ". Turns clockwise when hits obstacle" << endl;
            }
            else if (map[row][col] == '#')
            {
                cout << "Wall." << endl;
            }
            else if (map[row][col] == 'D')
            {
                if (doorOpen)
                {
                    cout << "Open door." << endl;
                }
                else
                {
                    cout << "Closed door." << endl;
                }
            }
            else if (map[row][col] == 'S')
            {
                cout << "Switch controlling door group 1." << endl;
            }
            else if (map[row][col] == '$')
            {
                cout << "Goal." << endl;
            }
            else
            {
                cout << "Empty tile." << endl;
            }
            continue;
        }

        int newX = playerX;
        int newY = playerY;

        if (input != "w" && input != "a" && input != "s" && input != "d" &&
            input != "W" && input != "A" && input != "S" && input != "D")
        {
            cout << "Invalid input.\n";
            continue;
        }

        if (input == "w" || input == "W") newX--;
        if (input == "s" || input == "S") newX++;
        if (input == "a" || input == "A") newY--;
        if (input == "d" || input == "D") newY++;

        // PLAYER WALKS INTO GUARD
        if (newX == guardX && newY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }

        // WIN MESSAGE
        if (map[newX][newY] == '$')
        {
            cout << "YOU WIN LEVEL 5!" << endl;
            return;
        }

        // MOVE PLAYER
        if (map[newX][newY] != '#' && (map[newX][newY] != 'D' || doorOpen))
        {
            playerX = newX;
            playerY = newY;

            if (map[playerX][playerY] == 'S')
            {
                doorOpen = !doorOpen;
                cout << "You stepped on the switch! Door toggled!" << endl;
            }
        }
        else
        {
            cout << "You hit a wall or a closed door!" << endl;
            continue;
        }

        // GUARD PATROL
        int nextX = guardX + guardDX;
        int nextY = guardY + guardDY;

        // Check if next step would leave map bounds,
        bool outOfBounds = (nextX < 0 || nextX >= 7 || nextY < 0 || nextY >= 10);

        // Hit wall, closed door, or out-of-bounds = turn clockwise
        if (outOfBounds || map[nextX][nextY] == '#' || (map[nextX][nextY] == 'D' && !doorOpen))
        {
            // Left -> Up
            if (guardDX == 0 && guardDY == -1)
            {
                guardDX = -1;
                guardDY = 0;
                guardSymbol = '^';
            }
            // Up , Right
            else if (guardDX == -1 && guardDY == 0)
            {
                guardDX = 0;
                guardDY = 1;
                guardSymbol = '>';
            }
            // Right , Down
            else if (guardDX == 0 && guardDY == 1)
            {
                guardDX = 1;
                guardDY = 0;
                guardSymbol = 'V';
            }
            // Down , Left
            else
            {
                guardDX = 0;
                guardDY = -1;
                guardSymbol = '<';
            }
        }
        else 
        {
            guardX = nextX;
            guardY = nextY;
        }

        //Guard touches the switch
        if (map[guardX][guardY] == 'S')
        {
            doorOpen = !doorOpen;
            cout << "Guard stepped on the switch! Door toggled!" << endl;
        }

        // GUARD WALKS INTO PLAYER
        if (playerX == guardX && playerY == guardY)
        {
            cout << "YOU WERE CAUGHT!" << endl;
            return;
        }

        // GUARD VISION 
        if (guardSymbol == '<')
        {
            for (int y = guardY - 1; y >= 0; y--)
            {
                if (map[guardX][y] == '#' || (map[guardX][y] == 'D' && !doorOpen))
                    break;
                if (guardX == playerX && y == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }
        else if (guardSymbol == '>')
        {
            for (int y = guardY + 1; y < 10; y++)
            {
                if (map[guardX][y] == '#' || (map[guardX][y] == 'D' && !doorOpen))
                    break; 
                if (guardX == playerX && y == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }
        else if (guardSymbol == '^')
        {
            for (int x = guardX - 1; x >= 0; x--)
            {
                if (map[x][guardY] == '#' || (map[x][guardY] == 'D' && !doorOpen))
                    break;
                if (x == playerX && guardY == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }
        else if (guardSymbol == 'V')    
        {
            for (int x = guardX + 1; x < 7; x++)
            {
                if (map[x][guardY] == '#' || (map[x][guardY] == 'D' && !doorOpen))
                    break;
                if (x == playerX && guardY == playerY)
                {
                    cout << "YOU WERE CAUGHT!" << endl;
                    return;
                }
            }
        }   
    }
}

//LEVEL 6: CREATE YOUR OWN LEVEL, user creates their own level. 
//ALL input must be validated 
void loadCreateLevel(){
    string levelName;
    int rows;
    int cols;

    cout << "===== CREATE NEW LEVEL =====" << endl;
    cout << "Enter level name: ";
    cin >> levelName;
  //validate level name.
    while (levelName.empty())
    {
    cout << "Level name cannot be empty. Enter again: ";
    cin >> levelName;
    }   
    cout << "Enter number of rows: ";
    cin >> rows;
  
    //if user enters number
    while (rows <= 0)
    {
        cout << "Rows must be greater than 0. Enter again: ";
        cin >> rows;
    }
    cout << "Enter number of columns: ";
    cin >> cols;
    while (cols <= 0)
    {
        cout << "Columns must be greater than 0. Enter again: ";
        cin >> cols;
    }
    vector<string> map(rows, string(cols, ' '));

    cout << endl;
    cout << "Create level \"" << levelName << "\"" << endl;
    //Display map
    while (true)
{
    // Display the map
    cout << "\n  ";
    for (int j = 0; j < cols; j++)
    {
        cout << j << " ";
    }
        cout << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << i << " ";
        for (int j = 0; j < cols; j++)
        cout << map[i][j] << " ";
        cout << endl;
    }

    // Menu
    cout << "\nObjects:\n";
    cout << "1. Wall (#)\n";
    cout << "2. Player (@)\n";
    cout << "3. Goal ($)\n";
    cout << "4. Guard (G)\n";
    cout << "5. Door (D)\n";
    cout << "6. Switch (S)\n";
    cout << "7. Empty\n";
    cout << "8. Inspect\n";
    cout << "9. Save & Quit\n";

    int objectChoice;
    cout << "Choose object: ";
    cin >> objectChoice;

    if (objectChoice < 1 || objectChoice > 9)
    {
    cout << "Invalid object.\n";
    continue;
    }
    //FILE
    if (objectChoice == 9)
    {
    ofstream file(levelName + ".lvl");

    file << rows << " " << cols << endl;

    for (int i = 0; i < rows; i++)
    {
        file << map[i] << endl;
    }

    file.close();

    cout << "Level saved as " << levelName << ".lvl\n";
    break;
}

    if (objectChoice == 8)
    {
    int row, col;

    cout << "Enter row: ";
    cin >> row;

    cout << "Enter column: ";
    cin >> col;

    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        cout << "Invalid location.\n";
        continue;
    }

    cout << "Object at (" << row << ", " << col << "): ";

    if (map[row][col] == ' ')
        cout << "Empty" << endl;
    else
        cout << map[row][col] << endl;

    continue;
}

    int row, col;
    cout << "Enter row: ";
    cin >> row;
    cout << "Enter column: ";
    cin >> col;

    // Validate
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        cout << "Invalid location.\n";
        continue;
    }

    switch(objectChoice)
    {
        case 1:
            map[row][col] = '#';
            break;

        case 2:
            map[row][col] = '@';
            break;

        case 3:
            map[row][col] = '$';
            break;

        case 4:
            map[row][col] = 'G';
            break;

        case 5:
            map[row][col] = 'D';
            break;

        case 6:
            map[row][col] = 'S';
            break;

        case 7:
            map[row][col] = ' ';
            break;

        default:
            cout << "Invalid object.\n";
            break;
        }
    }
}

//Level 7: LOAD CUSTOM LEVEL, made by user!
void loadCustomLevel(){


}

//Main menu with user input & loading the levels, play again added!
int main()
{
 // user input
 // play again button (NEW ADDITION/PEER)
string choice;
char playAgain = 'y';
//main menu
while (playAgain == 'y' || playAgain == 'Y')
{
    cout << "Welcome to Ultra-Spy" << endl;
    cout << "Select a level: " << endl; 
    cout << "1) A New Enemy" << endl;
    cout << "2) The Truth of the Weapon" << endl;
    cout << "3) Revenge of the General" << endl;  
    cout << "4) Guard Color Doors" << endl;
    cout << "5) Rectangle Guard" << endl;
    cout << "6) Create Level" << endl;
    cout << "7) Load Custom Level" << endl;


getline(cin, choice);
 for (int i = 0; i < choice.length(); i++)
 {
    choice[i] = tolower(choice[i]);
 }
 


//case insensitive, if statements for user's input
if (choice == "1" || choice == "A New Enemy" || choice == "a new enemy")
{
    loadLevel1(); // function level 1
}
else if (choice == "2" || choice == "The Truth of the Weapon" || choice == "the truth of the weapon")
{
    loadLevel2(); // function level 2
} 
else if (choice == "3" || choice == "revenge of the general" || choice == "Revenge of the General")
{
    loadLevel3(); //function level 3
}
else if(choice == "4" || choice == "guard color doors" || choice == "Guard Color Doors" ){
    loadLevel4();
}
else if(choice == "5" || choice == "rectangle guard" || choice == "Rectangle Guard" ){
    loadLevel5();
}
else if(choice == "6" || choice == "create level" || choice == "Create Level" ){
    loadCreateLevel();
}
else if(choice == "7" || choice == "load custom level" || choice == "Load Custom Level" ){
    loadCustomLevel();
}
else 
{
    cout << "Invalid choice." << endl;
}
 cout << "Would you like to play again? (y/n): ";
 cin >> playAgain;
 cin.ignore(); //getline for next loop   

}
cout << "Thanks for playing!" << endl;
return 0;
}  