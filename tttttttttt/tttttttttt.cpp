#include "test.hpp"


#define IOCTL_READ_DATA 0x9C406104






void ReadMemoryFromKernels(HANDLE hDriver, uint64_t srcAddress, void* buffer, size_t size)
{
    if (srcAddress == 0 || buffer == nullptr || size == 0) {
        std::cerr << "Invalid parameters" << std::endl;
        return;
    }

    read request;
    request.src = srcAddress;
    request.param2 = 16;
    request.dst = reinterpret_cast<uint64_t>(buffer);
    request.param4 = static_cast<unsigned int>(size);
    request.buffer = buffer;
    request.size = reinterpret_cast<unsigned int*>(&size);

    DWORD bytesReturned;
    BOOL status = DeviceIoControl(
        hDriver,
        IOCTL_READ_DATA,
        &request,
        sizeof(read),
        buffer,
        static_cast<DWORD>(size),
        &bytesReturned,
        nullptr
    );

    if (!status) {
        std::cerr << "DeviceIoControl failed: " << GetLastError() << std::endl;
    }
    else {
        std::cout << "DeviceIoControl succeeded. Bytes returned: " << bytesReturned << std::endl;
    }
}

template <typename T>
T Rpm(HANDLE hDriver, uint64_t srcAddress)
{
    T buffer;
    ReadMemoryFromKernels(hDriver, srcAddress, &buffer, sizeof(T));
    return buffer;
}


DWORD proc_id(LPCTSTR process_name)
{
    PROCESSENTRY32 pt{};
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &pt))
    {
        do {
            if (!lstrcmpi(pt.szExeFile, process_name))
            {
                CloseHandle(hsnap);
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }
    CloseHandle(hsnap);
    return 0;
}

uintptr_t base_addy(DWORD processId, const std::wstring& moduleName)
{
    uintptr_t baseAddress = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 moduleEntry;
        moduleEntry.dwSize = sizeof(moduleEntry);
        if (Module32First(snapshot, &moduleEntry)) {
            do {
                if (moduleName == moduleEntry.szModule) {
                    baseAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
                    break;
                }
            } while (Module32Next(snapshot, &moduleEntry));
        }
        CloseHandle(snapshot);
    }
    return baseAddress;
}

uintptr_t base_address;
int main()
{
    HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
    if (hKernel32 == NULL) {
        std::cout << "Error.";

    }
    deviceIoControl = (DeviceIoControlFunc)GetProcAddress(hKernel32, "DeviceIoControl");
    if (deviceIoControl == NULL) {
        FreeLibrary(hKernel32);
    }

    createFileW = (CreateFileWFunc)GetProcAddress(hKernel32, "CreateFileW");
    if (createFileW == NULL) {
        FreeLibrary(hKernel32);
    }

    HANDLE dev = createFileW((L"\\\\.\\\MyDrivers0_0_1"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (dev == INVALID_HANDLE_VALUE) {
        return 1;
    }


    __int64 a1 = 0;

    KM_PID = proc_id(L"Notepad.exe");
    base_address; //your way to get the base address

   // std::cout << base_address;
    int value = Rpm<uintptr_t>(dev, base_address + 0x12BA7050);
    std::cout << "Read: " << value << std::endl;

    CloseHandle(dev);
    return 0;
}

