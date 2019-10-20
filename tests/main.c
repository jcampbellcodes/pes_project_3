#include "uCUnit.h"
#include "memory_tests.h"
#include "mem_types.h"
#include "logger.h"
#define ALLOC_SIZE 16

int main()
{
#ifdef DEBUG
	log_enable();
#endif

	{
	    UCUNIT_TestcaseBegin("allocate words");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
	    for(int i = 0; i < ALLOC_SIZE; i++)
	    {
	    	UCUNIT_CheckIsEqual(((uint8_t*)ptr)[i], 0x0);
	    }

	    UCUNIT_CheckIsNotNull(ptr);
	    UCUNIT_TestcaseEnd();

	    // clean up
	    free_words(ptr);
	}

	{
	    UCUNIT_TestcaseBegin("allocate words fail");
	    uint32_t* ptr = allocate_words(0);
	    UCUNIT_CheckIsNull(ptr);
	    UCUNIT_TestcaseEnd();

	    // clean up
	   	free_words(ptr);
	}

	{
		UCUNIT_TestcaseBegin("get address");
		uint32_t* ptr = allocate_words(ALLOC_SIZE);
		uint32_t * addr = get_address(ptr, 8);
		UCUNIT_CheckIsEqual(addr, (ptr + 8));
		UCUNIT_TestcaseEnd();

		// clean up
		free_words(ptr);
	}

	{
	    UCUNIT_TestcaseBegin("free words");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
		UCUNIT_CheckIsEqual(free_words(ptr), SUCCESS);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("free words null");
		UCUNIT_CheckIsEqual(free_words(NULL), FAILED);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("free words garbage");
		UCUNIT_CheckIsEqual(free_words((uint32_t*)0xDEADBEEF), FAILED);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("write pattern");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
		const int8_t seed = 2;
		mem_status status = write_pattern(ptr, 16, seed);
		UCUNIT_CheckIsEqual(status, SUCCESS);

		// clean up
		free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("display memory");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
		uint8_t * disp = display_memory(ptr, 16);
		UCUNIT_CheckIsNotNull(disp);
		// clean up
	    free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("verify pattern");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
	    const int8_t seed = 2;

	    mem_status status = write_pattern(ptr, 16, seed);
	    UCUNIT_CheckIsEqual(status, SUCCESS);

	    uint32_t * nonMatchingValues = verify_pattern(ptr, 16, seed);
	    UCUNIT_CheckIsNull(nonMatchingValues);

	    // clean up
	    free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("write memory");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
	    for(int i = 0; i < ALLOC_SIZE/sizeof(uint32_t); i++)
	    {
			ptr[i] = 0xABABABAB;
		}

		uint8_t* ptrBytes = (uint8_t*)ptr;

		uint32_t offset = 2;
	    uint8_t valToWrite = 0xEE;
	    mem_status status = write_memory(ptr+offset, valToWrite);

	    for(int i = 0; i < ALLOC_SIZE; i++)
	    {
	    	UCUNIT_CheckIsEqual(ptrBytes[i], i == 8 ? 0xEE : 0xAB);
	    }

	    UCUNIT_CheckIsEqual(status, SUCCESS);

	    // clean up
	    free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("write memory fail");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
	    for(int i = 0; i < ALLOC_SIZE/sizeof(uint32_t); i++)
	    {
	    	ptr[i] = 0xABABABAB;
	    }

	    uint8_t* ptrBytes = (uint8_t*)ptr;

	    uint32_t offset = 200;
	    uint16_t valToWrite = 0xFFEE;
	    mem_status status = write_memory(ptr + offset, valToWrite);
	    UCUNIT_CheckIsEqual(status, FAILED);

	    for(int i = 0; i < ALLOC_SIZE; i++)
	    {
	    	UCUNIT_CheckIsEqual(ptrBytes[i], 0xAB);
	    }

	    // clean up
	    free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("invert block");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);
	    for(int i = 0; i < ALLOC_SIZE/sizeof(uint32_t); i++)
	    {
	    	ptr[i] = 0xABABABAB;
	    }

		uint8_t* ptrBytes = (uint8_t*)ptr;

	    uint32_t offset = 1;
	    mem_status status = invert_block(ptr + offset, 4);

	    for(int i = 0; i < ALLOC_SIZE; i++)
	    {
			UCUNIT_CheckIsEqual(ptrBytes[i], (i >= 4 && i < 8 ) ? 0xAB^0xFF : 0xAB);
	    }

	    UCUNIT_CheckIsEqual(status, SUCCESS);

	    // clean up
	    free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	{
	    UCUNIT_TestcaseBegin("invert block fail");
	    uint32_t* ptr = allocate_words(ALLOC_SIZE);

	    for(int i = 0; i < ALLOC_SIZE/sizeof(uint32_t); i++)
	    {
			ptr[i] = 0xABABABAB;
	    }

		uint8_t* ptrBytes = (uint8_t*)ptr;

	    uint32_t offset = 200;
	    mem_status status = invert_block(ptr + offset, 4);

	    for(int i = 0; i < ALLOC_SIZE; i++)
	    {
			UCUNIT_CheckIsEqual(ptrBytes[i], 0xAB);
	    }

	    UCUNIT_CheckIsEqual(status, FAILED);

	    // clean up
	    free_words(ptr);
	    UCUNIT_TestcaseEnd();
	}

	return 0;
}
