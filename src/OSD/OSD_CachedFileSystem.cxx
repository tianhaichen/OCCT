// Copyright (c) 2021 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <OSD_CachedFileSystem.hxx>
#include <OSD_OpenFile.hxx>

IMPLEMENT_STANDARD_RTTIEXT(OSD_CachedFileSystem, OSD_FileSystem)

//=======================================================================
// function : IsSupportedPath
// purpose :
//=======================================================================
Standard_Boolean OSD_CachedFileSystem::IsSupportedPath (const TCollection_AsciiString& theUrl) const
{
  return OSD_FileSystem::DefaultFileSystem()->IsSupportedPath (theUrl);
}

//=======================================================================
// function : IsOpenIStream
// purpose :
//=======================================================================
Standard_Boolean OSD_CachedFileSystem::IsOpenIStream (const opencascade::std::shared_ptr<std::istream>& theStream) const
{
  return OSD_FileSystem::DefaultFileSystem()->IsOpenIStream (theStream);
}

//=======================================================================
// function : IsOpenOStream
// purpose :
//=======================================================================
Standard_Boolean OSD_CachedFileSystem::IsOpenOStream (const opencascade::std::shared_ptr<std::ostream>& theStream) const
{
  return OSD_FileSystem::DefaultFileSystem()->IsOpenOStream (theStream);
}

//=======================================================================
// function : OpenIStream
// purpose :
//=======================================================================
opencascade::std::shared_ptr<std::istream> OSD_CachedFileSystem::OpenIStream (const TCollection_AsciiString& theUrl,
                                                                              const std::ios_base::openmode theParams,
                                                                              const int64_t theOffset,
                                                                              const opencascade::std::shared_ptr<std::istream>& /*theOldStream*/)
{
  if (myStream.Url != theUrl)
  {
    myStream.Url = theUrl;
    myStream.Reset();
  }
  myStream.Stream = OSD_FileSystem::DefaultFileSystem()->OpenIStream (theUrl, theParams, theOffset, myStream.Stream);
  return myStream.Stream;
}

//=======================================================================
// function : OpenOStream
// purpose :
//=======================================================================
opencascade::std::shared_ptr<std::ostream> OSD_CachedFileSystem::OpenOStream (const TCollection_AsciiString& theUrl,
                                                                              const std::ios_base::openmode theMode)
{
  return OSD_FileSystem::DefaultFileSystem()->OpenOStream (theUrl, theMode);
}

//=======================================================================
// function : OpenStreamBuffer
// purpose :
//=======================================================================
opencascade::std::shared_ptr<std::streambuf> OSD_CachedFileSystem::OpenStreamBuffer (const TCollection_AsciiString& theUrl,
                                                                                     const std::ios_base::openmode theMode,
                                                                                     const int64_t theOffset,
                                                                                     int64_t* theOutBufSize)
{
  if ((theMode & std::ios::out) == std::ios::out)
  {
    return OSD_FileSystem::DefaultFileSystem()->OpenStreamBuffer (theUrl, theMode, theOffset, theOutBufSize);
  }
  if (myStream.Url != theUrl)
  {
    myStream.Url = theUrl;
    myStream.Reset();
  }
  myStream.StreamBuf = OSD_FileSystem::DefaultFileSystem()->OpenStreamBuffer (theUrl, theMode, theOffset, theOutBufSize);
  return myStream.StreamBuf;
}
