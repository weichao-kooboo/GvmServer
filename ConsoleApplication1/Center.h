#pragma once

#ifndef _C_CENTER_INCLUDE_
#define _C_CENTER_INCLUDE_

#include <vector>
#include <string>
#include "RegisterCenter.h"
using namespace std;

typedef void* (*NewInstance)();

#define REGISTER_CLASS(class_name)		\
class class_name##Register			\
{	\
public:				\
	static void *NewInstance()		\
{	\
		return new class_name();		\
}	\
private:			\
	static Center c;			\
};		\
Center class_name##Register::c(#class_name,class_name##Register::NewInstance)

#define MM(class_name)			\
int temp=getCenter(#class_name,new class_name());

int getCenter(string, void *c);

class Center {
public:
	Center() = default;
	Center(string, NewInstance c);
	~Center() = default;
	static int registerClass(string , void *c);
private:
	typedef struct{
		//class name
		string className;
		//class pointer
		void *c;
	}Elem;
	vector<Elem *> class_vec;
};
#endif // !_C_CENTER_INCLUDE_