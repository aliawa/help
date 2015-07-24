
/////////////////////////////////////////////////////////////////////////
// File Name		: IniFile.h
// 
// Author			: Ali Awais
//
// Creation Date	: 3/29/2001 12:58:47 PM
//
// Description		:
//
// Modification History:
//    3/29/2001, Awais, Create)
//
///////////////////////////////////////////////////////////////////////
//

#if !defined(AFX_INIFILE_H__E8DA3D02_3C0B_4760_AC6A_22ECDE86554C__INCLUDED_)
#define AFX_INIFILE_H__E8DA3D02_3C0B_4760_AC6A_22ECDE86554C__INCLUDED_

#pragma warning (disable : 4786)

#include <string>
#include <map>


class CIniFile  
{
// LifeCycle
public:
	CIniFile(){};
	virtual ~CIniFile(){};


// Interface
public:
	typedef std::map<std::string,std::string>	INI_SECTION;

	bool Create(const char* pchFileName);
		
	INI_SECTION& operator[](const char* pchSection)
	{
		return m_IniTree[std::string(pchSection)];
	}


//Data
private:
	typedef std::map<std::string, INI_SECTION > INI_TREE;

	INI_TREE	m_IniTree;
	std::string m_strLine;
};

#endif // !defined(AFX_INIFILE_H__E8DA3D02_3C0B_4760_AC6A_22ECDE86554C__INCLUDED_)
