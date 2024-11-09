<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ClassicFoldLeftFirst`

## Description

`Typelivore::ClassicFoldLeftFirst` accepts a list of elements and produces a function.
When invoked with an operation, the function left-folds the list with the first element as the initiator.
The type result of the operation is used for continuation.
<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>..., E<sub>n</sub>
-> Operation
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       E<sub>0</sub>, E<sub>1</sub>
   &gt;::type, E<sub>2</sub>
   &gt;::type
   ..., E<sub>n</sub>&gt::type</code></pre>

## Type Signature

```Haskell
ClassicFoldLeftFirst ::  typename...
                      -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct ClassicFoldLeftFirst
{
    template<template<typename...> class...>
    alias Road = RESULT;
        
    template<template<typename...> class>
    alias UniRoad = RESULT;
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

template<template<typename...> class...Args>
using Metafunction 
= ClassicFoldLeftFirst<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 2>
  >::Road<Args...>;

using SupposedResult
= std::integral_constant<int, 16777216>;

using Result = Metafunction<Power>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::ClassicFoldLeftFirst` relies on recursion to reduce the number of parameters.
Each recursive case has two functionalities:

1. left-fold several parameters;
2. use the result from 1 as an initiator and perform recursion to fold the rest.

The function always ends in base cases, which fold the last couple of elements to produce a result.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct ClassicFoldLeftFirst {};

template<typename Initiator, typename Element>
struct ClassicFoldLeftFirst<Initiator, Element>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = Operation<Initiator, Element>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<typename Initiator, typename First, typename Second>
struct ClassicFoldLeftFirst<Initiator, First, Second>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = Operation<
          typename Operation<
            Initiator, First
          >::type, Second
          >::type;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

template<typename Initiator, typename First, typename Second, typename...Others>
struct ClassicFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = ClassicFoldLeftFirst<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcXKQADqgKhE4MHt6%2BehlZjgLhkTEs8YkAbGa2mPYlDEIETMQEeT5%2BQfWNOS1tBGXRcQnJqQqt7Z0FE1NDESOVY7UAlLaoXsTI7BwEmCxpBvsmgW4EAJ5pjKyYAHQP2PRsggqn2CYaAIKTxF4OAGo3AYFFlkAAxTzoUKYKgEcF4YiTAEmADsVlRABFTlZvp8vvtDsdMKdzlcbmwAQBJBjZJhEMgAy7XZiUp4HRgEd7437/AhAkFgyG0aGw%2BGIyakml0hmkAHsl5cwIfPHo/EAjVMg5Hekks6EnUnfXk1n3B7vAHIQUAgDy12I9Jy3O%2BmoBvMBmMwrTo6s1aNxX1drq8WSMTPJKJdQY1p0xtvtjoEUtpjnpJDlCs57xAIGZeoDrrR2MCAd9GoNxNJFd1VZNtwedwtVqYoIbX2AxEwHNezsDmpDEWAAIASqgmOgUYE457vbRSe3O92CAoG9nc%2BScfii5u8d9q0aySzbtSU3g04y86aAQikQQ5Zfj0JMGgGOhe%2B7%2BcCW0KoTC4TfJTOaVU1la8JTvAEnxfN9lS3NUo3LbVK31JCa2NI82FXZVLWtO0EkTBhe1dD8ARnJgfQQlF4L7aMBzDPNIxooNY3jfCmlJMto3DDDMFYh12LOTiuJPGV0zA28hOY5UczzOUoIEN9KOjNc8x3JjtxLLdKP3PVzlQg8H0w81sObVsHgXLtFTeWDKLoodR3HSdpy9ci5zOCylxXYzsBkjdNNVYtSz3fTdMM3jgLPUCwvEyZ7zrSl5NfOKeIbG0CAQBJrJVH4CD%2BQEv1BPAIV/MUAKVNwIvPOUyrk58FLlNKMqRLDsv9TidKrELaxS7ycO/PiCKIzUSLIij1Oo4S7O43jJJjKcBW/IrhVFf9wI4pSuOivD%2BKdQSNujLaEwEtxZuEkSQLEsrTsLaT12uWroOuv1btk210sy1d9snHzcxCkcxxgtxtsG2D/PGwKtKYjqUKJNDDwpM1GxMwU2w7SzOSyzipocicWNGty3A8qyWt8641I0oKvgAegAKjp%2BmGap/FabpgAVbAhFZ%2Bmme%2BFmGcZyHzECCIrS8LBJzcF8djSZde3xF9JkwAA3MQAQifkMgAdwSCB1YBJg5T12JVjggtNT15AqIsJgKc4/hiAgHFYjAMBYy4J2AFoPZNyj/UtGnYxtksqOxSjOwILYGEtcmsUh6H4avL5koRgErBsnK8v5ZRUG14hTax0Mh1U335smdAc3VzAOzEAB9BXWkEUl1blLWda%2BHMVe8TA5QsDuxC8TATdB0tY7B/F44n%2BLEabFHzOIYBMe%2BKaAFkXKoLwGAcHJGJYgqfxFP9xQkvamLLivBCrh1aDrgRJkMcrm4BMx3lITiz5ASvq%2Bv%2Bv76bwQ5UCC/N%2BBBy4fwvl/G%2BDA76NzOI/SQQDKLv0/lfSB0CH7/yfkNNcON5zzy8kjD4Y8l6F0gl4NIRRMDoGHJgBQXhaBcjxKXEB599gQJ/jAtwj8uDVFRLwsw3DuREK%2BNjGhdD%2BQsVXq0dem9jrZ1zoIymd9HDIBrt%2BBIBAIDvwULcVR1k3DUNofQuSZCKFUNEfQ94Q8LAcHWLQTg/heB%2BG4LwVAnATqWGsG6TY2wZpmECDwUgBBNA2PWAAawCJIO4GhJBcFRIEDQ/gNBmGqLUAAHKk/QnBJC8BYBIDQGhSBOK0KQVxHBeAKBAAUoJHAtDrDgLAGAiAQCbAIGkLwd4KAQDQIcOgCQoi3E4KoVJ1QPbVEkACYAyBLZSDuGYXglDCAkDwOXVI/BBAiDEOwKQMhBCKBUOoGpOg9CawdGkTgPBbH2MccEkpnAbTtLafyVAVAARDJGWMiZUyAQzLMACCAHgen0GICiPxXBVi8GqbU0gEAkDdLSL0sgnS4UIpAMAKQdQaD0MypQWINzYgRDaBcc5vB8XMGIBcG0sRtDPmqQE7piobQMFoESw5pAsCxC8MANwYhaAVOcWyg4hhgDiFZfgTsW8lY0JuZgVQz52m7ACZXOxrLaB4FiA6clHgsA3NyngXJ/LJXEFiJkTAnoWBCtVUYYJ6wqAGAXgANTwJgTWeEnEBLWcIUQ4htker2WoG5uhUgGCtaYDxlh9BqoqZAdYqAZY5D5R7MusZQ1WEsGYYpqBDXEGWVK6NvQaU5BcK%2BGYfhUhhEWBUKohRMjZAECW6txQcjDErWMCYDQC0CAGNMTwXQ9B2A7c0eYzbRiJDmIMetY72jDuWKO9YChvE7AkJcjgDjCk3NKa84ZozxmTOmZE35EBcCLOBULMFELrXrAyuOMYEAwkgEkIEO4SRAiokkNEswkhqj5P8NUJImSODZNILk/xdxqjcNSUkVJ3D/AxP8M%2B6oa7WWlPKZUwJ1roWNJhc0h57TyCUGRUC/pbBOBtBYErVEHsmB9TDFwJIdwuBRPmfgBkyy9Aeo2d66QvqlD%2BtZboOoJymBnOccu1dRSXF3Jw08l5pHyOUeo0OWj9Gol/IBfCoFILAhmHBWhw5dTYWoEBQkPDXTDPqbGLJijzYjC0a4AUzF%2BwkQ4rxQS8lxLSCksJZS6lDh3P0s5Iy5lNz2Wcu5bQXl7msDmqMCK4pYqC2Sr5cUmVcr9juaVTc1V6rCVat2MU3V%2BqAmGuNUoM1FrBzodtUwB1TqXUsnc%2Bxr1WyuOyD9Qc4p/H9BCpQNYawEbYhRtvSUuNt9OCJpAcm3raaM1ZpzYNud7at7OAgK4CdIRXzTqrakIotbcg9tmOkGtTRNutvzUtwd479ulrO00LtCxygjr7fMNbd8p0Vse2CjYWxF2feVWJ9dnB9bEDIxRqj1nFN0YYxoP5R6GSabPbp2pl7MDXsSEN5VgHgN0eiaiODvDAiSA/WM1I4nbllNsKhyFNiMPwCwy0x5JmCN9IGRwUjHyWAKCVpbJWSniSTCY8e1jqzZAceazs%2BQPH2tHOCIJ4TFz/3/aQ5J1p7SATPKBywdnnPue891Mif5ZmEWacCDpqn%2BmUCG6BYzy3YwufkJrjzpINc%2BcEFUcDsZfA6COYqRAXFrLPNuf5QHilVKaV%2BcMwyplLK4uYA5VynlfKAlRYtXl3g8WJVStZSl5A8r0sX2VcUrLGqLi5Z1dmwrvBismrKzFirem%2BB2oUI651rqGsi6axIFruzJcBpAMEYNxgps2Cy/N4bTQ%2BVUzPim6w6aXGzawKP/t52i3uCu3octD2Z0Nt22tnbx33tb7bX0Ttz219H4HXdk7o7bCn/yNd1792lhbbnQurZonrlK44BrrXXOASO7uC7jDsxiQPDqbheqQFelgGjsupjiAGYHRoEIEP4IkjEvkogaiNUBkqTshhTlUuAeEpIP4E%2Bv4KkskkkJIEkHEi%2BlwP3pwIEB/hmpwOenpsunMohoweTmbusIalkM4JIEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/classic_fold_left_first.hpp)
- [unit test](../../../../tests/unit/typelivore/classic_fold_left_first.test.hpp)
