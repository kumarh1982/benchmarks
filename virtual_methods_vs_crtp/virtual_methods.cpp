#define TEST_RUN 10000

class VirtualBase
{
	public :
		virtual int tick(int n) = 0;
};

class VirtualDerived : public VirtualBase
{
	private :
		int m_counter;
	public :
		VirtualDerived() : m_counter(0) {}
		int tick(int n) { m_counter += n; }
};

void test_virtual_methods ()
{
	VirtualBase* pObj = static_cast<VirtualBase*>(new VirtualDerived);
	for( int i = 0 ; i < TEST_RUN; i++ )
	{
		for( int j = 0 ; j < TEST_RUN; j++ )
		{
			pObj->tick(j);
		}
	}
}

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
		int tick(int n) { m_counter += n; }
};

void test_crtp ()
{
	CRTPBase<CRTPDerived>* pObj = new CRTPDerived ;
	for( int i = 0 ; i < TEST_RUN; i++ )
	{
		for( int j = 0 ; j < TEST_RUN; j++ )
		{
			pObj->tick(j);
		}
	}
}

#include<string>
using namespace std;

int main (int argc, char** argv)
{
	if( argc < 2 ) return -1;
	
	string arg(argv[1]);
	
	if( arg.compare("virtual") == 0 )
	{
		test_virtual_methods();
	}
	else if ( arg.compare("crtp") == 0 ) 
	{
		test_crtp();
	}
	
	return 0;
}