
#include "jamb.h"

int main() 
{
	//Jamb::Window jw;

	Jamb::ContainerWidget bw;
	Jamb::ContainerWidget bw2(bw);

	bw.add_child(bw2);

	return 0;
}
