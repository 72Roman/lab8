/**
 * @file
 * @brief send response at json-format to client
 */

#ifndef JSONCREATE_H
#define JSONCREATE_H

#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>


#define path "/home/romario/progbase2/labs/lab8/data/Websites.json"
#define data "/home/romario/progbase2/labs/lab8/data/data.txt"

/**
 * @brief get information about server
 * @param str
 * @return void
 */
void JsonCreate_Info_about_server(char * str);


/**
 * @brief get json-array with information about websites
 * @param str
 * @return void
 */
void JsonCreate_Get_all_websites(char * str);



/**
 * @brief get json-object with count of bytes, name of file and file content
 * @param str
 * @return void
 */
void JsonCreate_Get_information_about_file(char * str);



/**
 * @brief get json-object with key and value set by user
 * @param key, value, str
 * @return json-object or error code
 */
char * JsonCreate_Get_website_by_key_and_value(char * key, char * value, char * str);



/**
 * @brief get json-object with id set by user
 * @param id, str
 * @return json-object or error code
 */
char * JsonCreate_Get_website_by_id(int id, char *str);




/**
 * @brief get json-object with count of numbers and average value of this numbers
 * @param str
 * @return json-object
 */
void JsonCreate_Get_count_and_average_from_file(char * str);














#endif