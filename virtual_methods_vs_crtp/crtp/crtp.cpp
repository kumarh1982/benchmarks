#include<string>
#include<iostream>
using namespace std;

template <typename T>
class CRTPBase
{
	public:
		int tick(int n) 
		{
			return impl().tick(n);
		}
	private:
		T& impl() { return *static_cast<T*>(this); }
};

class CRTPDerived : public CRTPBase<CRTPDerived> 
{
	private :
		int m_counter;
	public:
		CRTPDerived() : m_counter(0) {}
		int tick(int n) { m_counter += n; return m_counter; }
};

void test_crtp (int test_run)
{
	CRTPBase<CRTPDerived>* pObj = new CRTPDerived ;
	for( int i = 0 ; i < test_run; i++ )
	{
		for( int j = 0 ; j < test_run; j++ )
		{
			pObj->tick(j);
			//cout << pObj->tick(j) << endl; 
		}
	}
}

int main (int argc, char** argv)
{
	if( argc < 2 ) return -1;
	
	int test_run = stoi ( string(argv[1]) );
	
	test_crtp(test_run);
	
	return 0;
}