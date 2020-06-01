
#include "TXLib.h"

#define DEBUG
#define TESTS

const int N = 100;

//поиск позиции одной строки (word) в большей строке (text)
int myPosWord (const char word[], const char text[]);

int myStrLen (const char str[]);

int RunTests();

void Table (int* tableSdvig, const char word[], int lenWord);

int main()
    {
    #ifdef TESTS
    RunTests();
    #endif

    txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
    char str1[N] = "";
    char str2[N] = "";

    printf ("Please, enter a first  string (word) len <= 100 \n");
    gets (str1);
    printf ("Please, enter a second string (text) len <= 100 \n");
    gets (str2);

    printf ("\n");
    printf ("Number of inclusion first string in your second string = %d\n", myPosWord (str1, str2));

    return 0;
    }

int myStrLen (const char str[])
    {
    int len = 0;
    assert (0 <= len);     //не понимаю как правильно

    while (str[len] != '\0') len++;
    return len;
    }

//поиск позиции одной строки (word) в большей строке (text)
int myPosWord (const char word[], const char text[])
    {
    int lenText = myStrLen (text);
    int lenWord = myStrLen (word);

    int tableSdvig [256] = {};

    Table (tableSdvig, word, lenWord);

                    //for (int i = 32; i < 123; i++) printf ("[%c]=%d ", i, tableSdvig[i]);
                    //printf ("\n");
    #ifdef DEBUG
    txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_BLUE);
    printf ("Table of sdvig\n");

    txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);

    for (int i = 0; i < 256; i++)
        for (int j = 0; j < lenWord; j++)

            if (i == word[j])
                {
                printf ("[%c]=%d ", i, tableSdvig[i]);
                break;
                }

    printf ("\n\n");

    for (int i = 0; i < lenText; i++) printf ("%d", (i + 1)/10);
    printf ("\n");

    for (int i = 0; i < lenText; i++) printf ("%d", (i + 1)%10);
    printf ("\n");

    txSetConsoleAttr (FOREGROUND_YELLOW | BACKGROUND_BLUE);
    puts (text);
    #endif

if (lenWord == 0) return 0;

    int i = lenWord - 1;

    while  (i < lenText)
        {
        #ifdef DEBUG
        for (int ii = 0; ii < i - lenWord + 1; ii++) printf (" ");

        txSetConsoleAttr (FOREGROUND_LIGHTGREEN | BACKGROUND_DARKGRAY);
        for (int ii = 0; ii < lenWord; ii++) printf ("%c", word[ii]);
        printf ("\n");

        txSetConsoleAttr (FOREGROUND_WHITE | BACKGROUND_BLACK);
        #endif

        int j = 0;

        for (j = 0; j < lenWord; j++)
            if (text[i - j] != word[lenWord - 1 - j]) break;

        if (j == lenWord) return i + 2 - lenWord;

        int code = (unsigned char) text[i-j];

        if      (tableSdvig[code] == lenWord) i += tableSdvig[code];
        else if (tableSdvig[code] != 0)       i += tableSdvig[code] - j;
             else i ++;
        }

    return 0;
    }

void Table (int* tableSdvig, const char word[], int lenWord)
    {
    for (int i = 0; i < 256; i++)
        {
        tableSdvig [i] = lenWord;
        }

    for (int i = 0; i < lenWord; i++)
        {
        //int code = word[i];
        //if (code < 0) code += 256;  это костыль))
        int code = (unsigned char) word[i];
        tableSdvig [code] = lenWord - i - 1;
        }
    }

int RunTests()
    {
    $unittest (myPosWord ("qw",  "qw"),              1);
    $unittest (myPosWord ("qw",  "qwewee"),          1);
    $unittest (myPosWord ("qw",  "wewwwqweeqweqwe"), 6);
    $unittest (myPosWord ("qw",  "qede dqw"),        7);
    $unittest (myPosWord (" qw", "qwde qwd"),        5);
    $unittest (myPosWord ("",    "qw"),              0);
    $unittest (myPosWord ("",    ""),                0);
    $unittest (myPosWord ("qw",  ""),                0);
    $unittest (myPosWord ("qw",  "ewewq"),           0);
    $unittest (myPosWord ("88",  "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567788"), 99);

    $unittest (myPosWord ("DABA",  "ABACABADABACABA"), 8);
    $unittest (myPosWord ("DABA",  "ABACABADABCCABADABAA"), 16);
    $unittest (myPosWord ("DABA",  "ABACABADABCCABADABADABA"), 16);
    $unittest (myPosWord ("DABA",  "ABACABADABCCABADABAABACACD"), 16);

    $unittest (myPosWord ("при",  "¬асилий, привет!"), 10);
    $unittest (myPosWord ("Ћ»÷",  "ѕќЋ»÷»я"), 3);
    $unittest (myPosWord ("корова",  "ковкорова"), 4);

    $unittest (myPosWord ("korova",  "kovkorova"), 4);
    $unittest (myPosWord ("world",  "worlrworlrworld"), 11);
    $unittest (myPosWord ("world",  "worlrworldworld"),  6);
    $unittest (myPosWord ("world",  "worldworldworld"),  1);
    $unittest (myPosWord ("wor ld",  "wor lrwor lrwor ld"), 13);

    $unittest (myPosWord ("DABA",  "ABACABADABCABDABCDABCDDDABAA"), 24);

    $unittest (myPosWord ("qwertyuio",  "asdftyuioqwertqwertqqqqhjklyuioqwertyuiqwertyuiooooo"), 40);
    return 0;
    }

