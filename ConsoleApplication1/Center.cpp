#include "Center.h"

Center::Center(string, NewInstance c)
{

}

int Center::registerClass(string className, void *c)
{
	if (className.length() == 0)
		return -1;

	//void *i= REGISTER_CLASS(className);
	return 0;

}

int getCenter(string class_name, void *c) {
	int temp = tool::RegisterCenter<Center>::CreateInstance().registerClass(class_name, c);
	return temp;
}
