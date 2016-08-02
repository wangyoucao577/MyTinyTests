// RESTClientSample.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include "curl/curl.h"

#include "json_samples.h"

size_t post_response_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
    printf("Response: %d bytes\n%s", (int)nmemb, (char*)buffer);

    return nmemb;
}



void curl_post_sample()
{
    printf("Enter %s, %s.\n\n", __FUNCTION__, curl_version());

    int max_post_data_bytes = 10240;
    char * post_data = (char*)malloc(max_post_data_bytes);
    if (NULL == post_data) {
        printf("malloc %d bytes failed.\n", max_post_data_bytes);
        return;
    }
    memset(post_data, 0, max_post_data_bytes);

    CURL *curl;
    CURLcode res;

    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
    curl = curl_easy_init();
    if (curl) {
        /* First set the URL that is about to receive our POST. This URL can
        just as well be a https:// URL if that is what should receive the
        data. */
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:7000/");

        /* Now specify the timeout to 3 sec */
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

        /* Now specify the response data callback */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, post_response_callback);

        /* Now specify the custom header */
        struct curl_slist *chunk = NULL;

        /* Remove a header curl would otherwise add by itself */
        chunk = curl_slist_append(chunk, "Accept:");

        /* Add a custom header */
        chunk = curl_slist_append(chunk, "Content-Type: application/json");

        /* set our custom set of headers */
        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        /* Now specify the POST data */
        memset(post_data, 0, max_post_data_bytes);
        serialize_sample_2(post_data, max_post_data_bytes);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        /* Now specify the Debug option */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    free(post_data);

    printf("Exit %s.\n\n", __FUNCTION__);
}


int main()
{
    json_samples();

    curl_post_sample();



    printf("Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
    return 0;
}

