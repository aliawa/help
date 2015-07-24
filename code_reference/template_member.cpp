
#include <iostream>

using namespace std;

// template member
// use of typeid
// pointer to function


class VarData
{
	public:
        // A string will be deleted by the destructor
		VarData(char* d):m_data((void*)d),m_type(typeid(d)),m_fdel(&VarData::delStr)
        {
        }
        
        // A const string will be not be deleted by the destructor
		VarData(const char* d):m_data((void*)d),m_type(typeid(d)),m_fdel(NULL)
        {
        }
       
        // An int is not deleted by the destructor
		VarData(int d):m_data((void*)d),m_type(typeid(d)),m_fdel(NULL)
        { 
        }

        // return the stoted data correctly casted to the requested type
        // if the original type of the data was not what is being requested
        // then return zero.
        template<class T> T getData( T type)
        {

            if (typeid(type) == m_type)
                return reinterpret_cast<T>(m_data);
            else
                return 0;
        }

        // This function knows how to delete a string
        void delStr()
        {
            cout << "deleting string" << endl;
            delete[] (char*)m_data;
        }

        ~VarData(){
            if (m_fdel) {
                (this->*m_fdel)();
            }
        }

		
    private:
        const type_info& m_type;
        void * m_data;
        void (VarData::*m_fdel)();
};



int main()
{
	VarData intData(1);

    char* x = new char[strlen("allocated string")+1];
    strcpy (x, "allocated string");
	VarData strData(x );

    VarData conststrData("const string");

    int d = intData.getData(d);
    char* p = strData.getData(p);
    const char* c = conststrData.getData(c);

	cout << d << endl;
	cout << p << endl;
    cout << c << endl;
}
