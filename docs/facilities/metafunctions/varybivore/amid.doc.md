<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amid`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-amid">To Index</a></p>

## Description

`Varybivore::Amid` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amid
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct Amid
{
    template<auto>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Amid<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

Note that `Label::idyl` maps its parameter type `Key` to its return type `Treasure`. We will pack each variable into a `Vay` so that we can use it as a return type:

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Vay&lt;Variablv<sub>I</sub>&gt;</code></pre>

Now, we will assemble an overload set and instruct compilers to pull the variable out when provided with an index. Here's the entire implementation:

```C++
template<auto...Variables>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Vay<Variables>, std::integral_constant<size_t, I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Vay<Variables>, std::integral_constant<size_t, I>>::idyl...;
    };

    template<size_t I>
    struct ProtoPage
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the value result of the return type
        // of such `idyl` is the variable of index I in the list.
        static constexpr auto value 
        {
            decltype
            (
                Detail<std::make_index_sequence<sizeof...(Variables)>>
                ::idyl(std::integral_constant<size_t, I>{})
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAbAmkAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLMAGYwshvFhriYQW4vI5aIQAJ4w7BA8xghgQrxQmFuZBjdBYKio9HfA7XYJMWK0D77AEETAsFIGRl4ghIx7MNjXAAqxEwTAUa0wpGuHK5rEw1wA0pgUSC0RcxsQvA5KdTauiAOwWaEXa6G64zRzIa5oBhjTCqFLEa5MeGoa54dBI2gQOVIxbXAC0qL5AqFIphVguJm1txDZMuFIAakwkXS9gymSymGzYQ6iNd48Q8NT6KTlQRVer4yiw7qgUbjU1TeaBFabXas06AG5iLzS8MWXP56KFiNRyuRkGhwHkv5Tz5An47a4ASWZ9DYgnTWSTJ1n053W7DF0Zy/TmDxrYAdBe%2BwW3kXziq1QRrucWC6deOa4e0xm3BLGFLbzW97qvcTR0NCVZDmO0YfqmrInrCGQAF6YAA%2BgQF5nguAFGkBj4gUwdB4oSIAgGEWCqChSgAI5dli8FuAuGGkoq1ZGlsWzXAA6tKyCBoy9oMNcqBtnEtCoEw6DGpgj6oFQ0IJBoLpuiYCniggxCrMACDOgwCBxIQhgbGerGGiA1wpF4A54GaVI0ni5b2c0/b0AoqJisRpGCJgwDEGIKEWjMghEXgyFoWKWEsYqTEGkaPYmTW1zsVx0rRHmRjXJgInEImKmKa6tC5dcVAaSwzoEO80RCjxBgKO82YEHp5prAKgjGmgjzGTFCXXF4GTpbZWqwg5Q1OdermKu5BDoCRYSMj5fkBU0QUISFqEEOFzHYDN%2BVMVBXXgaO47xZ%2BcHBaFj4RUq5yASWD7XMoGlEMoTDACe%2B1xftNZJdx9oKAA1mpPGoMydBxOKTo0AwkmGPJeXKapDXpvFX0cVgELNG89rmc0UqMnasnipy3YKR5s3eb5tD%2BY2S0EGda0bSxCmddd3WJRxC5yfwXhQ2KDXSh23jSgKwq0DJcl89cAoEGsgm/sjbEcQTwrINpuVKQVql4HVjUdnm15CXJZHWouOmA9ciJjMzrO1uuZqLdatr2o61wC12%2Bos91H0e9b1xo6LRPy91ECBz7%2BGEQhU0kSwTB/ahRsUdRtEbHTskYRAV4Dm8iybSH1vbW6ECk1582U4thi0yt50M2iEG3Nnn2s4sJGu293s1uGh3xR3w4Tt7J3HqejoYecPmYEyjDldhhq9WEwD3S93Ygrc92Pagz2vXiI8CuPggKLtaJ7YCkFHZOu7JtuNzYKorAstKM6n2fAJAia1koUKSgtBAz6vrCGhilwYozBihBKiEi696IgMVM3Tsi9RzLxBNnMcHBli0E4P4XgfgOBaFIKgTgbhrDWGNKsdY3ZQQ8FIAQTQyDlh/XyGeDQAAOMwZgACcLCuD%2BEYQwrg2ptTSFQRwSQvAWASA0H/TB2DcEcF4AoEAf9KFYOQaQOAsAYCIBAKsAgFl1oUAgGgEG9BiARClJwVQDCEg%2BgSJIa4wBkBmikGeMwvBMD4CIHmaaAD%2BCCBEGIdgUgZCCEUCodQijSC6AAQAd18ikTgPAUFoIwVQnBnAADy8JtEG2uGYixVibF2OuA4sw1wIAeAMWDDEXBFi8AUVoZYEAkD6JSKDMgujGnNJAMAKQQCaCiziLIiA0QknRDCM0JEsTeDDOYNlFJ0RtCYAcOM0g%2BjVwEBSQwWgYzQlYGiF4YAbgxC0FkdwXgWBo5GHEFsvAAoHB4BEkc7B1p5nwk2OQsmAjsGIlSqMjwWAkkljwCI45pAsrRHSJge4ZzgCIiMFQ5YVADDAAULGV4ESUlckWV44QohxD%2BMxUEtQSTwn6EMMYAhlh9B4GiLIyAyxUApHqEcn0hIYS3FMJYawZhJFZXcW8eAyw7DzPqC4KGkw/AAJCGEQYFRhgAMKJkAQoq9ByvqHMIY8QAECpuQIXoExPDtD0Jq%2BoOr%2BiSvmDK2w4xWh6ryBqy1qrpXqv5cQjYEh4kcHQaQCRvApFZPMZY6xtj7GSEccU3AhASDQjIVUihsLlh6QksMCANCQCSBBGeFhII%2BEaEkGYSQCkND%2BASCw/QnAhGkBESCLgZ4EhcASAwlh3CEiBA4Rm5IXrknSNsHImNii6lqPqRo9J8JyCUDaYY4xbBODNBYG2bUPomDmgMOlLgLCzxVoea4kgLo9CYp8Ti6QeKlAEtCboIBUSmAxOOW6j17apFpK0fCTJ2T/WLpJQU1d67imlKaYYyNIIzDRpqUogdY64gjr0cDH9wx0ZGBXVwP%2BPS8b9MGaEyZozFloembMwVizlkTzWRspJ2zdn7NoIcxZpySUXOwfga5jg7lJMecgZ5iy3lJM%2Bb5bKPzNjYP%2BYC8hIKwUQqo7PWFfAEVIpRWixgGLZB7r8Qe2Q%2BKQnYNPcSmFbKrDks%2BdSpNOD6VZEZcypemmOVcriDy3T/LaiCqyMK9w1qxWkAlWUNVSr0jyuyI59zRQsj2oWBqmzWqGiWsVYF7o2q7Wmrc7avoYWLWzGiw611Kw1gusqSW91iTQk%2BufbkmDc8V1rvoaGzddoKmAdjaQeNWB4h6YEWWitq7s3an8Cw3hIIc15skAA29nAZHdqA32%2BAA7NHaPA6BoxJiODTtySwBQbYzRtiK3BMYziyvbs8XJ7FCmAnyCPSpnQIAQSkHPZeuJmWb1JLvUOsWWS5sLaWyt48Ywv2QeaX%2BhB1SxMgfe4Yibf3hiLZSCkFCy2WEoVWwQFCqgrF8DoEhygKHsGYc2eQ1HMy5kLKBXhwQBHNk0cwDsvZByjnkMo%2BcnjJyrm2YY6EpjLGgVsdCRx75GAqcULzPx3ggmlDCfOaJ3t4mXqScwKi9FQLd07YkIpwJB3CXHfU6S9l2nKVWf0wyzgWxiKmcsJy713KXS8ppV0WzzgICuHiy5qVAXUgefqPF5Vfmku28NT0UL3nwtm5C4l1zyXYu6tyE5mYLR/MyqdWlvx17suSM4Pd6x83Fsu2e4yV7EAw1uL/ZU77va42Clq5QN1jWQCsLPCCEE/hOE9bEeX7UdbPXXf612%2BRVXaGSH8Omnh2oxEMMkOwrgTCzDJAESCGP3qm9DbdU4hvOWJ9VayhkZwkggA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/amid/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/amid.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/amid.test.hpp)
