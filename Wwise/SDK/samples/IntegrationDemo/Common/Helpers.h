/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided 
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

  Version: v2017.1.3  Build: 6377
  Copyright (c) 2006-2017 Audiokinetic Inc.
*******************************************************************************/

// IntegrationDemo.h
/// \file 
/// Declares various helpers for the Integration Demo

#pragma once
#include <string>
#include <AK/SoundEngine/Common/AkTypes.h>

namespace IntegrationDemoHelpers
{
	/// Returns the number of elements in an array
	template <class T, size_t N> AkForceInline size_t AK_ARRAYSIZE(T(&)[N])
	{
		return N;
	}

	void WordWrapString( std::string& io_strWrapped, const size_t in_nMaxWidth );
	std::string WordWrapString( const char* in_szOriginal, const size_t in_nMaxWidth );
}
