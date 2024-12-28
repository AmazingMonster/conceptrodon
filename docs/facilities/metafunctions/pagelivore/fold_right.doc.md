<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::FoldRight`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-fold-right">To Index</a></p>

## Description

`Pagelivore::FoldRight` accepts an operation. Its first layer accepts an initiator and returns a function.
When invoked, the function right-folds its argument list using the operation and the initiator.

<pre><code>   Oper
-> Init
-> Arg<sub>0</sub>, Arg<sub>1</sub>..., Arg<sub>n</sub>
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
FoldRight
 :: template<auto...> class...
 -> auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<template<auto...> class>
struct FoldRight
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            static constexpr auto value
            {RESULT};
        };
    
        template<auto...>
        static constexpr auto Page_v
        {RESULT};

    };
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
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldRight<Subtract>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<3>::Page<1, 3, 4>::value == -1);
```

## Implementation

We will implement `FoldRight` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Right-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct FoldRight
{
    template<auto Initiator>
    struct ProtoPage
    {
        struct Slash
        {
            template<auto...Variables >
            struct ProtoPage {};

            // Base Case:

            // Fold once.
            template<auto Variable>
            struct ProtoPage<Variable>
            {
                static constexpr auto value
                { Operation<Variable, Initiator>::value };
            };

            // Fold twice.
            template<auto First, auto Second>
            struct ProtoPage<First, Second>
            {
                static constexpr auto value 
                { 
                    Operation<First,
                    Operation<Second,
                        Initiator
                    >::value
                    >::value
                };
            };

            // Recursive Case:

            // Write out the last two folds, handle the first two parameters,
            // and recurse using the rest to obtain the initiator.
            template<auto First, auto Second, auto...Others>
            struct ProtoPage<First, Second, Others...>
            {
                static constexpr auto value
                {
                    Operation<First,
                    Operation<Second,
                        FoldRight
                        ::template ProtoPage<Initiator>
                        ::Slash
                        ::template ProtoPage<Others...>
                        ::value
                    >::value
                    >::value
                };
            };
        };
        
        template<auto...Agreements>
        using Page = Slash::template ProtoPage<Agreements...>;
    };
        
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwapK4AMngMmAByPgBGmMQgABwAnKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMAGY3KDwe9MNC3EwvEQAHQY6HYW7IAwKBS3ADyaXi7xyWOBE2IXgctwAYp50AAlPDABAEYEmADsViut35tzhzwRSJRRAeDGy7xIFL5AqpNIIt2UxFQRGUTGAiLl/O5vMuAsNtwVtKEeIQwKNAr1lqtRqFEMRMLFqAxaIAaq08EwYvQCbKDXbDSalSq1agNVrbjauQARaH621B/k7Ha3CxMJS3ZFKECcnXJ1P0xm3ARbNFJ5MOkXO1GoW6e4je31O7CVoMh5Wq9Wap1uRvN%2BgB5PWnntkfGlqOZA4gQTTCqNLEW4u24ANzEXm1gYno4sRJJxDJAiRA599FIEqlRGIWJAIA33kw0bjCfHVu58ahiYLQaLDNodBBQAdzwct33tMFhUhWtxTpPBiAmS9VyETA0AYdBhwnTswx7LUkXgxCCEvVD0MwqE21/O0bSokc5mnWcGHnRdl1XR8t2jWjkz1Tid13I1iVJRoCIQpCIN3QSj2EmFSIEdBSHE/j%2BXuSVHGlW8uN3O8H03bclI/Cj73YvT9M/N9NNHL8fz4v80yZNCNiyNdnxzdh8xsu0iwAdSbUFS1RQUEGfPElQIYD634QCFEvBBDHQehAufGgiJA%2Bs0laVhMFBRCFIslM0zi25iAcxDny8LIjESorMAmQV61QGIWnCKrwmvEgKzywUoMdUU63pUTiJXPrZIw5C6zdQkCCCxCsLoghqVpXCI17ESiJItC5MvSbpoUN1Zu4sdOuDKcwMY5ilyG8VjMUj9Do8pTJOPBhVrEo67Ue6S3BG%2BSbv4gDmVZdlft3e9qz8pbIz7FS2tvCjgYne8zUzC03pHUHuoRLtw0hpFtviXbMTh1HkyM3T4YM7BSafcmjW067ibM79fsZ/UgxZiCILBvsXTdS5gGKsFGAIBR9sNcrwmAZVe2jKFY1uJGFCQEAuaxvC%2Bz5gXXmFva4aZgt2a4ysud69EMQ1zBBcEEWib48XKshmW5YhlaYXNy3tcJts9aBV9veBX5/mOQEA9ubBVFYZ5ny%2Bf3A4BdyQ6ELxGqPWlo6uY3YPrS4xvFKwbc7RPk6YBxOTu46yRndDztYvr6b4niDQAWnTF8rNLturhju4AFksqYKgvAYBwck%2BM5gQz5FxrN4hgGtyjLjtyXe5aAeh4%2BTlZeLQCWTZDkZKT%2Bbi73%2Bf7xx12Z4JitdeskOABUaqVNPLnosCAH1MyUNoIGX/vB%2BHk8YRQm0mfNwXBLxQkvJIOmulHbQjlo3LgywEwcFWLQTgABWXgfgOBaFIKgTgbhrDWGNOsTYz5zBQh4KQAgmgUGrAANYgHQZINEGhEhmDMMkZIXB0FsMSFwLkXJpBoI4JIXgLAJAaCCNg3B%2BCOC8AUCAIINCcEoNIHAWAMBEAgHWAQNIqJyCUDQE8Og8RIiZU4KoRI/hG7%2BEkLcYAyAZxSDRGYXgmB8A3jwOgPQ/BBAiDEOwKQMhBCKBUOoVRpBdBgOAkeNInAeCoIwVg2heDOCElRPopUqAqC3CsTYuxDinG3BcWYW4EAPAmPoMuChiDeAqK0KsCASBjFpFMWQCgEBWntJAMAKQZg%2BB0GyooiAMRUkxHCK0AAngk3gEzmDECmYSGI2g0IqKocYrWhIGC0BmZErAMQvDAGRLQWgijuC8CwCwQwwBxD7IQmsvAzlzm4IXA5UEszyCCHqKk2geAYhHkWR4LAqT5p4AkRc0gzliAxEyJgWMYIbl/KMLQ1YVADCz3dHgTAwFBLYKoX44QohxDBMJWEtQqTon6BuSgIhlh9D/MUZAVYqA0iNHOY3CY5FYymEsNYMwsjoVNiwEyiAqw7CPOcBAVw0w/BgNCOEYYVRRhgOKNkAQsq9BqsaAsEYCQwESv/k0SY7RPCdD0Iaxo/Q2i6uVfq2wJrNUGpNbapYiC1gbC2BIJJHBMGkBkbwOReTrG2PsY45xLCykQFwIQEg0YzCUOWPU1FqwgpMCwAkMVpBGGSChGiZIUIhEaEkGYSQgQNDoP8KkERYjSASMoWifwXB/ApH4f4ZhPCC3%2BH9akuRCilHUNReorRzSdGZIMZ07p1TzFsE4K0Fga4uSNyYDiAwlUuDJDRFwVh7jPEkG8b42QASSXSDJUoClkTdADNiUweJFyfV%2BoDWkjgGS9EBRycGgp9jcQ3JKZu7dGhymVLadU%2BNUIzBJsHaoppLTUBVPiIYrpcGQOjB/UYDdXAgg0FoMMygYzInzOmZ8wjizlmrIcJ8zZQttm7NSQco5JyzmfKuUi7YuD8DFWHs81JbzkCom2FQ8IoIRG4L%2BQC6ZwK2P1KbBCqh0LYVKARdcowyLQDQb4BihQWKcV4s%2BYS49QTT2yHJRE3BV7qUot5VYelYnRUsrZTkDlXK4FWf5YK%2BIwqarwHFfUSVfhpUYSdcEDCrqVXpEyOq3IZqCiqoizqxViwwuWr6I66Lcqeh%2BetYMBLeqLWpfyOluYNqct2u9R6shZWRGPt7ZwT9obV2/o3Vu1h5SY03jA3UqDjTU2YHTaMLNNbxEgChJu4tXJ0HJEEVCEtZbJBgKfX22wA6GlqI0do3RWTENTrMRYjg87CksAUGuGca4muOgmLu2NwrD3%2BOJYZkJ8hz2mZ0MN0gN672JP0MkntkS5GvqyaWXJqgDtHZO2dhEtUKnIfaWBqEkGVswZQND6pW3kejGO2kNIr9TvJFfudggr9genqGfjPD4zJmLOIxTpZKy1mUbg1snZez2OYEOccsQTHIUsZU1J0gHHHnccibx/jnyhM/MiWJwFUzJOgpk58%2BTcKlNIolkO9FmotPYtxSSfFvB9N3YkEZ0JT3KWvbXcYOlNhbPebwQ5ucnAdhctpXyywArA1Cu8V55lGWjUuEC2lvQCqKi5diyUHIQXtU5FC/a5LAgstBZj8a%2BYJW3UOoGPHl1yeVXitIV691VWUm/dq0T24h3jvrnB6CSHbW421Phym0gaaM2UB9bWiRnC0RQihOg3hc2pGd65C2n7sjOD9uUfXnN6D80CK5FIxIkhuFcHYWYbtIioQF%2BH/IrrdCvscDcUPwNI%2Bt/LFWNCrIzhJBAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/fold_right/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/fold_right.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/fold_right.test.hpp)
