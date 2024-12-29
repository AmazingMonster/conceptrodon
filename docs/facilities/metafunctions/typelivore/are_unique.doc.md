<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreUnique`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-unique">To Index</a></p>

## Description

`Typelivore::AreUnique` accepts a list of elements. It returns true if no two elements in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreUnique
 :: typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct AreUnique
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are unique. Then, we will append `int*` and check again.

```C++
static_assert(AreUnique<int, int*, int**, void>::value);
static_assert(! AreUnique<int, int*, int**, void, int*>::value);
```

## Implementation

`AreUnique` is implemented as a special case of `Typelivore::AreOverlapping`:

```C++
template<typename FirstElement, typename...RestElements>
struct AreUnique
{
    static constexpr bool value 
    {
        ! AreOverlapping<FirstElement>
        ::template Mold<RestElements...>
        ::value
    };
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIADs/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYIshvFhbiYwW4CABPZ4AfQIxCYhAUcOwIJBfz2tzcTDSCi89C%2BhyBBEwLDSBhpcIRyMYrEwADpOTiQRNiF4HESSWT6HCrFd8UdbpdiJgAPIANwSBjSaQiwEpB2ptPpTEZ8KRz2YbE57IAkgwFM8HJh0Nh6GxBNiwbirrz%2BQQpTKFUqSaqjCCQLc0l5YrQ8MhbhN0CAQAbMCi8FhBIREUzzZbMNbbfbGAQndgTXikmLLrcy5H0e6HpgWnQQeXYcX6w3yzS6QzMEy40aOVznc2WxW%2BQLlMRUEQALKedADlsmYu3LxZIy3OOwsH3W7y1CJ0WN%2B6i2fzg9gkv4na3ABKmY2WUVgqUIFnbZ1euZhrZt3TVscRjttNzUhVxZHsTWvCZ/wdPNuSuBs3RHMdJ2nI8m1gwdbh2C8TH8DRHlrWhsI0W4AHc6FoCtUDSW4ZWQW8ciAphkAQd55TVSMEBIAgAFo3k2LxCHZWcGyXNi1zhTcoxjNAGHwRoxCE8smQUwdJJAPAFBRWImCUFFUCoJlVLjBMk0cJE0wtH81Ug3McVIaU5UVYhlT9YAcRjeUxC8TAgOUls8MxWgfLQ9Dy3s70nN9NVzIzLNrMdE0gO/TNf2AOKCBg0t0Lc2MWRjF8O1uUdx1QKdaBneFwIINKFELZ08pZQ9xWCls5kcCNpImTBVDSYhbliVBPC3TzMEbCxVPUlEFDZFF5S7FkgO3Xd%2BySE8SwbY9GuBX4LwsbSRuJR9n21Ds5o/Ngvws5KrJzQQMrgysEOK0ryrcJKHGugDbv7Zr5zW9CRJXMSNwraMUAEWScnk5r1vhXz7tBiatJ0vSDIIUGjMTXMU2iyy/xu9LnSAsLHOcqK6pADzvG82FofQxb0FIOHy2JUlyU7eE3ppbNPrzBKLpilK0rurLybjTaQt81rw1uDqaW63r%2BsGymvNGhhxxBmMJqmtgZtO6n6e5FbxcUo3TzxZr8t1dn31ZY1OWq4WywB9VnvXTciqQsqmWq2rcTN8VTbPX4ARDwEJTuU12x53Ucg1M5w9D0OgRBS2327T8ADE8GICD8aA9O7fZSqHe%2By54I9ey5AYPAAEcvKLP6yyl9qBE6%2BW%2BoG8jlZGlDG5bMAwE9ByfRVMm3CznOqvxx2Wzy46rduZ6mWL/Gar7F1MsHdzhpQ1aiz3prrkTzUE8JAAVD4PW%2BU%2BQ%2BT10WjalFtKUNoIEr6u6%2BtiICCA7%2B9l/wQBwFo7nKtgbeVNlibWbk/BQL8CAQAHkPKutd67wm/gAgg/9bh/ywfTDBexsrd0gaeDgqxaCcECLwPwHAtCkFQJwNw1hrCRnWJsHu4IeCkAIJoUhqwADWIBAiSHZBoAAHGYMwABOSRXBAhiNEVwJISRpDkI4JIXgLAJAaA0KQahtD6EcF4AoEAOjuE0NIaQOAsAYCIBAOsAgwYf4UAgGgOkdAEhRDZJwVQoj/BcX8JIW4wBkARikOyMwvAbSEBIImPQ/BBAiDEOwKQMhBCKBUOocxpBdBcFIMRDEaROA8DIRQqhPC6GcFlF4Bx1Tbh6VuD4vxASgkhNuGEswtwIAeDcfQXq5gwRcGWLwMxWhVgQCQK41UvTyCUEme4xIwApBmD4HQGkOdKCxHKbECIrRERFN4Ns5gxBESyliNoZK%2BzSCuKgrKBgtA9lZKwLELwwBiS0FoMY7gvAsAsEMMAcQjzs5XUVJ82hXUbw0kud/eo5SwyxAxMcjwWBynojwJor5pBHL9SUI8X5RgwxGB4asKgBhgAKAAGrvGIrKQ0lz4nCFEOIFJ9L0lqHKTk/QfyUBMMsPoPAsRjGQFWJRRonyuJRnEqYSw1gzD6McsQTGgqICrDsFdZwEBXDTD8LksIERhhVFGLk4o2QBBar0MaxoCwRiJFyaq96Ah%2BhTE8J0PQdrGiOsGHqxYhrbCTHaM6gotq/VWoNTalVrCtgSBKRwShujykGIab4/xgTgmhOER0iAuBol9I4UMrhRLVgIEwEwLAiRlWkAEZIME7JJFgmURoSQZhJA4Q0IEfwkj9CcHUaQTRAz2T%2BC4P4URkiFFBEkLI2tqQ9G8AMUYkx%2BbzFjJseMux1THEzJcagHpHivEcFaCweUSQuJMBlgYFcXBJHsi4CIyJskYnRlyfSxJTLpAsqUGyrJuhln5JJPs6Nsbp0VI4FUmpHp6mNOTaev5bTL3XqIl0rdUyEiwnBGYPNIyLErrmdM5x2HRhQj%2BRergOiaC0DWcYiAmysmHN2ZcmjxzTnnIcJc65uZbn3PKU8l5byPmXJ%2BX8gFtD8A0UcCC8p4LaKQoxdC1RtC4UIsREi7YtDUXos4VizImBcUCbVESvgpKKVUppYwOlshn3JNfbIVlmTaFfs5YSqVVheVwqVcKtIorODirRpKnlFhZUzvlYq%2BAKr6hqr8BqmSZqdUyRDUsI1mQTW5ADdq9ICXLVeuta60L9qmh%2Bqiz0MLHrYs%2BrmE6/IKXSueoqJlwZawNiRtq6ogD8bOCJqaYEgj57YMiM6VmogOaBnoYLaQItJbRjltUd23tl6G1JECJIpRYJG3NvHXGrJs7bDzow0u%2BAK77Hrtw4h%2BZni2CcH3c0lgCh5QRnlBe9kHYJi3uzbEx9ZnGUWdSfId9NmdAgDBHkgpf7O0xrKetypa7angYu1dm7d2HsegQ9ugbYIhuLssRMo7OHZmY9GNdlUM0L0onhyiVQASVlkYSBRqjtD6MPM4bTxjFyMWscEOxh5QnMDPNeWIXjGL%2BP4uU98oF70xNZIk9U7YnCZOwv5QppTKKFVqd4BpnFtIdOErRySpgZLKWYGpbSjFT73sSEs2k777K/v2eML5vlArgt0PczkT5OxJKOZlXKhICqsCuYKzllwkXkt6F1dV0N5q0s5HyxanIxWbW%2B/dXlwPtrsvx/mBl0PQaBj5cqzHqNdW2G56a6D/RrXSeBMu9drccOrYTF63egbgzhnDdG6Wyg0apsgCkeyMEYJAhyPHdo7vKRRFreL4YzbpjhuVsCDWxRSRtGiMkDIrg4izCpFUWCIvM7OCN8XdGiJI%2Bt9j%2B26sRyWRnCSCAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/are_unique/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/typelivore/are_unique.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/are_unique.test.hpp)
