#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Point
{
    int m_x;
    int m_y;
} Point_t;

typedef struct A
{
	char place_holder;
} A_t;

typedef struct B
{
    int x;
    int y;
    Point_t p;
    void (*BSetX)(struct B *this, int inX);
    void (*BSetY)(struct B *this, int inY);
    void (*BBla)();
} B_t;

void BSetX(B_t *this, int inX);
void BSetY(B_t *this, int inY);
void BBla();

Point_t PointCreate(int x, int y)
{
    Point_t point = {0};
    point.m_x = x;
    point.m_y = y;

    return point;
}

void BInit(B_t *this, int x, int y, int px, int py)
{
    this->x = x;
    this->y = y;
    this->p = PointCreate(px, py);
    this->BSetX = &BSetX;
    this->BSetY = &BSetY;
    this->BBla = &BBla;
}

void BCleanup(B_t *this)
{
    (void)this;
}

void BCopy(B_t *this, const B_t *other)
{
    this->x = other->x;
    this->y = other->y;
    this->p = PointCreate(other->p.m_x, other->p.m_y);
}

void BAssign(B_t *this, const B_t *other)
{
    if (this == other)
	{
        return;
    }
    BCleanup(this);
    BCopy(this, other);
}

void AInit(A_t *this)
{
	(void)this;
}

void ACleanup(A_t *this)
{
	(void)this;
}

void BSetX(B_t *this, int inX)
{
    this->x = inX;
}

void BSetY(B_t *this, int inY)
{
    this->y = inY;
}

void Foo()
{
    int i = 0;
    B_t array1[100];
    B_t *array2 = (B_t *)malloc(sizeof(B_t) * 100);
    if (NULL == array2)
    {
        printf("error!");
        return;
    }

    for (i = 0; i < 100; ++i)
    {
        BInit((array1 + i), 0, 0, 0, 0);
    }

    for (i = 0; i < 100; ++i)
    {
        BInit((array2 + i), 0, 0, 0, 0);
    }

    for (i = 100; i > 0; --i)
    {
        BCleanup(array1 + i);
    }

    for (i = 100; i > 0; --i)
    {
        BCleanup(array2 + i);
    }
    free(array2);
}

B_t Bar(B_t b1, B_t *b2, B_t *b3)
{
    (void)b2;
    (void)b3;

    return b1;
}

void BBla()
{

}

int main()
{
    A_t a = {0};
    B_t b = {0};
    B_t b2 = {0};
    B_t *p = (B_t *)malloc(sizeof(B_t));
    if (NULL == p)
    {
        return -1;
    }

	BInit(&b, 0, 0, 0, 0);
    BInit(&b2, b.x, b.y, b.p.m_x, b.p.m_y);

    BCopy(&b2, &b);
    BAssign(&b2, &b);

    b.BSetX(&b, 5);
    b.BSetY(&b, 6);

    BInit(p, 0, 0, 0, 0);
    p->BSetX(p, 5);
    p->BSetY(p, 6);
    
    BCleanup(p);
    free(p);
    p = NULL;

    Foo();
    Bar(b, &b2, &b);

    b.BBla();

    BCleanup(&b2);
    BCleanup(&b);
    ACleanup(&a);

	return 0;
}