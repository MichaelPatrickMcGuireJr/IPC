/*
 *   Author:  Michael McGuire
 *  Purpose:  using the boost library to read variables created in a separate processes
 * Language:  c++
 */

// headers
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>


int main(int argc, char* argv[ ])
{
    // when using functions from the boost library this statement allows us to make calls from boost::interprocess name space implicitly
	using namespace boost::interprocess;

	// try-catch block to access shared memory space
	try
	{
		// find the shared memory location
		shared_memory_object shm (open_only, "mem1", read_only);

		// Map shared memory region into this process
		mapped_region region(shm, read_only);

		// place memory space allocated locally into a char* variable
		char* mem = static_cast<char*>(region.get_address());

		// display char* variable on the console
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
	    // print exception
        printf("interprocess exception \"%s\"", e.what());
	}

	// exit main
	return 0;
}
