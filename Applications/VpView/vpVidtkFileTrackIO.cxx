/*ckwg +5
 * Copyright 2018 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#include "vpVidtkFileTrackIO.h"

#include "vpFileTrackIOImpl.h"
#include "vpVidtkFileReader.h"

//-----------------------------------------------------------------------------
vpVidtkFileTrackIO::vpVidtkFileTrackIO(
  vpVidtkFileReader& reader,
  std::map<vtkVgTrack*, vidtk::track_sptr>& trackMap,
  std::map<unsigned int, vtkIdType>& sourceIdToModelIdMap,
  vtkVpTrackModel* trackModel,
  TrackStorageMode storageMode,
  TrackTimeStampMode timeStampMode,
  vtkVgTrackTypeRegistry* trackTypes,
  vtkMatrix4x4* geoTransform,
  vpFrameMap* frameMap) :
  vpVidtkTrackIO(reader, trackMap, sourceIdToModelIdMap, trackModel,
                 storageMode, timeStampMode, trackTypes, geoTransform,
                 frameMap)
{}

//-----------------------------------------------------------------------------
bool vpVidtkFileTrackIO::ReadTracks()
{
  auto& reader = static_cast<const vpVidtkFileReader&>(this->GetReader());
  const auto& tracksFileName = reader.GetTracksFileName();

  vpFileTrackIOImpl::TrackRegionMap trackRegionMap;
  vpFileTrackIOImpl::ReadRegionsFile(this, tracksFileName, 0.0f, 0.0f,
                                     trackRegionMap);

  if (!vpVidtkTrackIO::ReadTracks(&trackRegionMap))
    {
    return false;
    }

  vpFileTrackIOImpl::ReadTypesFile(this, tracksFileName);

  return true;
}

//-----------------------------------------------------------------------------
bool vpVidtkFileTrackIO::ImportTracks(vtkIdType idsOffset,
                                      float offsetX, float offsetY)
{
  auto& reader = static_cast<const vpVidtkFileReader&>(this->GetReader());
  const auto& tracksFileName = reader.GetTracksFileName();

  vpFileTrackIOImpl::TrackRegionMap trackRegionMap;
  vpFileTrackIOImpl::ReadRegionsFile(this, tracksFileName, offsetX, offsetY,
                                     trackRegionMap);

  if (!vpVidtkTrackIO::ImportTracks(&trackRegionMap, idsOffset,
                                    offsetX, offsetY))
    {
    return false;
    }

  vpFileTrackIOImpl::ReadTypesFile(this, tracksFileName);

  return true;
}

//-----------------------------------------------------------------------------
bool vpVidtkFileTrackIO::ReadTrackTraits()
{
  return vpFileTrackIOImpl::ReadTrackTraits(
           this, static_cast<const vpVidtkFileReader&>(
                   this->GetReader()).GetTrackTraitsFileName());
}
