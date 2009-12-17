// Copyright (c) 2001-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// This main DLL entry point for the TS_CommDb.dll
// 
//


// EPOC includes
#include <e32base.h>

// Test system includes
#include <networking/log.h>
#include <networking/teststep.h>
#include "Teststepcommdb.h"
#include <networking/testsuite.h>
#include "TestSuiteCommdb.h"
#include "step_001_01.h"
#include "step_002_01.h"
#include "Step_003_xx.h"
#include "step_004_xx.h"
#include "step_005_xx.h"
#include "step_006_xx.h"
#include "Step_007_xx.h"
#include "Step_008_xx.h"
#include "Step_009_xx.h"
#include "Step_010_xx.h"
#include "Step_011_xx.h"
#include "Step_012_xx.h"
#include "Step_013_xx.h"
#include "Step_014_xx.h"
#include "Step_015_xx.h"
#include "Step_016_xx.h"
#include "Step_017_xx.h"
#include "Step_018_xx.h"
#include "Step_019_xx.h"
#include "Step_020_xx.h"
#include "Step_021_xx.h"
#include "Step_022_xx.h"
#include "Step_023_xx.h"
#include "Step_024_xx.h"
#include "Step_025_xx.h"
#include "Step_026_xx.h"
#include "Step_027_xx.h"
#include "Step_028_xx.h"
#include "Step_029_xx.h"
#include "Step_030_xx.h"
#include "Step_031_xx.h"
#include "Step_032_xx.h"
#include "Step_033_xx.h"
#include "Step_034_xx.h"
#include "Step_035_xx.h"
#include "Step_036_xx.h"
#include "Step_037_xx.h"
#include "Step_038_xx.h"
#include "Step_039_xx.h"
#include "Step_040_xx.h"
#include "Step_041_xx.h"
#include "Step_042_xx.h"
#include "Step_043_xx.h"
#include "Step_044_xx.h"
#include "Step_045_xx.h"
#include "Step_046_xx.h"
#include "Step_047_xx.h"
#include "step_051_xx.h"
#include "step_052_xx.h"
#include "step_053_xx.h"
#include "step_054_xx.h"
#include "step_055_xx.h"
#include "step_056_xx.h"
#include "step_057_xx.h"
#include "step_058_xx.h"
#include "step_059_xx.h"
#include "Step_061_xx.h"
#include "Step_062_xx.h"
#include "step_063_xx.h"
#include "Step_064_xx.h"
#include "CommDbPreCopy.h"


EXPORT_C CTestSuiteCommDb* NewTestSuiteCommDb( void ) 
    { 
	return new (ELeave) CTestSuiteCommDb;
    }

// destructor
CTestSuiteCommDb::~CTestSuiteCommDb()
{
}

// make a version string available for test system 
#ifdef _DEBUG
_LIT(KTxtVersion,"1.0 (udeb)");
#else
_LIT(KTxtVersion,"1.0");
#endif

TPtrC CTestSuiteCommDb::GetVersion( void )
	{
	return KTxtVersion();
	}

// Add a test step into the suite
void CTestSuiteCommDb::AddTestStepL( CTestStepCommDb * ptrTestStep )
{
	// test steps contain a pointer back to the suite which owns them
	ptrTestStep->iCommDbSuite = this; 

	// add the step using tyhe base class method
	CTestSuite::AddTestStepL(ptrTestStep);
}


// second phase constructor for CommDb test suite
// this creates all the CommDb test steps and
// stores them inside CTestSuiteCommDb
void CTestSuiteCommDb::InitialiseL( void )
{

	// add test steps
	AddTestStepL( new(ELeave) CCommDbTest001_01 );
	AddTestStepL( new(ELeave) CCommDbTest001_03 );
	AddTestStepL( new(ELeave) CCommDbTest001_04 );
	AddTestStepL( new(ELeave) CCommDbTest001_05 );
	AddTestStepL( new(ELeave) CCommDbTest001_07 );
	AddTestStepL( new(ELeave) CCommDbTest001_08 );
	AddTestStepL( new(ELeave) CCommDbTest001_09 );
	AddTestStepL( new(ELeave) CCommDbTest001_10 );
	AddTestStepL( new(ELeave) CCommDbTest002_01 );
	AddTestStepL( new(ELeave) CCommDbTest003_01 );
	AddTestStepL( new(ELeave) CCommDbTest003_02 );
	AddTestStepL( new(ELeave) CCommDbTest003_03 );
	AddTestStepL( new(ELeave) CCommDbTest003_04 );
	AddTestStepL( new(ELeave) CCommDbTest003_05 );
	AddTestStepL( new(ELeave) CCommDbTest003_06 );
	AddTestStepL( new(ELeave) CCommDbTest003_07 );
	AddTestStepL( new(ELeave) CCommDbTest003_08 );
	AddTestStepL( new(ELeave) CCommDbTest004_01 );
	AddTestStepL( new(ELeave) CCommDbTest004_02 );
	AddTestStepL( new(ELeave) CCommDbTest004_03 );
	AddTestStepL( new(ELeave) CCommDbTest004_04 );
	AddTestStepL( new(ELeave) CCommDbTest004_05 );
	AddTestStepL( new(ELeave) CCommDbTest004_06 );
	AddTestStepL( new(ELeave) CCommDbTest005_01 );
	AddTestStepL( new(ELeave) CCommDbTest005_02 );
	AddTestStepL( new(ELeave) CCommDbTest005_03 );
	AddTestStepL( new(ELeave) CCommDbTest005_04 );
	AddTestStepL( new(ELeave) CCommDbTest006_01 );
	AddTestStepL( new(ELeave) CCommDbTest006_02 );
	AddTestStepL( new(ELeave) CCommDbTest006_03 );
	AddTestStepL( new(ELeave) CCommDbTest006_04 );
	AddTestStepL( new(ELeave) CCommDbTest006_05 );
	AddTestStepL( new(ELeave) CCommDbTest007_01 );
	AddTestStepL( new(ELeave) CCommDbTest007_02 );
	AddTestStepL( new(ELeave) CCommDbTest007_03 );
	AddTestStepL( new(ELeave) CCommDbTest007_04 );
	AddTestStepL( new(ELeave) CCommDbTest007_05 );
	AddTestStepL( new(ELeave) CCommDbTest007_06 );	
	AddTestStepL( new(ELeave) CCommDbTest007_07 );
	AddTestStepL( new(ELeave) CCommDbTest007_08 );
	AddTestStepL( new(ELeave) CCommDbTest007_09 );
	AddTestStepL( new(ELeave) CCommDbTest007_10 );
	AddTestStepL( new(ELeave) CCommDbTest007_11 );
	AddTestStepL( new(ELeave) CCommDbTest007_12 );
	AddTestStepL( new(ELeave) CCommDbTest007_14 );
	AddTestStepL( new(ELeave) CCommDbTest007_15 );
	AddTestStepL( new(ELeave) CCommDbTest007_16 );
	AddTestStepL( new(ELeave) CCommDbTest007_17 );
	AddTestStepL( new(ELeave) CCommDbTest007_18 );
	AddTestStepL( new(ELeave) CCommDbTest007_19 );
	AddTestStepL( new(ELeave) CCommDbTest007_20 );
	AddTestStepL( new(ELeave) CCommDbTest008_01 );
	AddTestStepL( new(ELeave) CCommDbTest008_02 );
	AddTestStepL( new(ELeave) CCommDbTest008_03 );
	AddTestStepL( new(ELeave) CCommDbTest008_04 );
	AddTestStepL( new(ELeave) CCommDbTest009_01 );
	AddTestStepL( new(ELeave) CCommDbTest009_02 );
	AddTestStepL( new(ELeave) CCommDbTest009_03 );
	AddTestStepL( new(ELeave) CCommDbTest009_04 );
	AddTestStepL( new(ELeave) CCommDbTest009_05 );
	AddTestStepL( new(ELeave) CCommDbTest009_06 );
	AddTestStepL( new(ELeave) CCommDbTest009_07 );
	AddTestStepL( new(ELeave) CCommDbTest009_08 );
	AddTestStepL( new(ELeave) CCommDbTest009_09 );
	AddTestStepL( new(ELeave) CCommDbTest009_10 );
	AddTestStepL( new(ELeave) CCommDbTest009_11 );
	AddTestStepL( new(ELeave) CCommDbTest009_12 );
	AddTestStepL( new(ELeave) CCommDbTest009_13 );
	AddTestStepL( new(ELeave) CCommDbTest009_14 );
	AddTestStepL( new(ELeave) CCommDbTest009_15 );
	AddTestStepL( new(ELeave) CCommDbTest009_16 );
	AddTestStepL( new(ELeave) CCommDbTest009_17 );
	AddTestStepL( new(ELeave) CCommDbTest009_18 );
	AddTestStepL( new(ELeave) CCommDbTest009_19 );
	AddTestStepL( new(ELeave) CCommDbTest009_20 );
	AddTestStepL( new(ELeave) CCommDbTest009_21 );
	AddTestStepL( new(ELeave) CCommDbTest010_01 );
	AddTestStepL( new(ELeave) CCommDbTest010_02 );
	AddTestStepL( new(ELeave) CCommDbTest010_03 );
	AddTestStepL( new(ELeave) CCommDbTest010_04 );
	AddTestStepL( new(ELeave) CCommDbTest010_05 );
	AddTestStepL( new(ELeave) CCommDbTest011_01 );
	AddTestStepL( new(ELeave) CCommDbTest011_02 );
	AddTestStepL( new(ELeave) CCommDbTest011_03 );
	AddTestStepL( new(ELeave) CCommDbTest011_04 );
	AddTestStepL( new(ELeave) CCommDbTest012_01 );
	AddTestStepL( new(ELeave) CCommDbTest012_02 );
	AddTestStepL( new(ELeave) CCommDbTest012_03 );
	AddTestStepL( new(ELeave) CCommDbTest012_04 );
	AddTestStepL( new(ELeave) CCommDbTest012_05 );
	AddTestStepL( new(ELeave) CCommDbTest012_06 );
	AddTestStepL( new(ELeave) CCommDbTest012_07 );
	AddTestStepL( new(ELeave) CCommDbTest013_01 );
	AddTestStepL( new(ELeave) CCommDbTest013_02 );
	AddTestStepL( new(ELeave) CCommDbTest013_03 );
	AddTestStepL( new(ELeave) CCommDbTest013_04 );
	AddTestStepL( new(ELeave) CCommDbTest014_01 );
	AddTestStepL( new(ELeave) CCommDbTest014_02 );
	AddTestStepL( new(ELeave) CCommDbTest014_03 );
	AddTestStepL( new(ELeave) CCommDbTest014_04 );
	AddTestStepL( new(ELeave) CCommDbTest015_01 );
	AddTestStepL( new(ELeave) CCommDbTest015_02 );
	AddTestStepL( new(ELeave) CCommDbTest015_03 );
	AddTestStepL( new(ELeave) CCommDbTest015_04 );
	AddTestStepL( new(ELeave) CCommDbTest015_05 );
	AddTestStepL( new(ELeave) CCommDbTest015_06 );
	AddTestStepL( new(ELeave) CCommDbTest015_07 );
	AddTestStepL( new(ELeave) CCommDbTest015_08 );
	AddTestStepL( new(ELeave) CCommDbTest015_09 );
	AddTestStepL( new(ELeave) CCommDbTest015_10 );
	AddTestStepL( new(ELeave) CCommDbTest015_11 );
	AddTestStepL( new(ELeave) CCommDbTest015_12 );
	AddTestStepL( new(ELeave) CCommDbTest015_13 );
	AddTestStepL( new(ELeave) CCommDbTest015_14 );
	AddTestStepL( new(ELeave) CCommDbTest015_15 );
	AddTestStepL( new(ELeave) CCommDbTest015_16 );
	AddTestStepL( new(ELeave) CCommDbTest016_01 );
	AddTestStepL( new(ELeave) CCommDbTest016_02 );
	AddTestStepL( new(ELeave) CCommDbTest016_04 );
	AddTestStepL( new(ELeave) CCommDbTest016_05 );
	AddTestStepL( new(ELeave) CCommDbTest016_07 );
	AddTestStepL( new(ELeave) CCommDbTest016_08 );
	AddTestStepL( new(ELeave) CCommDbTest016_09 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_01 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_02 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_03 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_04 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_05 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_06 ); 
	AddTestStepL( new(ELeave) CCommDbTest017_07 ); 
	AddTestStepL( new(ELeave) CCommDbTest018_01 ); 
	AddTestStepL( new(ELeave) CCommDbTest018_02 ); 
	AddTestStepL( new(ELeave) CCommDbTest018_03 ); 
	AddTestStepL( new(ELeave) CCommDbTest018_04 ); 
	AddTestStepL( new(ELeave) CCommDbTest018_05 );
	AddTestStepL( new(ELeave) CCommDbTest018_06 );
	AddTestStepL( new(ELeave) CCommDbTest018_07 );
	AddTestStepL( new(ELeave) CCommDbTest018_08 );
	AddTestStepL( new(ELeave) CCommDbTest019_01 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_02 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_03 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_04 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_05 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_06 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_07 ); 
	AddTestStepL( new(ELeave) CCommDbTest019_08 );
	AddTestStepL( new(ELeave) CCommDbTest019_09 );
	AddTestStepL( new(ELeave) CCommDbTest019_10 );
	AddTestStepL( new(ELeave) CCommDbTest019_11 );
	AddTestStepL( new(ELeave) CCommDbTest019_12 );
	AddTestStepL( new(ELeave) CCommDbTest019_13 );
	AddTestStepL( new(ELeave) CCommDbTest019_14 );
	AddTestStepL( new(ELeave) CCommDbTest020_01 );
	AddTestStepL( new(ELeave) CCommDbTest020_02 );
	AddTestStepL( new(ELeave) CCommDbTest020_03 );
	AddTestStepL( new(ELeave) CCommDbTest020_04 );
	AddTestStepL( new(ELeave) CCommDbTest020_05 );
	AddTestStepL( new(ELeave) CCommDbTest020_06 );
	AddTestStepL( new(ELeave) CCommDbTest020_07 );
	AddTestStepL( new(ELeave) CCommDbTest020_08 );
	AddTestStepL( new(ELeave) CCommDbTest021_01 );
	AddTestStepL( new(ELeave) CCommDbTest021_02 );
	AddTestStepL( new(ELeave) CCommDbTest021_03 );
	AddTestStepL( new(ELeave) CCommDbTest021_04 );
	AddTestStepL( new(ELeave) CCommDbTest021_05 );
	AddTestStepL( new(ELeave) CCommDbTest022_01 );
	AddTestStepL( new(ELeave) CCommDbTest022_02 );
	AddTestStepL( new(ELeave) CCommDbTest022_03 );
	AddTestStepL( new(ELeave) CCommDbTest022_04 );
	AddTestStepL( new(ELeave) CCommDbTest022_05 );
	AddTestStepL( new(ELeave) CCommDbTest022_06 );
	AddTestStepL( new(ELeave) CCommDbTest022_07 );
	AddTestStepL( new(ELeave) CCommDbTest022_08 );
	AddTestStepL( new(ELeave) CCommDbTest022_09 );
	AddTestStepL( new(ELeave) CCommDbTest022_10 );
	AddTestStepL( new(ELeave) CCommDbTest022_11 );
	AddTestStepL( new(ELeave) CCommDbTest022_12 );
	AddTestStepL( new(ELeave) CCommDbTest022_13 );
	AddTestStepL( new(ELeave) CCommDbTest022_14 );
	AddTestStepL( new(ELeave) CCommDbTest022_16 );
	AddTestStepL( new(ELeave) CCommDbTest022_17 );
	AddTestStepL( new(ELeave) CCommDbTest022_18 );
	AddTestStepL( new(ELeave) CCommDbTest022_19 );
	AddTestStepL( new(ELeave) CCommDbTest022_20 );
	AddTestStepL( new(ELeave) CCommDbTest022_21 );
	AddTestStepL( new(ELeave) CCommDbTest022_22 );
	AddTestStepL( new(ELeave) CCommDbTest022_23 );
	AddTestStepL( new(ELeave) CCommDbTest022_24 );
	AddTestStepL( new(ELeave) CCommDbTest022_25 );
	AddTestStepL( new(ELeave) CCommDbTest022_26 );
	AddTestStepL( new(ELeave) CCommDbTest022_27 );
	AddTestStepL( new(ELeave) CCommDbTest022_28 );
	AddTestStepL( new(ELeave) CCommDbTest022_29 );
	AddTestStepL( new(ELeave) CCommDbTest022_30 );
	AddTestStepL( new(ELeave) CCommDbTest023_01 );
	AddTestStepL( new(ELeave) CCommDbTest023_02 );
	AddTestStepL( new(ELeave) CCommDbTest023_03 );
	AddTestStepL( new(ELeave) CCommDbTest023_04 );
	AddTestStepL( new(ELeave) CCommDbTest023_05 );
	AddTestStepL( new(ELeave) CCommDbTest023_06 );
	AddTestStepL( new(ELeave) CCommDbTest024_01 );
	AddTestStepL( new(ELeave) CCommDbTest024_02 );
	AddTestStepL( new(ELeave) CCommDbTest024_03 );
	AddTestStepL( new(ELeave) CCommDbTest024_04 );
	AddTestStepL( new(ELeave) CCommDbTest024_05 );
	AddTestStepL( new(ELeave) CCommDbTest024_06 );
	AddTestStepL( new(ELeave) CCommDbTest024_07 );
	AddTestStepL( new(ELeave) CCommDbTest024_08 );
	AddTestStepL( new(ELeave) CCommDbTest024_09 );
	AddTestStepL( new(ELeave) CCommDbTest025_01 );
	AddTestStepL( new(ELeave) CCommDbTest025_02 );
	AddTestStepL( new(ELeave) CCommDbTest026_01 );
	AddTestStepL( new(ELeave) CCommDbTest026_02 );
	AddTestStepL( new(ELeave) CCommDbTest026_03 );
	AddTestStepL( new(ELeave) CCommDbTest026_04 );
	AddTestStepL( new(ELeave) CCommDbTest026_05 );
	AddTestStepL( new(ELeave) CCommDbTest026_06 );
	AddTestStepL( new(ELeave) CCommDbTest026_07 );
	AddTestStepL( new(ELeave) CCommDbTest026_08 );
	AddTestStepL( new(ELeave) CCommDbTest026_09 );
	AddTestStepL( new(ELeave) CCommDbTest026_10 );
	AddTestStepL( new(ELeave) CCommDbTest026_11 );
	AddTestStepL( new(ELeave) CCommDbTest026_12 );
	AddTestStepL( new(ELeave) CCommDbTest026_13 );
	AddTestStepL( new(ELeave) CCommDbTest026_14 );
	AddTestStepL( new(ELeave) CCommDbTest026_15 );
	AddTestStepL( new(ELeave) CCommDbTest026_16 );
	AddTestStepL( new(ELeave) CCommDbTest027_01 );
	AddTestStepL( new(ELeave) CCommDbTest027_02 );
	AddTestStepL( new(ELeave) CCommDbTest028_01 );
	AddTestStepL( new(ELeave) CCommDbTest028_02 );
	AddTestStepL( new(ELeave) CCommDbTest028_03 );
	AddTestStepL( new(ELeave) CCommDbTest028_04 );
	AddTestStepL( new(ELeave) CCommDbTest028_05 );
	AddTestStepL( new(ELeave) CCommDbTest028_06 );
	AddTestStepL( new(ELeave) CCommDbTest028_07 );
	AddTestStepL( new(ELeave) CCommDbTest029_01 );
	AddTestStepL( new(ELeave) CCommDbTest029_02 );
	AddTestStepL( new(ELeave) CCommDbTest029_03 );
	AddTestStepL( new(ELeave) CCommDbTest029_04 );
	AddTestStepL( new(ELeave) CCommDbTest030_01 );
	AddTestStepL( new(ELeave) CCommDbTest030_02 );
	AddTestStepL( new(ELeave) CCommDbTest030_03 ); 
	AddTestStepL( new(ELeave) CCommDbTest031_01 );
	AddTestStepL( new(ELeave) CCommDbTest031_02 );
	AddTestStepL( new(ELeave) CCommDbTest031_03 );
	AddTestStepL( new(ELeave) CCommDbTest031_04 );
	AddTestStepL( new(ELeave) CCommDbTest031_05 );
	AddTestStepL( new(ELeave) CCommDbTest032_01 );
	AddTestStepL( new(ELeave) CCommDbTest032_02 );
	AddTestStepL( new(ELeave) CCommDbTest032_03 );
	AddTestStepL( new(ELeave) CCommDbTest032_04 );
	AddTestStepL( new(ELeave) CCommDbTest032_05 );
	AddTestStepL( new(ELeave) CCommDbTest033_01 );
	AddTestStepL( new(ELeave) CCommDbTest033_02 );
	AddTestStepL( new(ELeave) CCommDbTest033_03 );
	AddTestStepL( new(ELeave) CCommDbTest033_04 );
	AddTestStepL( new(ELeave) CCommDbTest033_05 );
	AddTestStepL( new(ELeave) CCommDbTest033_06 );
	AddTestStepL( new(ELeave) CCommDbTest033_07 );
	AddTestStepL( new(ELeave) CCommDbTest033_08 );
	AddTestStepL( new(ELeave) CCommDbTest033_09 );
	AddTestStepL( new(ELeave) CCommDbTest034_01 );
	AddTestStepL( new(ELeave) CCommDbTest034_02 );
	AddTestStepL( new(ELeave) CCommDbTest034_03 );
	AddTestStepL( new(ELeave) CCommDbTest034_04 );
	AddTestStepL( new(ELeave) CCommDbTest034_05 );
	AddTestStepL( new(ELeave) CCommDbTest034_06 );

	AddTestStepL( new(ELeave) CCommDbTest035_01 );
	AddTestStepL( new(ELeave) CCommDbTest035_02 );
	AddTestStepL( new(ELeave) CCommDbTest035_03 );
	AddTestStepL( new(ELeave) CCommDbTest035_04 );
	AddTestStepL( new(ELeave) CCommDbTest036_01 );
	AddTestStepL( new(ELeave) CCommDbTest036_02 );
	AddTestStepL( new(ELeave) CCommDbTest036_03 );
	AddTestStepL( new(ELeave) CCommDbTest036_04 );
	AddTestStepL( new(ELeave) CCommDbTest036_05 );
	AddTestStepL( new(ELeave) CCommDbTest036_06 );
	AddTestStepL( new(ELeave) CCommDbTest036_07 );
	AddTestStepL( new(ELeave) CCommDbTest036_08 );
	AddTestStepL( new(ELeave) CCommDbTest036_09 );
	AddTestStepL( new(ELeave) CCommDbTest036_10 );
	AddTestStepL( new(ELeave) CCommDbTest036_11 );
	AddTestStepL( new(ELeave) CCommDbTest036_12 );
	AddTestStepL( new(ELeave) CCommDbTest036_13 );
	AddTestStepL( new(ELeave) CCommDbTest036_14 );
	AddTestStepL( new(ELeave) CCommDbTest036_15 );
	AddTestStepL( new(ELeave) CCommDbTest036_16 );
	AddTestStepL( new(ELeave) CCommDbTest036_17 );
	AddTestStepL( new(ELeave) CCommDbTest036_18 );
	AddTestStepL( new(ELeave) CCommDbTest037_01 );
	AddTestStepL( new(ELeave) CCommDbTest037_02 );
	AddTestStepL( new(ELeave) CCommDbTest037_03 );
	AddTestStepL( new(ELeave) CCommDbTest038_01 );
	AddTestStepL( new(ELeave) CCommDbTest038_02 );
	AddTestStepL( new(ELeave) CCommDbTest038_03 );
	AddTestStepL( new(ELeave) CCommDbTest039_01 );
	AddTestStepL( new(ELeave) CCommDbTest039_02 );
	AddTestStepL( new(ELeave) CCommDbTest040_01 );
	AddTestStepL( new(ELeave) CCommDbTest040_02 );
	AddTestStepL( new(ELeave) CCommDbTest040_03 );
	AddTestStepL( new(ELeave) CCommDbTest041_01 );
	AddTestStepL( new(ELeave) CCommDbTest041_02 );
	AddTestStepL( new(ELeave) CCommDbTest041_03 );
	AddTestStepL( new(ELeave) CCommDbTest041_04 );
	AddTestStepL( new(ELeave) CCommDbTest041_05 );
	AddTestStepL( new(ELeave) CCommDbTest041_06 );
	AddTestStepL( new(ELeave) CCommDbTest041_07 );
	AddTestStepL( new(ELeave) CCommDbTest041_08 );
	AddTestStepL( new(ELeave) CCommDbTest041_09 );
	AddTestStepL( new(ELeave) CCommDbTest041_10 );
	AddTestStepL( new(ELeave) CCommDbTest041_11 );
	AddTestStepL( new(ELeave) CCommDbTest041_12 );
	AddTestStepL( new(ELeave) CCommDbTest041_13 );
	AddTestStepL( new(ELeave) CCommDbTest041_14 );
	AddTestStepL( new(ELeave) CCommDbTest041_15 );
	AddTestStepL( new(ELeave) CCommDbTest041_16 );
	AddTestStepL( new(ELeave) CCommDbTest041_17 );
	AddTestStepL( new(ELeave) CCommDbTest041_18 );
	AddTestStepL( new(ELeave) CCommDbTest041_19 );
	AddTestStepL( new(ELeave) CCommDbTest041_20 );
	AddTestStepL( new(ELeave) CCommDbTest041_21 );
	AddTestStepL( new(ELeave) CCommDbTest041_22 );
	AddTestStepL( new(ELeave) CCommDbTest041_23 );
	AddTestStepL( new(ELeave) CCommDbTest041_24 );
	AddTestStepL( new(ELeave) CCommDbTest041_25 );
	AddTestStepL( new(ELeave) CCommDbTest041_26 );
	AddTestStepL( new(ELeave) CCommDbTest041_27 );
	AddTestStepL( new(ELeave) CCommDbTest041_28 );
	AddTestStepL( new(ELeave) CCommDbTest041_29 );
	AddTestStepL( new(ELeave) CCommDbTest041_30 );
	AddTestStepL( new(ELeave) CCommDbTest041_31 );
	AddTestStepL( new(ELeave) CCommDbTest041_32 );
	AddTestStepL( new(ELeave) CCommDbTest041_33 );	
	AddTestStepL( new(ELeave) CCommDbTest041_34 );
	AddTestStepL( new(ELeave) CCommDbTest042_01 );
	AddTestStepL( new(ELeave) CCommDbTest042_02 );
	AddTestStepL( new(ELeave) CCommDbTest042_03 );
	AddTestStepL( new(ELeave) CCommDbTest043_01 );
	AddTestStepL( new(ELeave) CCommDbTest043_02 );
	AddTestStepL( new(ELeave) CCommDbTest043_03 );
	AddTestStepL( new(ELeave) CCommDbTest043_04 );
	AddTestStepL( new(ELeave) CCommDbTest043_05 );
	AddTestStepL( new(ELeave) CCommDbTest044_01 );
	AddTestStepL( new(ELeave) CCommDbTest044_02 );
	AddTestStepL( new(ELeave) CCommDbTest044_03 );
	AddTestStepL( new(ELeave) CCommDbTest045_01 );
	AddTestStepL( new(ELeave) CCommDbTest045_02 );
	AddTestStepL( new(ELeave) CCommDbTest045_03 );
	AddTestStepL( new(ELeave) CCommDbTest046_01 );
	AddTestStepL( new(ELeave) CCommDbTest046_02 );
	AddTestStepL( new(ELeave) CCommDbTest046_03 );
	AddTestStepL( new(ELeave) CCommDbTest046_04 );
	AddTestStepL( new(ELeave) CCommDbTest046_05 );
	AddTestStepL( new(ELeave) CCommDbTest047_01 );
	AddTestStepL( new(ELeave) CCommDbTest047_02 );
	AddTestStepL( new(ELeave) CCommDbTest047_03 );
	AddTestStepL( new(ELeave) CCommDbTest047_04 );
	AddTestStepL( new(ELeave) CCommDbTest047_05 );
	AddTestStepL( new(ELeave) CCommDbTest047_06 );
	AddTestStepL( new(ELeave) CCommDbTest047_07 );
	AddTestStepL( new(ELeave) CCommDbTest047_08 );
	AddTestStepL( new(ELeave) CCommDbTest047_13 );
	AddTestStepL( new(ELeave) CCommDbTest051_01 );
	AddTestStepL( new(ELeave) CCommDbTest051_02 );
	AddTestStepL( new(ELeave) CCommDbTest052_01 );
	AddTestStepL( new(ELeave) CCommDbTest052_02 );
	AddTestStepL( new(ELeave) CCommDbTest053_01 );
	AddTestStepL( new(ELeave) CCommDbTest053_02 );
	AddTestStepL( new(ELeave) CCommDbTest054_01 );
	AddTestStepL( new(ELeave) CCommDbTest054_02 );
	AddTestStepL( new(ELeave) CCommDbTest055_01 );
	AddTestStepL( new(ELeave) CCommDbTest055_02 );
	AddTestStepL( new(ELeave) CCommDbTest056_01 );
	AddTestStepL( new(ELeave) CCommDbTest056_02 );
	AddTestStepL( new(ELeave) CCommDbTest057_01 );
	AddTestStepL( new(ELeave) CCommDbTest057_02 );
	AddTestStepL( new(ELeave) CCommDbTest058_01 );
	AddTestStepL( new(ELeave) CCommDbTest058_02 );
	AddTestStepL( new(ELeave) CCommDbTest059_01 );
	AddTestStepL( new(ELeave) CCommDbTest060_01 );
	AddTestStepL( new(ELeave) CCommDbTest060_02 );
	AddTestStepL( new(ELeave) CCommDbTest061_01 );
	AddTestStepL( new(ELeave) CCommDbTest061_02 );
	AddTestStepL( new(ELeave) CCommDbTest061_03 );
	AddTestStepL( new(ELeave) CCommDbTest061_04 );
	AddTestStepL( new(ELeave) CCommDbTest062_01 );
	AddTestStepL( new(ELeave) CCommDbTest062_02 );
	AddTestStepL( new(ELeave) CCommDbTest062_03 );
	AddTestStepL( new(ELeave) CCommDbTest062_04 );
	AddTestStepL( new(ELeave) CCommDbTest062_05 );
	AddTestStepL( new(ELeave) CCommDbTest063_01 );
	AddTestStepL( new(ELeave) CCommDbTest063_02 );
	AddTestStepL( new(ELeave) CCommDbTest063_03 );
	AddTestStepL( new(ELeave) CCommDbTest063_04 );
	AddTestStepL( new(ELeave) CCommDbTest063_05 );
	AddTestStepL( new(ELeave) CCommDbTest063_06 );
	AddTestStepL( new(ELeave) CCommDbTest063_07 );
	AddTestStepL( new(ELeave) CCommDbTest063_08 );
	AddTestStepL( new(ELeave) CCommDbTest064_01 );
	AddTestStepL( new(ELeave) CCommDbPreCopy );

	// Ensure that the properties get created; normally the RootServer does this
	CommsDat::CMDBSession* ptrCommsdatSession = NULL;
#ifdef SYMBIAN_NON_SEAMLESS_NETWORK_BEARER_MOBILITY
	TRAPD(result, ptrCommsdatSession = CommsDat::CMDBSession::NewL(KCDVersion1_2));
#else
	TRAPD(result, ptrCommsdatSession = CommsDat::CMDBSession::NewL(KCDVersion1_1));
#endif
	if (result == KErrNone)
		{
		result = ptrCommsdatSession->PublishProperties();
		delete ptrCommsdatSession;
		}

}


