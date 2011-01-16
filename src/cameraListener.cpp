/*
 * cameraListener.cpp
 *
 *  Created on: 2011-01-01
 *      Author: bunny1985
 */

#include "MainForm.h"


MainForm::cameraListener::cameraListener(MainForm *MF){
	mainform=MF;
}
void MainForm::cameraListener::OnCameraAutoFocused(bool completeCondition)
{
}

void MainForm::cameraListener::OnCameraPreviewed( Osp::Base::ByteBuffer& previewedData, result r)
{

}

void MainForm::cameraListener::OnCameraCaptured( Osp::Base::ByteBuffer& capturedData, result r)
{

}

void MainForm::cameraListener::OnCameraErrorOccurred(CameraErrorReason r )
{
	 AppLogException("WHAT A TERIBLE FAIL (WTF?)");
	 mainform->CancelFlash();

}



void MainForm::cameraListener::OnVideoRecorderEndReached(RecordingEndCondition endCondition)
{
	AppLog("End of writing need to be restarted\n");
	mainform->FlashAgain();

}

void MainForm::cameraListener::OnVideoRecorderErrorOccurred( RecorderErrorReason r )
{
	AppLogException("WHAT A TERIBLE FAIL (WTF?)");
	mainform->CancelFlash();
}

void MainForm::cameraListener::OnVideoRecorderCanceled( result r )
{
	AppLog("Stoped ");
}
void MainForm::cameraListener::OnVideoRecorderClosed( result r )
{
	AppLog("recorder object closed \n");
}


void MainForm::cameraListener::OnVideoRecorderPaused( result r )
{
}
void MainForm::cameraListener::OnVideoRecorderStarted( result r )
{
}
void MainForm::cameraListener::OnVideoRecorderStopped( result r )
{
}

