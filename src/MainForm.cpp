

#include "MainForm.h"
#include "foo.h"
//#include "cameraListener.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;
using namespace Osp::System;




MainForm::MainForm(void)
{
}

MainForm::~MainForm(void)
{}

bool MainForm::Initialize()
{
	Form::Construct(L"IDF_FORM1");
	return true;
}

result
MainForm::OnInitializing(void)
{
	result r = E_SUCCESS;


	SetSoftkeyActionId(SOFTKEY_1, 111);
	AddSoftkeyActionListener(SOFTKEY_1, *this);

	getfilenameanddsize();
	// Tworzenie obiektu obs³uguj¹cego zdarzenia kamery i nagrywania
		pListener = new cameraListener(this);

		//PreviewBufferInfo = new Osp::Graphics::BufferInfo();

		cam = new Camera();
		r = cam->Construct(*pListener, CAMERA_PRIMARY);
				if (IsFailed(r)) { goto ERRORHANDLER; }
		cam->PowerOn();
		recorder=new VideoRecorder;
		r = recorder->Construct(*pListener, *cam);
				if (IsFailed(r)) { goto ERRORHANDLER; }
		recorder->SetMaxRecordingTime(3600000); //time is 1 hour
		recorder->SetMaxRecordingSize(this->thefilesize.ToInt()); //  wielkoœc to 50 mega
		recorder->SetMode(VIDEORECORDER_MODE_VIDEO_ONLY); // tylko wideo
		recorder->SetQuality(RECORDING_QUALITY_LOW); //jakoœæ niska

		r=cam->SetFlash(true);
		r = cam->StartPreview(&PreviewBufferInfo, false);
				if (IsFailed(r)) { goto ERRORHANDLER; }
		r = recorder->CreateVideoFile(filename, true);
				if (IsFailed(r)) { goto ERRORHANDLER; }
		recorder->Record();
				if (IsFailed(r)) { goto ERRORHANDLER; }






	return r;
	ERRORHANDLER:
	this->termination_requested();
	return r;

}

result
MainForm::OnTerminating(void)
{
	CancelFlash();
	result r = E_SUCCESS;
	return r;
}



void
MainForm::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{

	if(actionId==111){
		this->showWarningMessage();
	}
}

void MainForm::termination_requested(){
	this->~MainForm();
}
void MainForm::showWarningMessage(){
	MessageBox messageBox;
	messageBox.Construct(L"WARNING!!!", L"Long Flashing can damage your led\nDo not forget to turn this app off\nmichal_banas@oicw.pl", MSGBOX_STYLE_OK, 20000);
	int res = 0 ;
	messageBox.ShowAndWait(res);
	this->RequestRedraw(true);
}
void MainForm::CancelFlash(){
	recorder->Cancel();
	recorder->Close();
	delete recorder;
	recorder=null;
	cam->PowerOff();
	delete cam;
	cam=null;
	delete pListener;
}
void MainForm::FlashAgain(){
	recorder->Cancel();
	recorder->Close();
	recorder->CreateVideoFile(filename, true);
	recorder->Record();

}
void MainForm::showErrorMessage(){
	MessageBox messageBox;
	messageBox.Construct(L"ERROR OCURED!!!", L"There has been terible error\nplease close this app \n It would be great if you send me this error descrpition  \nmichal_banas@oicw.pl" , MSGBOX_STYLE_OK, 20000);

	int res = 0 ;
	messageBox.ShowAndWait(res);
	this->RequestRedraw(true);
}
void MainForm::getfilenameanddsize(){
	int phonememory;
	int microsdmemory;

	RuntimeInfo::GetValue(L"AvailableInternalStorage", phonememory);

	RuntimeInfo::GetValue(L"AvailableExternalStorage", microsdmemory);
	Osp::Base::Long mem;
	if(phonememory>microsdmemory){
		mem = (phonememory/1024);
		AppLogException("writing on internal memory");
		filename =L"/Storagecard/Media/opentorch.mp4";
	}else{
		mem = (microsdmemory/1024);
		AppLogException("writing on external memory");

		filename = L"/Media/opentorch.mp4";
	}

	thefilesize=mem;
}


