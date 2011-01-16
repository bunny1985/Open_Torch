
#ifndef _MAINFORM_H_
#define _MAINFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FMedia.h>
#include <FSystem.h>

using namespace Osp::Media;



class MainForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IActionEventListener
{


public:
	MainForm(void);
	virtual ~MainForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void termination_requested();
private:
	class cameraListener :
		public Osp::Media::IVideoRecorderEventListener,
		public Osp::Media::ICameraEventListener

	{
	public:

			cameraListener(MainForm *MF);
	    void OnCameraAutoFocused(bool completeCondition);
	    void OnCameraPreviewed( Osp::Base::ByteBuffer& previewedData, result r) ;
	    void OnCameraCaptured( Osp::Base::ByteBuffer& capturedData, result r);
	    void OnCameraErrorOccurred(CameraErrorReason r );
		   void OnVideoRecorderCanceled( result r );
		   void OnVideoRecorderClosed( result r );
		   void OnVideoRecorderEndReached(RecordingEndCondition endCondition);
		   void OnVideoRecorderErrorOccurred( RecorderErrorReason r );
		   void OnVideoRecorderPaused( result r );
		   void OnVideoRecorderStarted( result r );
		   void OnVideoRecorderStopped( result r );
	private:
		  MainForm* mainform;

	};


	cameraListener* pListener;
	Osp::Media::VideoRecorder* recorder;
	Osp::Graphics::BufferInfo PreviewBufferInfo;
	Osp::Media::Camera* cam;
	void showWarningMessage();
	void CancelFlash();
	void FlashAgain();
	void showErrorMessage();
	void getfilenameanddsize();
	Osp::Base::String filename;
	Osp::Base::Long thefilesize;



protected:
public:
	virtual void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
};

#endif
