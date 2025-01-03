<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-conjure-set">To Index</a></p>

## Description

`Typelivore::TypicalConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalConjureSet
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalConjureSet
{
    using type = RESULT;
};
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = TypicalConjureSet<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will traverse the element list and only collect each element's last appearance. We do this by only collecting an element into a capsule if it will not appear again. Then, we will concatenate all the capsules.

We will expand the constraint `Prefix<***>` alongside the arguments to skip the examined items.

```C++
template<typename, auto>
concept Prefix = true;
```

We check if the element we are inspecting will appear again using the following static member function.

```C++
template<typename Inspecting, typename...BackArgs>
static consteval auto idyl
(
    Prefix<I> auto...,
    Inspecting,
    BackArgs...
)
-> std::conditional_t
<
    (...||std::is_same_v<Inspecting, BackArgs>),
    Capsule<>,
    Capsule<typename Inspecting::type>
>;
```

In `std::conditional_t,` we check if `Inspecting` will appear in `BackArgs...`.
If so, an empty `Capsule` is returned.
Otherwise, `idyl` returns a `Capsule` containing `Inspecting`.

Here is the entire implementation.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<typename Inspecting, typename...BackArgs>
        static consteval auto idyl
        (
            Prefix<I> auto...,
            Inspecting,
            BackArgs...
        )
        -> std::conditional_t
        <
            (...||std::is_same_v<Inspecting, BackArgs>),
            Capsule<>,
            Capsule<typename Inspecting::type>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::TypicalPaste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::idyl(std::type_identity<Elements>{}...)
            )...
        >::type;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCD%2BGqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BflyBdpgOmfWNBMWRMXEJSQoNTS257bbj/WGDZcOJAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAGYwshvFhbiYwW4vI5aIQAJ5w7Ag8wQhhQrwwuFuZBjdBYKjozG/I63ZTETA0VRfQ5AgiYFjJAwsgkEFHPZhsUi3JiI1Dkq5oHFPAjU2n02Fg%2B63AjELyYOFWK4gv57W5uJjJBReeiMg7M1nspic%2BHc3msTAAOgdosuY2VDh1eoN9DVFOuVI8DQYeAAbiR2CAACo8vCiWjKJhjTDGs4gvkfZJMLY61AB4Oh2EAdnVwKuLLZHNVVp5jFtDrtTpdXjdkeS0bEcYTBas%2Bfu3o1vx2tws8cTuqUIB9pfNlrc1urbGpGYA1ph3LImPNiPWlY2pc3W7H49O48hl6vBOvwpuwRiNYWQbcH7cvOkjIqq3KFcfTx5zxve8Du3/TUBwAJS6DZ0iDEdh3HPtLknctMXhe9HwQi0KxnKtU1rdFbiheNPh/BoN0uUgUIfNDp1nbDHWvPCDAUQi1w3GxyLfG02FrbB6DYQRnQFNjqJrB1uNZRgCAsBQyKuR92Lne0HQAeQIBA4gUJCb2dbcmyjGN22nIiLziYF4VE3iCGdHDrwFQyWIJMzxMkqzsAFZTVOIBRnMxO8ZMfZ8wmAOSP1uPc9MPVVfIfAk2Nk2zLxMtwHL4zyHQFJKJJSutrJix83LUnDIrlbAQBAWcgMAsEi28ns4K1AF6uTSk7gASTLMTz1qBgkyBOqGv%2BIEQUojChM4kSePE9TrxBBsdJbGMf20DZMCETACG8otZKGrksNtJ1ZJmqVHmI2hOxMCqqsKrb4XSAAvTAAH0CFrZq9sfA6HlW9daAJYkSrCLBVHupQAEcVQlAlmq8qbCrOjbZNQs1EMrDjE2ahgFGebojAFEaFLtIcT0uYhgEmzT4behpHGQPCBATIMxEFYVbjwdAUW%2BwrZIgHLyZpOk8FUCHcKFIha2ky5yfJtGMa6Rxse5%2BGCcXImSYK8WJeWeWAFpcN%2BlABHwTqxEe%2BXoo5iWIBw/M3DOtxdbwBQgdte6gwh9HMdl4ABUV5XSdWeXYo9Q0MPRMWJfh3V9SD7aUduKX3YCkqyuhtXyfJSq2LOnt07gzbEfQ6P5Neh93oACRZrAuthzOgMuvPp1uh6nodF7k/27SpTLklGB%2Bgh0D%2BhgAaBzBQdeDDIdojFW8fKuzYffzX1nYL/UMXNaRK0K23Ck3kNn%2BGsChMrd85/2JaOr6e77kAWCYZd7v%2BzBAZBsGtkFqap7D8m/tZ2gIF12c74ro4bk9lxqCFJlXbstYNZH0fMsVWYd0SJyrP%2BWS1ds7FhTk%2BF8gVF5wgVJ3CuF8SrX1vvfR%2Bw9n4YQbqgKgtYIDpQUBrN%2BxVSrIPQWgi6vo%2BrfE1FSbAqhWDskTDwpq3CTQ%2BixJCaEiYCTii2MkAg4Dap%2BkDkaER8E67DR2qNLKml3oR09BWThWpbhCC8MkVISh0BgU9FKdR89ApmIsWkFcNjDRSjwe6SOXp4RhAIAKPxewAmCAOGnYxVI3G0DsUyEEDjbiRI8fKEKukxALSWitNavjBDBIIEE5mIS8mBL2Ig1hzwa5cIOCFD40TxFXDGBaaM90CJxAIL/XuJUFBO3jASBJAonGWNcR8dx6ImEWA4KsWgnAACsvA/AcC0KQVAnBraWGsLcBQ6xNgyPBDwUgBBNDjNWIuEAUzJB2g0AADjMGYfw/guBTMuRcrg%2BZ8zSEmRwSQvAWASA0EkOZCylkcF4AoEASR9nzPGaQOAsAYCIBAOsAgyRETkEoGgNkdA4gRFtJwVQFyABsms8WSFuMAZA1MpB2jMLwFchASAsz0PwQQIgxDsCkDIQQigVDqAhaQXQXBSAAHdiB6k4DwCZ0zZkHMWZwRSiIkVShobcXFBKiUkrJbcClZhbgQA8Oi%2BgxBYQ7OWLwcFWhVgQCQGils%2BqUUQCtRi%2BIwApBmD4HQFkHlKDRCldEMIjQUSit4D65gxAUSKWiNoGWAbSBovMopBgtB/U8qwNELwwBdS0FoCC7gvAsDXyMOIJNeBaTdCglmhZD9wIsijX46oUrkTRGFSGjwWApVKjwN87NpAoLEGiC4x4ebgDIiMAc1YVADAkwAGrvAFYpXkUbGXCBjKy6QC7OVqClXy/QhhjDWGsPoPA0QQWQFWKgBRmQs2a2JHg0wqzLBmABd24gLMPjwFWJ0bozgICuEmG0IIA8BilHKHoSxhQsieFaMBgonUANDHiPy99nVegTHA1MKoNQeizBg4sODMw%2Bg/r0PUpoWGgNcDfZsrYEhxUcBmaQf5vBAVKvxYS4lpLyVnK1fQg2JBDVglIyakdqxVJMCwPECARyQCSDBHafwYJXkaEkGYSQeLflTLxYEd5nzSDfN43aPFXA8UXP8E8vFpz7kybxbRqVgLgWgr2SOqFsKLXwrlciigdrUB6sxdijgjQWBBnzJrJg9Ft0av8HaLg5zqVcafX3flC7mXiDZaupQ66eW6BdUKkV2aqM0bo9KjgsrEWIluIq5VzHguvnaOF852rdXWriDxswxq7MQvNZajz9WyBuftfqlABgjDtC4EkGgUS1Keu9b6kNUag1%2BrDRGhwUaY3iTjQmqVybU3pszVG3N26C0LPwMWxwpapUVuQIibYuya3vIWfWxtKJm3bAWW2jtuzu29qUP23bCdWt8HHQoKdmAZ1zs7fFpdEgV2yDXdyhZ6Wt3DpvVYSw%2B7D2vsWWe2mnBL292vbuu9D64gxZfcetDMtMguAHvh/lIR5iAeGPykDnVKf5HSNBmnsGCPVFJ3UWYTOEMYb6MRunuHkM5F/YRuYJR2ekbWBsCj0v3m5as5wRjKriX4Uq2FiLGhtW4FpQarEfGWtmsE5gYTwwxP6E4Jp7TYX5P5imf4F5YIFNKckPyvL1nbC2dNZC6FcKEXyttT1rzbBOC%2BdVSwBQQZqZBiq%2BWMYUW9f0ri7IBLy72XyBS9DnQIAwSCuFckANOXJU8sBYV%2BVJWqBKoj1HmPcf0JjFqx1h1PGwTNZ921vWnmuuoub716PFjnbtHuvHgg91VBEtdaNj1EAvU8pm1NztC/Q3hsjZ2pbggVuJv25gFNaaxBbc7Tt/Nj2c1FtJ8dnlp3zvVsELWnlt2/UPdbU%2Bl7vA3t9tZF94dP2x1MEndOrOowPOqnmDklpDlnhurnnDjurejYPWkehbqep1FmjsL9AjtYPevRo%2Bs%2BogW%2Bpzh%2Bn4F%2BhTihr%2BtTpLthpBizpkEzgzpkILjhnztznhqQRzuhswURmzpQfBjzqwTwQLlwSRmRrLqysXpZqXsrhPsSpHtHrcLHmFqPjrtFjxobh3ibmbqJlRtbiADcnaGCGCFMg8m7r8vofmAZuIQCpwDZmCgJqQMcpIFMtJs8vmL8hcpIHclwFcmYBZu8mCCXpYUCkbocpbhwFShYfRlYUEcsKsN2ukM4JIEAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_conjure_set.test.hpp)
