<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::FoldLeftFirst`

## Description

`Typelivore::FoldLeftFirst` accepts a list of elements and produces a function.
When invoked with an operation, the function left-folds the list with the first element as the initiator.
<pre><code>   E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>..., E<sub>n</sub>
->&nbsp;Operation
->&nbsp;Operation&lt;...
   Operation&lt;
   Operation&lt;
       E<sub>0</sub>, E<sub>1</sub>
   &gt;, E<sub>2</sub>
   &gt;
   ..., E<sub>n</sub>&gt</code></pre>

## Type Signature

```Haskell
FoldLeftFirst ::  typename...
                  -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct FoldLeftFirst
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

template<typename...Args>
using Power_t = Power<Args...>::type;

template<template<typename...> class...Args>
using Metafunction 
= FoldLeftFirst<
    std::integral_constant<int, 2>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 2>
  >::Road<Args...>;

using SupposedResult
= std::integral_constant<int, 16777216>;

using Result = Metafunction<Power_t>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::FoldLeftFirst` relies on recursion to reduce the number of arguments.
Each recursive case has two functionalities:

1. left-fold several arguments;
2. use the result from 1 as an initiator and perform recursion to fold the rest.

The function always ends in base cases, which fold the last couple of elements to produce a result.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct FoldLeftFirst {};

template<typename Initiator, typename Element>
struct FoldLeftFirst<Initiator, Element>
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

template<typename Initiator, typename First, typename Second>
struct FoldLeftFirst<Initiator, First, Second>
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

template<typename Initiator, typename First, typename Second, typename...Others>
struct FoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = FoldLeftFirst<
            Operation<
            Operation<
                Initiator, First
            >, Second
            >, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArNIADqgKhE4MHt6%2BeqnpjgKh4VEssfFctpj2hQxCBEzEBNk%2BfoF2mA6Z9Y0ExZExcYnSCg1NLbmVo739peUSAJS2qF7EyOwcBJgsyQZbJv5uBACeyYysmAB019j0bIIKB9gmGgCCo8ReDgDUAGKe6GCmCoBF%2BeGIo2%2BJgA7FZoQARA5WN4vV5bHZ7TAHI6nc5sb4ASQYGSYRDI3xOZ2Y%2BNu20YBCeqI%2BXwIfwBQJBYIhDMORJJZNI31p9x5zxRsNR3ylFO2u1JWMO6Ll%2B0VuOpV2uT2%2ByAMCgU3wA8mdiKTMoy3tLvsyfvDMA06JLpTDka9LZavOkjBTcVCLW6pQd4YbjaaBNi%2BY5SSRBcL6Yz/C7LTDEQnUY6pUrMdjM/Ls2qLtdLlqdUw9YXXsBiJg6Q9za7pR6wsBvgAlVBMdBQ/xB2322jYitVmsEBSFp4gECUhUu5NItNvHMqnFUi6E4mRgXelf4rmjQVT9XfISdAToOvW1n/WiA4Gg8GjcPrvBR8m7giC49oBhn/xi17O9MZQxXNFVlLNVW3DUi1/bVdX1I04lDBg60tC9vl7JgHT9AMJWwt1Gy9KdfXrf1A2DRDamxQD/QQk1KMOaj/TXfloz%2Be8GTw0jfw/E9v0YpNfznPDZ1TFE8MXBUjjAkDlzxKDizg8tK2rEVHkEvCCObNsOy7Hs7Uw/tDkHFT6VHTVfwnKchP/BFrNRCS80g5iN1Yg9Vzffd83xT9T08yDCwNAgEDiNS/zQq8b05djHxY192J4r90EFQLgohMd1JsxNpQc0DgKXNy2HS7BYNLeCQ3ov9UIIT4bX0rCSKhXCGvdT1myI/jdLZa8OTvbkqM4pjaKQ/rmsG8qzQYgamOlCNn03N8OoE7AEtPRanW4w0gpCscpq7bBLOkrZW3bH83CGirrKTWzRP/cTDsknLZPVIqSrLa5jOHULAM046dLIjCHSM5TPqKyzcTs66ZzeAB6AAqeGEcR6HUTh%2BGABVsCENGEeRmHEfx2Hcdu/8zH8MIdS8LAuzcL91mSEc61RL9RkwAA3MRvjCVlUgAdziCAue%2BJhBUF6IFjTJrLUF5BGosJgRKyqV%2BGICAkWiMAwEDLg1YAWh18XhNhbVYcDeWE0axE8KrAhVgYbUIct4nHoKzBvlePy5O%2BKwMrQ5RUD54gJcV74fqs4TuytAh0AnLnMErMQAH1mYaQRsS5wVef514J3Z7xMEFCwc7ELxMHFwSboV%2Bc0Xuxy5PLYhgC%2Bt4fr9gOE9ZMjW7iAcG7M6D9sncGK4XGvcuVB6vPkmCSzey5Xl7usfoAWX0qgvAYLoBGIsiIp6hbJoa0Zo5AWP49oJOBGmVPDnT74zCeUhAKPmPBDjk1z%2BTwweTcW//Afp%2Bo4vy2GfC%2BDAr7f1vpIf%2BeFn4n1fiAz%2B18f6CEFPfDKAYLIgG0qdeejcip2Wbq1I8Xhkj5EwOgFsmAFBeFoBxf8EdYGn3fqA8BacUHfC4AANmhDwswXD4xQ1eD9Sh1DaGdRXg0NeG96JuC7sQduAiq7TEcMgBOpU4gEAgLAhQFw1FqTcCImh75iGkLSOQwxtCnhlwsBwJYtBOAJF4H4bgvBUCcDcNYawVoVhrFduYfwPBSAEE0LYpYABrYYlwNCSC4NCfwGgEgaDMJwzhZgAAcaT9CcEkLwFgEgNAaFIM4rQpA3EcF4AoEAhTgkcC0EsOAsAYCIBACsAgyQvDvgoBANAOw6BxAiBcTgqg0mcJ1pwyQ3xgDIBllIS4ZheDkMICQPA0dKj8EECIMQ7ApAyEEIoFQ6hak6D0DzE0yROA8DsQ4pxITSmcANB09prJUBUG%2BMM0Z4zJnTI4ZIOZ3wIAeF6fQYgUJSZcAWLwGpdTSAQCQD05IfSyBdPhYikAwApBmD4HQLYEJKDRFudEMIjRjgXN4IS5gxBjgGmiNoToNTAk9JFAaBgtASVHNIFgaIXhgBuDELQSpLiOXbEMMAcQ7L8BVi6KzKhtzMCqE6B0jYgTY72PZbQPA0QTSUo8FgW51U8B5MFdK4g0QzG2hYCK9VRgQlLCoAYRuAA1PAmAeYIWcYE9ZwhRDiB2Z6/Zahbm6EqAYa1phLDWH0BqypkAlioHppkAVOsj6BjDVYSwZgSmoGNcQFZMqY1VBqJkFw34Jh%2BEqCEMIAwyhDEqPkDIAhS15DSPWhgsxBgVALXS7oYxmieFaHoDom86g9rbdWjt0xxh9smLYEdla5g1qWAoHx6xFhZI4I4optyylvJGWMiZUyZm/LMP83ASyQX%2BPBZCm1SxgodiGBAcJIBJD%2BEuAATn8NCSQ0SzCSE4QUhInDX1rpyaQPJATLicK4Wk19aSuFJC4Akd9nDN3srKRUqpQSbUwqabClpjyOnkEoCi4FAy2CcEaCwVm0IdZMBKl6Lgr7LhcCiQs/AZIVl6E9Zsn10g/VKADey3QmLTlMHOS4q566bmofufh55ryKNUZo3R5sDGmNRP%2BYChFwLQX%2BDMBCzDRz6lwtQECuIhHukma00MBT1GSxGAY1wQpNBaEhTxQSollLSWkHJcS6ltKHBecZfSZlrLbmcu5by2g/KvNYAtUYMVJSJVdulQKkpcqFVbC8yq256rNXEp1RsEp%2BrDWBONaapQ5rLVNiw3apgjrnWuqpF5rj3rtm8dkP6w5JShP6BFSgTxlhI3RGjQ%2B0p8bL6cCTVHFNA2LAZtcdm3NI3F3VC7c4CArhG3lu/KO%2BYtbm21C26QOttRds1s7UOnok6chlou7UK7fQ53toHT2o7E7HslGe%2BC5YqwV3fdVRu4prjOBC2IJR6jtG7MqcY8xjQJ62MkB05egzdSb2YDvfEUbqqQNgcY9E6EiGeH%2BEkD%2B8ZlQgd3PKbYDDULbHYfgLh1pTzzPEf6YMjgFHPksAUKzGWrNVOYlGKxs9HG1myG4213Z8h%2BNdeOYEETYnLlrsB1umTbSOnfBeaDlgXOed84F/KSEALLOIp0/4fTtOjMoBN8ClnNuhi89IQnfnr6E6C4IGosH4ysUudxRAfF7KfOecFUHqlNK6WBZM0yllbLEuYC5TyvlArAmxctYV3gSWpUyvZel5Aiqsuv1VSU3LWrjgFb1TmkrvAytmuFfF6rhm%2BD2oUE6l1brmvi9axIdreyZeBoCL10Ns2hvLbG7UAV0Nn6pusPN0pi2sCj8HbUYt7gp23YrZ9sdTaCiZCOydzIZ3x2rcu69tfA7j/3dnZvvbM7ehvav1Wvbi7l3bIkyr6THBte69598F3lx3fw5npI4W7XqkC3pYCY4SY44gBmCMb%2BD%2BAJCJIxIFLwHQicKZIU5obU7VKgERKSAJBvoJBpLJKvqSCvpxIfpcCBCqr%2BBSaZqcBXqGYSbzIob0FU6W5LDGrpDOCSBAA)

## Links

- [source code](../../../../conceptrodon/typelivore/fold_left_first.hpp)
- [unit test](../../../../tests/unit/typelivore/fold_left_first.test.hpp)
