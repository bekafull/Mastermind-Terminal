#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

char* read_input_number()
{
    int numberzero = 0;
    char sign;
    char* place = malloc(10);

    for (int i = 0; (i = read(0, &sign, 1)) > 0; i++)
    {
        if (sign == '\n')
        {
            return place;
        }
        else
        {
            place[numberzero] = sign;
            numberzero++;
        }
    }
    return 0;
}

int miss(char* code, char* inp)
{
    int missp = 0;
    for (int i = 0; code[i] != '\0'; i++)
    {
        for (int b = 0; inp[b] != '\0'; b++)
        {
            if (code[i] == inp[b] && i != b)
            {
                missp++;
            }
        }
    }
    return missp;
}

int well(char* code, char* inp)
{
    int wellp = 0;
    for (int i = 0; code[i] != '\0'; i++)
    {
        if (code[i] == inp[i])
        {
            wellp++;
        }
    }
    return wellp;
}

bool checksome(char* az)
{
    for (int i = 0; az[i] != '\0'; i++)
    {
        if (az[i] < '0' || az[i] > '9')
        {
            return false;
        }
    }
    for (int l = 0; l < 3; l++)
    {
        for (int b = l + 1; b < 4; b++)
        {
            if (az[l] == az[b])
            {
                return false;
            }
        }
    }
    return true;
}

bool somparesome(char* com, char* nill)
{
    int i = 1;
    if (strlen(com) != strlen(nill))
    {
        return false;
    }
    if (com[i] != nill[i])
    {
        return true;
    }
    return false;
}

bool consictsome(char* a, char b)
{
    for (int i = 0; a[i] != '\0';)
    {
        if (a[i] == b)
        {
            return false;
        }
        i++;
    }
    return true;
}

char* randint()
{
    srand(time(0));
    char* a = malloc(4);
    char b;
    int i = 0;
    while (i < 4)
    {
        b = rand() % 8 + '0';
        if (consictsome(a, b) == 1)
        {
            a[i] = b;
            i++;
        }
    }
    return a;
}

int main(int args, char* argv[])
{
    char* code = malloc(4);
    code = 0;
    int round = 10;
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");
    for (int i = 1; i < args; i++)
    {
        if (somparesome(argv[i], "-c") == 0)
        {
            i++;
            code = argv[i];
        }
        else if (somparesome(argv[i], "-t") == 0)
        {
            i++;
            round = atoi(argv[i]);
        }
    }

    int all_rand = 1999;
    if (code == 0)
    {
        code = randint();
    }
    for (int n = 0; n < round; n++)
    {
        if (all_rand != n)
        {
            printf("---\n");
            printf("Round %d\n", n);
        }
        write(1, ">", 1);
        char* inp = malloc(10);
        inp = read_input_number();
        all_rand = n;
        if (checksome(inp) == 0)
        {
            printf("Wrong input!\n");
            n--;
        }

        else if (checksome(inp) == 1)
        {
            if (well(code, inp) == 4)
            {
                printf("Congratz! You did it!\n");
            }
            else
            {
                printf("\nWell placed pieces: %d\n", well(code, inp));
                printf("Misplaced pieces: %d\n", miss(code, inp));
            }
        }
    }
    return 0;
}