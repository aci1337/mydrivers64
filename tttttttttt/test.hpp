#include <iostream>
#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <mutex>
#include <vector>

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")

#pragma comment (lib, "d3d9.lib")

#pragma warning (disable : 26495)
#pragma warning (disable : 4702)

#define PI 3.14159265358979323846f
#define M_PI 3.14159265358979323846264338327950288419716939937510
#include <Windows.h>
#include <iostream>
#include <random>
#include <dwmapi.h>
typedef BOOL(WINAPI* DeviceIoControlFunc)(
    HANDLE hDevice,
    DWORD dwIoControlCode,
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesReturned,
    LPOVERLAPPED lpOverlapped
    );

typedef HANDLE(WINAPI* CreateFileWFunc)(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );
DeviceIoControlFunc deviceIoControl;
CreateFileWFunc createFileW;

int center_x;
int center_y;
int Width;
int Height;

HANDLE hDriver;

std::vector<std::thread> thread_pool;
std::mutex mtx;

const size_t max_threads = std::thread::hardware_concurrency();


DWORD KM_PID;
#pragma pack(push, 1)
struct read {
    uint64_t src;
    int param2;
    uint64_t dst;
    unsigned int param4;
    void* buffer;
    unsigned int* size;
};
#pragma pack(pop)

using DeviceIoControl_t = bool(__stdcall*)(
    HANDLE       hDevice,
    DWORD        dwIoControlCode,
    LPVOID       lpInBuffer,
    DWORD        nInBufferSize,
    LPVOID       lpOutBuffer,
    DWORD        nOutBufferSize,
    LPDWORD      lpBytesReturned,
    LPOVERLAPPED lpOverlapped);
#include <iomanip>


int device_ioctl_hits = 1;




bool second_time = false;


using DeviceIoControl_t = bool(__stdcall*)(
    HANDLE       hDevice,
    DWORD        dwIoControlCode,
    LPVOID       lpInBuffer,
    DWORD        nInBufferSize,
    LPVOID       lpOutBuffer,
    DWORD        nOutBufferSize,
    LPDWORD      lpBytesReturned,
    LPOVERLAPPED lpOverlapped);
DeviceIoControl_t o_device_ioctl = { 0 };

//bool __stdcall hk_device_ioctl(
//    HANDLE       hDevice,
//    DWORD        dwIoControlCode,
//    LPVOID       lpInBuffer,
//    DWORD        nInBufferSize,
//    LPVOID       lpOutBuffer, //PSTORAGE_DEVICE_DESCRIPTOR
//    DWORD        nOutBufferSize,
//    LPDWORD      lpBytesReturned,
//    LPOVERLAPPED lpOverlapped)
//{
//    if (!hDevice || !(dwIoControlCode == IOCTL_STORAGE_QUERY_PROPERTY || dwIoControlCode == SMART_RCV_DRIVE_DATA) || !second_time) {
//        second_time = true;
//        return o_device_ioctl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
//    }
//
//    o_device_ioctl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
//
//    PSTORAGE_DEVICE_DESCRIPTOR p_device_descriptor = ReCa<PSTORAGE_DEVICE_DESCRIPTOR>(lpOutBuffer);
//
//    return true;
//}

//some deleted
