/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stdio.h>

#define returnWithError(msg, ret) \
        fprintf(stderr, "Error: %s at line %d in file %s\n", \
        msg, __LINE__, __FILE__); \
        return ret;
