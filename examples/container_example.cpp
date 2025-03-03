
#include "jamb/jamb.h"

class Win : public Jamb::JWindow
{
public:
	int i;
};

int main() 
{
	Win window;

	Jamb::JContainer container;
	Jamb::JContainer panel1;
	Jamb::JContainer panel2;
	Jamb::JContainer cpanel1;
	Jamb::JContainer cpanel2;
	Jamb::JContainer cpanel3;

	container.add_child(panel1);
	container.add_child(panel2);
	container.add_child(panel1); // will return false and do nothing, due to panel1 already having parent

	panel1.add_child(container); // will return false and do nothing, due to cycle prevention
	panel1.add_child(panel1);	 // will return false and do nothing, due to cycle prevention
	panel1.add_child(cpanel1);
	panel1.add_child(cpanel2);
	panel1.add_child(cpanel2);	 // will return false and do nothing, due to cpanel2 already having parent
	panel2.add_child(cpanel1);	 // will return false and do nothing, due to cpanel1 already having parent
	panel2.add_child(cpanel3);

	return 0;
}
