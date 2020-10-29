/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 23, 2020
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>

using namespace std;

enum tGenre
{
    action = 1,
    adventure,
    scify,
    comedy,
    drama,
    mystery,
    horror
};
enum tLanguage
{
    spanish = 1,
    english,
    french,
    german,
    italian,
    portuguese
};

tGenre readGenre();
string genreToStr(tGenre genre);
tLanguage readLanguage();
string languageToStr(tLanguage lang);

int main()
{
    const string FILE_NAME = "rental.txt";
    string title, director, nif, date;
    bool is_subtitled;
    int minutes, rental_days, temp, rental_n;
    char answer;
    tGenre genre;
    tLanguage language, subtitle;

    ifstream inputFile;

    // ------------------------------------- Reading input & creating output -------------------------------------
    ofstream outputFile;
    outputFile.open(FILE_NAME);

    cout << "Film title: (# to end): ";
    getline(cin, title);
    outputFile << title << endl;
    while (title != "#"){
        cout << "Film director: ";
        getline(cin, director);
        genre = readGenre();
        language = readLanguage();
        cout << "Film subtitles (y/n): ";
        cin >> answer;
        is_subtitled = (tolower(answer) == 'y');
        if (is_subtitled)
            subtitle = readLanguage();
        cout << "Minutes: ";
        cin >> minutes;
        cout << "Client NIF: ";
        cin >> nif;
        cout << "Rental date: ";
        cin >> date;
        cout << "Rental days: ";
        cin >> rental_days;

        outputFile << director << endl;
        outputFile << genre << endl << language << endl;
        outputFile << answer << endl;
        if (is_subtitled){
            outputFile << subtitle << endl;
        }
        outputFile << minutes << endl;
        outputFile << nif << endl << date << endl << rental_days << endl;

        cout << "Film title: (# to end): ";
        cin.get();
        getline(cin, title);
        outputFile << title << endl;
    }

    // ------------------------------------- Reading input & creating output -------------------------------------
    cout << endl << endl;
    inputFile.open(FILE_NAME);
    if (inputFile.is_open())
    {
        rental_n = 1; 
        getline(inputFile, title);
        while (title != "#"){
            getline(inputFile, director);
            inputFile >> temp;
            genre = (tGenre) temp; 
            inputFile >> temp;
            language = (tLanguage) temp;
            inputFile >> answer;
            is_subtitled = (tolower(answer) == 'y');
            if (is_subtitled){
                inputFile >> temp;
                subtitle = (tLanguage) temp;
            }
            inputFile >> minutes;
            inputFile >> nif;
            inputFile >> date;
            inputFile >> rental_days;

            // ----------------------------- Formatted output --------------------------------
            // Movie
            cout << "Rental " << rental_n << endl;
            cout << title << " (" << director << "), " << genreToStr(genre) << ", " << languageToStr(language);
            if (is_subtitled)   
                cout << " (subt. " << languageToStr(subtitle) << ")";
            cout << ", " << minutes << " min." << endl;

            // Client
            cout << "Client: " << nif << " - " << date << ", " << rental_days << " days" << endl;
            cout << "----------" << endl;

            rental_n++;
            inputFile.get();
            getline(inputFile, title);
        }
    }
    
    inputFile.close();
    outputFile.close();

    return 0;
}

tGenre readGenre()
{
    int genre;
    tGenre result;

    cout << "Film genre:" << endl;
    cout << "1 - Action" << endl;
    cout << "2 - Adventure" << endl;
    cout << "3 - Science Fiction" << endl;
    cout << "4 - Comedy" << endl;
    cout << "5 - Drama" << endl;
    cout << "6 - Mystery" << endl;
    cout << "7 - Horror" << endl;
    cout << "Choose a genre: ";
    cin >> genre;

    result = (tGenre)genre;

    return result;
}

string genreToStr(tGenre genre)
{
    string result;

    if (genre == action)
    {
        result = "Action";
    }
    if (genre == adventure)
    {
        result = "Adventure";
    }
    if (genre == scify)
    {
        result = "Scify";
    }
    if (genre == comedy)
    {
        result = "Comedy";
    }
    if (genre == horror)
    {
        result = "Horror";
    }
    if (genre == drama)
    {
        result = "Drama";
    }
    if (genre == mystery)
    {
        result = "Mystery";
    }
    if (genre == horror)
    {
        result = "Horror";
    }

    return result;
}

tLanguage readLanguage()
{
    int lang;
    tLanguage result;

    cout << "Film genre:" << endl;
    cout << "1 - Spanish" << endl;
    cout << "2 - English" << endl;
    cout << "3 - French" << endl;
    cout << "4 - German" << endl;
    cout << "5 - Italian" << endl;
    cout << "6 - Portuguese" << endl;
    cout << "Choose a language: ";
    cin >> lang;

    result = (tLanguage)lang;

    return result;
}

string languageToStr(tLanguage lang)
{
    string result;

    if (lang == spanish)
    {
        result = "Spanish";
    }
    if (lang == english)
    {
        result = "English";
    }
    if (lang == french)
    {
        result = "French";
    }
    if (lang == german)
    {
        result = "German";
    }
    if (lang == italian)
    {
        result = "Italian";
    }
    if (lang == portuguese)
    {
        result = "Portuguese";
    }

    return result;
}