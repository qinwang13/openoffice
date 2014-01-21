/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_svtools.hxx"
#include <svtools/sychconv.hxx>
#include <vcl/outdev.hxx>

sal_Bool SymCharConverter::Convert( Font& rFont, UniString& rString, OutputDevice* pDev )
{
    // hibyte 0 = exact matching
    //		  1 = little differences, 
    //		  2 = the converted character does not look like the original but got the same meaning
    //		  3 = the destination does not match looking and meaning of the original

	static sal_uInt16 __READONLY_DATA aWingdingsToStarBatsTable[ 256 - 32 ] =
	{
		0x0020, 0x0238, 0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0174,	0x02BA,	0x017B,	0x017C,	0x037C,	0x037C,	0x037C,	0x037C,
		0x0000, 0x0000, 0x0372,	0x0272,	0x0372,	0x0000,	0x0000,	0x0374,	0x0279,	0x0000,	0x027A,	0x0000,	0x0178,	0x0278,	0x0000,	0x0137,
		0x027E, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x017D,	0x0000,	0x0000,	0x0000,	0x0021,	0x03AC,	0x00AD,	0x0000,	0x0000,	0x0000,
		0x0000, 0x0000, 0x01C0,	0x0000,	0x0000,	0x0286,	0x0286,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,
		0x0000, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0022,	0x0023,	0x0024,	0x0025,
		0x0026, 0x0027, 0x0028,	0x0029,	0x002A,	0x002B,	0x002C,	0x002D,	0x0133,	0x0000,	0x0000,	0x0000,	0x0000,	0x0193,	0x0194,	0x0000,
		0x0067, 0x0068, 0x0069,	0x006A,	0x006B,	0x006C,	0x006D,	0x006E,	0x006F,	0x0070,	0x0071,	0x005C,	0x005D,	0x005E,	0x005F,	0x0060,
		0x0061, 0x0062, 0x0063,	0x0064,	0x0065,	0x0066,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x01A5,	0x0095,
		0x0000, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x002E,	0x0024,	0x0125,	0x0000,	0x0000,	0x0000,	0x014B,	0x024D,	0x014E,	0x014A,
		0x0000, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,
		0x0000, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,
		0x0000, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x002F,	0x0000,	0x0000,	0x0000,	0x0035,	0x0000,	0x0000,	0x0000,
		0x0030, 0x0000, 0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0031,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x01B1,
		0x01AF, 0x01B2, 0x01B0,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0150,	0x0032,	0x0033,	0x0034,	0x01C8
	};

	static sal_uInt16 __READONLY_DATA aMonotypeSortsToStarBatsTable[ 256 - 32 ]=
	{
		0x0020,	0x00cb,	0x00cb,	0x00cb,	0x00cb,	0x0074,	0x00ba,	0x0021,	0x00cc,	0x007b,	0x0036,	0x007d,	0x007e,	0x0037,	0x0038,	0x0038,
		0x0039,	0x0038,	0x0038,	0x0039,	0x003a,	0x004f,	0x0050,	0x004f,	0x0050,	0x0051,	0x0052,	0x0053,	0x0054,	0x0086,	0x0086,	0x0086,
		0x0052,	0x00cd,	0x0044,	0x0045,	0x0046,	0x0047,	0x0041,	0x0041,	0x0058,	0x0057,	0x0075,	0x0055,	0x0056,	0x0057,	0x0058,	0x0059,
		0x005a,	0x004b,	0x004b,	0x0048,	0x0049,	0x004a,	0x004b,	0x004c,	0x004d,	0x004e,	0x004e,	0x004b,	0x004b,	0x00ce,	0x00ce,	0x00ce,
		0x00ce,	0x00ce,	0x00ce,	0x00ce,	0x00cf,	0x00cf,	0x00cf,	0x00cf,	0x00cf,	0x00cf,	0x00b9,	0x00b9,	0x003b,	0x003c,	0x003d,	0x003e,
		0x003f,	0x003e,	0x0040,	0x00c5,	0x00c4,	0x002b,	0x002c,	0x00d0,	0x00d1,	0x00d1,	0x00d1,	0x0091,	0x0092,	0x0093,	0x0094,	0x0000,
		0x00d2,	0x00d3,	0x00d2,	0x00d3,	0x00d2,	0x00d3,	0x00d2,	0x00d3,	0x00d2,	0x00d3,	0x00d2,	0x00d3,	0x00d2,	0x00d3,	0x0000,	0x0000,
		0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,	0x0000,
		0x0000,	0x00d4,	0x00d4,	0x00d4,	0x00d6,	0x00d6,	0x00d4,	0x00d4,	0x00d5,	0x002a,	0x00d6,	0x00d7,	0x0068,	0x0069,	0x006a,	0x006b,
		0x006c,	0x006d,	0x006e,	0x006f,	0x0070,	0x0071,	0x005d,	0x005e,	0x005f,	0x0060,	0x0061,	0x0062,	0x0063,	0x0064,	0x0065,	0x0066,
		0x0068,	0x0069,	0x006a,	0x006b,	0x006c,	0x006d,	0x006e,	0x006f,	0x0070,	0x0071,	0x005d,	0x005e,	0x005f,	0x0060,	0x0061,	0x0062,
		0x0063,	0x0064,	0x0065,	0x0066,	0x0030,	0x0031,	0x00d8,	0x00d9,	0x00da,	0x00bc,	0x00db,	0x00bc,	0x00bc,	0x00bc,	0x00bc,	0x0031,
		0x0031,	0x0031,	0x002f,	0x002f,	0x002f,	0x00be,	0x00be,	0x0031,	0x0031,	0x00af,	0x00af,	0x00af,	0x00af,	0x00af,	0x00af,	0x00af,
		0x0000,	0x00af,	0x0035,	0x00dc,	0x00da,	0x00dc,	0x00db,	0x00da,	0x00dc,	0x00db,	0x00dc,	0x00dc,	0x00dc,	0x00dc,	0x00af,	0x0000
	};

	const sal_uInt16* pTransTable = NULL;

	sal_Bool bIsAvailable = ( pDev ) ? pDev->IsFontAvailable( rFont.GetName() ) : sal_False;
	if ( !bIsAvailable )
	{
		if ( rFont.GetName().CompareToAscii( RTL_CONSTASCII_STRINGPARAM( "Wingdings" ) ) == COMPARE_EQUAL )
			pTransTable = &aWingdingsToStarBatsTable[ 0 ];
		else if ( rFont.GetName().CompareToAscii( RTL_CONSTASCII_STRINGPARAM( "Monotype Sorts" ) ) == COMPARE_EQUAL )
			pTransTable = &aMonotypeSortsToStarBatsTable[ 0 ];
	}
	if ( pTransTable )
	{
		sal_Unicode c;
		for ( sal_uInt16 i = rString.Len(); i--; )
		{
			c = rString.GetChar( i );
			c -= 32;
			c = ( ((sal_uInt16)c) >= 224 ) ? 0 : (sal_Unicode) pTransTable[ c ];
			if ( !c )				// if character is out of range or not matching
				c = 0xA5;			// we will default a StarBats-Bullet
			rString.SetChar( i, c );
		}
		rFont.SetCharSet( RTL_TEXTENCODING_SYMBOL );
		rFont.SetName( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "StarBats" ) ) );
		return sal_True;
	}
	else return sal_False;
};