<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Hay`

<p style='text-align: right;'><a href="../utilities.md#hay">To Index</a></p>

## Description

`Hay` accepts a `Hail` operation and returns the operation via member `Hail`.

<pre><code>   Oper
-> struct { using Flow = Oper; }</code></pre>

## Type Signature

```Haskell
Hay
 :: template<template<template<template<auto...> class...> class...> class...> class...
 -> template<template<template<template<auto...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<template<auto...> class...> class...> class...> class>
struct Hay
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT;
};
```

## Examples

This function injectively maps a `Hail` to a type.
In the following example, We will create an overload set of `fun` using operations `Op_0` and `Op_1`.

```C++
/**** Operations ****/
template<template<template<template<auto...> class...> class...> class...>
struct Op_0 {};

template<template<template<template<auto...> class...> class...> class...>
struct Op_1 {};

/**** fun ****/
constexpr bool fun(Hay<Op_0>) { return false; }

constexpr bool fun(Hay<Op_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Hay<Op_0>{}));
static_assert(fun(Hay<Op_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Hay<Op_0>) -> std::false_type;

constexpr auto gun(Hay<Op_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Hay<Op_0>>()))::value);
static_assert(decltype(gun(std::declval<Hay<Op_1>>()))::value);
```

## Implementation

```C++
template<template<template<template<template<auto...> class...> class...> class...> class Operation>
struct Hay
{
    template<template<template<template<auto...> class...> class...> class...Args>
    using Hail = Operation<Args...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGzSrgAyeAyYAHI%2BAEaYxCCSAKykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXEJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3MDQa9MJDoSDHnCETDkeCoWiwfCoUwvEQAHREyHYa7IAwKBREgkkskUqnEiGk8lMSnU2ksynXADyKTiryyJMBY2IXgc1wAEkwAJ6AkwAdisF2uKuuWJRmKR2NRWo1iNhGLceMJjOZ9PZTLprIZNMtnJt52IwAUQuVqq8GSMkqYdGukIAIjy%2BcQBQIEY7nRbsJClQD5f6Y3Kvr8Ux9Ad8dtcAGJ4Yhja7YVSsR6Yd4ndOpyv/Cs3Xn8%2BoKMt7f7qw2tnH69Ed9sI42oKNWtmmwc2jnm03Cgii8W8gD6Gj9ioVCYhscBPc1Bu7urbO47fYH9sP49tZutUcn04IQdnXEXVnjiYuNb21yoXgYTZ2/zQDDGmFUFJiGuaJUE8N8PwgKVZShOcNBJRZ72uYhMAINZPyoMQlBjRcE2fC5f3/QDgNA8D3wYKCZQROcuAQpCULQ4hPynLwcQsXCk0uA5rgAFUwMZGzTC4ZkcZBZ2tOICAgBhUGvcjKJgtw4KFJd40WRYn3OES8DEiSWmoSDoOolJbxUh9/XUzSX0rX5/gza4hEwX90ALItQVLISuJslNq2fMwITCckvCwP1MWlPlZynH0CBdJlOPs4APy/H8BCIoDrj7a5EooozYJM%2BCmUQgBaWkxnQEAQEw2glEi8K2M4wjgWIjL8VQLLDKovLTMK64SstMqKpYzBar5KzkxuPiBOSycBV0ylJOk2TriwckCDq6BIIGkAVtoAA3MQEVypT8qFJkIHUxYKv27xMA01cZtE8T5v0na1r5DaKK2nbrsOzrju66Mzouq6xFYu6LA4ZZaE4RJeD8DgtFIVBODcaxrGuBRVnWUtzAhHhSAITRIeWABrEBEkkAkNAADjMMwAE56a4RIaeprh5XlaRoY4SReBYCQNA0Uh4cR5GOF4BQQCFwmEch0g4FgGBEBAVYCBSfFyEoNAHjoOIIlYTZVGp/wisCLLkGQa4pAJMxeEwfAiGIPByq4GRBBEMR2CkN35CUNQidIXRXYAdxDFJOB4KGYbhgOxe5fF1evVAqGuI2TbN4ALatymzGuCAPB1%2BhgNxrhFl4GWtGWCAkG1lJdbICgIFr%2BuQGAKQzD4OhgTzShogD6IwmaaUI94AfmGIaVuWibQnJl/HteeAhuQYWhh9l0gsGiLxgCNWhqpHjeQUMYBxHX/AUIcPBdv4gOAKc/FNnxsJgW5xHaDwaIQwnjwsADqc8H5twXg19iCgSUP6I%2BRh35GCJssKgBhnQADU8CYGDnWeG%2BN%2BDu1EOIb2WDfYqHUOvIO%2Bhj4oDRpYfQH9JaQGWKgFIDZOBFTKgGUwlhrBmFFiAp2WAaHnS6LPLILgGDuE8O0PQIQwiDAqMMV2hRMgCEmH4OR6QFEMDmEMeIrs7CCIEL0CYYi8jaNqLoho4x%2BhSPmLI2w5ilF6BmC0DRMitHLExmsDYEgo4cFhsLWOnBU7G1NpIc2ltra5wgLgQgJA/T%2BVLuXWBywECYCYFgeI/CyaSAhASemEJOYaEkGYSQ/hBaJH8PTfQnBeakH5njAk/guD%2BGpvTNm/gKbMxyf4Xx68xYSylgTWB8slbVxVgnDWjdm5F31mwTgzQWC7XlEVJgVovRcHpgSLgVM7YOxIM7PQ%2BCPa4OkPgxQhCA66A7qHJg4cgFeJ8SLXgcdRlJxTmnIJyzgBWzWRshc%2BdUCFziDEiEZgy79NllXGufy65F01k3SFLcWRGFWVwIWNBaDd0lhAPu68x5DwPjiieU8Z4OAPgvRgS8V5r0Rpvbeu995AMPiwY%2Bp8qW5kEdfSW6877IAfgfZ%2BtQA7v0/kPH%2BmxEb/0AfjEBYDMAQMZVAsIoAwV8AQQoZBqD0EH32Tgr2RzZAnP9sQkAHcDAwLYVYShgq%2BF0IYVkDlzCCDoFYRQiwnCHncOdjfWhAjL7OAgK4OxrtJFlE0XoeR9QA2pFUfUJxCxjHdD0bYwxyjvX1H0RY4Nzj7GJtyMmhx6bpGxtcVjDxpcKneJjt0/xryzYIo%2Bas9ZVM86RMdoCuJoLK6JOSakygXiqk1LWfk%2BUiR6YcwhAUopkhXb3KRpwXp0sBkK2VqrROMKJl6wNjM4gLAzYsAULtS2u163YjGFsqJPC9myAOTqn2%2BqiGI10BCUglzrmRzLXcvxHB45q3xNcZOqcd17oPUeuE%2BZfn/OLv5CEIKK5y2GWuhuWs4VFxAPulIJlD301nMeggs5VCdFRei3u/dB4TzxSRye09Z4kr%2BYvZeq8A7Up3mIOl%2BMsBypPqK3g582U305aoe%2BwJeWCH5evQVX9pQir/k7CVwC4jStlUyhVAz4FMCQSgtBfIMG8C1Z7CQurBC3rOSAR9JrjDOqodEK1SMbWpU4FsAaZqOFcLiDwz1/CdE%2Br8H6kREag0FusWGrIEbAslEsSGuNpi00Ro86m8xMbrF5ui3FsLmbS1uOxp4t9FbRZVoA/u64GGCTYabdsiDeNoMJNIEklJwx%2BHcz7UatZEIISJBZpOwWzX5SNK6Tl8Wtg%2BkwfUqQDJiRsns3lILamkgmZcFpmYTp3MITZYebO9txMy22x6ytvrg3lggIyM4SQQA%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/hay/implementation.hpp)
- [Source code](../../../conceptrodon/hay.hpp)
