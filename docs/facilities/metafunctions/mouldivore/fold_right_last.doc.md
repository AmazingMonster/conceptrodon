<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::FoldRightLast`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-fold-right-last">To Index</a></p>

## Description

`Mouldivore::FoldRightLast` accepts an operation and returns a function.
When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::value
   &gt;::value
        &vellip;
   &gt;::value</code></pre>

## Type Signature

```Haskell
FoldRightLast
 :: template<typename...> class...
 -> typename...
 -> typename
```

## Structure

```C++
template<template<typename...> class>
struct FoldRightLast
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will right-fold 1, 3, 4 and 3 using a subtraction.
The process can be described as follows:

```C++
   1-(3-(4-3))
-> 1-(3-1)
-> 1-2
-> -1
```

```C++
/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
>;

/**** Test ****/
static_assert(Result::value == -1);
```

## Implementation

We will implement `FoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct FoldRightLast
{
    template<typename...Elements >
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Element, typename Initiator>
    struct Detail<Element, Initiator>
    {
        using type = Operation<Element, Initiator>;
    };

    // Fold twice.
    template<typename First, typename Second, typename Initiator>
    struct Detail<First, Second, Initiator>
    {
        using type
        =   Operation<First,
            Operation<Second,
                Initiator
            >
            >;
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<typename First, typename Second, typename...Others>
    struct Detail<First, Second, Others...>
    {
        using type
        =   Operation<First,
            Operation<Second,
                typename FoldRightLast<Operation>
                ::template Detail<Others...>
                ::type
            >
            >;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};

```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIADsABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHASYLOkGeyb%2BbnsHR5gnZwCe6YysmAB0LyfYANTIBgoK7wDy92ITCabxMGgAgpNiF4HO8AGKedAAJTwwAQQyYkzB4JMSSsEPehPe50OwKupwIdwebBeT2w9DYgl%2BoIJRKhMII7wAIphWnR3rirEkuSd8TjWYSAPSS94WTGYd5ueUgbHYonvaXwxHvATbJ5qokky7XSn3Zhsd70/aMAikYlU80KgCSDBywJILPB6vZsJ5fNo1ytjNt7xdbqIxE96sFBvVhK82SM9vuAv8XP%2BgOBuUDDJtdrDjndkf82FFsYFwrLEPLmoRtHQxIA7ng9eWjWSTQ7HvC8MRJnbTdSFUJMGgGOgB12LQW8EWo2yCNDfbymHRrnDe/33iOxxPQ67CxH54SYxK4wmIsBk1cz9G00SAQkswJ15vbeW4w/MyDTjuBBOP0/OMZznW8gOPICTxLKsvSJXERX8MUaxlJFR02bIADcFSVJQVWrM9NQAdWIQgFQ2TkCAQBVvgoxtUHefh6wUO0EEMdB6GJKiGLfJt6PSNpHj2PtSGQ942PeYg0L7BULyTSiFUkyZiXo1BYj5BhOIVCJwxIfUz3bY4KSnBUNz7ENB0dbdR3/SczUeWk/nkvsIJ9Tk/VXANTlMrc/3HO1HKovtaQg09YM/WSr0HQCoPTQlHyBH83G898wM/eLnwYa5fIA1LIOvSy62RVF0VCTECGudKf1LXLIJAEADIVdy11OAKEgUYLoJqoC6qirqoOqsK8tBRDy3gmC232UlDNuOyaRecFgEk60mQgiL3gAWW1E50yazy3AWpbg3a14Sx6qlxsrEb8PBSUACp7oex6nslbE7oe94ABVMEmX5HpeiE3qeoH7v%2B8UcTMfwIi%2BLwsFTNwvEcWhCBuT1sQaztZoVcFbKHWVPVc7cvDUoEHAACQaQFVTxcs1t6wbtveSZ0DqiI9kWsQAH0x3mQRrlZu1wTqjCxC8BUAFpZSFkXyVLK6cUupCIXRozMdpcFiGABRPTWoQicXJhYQZ3XiYNghydoSnTnVzWOuwM77nGpXJuNFWhzVjWtc68E1vWlcqC8BgHFyAVq3vQqUTRDEsV/PWSfKr26s2%2Btrmt479WguXsTW1CFC8WhOQZ33Wn9wOQVDtxyyZlnBEwdnaC5gQefjtx%2BfeLg3hEs8q5AVna6BevudaXnTlb/wO8rghmZ7mu64bhgm75wQ7Ukceu8n6u2f7ueF5Hpf3jHr3hsVyFWkcZAOcxJR2ggHO84IKXvAVbaGbFrgVlFDg1loTgAFZeD8DgWhSCoE4BXSw1hGYbC2E/CGPBSD30AZ/NYABrEAP9JBPA0CkMwZgACcuCuA/ywSkLgSQkjSG/hwSQvAWASA0BoUgACgEgI4LwBQIAGEIK0GsOAsAYCIBAORdICNyCUDQAcOgCQoiPE4KoFIgQxaBEkO8YAyBkBtwwWYXgmB8ARjwMzLgMhBAiDEOwKQRj5BKDUJoHQehGxAnSJwHgX9f7/xscAzgfwEbCM5KgKg7w5EKKUSotRGinhmHeBADwEj6DEAFLAlYvAuGf1IBAJA4j0iSLIBQCAGSskgGAFIMwfA6BCXYRAWI7jYgRDaDcJxvBqnMGIDcP4sRtCjgQXA8RwY/gMFoHUxBpAsCxC8MAJUtBaDsO4LwLALBDDAHEIM/Akkg5YSmUAzAqg0J7HqeQGulCgFI1iECZpHgsDuMXHgWh0zSBYWILELImAeRzKMEjIwNi1hUAMJrAAangTAjZHwALgfwYxohxDmNBZYlQ6hBm6EMQYd5phwGWH0HgWI7DIBrFQOkJoUyxZM22siqwlgzDMLuSRLAmKIBrDsB03ILhxwzD8IYsIEQRjVDGIYkoOQBDMr0DypoixRiJEMXSoOAgBjTE8F0PQ4qmhSqGOypYXLbBTA6DKwoYr1XCs5aK2lUDtgSBcRwP%2BjD3EsICfIxRyjVHqKkOEyJuBCAkHif4N%2BSSPlrCokwLAiQaWkFQZIfwTxcH%2BHIRoSQZhJCBHoT/QIuD9CcGoaQWh7qniBC4IEFIuCSGBHQYQsNwQmG8BYWwjh8CPmpP4WkwR3iRE5LybE6RbBOBtBYBhJIYsmCfERVeLguCnhcEwdo3RJB9F6ChSYiF0goWKBhe43QxT7FMEcdMk1ZqS0eI4F4ggPidT%2BMCTa3t8y26DuHRoSJ0TMmxLdWYRJlbEE8PSagGJCRRG5NfTesYXx5kDq4Awmg%2Bc2qUEqYMxptTdkQeaa09pDhdndJtL0/p7jhmjPGZM3Zsz5mLKAcs%2Blaz3GbO2TsOBvcDm8COScm4ZydhAMudcuBdyHlKGeThy8VavlMF%2Bf8wFZpdlTvBWY2dsh53WLhSAYpfaUDWGsGijF8BsW4tyPiwlaZiXWDJaWil%2BjvqKd6PS5wEBXD8tZeOXVyxuVZF5XkTVLKMjWaFcqkVcqGiGeaOq0zBmJUeYWM5vVcrPN2cC35yoLm37rE2EaiLlDN0Ws4FaoJyjf1JgHUOzBTqx1xPMO6h9ySVjeswL6sYAbKEprTYOyNSQf64LIf4KNMbJCGK3WW2wFb8vVvgLWoRDaxFfqyS2nY7bgksAUBhdRGE0uXEmKOl1lLJ2yGncJixYnYVAN0P4UgK613OKTaatxgyWG7v3X4gJI2xsTam2SJSUT%2Bu3py/4PLVba1NvfY2u7YxxvpHSBzSbuCObTYIBzVQSiSnAb7KBqpNTmlQehy0tpHSEOvp6X0gZeHMAjLGWITDNzsOvLozM3sBG9ODOI8gBGpHeDkfcVR2ptGLkkUY7wZjjy2OvI40%2Bvg3yFB/IBUCgTi2hMSBE4IVbi6Aj6HmTJlFNgjnUqU3izgkoq4adJeShIlK9NYu800Rl7hgtmfQBZ1VgrchedN%2BUfzlmdf9CCwUez8rbehY5db%2BY0r7chfaMb/VkXoHGr23Fw7CWQfKNG%2BN94f2niA8y3Nt1HrH3cMK8V/1JryuScHf4fwP8iFNfoZnpI2bzVB9YW1zhXrA0gEkD/UNpCkj0JSJIAhXBsFmGCJQ/wB3mGcE9U%2Bk1Wii9d5L/ltYdzsjOEkEAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/fold_right_last.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/fold_right_last.test.hpp)
