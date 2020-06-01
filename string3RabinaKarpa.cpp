
#include "TXLib.h"

//сравнение строк: 0 - если строки равны, 1 - если первая больше, -1 - если первая меньше
int myCompare (const char word1[], int len1, const char word2[], int len2, int start1 = 0, int start2 = 0);

//поиск позиции одной строки (word) в большей строке (text)
int myPosWord (const char word[], const char text[]);

int myStrLen (const char str[]);
int RunTests();

int mySummaKodov (const char word[], int start, int len);

bool myRabinKarp (int kod, const char text[], int start, int len);

int main()
    {
    RunTests();

    char str1[100] = "";
    char str2[100] = "";

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

    while (str[len] != '\0') len++;
    return len;
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
    int kod = mySummaKodov (word, 0, lenWord);

    for (int i = 0; i < lenText - lenWord + 1; i++)
        {
        if (myRabinKarp (kod, text, i, lenWord))
            if (myCompare (word, lenWord, text, lenWord, 0, i) == 0)
            {
            if (word[0] != '\0') return i + 1;
            else return 0;
            }
        }
    return 0;
    }

int mySummaKodov (const char word[], int start, int len)
    {
    int s = 0;

    for (int i = start; i < start + len; i++)
        {
        s += word[i];
        }

    return s;
    }

bool myRabinKarp (int kod, const char text[], int start, int len)
    {
    if (kod == mySummaKodov (text, start, len)) return true;
    return false;
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

