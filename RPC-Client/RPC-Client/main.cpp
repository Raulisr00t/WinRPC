#define RPC_USE_NATIVE_WCHAR
#include <windows.h>
#include <rpc.h>
#include "..\..\RPC-Server\RPC-Server\calculator_h.h"
#include <iostream>
#include <assert.h>

#pragma comment(lib,"rpcrt4")

using namespace std;

int main(int argc, char* argv[]) {

    int result;

    RPC_WSTR binding;
    RPC_BINDING_HANDLE h;

    auto status = RpcStringBindingCompose(nullptr, (PWSTR)L"ncalrpc",
        nullptr, (PWSTR)L"ncalrpc:[calc]", nullptr, &binding);

    assert(status == RPC_S_OK);

    status = RpcBindingFromStringBinding(binding, &h);

    assert(status == RPC_S_OK);

    result = Add(h, 3, 5);

    cout << "[+] Result is: " << result << endl;

    RpcBindingFree(&h);  

    return 0;
}

void* midl_user_allocate(size_t size) {
    return malloc(size);
}

void midl_user_free(void* p) {
    free(p);
}
