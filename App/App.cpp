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
//======================================================================
// this Error handling code is taken and modified from:
// https://github.com/01org/linux-sgx/tree/master/SampleCode/Cxx11SGXDemo
typedef struct _sgx_errlist_t {
    sgx_status_t err;
    const char *msg;
    const char *sug; /* Suggestion */
} sgx_errlist_t;

/* Error code returned by sgx_create_enclave */
static sgx_errlist_t sgx_errlist[] = {
    {
        SGX_ERROR_UNEXPECTED,
        "SGX_ERROR_UNEXPECTED: Unexpected error occurred.",
        NULL
    },
    {
        SGX_ERROR_INVALID_PARAMETER,
        "SGX_ERROR_INVALID_PARAMETER: Invalid parameter.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_MEMORY,
        "SGX_ERROR_OUT_OF_MEMORY: Out of memory.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_LOST,
        "SGX_ERROR_ENCLAVE_LOST: Power transition occurred.",
        "Please refer to the sample \"PowerTransition\" for details."
    },
    {
        SGX_ERROR_INVALID_ENCLAVE,
        "Invalid enclave image.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ENCLAVE_ID,
        "SGX_ERROR_INVALID_ENCLAVE: Invalid enclave identification.",
        NULL
    },
    {
        SGX_ERROR_INVALID_SIGNATURE,
        "SGX_ERROR_INVALID_SIGNATURE: Invalid enclave signature.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_EPC,
        "SGX_ERROR_OUT_OF_EPC: Out of EPC memory.",
        NULL
    },
    {
        SGX_ERROR_NO_DEVICE,
        "SGX_ERROR_NO_DEVICE: Invalid SGX device.",
        "Please make sure SGX module is enabled in the BIOS, and install SGX driver afterwards."
    },
    {
        SGX_ERROR_MEMORY_MAP_CONFLICT,
        "SGX_ERROR_MEMORY_MAP_CONFLICT: Memory map conflicted.",
        NULL
    },
    {
        SGX_ERROR_INVALID_METADATA,
        "SGX_ERROR_INVALID_METADATA: Invalid enclave metadata.",
        NULL
    },
    {
        SGX_ERROR_DEVICE_BUSY,
        "SGX_ERROR_DEVICE_BUSY: SGX device was busy.",
        NULL
    },
    {
        SGX_ERROR_INVALID_VERSION,
        "SGX_ERROR_INVALID_VERSION: Enclave version was invalid.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ATTRIBUTE,
        "SGX_ERROR_INVALID_ATTRIBUTE: Enclave was not authorized.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_FILE_ACCESS,
        "SGX_ERROR_ENCLAVE_FILE_ACCESS: Can't open enclave file.",
        NULL
    },
    {
        SGX_ERROR_NDEBUG_ENCLAVE,
        "SGX_ERROR_NDEBUG_ENCLAVE: The enclave is signed as product enclave, and can not be created as debuggable enclave.",
        NULL
    },
};

//Check error conditions for loading enclave 
//modified to give more detailed information
void print_error_message(sgx_status_t ret)
{
    size_t ttl = sizeof sgx_errlist/sizeof sgx_errlist[0];
	size_t idx = 0;
    for (idx = 0; idx < ttl; idx++) {
        if(ret == sgx_errlist[idx].err) {
			printf("\nError (%d): %s\n", ret, sgx_errlist[idx].msg);
            if(NULL != sgx_errlist[idx].sug)
            {
				printf("Info: %s\n", sgx_errlist[idx].sug);
			}
            break;
        }
    }
    
    if (idx == ttl){
		printf("Error: Unexpected error occurred.\n");
	}
}
//Error handling code ends
//======================================================================
sgx_status_t initialize_enclave(void)
{
    sgx_launch_token_t token = {0};
    sgx_status_t ret;
    int updated = 0;
    
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &enclave_id, NULL);
    if (ret != SGX_SUCCESS) {
        return ret;
    }
    return SGX_SUCCESS;
}

int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    sgx_status_t ret=initialize_enclave();
    if(ret != SGX_SUCCESS){
        print_error_message(ret);
        return -1; 
    }
    
    //driver code - To test if Enclave is created and function from enclave can be called
    int secret=6;
    printf("\nIninitialized value of secret: %d\n",secret);
    ecall_random(enclave_id,&secret);//call to enclave function
    printf("\nValue of secret after increment by Enclave function : %d\n",secret);
    sgx_destroy_enclave(enclave_id);    
    printf("\nEnclave successfully returned.\n");
    return 0;
}

