; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CISAMExtension
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ISAM.h"

ClassCount=2
Class1=CISAMExtension
ResourceCount=0
LastPage=0
Class2=CImagesRS

[CLS:CISAMExtension]
Type=0
HeaderFile=ISAM.h
ImplementationFile=ISAM.cpp
Filter=N
LastObject=CISAMExtension

[CLS:CImagesRS]
Type=0
HeaderFile=ImagesRS.h
ImplementationFile=ImagesRS.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CImagesRS

[DB:CImagesRS]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[image_id], 4, 4
Column2=[image_title], 12, 255
Column3=[image_filename], 12, 255

