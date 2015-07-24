#pragma warning (disable : 4786)

/////////////////////////////////////////////////////////////////////////
// File Name		: IniFile.cpp
// 
// Author			: Ali Awais
//
// Creation Date	: 3/29/2001 1:04:34 PM
//
// Description		:
//
// Modification History:
//    (Date, Modified by, Description)
//
///////////////////////////////////////////////////////////////////////
//

// ===================== USAGE INFO ==============================
/*		
*		CIniFile IniFile;
*
*		if (IniFile.Create("MBase.ini"))
*		{
*			strAddr = IniFile["MBASE_SERVER"]["Address"];
*		}
*		else
*		{
*			// Handle error
*		}
*		
*				-- OR --
*
*		CIniFile IniFile;
		
*		if (IniFile.Create("MBase.ini"))
*		{
*			CIniFile::INI_SECTION Section = IniFile["MBASE_SERVER"];
*			strAddr = Section["Address"];
*			strPort = Section["Port"];
*		}
*		else
*		{
*			// Handle error
*		}
*/
// ===============================================================

#include "StdAfx.h"

#include <fstream>

#include "IniFile.h"



// Reads the ini file
/* --------------------------------------------------*
	Arguments: 
	-  char* pchFileName :	Name of the ini file e.g. 
							"MBase.ini"

	Return : 
	- 	bool : true if the file was successfully read
* --------------------------------------------------*/
bool CIniFile::Create(const char* pchFileName)
{
	char szPath[50];
	GetWindowsDirectory(szPath, 50);
	strcat(szPath, "\\");
	strcat(szPath, pchFileName);
	
	
	std::ifstream from (szPath);
	if (!from) return false;
	
	std::string strSection;
	
	bool bInSection = false;
	while (from)
	{
		std::getline(from, m_strLine);
		if(m_strLine.empty() || m_strLine[0] == '#')
			continue;
		
		short nLast = m_strLine.size()-1;
		if ((m_strLine[0] == '[') && (m_strLine[nLast] == ']'))
		{
			strSection = m_strLine.substr(1, nLast-1);
			bInSection = true;
			continue;
		}
		if (!strSection.empty())
		{
			int nPos = m_strLine.find('=');
			std::string attr = m_strLine.substr(0, nPos);
			std::string val  = m_strLine.substr(nPos+1);
			
			m_IniTree[strSection][attr] = val;
		}
	}

	return true;
}

