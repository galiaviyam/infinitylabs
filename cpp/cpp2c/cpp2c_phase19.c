#include <stdio.h>
#include <stdlib.h>

struct Base
{
    const struct VTable *vptr;
    int x;
    int y;
};

struct Derived
{
    const struct DerVTable *vptr;
    int x;
    int y;
    int z;
};

void BaseCleanup(struct Base *this);
void DerivedCleanup(struct Derived *this);
void Foo(struct Base *this);
void DerivedFoo(struct Derived *this);

struct VTable
{
    void (*destructor)(struct Base *);
    void (*Foo)(struct Base *);
} vtable = {&BaseCleanup, &Foo};

struct DerVTable
{
    void (*destructor)(struct Derived *);
    void (*Foo)(struct Derived *);
} der_vtable = {&DerivedCleanup, &DerivedFoo};

struct Base *BaseCreate(struct Base *this, int inX, int inY)
{
    this->x = inX;
    this->y = inY;

    this->vptr = &vtable;

    return this;
}

struct Derived *DerivedCreate(struct Derived *this, int inX, int inY, int inZ)
{
    this = (struct Derived *)BaseCreate((struct Base *)this, inX, inY);
    
    this->vptr = &der_vtable;
    
    this->z = inZ;
    
    return this;
}

void BaseCleanup(struct Base *this)
{
    (void)this;
}

void DerivedCleanup(struct Derived *this)
{
    (void)this;
}

void BaseCopy(struct Base *this, const struct Base *other)
{
    this->x = other->x;
    this->y = other->y;
    this->vptr = other->vptr;
}

void BaseAssign(struct Base *this, const struct Base *other)
{
    BaseCopy(this, other);
}

void DerivedCopy(struct Derived *this, const struct Derived *other)
{
    BaseCopy((struct Base *)this, (struct Base *)other);

    this->z = other->z;
}

void DerivedAssign(struct Derived *this, const struct Derived *other)
{
    DerivedCopy(this, other);
}

void Foo(struct Base *this)
{
    (void)this;
}

void DerivedFoo(struct Derived *this)
{
    (void)this;
}

int main()
{
    struct Base *pBase = (struct Base *)malloc(sizeof(struct Derived));
    if (NULL == pBase)
    {
        return -1;
    }

    DerivedCreate((struct Derived *)pBase, 5, 6, 7);
    pBase->vptr->Foo(pBase);

    pBase->vptr->destructor(pBase);

    free(pBase);
    pBase = NULL;

    return 0;
}

