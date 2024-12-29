<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::ClassicFoldRightLast`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-classic-fold-right-last">To Index</a></p>

## Description

`Mouldivore::ClassicFoldRightLast` accepts an operation and returns a function.
When invoked, the function right-folds its argument list using the operation with the last argument as the initiator.

<pre><code>   Oper
-> Init, Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>,
        &vellip;
   Oper&lt;Arg<sub>n-1</sub>,
   Oper&lt;Arg<sub>n</sub>,
       Init
   &gt;::type
   &gt;::type
        &vellip;
   &gt;::type</code></pre>

## Type Signature

```Haskell
ClassicFoldRightLast
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct ClassicFoldRightLast
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
struct Subtract
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= ClassicFoldRightLast<Subtract>
::Mold<Args...>::type;

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

We will implement `ClassicFoldRightLast` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<typename...> class Operation>
struct ClassicFoldRightLast
{
    template<typename...Elements >
    struct Detail {};

    // Base Case:

    // Fold once.
    template<typename Element, typename Initiator>
    struct Detail<Element, Initiator>
    {
        using type = Operation<Element, Initiator>::type;
    };

    // Fold twice.
    template<typename First, typename Second, typename Initiator>
    struct Detail<First, Second, Initiator>
    {
        using type
        =   Operation<First,
            typename Operation<Second,
                Initiator
            >::type
            >::type;
    };

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<typename First, typename Second, typename...Others>
    struct Detail<First, Second, Others...>
    {
        using type
        =   Operation<First,
            typename Operation<Second,
                typename ClassicFoldRightLast<Operation>
                ::template Detail<Others...>
                ::type
            >::type
            >::type;
    };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEIAAc/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJM/jcoPB70wUJhAE80oxWJgAHRYqHYW7IAwKBS3ADyqOI7xyOOBE2IXgctzcBKyyAAYp50AAlPDABCDJgTYEmADsViut3Ft1hz3hiIIKLRbCxGOwL0YBCJVLFEppdIItwAIpgWnRbsKrEL9VDRUCteKdjtbhZ%2BZgGc6QILbbd7bc2bR0LcBFsMcCJZKwdLIdC5ajmGxbiqwWrSJL5bGXfcGNl3iRNZdQzr6YbjbREQnXgRkxms0RiLnQ2aQ6GJV4skYU6jTf59SSyRSBKXVYJK5nHNna/5sCAQNGEf5rfWLVaPXmJd7ff6CAB3PBBxviqUQ2fImPon14YgTZMztO3ISYNAMdBX1Onqujmt17UEWmFo1MOiIiy56Xre94CE%2BDwjngY6fuKDaeqGLYRMA7YIghEpQt24qkgkfYMIBwEVnuTahtep44eSjSIneD5PsRJEkW%2B0EfuhJE4lOM70Qx7HTvKS6esKlpzsuobehy94bFkABuLpuG6Imrg6ADqxCEC66x6gQCAugSmmbqgtz8H6CjJgghjoPQkraYZhGSvptxpK06KghepDEd65m3MQEkXi6SFtlpLreRMkoGagsTGgwVkuhE1YkMGnoHjKUYvnGQEXhWqE3jR4HPieipYsSgUXrBtwFnqRb/iW0LpSBOWPsmRXaReSqlfBK4kf5KGcaxnZYT2uFUTVhFub1pGpS6FF4dRYENVxDESmRcaMvyzLrlyPJ8gK0JTUN2DzQttwceGh4Gn%2BAE7cVCitROB0LRxfFjRhE4Paid3PZOvFvcJAmLj9NodWGcKRseCqYlilzAN5iaCAopVdbcACy7J9WdxaIpD0Pltd2IvV9s7WoJ/EA78/zHICpPxqorDPC6XzAqTZNnMu5j%2BBE%2BJeFgnagwA%2Bt%2B/7qrmDNHLeXgReS9L01cSUg0tLqXHlYOOrm5Wi%2BLTAOIKIrEQjPWA5hZUEOgU4RKCUNiDzD5zIIiKm8mlxTlJYheC6AC0jqO87s77f9RO%2Bz8IuI3%2BVBeAwDg5J8zPSydyWg2mSqXMQwBw7dVwI0HLQh2HHyCl2DJMju63cryoT8gQ1Fi/zmupw7IDI36GNJzjwZ45x/vXCL4kKF4tB6lLlwI13Pd6gbGdMFn4f9lciLERMxsgKbmDm7QlsCNb5fQnbtxcDio2A3PJuCEv5Ir1bLQ25vQ63P4u%2Bz0bh9myfq8MOvttX5It%2BegfC9H8vz%2Bv5fTKN8a5UnbpTAAKpgEK/c5iOGQDzVaCQCAQCHr3T23gXSYQNq7LgywrQcFWLQTgABWXgfgOBaFIKgTgbhrDWDKusTYmCzD%2BB4KQAgmgCGrAANYgGIZIDEGgkhmDMAATlEVwYhQikhcCFEKaQRCOCSF4CwCQGgNCkHIZQ6hHBeAKBABojhFCCGkDgLAGAiAQAaTSF4CsFAIBoCeHQBIUR0ScFUEkQIrtAiSFuMAZAyBt4CLMLwTA%2BAax4GNlwGQggRBiHYFIGJ8glBqE4aQXQ0TNzkjSJwHghCSFkLSTo4ktibF6lQFQW4HivE%2BL8QEoJGIzC3AgB4Jx9BiCmhYbg3gRitCrAgEgRxaRnFkHsUMkZIBgBSDMHwOgLl9EQFiGk2IERWhIlybwFZzBiBImJLEbQ94jFsMceWYkDBaDrOMaQLAsQvDADkrQWg%2BjuC8CwCwQwwBxBXPwN5cOMlnmUMwKoCSoINnkCPooyhtA8CxHJDsjwWA0nfjwKol5pAZLEFiJkTAhp3lGGhUYThqwqAGGTgANTwJgTcOFyFsP4LE0Q4hEn0uSSodQVyMn6A%2BSgOhlh9Awv0ZAVYqA0iNGea7OemFTCWGsGYbRGLVJYEFRAVYdhDk5BcI%2BaYfholhAiMMKooxonFGyAIbVegTWNAWCMRI0S1WTyaJMdonhOh6HtY0fobRrWGttbYJ15q7VOu9UsXBawNhbAkPkjgpDNFFM4FUzx3jfH%2BMCVIRpzTcCEBIJ01hywelEtWNpJgWBEgqtILwyQ/gMSiP8PIjQkgzCSECOo4hgRRH6E4Mo0gqjWEYkCFwQISRREyMCPwyRNbghaN4DovRBj2FEtMRYgZVjSm2PIJQcZ7TXFsE4K0FgUkhSuyYHiAwbYuCiIxFwQRoTwkkEiXoFlcSmXSBZYoNlaTdAzKyUwHJLyo0xqnVQzgJSCBlIDJU6pSaT0fO3heq9GhmmtOGe0nNZg83zuMf0wZqA2kJHXQ4nDyHRj4g%2BeergGiaC9wSAspZVytlrLBfRnZeyDkODBSctUZyLlpJuXch5TywVvI%2BV8yhPz1X/LSUCkF2w2GL0hbwaFsK1kIu2JQ5FqK2EYqxUoXFwnkILpJUwcllLqUxjBY%2BxlCSX2yDfakjlIAZmnuMLymwinlXCtFTkcVkquzSqsJYOV06FWRKgfAVV9R1XOAgK4ANIRHzBqNekTIprcguoKMa5LVr9WLES%2B6vo/q0s6p6JFx18xss2rdQV/IRW5hevKz6yNYamGNcUQBuNHAE01N8SRs9cHBEZtvR01m3SMN9MLZgYtowy2KK7T2i99ahTENEXI/wDam2SGiYBmdtg529JMWYyx1i11jMIyM7d2w921JYAoKSgSpLnoxIeCYN6s2KofbIJ9Vmkm2fZZQ3QqRv2/ryR26NhSrnFNXeUiDV2bt3Ye09vULTTsodZv4dDe2sMoGR3hk7uHEi3bSGkHm93RE8wRzzVQPjZlUYvJQWjlCmOXLYYzljhz2M4dOecy5onMC3PuWIATaKhP4tU68884nQtXKk8gWxMneBybSYpuFSIVNItUhp3gWnsW6fxfpzDfBSUKApVSml5mPuWYkNZwQP2P0BC5YSvz1h%2BWxHc1Qzza9OA7APo7gL8qEiKtC0K4rDrNXuEK3oPVFQKsZZKDkWLlqcgJd9XlgQnrnXVbdRFh1aek%2BVYGLF2rgx6shtVYwiNobWtg%2B0fGynvjru3duCTx78IQoQEzTWHNI2Mfjcm6WqNs2HMXv8P4YhUiNvqOH0KQdsbwecFnYYgt5aQCSGIdW2RQp1FJEkBIrgwizDBEUf4Kv065%2Bja4SDkJM/q%2B6LP8sVYGKsjOEkEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/classic_fold_right_last/implementation.hpp)
- [Source code](../../../../conceptrodon/mouldivore/classic_fold_right_last.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/classic_fold_right_last.test.hpp)
