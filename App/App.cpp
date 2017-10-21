/*
 * Hitender Prakash
 * References: https://github.com/01org/linux-sgx/tree/master/SampleCode
 *
 * Application code: untrusted part and test code
 * Will create and Enclave and call a function inside the Enclave 
 */

#include <stdio.h>
#include "sgx_urts.h"
#include "sgx_error.h" 
#include "sgx_eid.h"  
#include "Enclave_u.h"

#define ENCLAVE_FILENAME "enclave.signed.so"

sgx_enclave_id_t enclave_id = 0;

int initialize_enclave(void)
{
    sgx_launch_token_t token = {0};
    sgx_status_t ret;
    int updated = 0;
    
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &enclave_id, NULL);
    if (ret != SGX_SUCCESS) {
        return -1;
    }
    return 0;
}

int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    int ret=initialize_enclave();
    if(ret < 0){
        printf("\nFaiure in Enclave loading!\n");
        return -1; 
    }
    
    //driver code - To test if Enclave is created and function from enclave can be called
    int secret=0;
    printf("\nIninitialized value of secret: %d\n",secret);
    ecall_random(enclave_id,&secret);
    printf("\nValue of secret set by Enclave: %d\n",secret);
    sgx_destroy_enclave(enclave_id);    
    printf("\nEnclave successfully returned.\n");
    return 0;
}

