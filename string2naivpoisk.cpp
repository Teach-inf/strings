
#include "TXLib.h"
//поиск позиции буквы в строке
int myPosN (char symbol, const char text[], int start, int len);

//сравнение строк: 0 - если строки равны, 1 - если первая больше, -1 - если первая меньше
int myCompare (const char word1[], int len1, const char word2[], int len2, int start1 = 0, int start2 = 0);

//поиск позиции одной строки (word) в большей строке (text)
int myPosWord (const char word[], const char text[]);

int myStrLen (const char str[]);
int RunTests();

int main()
    {
    #ifdef MY_COMPUTER
    RunTests();
    #endif

    char str1[100] = "";
    char str2[100] = "";

    printf ("Please, enter a first  string (word) len <= 100 \n");
    gets (str1);
    printf ("Please, enter a second string (text) len <= 100 \n");
    gets (str2);

    /*
    char symb;
    printf ("Please, enter a symbol \n");
    scanf  ("%c", &symb);

    printf ("Number of inclusion symbol in your first  string = %d\n", myPosN (symb, str1, 0, myStrLen(str1)));
    printf ("Number of inclusion symbol in your second string = %d\n", myPosN (symb, str2, 0, myStrLen(str2)));
    printf ("\n");

    switch (myCompare (str1, myStrLen(str1), str2, myStrLen(str2)))
        {
        case  0: puts("Strings are equal");       break;
        case  1: puts("First  string is bigger"); break;
        case -1: puts("Second string is bigger"); break;
        }
    */

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

//поиск позиции буквы в строке с заранее известной длиной len, начиная с номера start
int myPosN (char symbol, const char text[], int start, int len)
    {
    for (int i = start; i < len; i++)
        {
        if (text[i] == symbol) return i + 1;
        }
    return 0;
    }

//сравнение строк: 0 - если строки равны, 1 - если первая больше, -1 - если первая меньше
int myCompare (const char word1[], int len1, const char word2[], int len2, int start1, int start2)
    {
    if (len1 == len2)
        {
        int i = 0;

        while ((word1[i + start1] == word2[i + start2]) && (i < len1) && (i < len2))
            {
            i++;
            }

        if (i == len1) return 0;

        if (word1[i + start1] > word2[i + start2]) return 1;

        return -1;
        }

    else if (len1 < len2) return -1;
         else return 1;
    }

//поиск позиции одной строки (word) в большей строке (text)
int myPosWord (const char word[], const char text[])
    {
    int lenText = myStrLen (text);
    int lenWord = myStrLen (word);

    for (int i = 0; i < lenText - lenWord + 1; i++)
        {
        int  j = myPosN (word[0], text, i, lenText - lenWord + 1);

        if (j == 0) return 0;
        j--;

        if (myCompare (word, lenWord, text, lenWord, 0, j) == 0)
            {
            if (word[0] != '\0') return j + 1;
            else return 0;
            }
        }
    return 0;
    }

int RunTests()
    {
    $unittest (myPosWord ("qw",  "qw"),              1);
    $unittest (myPosWord ("qw",  "qwewee"),          1);
    $unittest (myPosWord ("qw",  "wewwwqweeqweqwe"), 6);
    $unittest (myPosWord (" qw", "qwde qwd"),        5);
    $unittest (myPosWord ("",    "qw"),              0);
    $unittest (myPosWord ("",    ""),                0);
    $unittest (myPosWord ("qw",  ""),                0);
    $unittest (myPosWord ("qw",  "ewewq"),           0);
    $unittest (myPosWord ("88",  "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567788"), 99);

    return 0;
    }

