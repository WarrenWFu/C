#include "soapH.h"
#include "ns.nsmap"
#include <cstdio>
#include <pthread.h> 
#define BACKLOG (100) // Max. request backlog 
int main(int argc, char **argv) 
{ 
	struct soap soap; 
	soap_init(&soap); 
	if (argc < 2) // no args: assume this is a CGI application 
	{ 
		soap_serve(&soap); // serve request, one thread, CGI style 
		soap_destroy(&soap); // dealloc C++ data 
		soap_end(&soap); // dealloc data and clean up 
	} 
	else 
	{ 
		soap.send_timeout = 60; // 60 seconds 
		soap.recv_timeout = 60; // 60 seconds 
		soap.accept_timeout = 3600; // server stops after 1 hour of inactivity 
		soap.max_keep_alive = 100; // max keep-alive sequence 
		void *process_request(void*); 
		struct soap *tsoap; 
		pthread_t tid; 
		int port = atoi(argv[1]); // first command-line arg is port 
		SOAP_SOCKET m, s; 
		m = soap_bind(&soap, NULL, port, BACKLOG); 
		if (!soap_valid_socket(m)) 
			exit(1); 
		fprintf(stderr, "Socket connection successful %d\n", m); 
		for (int i = 0;; i++) 
		{ 
			s = soap_accept(&soap); 
			if (!soap_valid_socket(s)) 
			{ 
				if (soap.errnum) 
				{ 
					soap_print_fault(&soap, stderr); 
					exit(1); 
				} 
				fprintf(stderr, "server timed out\n"); 
				break; 
			} 
			fprintf(stderr, "Thread %d accepts socket %d connection from IP %d.%d.%d.%d\n", i, s, (soap.ip >> 24)&0xFF, (soap.ip >> 16)&0xFF, (soap.ip >> 8)&0xFF, soap.ip&0xFF); 
			tsoap = soap_copy(&soap); // make a safe copy 
			if (!tsoap) 
				break; 
			pthread_create(&tid, NULL, (void*(*)(void*))process_request, (void*)tsoap); 
		} 
	} 
	soap_done(&soap); // detach soap struct 
	return 0; 
} 

void *process_request(void *soap) 
 { 
    pthread_detach(pthread_self()); 
    soap_serve((struct soap*)soap); 
    soap_destroy((struct soap*)soap); // dealloc C++ data 
    soap_end((struct soap*)soap); // dealloc data and clean up 
    soap_done((struct soap*)soap); // detach soap struct 
    free(soap); 
    return NULL; 
 } 

/*加法的具体实现*/
int ns__add(struct soap *soap, int num1, int num2, int* result )   
{
    if (NULL == result)
    {
        printf("Error:The third argument should not be NULL!\n");
        return SOAP_ERR;
    }
    else
    {
        (*result) = num1 + num2;
        return SOAP_OK;
    }
    return SOAP_OK;
}

/*减法的具体实现*/
int ns__sub(struct soap *soap,int num1, int num2, int* result )
{
    if (NULL == result)
    {
        printf("Error:The third argument should not be NULL!\n");
        return SOAP_ERR;
    }
    else
    {
        (*result) = num1 - num2;
        return SOAP_OK;
    }
    return SOAP_OK;
}

/*乘法的具体实现*/
int ns__mult(struct soap *soap, int num1, int num2, int *result)
{
    if (NULL == result)
    {
        printf("Error:The third argument should not be NULL!\n");
        return SOAP_ERR;
    }
    else
    {
        (*result) = num1 * num2;
        return SOAP_OK;
    }
    return SOAP_OK;
}

/*除法的具体实现*/
int ns__divid(struct soap *soap, int num1, int num2, int *result)
{
    if (NULL == result || 0 == num2)
    {
        printf("Error:The second argument is 0 or The third argument is NULL!\n");
        return SOAP_ERR;
    }
    else
    {
        (*result) = num1 / num2;
        return SOAP_OK;
    }
    return SOAP_OK;
}
