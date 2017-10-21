/*
 * Hitender Prakash
 * References: https://github.com/01org/linux-sgx/tree/master/SampleCode
 * Taken unmodified from SampleEnclave project 
 * if this file is not present, comment out line #144 in makefile where this linker script is being passed to linker 
 */
 
Enclave.so
{
	global:
		g_global_data_sim;
		g_global_data;
		enclave_entry;
		g_peak_heap_used;
	local:
		*;
};
