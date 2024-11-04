<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::FoldLeft`

## Description

`Typelivore::FoldLeft` accepts a list of elements.
It produces a function that accepts an initiator and an operation.
The function left-folds the list with the operation and the initiator.
<pre><code>   E<sub>0</sub>, E<sub>1</sub>..., E<sub>n</sub>
->&nbsp;Initiator
->&nbsp;Operation
->&nbsp;Operation&lt;...
   Operation&lt;
   Operation&lt;
       Initiator, E<sub>0</sub>
   &gt;, E<sub>1</sub>
   &gt;
   ..., E<sub>n</sub>&gt::type</code></pre>

## Type Signature

```Haskell
FoldLeft ::   typename...
           -> typename...
           -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct FoldLeft
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;
        
        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

## Example

We will left-fold 2, 3, 4 and 3 using a power operation.
The process can be described as follows:

```C++
   ((2^3)^4)^2
-> ((8)^4)^2
-> (4096)^2
-> 16777216
```

```C++
consteval int power(int a, int b)
{
    int c {a};
    for(;b!=1;b--)
    { c*=a; }
    return c;
}

template<typename A, typename B>
struct Power
{
    using type
    = std::integral_constant<int, power(A::value, B::value)>;
};

template<typename...Args>
using Power_t = Power<Args...>::type;

template<typename...Args>
using Metafunction 
= FoldLeft<
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 2>
  >::Mold<Args...>;

using SupposedResult
= std::integral_constant<int, 16777216>;

using Result = Metafunction<std::integral_constant<int, 2>>
::Road<Power_t>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::FoldLeft` relies on recursion to reduce the number of arguments.
Each recursive case has two functionalities:

1. left-fold several arguments;
2. use the result from 1 as an initiator and perform recursion to fold the rest.

The function always ends in base cases, which fold the last couple of elements to produce a result.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct FoldLeft {};

template<typename Element>
struct FoldLeft<Element>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<Initiator, Element>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename First, typename Second>
struct FoldLeft<First, Second>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = Operation<
              Operation<
                Initiator, First
              >, Second
              >;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct FoldLeft<First, Second, Others...>
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type 
            = FoldLeft<Others...>
            ::template Mold<
                Operation<
                Operation<
                    Initiator, First
                >, Second
                >
            >::template Road<Operation>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElwAbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgAdPfY9GyCCifYJhoAgpPEXg4A1AAxTzoUKYKgEf4mADsVmhABETlYvh9PnsDkdMCczpdrmx/o99owCG9UT8/pDgbRQeCSadCc86e8UbDUf92f90YcmMdThcrsx8QBJBjZHkkUlfDn/ckA5TEVBEACyILZHJhyM%2B0ulXMx2N1PKxfNxgru9ze/2QBgUCn%2BAHkrsQeTlJVrtezZZD4ZhWnQ1e6Nf73RyvFkjJzcVCpcHpSd4fbHc6BNiRWKiGQCU9iaTApqYzDEbnUUGdftubyzmW9caBTd7rcLVamDb659gMRMESXq6Y6GIsB/gAlVBMdBQwLx72%2B2jYtsdrsEBT1t4gED8o159UIpHF6Psg0V9em1vtzuM16BZlu9l98Mq6nj%2BPyxWoe/oWenhdL82XncswuaqiB5Gjitb4oCeDEJMpARmBmD/EImBoAw76/l8npAiCYIQtiEFQQQMGIchqFXoGe6clWhr6iaNz/KmjjisQPYchhz7Kqq5Fkde2rAfqlGHjRbDLpelrWraDoJEmDDMe6GFTkwfrkbGrJKcGt4DuuUbcfmE4JpJTTYiWMZ6U6BmnEZxl0aKDHpjBeGTBZwZvIRSECO%2Bqk6e8RYeVC27eZ8jm8Xy/EgUedY/tgonNt%2BtxzmexIXlevZhgOw6jo%2B/zyX6pxxV%2BwnYKu65/txBbFUGQWgXiZqxZ%2B54yf86n/G%2BGVsa%2Bqo5bVCX5WVfmAV8FVheBkHQbBVUIa5KEwYN1V2gQCAJIlZIEL8AJUjSOGnPZBHjcRMGzfNUHdSym77iF1FwVZaYSmh3GsQq7HUkGXExgNZ01lV%2BVRTaJlSfV0pyT6Ckzj5z2WQ1KWjVpYMZWt2F0m4%2B0LUd2nBoVIVNe1biOTGEmmS65k%2BTjiZmVjhNg/ReCMXZw0kmTAaXi5xHY05N3Qyua7o2lqEI8T%2BNeSd2qlf5gVvZWGJUe9x4RV9MW5XVrNqRDXMZVlM4dfO575YVuLFcpAG7txA2CdVcsJfVjXNXG/ytW%2BH4a11EU9frKJfAA9AAVJ7Xve67qIe57AAq2BCAHXu%2B273uR%2B74cBSiZiBBEVpeFg45uMh2xpIurqoshkyYAAbmI/wRJCGQAO4JBAJf/EwMHV7EKzFip3HV8gvkWEwQsC/wxAQEisRgGAcZcP3AC0o%2BN5xsKWu7cad7mvmIuRHYEJsDCWk7BtGxdnxTcb/xWDdrGoBXTHHUGjVFZxumTOgq4l5g7ZiAA%2BrnrSCNiJcweXlefKuhfeEwDBCw/8xBeEwI3X8wtepb1FtNVsxBgCLS%2BI1ZQJ8EjP0hFbNBp9ZyIJiuzIqwt%2BpwONggpBroLaAyoF4BgDgchaStrDWkhlyK33voIR%2BTpaCvwEPMD%2Bpwv7/ECM5IM7CQAPyfjwt%2Bhh4ZCMkKIthBA74SM4VI3hDB%2BFyMEDBMwzF2a2xyvg7qxDPiNSEF4NIxRMDoEHJgBQXhaC0wCjfZRHC9jqJkQItwQiUjQn8WYFIOY%2BpmKVvYxxWDdJKmobQ%2BhyZTjiMkdwjRWjP46P%2BHoqBV5Vxc2xDgjBTIyroVaI4ZAz9ooJAIBAcRCgbjlIvG4OxDinGEUsdY2x4SnFvEgRYDgaxaCcH8LwPw3BeCoE4FjSw1gZQbC2PBcwgQeCkAIJoPpawADWARJC3A0JILg0JAgaH8BoMwyRkhmAABwXP0JwSQvAWASA0BoUgIytCkHGRwXgCgQDPJWRwLQaw4CwBgIgEAGwCBpC8ARCgEA0AHDoAkKINxOCqAuckUeyRJD/GAMgNuUhbhmF4DYwgJA8B3y4DIQQIgxDsCkJS%2BQSg1CrNILoClZcnRpE4DwfpgzhnMo%2BXaKFkLISoCoP8VF6LMXYtxf8fFZh/gQA8PC%2BgxAoTxy4CsXgfyAWkAgEgOFaQEVkBhQao1IBgBSDMHwOgewoKUFiMy2IEQ2jnC5bwJ1zBiDnDtLEbQSE/lLLhYyO0DBaCuv%2BbwLAsQvDADcGIWg3zRmkCwCwQwwBxARuTZBf1eB872OZZgVQSEoU7CWQ/AZmbaB4FiE6L1HgsDMuWngB5Sa83EFiJkTA3pU1GCrUYVZawqAGCQQANTwJgMuEkRlLP4FS0Q4g6WzoZSodQmbWX6DTSgaw1h9DVu%2BZANYqBM45ETaPW%2BcZTBTMsGYN5qA23EDJfmg9vQc3OAgK4GYfgKVhAiCMKoYwKXFGyAIT9eggNNEWKMGoL64nNCmB0TwXQ9B2FfXBhYv6lgAdsPB0DFL5jtEg/%2BmoawFCzO2BIHlHAhkvP5ZwcVaKMVYpxXi7Z8qIC4BJaqhZGqtUDrWPNUcYwIAbJAJIQItwACcgRoSSF2WYSQyQnn%2BGSBJm5HA7mkAeYs24yQUgXIkxclI/g9n%2BCk6kV5YzOBfJ%2BcsgduqQV6rBUKqF5BKCmpVUitgnA2gsHztCUeTAorhi4BJ24XAdlEvwOmMlegl3UoXdIJdigV3Mt0Fa9lTBOWjMo9Riz7zOCCohVC/4oqa7EF8/5wLTZguhfCxoBVSrDUqrVYEMwmrbMRsBfq1AyqEiudhT1prYwfN%2BdHtVi1EmuDPJoE4ha9rHXOq9W60gHqXU%2Br9Q4ZbQbiQhrDcyqNMa420ATctlNaaM1vPwB2ehebE1vMLcWvYy3y3MqrTWl19adhvKbS2pZbaO1KG7ed/sdmh1MFHeOydApltxfnbSxLshktMrXSAK1Bh%2B2XqsJYXdsR93CfecevhnAz3KIvdu69t772PrxyRhoqGXAoVwyEFChHliAcyMB3IiGCjs5KDkVnWGUOwYGNMbnX6YNNBF0MDDUHkM4bF3L9DFRZcavWJscjquK25doxwMrFWAtBYHCFsLOyFUcfTC1njHWAX8cwIJxI%2BOK0aa06F3Z0JTP%2BMCJIeTmKKV5Y%2BdZ35dmgWgvBcK/r7nEXIo4D5qVLAFD5zbvnY3mJJiRc4zFilsOaUSAR4IJHq63m6GCBlrL3K1Pa8zQK5zIqxWx6xfHxP/xk%2BhdT5CRVg2jUtcCO17VfTdXdd68atzneVUgET1Y5%2BLfn5t/KeVzF1rZt2ogA6zNq2ltJvX9631/qts9eDaG8Nl3MDRtjfGxNSyzu9q%2B5G7NN382Zoe8gEtz3OEVreW92t5xPuNofb93g/2naQOvaIOnWfAw6CgY6E6U6MOsg8W8O9KBeqWIAwQ6Oxg5ONgb2NOBOTQiars7CmO1gN6YyVOWA2BQuTQDO7gCu36LOMuRGYGHOTQTO4G/O9BbOEu/Q8u%2BQ4uFBXBSuf6HB%2BGCGPBiuBG7BAGJGZGtKOWfKVedG9e/wjeSeKehokwZuUWJAluvefGpAAmWADulGzuqOoWgQgQ/gxyeyTyZh0IyQ1y/uVmtgNmfeKwImkg/gkm/gFypyEmkgEmBy0mXAqBnAgQcht6jhLhlGhKNG8hny1uaypAbaWQzgkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/fold_left.hpp)
- [unit test](../../../../tests/unit/typelivore/fold_left.test.hpp)
