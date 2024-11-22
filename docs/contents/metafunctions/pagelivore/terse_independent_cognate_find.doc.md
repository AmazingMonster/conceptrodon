<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::TerseIndependentCognateFind`

## Description

`Pagelivore::TerseIndependentCognateFind` accepts a list of predicates and returns a function.
When invoked, the function returns the index of the first argument that satisfies all predicates, or `-1` if it cannot find the argument.

`Pagelivore::TerseIndependentCognateFind` prepares fewer base cases than `Pagelivore::IndependentCognateFind`.

<pre><code>   Predicates...
-> Arguments...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
TerseIndependentCognateFind ::   template<auto...> class...
                              -> auto...
                              -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct TerseIndependentCognateFind
{
    template<auto...>
    alias Page
    {
        static constexpr std::make_signed_t<size_t> value
        {RESULT};
    };

    template<auto...>
    static constexpr std::make_signed_t<size_t> Page_v
    {RESULT};
};
```

## Examples

We will find the indices of `2` in list `0, 1, 2, 3` and `0, 1, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto...Args>
using Metafunction = TerseIndependentCognateFind<IsTwo>
::Page<Args...>;

static_assert(Metafunction<0, 1, 2, 3>::value == 2);
static_assert(Metafunction<0, 1, 3>::value == -1);
```

## Implementation

We will implement `TerseIndependentCognateFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class...Predicates>
struct TerseIndependentCognateFind
{
    template<auto...>
    struct ProtoPage
    { static constexpr std::make_signed_t<size_t> value {-1}; };

    template<auto First>
    struct ProtoPage<First>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    ProtoPage<Others...>
                    ::value != -1
                )
                { 
                    return 2 + ProtoPage<Others...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKxcpK4AMngMmAByPgBGmMQgAOyJpAAOqAqETgwe3r4BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMzhyN5YANQmO24EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLFSBkhp3OUJhTDhZyYXiIADosS8jgcmAoFFiMcpiJh8KJIc8dq8PuNiF4HEcACrxJQASQYWGunMYbVQwGYkIAYuF0GCTIkrB8jjKjpDobDMPC0ZjsdSwbKjnSGQQjiTUERlExgErpbKJRYtc1HMhcQJxphVKliFb0CAQCwmABrW6ZAVku7wzIAL1uBBxADcxF5fhaALRcCUAEVOluTqfFZpl8qRKLcKtQRxFxHGoKzVvpjP1huNSrOxdL6vLFvN5c1sxtdoYDqdLoLRyj3ljbfNko1monMpM/is/iTECWRzjOMB7s9Ppufoi6EDZxDYbL70nk4t4%2BPx7wVC7PedRygRPMADYnySyXgKZgqW4G%2BHqe7BzGSxLGe54Ti2pIEOsDBHBoqYnIkKYfCBoGynUSjISh8GWhBUFLomOxpghGEnghC7EfBKYESB6ZUUh5Y5oqyrooWP6kEc/ZCJgaCcmxBZEgA8gQCCsoe7b3DqerEAaqBGia8KsUcnHcegbGCcJJYPk2R6jpaU4jjKHbvtekK9uxzEDtGw7aSRUrWaB06zvOi7LtSrprt6vp4P6O6/m4%2B67jSdnnqe%2BmgZexmOs65Hnve2JmM%2B8WvuSyKfvJeAlr%2B2D/pZQHRce4GYJBxDQbBBEUZmQWYWhvzhdxN7EHlk6xRiT4vqSyWUvCSkCGKf4gABmC5aFwWSkcOHFUc%2BGEYh4KVSh1VHLV9omVFw3HhAjWgdWMm1vCamsppgWYaB2VDkcYBgKcSZ4ZtmrAWtNknA9oHjdBZgnJYknSbJdZuPtGlqkdx3HqdMZwbdo4zRDMrVdDWFjYVuEJuDRHPcmZGhTRtmaljFWagxKVMaqGLvMApJQryVJAzKXiZEYeq1n813bT98Kk%2BTbCCISgMZkhRG0bNAD0ABUoti%2BLEuC2CIti8yn4EAoRzi1LHwyxL6uiyrs1fAwBxeMc8LcZsqQK4eYIE3m/Zsoe2qMmyChMgA7qgYIgEcqReDEtBGauIAxKgng3HVzSCPCbJM1dRxmDip787Z5uIoxqLMUS7zEMAVNgrT4TAEcACyhVMFQXi6w0TNyyWmAclyri8h4AopSKnJhw7zuHu6rNnGnGeHbzs2GcgNz4korQQAXzTF6X2TwhobFBFHbE7C8oOxjslHXWYwECwPQ8EvEBBj4Xk8ONPZyz5Ni/L/1lkR2veFb7ZHArLQnD%2BLwfgcFopCoJwbjWNYWo1gbFjGYHYPBSAEE0E/FYXoAiSAxBoSQXBEg7A0P4DQ8VHxmAABzYP0JwSQvAWASA0LPD%2BX8f4cF4AoEAs9IGfyfqQOAsAYCIBAGsAgHsCDkEoGgaEdB4iRFYFsVQ2DHxxkfJII4wBkC2ikBiMwvA3xEGIHgN0QR%2BCCBEGIdgUgZCCEUCodQDDSC6CCI7B4qROA8Gfq/d%2BUDv6cH4uiLhRxUBXlEeIyR0jZGTXge9CAHh%2BH0BdLsLgSxeD0K0CsCASA%2BGpAEWQCgEB4mJJAMAKQZg%2BB0EhCWSgMQHExHCC0C41jeBFOYMQC4/EYjaC4vQ8BfDOYEH4gwWgpSTFYBiF4YA%2BZaC0BodwXgWBPRGHEJ09K9S8ARk/A4x0XF0RbHAeESEL8THexiA8KpHgsAOPuHgYhQzSAzOIP7JQSYoSGGAN7IwUCVhUAMBnAAangTAjt%2BLcjKfo4QohxB6M0fIJQagHFmP0FclA/9LD6DwDEGhkAVioBNtkQZcZARXVMJYawZgKEnNUVgOFC5uhTOcBAVwUw/BBFCOEIYlQRiFAyFkAQ5K9BFEZQweYwwEhBDsMSxoEw%2BR5ApUSk%2BAg%2BitA5bSrlth%2BXMu5fyiVixwmrHWJsCQtiOBv1IOQ3glCjieIkVImRcj/F3lwIQEgH0wERIgXclYwkmBYASIS2BkgdgYgAJw7ESJIRBZhJCPlIf4R87r8EcEIaQYhYCMSPi4I%2BbB7rsGxv8Eg/wnrHxaocZQ6htCbUMJiaw2J7CXHoh4Sk1AwTBHCM4C0FgEZEhxiYLiAw9MuDuoxFwBBSj8AqLUXoAF2i/nSABYY4FJjdBZIsUwKxQz1Wau1Y4jgzjOHojcVeGtdaG1NquZNNtHaNB3iCQkkJlrN6RLuUwuJ5aj3xFLakkJIB131rxEYVtXBZ40FoLkmhEACkmIqSUr5/6qk1LqQ4L5TTeStPaQ4rpPS%2BkDK%2BSMq54yv74FJCfGZgyv7zOQIsr5Ky6gOI2Vsi4Oythf32Yc8BJyzmYAuaM65Odz0PONAoF5byPmMC%2Bf235uih2yBHcYr%2B46wW3IxVYKFGyCUIqRfaTgqKCC9STOJrFOL4h4tmfC4VDQXCcllcETkCq6VpAZQ0fTrKGhGalTykVfL%2Bj6Zsw0MVAxqULGM7MSYngOh6A8y58onK1XKuAYFtZc7M2cHYsQWt9bG3Ptzq29tCDTXdotWE61UToGkHtY6yg6rw2RrbYgxIqbkg7EkH6yRQR51ZtsDmjL%2Bb4CFo4Vw29V7ElCLYNWqL3iWAKAjLaCMCXFTjC7eavFfbZADr498wTIKQA7FIJO6dNjQ1hZMZQpdrj3GRZYD1vrA2hspXGAetrx7dg7HS%2Bewtd6b3JJuwkfrqRUg3EG%2B6m4w2CBD260OnJrJ8mFOKVUwDgPqm1PqeB8tzSoMdNQ5gbpvSxAIaOUhsZ5HhmTIw7MkxOG8NHII2sr%2BxGSlkb2aoqjvAaMZDo5csZTG818EeWx157zPlHJ4zoiQ/GDFAqEzoebonjCQpsFJ%2BAMmGiDMFquFTlhsU6txWozThLHPZF0%2B4Lz%2BRKWGdcwF%2BlxRsjmdM9kKzPm6i8ucw503tnnPG7lfZ9XQrfM25WAoIBqqlWhfsetiLNa9v9YHIdykuoIBmpUZa8JZ6812swA6kYhK1n5ZAGYNtOwdj%2BHQUg0hKfEhxozV7qhtW6G2tIC6/wHr/DYPiu6yQ7qUFeq4AttZOxPcUM4BH6J6rFG55b/n%2BrKwTmZGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/terse_independent_cognate_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/terse_independent_cognate_find.test.hpp)
