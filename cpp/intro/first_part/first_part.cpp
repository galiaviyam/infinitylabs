#include <cstdio> //printf
#include <cstdlib> //malloc
#include <iostream> //cout
typedef struct List
{
	int num;
	void *data;
}List_t;

typedef struct Person
{
	int key;
	int age;
}Person_t;

static void Ex2(void);
static void Ex3(void);
static void foo(List_t *ll, int key, int age);
static void *ll_find(List_t *ll, int key);
static void Ex8(void);

int main(void)
{
	List_t *ll = (List_t *)malloc(sizeof(List_t));
	if (NULL == ll)
	{
		return -1;
	}
	Ex2();
	Ex3();
	foo(ll, 1, 1);
	
	free(ll);
	ll = NULL;
	
	Ex8();
	
	return 0;
}

void Ex2(void)
{
	enum E {AA, BB, CC, DD};
	enum E2 {TT, KK};
	enum E e = (enum E)2;
	enum E2 e2 = (enum E2)AA;
	// E2 e22 = KK;
	//++e;
	int i = e;
	(void)e2;
	(void)i;
}

void Ex3(void)
{
	bool b1 = true;
	bool b2;
	int i = b1;
	i = 7;
	b2 = i;
	printf("%d\n", b2);
	printf("%ld\n", sizeof(bool));
}


void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    //We know that the list actually contains person data, so we
    //want to convert the void pointer to Person to access it.
    Person_t *p = static_cast<Person_t*>(vv); //Accidentally used ll instead of vv
    p->age = age;
}

static void *ll_find(List_t *ll, int key)
{
	void *p = ll;

	(void)key;
	return p;
}

static void Ex8(void)
{
	size_t i = 0;
	std::cout << "ksjdkfjfk" << i << std::endl;
	std::cin >> i;
	std::cerr << "ksjdkfjfk" << i;
}
