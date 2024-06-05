CVE-2023-1678

DriverGenius 9.70.0.346, mydrivers64.sys 9.2.707.1214
http://www.drivergenius.com/

```
__int64 __fastcall sub_11530(__int64 a1, int a2, void *a3, unsigned int a4, unsigned int *a5)
{
    unsigned int v9; //memory to be copied
    __int64 v10; //memory to be mapped
    const void *v11; // points to the mapped memory
    char v12; // for errors
    __int64 v13; 
    _DWORD *v14; // points to the destination buffer (DWORD)
    _DWORD *v15; // points to the source buffer (DWORD copy, also)
    __int64 v16; //
    _WORD *v17; // points to the destination buffer (WORD copy)
    _WORD *v18; // points to the source buffer (WORD copy also)

// here we check if the operation size matches the value.
    if (a2 != 16)
        return 3221225485i64;


// here the size of memory is being calculated for being copied
    v9 = *(_DWORD *)(a1 + 12) * *(_DWORD *)(a1 + 8);

// checks if the buffer size is sufficient 
    if (a4 < v9)
        return 3221225485i64;


// maps the request to the memory space
    v10 = v9;
    v11 = (const void *)MmMapIoSpace(*(_QWORD *)a1, v9, 0i64);

    v12 = 0;


    switch (*(_DWORD *)(a1 + 8))
    {
    case 1: // BYTE 
        qmemcpy(a3, v11, *(unsigned int *)(a1 + 12));
        break;
    case 2: // WORD 
        v16 = *(unsigned int *)(a1 + 12);
        v17 = a3;
        v18 = v11;
        while (v16)
        {
            *v17++ = *v18++;
            --v16;
        }
        break;
    case 4: // DWORD copy
        v13 = *(unsigned int *)(a1 + 12);
        v14 = a3;
        v15 = v11;
        while (v13)
        {
            *v14++ = *v15++;
            --v13;
        }
        break;
    default: // the size was invalid.
        v12 = 1;
        break;
    }

    // unmaps the memory space
    MmUnmapIoSpace(v11, v10);

    if (v12)
        return 3221225485i64;

    // updates
    *a5 = a4;

    // success
    return 0i64;
}

```

```
__int64 __fastcall sub_110D8(__int64 a1, __int64 a2)
{
  _QWORD *v2; // rsi
  __int64 v4; // rdx
  unsigned int v5; // ebx
  unsigned int v6; // eax
  int *v7; // rcx
  int v8; // r8d
  int v9; // edx
  unsigned int v10; // eax
  int v11; // eax
  unsigned __int16 v12; // ax
  unsigned __int8 v13; // al
  unsigned int v14; // ebx
  _DWORD *v15; // r9
  int *v16; // rcx
  int v17; // edx
  int v18; // ebp
  int BusDataByOffset; // eax
  int v20; // eax

  v2 = (_QWORD *)(a2 + 56);
  v4 = *(_QWORD *)(a2 + 184);
  *v2 = 0i64;
  v5 = -1073741822;
  if ( !*(_BYTE *)v4 )
  {
    if ( dword_13110 == -1 )
      goto LABEL_65;
    v20 = dword_13110 + 1;
    goto LABEL_64;
  }
  if ( *(_BYTE *)v4 == 2 )
  {
    if ( dword_13110 == -1 )
      goto LABEL_65;
    v20 = dword_13110 - 1;
LABEL_64:
    dword_13110 = v20;
    goto LABEL_65;
  }
  if ( *(_BYTE *)v4 != 14 )
    goto LABEL_66;
  v6 = *(_DWORD *)(v4 + 24);
  if ( v6 > 0x9C4060D4 )
  {
    switch ( v6 )
    {
      case 0x9C406104:
        v10 = sub_11530(
                *(_QWORD *)(a2 + 24),
                *(_DWORD *)(v4 + 16),
                *(_QWORD *)(a2 + 24),
                *(_DWORD *)(v4 + 8),
                (__int64)v2);
        break;
      case 0x9C406144:
        v18 = *(_DWORD *)(v4 + 8);
        if ( *(_DWORD *)(v4 + 16) != 8 )
          goto LABEL_19;
        BusDataByOffset = HalGetBusDataByOffset(
                            4i64,
                            (unsigned __int8)BYTE1(**(_DWORD **)(a2 + 24)),
                            (32 * (**(_DWORD **)(a2 + 24) & 7)) | (unsigned int)((unsigned __int8)**(_DWORD **)(a2 + 24) >> 3));
        if ( BusDataByOffset )
        {
          if ( v18 == 2 || BusDataByOffset != 2 )
          {
            if ( v18 == BusDataByOffset )
            {
              *(_DWORD *)v2 = v18;
              goto LABEL_65;
            }
            v5 = -536870908;
          }
          else
          {
            v5 = -536870910;
          }
        }
        else
        {
          v5 = -536870911;
        }
        *(_DWORD *)v2 = 0;
        goto LABEL_66;
      case 0x9C40A0C8:
      case 0x9C40A0D8:
      case 0x9C40A0DC:
      case 0x9C40A0E0:
        v16 = *(int **)(a2 + 24);
        v17 = *v16;
        switch ( v6 )
        {
          case 0x9C40A0D8:
            __outbyte(v17, *((_BYTE *)v16 + 4));
            break;
          case 0x9C40A0DC:
            __outword(v17, *((_WORD *)v16 + 2));
            break;
          case 0x9C40A0E0:
            __outdword(v17, v16[1]);
            break;
          default:
            goto LABEL_19;
        }
        goto LABEL_65;
      case 0x9C40A108:
        v10 = sub_115F8(
                *(_QWORD *)(a2 + 24),
                *(_DWORD *)(v4 + 16),
                *(_QWORD *)(a2 + 24),
                *(_DWORD *)(v4 + 8),
                (__int64)v2);
        break;
      case 0x9C40A148:
        v14 = *(_DWORD *)(v4 + 16);
        if ( v14 >= 8 )
        {
          v15 = *(_DWORD **)(a2 + 24);
          *(_DWORD *)v2 = 0;
          v5 = v14 - 8 != (unsigned int)HalSetBusDataByOffset(
                                          4i64,
                                          (unsigned __int8)BYTE1(*v15),
                                          (32 * (*v15 & 7)) | (unsigned int)((unsigned __int8)*v15 >> 3),
                                          v15 + 2,
                                          v15[1],
                                          v14 - 8)
             ? 0xE0000003
             : 0;
          goto LABEL_66;
        }
        goto LABEL_19;
      default:
        goto LABEL_66;
    }
LABEL_59:
    v5 = v10;
    goto LABEL_66;
  }
  switch ( v6 )
  {
    case 0x9C4060D4:
LABEL_15:
      v7 = *(int **)(a2 + 24);
      v8 = *(_DWORD *)(v4 + 16);
      v9 = *v7;
      switch ( v6 )
      {
        case 0x9C4060CC:
          v13 = __inbyte(v9);
          *(_BYTE *)v7 = v13;
          break;
        case 0x9C4060D0:
          v12 = __inword(v9);
          *(_WORD *)v7 = v12;
          break;
        case 0x9C4060D4:
          v11 = __indword(v9);
          *v7 = v11;
          break;
        default:
          *(_DWORD *)v2 = 0;
LABEL_19:
          v5 = -1073741811;
          goto LABEL_66;
      }
      *(_DWORD *)v2 = v8;
LABEL_65:
      v5 = 0;
      break;
    case 0x9C402000:
      **(_DWORD **)(a2 + 24) = 16908293;
      goto LABEL_25;
    case 0x9C402004:
      **(_DWORD **)(a2 + 24) = dword_13110;
LABEL_25:
      *v2 = 4i64;
      goto LABEL_65;
    case 0x9C402084:
      v10 = sub_11494(
              *(_QWORD *)(a2 + 24),
              *(_DWORD *)(v4 + 16),
              *(_QWORD *)(a2 + 24),
              *(_DWORD *)(v4 + 8),
              (__int64)v2);
      goto LABEL_59;
    case 0x9C402088:
      v10 = sub_114C8(
              *(_QWORD *)(a2 + 24),
              *(_DWORD *)(v4 + 16),
              *(_QWORD *)(a2 + 24),
              *(_DWORD *)(v4 + 8),
              (__int64)v2);
      goto LABEL_59;
    case 0x9C40208C:
      v10 = sub_114FC(
              *(_QWORD *)(a2 + 24),
              *(_DWORD *)(v4 + 16),
              *(_QWORD *)(a2 + 24),
              *(_DWORD *)(v4 + 8),
              (__int64)v2);
      goto LABEL_59;
    case 0x9C402090:
      __halt();
    case 0x9C4060C4:
    case 0x9C4060CC:
    case 0x9C4060D0:
      goto LABEL_15;
  }
LABEL_66:
  *(_DWORD *)(a2 + 48) = v5;
  IofCompleteRequest(a2, 0i64);
  return v5;
}

```
