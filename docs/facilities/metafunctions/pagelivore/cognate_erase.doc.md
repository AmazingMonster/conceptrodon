<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-erase">To Index</a></p>

## Description

`Pagelivore::CognateErase` accepts an operation.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked, the function removes the argument at the index from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I+1</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked, the function removes the arguments of indices within the interval from its argument list and invokes the operation with the result.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>J</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateErase ::   template<auto...> class...
               -> auto...
               -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

```C++
template<template<auto...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the variable of index one from `0, 1, 2, 2`.
Then, we instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 2, 2>;

template<auto...Args>
using Metafunction = CognateErase<Operation>::Page<1>::Page<Args...>;

using Result = Metafunction<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<0, 2>;

template<auto...Args>
using Metafunction_1 = CognateErase<Operation>::Page<1, 3>::Page<Args...>;

using Result_1 = Metafunction_1<0, 1, 2, 2>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `CognateErase` only accepts one index, we want to remove the variable at the index from the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Ditch {};

template<size_t...I>
struct Ditch<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl() -> 
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateErase` accepts two indices, we want to remove the variables between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted variables.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the variables we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl() ->
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    Operation<FrontTargets::value..., BackTargets::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEElwAHKQADqgKhE4MHt6%2BehlZjgLhkTEs8YlcNbaY9iUMQgRMxAR5Pn5BdQ05za0EZdFxCUmpCi1tHQVctpODEcOVozVcAJS2qF7EyOwc5gDMEcjeWADUJgduXo60hACel9gmGgCCh8enmBdXyBPoWCoTxe7zeAHoAFRQiFnACyAlQRAY9zO0IhYJBBEwLDSBixlzcTBuqDOADVWngmLF6MC3hNiF4HHCEUjHm8TIELGcJkxHMgzmgGBNMKo0sQzkSiGcAG5iLzfDkWcnESnUzAcgAily5mu1IJBkOhZ2UxEwNFUqOhGLeWJxePVVwI9zSjFYmFIEuJtNegt2aQIxtN5p%2BGrOBAZDqs7PBaLOGsIyAQlqh1tettxvIdbidLuYbG99MZAfjBETF05uoOUdBaexGfxVyyAC9MAB9AgAOi7AEkC%2BGi3GEwgCf8QCAIlhVK2lABHeUMXYE7tdjvAg7PdkVt5nHdhuv2kG7n5uQ9H3fpg9XSWoFdPAUGBQKM4AeRdxF5OVIp7PgbNeFUS5PCuABixCyAAKq0wCYAQChftuP5hs6rpsPBryIUhuZuiuFhMMgADWkHENBsHfj8G7obuPJ8gKAjCrKtCelKeDoPctAQGsZwALR3mRYJgmcUSIt8BAILyFwAGwaK%2BCQfgIJhSWceBPhE0qoPhmDoGcsQogx8oKHxAkiuGeFYlpVBgSwYYICJ%2B6ZmcaStG6WLEAoq4ITuMnvo0BKgRBUEwQoY56ZgK4erhBFESRQUgCFt7rnqm5alW%2Boxka2Cil4RjfGiqYXpmBI5ih7qYcVfYMkyGVpFl0HllYgTJdWmJ2Q2bjNm2nY9h67XtiuABS5UDlVNVZqO44MJO06YHOjCLlcy5dk83UEOgY4TiKU0zQuWZ9fFzwJZu1ZHvl%2BIeceZHHS1WbXnt95MI%2BL5vnJDBoRh/FnAA6t8XhKJJGgmn%2BAHzUBi2KVKpp4UmonfDybRnKgVDWd9DAAO6GGZMoUlS9BuRdu4A%2BagHriBYGCFFgWvYh71fWcP0KlJBP/gSA3E6DGhhiSjA%2BLJWJI5jKrY5gT4o98aOCBzZyyUo7mUT%2BjNA24LPYGFeM7kVeahV2EWEQFpFnd6R7UXg/KCvRYhMSSLFsRx3EG7u71CbzoniQp0lPT5inKUpDBqRpWk6Zj3hC4ZkuqCZDiaWcFmoFZ0N7na9mOe%2BbAubjZ1ec9vmkwQ5OwcFcqax24V4TrxGBfnQd7Yl7wNdXBqxh4wDMFi2Dvr9uXNQnrUnddxK3Sc91PhnPkHa8hZMo3zc4G36qHWRPcjngLa9Yto%2BG/2TImoiqDKEwtWKpWTVnQvjZLx1ZzdhNIp2zu48BlvRC79BS5X0DFFHgfZ2XV3vdECuyqqhxjfM8P0IjAGNHvBUBxQxYBOEVVWZwIAIKPCWRMI4VpjhYEwDSrZ1pTlnPOOabhL6TjXO/DCu4xw9yUqxWgBJh6fmZAwbeyICQAMFgZVmq51wcQQWsauH9a4pWjLLeO9ZRpn3bGcfobRuqSIDNgCawDTRzjwKaJ8EAZEBgJJcUMij0D8LOnfQM28n5Zi0R6fRwDP6iO/uIgkN0uzsLVJw8hP5QFGAgfvaBZxYG0HgV/XcSDAk/mGtldBq0QBYJwXgzahDzHzCWtyDBUTsFtliQQ2aWZ9FcS0WQ5BlCQDUKtnQq4DCBAenhMw1kbCsYuJBtw7AvCQlnH4cI0Rh9UqiJPoSPuXZXjAFNNiRgpE167g8eAsxIYTGP0gQSAZQy2CCDcqvfaTUhFH1eIaNEOyO5pShGccCQtYLJnRPXXZFyzkiI%2BAuL4x4bh0AeN6Tu9irx9MaSCYx5SGB132TCYCaiJhnAyqwXEOUrRdImdIrwaQiiaQAEpCy8P46Z3yCQaA9GYTFa5Nk9McR2V4xFXEgihbCGCTAqBZQcDkaZk9Myt3ulmNF64xxmIJFwJ4rK5lXEJcAFZHz2kkqyJ4xFChkXaJ8WSlolKFwjzcBis4swzhYuVTirpRtkCtkHgkAgEAxoKDdFqzhbghAwrhegUV4qPSWv8U8NpmztkwiEJgQUWkQV2nBSmSFwrwGmthZkBFSL/Gti4Ki92OR0XYoSoKm0V0HHvN5cSt4pLyUyupQIENtLUBN3pTPeh4b5IspAGyq4SqDicuLdytwiaq4xteFCm1BBM26LhKmqljQQ2RsVZiqNaz1UtD5EapQbQ9UpINWwI1BI/XmsbSG61Qam0cvXPajgGxaCcH8LwPwHAtCkFQJwE8lhrDci2DsBUZgDg8FIAQTQq6Nj4QCGYDsgQzCSGSMkfwGgACc/gzAaAkskA4%2BhOCSF4CwCQGgMXbt3fujgvAgoYpvTu1dpA4CwBgIgEAWwCDVQIOQSgaAcR0ASFEN0nBVDJAklxCSkgzjAGQPyKQHYzC8E0oQEgLE9D8EECIMQ7ApAyEEIoFQ6hkOkF0LMFG740icB4GujdW7b17s4M%2BG4uH4aIwo1RmjdGGOKskMxxBHgiP0HFIcdYvAkNaA2BAJAhG0jEbIBQCA9nHMgGAFILFNB/EJCChAWISnYgRFaPcWTvAgvMGIPcZ8sRtAuqQ1ewjSyCDPgYLQULYmsCxC8MAQktBaBBW4LwLAWCjDiEy2o%2BLeBpRCyUyKF1Nw9hXoiFiddYm7ixHfFFjwWAlPhjwOBorpAavEFiAGjU2JDDADuEYW9GwqAGD5aSPAmAUYyW3Ve7jwhRDiAE1t4TaglMSf0FNlA1hrD6DwLEIKkANioH9DkQrXF/i6NMEeywf7eCoBGyqLAN2OI9Cq84CArhph%2BFmGERYFQqiFEyNkAQYPYfFByEMaHKxAfpqaPMRHsw7BA6xwMVHIxqhzAGDj0nbQifLGqBsBQp7dgSHkxwTdpBoNfc4GcLT1HaP0cYwZswiDcDsbMxeiz165sbBskwLAiQAcPskAcDsX6DiBEkBoSQr6pIaH8BJL9wGOCgdIOBy9HYJJcAA1%2B5I5v/CSC4P4ZXElWdKdg/BkAiG5uoYw7ZrDambj4ZczHBzpnSNsE4K0Fg0pAhcSYHdTxXAv0di4B2XdbGiC/a47IXju3pD7aUIdsTugsVSaYDJorTOWds%2BUxwVTOGbgaYlMQCPUeY8DzjwnpP7MIDGaDwkC4F6zBrEsx773rnTP%2B9H6McPkeuKt481%2BrgGLvOp0oAFsTEWQthdIOvqLMW4sOE30lkZqX0tKayzlvLBXN8lam%2BV3d%2BBTTUpq4VlPqgGtYk3y1%2BoSmOtdfuD1vYu6/Wg2V6I2Y2SgE2pW02YCHuC2e8Cgy2q262m%2BW2We/GOesgB2omu6heJ2s2b2Vglgl2128Ad2D2dEnAz2K0r252H2MGP2LEtWt2GOjQLgE05OkO5QxOSO8OuQngnQ3BjQVOMOuO9Q%2BOWi5OeOmOWiQh6OsM7QfBMwFOCwnB1OjOmw2wDO6w%2BuFezuHOU%2Bzese4C8eieyegu%2BAaefel6g%2B4uyGawkumA0uowAObWhuxuCe6ugQ9ugQgQBwGukgNGswleLutgbuNh1mnu8A3u2GuG4%2BgejmIeew4eOmLACg0o/I0oxh9oEwrG5hHGq0swKBO2aBgm8geeWBOgIAQGxepecm2himYmsGNe6mCMDeLAyRqR6RmRmYQKXecRpmlhBw1hVmKGI%2BfRCQsRJmowaRsKrYGRX6rYWRTaSROedAy%2B/mgWwWUWm%2B2%2B0WsW8WB%2BMcyWx%2BGWd%2BmA2WuWYgl%2BQ21%2BZWABxWlWj%2BtWYm9WyAjWH%2BggX%2B7WV2v%2B/%2BfWKowBvAoB42k2ZW0BthfAi28BK2a2uYyBmeRREg6BQmZRR2lRuBxgNBNgHW/2pBjQhWYIo4%2BB1gn2e69Bf2JBzBOQrB7gCh4OIQE0MhJORQPB5OzJghUOXBIhvQAg4htJegkhjQ0hHJqhuO2OfJophOwpwhtO9O/G5e9RMGehje7RaRMoXRWIPRQuFh5mQxEupAUuMulATOrhIAZgCeBwBw/gn6tukGFpgQAGTuDRnAru7uth96IAkggQzGnhNQkgX6HhyuXAwQbWBwCp7OcGYRd6%2BuLGjpipEZwxdhw2vmVJkgQAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_erase.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_erase.test.hpp)
