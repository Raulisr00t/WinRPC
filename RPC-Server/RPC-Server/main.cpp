#define RPC_USE_NATIVE_WCHAR

#include <Windows.h>
#include <iostream>
#include <assert.h>
#include <rpc.h>
#include "calculator_h.h"

#pragma comment(lib,"rpcrt4")

using namespace std;


int main(int argc, char* argv[]) {
	auto status = RpcServerUseProtseqEp((PWSTR)L"ncalrpc", 1,
		(PWSTR)L"ncalrpc:[calc]", nullptr);

	assert(status == RPC_S_OK);

	status = RpcServerRegisterIf(Calculator_v0_0_s_ifspec, nullptr, nullptr);

	assert(status == RPC_S_OK);
	
	cout << "[+] Server PID is: " << GetCurrentProcessId() << endl;

	status = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, FALSE);
	
	return 0;
}

void* midl_user_allocate(size_t size) {
	return malloc(size);
}

void midl_user_free(void* p) {
	free(p);
}

int Add(handle_t handle, int a, int b) {
	cout << "[+] Add Invoked with " << a << " " << b << endl;
	return a+b;
}