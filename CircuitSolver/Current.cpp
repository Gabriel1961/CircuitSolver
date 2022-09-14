#include "Current.h"

std::ostream& operator<<(std::ostream& os, const Current& t)
{
	os << t.value << " A";
	return os;
}