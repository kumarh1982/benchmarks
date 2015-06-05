#include<string>
#include<iostream>
using namespace std;

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
		int tick(int n) { m_counter += n; return m_counter; }
};

void test_virtual_methods (int test_run)
{
	VirtualBase* pObj = static_cast<VirtualBase*>(new VirtualDerived);
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
	
	test_virtual_methods(test_run);
	
	return 0;
}