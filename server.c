#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <err.h>
#include <event.h>
#include <evhttp.h>
#include <string.h>
#include "jsonCreate.h"
#include "uriRequest.h"

void analyze(struct evhttp_request * req, void * arg);
char *getRespond(const char * uri, char * respond);

int main() {
    struct evhttp *httpd;
    event_init();
    httpd = evhttp_start("127.0.0.1", 3000);
    evhttp_set_gencb(httpd, analyze, NULL);
    event_dispatch();
    evhttp_free(httpd);
    return 0;
}


char *getRespond(const char *uri, char *respond) {
    if (strcmp(uri, "/") == 0) {
        JsonCreate_Info_about_server(respond);
    } else if(strcmp(uri,"/favorites") == 0){
        JsonCreate_Get_all_websites(respond);
    } else if(strcmp(uri, "/file") == 0) {
		JsonCreate_Get_information_about_file(respond);
	} else if(strcmp(uri, "/file/data") == 0) {
		JsonCreate_Get_count_and_average_from_file(respond);
	} else if (UriRequest_is_id_request(uri)) {
        JsonCreate_Get_website_by_id(UriRequest_get_Id(uri),respond);
    } else if(UriRequest_is_key_and_value_request(uri)){
        Request keyValue = UriRequest_get_key_and_value(uri);
        JsonCreate_Get_website_by_key_and_value(keyValue.key,keyValue.value,respond);
    }
    else respond = NULL;
    return respond;
}

void analyze(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf;
    buf = evbuffer_new();
    if (buf == NULL) err(1, "failed to create response buffer");
    char resp[10000] = "";
    getRespond(evhttp_request_uri(req), resp);
    if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
        evhttp_send_reply(req, HTTP_BADMETHOD, "BAD METHOD", buf);
    } else if (resp == NULL || strlen(resp) == 0) {
        evhttp_send_reply(req, HTTP_NOTFOUND, "NOT FOUND", buf);
    } else {
        evbuffer_add_printf(buf, "%s\n", resp);
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
    }
}


