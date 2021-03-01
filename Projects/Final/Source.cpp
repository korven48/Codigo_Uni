#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits> // For pause()
#ifdef _WIN32 // Automatically defined in Visual Studio
#include <windows.h>
#undef max // To be able to use max() in pause()
#endif
using namespace std;

typedef enum { Yellow = 0, Blue, Red, Green, Gray, None } tColor;
const int NUM_PLAYERS = 4;
const int NUM_MARKERS = 4;
const int NUM_SPACES = 68;
const bool Debug = true;
const bool debugRoll = false;
const string FileName = "C:\\Users\\lucas\\Desktop\\Informatica\\FP1\\Projects\\Final\\canMove.txt";

typedef int tMarkers[NUM_MARKERS];

struct tPlayer {
    tColor color;
    tMarkers markers;
};

typedef tPlayer tPlayers[NUM_PLAYERS];

struct tSpace {
    tColor lane1, lane2;
};

typedef tSpace tSpaces[NUM_SPACES];

struct tGame {
    tSpaces spaces;
    tPlayers players;
    tColor playerTurn;
    int roll;
    int reward;
    int sixes;
    int lastMarkerMoved = -1;
};

void display(const tGame& game);
void setColor(tColor color);
void pause();
void initColors();

bool isSafe(int space);
int startSpace(tColor color);
int zanataSpace(tColor color);
string colorToStr(tColor color);
int readDice(ifstream& file);

void initialize(tGame& game);
int howMany(const tMarkers player, int space);
int firstAt(const tMarkers player, int space);
int secondAt(const tMarkers player, int space);

void markerOut(tGame& game);
void toHome(tGame& game, int space);
bool process5(tGame& game, bool& nextPlayer);

bool bridge(const tGame game, int space);
bool canMove(tGame& game, int marker, int& space);
void move(tGame& game, int marker, int space);
bool isHome(tGame& game, int marker);

void openBridge(tGame& game, int space, int space2);
bool process6(tGame& game, bool& nextPlayer);

bool allIn(const tGame game);
bool play(tGame& game, bool& winner);
void load(tGame& game, ifstream &file);
int nextSpace(int pos, tColor playerTurn);


int main() {
    tGame game;
    bool nextPlayer = false, noMove;
    bool must = false, winner = false;
    int space = -1, marker = 0, nextTurn;
    ifstream file;

    initColors();
    initialize(game);

    if (Debug) {
        load(game, file);
        cout << "Info loaded" << endl;
    }

    if (!winner) {
        do {

            display(game);

            setColor(game.playerTurn);
            must = false;

            cout << "Turn for the " << colorToStr(game.playerTurn) << " player..." << endl;
            if (game.reward == 0) {
                game.roll = readDice(file);
                cin.get();

                cout << "A " << game.roll << " is rolled" << endl;
            }
            else
                game.roll = game.reward;

            if (game.roll != 0) {
                if (howMany(game.players[game.playerTurn].markers, -1) == NUM_MARKERS && game.roll != 5) {
                    noMove = true;
                    cout << "Cannot leave home without a 5" << endl;
                    if (game.roll == 6) {
                        game.sixes++;
                        if (game.sixes == 3) {
                            nextPlayer = true;
                            cout << "Third six in a row" << endl;
                            pause();
                        }
                        else {
                            nextPlayer = false;
                            cout << "6 rolled. Player will game.roll again" << endl;
                            pause();
                        }
                    }
                }
                else
                {
                    if (game.roll == 5) {
                        must = process5(game, nextPlayer);
                        if (must) {
                            cout << "Marker out(game.reward: " << game.reward << "; nextPlayer: " << (nextPlayer ? "true" : "false") << ")" << endl;
                            pause();
                        }
                        else {
                            cout << "Not able to leave home" << endl;
                            pause();
                        }
                    }
                    if (game.roll == 6) {
                        must = process6(game, nextPlayer);
                    }
                    if (!must) {
                        play(game, winner);
                    }
                }


                if (allIn(game)) {
                    winner = true;
                }
                if ((game.reward == 0) && game.roll != 6 && game.roll != 7) {
                    nextPlayer = true;
                }

                if (nextPlayer) {
                    nextTurn = (game.playerTurn + 1) % 4;
                    game.playerTurn = tColor(nextTurn);
                    game.reward = 0;
                    game.sixes = 0;
                    game.lastMarkerMoved = -1;
                    nextPlayer = false;
                    game.sixes = 0;
                }
            }
            else {
                winner = true;
                cout << "Game ended" << endl;
            }
        } while (!winner);
    }
    if (winner) {
        display(game);
        cout << colorToStr(game.playerTurn) << " is the winner!" << endl;
    }
    pause();
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
        cout << "               ";
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
        cout << "               ";
        space += 17;
    }
    cout << endl << endl;
    setColor(Gray);
}

void setColor(tColor color) {
    switch (color) {
    case Yellow:
        cout << "\x1b[33;107m";
        break;
    case Blue:
        cout << "\x1b[34;107m";
        break;
    case Red:
        cout << "\x1b[31;107m";
        break;
    case Green:
        cout << "\x1b[32;107m";
        break;
    case Gray:
    case None:
        cout << "\x1b[90;107m";
        break;
    }
}

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void initColors() {
#ifdef _WIN32
    for (DWORD stream : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE}) {
        DWORD mode;
        HANDLE handle = GetStdHandle(stream);

        if (GetConsoleMode(handle, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(handle, mode);
        }
    }
#endif
}

bool isSafe(int space) {
    int safe_spaces[12] = { 0, 5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63 };
    int counter = -1;
    bool is_safe = false;
    do
    {
        counter++;
        if (space == safe_spaces[counter])
            is_safe = true;
    } while (safe_spaces[counter] < space);
    return is_safe;
}

int startSpace(tColor color) {
    int startSpaces = 0;

    switch (color)
    {
    case Red:
        startSpaces = 39;
        break;
    case Green:
        startSpaces = 56;
        break;
    case Blue:
        startSpaces = 22;
        break;
    case Yellow:
        startSpaces = 5;
        break;
    }

    return startSpaces;

}

int zanataSpace(tColor color) {
    int zanata;
    zanata = startSpace(color) - 5;
    return zanata;
}

string colorToStr(tColor color) {
    string colorName;

    switch (color) {
    case Red:
        colorName = "Red";
        break;
    case Green:
        colorName = "Green";
        break;
    case Yellow:
        colorName = "Yellow";
        break;
    case Blue:
        colorName = "Blue";
        break;
    case Gray:
        colorName = "Gray";
        break;
    case None:
        colorName = "None";
        break;
    }

    return colorName;
}

int readDice(ifstream& file) {
    int num;
    if (Debug && debugRoll) {
        file.open(FileName);
        file >> num;
        file.get();
        if (num == -1) {
            num = 0;
            file.close();
        }
    }
    if (Debug && !debugRoll) {
        cout << "Roll (0 to exit): ";
        cin >> num;
        cin.get();
    }
    else {
        num = (rand() % 6) + 1;
    }
    return num;
}

void initialize(tGame& game) {
    int num;
    int i = 0, j = 0;

    game.lastMarkerMoved = 0;
    game.reward = 0;
    game.roll = -1;
    game.sixes = 0;

    srand(time(NULL));
    for (i = 0; i < NUM_PLAYERS; i++) {
        game.players[i].color = tColor(i);
        for (j = 0; j < NUM_MARKERS; j++) {
            game.players[i].markers[j] = -1;
        }
    }
    for (int i = 0; i < NUM_SPACES; i++)
    {
        game.spaces[i].lane1 = None;
        game.spaces[i].lane2 = None;
    }
    num = rand() % 4;
    game.playerTurn = tColor(num);
    setColor(Gray);
}

int howMany(const tMarkers player, int space) {
    int counter = 0, i = 0;
    for (i = 0; i < NUM_MARKERS; i++) {
        if (player[i] == space)
            counter++;
    }
    return counter;
}

int firstAt(const tMarkers player, int space) {
    bool found = false;
    int counter = -1, least = -1;
    while ((counter < NUM_MARKERS) && (!found)) {
        counter++;
        if (player[counter] == space)
            found = true;
    }
    if (found)
        least = counter;

    return least;
}

int secondAt(const tMarkers player, int space) {
    bool found = false;
    int counter = 0, greatest = -1;
    counter = NUM_MARKERS - 1;
    while ((counter >= 0) && (!found)) {
        if (player[counter] == space)
            found = true;
        else
            counter--;
    }
    if (found)
        greatest = counter;

    return greatest;
}

void markerOut(tGame& game) {

    int space, markerHome;
    bool found = false;
    space = startSpace(game.playerTurn);
    game.spaces[space].lane2 = game.spaces[space].lane1;

    markerHome = firstAt(game.players[game.playerTurn].markers, -1);
    game.players[game.playerTurn].markers[markerHome] = space;
    game.spaces[space].lane1 = game.playerTurn;
}

void toHome(tGame& game, int space) {
    tColor eliminated;
    int marker;

    eliminated = game.spaces[space].lane2;
    marker = secondAt(game.players[eliminated].markers, space);

    game.players[eliminated].markers[marker] = -1;
    game.spaces[space].lane2 = None;
}

bool process5(tGame& game, bool& nextPlayer) {
    int start, j, marker;
    bool inside = false, outside = false;

    for (j = 0; j < NUM_MARKERS; j++) {
        if (game.players[game.playerTurn].markers[j] == -1)
            inside = true;
    }

    if (inside) {
        start = startSpace(game.playerTurn);
        marker = firstAt(game.players[game.playerTurn].markers, -1);
        if (marker != -1) {
            if (game.spaces[start].lane2 == None) {
                markerOut(game);
                outside = true;
            }
            else {
                if (game.spaces[start].lane2 == game.playerTurn)
                    outside = false;
                else {
                    toHome(game, start);
                    markerOut(game);
                    game.reward = 20;
                    nextPlayer = false;
                    outside = true;
                }
            }
        }
    }

    return outside;
}

bool bridge(const tGame game, int space) {
    bool block = false;

    if (space >= 0 && space < 68) {
        if ((game.spaces[space].lane1 == game.spaces[space].lane2)
            && (game.spaces[space].lane1 != None)) {
            block = true;
        }
    }
    return block;
}


bool canMove(tGame& game, int marker, int& space){

    int moveCount = 0, i;
    bool able = true;
    bool home = false, goal = false;
    bool blocked = false;
    int catwalk = 0;

    if (game.players[game.playerTurn].markers[marker] == 108)
        goal = true;
    if (game.players[game.playerTurn].markers[marker] == -1)
        home = true;

    space = game.players[game.playerTurn].markers[marker];

    while ((!blocked) && (moveCount < game.roll)) {
        if (zanataSpace(game.playerTurn) == space)
            space = 101;
        else if (space > 100)
            space++;
        else if (space == 67)
            space = 0;
        else
            space++;
        for (i = 101; i < 108; i++) {
            catwalk = howMany(game.players[game.playerTurn].markers, i);
            if (catwalk == 2 && space == i && moveCount == game.roll - 1)
                blocked = true;
        }

        if (bridge(game, space) && isSafe(space))
            blocked = true;
        if (space == 108 && moveCount != game.roll - 1)
            blocked = true;
        // if ((game.spaces[space].lane1 != None) && (game.spaces[space].lane2 != None) && moveCount == game.roll - 1)
        //     blocked = true;

        if (!blocked)
            moveCount++;
        else
            blocked = true;

    }

    if (goal || home)
        able = false;
    else if (blocked)
        able = false;
    else
        able = true;

    return able;
}


void move(tGame& game, int marker, int space) {

    int prevSpace;
    prevSpace = game.players[game.playerTurn].markers[marker];
    if (game.spaces[prevSpace].lane1 == game.playerTurn) {
        game.spaces[prevSpace].lane1 = game.spaces[prevSpace].lane2;
        game.spaces[prevSpace].lane2 = None;
    }
    else if (game.spaces[prevSpace].lane2 == game.playerTurn) {
        game.spaces[prevSpace].lane2 = None;
    }

    game.reward = 0;
    game.players[game.playerTurn].markers[marker] = space;
    if (space == 108) {
        game.reward = 10;
        cout << "Marker has reached the goal." << endl;
    }
    if (space <= NUM_SPACES) {
        if (game.spaces[space].lane1 == None) {
            game.spaces[space].lane1 = game.playerTurn;
        }
        else
        {
            if (game.spaces[space].lane1 != game.playerTurn && !isSafe(space)) {
                game.spaces[space].lane2 = game.spaces[space].lane1;
                game.reward = 20;
                cout << "Marker from " << colorToStr(game.spaces[space].lane2) << " has been eaten" << endl;
                toHome(game, space);
                game.spaces[space].lane1 = game.playerTurn;
            }
            else {
                game.spaces[space].lane2 = game.playerTurn;
            }
        }
    }
    game.lastMarkerMoved = marker;
}


bool isHome(tGame& game, int marker) {
    bool inside = false;
    if (game.players[game.playerTurn].markers[marker] == -1)
        inside = true;
    return inside;
}

void openBridge(tGame& game, int space, int space2) {

    int i = 0;
    i = secondAt(game.players[game.playerTurn].markers, space);
    move(game, i, space2);
    game.lastMarkerMoved = i;
}

bool process6(tGame& game, bool& nextPlayer) {

    bool output = false;
    int bridgeSpace1 = -1, bridgeSpace2 = -1;
    bool bridgeFound = false;
    int num_bridges = 0;
    int bridgeMarker1 = 0, bridgeMarker2 = 0;
    int posSpace1 = 0, posSpace2 = 0;
    bool moveM1 = false, moveM2 = false;
    bool allOut = true, can = false;
    int i = 0;

    nextPlayer = false;
    game.reward = 0;
    game.sixes++;

    if (howMany(game.players[game.playerTurn].markers, -1) == 0) {
        game.roll = 7;
        cout << "game.roll is a 7 (all markers out)" << endl;
    }

    if (game.sixes == 3) {
        if (game.lastMarkerMoved != -1) {
            if (game.players[game.playerTurn].markers[game.lastMarkerMoved] < 101) {
                cout << "Last marker moved returns home!" << endl;
                if (firstAt(game.players[game.playerTurn].markers, game.players[game.playerTurn].markers[game.lastMarkerMoved]) == game.lastMarkerMoved) {
                    game.spaces[game.players[game.playerTurn].markers[game.lastMarkerMoved]].lane1 = game.spaces[game.players[game.playerTurn].markers[game.lastMarkerMoved]].lane2;
                    game.spaces[game.players[game.playerTurn].markers[game.lastMarkerMoved]].lane2 = None;
                    game.players[game.playerTurn].markers[game.lastMarkerMoved] = -1;
                }
                else {
                    game.spaces[game.players[game.playerTurn].markers[game.lastMarkerMoved]].lane2 = None;
                    game.players[game.playerTurn].markers[game.lastMarkerMoved] = -1;
                }
                cout << "Last marker moved returns home!" << endl;
            }
            else
                cout << "The marker is safe in the runway to the goal!" << endl;
        }
        nextPlayer = true;
        output = true;
    }
    else {
        for (i = 0; i < NUM_MARKERS - 1; i++) {
            if (game.players[game.playerTurn].markers[i] != -1)
                bridgeFound = bridge(game, game.players[game.playerTurn].markers[i]);
            if (bridgeFound) {
                if (bridgeSpace1 == -1) {
                    bridgeSpace1 = game.players[game.playerTurn].markers[i];
                    num_bridges++;
                }
                else {
                    if (bridgeSpace1 != game.players[game.playerTurn].markers[i]) {
                        if (bridgeSpace2 == -1) {
                            bridgeSpace2 = game.players[game.playerTurn].markers[i];
                            num_bridges++;
                        }
                    }
                }
            }

        }

        if (num_bridges == 1) {
            bridgeMarker1 = secondAt(game.players[game.playerTurn].markers, bridgeSpace1);
            if (canMove(game, bridgeMarker1, posSpace1)) {
                cout << "Bridge in space " << bridgeSpace1 << " is now open!" << endl;
                openBridge(game, bridgeSpace1, posSpace1);
                output = true;
            }
            else {
                cout << "Cannot open the bridge, a regular move will be processed" << endl;
                for (i = 0; i < NUM_MARKERS; i++) {
                    if (canMove(game, i, posSpace1)) {
                        cout << "From space " << game.players[game.playerTurn].markers[i] << " to " << posSpace1 << endl;
                        can = true;
                    }
                }
                if (!can)
                    cout << "Cannot move any marker" << endl;
                nextPlayer = false;
                output = true;
            }
        }

        if (num_bridges == 2) {
            bridgeMarker1 = secondAt(game.players[game.playerTurn].markers, bridgeSpace1);
            bridgeMarker2 = secondAt(game.players[game.playerTurn].markers, bridgeSpace2);

            moveM1 = canMove(game, bridgeMarker1, posSpace1);
            moveM2 = canMove(game, bridgeMarker2, posSpace2);

            if (moveM1 && !moveM2) {
                cout << "Bridge in space " << bridgeSpace1 << " is now open!" << endl;
                openBridge(game, bridgeSpace1, posSpace1);
                output = true;
            }
            if (!moveM1 && moveM2) {
                cout << "Bridge in space " << bridgeSpace2 << " is now open!" << endl;
                openBridge(game, bridgeSpace2, posSpace2);
                output = true;
            }
            if (!moveM1 && !moveM2) {
                cout << "Cannot open the bridges" << endl;
                output = true;
            }
        }
    }

    return output;
}

bool allIn(const tGame game) {
    bool allIn = true;
    for (int i = 0; i < NUM_MARKERS; i++) {
        if (game.players[game.playerTurn].markers[i] != 108)
            allIn = false;
    }
    return allIn;
}

bool play(tGame& game, bool& winner) {
    bool output = true;
    bool able = false;
    int desSpace;
    int marker;

    if (game.reward != 0) {
        cout << "Must count " << game.reward << "!" << endl;
    }
    cout << "Choose the marker you want to move " << endl;
    for (int marker = 0; marker < NUM_MARKERS; marker++) {
        cout << marker + 1 << ": ";
        if (canMove(game, marker, desSpace)) {
            cout << "From space " << game.players[game.playerTurn].markers[marker] << " to " << desSpace << endl;
            able = true;
        }
        else
            cout << "Cannot move" << endl;
    }

    if (able) {
        cout << "marker to move: ";

        cin >> marker;
        cin.get();
        marker--;
        if (canMove(game, marker, desSpace)) {
            move(game, marker, desSpace);
            cout << "game.reward: " << game.reward << endl;
            if (game.reward != 0) output = false;
        }
    }


    return output;
}

void load(tGame& game, ifstream& file) {
    int player, space;

    file.open(FileName);
    if (file.is_open()) {
        for (int i = 0; i < NUM_PLAYERS; i++)
            for (int f = 0; f < NUM_MARKERS; f++) {
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
        file.close();
    }
}
