
#include "jamb/jamb.h"

class Win : public Jamb::JWindow
{
protected:

	Jamb::JContainer container;
	Jamb::JContainer panel1;
	Jamb::JContainer panel2;
	Jamb::JContainer cpanel1;
	Jamb::JContainer cpanel2;
	Jamb::JContainer cpanel3;

	void on_create(Jamb::JCreateEvent& jce)
	{
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

		show();
	}

	void on_size(Jamb::JSizeEvent& jre)
	{
		printf("size %i, %i\n", jre.height, jre.width);
	}

	void render(Jamb::JDrawEvent& jde)
	{

	}

	int i = 0;
};

int main()
{
	Win window1;
	window1.init();

	return Jamb::run_loop();
}
