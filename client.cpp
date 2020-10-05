#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MaxOutput 300

//this function display client how to use this product
void usage()
{
    char output[MaxOutput];
    int ret = snprintf(output, MaxOutput,
        "\t%s\n\t%s\n\t%s\n\t%s\n",
        "[usage]",
        "[-s]   sleep or wake up now"
        "[-w]   start or stop work/study now"
        "[-p]   start or stop play telephone now"
        );
    if (ret > 0)
        printf("%s", output);
    else
        printf("%s", "The usage is wrong\n");
}
#define MaxTimeChar 100
//This function is used to show the time now
int getTimeNow(char* input)
{
    time_t  now;
    struct  tm* w;
    time(&now);
    w = localtime(&now);
    char timeNow[MaxTimeChar];
    snprintf(timeNow, MaxTimeChar,
        "%04d/%02d/%02d %02d:%02d:%02d\n",
        w->tm_year + 1900,
        w->tm_mon + 1,
        w->tm_mday,
        w->tm_hour,
        w->tm_min,
        w->tm_sec);
    strncpy(input, timeNow, MaxTimeChar);
    return 0;
}
int getTimeYear()
{
    time_t  now;
    struct  tm* w;
    time(&now);
    w = localtime(&now);
    return w->tm_year + 1900;
}
int getTimeMonth()
{
    time_t  now;
    struct  tm* w;
    time(&now);
    w = localtime(&now);
    return w->tm_mon + 1;
}
int getTimeDay()
{
    time_t  now;
    struct  tm* w;
    time(&now);
    w = localtime(&now);
    return w->tm_mday;
}

int getPathToday(char* pathToday);
int actNow(const char action)
{
    if (!isalpha(action))
        return -1;
    char actMessage[100];
    char tNow[MaxTimeChar];
    getTimeNow(tNow);

    switch (action)
    {
    case 's':
        snprintf(actMessage,
            100,
            "%05s=%s\n",
            "sleep",
            tNow
            );
        break;
    case 'w':
        snprintf(actMessage,
            100,
            "%05s=%s\n",
            "work",
            tNow
            );
        break;
    case 'p':
        snprintf(actMessage,
            100,
            "%05s=%s\n",
            "phone",
            tNow
            );
        break;
    }
    printf("%s", actMessage);

    char pathToday[100];
    getPathToday(pathToday);
    FILE* file = fopen(pathToday, "a");
    if (file == NULL)
    {
        printf("open error!\n");
        return 0;
    }
    fprintf(file, "%s\n", actMessage);
    fclose(file);
    return 0;
}
int getPathToday(char* pathToday)
{
    snprintf(
        pathToday,
        100,
        "%d.%d.%d.txt",
        getTimeYear(),
        getTimeMonth(),
        getTimeDay()
        );
    return 0;
}

int main(int argc, char** argv)
{
    actNow('s');
    char pathToday[100];
    getPathToday(pathToday);
    printf("%s\n", pathToday);
}
