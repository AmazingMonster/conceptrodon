<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::RemoveTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-remove-types">To Index</a></p>

## Description

`Omennivore::RemoveTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices and returns a function.
When invoked, the function removes arguments from its argument list according to the `std::index_sequence`s.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
            Arg<sub>0</sub>,
            Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
            Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
RemoveTypes
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct RemoveTypes
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will remove elements of indices `1, 3, 5` from `Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_sequence&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `RemoveTypes`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = RemoveTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<2>, Vay<4>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `RemoveTypes` is similar to that of `Omennivore::Insert`. We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

We will use `Prefix` to enumerate arguments like in `Typelivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct RemoveTypes {};

/**** Base Case ****/
template<auto...I>
struct RemoveTypes<std::index_sequence<I...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Capsule
    <
        FrontTargets...,
        BackTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

template<auto...I, auto...J>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Capsule
    <
        FrontTargets...,
        MiddleTargets...,
        BackTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template
    <
        // We use `Prefix<I>...` to enumerate `FrontTargets`.
        Prefix<I>...FrontTargets,
        // We drop the next argument.
        typename,
        // We use `Prefix<J>...` to go across the distance
        // between two targets.
        Prefix<J>...MiddleTargets,
        // We drop the next argument.
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> ExtendFront
    <
        typename RemoveTypes<OtherSequences...>
        ::template Mold<BackTargets...>
    >
    ::template Mold
    <
        FrontTargets...,
        MiddleTargets...
    >;

    template<typename...Agreements>
    using Mold = decltype(idyl<Agreements...>());
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEv4apAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWKkDMz8QRkc9mGxSLdMgAvTAAfQIZKuaGxTwIVJpdJhgXutwIxC8mFhViuIL%2Be1ubiYqQUXnoDIOTJZbKYHLhXJ5rEwADpnRLLhM1Q59YbjfRNeTrpTsKpmQx0AAxYiyM1nEHM1nsjW27mMB3Ox2u91eT1BkPhyOCGEAdishfufu1VzjVptbirCc5yd5TpdgWwt0hTAUnw8giYEQS/LtKbYaew9DYggUGdVWdlOdcEdk%2BJ7LX7xHxY5ZjAICjTZNbGOLINuJ5VlvrSftI%2BdUUwAHdNxOd67T7cvJkjLcALKedCK5Urn2kTrnCt4PuO267s6/KPpBe4HoEWrAqW5bAhSAIYd8OqUgAkvGW69o00ZArqmEAkCsbntaia1o2qYtuiVyZp6ABKLKoAAbpgAAqyafCYR4oYh/q6rcFidpgXpKMRlHxtR%2BJMAiqBpjh04erKbEsJxPF8fiRIgCAERYKoIpKAAjuq0r4jh8Hoge2pHlcr51vJTmnvix6vqeOw7LcADqknvpJJgAGwaNStJ4Ko1lonuYUqqgtyMD4CTUTCYWLoI3GtMAmDPmF6ZuV5cqRdFcKqa2aaZQQ2XELlO6kJ5xU%2Bf5knoJGqQqggkmRMGtw5SlgiFZcxUnkOTaNUVXnjfRjricgADWtX1VOU0vqecyOMg7YCBMmAcWI/VKbceDoMitAQMsTW3AAtGiXpGiaGprXC12vtVy15VBjqTSNo3zUtOVfXuL12Uh10uTWM3Xo6lzADSBHPvZf0nu%2BETAN%2Bv7/rcWCQkOECned%2BJwwjT7fWil1XcJDlltTaGXJDNGKUQKn8szynOgAUmps63Jp2m8c8U5wvphmhpgJnmZZWzWbZ/Ki0ZEumZgFmvDRnO2a6AlIc5VEci9bhvd5vkBW%2B0mheF8pRTFlUuvFRBJQwKXEGlFsfUD%2BUaMNo0lXSNvYFV%2BY1R7Ci/T7LWm%2B1qCdQQ3W3L1soDU%2B3ujdDmBh6NEeBebYURX7cLc7b6b24lwCJUwyCRl2XVtXgcxWVNr4tfEBB3pgjAqneiWTCtKfFXn1sF7Fzpfqd6D0J9DVGyeWc4x1NfxxLid1YNBB99NdF8tPKqb82c0V4DdVfdd60npteDbVKe0HbQR0O4TF1XVNd2tg9PrPSjiqG43p7u0fO5pgzsVUexIJ4h0AdvAGk9yag1QhDPWNE05phJu3Mmp8zbo0xrQP8sJlS41oPjB%2BxN4aoLggxSmcChLg3QgcPmmBkAbEyFxKSkksKVgQQpJSrM74c0dJzQcu80wAHlY4JCECraWHweasXYlxQWUiRYEHQAZRWksJFq1lgxeWSiVHizUarKyBc5a3BEd1Yg4iDFbHJsjbW8C5L60/h5H%2BM8TbZ2CrnK2ZU3AVQDnbDQCVHbO1dhlIO0CLbr1fAPLxPjA6yGgUArys8o4xzjgnfqK9k7bzTgkpurizbuMtqVfEhdfHF38Q7Mu/VK4ZE%2BKInGdcWgN0/rk24Lc24d1bt3cB28onFOHo6EB48eIhxycbVqc9o4LzSUnbcETTzZKyYI50UCQ4n2Rq%2Bc%2Bl9drMhvjwk6Z1H7XRfm2ecoZqprO/s0%2BZu86FaTkbpOEpixHqOlNYxiVyTwGUZlg9A%2BIVn/zeWs95r4vkIJ%2BRc7ef9e7QW3oMsBAKQaOIQtQz%2BjMGxXj3igxGwtgWnjRp%2BH82Dsb4MIQc4hpMyHplbBQumAlaYotImREigZVCsDZKwxk2EyJsPppiCEUJgpwilFsVISN3lctoQANSYMiGS7D7FM2Oj4kEzFZTStRA5CwAoWhbR2gwPaqhUjED2TfdURYLCqSoUWelIlKQGkeqaHlaLLzDj3tI2U9r35wJoXqL8eUmBUC8NiIiTqOEuqbMguqOKQT4oxn6logbg3ZGxvze5QsMSvSmqLFgTAFqilUcrSxNEuBogSdm3N%2Ba9GFskfiQIN0uD1tLddcteaRQFqlhouE/gbp1pLTY5GBlCW/LhJcKNmtaU%2BtuEILwqQiiYHQGxH0soeWxqnTOudC6PgmllLgt%2BT18TqvxBoUttxD1wjMCes9bhJD7jBrau4i7t1ysuKux9BDsbxoDUGhw2QD0yqPZe/9cJG2tn5Fei9oHT1AbcD2wDqI4Q3sg1em6/hb3eoDHcbiHxl2cqYjqi%2BIpOxKDaBAUWCgHSEeFm4ads6MjzrfQQfkDG0RUwsBwVYtBOD%2BF4H4DgWhSCoE4IbSw1gBTrE2MFMEPBSAEE0Ox1YC0AiSEdBoAAHGYMwABOTTNQ1Oqa4IWQs0hOMcEkLwFgEgNApF4/xwTHBeAKBACkWTfH2OkDgLAGAiAQDrAIKkBE5BKBoFZHQBIUQHScFUKpkKN0QqSFuMAZA20pCOjMLwedhASCnT0PwQQIgxDsCkDIQQigVDqFc6QXQXBSB3hdqkTgPAONcZ43JgTnAhEIn87KVAVBbhRZi3FhLSXbgpbMLcCAHgQv0GNZiLgyxeAua0KsCASBgupFC2QCgEA1sbZAMAKQZg%2BB0GZMQRzEBYitdiBEVoyIGu8Cu8wYgyIhGxG0PQlz0ngtPiEQwWgt2KtYFiF4YABpaC0Ec9wXgWAc1GHEADvANIf1cQh/xiW9CETbGkxEZkJn%2BNIliC7J7HgsCtdVHgCzkPSBcWILEOjjwYfACREYOTqwqAGGAAoSV7w7xCJ5Hd4rwhRDiCK7l%2BQSg1Ctaq/oQwxhrDWH0HgWIjnICrGjo0CHN0iS4NMCJywZhbPU%2BIKdD48BVh2He9kFwoZph%2BGq2EfsixRjVaKFkAQNu9Au8aAsEY1QegW4EP0KYnhOh6HNz%2BgPkxBgO596HyP7vqtzDaN7yoTuzfia2BIJrHBuOkBs7wOzfXouxfi4l5LymxsQFwJlmbUn5syZZ6sbqTAsCJEuqQRTkhAiOk04EIzGhJBmEkGFDQ/gQqaf0JwMzpALOBC4I6EKXAQqqc0/pkK/hJA1B7yFXPrW7MOac/X1zy2vMrZ851gLW2dvTfC2wTgrQWAcULDdJg7YDCfi4Jpx0c/Uf4CIEb5R1Wou%2BWwu0goupWEuFWugh2tWhod2WeOeeebWHAHWfmCItwPWheA28WHY7%2Bn%2B3%2B42k26202MIYIZgdei2bmp%2BV%2BA4l%2BqAU2owOB%2B2OmKQNABCCQZ2F2FWD2N2/O3BT2L2b2Dg/OX224P2f2rWgOwOoO4O/O0OMucO/G%2BAiOjgyOrWaODCzI/O2O9QrW%2BOhOyIxO2w/GZOFO0m1OtOSg9O8h6MLOfA7OnO3OvOjA/OQBQuhWoBsg4B5W/GUB0uzOOuVglgCuSupuAmoq2QGuWuSoAR1g%2Bu%2BehuxuyubeYejQVu7gwe%2BQduoYyeSwzuGQruOQGRtuaQ%2BRXu0eKevuKRfQceRRoe9Q/uTQkeORTutgNReQxRieUe5QMec2awGwGevRJmCBu%2BnAmBxer%2BMuI2eBKm42Vef%2BJBs%2B5BDepATeLelAWeU%2BM%2Bn%2B/ehY/gmmhmgQA%2BQ%2BG%2BO%2BFWe%2BtgB%2BFBx%2B8Ap%2BvmXWgW22dBRBYWEWHA9%2Bg2LACgHE20HEH%2BjoCYEw6Wv%2BWWABAuwB7hAuXhkuIAwQMB9WkO8BLWZx7W5%2B3WvWqgHxXxPxfxAJsoE2TxG2CxgQSxR%2B7mq2BJ02Dx1BiQ3xs6IovxmmIouJIoGJoBx27BlAnB/GfB/20mPJAh72whdB32v2/2ihmAQOIOYgMhlOchsORhUOCOFuqhFW6hGOWhggOhFWehN2hhpORuphvA5hdOLI1hzOpJbOTAHOXO94ThvG0mrhBWEgHhJW4u3hOgMJfhsuuuNg%2BOSRqu4Ru0nAOw%2BkMReuBuCQ/%2BJuKufu4efgEArg8eIQ2R5RuRJRxQ2QSZnu2QzRlR9RcZge7QtRCe%2BZjQhZuZseAwSZnRFZvRCg6ehWiJpxtmoxrJtwnx3xtwDJ/x1EEwsxwJNeixC2yxqxowbeJmmxIAWmjogQgQ/gyQG%2BVms5hYS%2BzZ%2BenA%2B%2BzmyxHe/g3eBmhYVmqmkgOmXA6mZg2%2BJmgQSJLZ9mh%2BS2WeaWa5SBw5R%2Bqw1OmQzgkgQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/remove_types/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/remove_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/remove_types.test.hpp)
