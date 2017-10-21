/*
 * Hitender Prakash
 * References: https://github.com/01org/linux-sgx/tree/master/SampleCode
 *
 * Function: ecall_random
 * input: reference of memory location in untrusted area
 * the function will write a value to that memory and return
 */
 
#include "Enclave_t.h"

void ecall_random(int *num){
	//now communication is bidirectional and enclave can access the value of num as set by untrusted part and write it back
	*num+=5;//increment by 5
}
