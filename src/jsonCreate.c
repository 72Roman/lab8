#include <jansson.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "jsonCreate.h"


typedef enum {
	NUMBER, INFO, FILES, WRONG_TYPE 
}KEY;

void Read_text_from_file(char * filename, char * str) {
	FILE *dataFile = fopen(filename, "r");
    int textIndex = 0;
    while (!feof(dataFile)) {
        str[textIndex] = (char) fgetc(dataFile);
        textIndex++;
    }
    str[textIndex - 1] = '\0';
    fclose(dataFile);
}

void JsonCreate_Info_about_server(char * str) {
	json_t * obj = json_object();
	time_t date = time(NULL);
	char * timeStr = ctime(&date);
    timeStr[strlen(timeStr) - 1] = '\0';
    json_object_set_new(obj, "title", json_string("Server"));
    json_object_set_new(obj, "developer", json_string("Roman Yereshko"));
    json_object_set_new(obj, "time", json_string(timeStr));
    char *jsonString = json_dumps(obj, JSON_INDENT(2));
    strcpy(str, jsonString);
    free(jsonString);
    json_decref(obj);
}

KEY Is_valid_key(const char * key) {
	if(strcmp(key, "id") == 0 || strcmp(key, "visitors") == 0 || strcmp(key, "rating") == 0) {
		return NUMBER;
	} else if(strcmp(key, "host") == 0) {
		return INFO;
	} else return WRONG_TYPE;
}


void JsonCreate_Get_all_websites(char * str) {
	Read_text_from_file(path, str);
}


char * JsonCreate_Get_website_by_id(int id, char *str){
    json_error_t err;
    FILE *fin = fopen(path, "r");
    json_t *websites = json_loadf(fin, 0, &err);
    json_t *website = NULL;
    if (!websites) {
        assert(0 && "Error parsing json file");
    }
    int index = 0;
    json_array_foreach(websites, index, website) {
        if (json_integer_value(json_object_get(website, "id")) == id) {
            char *jsonString = json_dumps(website, JSON_INDENT(2));
            strcpy(str, jsonString);
            free(jsonString);
            json_decref(websites);
            return str;
        }
    }
	fclose(fin);
    return NULL;
}

char * JsonCreate_Get_website_by_key_and_value(char * key, char * value, char * str) {
    //MAKING SPACES
    //for (int i = 0; i < strlen(key); i++) if (key[i] == '+') key[i] = ' ';
    //for (int i = 0; i < strlen(value); i++) if (value[i] == '+') value[i] = ' ';

    KEY keyType = Is_valid_key(key);
    if (keyType == WRONG_TYPE) {
        strcpy(str, "404 Not Found");
        return str;
    }

    //JSON REDING
    json_error_t error;
    json_t *jsonArray = json_load_file(path, 0, &error);;
    if (!jsonArray) {
        assert(0 && "Error parsing json file");
    }

    //FORMING JSON
    size_t index = 0;
    json_t *jsonWebsite;
    json_t *newJsonArray = json_array();
    bool isFoundOne = false;
    json_array_foreach(jsonArray, index, jsonWebsite) {
        json_t *jsonValue = json_object_get(jsonWebsite, key);
        if (keyType == NUMBER) {
            if (json_integer_value(jsonValue) == atoi(value)) {
                json_array_append(newJsonArray, jsonWebsite);
                isFoundOne = true;
            }
        } else if (keyType == INFO) {
            if (strcmp(json_string_value(jsonValue), value) == 0) {
                json_array_append(newJsonArray, jsonWebsite);
                isFoundOne = true;
            }
        }
    }
    if (!isFoundOne) {
        str = NULL;
    } else {
        char *jsonString = json_dumps(newJsonArray, JSON_INDENT(2));
        strcpy(str, jsonString);
        free(jsonString);
        json_decref(jsonArray);
        json_decref(newJsonArray);
    }
    return str;
}

void JsonCreate_Get_information_about_file(char * str) {
	char buffer[100] = "";
	Read_text_from_file(data, buffer);
	int length = strlen(buffer);
	//create json
	json_t * obj = json_object();
    json_object_set_new(obj, "name", json_string("data.txt"));
    json_object_set_new(obj, "length", json_integer(length));
    json_object_set_new(obj, "contents", json_string(buffer));
    char *jsonString = json_dumps(obj, JSON_INDENT(2));
    strcpy(str, jsonString);
    free(jsonString);
    json_decref(obj);
}

void JsonCreate_Get_count_and_average_from_file(char * str) {
	char buffer[100] = "";
	Read_text_from_file(data, buffer);
	char * mPtr = buffer;
	int value = 0;
	int count = 0;
	int sum = 0;
	while(mPtr != NULL) {
		value = atoi(mPtr);
		count++;
		mPtr = strchr(mPtr, ',');
		sum += value;
		if(mPtr != NULL) {
			mPtr++;
		} else {
			char * newPtr = strrchr(buffer, ',');
			value = atoi(newPtr);
			count++;
			sum += value;
		}
	}
	double average =(double) sum / count;
	json_t * obj = json_object();
    json_object_set_new(obj, "count", json_integer(count));
    json_object_set_new(obj, "average", json_real(average));
	char *jsonString = json_dumps(obj, JSON_INDENT(2));
    strcpy(str, jsonString);
    free(jsonString);
    json_decref(obj);
}