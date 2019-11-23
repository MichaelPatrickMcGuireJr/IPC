#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


int main(int argc, char* argv[ ])
{

	using namespace boost::interprocess;
	try
	{

		//Open already created shared memory object.
		shared_memory_object shm (open_only, "Hello", read_only);


		//Map the whole shared memory in this process
		mapped_region region(shm, read_only);

		//Check that memory was initialized to 1
		char* mem = static_cast<char*>(region.get_address());

		printf("Found shared memory location \n");
        printf("Shared Memory = ");
		for(std::size_t i = 0; i < region.get_size(); ++i)
		{
			printf("%C",mem[i]);
		}
		 printf("\n\n");
	}
	catch (interprocess_exception& e)
	{

	}

	return 0;
}
