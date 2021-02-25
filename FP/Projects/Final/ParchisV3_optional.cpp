/*
    SUBMITTED BY:  Lucas Vukotic
    DATE:          January 16, 2020

    OPTIONAL PART: Included
    OTHER INFORMATION: 
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#undef max
#endif

using namespace std;

const string FileName = "C:\\Users\\lucas\\Desktop\\Informatica\\FP1\\Projects\\Final\\mine.txt"; // test5 canMove test6 mine | .txt
const bool Debug = true; // true false
const bool RollFromFile = true; // If false you get to select the dice roll
const int Goal = 108;

enum tColor
{
    Yellow = 0,
    Blue,
    Red,
    Green,
    Gray,
    None
};


const int NUM_PLAYERS = 4;
const int NUM_MARKERS = 4;
const int NUM_SPACES = 68;

typedef int tMarkers[NUM_MARKERS];
struct tPlayer{
     tColor color;
     tMarkers markers;
};
typedef tPlayer tPlayers[NUM_PLAYERS];

struct tSpace{
     tColor lane1;
     tColor lane2;
};
typedef tSpace tSpaces[NUM_SPACES];

struct tGame{
     tSpaces spaces;
     tPlayers players;
     tColor playerTurn;
     int roll;
     int reward;
     int sixes;
     int lastMarkerMoved;
};


string colorToString(tColor color);

int canEat(tGame &game, int &space);
int toGoal(tGame &game, int &space);
int toSafe(tGame &game, int &space);
int flee(tGame &game, int &space);
int firstPossible(tGame &game,int &space);

bool allAtHome(const tPlayer player);
bool allAtGoal(const tPlayer player);        
bool isSafe(int pos);        
bool bridge(const tGame &game, int space);      
bool process5(tGame &game, bool &passTurn);     
bool process6(tGame &game, bool &passTurn);     
bool play(tGame &game, bool passTurn, bool &end);               
bool canMove(const tGame &game, int marker, int &space);        

short startSpace(tColor color);         
short zanataSpace(tColor color);        
short dice(ifstream &file);                       

int nextSpace(int position, tColor playerTurn);
int howMany(const tMarkers player, int space);
int firstAt(const tMarkers player, int space);
int secondAt(const tMarkers player, int space);
int n_bridges(tPlayer player, int &marker1, int &marker2);

void load(tGame &game, ifstream &file);
void openBridge(tGame &game, int space, int space2);
void move(tGame &game, int marker, int space);
void markerOut(tGame &game);
void toHome(tGame &game, int space);
void display(const tGame &game);
void initialize(tGame &game);
void setColor(tColor color);
void initColors();
void pause();

int main()
{

    ifstream file;
    tGame game;

    bool forcedMove = false, passTurn = true, end = false, played;
    int next, marker;

    initColors();
    initialize(game);
    if (Debug){
        file.open(FileName);
        load(game, file);
    }
    display(game);



    setColor(game.playerTurn);
    cout << "The " << colorToString(game.playerTurn) << " player starts" << endl;
    while (!end)
    {
        played = false;
        setColor(game.playerTurn);
        cout << "Turn for the " << colorToString(game.playerTurn) << " player... ";
        if (game.reward > 0){
            cout << "The player has " << game.reward << " extra moves!" << endl;
            game.roll = game.reward;
            game.reward = 0;
        } else {
            game.roll = dice(file);
            cout << "A " << game.roll << " is rolled" << endl;
        }
        if (game.roll == 0) {
            end = true;
        } else {
            if (game.roll == 5){
                played = process5(game, passTurn); 
                if (played){
                    cout << "A marker gets out of home " << endl;
                    if (Debug)
                        cout << "Reward: " << game.reward << ", passTurn: " << passTurn << endl;
                }
                else
                    cout << "No marker can get out of home" << endl;
            } else if (game.roll == 6){
                played = process6(game, passTurn);
            }
            if (!played){
                passTurn = play(game, passTurn, end);
            }
            if (!end){
                if (allAtGoal(game.players[game.playerTurn])){
                    cout << "The " << colorToString(game.playerTurn) << " player wins!" << endl;
                    end = true;
                } else if (passTurn){
                    game.playerTurn = tColor((int(game.playerTurn) + 1) % NUM_PLAYERS);
                    game.sixes = 0;
                } else
                    passTurn = true;
                
                pause();
                display(game);
            }
        }
    }

    return 0;
}

int canEat(tGame &game, int &space);
int toGoal(tGame &game, int &space);
int toSafe(tGame &game, int &space);
int flee(tGame &game, int &space);
int firstPossible(tGame &game,int &space);

string colorToString(tColor color)
{
    string result;
    switch (color)
    {
    case Red:
        result = "red";
        break;
    case Green:
        result = "green";
        break;
    case Blue:
        result = "blue";
        break;
    case Yellow:
        result = "yellow";
        break;
    }

    return result;
}

bool allAtHome(const tPlayer player){
    bool all = true;
    for (int marker = 0; marker < NUM_MARKERS; marker++)
        if (player.markers[marker] != -1)
            all = false;
    return all;
}
bool allAtGoal(const tPlayer player){
    bool all = true;
    for (int marker = 0; marker < NUM_MARKERS; marker++)
        if (player.markers[marker] != Goal)
            all = false;
    return all;
}
bool isSafe(int pos)
{
    bool result = false;
    if (pos > 100)             // Zanata (not sure if it should be safe)
        result = true;
    pos %= 17;
    if (pos == 0 || pos == 5 || pos == 12)
    {
        result = true;
    }

    return result;
}
bool bridge(const tGame &game, int pos){
    tSpace space = game.spaces[pos];
    bool out;
    out = pos >= 0 && pos <= 67;                     // Space must be in the street
    out = out && (space.lane1 == space.lane2);      // If two markers of the same player in the space are
    out = out && (space.lane1 != None);                  // Those are real markers not space

    return out;
}
bool process5(tGame &game, bool &passTurn)
{
    bool out = false;
    int start, marker;
    start = startSpace(game.playerTurn);
    marker = firstAt(game.players[game.playerTurn].markers, -1);
    if (marker != -1){
        if (game.spaces[start].lane2 == None) {              // Lane 2 is free 
            markerOut(game);
            out = true;
        } else if (game.spaces[start].lane2 == game.playerTurn){        // Two of playerTurn at start
            out = false;
        } else {                                                    // One out
            toHome(game, start);
            markerOut(game);
            out = true;
            game.reward = 20;
            passTurn = false;
        }
    }
    return out;
}
bool process6(tGame &game, bool &passTurn){
    int marker1 = -1, marker2 = -1, bridges, next, space;
    bool out = false;
    bridges = n_bridges(game.players[game.playerTurn], marker1, marker2);
    game.sixes++;
    if (firstAt(game.players[game.playerTurn].markers, -1) == -1){     // No markers at home
        game.roll = 7;
        cout << "The player has no markers at home: 7 are counted!" << endl;
    }

    if (game.sixes == 3){
        space = game.players[game.playerTurn].markers[game.lastMarkerMoved];
        cout << "Third 6 in a row...";
        if (space > 100){
            cout << "The last marker moved is beyond zanata and it is not sent home!" << endl;
        } else{  
            // It is sent home, placing it first on lane2
            cout << "The last marker moved is sent home!" << endl;
            if (game.spaces[space].lane2 != game.playerTurn){
                tColor temp = game.spaces[space].lane1;
                game.spaces[space].lane1 = game.spaces[space].lane2;
                game.spaces[space].lane2 = temp;
            }
            toHome(game, space);
        }
        passTurn = true;
        out = true;
        game.sixes = 0;
    } else{
        passTurn = false;
        if (bridges == 1 && canMove(game, marker1, next)){
            space = game.players[game.playerTurn].markers[marker1];
            openBridge(game, space, next);
            out = true;
        }
        if (bridges == 2){
            bool first, second;
            int next2;
            first = canMove(game, marker1, next);
            second = canMove(game, marker2, next2);
            if (first && second){
                out = false;
            } else if (first){
                space = game.players[game.playerTurn].markers[marker1];
                openBridge(game, space, next);
                out = true;
            } else if (second){
                space = game.players[game.playerTurn].markers[marker2];
                openBridge(game, space, next2);
                out = true;
            } else {
                // No marker can be moved
                cout << "None of the two bridges can be opened! The roll is ignored..." << endl;
                out = true; // Suposed to be false but true makes more sense.
            }
        }
    } 
    return out;
}
bool play(tGame &game, bool passTurn, bool &end){
    // WIP
    int next, marker;
    int possibleMoves = 0;

    if (allAtHome(game.players[game.playerTurn]))
        cout << "All markers are at home... ";

    for (int m = 0; m < NUM_MARKERS ; m++) 
        if (canMove(game, m, next))
            possibleMoves++;

    if (possibleMoves == 0){
        cout << "Impossible to move!" << endl;
    } else if (possibleMoves == 1){
        for (int m = 0; m < NUM_MARKERS ; m++) 
            if (canMove(game, m, next)){
                cout << "The marker " << (m + 1) << " is moved from space " 
                      << game.players[game.playerTurn].markers[m] << " to space " << next << endl; 
                move(game, m, next);
            }
    } else {
        cout << "Please select the marker you want to move..." << endl;
        for (int m = 0; m < NUM_MARKERS ; m++) {
            if (canMove(game, m, next)){
                cout << (m + 1) << ": ";
                cout << "From space " << game.players[game.playerTurn].markers[m] << " to space " << next << endl;
            }
        }
        cout << "Marker (0 to exit): ";
        cin >> marker;
        cin.get();
        if (marker == 0)
            end = true;
        else{
            marker--;
            if (canMove(game, marker, next)){
                move(game, marker, next);
                if (Debug)
                    cout << "Reward: " << game.reward << endl;
                game.lastMarkerMoved = marker;
            }
        }
    }
    if (game.reward > 0)
        passTurn = false;
    if (game.sixes > 0 && game.roll > 7)
        passTurn = false;
    
    return passTurn;
}
bool canMove(const tGame &game, int marker, int &space){
    bool canmove = true, lastMove = false;
    int position = game.players[game.playerTurn].markers[marker];
    if (position != -1){
        for (int i = 0; i < game.roll; i++){
            position = nextSpace(position, game.playerTurn);          // No need to check first position
            if ((i + 1) == game.roll)
                lastMove = true;
            // if (lastMove && game.spaces[position].lane1 != None && game.spaces[position].lane2 != None) // Last move is full of players
            //     canmove = false;

            if (position == Goal && !lastMove)  // Moved further than goal
                canmove = false;

            if (bridge(game, position) && isSafe(position))  // Barrier encountered
                canmove = false;

            if (bridge(game, position) && lastMove)  // Lanes are full
                canmove = false;
            
            if (firstAt(game.players[game.playerTurn].markers, position) != secondAt(game.players[game.playerTurn].markers, position) && lastMove)
                canmove = false;    // Lanes are full but also works for zanatas (outside of lanes)

            if (position < -1 || (position > 67 && position < 100) || position > Goal) // Out of bounds (just in case)
                canmove = false;
        }
        if (canmove)
            space = position;
    } else
        canmove = false;              // If player at home it can´t move (process 5 would have catch it)
    return canmove;
}


short startSpace(tColor color)
{
    short result = 0;
    switch (color)
    {
    case Red:
        result = 39;
        break;
    case Green:
        result = 56;
        break;
    case Blue:
        result = 22;
        break;
    case Yellow:
        result = 5;
        break;
    }

    return result;
}
short zanataSpace(tColor color)
{
    return startSpace(color) - 5;
}
short dice(ifstream &file)
{
    short out;
    if (Debug && !RollFromFile)
    {
        cout << "Roll (0 to exit): ";
        cin >> out;
        cin.get();
    } else if (Debug && RollFromFile){
        file >> out;
        file.get();
        if (out == -1){
            file.close();
            out = 0;
        }
    }
    else
        out = rand() % 6 + 1;
    return out;
}


int nextSpace(int position, tColor playerTurn){
    int next;
    if (position == zanataSpace(playerTurn))
        next = 101;
    else if (position == 67)
        next = 0;
    else 
        next = position + 1;
    
    return next;
}
int howMany(const tMarkers player, int space)
{
    int out = 0;
    for (int i = 0; i < NUM_MARKERS; i++)
        if (player[i] == space)
            out++;
    return out;
}
int firstAt(const tMarkers player, int space)
{
    int out = -1;
    bool found = false;
    for (int i = 0; i < NUM_MARKERS; i++)
    {
        if (player[i] == space && !found)
        {
            out = i;
            found = true;
        }
    }
    return out;
}
int secondAt(const tMarkers player, int space)
{
    int out = -1;
    for (int i = 0; i < NUM_MARKERS; i++)
        if (player[i] == space)
            out = i;
    return out;
}

int n_bridges(tPlayer player, int &marker1, int &marker2){
    int bridges = 0;
    for (int i = 0; i < NUM_MARKERS; i++)
        for (int j = i + 1; j < NUM_MARKERS; j++)
            if (player.markers[i] == player.markers[j]){
                bridges++;
                if (marker1 == -1)
                    marker1 = i;
                else
                    marker2 = i;
            }
    return bridges;
}


void load(tGame &game, ifstream &file)
{
    
    int player, space;

    if (file.is_open())
    {
        for (int i = 0; i < NUM_PLAYERS; i++)
            for (int f = 0; f < NUM_MARKERS; f++)
            {
                file >> space;
                game.players[i].markers[f] = space;
                if ((space >= 0) && (space < NUM_SPACES))
                    if (game.spaces[space].lane1 == None)
                        game.spaces[space].lane1 = tColor(i);
                    else
                        game.spaces[space].lane2 = tColor(i);
            }
        file >> player;
        game.playerTurn = tColor(player);
        // file.close();
    } else 
        cout << "File not found" << endl;
}
void openBridge(tGame &game, int space, int space2){
    int marker = secondAt(game.players[game.playerTurn].markers, space);
    cout << "The bridge in space " << space << " is opened" << endl;
    move(game, marker, space2);
    game.lastMarkerMoved = marker;
}
void move(tGame &game, int marker, int space){
    int previous, next;
    previous = game.players[game.playerTurn].markers[marker];
    next = space;
    tSpace nextSpace = game.spaces[next];

    if (game.spaces[previous].lane1 == game.playerTurn)
        game.spaces[previous].lane1 = game.spaces[previous].lane2;
    game.spaces[previous].lane2 = None;
    // lane1[previous] = lane2[previous];      // Maybe problematic
    // lane2[previous] = None;

    game.players[game.playerTurn].markers[marker] = next;

    if (next == Goal){
        cout << "The players marker has arrived to the goal" << endl;
        game.reward = 10;
    }
    if (next >= 0 && next <= 67){
        if (nextSpace.lane1 == None)
            game.spaces[next].lane1 = game.playerTurn;
        else if (nextSpace.lane1 == game.playerTurn)
            game.spaces[next].lane2 = game.playerTurn;
        else if (isSafe(next))
            game.spaces[next].lane2 = game.playerTurn;
        else  // playerTurn eats lane1[next]
        {
            cout << "A marker of the " << colorToString(nextSpace.lane1) << " player has been eaten..." << endl;
            game.spaces[next].lane2 = nextSpace.lane1;
            game.spaces[next].lane1 = game.playerTurn;
            toHome(game, next);
            game.reward = 20;
        }
    }
}

void markerOut(tGame &game)
{
    // Saca una ficha del jugador en turno
    short space, markerHome;
    bool found = false;
    space = startSpace(game.playerTurn);
    game.spaces[space].lane2 = game.spaces[space].lane1;

    markerHome = firstAt(game.players[game.playerTurn].markers, -1);
    game.players[game.playerTurn].markers[markerHome] = space;
    game.spaces[space].lane1 = game.playerTurn;
}
void toHome(tGame &game, int space)
{
    tColor player = game.spaces[space].lane2;
    int marker = secondAt(game.players[player].markers, space);
    game.players[player].markers[marker] = -1;
    game.spaces[space].lane2 = None;
}
void display(const tGame& game) {
    int space, marker;
    tColor plyr;

    cout << "\x1b[2J\x1b[H"; // Se situa en la esquina superior izquierda
    setColor(Gray);
    cout << endl;

    // Filas con la numeraci�n de las spaces...
    for (int i = 0; i < NUM_SPACES; i++)
        cout << i / 10;
    cout << endl;
    for (int i = 0; i < NUM_SPACES; i++)
        cout << i % 10;
    cout << endl;

    // Borde superior...
    for (int i = 0; i < NUM_SPACES; i++)
        cout << '>';
    cout << endl;

    // Primera fila de posiciones de markers...
    for (int i = 0; i < NUM_SPACES; i++) {
        setColor(game.spaces[i].lane2);
        if (game.spaces[i].lane2 != None)
            cout << firstAt(game.players[game.spaces[i].lane2].markers, i) + 1;
        else
            cout << ' ';
        setColor(Gray);
    }
    cout << endl;

    // "Mediana"    
    for (int i = 0; i < NUM_SPACES; i++)
        if (isSafe(i))
            cout << 'o';
        else
            cout << '-';
    cout << endl;


    // Segunda fila de posiciones de markers...
    for (int i = 0; i < NUM_SPACES; i++) {
        setColor(game.spaces[i].lane1);
        if (game.spaces[i].lane1 != None)
            cout << secondAt(game.players[game.spaces[i].lane1].markers, i) + 1;
        else
            cout << ' ';
        setColor(Gray);
    }
    cout << endl;

    plyr = Yellow;
    // Borde inferior...
    for (int i = 0; i < NUM_SPACES; i++)
        if (i == zanataSpace(plyr)) {
            setColor(plyr);
            cout << "V";
            setColor(Gray);
        }
        else if (i == startSpace(plyr)) {
            setColor(plyr);
            cout << "^";
            setColor(Gray);
            plyr = tColor(int(plyr) + 1);
        }
        else
            cout << '>';
    cout << endl;

    // Metas y casas...
    for (int i = 0; i < NUM_MARKERS; i++) {
        space = 0;
        plyr = Yellow;
        setColor(plyr);
        while (space < NUM_SPACES) {
            if (space == zanataSpace(plyr)) {
                marker = firstAt(game.players[plyr].markers, 101 + i);
                if (marker != -1) {
                    cout << marker + 1;
                    if (howMany(game.players[plyr].markers, 101 + i) > 1) {
                        marker = secondAt(game.players[plyr].markers, 101 + i);
                        if (marker != -1) {
                            cout << marker + 1;
                        }
                        else
                            cout << "V";
                    }
                    else
                        cout << "V";
                }
                else
                    cout << "VV";
                space++;
            }
            else if (space == startSpace(plyr)) {
                if (game.players[plyr].markers[i] == -1) // En casa
                    cout << i + 1;
                else
                    cout << "^";
                plyr = tColor(int(plyr) + 1);
                setColor(plyr);
            }
            else
                cout << ' ';
            space++;
        }
        cout << endl;
    }

    // Resto de metas...
    for (int i = 105; i <= 107; i++) {
        space = 0;
        plyr = Yellow;
        setColor(plyr);
        while (space < NUM_SPACES) {
            if (space == zanataSpace(plyr)) {
                marker = firstAt(game.players[plyr].markers, i);
                if (marker != -1) {
                    cout << marker + 1;
                    if (howMany(game.players[plyr].markers, i) > 1) {
                        marker = secondAt(game.players[plyr].markers, i);
                        if (marker != -1) {
                            cout << marker + 1;
                        }
                        else
                            cout << "V";
                    }
                    else
                        cout << "V";
                }
                else
                    cout << "VV";
                space++;
                plyr = tColor(int(plyr) + 1);
                setColor(plyr);
            }
            else
                cout << ' ';
            space++;
        }
        cout << endl;
    }

    space = 0;
    plyr = Yellow;
    setColor(plyr);
    while (space < NUM_SPACES) {
        cout << ((game.players[plyr].markers[0] == 108) ? '1' : '.');
        cout << ((game.players[plyr].markers[1] == 108) ? '2' : '.');
        plyr = tColor(int(plyr) + 1);
        setColor(plyr);
        cout << "                    ";
        space += 17;
    }
    cout << endl;
    space = 0;
    plyr = Yellow;
    setColor(plyr);
    while (space < NUM_SPACES) {
        cout << ((game.players[plyr].markers[2] == 108) ? '3' : '.');
        cout << ((game.players[plyr].markers[3] == 108) ? '4' : '.');
        plyr = tColor(int(plyr) + 1);
        setColor(plyr);
        cout << "                    ";
        space += 17;
    }
    cout << endl << endl;
    setColor(Gray);
}
void setColor(tColor color)
{
    switch (color)
    {
    case Yellow:
        cout << "\x1b[33;40m";
        break;
    case Blue:
        cout << "\x1b[34;40m";
        break;
    case Red:
        cout << "\x1b[31;40m";
        break;
    case Green:
        cout << "\x1b[32;40m";
        break;
    case Gray:
    case None:
        cout << "\x1b[97;40m";     // \x1b[90;107m
        break;
    }
}
void initialize(tGame& game)
{
    int temp;

    srand(time(NULL));
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        game.players[i].color = tColor(i);
        for (int j = 0; j < NUM_PLAYERS; j++)
        {
            game.players[i].markers[j] = -1;
        }
    }

    for (int i = 0; i < NUM_SPACES; i++)
    {
        game.spaces[i].lane1 = None;
        game.spaces[i].lane2 = None;
    }

    temp = rand();
    temp %= NUM_PLAYERS;
    game.playerTurn = tColor(temp);
    setColor(Gray);

    game.lastMarkerMoved = 0;
    game.reward = 0;
    game.roll = -1;
    game.sixes = 0;
}
void initColors()
{
#ifdef _WIN32
    for (DWORD stream : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE})
    {
        DWORD mode;
        HANDLE handle = GetStdHandle(stream);

        if (GetConsoleMode(handle, &mode))
        {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(handle, mode);
        }
    }
#endif
}
void pause()
{
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

