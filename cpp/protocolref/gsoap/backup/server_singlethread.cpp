#include "soapH.h"
#include "ns.nsmap"
#include "stdio.h"

int main( int argc, char *argv[])
{
    struct soap *CalculateSoap = soap_new();                                //创建一个soap
    int iSocket_master = soap_bind(CalculateSoap, NULL, 10000, 100);         //绑定到相应的IP地址和端口（）NULL指本机，
    //10000为端口号，最后一个参数不重要。
    if (iSocket_master< 0)                                                  //绑定出错
    {
        soap_print_fault(CalculateSoap, stderr);
        exit(-1);
    }
    printf("SoapBind success,the master socket number is:%d\n",iSocket_master); //绑定成功返回监听套接字

    while(1)
    {
        int iSocket_slaver = soap_accept(CalculateSoap);
        if (iSocket_slaver < 0)
        {
            soap_print_fault(CalculateSoap, stderr);
            exit(-2);
        }
        printf("Get a new connection,the slaver socket number is:%d\n",iSocket_slaver); //绑定成功返回监听套接字
        soap_serve(CalculateSoap);
        soap_end(CalculateSoap);
    }
    soap_done(CalculateSoap);
    free(CalculateSoap);

    return 0;
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
