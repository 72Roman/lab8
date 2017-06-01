#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "uriRequest.h"


Request UriRequest_get_key_and_value(const char * uri) {
    Request result = {"", ""};
    char * mPtr = (char *) uri;
    mPtr = strchr(mPtr, '?');
    mPtr++;
	int i = 0;
    while(*mPtr != '=') {
		result.key[i] = *mPtr;
		mPtr++;
		i++;
	}
    mPtr++;
   	i = 0;
	while(*mPtr != '\0') {
		result.value[i] = *mPtr;
		mPtr++;
		i++;
	}   
    return result;
}


bool UriRequest_is_id_request(const char * uri) {
	char favorites[] = "/favorites/";
    char *mPtr = (char *) uri;
    int index = 0;
    while (index < strlen(favorites)) {
        if (*mPtr != favorites[index]) {
			return false;
		}
        mPtr++;
        index++;
    }
    do {
        if (!isdigit(*mPtr)) {
			return false;
		}
        mPtr++;
    } while (*mPtr != '\0');
    return true;
}

int UriRequest_get_Id(const char * uri) {
	char favorites[] = "/favorites/";
    char *mPtr = (char *) uri;
    mPtr += strlen(favorites);
    return atoi(mPtr);
}


bool UriRequest_is_key_and_value_request(const char * uri) {
	char favorites[] = "/favorites?";
    char *mPtr = (char *) uri;
    for (int i = 0; i < strlen(favorites); i++) {
        if (favorites[i] != *mPtr) {
			return false;
		}
        mPtr++;
    }
    if (strchr(mPtr, '=') == NULL)  {
		return false;
	}
    mPtr = strchr(mPtr, '=');
    mPtr++;
    if (strchr(mPtr, '=') != NULL || strchr(mPtr, '/') != NULL || *mPtr == '\0') {
        return false;
	}
    return true;
}


	



