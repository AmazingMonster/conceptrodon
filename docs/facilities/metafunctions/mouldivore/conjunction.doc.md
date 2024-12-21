<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Conjunction`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-conjunction">To Index</a></p>

## Description

`Mouldivore::Conjunction` accepts a list of predicates and returns a function.
When invoked, the function returns true if its argument list satisfies all of the predicates and returns false if otherwise.

<pre><code>   Preds...
-> Args...
-> ... && Preds&lt;Args...&gt;::value</code></pre>

## Type Signature

```Haskell
Conjunction ::   template<typename...> class... 
              -> typename...
              -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct Conjunction
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<typename...>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will combine `Pred_0`, `Pred_1`, and `Pred_2` into a new predicate using `Conjunction`.

```C++
/**** Pred_0 ****/
// Returns true if the argument is less than 10.
template<typename...>
struct Pred_0
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value < 10)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is greater than 0.
template<typename...>
struct Pred_1
{ static constexpr bool value {false}; };

template<typename I>
requires (0 < I::value)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<typename...>
struct Pred_2
{ static constexpr bool value {false}; };

template<typename I>
requires (I::value % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Example ****/
template<typename...Args>
using Metafunction = Conjunction<Pred_0, Pred_1, Pred_2>
::Mold<Args...>;

static_assert(Metafunction<std::integral_constant<int, 2>>::value);
static_assert(Metafunction<std::integral_constant<int, 4>>::value);
static_assert(! Metafunction<std::integral_constant<int, 5>>::value);
static_assert(! Metafunction<std::integral_constant<int, -2>>::value);

// If no predicate is provided,
// the value is always `true`.
static_assert
(
    Conjunction<>
    ::Mold
    <
        std::integral_constant<int, 1>,
        std::integral_constant<int, 2>,
        std::integral_constant<int, 3>
    >::value
);
```

## Implementation

We will implement `Conjunction` using a fold expression.

Note that we are not providing an initiator. The default initiator for `&&` is `true`. We place `...` on the left side of the expression to do a left-fold.

<pre><code>   ... && Predicates&lt;Elements...&gt;::value
-> true && ... && Predicates&lt;Elements...&gt;::value
-> (...((
       true
    && Predicate<sub>0</sub>&lt;Elements...&gt;::value)
    && Predicate<sub>1</sub>&lt;Elements...&gt;::value)
    && ...
    && Predicate<sub>Last-1</sub>&lt;Elements...&gt;::value)
    && Predicate<sub>Last</sub>&lt;Elements...&gt;::value
</code></pre>

In our case, left-fold and right-fold produce the same result since `&&` is commutative.

Here's the entire implementation:

```C++
template<template<typename...> class...Predicates>
struct Conjunction
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {(...&&Predicates<Elements...>::value)};
    };
    
    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMxqkrgAyeAyYAHI%2BAEaYxBIAnKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxXEl2mA6ZQgRMxATZPn4Btpj2RQwNTQQlkTFxibaNza25HQrjA2FD5SNVAJS2qF7EyOwcBJgsyQa7JgDMbrv7h5gnZwCeyYysmAB0LyfYANTIBgoKL0/KxEw%2BFEuwUbxMGgAgjNiF4HO8PAxtF4GHUBBDISYAOxWKHvfHvc4HJhHU4EO4PNh/bD0NiCMHHbAYgnvGFwgjvAGoIgAWU86GZBOxuMhLJZMxJeGQnwEM0wqmSxHe0VQnneADcxF4rnixfjhRA/uYAGwmgFAqUkzAMtw0vaMAi/V6MkAgTXeTDLbEAEROIpZPr9gv1uvxRMu13J92YVJedrpjvBofeXnSRnefNo6HeJ29nOI3NQmYFp3jDqdT3BxxFgerGIxAHoAFQt1tt9sNxtt94AFWtjvebc7UOb7bHreHmKh5mOYS%2BXiwOdOaFRmGSicZ9ZH3fN6AA%2BhpBxPGw33gAlTAEDYMBSE2GYd54KiEhAPprAHwOx%2B3%2Bg/F%2BGd4uA0SsoXDK1IwpGNnmdJkoTZeFdwPescVZRpHGlFc5QVJUVTVd1tRzHEqDEJRawsQjfTradQL2YlSVuaNHneABJJNIUBABHLw8EBW8IGY118Ifa5AI0L04IIWEEMBfcNGuVjN2nFCJXQmUb12bDlVVWgNS1YScUk7UyIooNqMhUcW3zIE9y4I8W0nBtTwvK9iBvO8CKfF832ID8E2/d5gEBK0lQIBAAOAjEwPoqNKWgytFOhQzpOsrhkPIlSpTUrDFS0vC9MIixiNoUisUo8iyK3SEoquMlIKYhTYPYzAuJ4613ggQ8RIEt09PExKpI5RDUtOBq0tQyUMNlDSctwnShIKwyrlKv0TKoqdzJ3GS9zMOymwcpzL2vW9FsfZ9Qu83yvzwW9MHVRgQKq2iI1qxjY3ixr4MGrazDGjLJvU%2BUZu03SPQKoqSrK1aaxoi5wJe2KWLYzjuN49ruvm8wAFZ3h23Nc3eMSMU%2Bqz9x%2Bka2OFcbVMw6acOBjGDPvYyKrMiym3ebBVFYA4HyHSKnrhhjYr%2BdjgAZRrUzCYAM0vJgqBRNEGCXPNEWRVEemuRDAhJmzSB1snGtdYtrlFisq2hxKJr3JgfjiAgIB5WX5fVzJrhmdBXTCXZArEPcacMAhri9vWDbeQTetMy30Ot23mgdp2FY1053c9wRMB92g/amgOg8EPXJCrbBw49L01r%2BmOlDjsAwBlxpncVt2CA9kAvfT4hff9wRc4IPXMcL4vtVLkVy5tyv7er2u5cT13k6b1PvfbzPO8D05g/eABaUOXR6kvI5PFjnwYVB3kVC0QQfa6T4LdU8CwdBSH386QY828xAAdyYG5bxMY0NEWn%2BIoSStqPO2GIIDBgRAINWDdThsRZEbfkEDrgQPFHPFuacM5Z3UjnVeedAJvAfsmVBzdW6YOXt3EOBCUEEhTugheHds5d1wT3d4xw4FCm3kJDEQ8OCrFoJwTGvA/AcC0KQVAnA3DWGsKydYmxhJmGODwUgBBNC8NWAAaxAJjSQTwNCSC4FiY4GhMYaDMMaY0ZgAAclj9CcEkLwFgEgNCBGEaI8RHBeAKBAIEFRIjeGkDgLAGAiAQDrAIMkLwPcKAQDQPsOgcQIiPE4KoSxxp17GkkAFZA0opBPDMLwC0RBiC3z0PwQQIgxDsCkDIQQigVDqD8aQXQXBSBv3bskTgPA%2BECKEaosRnAADykSIkclQM%2BFJaSMlZJyTonaEAPBxPoEqGcXBli8F8VoVYEAkCxOSPEsg0Tdn7JAMAKQZg%2BB0F2MQLxEBoh9OiGEJoNxOm8AecwYgNwBnRG0LUXxSjYkJgGQwWgzzGlYGiF4YAbgxDFReaQLALBDDAHEGC1qdQ7peMafKWokTthKNbvwxptA8DRHbh8jwWA%2BmSTwI47gvA7rEBVEob0ewkXEqMKo1YVADBiwAGp4EwG/AZ0Y4VlOEKIcQ1SxV1LUH05p%2BgkUoCkZYfQJKvGQFWKgdcmRMXr3drmUwlhrABF4KgBlxSsDqogKsGoisXAMHcJ4NoegQjzDKBUPQBQMgCEmH4FpXqeiDHdUsTo3R6izF9XoW1PQ%2BjNCDcMSoYx%2BiRpaRKONbqE0SBtbIrYWbbEcEEaQVxprODvAmekzJwBsmAVme1XAhASA5gUas9ZnLViviYFgeI1rSCaMkMcJ4CRjhYkkHoswkhf7GONEkQl9jSCOMUU8Y0XBjSWISJYld2iuCYyHcaItfT3GeO8cozlATgnbNCcMyJ5BKBHKWYktgnAmgsHVFideTBPgGHTFUJ4XBdEFPwEUkpLSxUVMldIaVShZWNN0OctpTAOl0u6QW3pjT3FDPCZE94Yz3jPtfe%2Bz9SLAIJF/bo9qCy9lLKbccMwayT1%2BK2Ts1Aiy4g3picxyjIw8Nvq%2BEiqoQELm0CuTcu5jS3lPLheJj5XyfkODhQCh0QKQV9PBZC6FtBYV0vhayowKLRH4EBOi60fTsXIFxXCglfTiWkqeRS7YojqW0qUQyplmAWWIt01LU93KmB8oFUKkVWnQMSqqRB2QMqGmiNgwqjlhqrAqus1azV2rZScD1U3A1yqLAmrEea2%2BxmNWht%2BZke1jqch%2BqCA6%2BNixE0BsyCmlIaRvUMGqx61NXRisCFjS0J1uR2thq67MVrIa009fK1GobGaat5oUDmqpyHC3Fv6RwXDxAX1vo/bx79JG/2HggPWop1GW30c2e2zAnaRg9tnQ4kAxwSN6KxDurEhjJDjoyS0pbh7bDHo2f4wJISwkjLY3ehJSSODPqmSwBQ6ppTqh/ZcGYAGG0WtKbIMDoWanyCg5FnQt3WntJeQt1DbjBlXtGc%2BCHmSocw41PDq0MxyMcf2dR44dHfuMZQEzpZwOucjBh8kZIe44cJD3Ajgg1s1sZME8JygonRFSdBUohXMnfnyeY4C4FoL9OYAhVCmFmKlEIrZfZ3gBnisYpM6oHFuwLNp0JaI6zZKbh2apcUpz9K4iufc2yrzDG%2BA8oUPywVwrGCirRyFiQYXanY7lXjr9xgsuquiElsRKWbycAbCnOLxq3F5ctfAG1HW7UQFcA111pRM3%2Bqaz0BrdXihTba0VxW3WGvRvDf0YbibRut8mxX6bqy1gbFzQPwli2D2lsp%2B8ansO6egg5PtwDjaVls7baQDtXbKDIbnY4swJHjjHExiY/Rzj99YlXfutDnAj0%2BNX32zGg7MaWLMQkSQCRDHDq4McfNxxiclo8SdtRfNfJC/Enf/dnVYBldIZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/conjunction.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/conjunction.test.hpp)
