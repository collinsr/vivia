/*ckwg +5
 * Copyright 2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include "vtkVgVideoFrame.h"

//-----------------------------------------------------------------------------
vtkVgVideoFrame::vtkVgVideoFrame()
{
}

//-----------------------------------------------------------------------------
vtkVgVideoFrame::vtkVgVideoFrame(const vtkSmartPointer<vtkImageData>& sptr) :
  Image(sptr)
{
  sptr->Register(sptr);
}

//-----------------------------------------------------------------------------
vtkImageData* vtkVgVideoFrame::GetImageData()
{
  return this->Image.GetPointer();
}
