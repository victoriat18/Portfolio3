//Final Portfolio, Spy Game
//Portfolio, Spy Game
#include <iostream>
#include <string>
#include <cctype>
#include <vector> //added
#include <fstream>
using namespace std;

// LEVEL 1 : A New Enemy, Basic Beginner level (One door & one switch)
// One moving guard
void loadLevel1()
{
    cout << "   Level 1 loaded - Beginner Level    " << endl;
    cout << "   -----  Directions  -----    " << endl;
    cout << "Reach the $ without being seen, Move using WASD." << endl;
    cout << "Type 'inspect' to check what is on a tile (doesn't use a turn)." << endl;
    cout << "Walk onto switches (S) to toggle doors (D)." << endl;
    cout << "Watch out for the patrolling guard." << endl;
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

    // Moving guard
    int guardX = 2;
    int guardY = 6;

    int guardDX = 0;
    int guardDY = -1;

    char guardSymbol = '<';

    bool doorOpen = false;

    string input;

    while(true)
    {
        // PRINT MAP
        for(int i = 0; i < 5; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(i == playerX && j == playerY)
                    cout << '@';

                else if(i == guardX && j == guardY)
                    cout << guardSymbol;

                else if(map[i][j] == 'D' && doorOpen)
                    cout << ' ';

                else
                    cout << map[i][j];
            }

            cout << endl;
        }

        cout << "Move (WASD) or type inspect: ";
        cin >> input;

        // INSPECT
        if(input == "inspect")
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
                cout << "Patrolling guard facing " << guardSymbol << endl;

            else if(map[row][col] == '#')
                cout << "Wall.\n";

            else if(map[row][col] == 'D')
                cout << (doorOpen ? "Open door.\n" : "Closed door.\n");

            else if(map[row][col] == 'S')
                cout << "Switch.\n";

            else if(map[row][col] == '$')
                cout << "Goal.\n";

            else
                cout << "Empty tile.\n";

            continue;
        }

        int newX = playerX;
        int newY = playerY;

        if(input == "w")
            newX--;

        else if(input == "s")
            newX++;

        else if(input == "a")
            newY--;

        else if(input == "d")
            newY++;

        else
        {
            cout << "Invalid input.\n";
            continue;
        }

        // PLAYER COLLIDES WITH GUARD
        if(newX == guardX && newY == guardY)
        {
            cout << "YOU WERE CAUGHT!\n";
            return;
        }

        // WALL / DOOR CHECK
        if(map[newX][newY] == '#')
        {
            cout << "You hit a wall.\n";
            continue;
        }
        if(map[newX][newY] == 'D' && !doorOpen)
        {
            cout << "Door is closed.\n";
            continue;
        }
        // WIN
        if(map[newX][newY] == '$')
        {
            cout << "YOU WIN LEVEL 1!\n";
            return;
        }
        // MOVE PLAYER
        playerX = newX;
        playerY = newY;

        // PLAYER SWITCH
        if(map[playerX][playerY] == 'S')
        {
            doorOpen = !doorOpen;

            if(doorOpen)
                cout << "Door opened!\n";
            else
                cout << "Door closed!\n";
        }

        // MOVE PATROLLING GUARD
        int nextX = guardX + guardDX;
        int nextY = guardY + guardDY;

        if(nextX < 0 || nextX >= 5 ||
           nextY < 0 || nextY >= 8 ||
           map[nextX][nextY] == '#' ||
           (map[nextX][nextY] == 'D' && !doorOpen))
        {
            // turn clockwise
            if(guardDX == 0 && guardDY == -1)
            {
                guardDX = -1;
                guardDY = 0;
                guardSymbol = '^';
            }
            else if(guardDX == -1 && guardDY == 0)
            {
                guardDX = 0;
                guardDY = 1;
                guardSymbol = '>';
            }
            else if(guardDX == 0 && guardDY == 1)
            {
                guardDX = 1;
                guardDY = 0;
                guardSymbol = 'v';
            }
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

        // GUARD SWITCH
        if(map[guardX][guardY] == 'S')
        {
            doorOpen = !doorOpen;
            cout << "Guard toggled the door!\n";
        }

        // GUARD CATCH PLAYER
        if(playerX == guardX && playerY == guardY)
        {
            cout << "YOU WERE CAUGHT!\n";
            return;
        }

        // MOVING GUARD VISION
        if(guardSymbol == '<')
        {
            for(int y = guardY - 1; y >= 0; y--)
            {
                if(map[guardX][y] == '#' ||
                  (map[guardX][y] == 'D' && !doorOpen))
                    break;

                if(guardX == playerX && y == playerY)
                {
                    cout << "YOU WERE CAUGHT!\n";
                    return;
                }
            }
        }
        else if(guardSymbol == '>')
        {
            for(int y = guardY + 1; y < 8; y++)
            {
                if(map[guardX][y] == '#' ||
                  (map[guardX][y] == 'D' && !doorOpen))
                    break;

                if(guardX == playerX && y == playerY)
                {
                    cout << "YOU WERE CAUGHT!\n";
                    return;
                }
            }
        }
        else if(guardSymbol == '^')
        {
            for(int x = guardX - 1; x >= 0; x--)
            {
                if(map[x][guardY] == '#' ||
                  (map[x][guardY] == 'D' && !doorOpen))
                    break;

                if(x == playerX && guardY == playerY)
                {
                    cout << "YOU WERE CAUGHT!\n";
                    return;
                }
            }
        }
        else if(guardSymbol == 'v')
        {
            for(int x = guardX + 1; x < 5; x++)
            {
                if(map[x][guardY] == '#' ||
                  (map[x][guardY] == 'D' && !doorOpen))
                    break;

                if(x == playerX && guardY == playerY)
                {
                    cout << "YOU WERE CAUGHT!\n";
                    return;
                }
            }
        }

    } // while
} // Level 1 

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

// STURCTURE
struct Door
{
    int row;
    int col;
    int group;
};

struct Switch
{
    int row;
    int col;
    int group;
};

struct Guard
{
    int row;
    int col;
    int movement;
    char direction;
    char previousTile;
    bool rectangle;
};
//add to menu. requirement !!
vector<string> customLevels;

void playLevel(vector<string> map,
               int rows,
               int cols,
               vector<Door> doors,
               vector<Switch> switches,
               vector<Guard> guards);

//LEVEL 6: CREATE YOUR OWN LEVEL, user creates their own level. 
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
// ROWS
cout << "Enter number of rows: ";

while (!(cin >> rows))
{
    cout << "Invalid input. Enter a number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

while (rows < 5)
{
    cout << "Rows must be at least 5. Enter again: ";

    while (!(cin >> rows))
    {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000,'\n');
    }
}

//COLUMNS
cout << "Enter number of columns: ";

while (!(cin >> cols))
{
    cout << "Invalid input. Enter a number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

while (cols <= 5)
{
    cout << "Columns must be greater than 5. Enter again: ";

    while (!(cin >> cols))
    {
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
    vector<string> map(rows, string(cols, ' '));
    //ADDS BORDERS.
    for(int i = 0; i < rows; i++)
{
    map[i][0] = '#';
    map[i][cols - 1] = '#';
}

for(int j = 0; j < cols; j++)
{
    map[0][j] = '#';
    map[rows - 1][j] = '#';
}

    vector<Door> doors;
    vector<Switch> switches;
    vector<Guard> guards;
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
    cout << "4. Guard (^ v < >)\n";
    cout << "5. Door (D)\n";
    cout << "6. Switch (S)\n";
    cout << "7. Empty\n";
    cout << "8. Inspect\n";
    cout << "9. Save & Quit\n";

    int objectChoice;
    cout << "Choose object: ";
    while (!(cin >> objectChoice))
{
    cout << "Invalid input. Enter a number (1-9): ";
    cin.clear();
    cin.ignore(1000, '\n');
}

    if (objectChoice < 1 || objectChoice > 9)
    {
    cout << "Invalid object.\n";
    continue;
    }

    //FILES
    if (objectChoice == 9)
    {
    bool hasPlayer = false;
    bool hasGoal = false;

for(int i = 0; i < rows; i++)
{
    for(int j = 0; j < cols; j++)
    {
        if(map[i][j] == '@')
            hasPlayer = true;

        if(map[i][j] == '$')
            hasGoal = true;
    }
}

if(!hasPlayer)
{
    cout << "You must place one player (@).\n";
    continue;
}

if(!hasGoal)
{
    cout << "You must place one goal ($).\n";
    continue;
}
    ofstream file(levelName + ".lvl");

    if (!file)
{
    cout << "Could not save file.\n";
    return;
}
file << rows << " " << cols << endl;

//SAVE PROCESS
// Save normal objects
for (int i = 0; i < rows; i++)
{
    for (int j = 0; j < cols; j++)
    {
        if (map[i][j] == '#')
            file << "Wall " << i << " " << j << endl;

        else if (map[i][j] == '@')
            file << "Player " << i << " " << j << endl;

        else if (map[i][j] == '$')
            file << "Goal " << i << " " << j << endl;
    }
}

// Save guards
for (Guard g : guards)
{
    file << "Guard "
         << g.movement << " "
         << g.direction << " "
         << g.row << " "
         << g.col << endl;
}


// Save doors
for (Door d : doors)
{
    file << "Door "
         << d.group << " "
         << d.row << " "
         << d.col << endl;
}


// Save switches
for (Switch s : switches)
{
    file << "Switch "
         << s.group << " "
         << s.row << " "
         << s.col << endl;
}

file.close();

cout << "Level saved as " << levelName << ".lvl\n";

// Add created level to main menu
bool exists = false;

for (int i = 0; i < customLevels.size(); i++)
{
    if (customLevels[i] == levelName)
    {
        exists = true;
        break;
    }
}

if (!exists)
{
    customLevels.push_back(levelName);
}

break;
}

    if (objectChoice == 8)
    {
    int row, col;

cout << "Enter row: ";
while (!(cin >> row))
{
    cout << "Invalid input. Enter a number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

cout << "Enter column: ";
while (!(cin >> col))
{
    cout << "Invalid input. Enter a number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

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
while (!(cin >> row))
{
    cout << "Invalid input. Enter a number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

cout << "Enter column: ";
while (!(cin >> col))
{
    cout << "Invalid input. Enter a number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

    // Validate
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        cout << "Invalid location.\n";
        continue;
    }
    //walls intact
    if ((row == 0 || row == rows - 1 ||
     col == 0 || col == cols - 1) && objectChoice != 1)
{
    cout << "Only walls are allowed on the border.\n";
    continue;
}
    switch(objectChoice)
    {
        case 1:
            map[row][col] = '#';
            break;

case 2:
{
    bool playerExists = false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (map[i][j] == '@')
                playerExists = true;
        }
    }

    if (playerExists)
    {
        cout << "Only one player allowed.\n";
    }
    else
    {
        map[row][col] = '@';
    }

    break;
}
    case 3:
{
    bool goalExists = false;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(map[i][j] == '$')
                goalExists = true;
        }
    }

    if(goalExists)
    {
        cout << "Only one goal allowed.\n";
    }
    else
    {
        map[row][col] = '$';
    }

    break;
}
        case 4:
{
int movement = 0;
char direction;

cout << "Movement type:\n";
cout << "1. Back and forth\n";
cout << "2. Rectangle patrol\n";
cout << "Enter choice: ";

while (!(cin >> movement) || (movement != 1 && movement != 2))
{
    cout << "Invalid movement. Enter 1 or 2: ";
    cin.clear();
    cin.ignore(1000, '\n');
    }  
    //MOVEMENT  
cout << "Direction (W/A/S/D): ";

while (!(cin >> direction))
{
    cout << "Invalid input. Enter W/A/S/D: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

direction = toupper(direction);

while (direction != 'W' &&
       direction != 'A' &&
       direction != 'S' &&
       direction != 'D')
{
    cout << "Invalid direction. Enter W/A/S/D: ";
    cin >> direction;
    direction = toupper(direction);
}

    // Store the correct guard symbol
    if (direction == 'W')
        map[row][col] = '^';
    else if (direction == 'A')
        map[row][col] = '<';
    else if (direction == 'S')
        map[row][col] = 'v';
    else if (direction == 'D')
        map[row][col] = '>';

guards.push_back({row, col, movement, direction, ' '});

break;
}
    case 5:
{
    map[row][col] = 'D';
//validate door group, DOOR CASE
int group;
cout << "Enter door group: ";
while (!(cin >> group))
{
    cout << "Invalid input. Enter a positive number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}
//DOOR CASE
while (group <= 0)
{
    cout << "Door group must be positive: ";

    while (!(cin >> group))
    {
        cout << "Invalid input. Enter a positive number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

doors.push_back({row, col, group});

break;
}
    case 6:
{
    map[row][col] = 'S';

//validate switch group
int group;
//SWITCH CASE
cout << "Enter switch group: ";

while (!(cin >> group))
{
    cout << "Invalid input. Enter a positive number: ";
    cin.clear();
    cin.ignore(1000, '\n');
}

while (group <= 0)
{
    cout << "Switch group must be positive: ";

    while (!(cin >> group))
    {
        cout << "Invalid input. Enter a positive number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

switches.push_back({row, col, group});

break;

}
    case 7:
    if (row == 0 || row == rows - 1 ||
        col == 0 || col == cols - 1)
    {
        cout << "Cannot erase border walls.\n";
    }
    else
    {
        map[row][col] = ' ';
    }
    break;
        }
    } // while true
} // loadCreateLevel

// Level 7: LOAD CUSTOM LEVEL (LEVEL 6), made by user!
void loadCustomLevel(string levelName)
{
    int rows, cols;

if(levelName.find(".lvl") == string::npos)
{
    levelName += ".lvl";
}


    ifstream file(levelName);

    if (!file)
    {
        cout << "Could not open level.\n";
        return;
    }


    file >> rows >> cols;


    vector<string> map(rows, string(cols, ' '));

    vector<Door> doors;
    vector<Switch> switches;
    vector<Guard> guards;


    string object;


    while(file >> object)
    {
        int row, col;


        if(object == "Wall")
        {
            file >> row >> col;
            map[row][col] = '#';
        }


        else if(object == "Player")
        {
            file >> row >> col;
            map[row][col] = '@';
        }


        else if(object == "Goal")
        {
            file >> row >> col;
            map[row][col] = '$';
        }


        else if(object == "Guard")
        {
            int movement;
            char direction;

            file >> movement >> direction >> row >> col;


            if(direction == 'W')
                map[row][col] = '^';

            else if(direction == 'A')
                map[row][col] = '<';

            else if(direction == 'S')
                map[row][col] = 'v';

            else if(direction == 'D')
                map[row][col] = '>';


            guards.push_back({row, col, movement, direction});
        }


        else if(object == "Door")
        {
            int group;

            file >> group >> row >> col;

            map[row][col] = 'D';

            doors.push_back({row, col, group});
        }


        else if(object == "Switch")
        {
            int group;

            file >> group >> row >> col;

            map[row][col] = 'S';

            switches.push_back({row, col, group});
        }
    }
    file.close();

    // Remove .lvl from the displayed name
    string displayName = levelName;

    if (displayName.find(".lvl") != string::npos)
    {
        displayName = displayName.substr(0, displayName.find(".lvl"));
        bool exists = false;

for (int i = 0; i < customLevels.size(); i++)
{
    if (customLevels[i] == displayName)
    {
        exists = true;
        break;
    }
}

if (!exists)
{
    customLevels.push_back(displayName);
}
    }

    cout << "\nLevel loaded successfully!\n";
    cout << "Loaded Level: " << displayName << endl;

    // DISPLAY CREATED LEVEL
    cout << "  ";

    for (int j = 0; j < cols; j++)
        cout << j << " ";

    cout << endl;

    // Display rows
    for (int i = 0; i < rows; i++)
    {
        cout << i << " ";

        for (int j = 0; j < cols; j++)
        {
            cout << map[i][j] << " ";
        }

        cout << endl;
    }

    // SEND CUSTOM LEVEL TO GAME
    playLevel(map, rows, cols, doors, switches, guards);
}


// PLAYERS CUSTOM LEVEL SAVED AND ABLE TO BE PLAYED
void playLevel(vector<string> map,
               int rows,
               int cols,
               vector<Door> doors,
               vector<Switch> switches,
               vector<Guard> guards)
{
    cout << "Custom Level Loaded!\n";


    int playerX = -1;
    int playerY = -1;
    char playerPreviousTile = ' ';


    // Find player
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(map[i][j] == '@')
            {
                playerX = i;
                playerY = j;
                map[i][j] = ' ';
            }
        }
    }


    if(playerX == -1)
    {
        cout << "No player found.\n";
        return;
    }


    // Initialize guard tiles
    for(int i = 0; i < guards.size(); i++)
    {
        guards[i].previousTile = ' ';
    }


    bool doorOpen = false;
    string input;

    while(true)
    {

        // DISPLAY MAP
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(i == playerX && j == playerY)
                    cout << '@';

                else if(map[i][j] == 'D' && doorOpen)
                    cout << ' ';

                else
                    cout << map[i][j];
            }

            cout << endl;
        }


        cout << "Move (WASD) or inspect: ";
        cin >> input;



        // INSPECT
        if(input == "inspect")
        {
            int row, col;

            cout << "Row: ";
            cin >> row;

            cout << "Column: ";
            cin >> col;


            if(row < 0 || row >= rows ||
               col < 0 || col >= cols)
            {
                cout << "Invalid location.\n";
                continue;
            }


            if(map[row][col] == '#')
                cout << "Wall\n";

            else if(map[row][col] == 'D')
                cout << (doorOpen ? "Open Door\n" : "Closed Door\n");

            else if(map[row][col] == 'S')
                cout << "Switch\n";

            else if(map[row][col] == '$')
                cout << "Goal\n";

            else if(map[row][col] == '^' ||
                    map[row][col] == 'v' ||
                    map[row][col] == '<' ||
                    map[row][col] == '>')
                cout << "Guard\n";

            else
                cout << "Empty\n";


            continue;
        }

        int newX = playerX;
        int newY = playerY;


        if(input == "w")
            newX--;

        else if(input == "s")
            newX++;

        else if(input == "a")
            newY--;

        else if(input == "d")
            newY++;

        else
        {
            cout << "Invalid input.\n";
            continue;
        }

        // Boundary
        if(newX < 0 || newX >= rows ||
           newY < 0 || newY >= cols)
        {
            cout << "Can't move there.\n";
            continue;
        }

        // Hit guard
        for(int i = 0; i < guards.size(); i++)
        {
            if(newX == guards[i].row &&
               newY == guards[i].col)
            {
                cout << "The guard caught you! GAME OVER!\n";
                return;
            }
        }

        // Wall
        if(map[newX][newY] == '#')
        {
            cout << "You hit a wall!\n";
            continue;
        }

        // Door
        if(map[newX][newY] == 'D' && !doorOpen)
        {
            cout << "Door is closed!\n";
            continue;
        }

        // WIN
        if(map[newX][newY] == '$')
        {
            cout << "YOU WIN!\n";
            return;
        }

        // Save what player stepped on
        playerPreviousTile = map[newX][newY];

        map[playerX][playerY] = ' ';

        playerX = newX;
        playerY = newY;



        // Switch toggle
        if(playerPreviousTile == 'S')
        {
            doorOpen = !doorOpen;

            if(doorOpen)
                cout << "Door opened!\n";

            else
                cout << "Door closed!\n";
        }



        // MOVE GUARDS
        for(int i = 0; i < guards.size(); i++)
        {

            int nextRow = guards[i].row;
            int nextCol = guards[i].col;


            if(guards[i].direction == 'W')
                nextRow--;

            else if(guards[i].direction == 'S')
                nextRow++;

            else if(guards[i].direction == 'A')
                nextCol--;

            else if(guards[i].direction == 'D')
                nextCol++;



            // blocked LOAD LEVEL & PLAY
// blocked
if(nextRow <= 0 || nextRow >= rows-1 ||
   nextCol <= 0 || nextCol >= cols-1 ||
   map[nextRow][nextCol] == '#' ||
   map[nextRow][nextCol] == 'D')
{

    // Rectangle guard turns corners
    if(guards[i].movement == 2)
    {
        if(guards[i].direction == 'D')
            guards[i].direction = 'S';

        else if(guards[i].direction == 'S')
            guards[i].direction = 'A';

        else if(guards[i].direction == 'A')
            guards[i].direction = 'W';

        else if(guards[i].direction == 'W')
            guards[i].direction = 'D';
    }

    // Normal back and forth guard
    else
    {
        if(guards[i].direction == 'W')
            guards[i].direction = 'S';

        else if(guards[i].direction == 'S')
            guards[i].direction = 'W';

        else if(guards[i].direction == 'A')
            guards[i].direction = 'D';

        else if(guards[i].direction == 'D')
            guards[i].direction = 'A';
    }

}
    else
{
    // Restore old tile
    map[guards[i].row][guards[i].col] =
        guards[i].previousTile;


    // Save tile guard is stepping onto
    guards[i].previousTile =
        map[nextRow][nextCol];


    // Move guard
    guards[i].row = nextRow;
    guards[i].col = nextCol;


    // Guard steps on switch
    if(guards[i].previousTile == 'S')
    {
        doorOpen = !doorOpen;

        if(doorOpen)
            cout << "Guard opened the door!\n";

        else
            cout << "Guard closed the door!\n";
    }
}
            // Draw guard
            if(guards[i].direction == 'W')
                map[guards[i].row][guards[i].col] = '^';

            else if(guards[i].direction == 'S')
                map[guards[i].row][guards[i].col] = 'v';

            else if(guards[i].direction == 'A')
                map[guards[i].row][guards[i].col] = '<';

            else if(guards[i].direction == 'D')
                map[guards[i].row][guards[i].col] = '>';



            // Guard catches player
            if(guards[i].row == playerX &&
               guards[i].col == playerY)
            {
                cout << "The guard caught you! GAME OVER!\n";
                return;
            }

        }

    }
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

for (int i = 0; i < customLevels.size(); i++)
{
    cout << i + 8 << ") " << customLevels[i] << endl;
}

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
else if(choice == "7" ||
        choice == "load custom level" ||
        choice == "Load Custom Level")
{
    string name;

    cout << "Enter level name: ";
    cin >> name;
    cin.ignore();

    loadCustomLevel(name);
}
else
{
    bool found = false;

    for (int i = 0; i < customLevels.size(); i++)
    {
        if (choice == to_string(i + 8) ||
            choice == customLevels[i])
        {
            loadCustomLevel(customLevels[i]);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Invalid choice." << endl;
    }
}
 cout << "Would you like to play again? (y/n): ";
 cin >> playAgain;
 cin.ignore(); //getline for next loop   

}
cout << "Thanks for playing!" << endl;
return 0;
}  
