<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreNoLessThan`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-no-less-than">To Index</a></p>

## Description

`Varybivore::AreNoLessThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are greater or equal to the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &ge; Target) && (V<sub>1</sub> &ge; Target) && ... && (V<sub>n</sub> &ge; Target)</code></pre>

## Type Signature

```Haskell
AreNoLessThan
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct AreNoLessThan
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction
= AreNoLessThan<5>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<5, 6, 7, 5>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

We will implement `AreNoLessThan` using only `<`, meaning <code>Variable &ge; Target</code> is expressed as:

```C++
not (Variable < Target)
```

```C++
template<auto Target>
struct AreNoLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Target))) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Target))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgAMwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnhzsmGgCC%2B4cA1ACSLGn0bIJMjbdH51c3p3%2Bn30uF0uBEwTwMoJMiTcTC8RFuABVWsBMAQodhgRNiF4HLdLsQoqgQpgFAoEQhDMCTAErFdbvTbqDwe9MFCYXDUAA6bkANVaeCYMXoCnRwIZtyxOIIt2UxFQRGUTBRYoZ1Npl3F4rmjmQtzQDAmmFUaWItxiqE8twAbmIvKy6Zr6WrbhBuZzzAA2T0QBjyl184gCoUk25sxHI1HLKOhgIAESh6vF1PjiUTqod9KZzxZbNhRDdl2ABLBjAIIsSGIzty8WSMMqVmFDiVjMrlCobbMLxdeZbdotTVKrWYhrOhea5vP5guFoqr2rwuv1huNpvNlsVKIA%2BlbQ1Xna7uZ7vb7pRAA0HhU23OHiCiCFHljGU%2BrkwnB9d/n9Ab89rdsKpWGeRsvmBH9PzOd8f1uABZVEmCoLwGAcHJPggq5hxzMcOQLW9y0rS4a3CYAYLghCkMaKlmzxAlIiJEkyQpBg2WSWdLhAEAN1HNx8WABQ%2BwrN8rlAo5ERJaUQKuedkE3JhSXiAgIFgloyOQgRmNIW4PQ0oJbhYit2JtbxMGWQTLikmS5LaCAwDAEjlMQ1SmOhLTbjMDTEnRAzbWMhMOFWWhOGSXg/A4LRSFQTg3GsawJXWTZG3MRIeFIAhND81YAGsQGSSROQ0AAOMwzAATmKrhkgK/KuACAJpACjhJF4FgJA0DRSBCsKIo4XgFBANrUtCvzSDgWAYEQEB1gINI4XISg0CeOh4kiVhtlUfKPQAWg9SRbmAZBdSkTkzF4TB8CIQN0D0fhBBEMR2CkGRBEUFR1EG0hdC4UgAHdiCYNJOB4fzAuCtLws4AB5OFpulVAqFuNbNu23b9tuQ6zBdDwFvoU1Eq4ZZeAGrRVggJB5rSRayAoCAyYpkBgCkNyaFoUFiF6iAYlBmJwlaABPAHeC55hiB58GYm0TAHH50h5p7cGGFoPm3qwGIvGAGFaFoXruF4LAWEMYBxCVvACWQq0SVBo0JbhbZkvCUF6rC2g8BiX7hY8LBQYIQNmu10gzeIc0lFjMF9adow0tWKgDF4nk8EwL7wbSRgpeu4RRHEB7U%2BetRQY%2B/R9ZQaLLH0Z3esgVZUDSRotY2iZ0ChWNTEsawzE6/2LvN8ueglxoXAYdxPE6PRQnCYYqlGT7imyARpj8SfMmnhgFhGBJPrsHu%2BkmdpB4KNf6g3gR%2BjaZfx9X2wt9nvQ5mP0fFgn1YFDirYJCBjggva0Guvh9atp2vaDtyujCAuBCAkFDGYJK%2BMUoR1WAgTATAsAJAgJlfwiROTFUSLVDQkgzCSA9K1ZIHpir6E4I1UgzUkqcg9FwD0%2BVipVQ9DlcqGCtIdV4F1HqfVoGDWJmNEmE0oYzSpjTbGy02CcFaCwK0AQNpMD1AYOsXBiqci4HlE6Z0SB4Eup9VOt0M7SCzkoHOb1dBuR%2Bn9fmr935sLBhwSGU04S3Fht/RGO1kAKOIkolReUMaoCxvEcBiQzBQMJkNfhIj4izWpn48m2MUAeKUVwNqTMWZsw5m9QWvMpaZOFqLcWktfYy1LHLBWoNlaq3VprKWutQ7bDCvgE2jgzZazCpbZA1spZ23qKDJ2LtebuzqQTb2Ut/aB0wMHPWRgw6gB4XwaOChY7x0TsnX2uj073QMbIbOr0wqmPzuHJuVhi69LLsg8KVccg1zrg3Q5Lc27xA7qch%2B%2B9HJ9wHvkOewR%2B4nyWPPEoORL5/MXj8ie3dHJH23h8q%2BLzGgQpBWfa%2BkKh5ry3vCl%2BawNjPzxiQt%2BIM3pfwRr/eR%2BtUbKNURoF0IDzqBLxgTGBpA4EINGGc%2BqZCKHKOwQEZIxUaqJBwXgyQn0bEcNsFw0JvD4D8MmtDKJETiBiO2JIpGLAFBWl1FaLxI4JjqNARdK6sg9EbMevIIxOydBJG%2Br9f62srF4s6hDQRMM4aqGVaq9VmqWQTF8f4nGEDEghIjsNUmMSKaypDXEtVaQ0jbiUZuLVBBNwuoMXQVJlB0lhRyYrZKma8k9ylkUwQJTFb1MwCrNWYgqm%2BxqVMwZpAGkb2aRbVQVtQSdMEN0t6vTXY8wGZ7YZvtRmZHGSHKZRFA1RyVAsuOCck4hWSmsu6EhNlPVNbnC1HjC7N2OaXeAFcLkCC1jsOum6jkWFbuw9uWjO5nPXq8iArhAVfPQGioFjRH1T0aC%2BsFsKL470%2Bben98xb4ryvr%2BqFKKgMVBA9ix%2BmL7q2o/vizg8NXVqutB60EXrgEaN9ZAulPDYHwMQZQV%2BbKQAlU5IkFIFVBWtSowEWhiH7XdVFf1elWVJDJHQdVAIrV8qSDKlwQqZgtL1USHa9hnB8NE1fsdJjkmWPitWP7LIzhJBAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_no_less_than/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_no_less_than.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_no_less_than.test.hpp)
