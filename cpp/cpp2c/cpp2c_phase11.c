struct Base
{
    int x;
    int y;
};
struct Derived
{
    struct Base *b;
    int z;
};

struct Base *BaseCreate(struct Base *this, int inX, int inY)
{
    this->x = inX;
    this->y = inY;

    return this;
}

struct Derived *DerivedCreate(struct Derived *this, int inX, int inY, int inZ)
{
    struct Base base = {0};
    this->b = BaseCreate(&base, inX, inY);
    this->z = inZ;

    return this;
}

void BaseCleanup(struct Base *this)
{
    (void)this;
}

void DerivedCleanup(struct Derived *this)
{
    BaseCleanup(this->b);
}

void BaseCopy(struct Base *this, const struct Base *other)
{
    this->x = other->x;
    this->y = other->y;
}

void BaseAssign(struct Base *this, const struct Base *other)
{
    if (this == other)
	{
        return;
    }
    BaseCleanup(this);
    BaseCopy(this, other);
}

void DerivedCopy(struct Derived *this, const struct Derived *other)
{
    BaseCopy(this->b, other->b);
    this->z = other->z;
}

void DerivedAssign(struct Derived *this, const struct Derived *other)
{
    if (this == other)
	{
        return;
    }
    DerivedCleanup(this);
    DerivedCopy(this, other);
}

int main()
{
    struct Derived d = {0};
    DerivedCreate(&d, 0, 0, 0);
    DerivedCleanup(&d);
    return 0;
}
