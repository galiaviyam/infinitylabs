
int main(void)
{
	enum E {AA, BB, CC, DD};
	enum E2 {TT, KK};
	enum E e = (enum E)2;
	enum E2 e2 = (enum E2)AA;
	// E2 e22 = KK;
	//++e;
	int i = e;
}
