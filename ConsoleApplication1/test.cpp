#include "stdafx.h"
#include "test.h"

int k = 0;
void func1() {
	k++;
	cout << "func1" << endl;
}

static void func2() {
	k++;
	cout << "func2" << endl;
}
test::test()
{
	num = 0;
}

void test::run()
{
	func2();
	func2();
	cout << k << endl;
}


test::~test()
{
}
