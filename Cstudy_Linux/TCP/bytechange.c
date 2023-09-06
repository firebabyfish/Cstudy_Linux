/*
    网络通信时，需要将主机字节序转换成网络字节序 (大端),
    另外一段获取到数据以后根据情况将网络字节序转换成主机字节序。

    // 转换端口
    uint16_t htons(uint16_t hostshort);
    uint16_t ntohs(uint16_t netshort);

    // 转换IP
    uint32_t htonl(uint32_t hostshort);
    uint32_t ntohl(uint32_t netshort);

*/ 

#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    // htons 转换端口
    unsigned short a = 0x0102;
    printf("a = %x\n", a);
    unsigned short b = htons(a);
    printf("b = %x\n", b);

    // htonl 转换IP
    unsigned char buf[4] = {192, 168, 10, 100};
    int num = *(int*)buf;
    int sum = htonl(num);
    unsigned char *p = (char*)&sum;
    printf("%d.%d.%d.%d\n", *p, *(p+1), *(p+2), *(p+3));

    return 0;
}