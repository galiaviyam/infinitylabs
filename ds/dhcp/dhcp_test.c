/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	DHCP               		*/
/*   Date:		09/02/23				*/
/*	 Reviewer:	Matan					*/
/*										*/
/****************************************/

#include <stdio.h>	/* printf */
#include <assert.h>	/* assert */

#include "dhcp.h"	/* heap file*/

static void TestCreateDestroy(void);
static void TestAllocateFree(void);

static void TestNumResultEqual(size_t result, size_t expected_result);
static void TestStatusResult(int result);


int main(void)
{
	TestCreateDestroy();
	TestAllocateFree();
	
	return 0;
}


static void TestCreateDestroy(void)
{
	dhcp_t *dhcp = NULL;
	char *net_ip = "192.168.111.10";
	
	printf("----------create----------\n");
	
	dhcp = DHCPCreate(net_ip, (unsigned int)(~255));
	
	TestNumResultEqual(DHCPCountFreeAddresses(dhcp), 253);
	
	DHCPDestroy(dhcp);
}

static void TestAllocateFree(void)
{
	char *net_ip = "192.168.111.10";
	const char *req_ip1 = "192.168.111.0";
	const char *req_ip2 = "192.168.111.242";
	const char *req_ip3 = "192.168.111.100";
	const char *req_ip4 = "191.168.111.999";
	dhcp_t *dhcp = NULL;
	
	char res_ip[16] = {0};
	
	printf("----------allocate----------\n");

	dhcp = DHCPCreate(net_ip, (unsigned int)(~255));
    
    printf("allocate 1: ");
    TestNumResultEqual(OCCUPIED_ADDRESS, DHCPAllocateIP(dhcp, req_ip1, res_ip));
    printf("requested: %s got: %s\n\n", req_ip1, res_ip);

    printf("allocate 2: ");
    TestStatusResult(DHCPAllocateIP(dhcp, req_ip2, res_ip));
	printf("requested: %s got: %s\n\n", req_ip2, res_ip);

	printf("allocate 3: ");
	TestStatusResult(DHCPAllocateIP(dhcp, req_ip3, res_ip));
	printf("requested: %s got: %s\n\n", req_ip3, res_ip);
	
    printf("allocate 4: ");
	TestNumResultEqual(INVALID_ADDRESS, DHCPAllocateIP(dhcp, req_ip4, res_ip));
    printf("requested: %s got: %s\n\n", req_ip3, res_ip);
    
    printf("free 2: ");
    TestStatusResult(DHCPFreeIP(dhcp, req_ip2));

    printf("free 4: ");
    TestNumResultEqual(INVALID_ADDRESS, DHCPFreeIP(dhcp, req_ip4));

	DHCPDestroy(dhcp);
}

/**************************test utility functions************************/
static void TestStatusResult(int result)
{
	if (result == SUCCESS)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

static void TestNumResultEqual(size_t result, size_t expected_result)
{
	if (result == expected_result)
	{
		printf("\033[0;32mPASS\033[0m\n");
	}
	else
	{
		printf("\033[0;31mFAIL\033[0m\n");
	}
}

