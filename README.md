CVE-2023-1678

DriverGenius 9.70.0.346, mydrivers64.sys 9.2.707.1214
http://www.drivergenius.com/

```__int64 __fastcall sub_11530(__int64 a1, int a2, void *a3, unsigned int a4, unsigned int *a5)
{
  unsigned int v9; // eax
  __int64 v10; // r12
  const void *v11; // rax
  char v12; // bp
  __int64 v13; // rcx
  _DWORD *v14; // rdi
  _DWORD *v15; // rsi
  __int64 v16; // rcx
  _WORD *v17; // rdi
  _WORD *v18; // rsi

  if ( a2 != 16 )
    return 3221225485i64;
  v9 = *(_DWORD *)(a1 + 12) * *(_DWORD *)(a1 + 8);
  if ( a4 < v9 )
    return 3221225485i64;
  v10 = v9;
  v11 = (const void *)MmMapIoSpace(*(_QWORD *)a1, v9, 0i64);
  v12 = 0;
  switch ( *(_DWORD *)(a1 + 8) )
  {
    case 1:
      qmemcpy(a3, v11, *(unsigned int *)(a1 + 12));
      break;
    case 2:
      v16 = *(unsigned int *)(a1 + 12);
      v17 = a3;
      v18 = v11;
      while ( v16 )
      {
        *v17++ = *v18++;
        --v16;
      }
      break;
    case 4:
      v13 = *(unsigned int *)(a1 + 12);
      v14 = a3;
      v15 = v11;
      while ( v13 )
      {
        *v14++ = *v15++;
        --v13;
      }
      break;
    default:
      v12 = 1;
      break;
  }
  MmUnmapIoSpace(v11, v10);
  if ( v12 )
    return 3221225485i64;
  *a5 = a4;
  return 0i64;
}```
