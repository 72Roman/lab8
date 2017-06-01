
/**
 * @file
 * @brief module, that parse uri request
 */
#ifndef URIREQUEST_H 
#define URIREQUEST_H

#include <stdbool.h>

#define STRING_SIZE 300


/**
    @struct Request
    @brief defines a generic Request data type
*/
typedef struct {
    char key[STRING_SIZE];
    char value[STRING_SIZE];
} Request;


/**
 * @brief get key and value from uri, that set by user
 * @param uri
 * @return new struct Request with information set by user
 */
Request UriRequest_get_key_and_value(const char * uri);




/**
 * @brief check that uri contains id request
 * @param uri
 * @return true if this is id request
 */
bool UriRequest_is_id_request(const char * uri);



/**
 * @brief get id from uri
 * @param uri
 * @return value of id
 */
int UriRequest_get_Id(const char * uri);



/**
 * @brief check that uri contains key and value request
 * @param uri
 * @return true if this is key and value request
 */
bool UriRequest_is_key_and_value_request(const char * uri);

#endif