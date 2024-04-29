#include <windows.h>
#include "nwpdlg.h"
#include "resource.h"
#include "exception"

class main_dialog : public vsite::nwp::dialog 
{
protected:

	public: POINT mousePosition;

	int idd() const override
	{ 
		return IDD_DIALOG1; 
	}
	bool on_init_dialog() override
	{
		// set initial values to edit controls
		set_int(IDC_EDIT1, mousePosition.x);
		set_int(IDC_EDIT2, mousePosition.y);
		return true;
	}
	bool on_ok() override
	{
		// get current values from edit controls
		// if not valid return false
		try {
			mousePosition.x = get_int(IDC_EDIT1);
			mousePosition.y = get_int(IDC_EDIT2);
		}
		catch (std::exception) {
			return false;
		}
		return true;
	}
	void on_cancel() override { }
	bool on_command(int id, int code) override { return false; }
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	main_dialog dlg;
	// find current mouse position and transfer to dialog
	GetCursorPos(&dlg.mousePosition);

	if(dlg.do_modal(instance, 0) == IDOK)
	{
		// set mouse position to coordinates from dialog
		SetCursorPos(dlg.mousePosition.x, dlg.mousePosition.y);
	}
	return 0;
}
