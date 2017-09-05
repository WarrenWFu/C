#include "soapH.h"
#include "ns.nsmap"
#include "stdio.h"


int main( int argc, char *argv[])
{
	printf("The Client is runing...\n");
	int num1 = 110;
	int num2 = 11;
	int result = 0;

	struct soap *CalculateSoap = soap_new();
	//soap_init(CalculateSoap);
	const char * server_addr = "http://127.0.0.1:10000";

	int iRet = soap_call_ns__add(CalculateSoap,server_addr,"",num1,num2,&result);
	if ( iRet == SOAP_ERR)
	{
		printf("Error while calling the soap_call_ns__add");
	}
	else
	{
		printf("Calling the soap_call_ns__add success。\n");
		printf("%d + %d = %d\n",num1,num2,result);
	}

	iRet = soap_call_ns__sub(CalculateSoap,server_addr,"",num1,num2,&result);
	if ( iRet == SOAP_ERR)
	{
		printf("Error while calling the soap_call_ns__sub");
	}
	else
	{
		printf("Calling the soap_call_ns__sub success。\n");
		printf("%d - %d = %d\n",num1,num2,result);
	}

	iRet = soap_call_ns__mult(CalculateSoap,server_addr,"",num1,num2,&result);
	if ( iRet == SOAP_ERR)
	{
		printf("Error while calling the soap_call_ns__mult");
	}
	else
	{
		printf("Calling the soap_call_ns__mult success。\n");
		printf("%d * %d = %d\n",num1,num2,result);
	}

	iRet = soap_call_ns__divid(CalculateSoap,server_addr,"",num1,num2,&result);
	if ( iRet == SOAP_ERR)
	{
		printf("Error while calling the soap_call_ns__divid");
	}
	else
	{
		printf("Calling the soap_call_ns__divid success。\n");
		printf("%d / %d = %d\n",num1,num2,result);
	}

    sleep(10);

	soap_end(CalculateSoap);
	soap_done(CalculateSoap);
	free(CalculateSoap);

	return 0;
}
