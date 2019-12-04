/*
 *   Author:  Michael McGuire
 *  Purpose:  using the boost library to create and write value to shared memory
 * Language:  c++
 */

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include<windows.h>


int main(int argc, char* argv[ ])
{
    // statement to use functions within the interprocess family within the boost library implicitly
    using namespace boost::interprocess;


    try
	{
	    // remove any other objects in shared memory having the same name
		struct shm_remove
        {
            shm_remove() { shared_memory_object::remove("mem1"); }
            ~shm_remove(){ shared_memory_object::remove("mem1"); }
        } remover;

    	// create and name a space in shared memory
    	shared_memory_object sharedmem1 (create_only, "mem1", read_write);

    	// allocate the size of the shared memory in bytes
    	sharedmem1.truncate (100);

   		// map this region of shared memory to a local variable
   		mapped_region region(sharedmem1, read_write);

    	// place a char* into the shared memory
    	std::strcpy(static_cast<char* >(region.get_address()), "Hello World!");

    	// indicate on console that the memory region has been written to
		printf("Writing \"Hello World!\" to shared memory location \n");
		// pause execution - the region of shared memory will be destroyed when thread is closed
		Sleep(36000);
    }
	catch (interprocess_exception& e)
	{
	    // print exception
		printf("interprocess exception \"%s\"", e.what());
    }

    // indicate end of main thread and that the location in memory will be over-written
    printf("removing shared memory location \n");

    // exit main
    return 0;
}






/*
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib> //std::system
#include <sstream>
int main (int argc, char *argv[])
{
	using namespace boost::interprocess;
	if(argc == 1)
	{ //Parent process
		//Remove shared memory on construction and destruction
		struct shm_remove
		{
			shm_remove() { shared_memory_object::remove("MySharedMemory"); }
			~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
		} remover;
		//Create a managed shared memory segment
		managed_shared_memory segment(create_only, "MySharedMemory", 65536);
		//Allocate a portion of the segment (raw memory)
		managed_shared_memory::size_type free_memory = segment.get_free_memory();
		void * shptr = segment.allocate(1024//bytes to allocate);
		//Check invariant
		if(free_memory <= segment.get_free_memory())
		return 1;
		//An handle from the base address can identify any byte of the shared
		//memory segment even if it is mapped in different base addresses
		managed_shared_memory::handle_t handle = segment.get_handle_from_address(shptr);
		std::stringstream s;
		s << argv[0] << " " << handle;
		s << std::ends;
		//Launch child process
		if(0 != std::system(s.str().c_str()))
			return 1;
		//Check memory has been freed
		if(free_memory != segment.get_free_memory())
			return 1;
	}
	else
	{
		//Open managed segment
		managed_shared_memory segment(open_only, "MySharedMemory");
		//An handle from the base address can identify any byte of the shared
		//memory segment even if it is mapped in different base addresses
		managed_shared_memory::handle_t handle = 0;
		//Obtain handle value
		std::stringstream s; s << argv[1]; s >> handle;
		//Get buffer local address from handle
		void *msg = segment.get_address_from_handle(handle);


		//Deallocate previously allocated memory
		segment.deallocate(msg);
	}
	return 0;

}
*/


