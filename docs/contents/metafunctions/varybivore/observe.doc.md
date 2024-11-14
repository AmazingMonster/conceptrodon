<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Observe`

## Description

`Varybivore::Observe` accepts a list of variables and returns a function.
When invoked by an operation, the function collects the indices of the variables that can be evaluated to `true` and instantiates the operation with the collection.

<pre><code>   ..., true<sub>i<sub>0</sub></sub>, ..., true<sub>i<sub>1</sub></sub>, ..., true<sub>i<sub>n</sub></sub>, ...
-> Operation
-> Operation&lt;i<sub>0</sub>, i<sub>1</sub>, ..., i<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Observe ::   auto...
          -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
struct Observe
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will observe `0, 1, nullptr, 3.0` and use the result to instantiate `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<1, 3>;

using Result = Observe<0, 1, nullptr, 3.0>::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Observe` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `stare`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    // `std::index_sequence<I...>` is created
    // for the length of `Phenomena...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        
        // `std::index_sequence<I...>` is created
        // for the count of `true` in `Phenomena...`.
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                // We make `std::array phenomena` so that
                // we can access items of `Phenomena...` using [index].
                std::array phenomena {Phenomena...};

                // We will sort `std::array indices`.
                std::array indices {I...};
                
                // We will use this comparison function to sort.
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return
                    // If `phenomena[i]` is `true` and
                    // `phenomena[j]` is false, then `i` is less than `j`.
                    // Therefore, an index of `true` is always less
                    // than an index of `false`.
                    // As a result, indices of `true` will
                    // assemble in the front of the array.
                        (phenomena[i] && ! phenomena[j])
                    // If `phenomena[i]` and `phenomena[j]` are both `true`,
                    // then we return `i < j` to preserve relative positions.
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                // `indices` will be reused for the result.
                std::ranges::sort(indices, comp);
                
                // return the result.
                return indices;
            }();

            // `result` is a `std::array`.
            // We collect its front part,
            // which contains all the indices of `true`.
            // Then, we instantiate `Operation`.
            // We return `std::type_identity` to avoid constructing
            // an object of type `Operation<...>`.
            return std::type_identity<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<auto...Phenomena>
struct Observe
{
    template<template<auto...> class...Agreements>
    using Rail = decltype
    (
        stare
        <
            Agreements...,
            static_cast<bool>(Phenomena)...
        >()
    )::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwAHKSuADJ4DJgAcj4ARpjEIACs0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMwRyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2ctxEy3O/dPLwYBy8x1ObjEwBIhAQLDuD2eZj2QLeHzcyHG6CwVDhAKeBEwLFSBnxYPxhOJmDBTAuqAAdPS7kcDkwFAojgB5VIJJgNUhHWKoTz02nKBCMVBsZg4x6zRzIJkCcaYABuYiO1KIR1mxEwECW8JMAHYrE8jmajgB6C0nfwaDEgEARLCqAD6SgAjl5GJswQBJYVw21HPBs5A6nmYdDw82W638YhHAhio70IxJo6oKg2jSi8WSpgB2206PmnUEdYME5JKxJAAiYMyAC9MC6CMLfXcIPbHQxnW7MJ7vZSzv6GX99abzUaTY8YzGS3PY9nu07MK6PV6gcO3KPi38TEGQ0zw/io5PF1ajvHE8m0F5BBmsweNARiF7n8HK8/cwwJYwCwyRYLnOZYVlWNb1mcTYtm29IAFKdiuvZrv2g5bmCcEBuOwHzsaOGLgqDBKqoqQJhqqBHDqCheLQBAfLW4EmHWer4Yu06sQRZqXgA6u8LBMAA1u8z7dl8PxHKkYq/vmH4KBRSY8hxnGXgA7u8oiVkwyCbKyRxsJUCRspm2Y/n%2BzCFhoRxeJkRjgauqhMbWxbnpxc6icQ3zXBJUlmUwJzGqZ%2BYBoakEzkpBE8e8Kl0LQWokHRIkEOgDpiV5Tp4Dpz7ObOrmLu5nmfvgOn%2BRYu5GqF4VsS5uVcdavFHNFtCxdZ7xJkeaCEi0IYCFe94ONkiYUXJrTZTVc7kQqhL0YxZj%2BJJeb/o5XZ4M2rbBny0FrdoE45WNZrsdVe1mqBxAMJVrmXr6T62vN0mLdWeCOR%2BR7Pq%2B75BoYZ67Ud5qXs%2Bt2%2BUxFjaE9h5slQYhKHySaMNmj1gymmC6QpX62iDQGHUdl4ACpijq8aYHyhiFWuj7Zm9lII2IKk/Gy9CsudynWij6qVvZZPPhDtBKFljMRdaMrqpRSM0QQfLpcVxmvW%2BlOWY1tB8xe1oskolT0J%2BN7vFQxCyGTMPqh5PyjT9nEQADMkPY5JyzeY/hHGAYDeQtUrViDdY7SbMaXddGjm/dFiPXWH6fdmfsu8DoOWS07wCum0vvRopCK3Ol4w5WanC%2BWp1w6iRzo5ZmqkUjCTKu8OrEngpcSRkWSKsbnv%2BW4RpuGaZs%2BRbAdW7bttO3d4duwx3ezcGufbacM4m%2BV4/J8nf22hLSMfvL/Jl5gLXoFeJCa8L1G0fXe3dt8RhIw6w0EBAC8KHyHWpPqOwTz9s/Widlb61Rov72NL%2BFRli/3%2Bd5UWL/1xN9Jm2Z360WemyPyiVkogFSrzTGKc6rqU8PUYMBBwY6wfKkfoSckFe2tCpBAGUECEWaBEaBTVt6Xw5raCmiDQH8yOLjRgfIM6UOaIIPAEZsycm5A0RhY1IqZzArAh0BBrhchdHgLA3DJEfk1EwZUqBZGEXGG%2BfqRhzqXmJqgWI2hMAOD1lI4Stp%2BHfEEWcLC9wMZMMXN/bskjpGyMYI4BRZwLE8myGCCBbYeQQDgksGxjJ2IhWnkgwB3Z%2BJCRkchdcA5Nw%2BjOBAAMlhAr/jvvcPCIU74P32iFLsSUHQxJbPZVCSTtzQUzMKCAGTmBZLCbWPJBpwnAOeHiAkRIIxUhpMKepTBpQaK8MY9ksQlDEFLq0/JiYukUlJHMnpnw%2BljmwEyAwrJhSPGADqAkbiFDShjNZCIwAjgACUmB0GmlgA4zjKQuQgBxbU9z7GonOts3ZkpMHCnwa8mMsoMoulEOMMEApPCdgGcEhkkS/gsRcksCRpiInPDaWFJ4FoABUWLsU4otPCTFWLsbYCENjbFeL0U4spRi8lHTHhkm6SSZZRAQlPGGaMrklifHtPhMc2yQgvCpCKJGM5ItaLTS8YIgEZxgIAuQEClkBAGwrRgp2LgKwZXNDlPKkFUFlWtk7DsHacJuVPF5ackVu8Eo7AYmMiZUyziJyOFwPkDAaK0FSK%2BPkOxaQaDuA6C5dAwQSq5fcE1MpNWApVgkc%2B3YFCsBbCyMEFrRZ8n5YKjIwrRWKuwvfDgKxaCcCSLwPwHAtCkFQJwJulhrBxXWJsa2OweCkAIJoPNKwBLJENLSfwkgACcOxDT%2BERFwLgZgzCGkNPoTgkheAsAkBoROJay0Vo4LwBQIBE4ttLXm0gcBYAwEQCANYBBUgXHIJQG%2BdAEhRHjZwVQgR/AAFoe1HGANpJ1khaRmF4JGQgUJkrOv4IIEQYh2BSBkIIRQKh1DbtILoZ1KlvipE4DwfNhbi2tvLZwdkFxT10WMvep9L633yikF%2Bo4EAPCEivQmXYareBbq0CsCASBL30DIBQCAbGRjACkGYPgdB8TEHXRAWImHYgRBaNcFDvAJPMGINcMZhiHAydIB1L57IGC0Gk7BrAsQvDAHBE1dd3BeBYH4kYcQum8A6n6qXEzZa1xGIuFsJtER8QFtg1cWI3wFMeCwJh18eA52mdIKXYgAolC1gJIYYAVwjCtpWFQAwwAFAADU8CYBUvwktTagPCFEOIcD%2BWoNqEw/B/QsWUDWGsPoPA4z4ArFQB67IJnH0YlOLWUw1bLBmGXeF4grj12QBWHYIxDQXC9imH4Z1YQIhDAMokZ1RRa45E8B0PQK2GjzGGEt7o43egTDaOt/Izqxv9QEH0VoO3Ft6G1MdvIM3bBHZu4sNVqw61gbQxwItpAl28BXUcQjz7JCvvfWRswFHcB/to8OpYDHEsrDFEwLAiQ9SkA7ZIb1/bDSSA0JIMwkhbQaCSP4XtU6OAztIHOxt3auBBF7YEenKQuBJH7f4P7mGV1ro3c2xLu6D0saPbhs9nHuPEBvWwTgLQWDKkNI%2BvyzJbJcF7bSLgPqf34CIINgDEGCugYkNIErSgyuwd0PxxDTBkOme%2B79/7WGOA4ZPRcMmMu5cK/WbFp1qv1eWUoxKVINGG1mHh3z7dzHWMB5o%2BerjUf2PwOILL%2BXSveO9q4InGgtFDKUDE7BuTUnVP54U0p8bqn1NuM09pzDemDNGe5qp8zsWrNlvwLZxw9nMNOeQC51T7m6iYe87564/mthlqCyFpt4XIuYGixZuLJz%2BfJaYKljLWWcuqfyyBorRvZClZg2W83lWEvdasJYOrDWRvlpa4qTg7WkqdZP9YPrAOBtDca/ti7fgICuGm3oOb5RdtNsa4Ghf9ltgDshXsRgzs6gDtLsjtQCP8GgrsBh5sFgoDnt%2BgED7tICltRs1gNgvsKc7cudOADYk8PcU9vc1cfUoctct46NQ9GM21SBkdUdKBvsqcadVd8dDQ2cJ0dgCcidJBnV7dudbBecmDmNBckBj08MY9xdJctgZcX0WAFBlR5RlQVdaQKRxhNcYdZE9BN9CswMd9IMTd98dAQAdhSBLdrdUMiCMNYMV0nc8NXdE8VC1CNCtCdC6J/dqN2MG1DUEdw9d1I9/CEh5C48Rh1DBUXRNDe0XQfCXRlCjdBNs9RNxNJMFNC8sjFMDFS9Qty9BBK8dMW9MB9NDMxB69QtG9LNR8zMbMDsO9YMu8e9Qs%2B9PMy1B8pMR9AtBsJ9eAp8M1Z8m8F8Qil8V9MtssuRcteAjCDditd9zDysrCj9jAasz9vNht0dmsGgTMLR7RH9et%2BsEgdcT5L9zsJtv8psTsnt/8Fs3tSAttsgEDnjShUDADoCeg4DMDbi7sYDP9kCcC7t4C/izsXsPjbt3s5JPsJBbdHDl1SCUi9JPCjh4jtCIxxhaCYcG16Mw8mMkdMAUcRh0dPNOCQAzBVcdgdgkgkh8d08NBqTB1ghRDOAedN1EcMcQACdaQaSNAh0B0ghAgJ0zBnVPMdgESAc2T8TmDPNv1OcnDpTJCVhwtMhnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/observe.hpp)
- [unit test](../../../../tests/unit/varybivore/observe.test.hpp)
