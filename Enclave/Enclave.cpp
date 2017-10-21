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
	*num=5;
}
