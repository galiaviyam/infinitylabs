/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	DHCP               		*/
/*   Date:		09/02/23				*/
/*	 Reviewer:	Matan					*/
/*										*/
/****************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */

/*-----------------------------------------------------------------------------
General Description:
	Dynamic Host Configuration Protocol (DHCP) is a client/server protocol that
	automatically provides an Internet Protocol (IP) host with its IP address 
	and other related configuration information such as the subnet mask and 
	default gateway. The DHCP server maintains a pool of IP addresses and 
	allocates and frees addresses. 
	
Main Functionality:
	Allocate IP
	Free Ip
-----------------------------------------------------------------------------*/

typedef struct dhcp dhcp_t;

typedef enum status
{
    SYS_FAULT = -1,
    SUCCESS = 0,
    INVALID_ADDRESS = 1,
    DOUBLE_FREE = 2,
    OCCUPIED_ADDRESS = 3,
    NO_AVAIL_IP = 4
} status_t;


/*-----------------------------------------------------------------------------
Description:
	The DHCPCreate function prepares the required resources and creates the DHCP.
	The resources must be destroyed manually using the DHCPDestroy function.
	
Parameters:
	net_ip - The IP address of the network to be managed by the DHCP.
	subnet_mask - A mask defining the addresses range to be managed by the DHCP.
	NOTE!
	Passing invalid subnet_mask argument may cause an undifined behavior.
	
Return Value:
	On succes- the function returns a handle to the DHCP.
	On failure- he function returns NULL.
	
Complexity: 
	time: O(log(n))  
-----------------------------------------------------------------------------*/
dhcp_t *DHCPCreate(const char *net_ip, unsigned int subnet_mask);

/*-----------------------------------------------------------------------------
Description:
	The DHCPDestroy function destroys all of the resources used by the DHCP.
Parameters:
	dhcp- a handle to the dhcp.

Complexity: 
	time: O(n) 
-----------------------------------------------------------------------------*/
void DHCPDestroy(dhcp_t *dhcp);

/*-----------------------------------------------------------------------------
Description:
	The DHCPAllocateIP function allocates a new IP address.
	
Parameters:
	dhcp - a handle to the dhcp.
	requested_ip - the requested IP address.
	res_ip - a pointer to the generated IP address the dhcp allocated.

Return Value:
	The function returns a status code from the optional statuses described in 
	the above enum.

comment:
	Passing NULL as the requested_ip is valid.
	The result IP may be a different IP address than requested.
	
Complexity: 
	average time: O(log(n)), worst time: O(nlog(n))  
-----------------------------------------------------------------------------*/
status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip, char *res_ip);

/*-----------------------------------------------------------------------------
Description:
	The DHCPFreeIP function frees an allocated IP address for re-use by the DHCP.
	
Parameters:
	dhcp- a handle to the dhcp.
	ip- the IP address to be freed.
	
Return Value:
	The function returns a status code from the optional statuses described in 
	the above enum.

comment:
	passing a non-allocated IP address will cause an undefined beahvior.

Complexity: 
	time: O(log(n))
-----------------------------------------------------------------------------*/
status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip);

/*-----------------------------------------------------------------------------
Description:
	The DHCPCountFreeAddresses function counts the number of free IP addresses 
	available.
	
Parameters:
	dhcp- a handle to the dhcp.
	
Return Value:
	The function returns the number of free IP addresses available.
	
Complexity: 
	time: O(n) 
-----------------------------------------------------------------------------*/
size_t DHCPCountFreeAddresses(const dhcp_t *dhcp);

#endif /* __DHCP_H__ */

