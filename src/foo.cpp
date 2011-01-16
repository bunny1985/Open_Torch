/**
 * Name        : foo
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "foo.h"


using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

foo::foo()
{
}

foo::~foo()
{
}

Application*
foo::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new foo();
}

bool
foo::OnAppInitializing(AppRegistry& appRegistry)
{
	pForm1= new MainForm();
	pForm1->Initialize();
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*pForm1);
	pFrame->SetCurrentForm(*pForm1);
	pForm1->Draw();
	pForm1->Show();

	return true;
}

bool
foo::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}

void
foo::OnForeground(void)
{
	//Nothing to do still flashing
}

void
foo::OnBackground(void)
{
	//Nothing to do still flashing
}

void
foo::OnLowMemory(void)
{
//nothing to do
}

void
foo::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{

	if(batteryLevel==BATTERY_CRITICAL || batteryLevel==BATTERY_EMPTY){
		pForm1->termination_requested();
		delete(pForm1);
		Terminate();
	}

}

void
foo::OnScreenOn (void)
{
	//nothing to do - still flashing
}

void
foo::OnScreenOff (void)
{
	//nothing to do - still flashing
}
