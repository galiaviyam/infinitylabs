/****************************************/
/*										*/   
/*	 Developer:	Gali Aviyam				*/
/*   Project:	DHCP               		*/
/*   Date:		09/02/23				*/
/*	 Reviewer:	Matan					*/
/*										*/
/****************************************/

#include <assert.h>		/* assert */
#include <stdlib.h>		/* malloc */
#include <arpa/inet.h>	/* inet_pton */
#include <string.h>		/* memcpy */
#include <limits.h>		/* CHAR_BIT */

#include "dhcp.h"		/* dhcp header file */

typedef enum bool
{
	FALSE = 0,
	TRUE
} bool_t;

enum 
{
	OFF = 0,
	ON,
	NUM_OF_CHILDREN
};

typedef struct trie_node
{
	bool_t is_full;
	struct trie_node *children[NUM_OF_CHILDREN];
} trie_node_t;

struct dhcp
{
	trie_node_t *root;
	const char *net_ip;
	unsigned int subnet_mask;
	size_t height;
};

static void InitDHCP(dhcp_t *dhcp, const char *net_ip, 
					unsigned int subnet_mask);
static void InitTrieNode(trie_node_t *node);
static status_t AllocSysAddresses(dhcp_t *dhcp, unsigned int subnet_mask);
static int CreateAddress(dhcp_t *dhcp, unsigned int ip, unsigned int *res_ip, 
			bool_t *is_found, status_t *status);

static void RecDestroyTrie(trie_node_t *root);

static size_t CountSetBits(unsigned int net_size);
static size_t CountAllocatedAddresses(trie_node_t *node);
static int IsIpInRange(unsigned int ip, unsigned int net_ip, 
						unsigned int subnet_mask);

/*-------------------------------DHCPCreate----------------------------*/
dhcp_t *DHCPCreate(const char *net_ip, unsigned int subnet_mask)
{
	dhcp_t *dhcp = NULL;
	
	assert(NULL != net_ip);	
	
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (NULL == dhcp)
	{
		return NULL;
	}
	
	dhcp->root = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (NULL == dhcp->root)
	{
		free(dhcp);
		dhcp = NULL;
		return NULL;
	}
	
	InitDHCP(dhcp, net_ip, subnet_mask);

	if (SUCCESS != AllocSysAddresses(dhcp, subnet_mask))
	{
		DHCPDestroy(dhcp);
		return NULL;
	}

	return dhcp;
}

/*------------------------------DHCPDestroy----------------------------*/
void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	RecDestroyTrie(dhcp->root);
	
	free(dhcp);
	dhcp = NULL;
}

/*------------------------------DHCPAllocateIP----------------------------*/
status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip, char *res_ip)
{
	status_t status = SUCCESS;
	unsigned int ip = 0;
	unsigned int tmp_res = 0;
	char *res = NULL;
	struct in_addr s_ip = {0};
	unsigned int net_ip = 0;
	bool_t is_found = FALSE;
	
	assert(NULL != dhcp);
	assert(NULL != res_ip);
	
	inet_pton(AF_INET, dhcp->net_ip, &net_ip);
	
	if (NULL == requested_ip)
	{
		ip = net_ip;
	}
	else if (1 != inet_pton(AF_INET, requested_ip, &ip))
	{
		status = INVALID_ADDRESS;
		ip = net_ip;
	}
	
	net_ip = htonl(net_ip);
	net_ip &= dhcp->subnet_mask;
	ip = htonl(ip);
	
	while (IsIpInRange(ip, net_ip, dhcp->subnet_mask) && !is_found &&
			(OCCUPIED_ADDRESS == CreateAddress(dhcp, ip, &tmp_res, &is_found, 
					&status)))
	{
		++ip;
	}
	
	if (net_ip != (ip & dhcp->subnet_mask))
	{
		status = NO_AVAIL_IP;
	}
	
	s_ip.s_addr = ntohl(tmp_res);
	res = inet_ntoa(s_ip);
	strcpy(res_ip, res);
	
	return status;
}

/*------------------------------DHCPFreeIP----------------------------*/
status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip)
{
	status_t status = DOUBLE_FREE;
	unsigned int ip_to_free = 0;
	unsigned int dir = 0;
	unsigned int mask = 1;
	int i  = 0;
	trie_node_t *runner = NULL;
	
	assert(NULL != dhcp);
	assert(NULL != ip);
	
	if (1 != inet_pton(AF_INET, ip, &ip_to_free))
	{
		return INVALID_ADDRESS;
	}
	
	ip_to_free = htonl(ip_to_free);
	runner = dhcp->root;
	mask <<= (dhcp->height - 1);
	
	for (i = dhcp->height - 1; i >= 0; --i)
	{
		dir = (mask & ip_to_free) >> i;
		
		if (NULL == runner->children[dir])
		{
			return INVALID_ADDRESS;
		}
		
		runner->is_full = FALSE;
		runner = runner->children[dir];
		
		mask >>= 1;
	}
	
	if (runner->is_full)
	{
		runner->is_full = FALSE;
		status = SUCCESS;
	}
	
	return status;
}

/*-------------------------DHCPCountFreeAddresses----------------------*/
size_t DHCPCountFreeAddresses(const dhcp_t *dhcp)
{
	size_t count = 0;
	
	assert(NULL != dhcp);
	
	count = 1 << dhcp->height;
	
	return (count - CountAllocatedAddresses(dhcp->root));
}

/*-----------------------------------------------------------------------*/
/*-----------------------------Static Functions--------------------------*/
/*-----------------------------------------------------------------------*/

/*--------------------------------InitDHCP-------------------------------*/
static void InitDHCP(dhcp_t *dhcp, const char *net_ip, unsigned int subnet_mask)
{
	assert(NULL != dhcp);
	assert(NULL != dhcp->root);
	assert(NULL != net_ip);
	
	InitTrieNode(dhcp->root);
	
	dhcp->net_ip = net_ip;
	dhcp->subnet_mask = subnet_mask;
	dhcp->height = CountSetBits(~subnet_mask);
}

/*------------------------------InitTrieNode----------------------------*/
static void InitTrieNode(trie_node_t *node)
{
	node->is_full = FALSE;
	node->children[OFF] = NULL;
	node->children[ON] = NULL;
}

/*---------------------------AllocSysAddresses------------------------*/
static status_t AllocSysAddresses(dhcp_t *dhcp, unsigned int subnet_mask)
{
	status_t status = SUCCESS;
	bool_t is_found = FALSE;
	unsigned int num_net_ip = 0;
	unsigned int broadcast_ip = ~subnet_mask;
	unsigned int server_ip = ~subnet_mask - 1;
	unsigned int res = 0;
	
	assert(NULL != dhcp);
	
	status += CreateAddress(dhcp, num_net_ip, &res, &is_found, &status);
	status += CreateAddress(dhcp, broadcast_ip, &res, &is_found, &status);
	status += CreateAddress(dhcp, server_ip, &res, &is_found, &status);
	
	return status;
}

/*-----------------------------IsIpInRange---------------------------*/
static int IsIpInRange(unsigned int ip, unsigned int net_ip, unsigned int subnet_mask)
{
	return (net_ip == (ip & subnet_mask));
}

/*------------------------------RecDestroyTrie----------------------------*/
static void RecDestroyTrie(trie_node_t *root)
{
	if (NULL != root)
	{
		RecDestroyTrie(root->children[OFF]);
		RecDestroyTrie(root->children[ON]);

		free(root);
		root = NULL;
	}
}

/*------------------------------CountSetBits----------------------------*/
static size_t CountSetBits(unsigned int net_size)
{
	size_t count = 0;
	
	while (0 != net_size)
	{
		++count;
		net_size = net_size & (net_size - 1);
	}
	return count;
}

/*------------------------------CreateAddress----------------------------*/
static int CreateAddress(dhcp_t *dhcp, unsigned int ip, unsigned int *res_ip,
						 bool_t *is_found, status_t *status)
{
	unsigned int mask = 1;
	unsigned int dir = 0;
	int i  = 0;
	trie_node_t *runner = NULL;
	
	assert(NULL != dhcp);
	
	runner = dhcp->root;
	mask <<= (dhcp->height - 1);
	
	for (i = dhcp->height - 1; i >= 0; --i)
	{
		dir = (mask & ip) >> i;
		
		if (NULL == runner->children[dir])
		{
			runner->children[dir] = (trie_node_t *)malloc(sizeof(trie_node_t));
			if (NULL == runner->children[dir])
			{
				*status = SYS_FAULT;
				return *status;
			}
			InitTrieNode(runner->children[dir]);
		}
		else
		{
			if (runner->children[dir]->is_full)
			{
				*status = OCCUPIED_ADDRESS;
				return *status;
			}
			else if (NULL != runner->children[!dir] &&
					runner->children[OFF]->is_full &&
					runner->children[ON]->is_full)
			{
				runner->is_full = TRUE;
				*status = OCCUPIED_ADDRESS;
				return *status;
			}
		}
		runner = runner->children[dir];
		mask >>= 1;
	}
	
	*is_found = TRUE;
	runner->is_full = TRUE;
	*res_ip = ip;
	
	return *status;
}

/*-------------------------CountAllocatedAddresses----------------------*/
static size_t CountAllocatedAddresses(trie_node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}
	
	if ((NULL == root->children[OFF]) && (NULL == root->children[ON]))
	{
		return root->is_full;
	}
	
	return (CountAllocatedAddresses(root->children[OFF]) + 
			CountAllocatedAddresses(root->children[ON]));
}

