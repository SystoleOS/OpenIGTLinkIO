/*==========================================================================

  Portions (c) Copyright 2008-2009 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Date:      $Date: 2010-11-23 00:58:13 -0500 (Tue, 23 Nov 2010) $
  Version:   $Revision: 15552 $

==========================================================================*/

#ifndef IGTLIOVIDEODEVICE_H
#define IGTLIOVIDEODEVICE_H

#include "igtlioDevicesExport.h"

#include "igtlioVideoConverter.h"
#include "igtlioDevice.h"


class vtkImageData;

namespace igtlio
{

typedef vtkSmartPointer<class VideoDevice> VideoDevicePointer;

/// A Device supporting the Video igtl Message.
class OPENIGTLINKIO_DEVICES_EXPORT VideoDevice : public Device
{
public:
  
  enum {
    VideoModifiedEvent         = 118961,
  };
  
 virtual unsigned int GetDeviceContentModifiedEvent() const VTK_OVERRIDE;
 virtual std::string GetDeviceType() const VTK_OVERRIDE;
 virtual int ReceiveIGTLMessage(igtl::MessageBase::Pointer buffer, bool checkCRC) VTK_OVERRIDE;
 virtual igtl::MessageBase::Pointer GetIGTLMessage() VTK_OVERRIDE;
 virtual igtl::MessageBase::Pointer GetIGTLMessage(MESSAGE_PREFIX prefix) VTK_OVERRIDE ;
 virtual std::set<MESSAGE_PREFIX> GetSupportedMessagePrefixes() const VTK_OVERRIDE;
 
 igtl::VideoMessage::Pointer GetCompressedIGTLMessage();
  
  void SetContent(VideoConverter::ContentData content);
  
  VideoConverter::ContentData  GetContent();
  
  std::string GetCurrentCodecType()
  {
    return CurrentCodecType;
  };
  
  int SetCurrentCodecType(std::string codecType)
  {
  if (codecType.compare(IGTL_VIDEO_CODEC_NAME_X265)==0 || codecType.compare(IGTL_VIDEO_CODEC_NAME_VP9)==0 || codecType.compare(IGTL_VIDEO_CODEC_NAME_H264)==0 || codecType.compare(IGTL_VIDEO_CODEC_NAME_OPENHEVC)==0)
    {
    this->CurrentCodecType = std::string(codecType);
    return 0;
    }
  else
    {
    return -1;
    }
  };
  

public:
  static VideoDevice *New();
  vtkTypeMacro(VideoDevice,Device);
  void PrintSelf(ostream& os, vtkIndent indent) VTK_OVERRIDE;

protected:
  VideoDevice();
  ~VideoDevice();

 protected:
  igtl::StartVideoMessage::Pointer StartVideoMessage;
  
  igtl::StopVideoMessage::Pointer StopVideoMessage;

  VideoConverter::ContentData Content;
  
  GenericDecoder* VideoStreamDecoderVPX;
  
  GenericDecoder* VideoStreamDecoderX265;
  
  GenericDecoder* VideoStreamDecoderH264;
  
  std::map<std::string,GenericDecoder*> DecodersMap;
  
  SourcePicture* DecodedPic;
  
  std::string CurrentCodecType;
  
  GenericEncoder* VideoStreamEncoderVPX;
  
  GenericEncoder* VideoStreamEncoderX265;
  
  GenericEncoder* VideoStreamEncoderH264;
  
};

//---------------------------------------------------------------------------
class OPENIGTLINKIO_DEVICES_EXPORT VideoDeviceCreator : public DeviceCreator
{
public:
  virtual DevicePointer Create(std::string device_name) VTK_OVERRIDE;
  virtual std::string GetDeviceType() const VTK_OVERRIDE;

  static VideoDeviceCreator *New();
  vtkTypeMacro(VideoDeviceCreator,vtkObject);
};

} //namespace igtlio

#endif //IGTLIOVIDEODEVICE_H
