#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define TEMPLATE_MAX(T) T Max_func##T(T t1, T t2) { return ((t1 > t2) ? t1 : t2);}
TEMPLATE_MAX(int)
TEMPLATE_MAX(double)

/**************************** Classes *********************************/

typedef struct PublicTransport
{
    const struct PublicTransportVTable *vptr;
    int m_license_plate;
} PublicTransport;

typedef struct Minibus 
{
    PublicTransport PublicTransport;
    int m_numSeats;
} Minibus;

typedef struct Taxi
{
    PublicTransport PublicTransport;
} Taxi;

typedef struct SpecialTaxi
{
    Taxi Taxi;
} SpecialTaxi;

typedef struct PublicConvoy
{
    PublicTransport PublicTransport;
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
	Minibus m_m;
	Taxi m_t;
} PublicConvoy;

/**************************** Functions *********************************/
void PublicTransportCtor(PublicTransport *const this);
void PublicTransportDtor(void *const this);
void PublicTransportCCtor(PublicTransport *const this, const PublicTransport *const other);
void PublicTransportDisplay(void *this);
void print_count();
int get_ID(PublicTransport *this);

void MinibusCtor(Minibus *const this);
void MinibusCCtor(Minibus *const this, const Minibus *const other);
void MinibusDtor(void *const this);
void MinibusDisplay(void *const this);
void wash(void *const this, int minutes);

void TaxiCtor(Taxi *const this);
void TaxiCCtor(Taxi *const this, const Taxi *const other);
void TaxiDtor(void *const this);
void TaxiDisplay(void *const this);

void SpecialTaxiCtor(SpecialTaxi *const this);
void SpecialTaxiCCtor(SpecialTaxi *const this, const SpecialTaxi *const other);
void SpecialTaxiDtor(void *const this);
void SpecialTaxiDisplay(void *const this);

void PublicConvoyCtor(PublicConvoy *const this);
void PublicConvoyCCtor(PublicConvoy *const this, const PublicConvoy *const other);
void PublicConvoyDtor(void *const this);
void PublicConvoyDisplay(void *const this);

void PublicTransportPrintInfo(PublicTransport *a);
void VoidPrintInfo();
void MinibusPrintInfo(Minibus *m);
PublicTransport IntPrintInfo(PublicTransport *tmp_addr, int i);
void taxi_display(Taxi s);

/**************************** VTables *********************************/
struct PublicTransportVTable
{
    void (*destructor)(void *const);
    void (*display)(void *const);
} const public_vtable = {&PublicTransportDtor, &PublicTransportDisplay};

struct MinibusVTable
{
    void (*destructor)(void *const);
    void (*display)(void *const);
    void (*wash)(void *const, int);
} const minibus_vtable = {&MinibusDtor, &MinibusDisplay, &wash};

struct TaxiVTable
{
    void (*destructor)(void *const);
    void (*display)(void *const);
} const taxi_vtable = {&TaxiDtor, &TaxiDisplay};

struct SpecialTaxiVTable
{
    void (*destructor)(void *const);
    void (*display)(void *const);
} const special_taxi_vtable = {&SpecialTaxiDtor, &SpecialTaxiDisplay};

struct PublicConvoyVTable
{
	void (*destructor)(void *const);
	void (*display)(void *const);
} const public_convoy_vtable = {&PublicConvoyDtor, &PublicConvoyDisplay};

int g_public_transport_count = 0;

/*------------------------------ PublicTransport ----------------------------*/
void PublicTransportCtor(PublicTransport *const this)
{
    this->vptr = &public_vtable;
    this->m_license_plate = ++g_public_transport_count;
    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void PublicTransportDtor(void *const this)
{
    --g_public_transport_count;
    printf("PublicTransport::Dtor()%d\n", ((PublicTransport *)this)->m_license_plate);
}

void PublicTransportCCtor(PublicTransport *const this, const PublicTransport *const other)
{
    this->vptr = &public_vtable;

    this->m_license_plate = ++g_public_transport_count;

    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
    (void)other;
}

void PublicTransportDisplay(void *this)
{
    printf("PublicTransport::display(): %d\n", ((PublicTransport *const)this)->m_license_plate);
}

void print_count(void)
{
    printf("s_count: %d\n", g_public_transport_count);
}

int get_ID(PublicTransport *const this)
{
    return this->m_license_plate;
}
/*---------------------------------- MiniBus --------------------------------*/
void MinibusCtor(Minibus *const this)
{
    PublicTransportCtor((PublicTransport *)this);
    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&minibus_vtable;
    this->m_numSeats = 20;

    printf("Minibus::Ctor()\n");
}

void MinibusCCtor(Minibus *const this, const Minibus *const other)
{
    PublicTransportCCtor(((PublicTransport *const)this), ((const PublicTransport *const)&other));
    
    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&minibus_vtable;
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(void *this)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDtor(((PublicTransport *const)this));
}

void MinibusDisplay(void *const this)
{
    printf("Minibus::display() ID:%d", get_ID((PublicTransport *const)this));
    printf(" num seats:%d\n", ((Minibus *const)this)->m_numSeats);
}

void wash(void *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID((PublicTransport *const)this));
}

/*----------------------------------- Taxi ----------------------------------*/
void TaxiCtor(Taxi *const this)
{
    PublicTransportCtor((PublicTransport *)this);
    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&taxi_vtable;

    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi *const this, const Taxi *const other)
{
    PublicTransportCCtor(((PublicTransport *const)this), ((const PublicTransport *const)other));

    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&taxi_vtable;
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(void *this)
{
    printf("Taxi::Dtor()\n");
    PublicTransportDtor((PublicTransport *const)this);
}

void TaxiDisplay(void *this)
{
    printf("Taxi::display() ID:%d\n", get_ID((PublicTransport *const)this));
}

/*------------------------------- special taxi ------------------------------*/
void SpecialTaxiCtor(SpecialTaxi *const this)
{
    TaxiCtor((Taxi *)this);
    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&special_taxi_vtable;

    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi *const this, const SpecialTaxi *const other)
{
    TaxiCCtor((Taxi *)this, (const Taxi *const)other);
    
    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&special_taxi_vtable;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(void *const this)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor((Taxi *)this);
}

void SpecialTaxiDisplay(void *const this)
{
    printf("SpecialTaxi::display() ID:%d\n", get_ID((PublicTransport *const)this));
}

/*------------------------------- public convoy ----------------------------*/
void PublicConvoyCtor(PublicConvoy *const this)
{
	PublicTransportCtor(((PublicTransport *)this));

	((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&public_convoy_vtable;

	this->m_pt1 = malloc(sizeof(Minibus));
	MinibusCtor((Minibus *)this->m_pt1);

	this->m_pt2 = malloc(sizeof(Taxi));
	TaxiCtor((Taxi *)this->m_pt2);

	MinibusCtor(&this->m_m);
	TaxiCtor(&this->m_t);
}

void PublicConvoyCCtor(PublicConvoy *const this, const PublicConvoy *const other)
{
	PublicTransportCCtor((PublicTransport *)this, (const PublicTransport *const)other);
    
    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&public_convoy_vtable;

    this->m_pt1 = malloc(sizeof(Minibus));
    MinibusCCtor((Minibus *)this->m_pt1, (const Minibus *const)other->m_pt1);
    
    this->m_pt2 = malloc(sizeof(Taxi));
    TaxiCCtor((Taxi *)this->m_pt2, (const Taxi *const)other->m_pt2);

    MinibusCtor(&this->m_m);
    TaxiCtor(&this->m_t);
}

void PublicConvoyDtor(void *const this)
{
    ((PublicConvoy *)this)->m_pt1->vptr->destructor(((PublicConvoy *)this)->m_pt1);
    free(((PublicConvoy *)this)->m_pt1);

    ((PublicConvoy *)this)->m_pt2->vptr->destructor(((PublicConvoy *)this)->m_pt2);
    free(((PublicConvoy *)this)->m_pt2);

    ((PublicTransport *)this)->vptr = (const struct PublicTransportVTable *)&public_vtable;

   	TaxiDtor(&((PublicConvoy *)this)->m_t);
   	MinibusDtor(&((PublicConvoy *)this)->m_m);
   	PublicTransportDtor((PublicTransport *)this);
}

void PublicConvoyDisplay(void *const this)
{
	((PublicConvoy *)this)->m_pt1->vptr->display(((PublicConvoy *)this)->m_pt1);
    ((PublicConvoy *)this)->m_pt2->vptr->display(((PublicConvoy *)this)->m_pt2);
    
    ((PublicConvoy *)this)->m_m.PublicTransport.vptr->display(&((PublicConvoy *)this)->m_m);
    ((PublicConvoy *)this)->m_t.PublicTransport.vptr->display(&((PublicConvoy *)this)->m_t);
}

void PublicTransportPrintInfo(PublicTransport *a)
{
    a->vptr->display(a);
}

void VoidPrintInfo()
{
    print_count();
}

void MinibusPrintInfo(Minibus *const m)
{
     ((struct MinibusVTable *)((PublicTransport *)m)->vptr)->wash(m, 3);
}

PublicTransport IntPrintInfo(PublicTransport *tmp_addr, int i)
{
    Minibus ret = {0};

    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    MinibusDisplay(&ret);

    PublicTransportCCtor(tmp_addr, (PublicTransport *)&ret);

    (void)i;
    
    ((PublicTransport *)&ret)->vptr->destructor(&ret);

    return *tmp_addr;
}

void taxi_display(Taxi s)
{
    ((struct TaxiVTable *)((PublicTransport *)&s)->vptr)->display(&s);
}

int main()
{
    Minibus m = {0};
    Minibus m2 = {0};
    Minibus arr3[4] = {0};
    PublicTransport tmp = {0};
    Taxi taxi_tmp = {0};

    PublicTransport *array[3] = {NULL};
    PublicTransport arr2[3] = {0};
    Taxi *arr4 = NULL;
    SpecialTaxi st = {0};

    Minibus *minibus1_arr = (Minibus *)malloc(sizeof(Minibus));
    Taxi *taxi_arr = (Taxi *)malloc(sizeof(Taxi));
    int i = 0;
    PublicConvoy *ts1 = NULL;
    PublicConvoy *ts2 = NULL;
    
    MinibusCtor(&m);
    MinibusPrintInfo(&m);

    IntPrintInfo(&tmp, 3);
    tmp.vptr->display(&tmp);
    PublicTransportDtor(&tmp);

    array[0] = malloc(sizeof(Minibus));
    array[1] = malloc(sizeof(Taxi));
    array[2] = malloc(sizeof(Minibus));

    MinibusCtor((Minibus *)array[0]);
    TaxiCtor((Taxi *)array[1]);
    MinibusCtor((Minibus *)array[2]);

    for (i = 0; i < 3; ++i)
    {
        array[i]->vptr->display(array[i]);
    }

    for (i = 0; i < 3; ++i)
    {
        array[i]->vptr->destructor(array[i]);
        free(array[i]);
    }

    MinibusCtor(minibus1_arr);
    PublicTransportCCtor((arr2 + 0), (PublicTransport *)&minibus1_arr);
    MinibusDtor(minibus1_arr);
    free(minibus1_arr);

    TaxiCtor(taxi_arr);
    PublicTransportCCtor((arr2 + 1), (PublicTransport *)&taxi_arr);
    TaxiDtor(taxi_arr);
    free(taxi_arr);

    PublicTransportCtor((arr2 + 2));
    
    for (i = 0; i < 3; ++i)
    {
        PublicTransportDisplay((arr2 + i));
    }
    PublicTransportPrintInfo(arr2 + 0);

    print_count();
    MinibusCtor(&m2);
    print_count();

    for (i = 0; i < 4; ++i)
    {
        MinibusCtor(arr3 + i);
    }

    arr4 = (Taxi *)malloc(sizeof(Taxi)* 4);

    for (i = 0; i < 4; ++i)
    {
        TaxiCtor(arr4 + i);
    }

    for (i = 3; i >= 0; --i)
    {
        ((PublicTransport *)(arr4 + i))->vptr->destructor(arr4 + i);
    }

    free(arr4);
    arr4 = NULL;

    printf("%d\n", Max_funcint(1, 2));
    printf("%d\n", Max_funcint(1, 2.0f));
    
    SpecialTaxiCtor(&st);
    TaxiCCtor(&taxi_tmp, (Taxi *)&st);

    taxi_display(taxi_tmp);
    TaxiDtor(&taxi_tmp);
    
    ts1 = malloc(sizeof(PublicConvoy));
	PublicConvoyCtor(ts1);

	ts2 = malloc(sizeof(PublicConvoy));;
    PublicConvoyCCtor(ts2, ts1);
    ((PublicTransport *)ts1)->vptr->display(ts1);
    ((PublicTransport *)ts2)->vptr->display(ts2);

    ((PublicTransport *)ts1)->vptr->destructor(ts1);
    free(ts1);
    ts1 = NULL;

    ((PublicTransport *)ts2)->vptr->display(ts2);

    ((PublicTransport *)ts2)->vptr->destructor(ts2);
    free(ts2);
    ts2 = NULL;

    SpecialTaxiDtor(&st);
    for (i = 3; i >= 0; --i)
    {
        MinibusDtor(arr3 + i);
    }

    MinibusDtor(&m2);

    for (i = 2; i >= 0; --i)
    {
        PublicTransportDtor(arr2 + i);
    }

    MinibusDtor(&m);
    
    return 0;
 }