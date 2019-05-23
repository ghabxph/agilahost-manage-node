#pragma once
#include "lib/include/s_Value.hpp"

/**
 * Key
 */
struct s_Key {

    /**
     * Pointer pointing to address of key
     */
    char *address;

    /**
     * Length of key from address (char pointer)
     */
    int length;

    /**
     * Pointer to next key
     */
    s_Key *next;

    /**
     * Pointer to value
     */
    s_Value *value;
};

