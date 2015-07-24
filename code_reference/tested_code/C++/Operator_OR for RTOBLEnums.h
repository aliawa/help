// Was not able to use because there should be enums for the values obtained after
// oring the original values. Or there should be some mechanism which should take these
// values out of the ored value.
// A nice idea however


// header file


struct CSVRTOBLEnumLookup_Helper
{
	CSVRTOBLEnumLookup_Helper(long x): m_n(x){}
	// implicit conversion operator
	operator RTOBLEnumLookupValues() { return RTOBLEnumLookupValues(m_n);}
	long m_n;
};


//
extern CSVRTOBLEnumLookup_Helper operator| (RTOBLEnumLookupValues l, RTOBLEnumLookupValues r);

// 
extern CSVRTOBLEnumLookup_Helper operator| (CSVRTOBLEnumLookup_Helper l, RTOBLEnumLookupValues r);





// cpp file

CSVRTOBLEnumLookup_Helper operator| (RTOBLEnumLookupValues l, RTOBLEnumLookupValues r)
{
	long x = 1;
	long y = 1;

	// expanded version
	x <<= r-1;
	y <<= l-1;

	long z = y | x ;
	return CSVRTOBLEnumLookup_Helper(z);

	// compact version
	//return CSVRTOBLEnumLookup_Helper( (y << (l-1)) | (x << (r-1)) );

};

// 
CSVRTOBLEnumLookup_Helper operator| (CSVRTOBLEnumLookup_Helper l, RTOBLEnumLookupValues r)		
{
	long x = 1;
	
	// expanded version
	x <<= r-1;
	long z = l | x ;
	return CSVRTOBLEnumLookup_Helper(z);

	// compact version
	//return CSVRTOBLEnumLookup_Helper( l | (x << (r-1)) );
};
