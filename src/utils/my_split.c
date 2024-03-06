/*
** EPITECH PROJECT, 2022
** B-MUL-100-NAN-1-1-myhunter-axel.eckenberg
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <string.h>
#include <stdlib.h>
#include "utils/my.h"

char **my_split(char const *str, char separator)
{
    int start = 0;
    int end = 0;
    int world_length;
    int i = 0;
    char **result = malloc(sizeof(char *) * (count_words(str, separator) + 1));

    while (str[end] != 0) {
        if (*(str + end + 1) == separator || *(str + end + 1) == 0) {
            world_length = end - start + 1;
            result[i] = malloc(sizeof(char) * (world_length + 1));
            strncpy(result[i], (str + start), world_length);
            result[i][world_length] = 0;
            start = end + 2;
            is_word(result[i], separator, &i);
        }
        end++;
    }
    result[i] = 0;
    return result;
}

int count_words(char const *str, char separator)
{
    int word_count = 0;

    while (*str != 0) {
        if (*(str + 1) == separator) {
            word_count++;
        }
        str++;
    }
    return word_count + 1;
}

bool is_word(char *str, char separator, int *i)
{
    int r = strlen(str) > 0;

    while (*str != 0) {
        r = r && *str != separator;
        str++;
    }
    if (r)
        *i += 1;
    return r;
}
