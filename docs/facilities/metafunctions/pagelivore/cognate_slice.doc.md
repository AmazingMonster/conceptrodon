<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSlice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-slice">To Index</a></p>

## Description

`Pagelivore::CognateSlice` accepts an operation.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked, the function collects all arguments with indices greater or equal to the given index from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all arguments of indices within the interval from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSlice
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateSlice
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};


template<template<auto...> class>
alias CognateSlice
{
    template<auto, auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2>;

/**** Result ****/
using Result = CognateSlice<Operation>
::Page<2>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2>;

/**** Result ****/
using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateSlice` using concept expansion.

We will transform variables into types so that we can avoid defining the bodies of helper functions `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

- In the case where the second layer of `CognateSlice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to enumerate the
        // unwanted arguments.
        Prefix<I>...Unwanted,
        typename...Targets
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};
```

`Prefix<I>...Unwanted` tells compilers that this function template is only allowed when `Unwanted` satisfies `Prefix<Unwanted, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateSlice` accepts two indices, we want to collect the variables between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<auto...> class Operation,
        // We use `Prefix<I>...` to reach the start of `Targets`.
        Prefix<I>...,
        // We use `Prefix<J>...` to enumerate the variables
        // we want to collect.
        Prefix<J>...Targets,
        typename...
    >
    static consteval auto idyl()
    // Note that `Operation` is invoked by values
    // extracted from the template parameters.
    // This is because we will pack every item
    // of `Variables...` into `Vay`.
    -> Operation<Targets::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Shear<std::make_index_sequence<Amount>>
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
            Incise<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Vay<Variables>...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMwQAOqAqETgwe3r4BaRlZAuGRMSzxiVwptpj2jgJCBEzEBLk%2BfkG19dlNLQSl0XEJycEKza3t%2BV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZiSEWQ3iwNxMSTcXkctEIAE8YdhgeYwQwIV4oTC3MhxugsFRUeifocbspiJgaKpPgdAQRMCxUgYmXiCEinsw2KQbkx4ahSZc0FjHgRKdTadCkncbgRiF5MDCrJdgb9djcAGpMJH0/aM5mspjs2ECojalp4JixejCi7jRUOS0otWBCw3WaOZA3UXjTCqVLEfmCm4ANzESuh7p1xGttuVgTuKujyaSqqB5P%2B2a%2B6opAEkWfQ2IITdl9ac8znq4Cq/sbkIEJgWhXDUWTcrYZzuaxO2jLo6vM7G83gyZ3eO0xngUz26a3JkAF6YAD6BAAdJv8/bB8Omy08YSQCAIlhVCulABHJVivH5zfr0lJftAieXG4f%2BVGtnK9%2BfvHAp%2BQFfnOnZuOaqAPqivoGAoHwAPJPMQZYCKQgHAR%2B2zbDcADqmA3F4SjQgAbBoVI0ngqh3qiUGkfKqA3IwPgJB28pNuhGFYQRDAAO6GEy6D8sQwDMYICiPn%2BGHkbS1HPg%2Bci8fxmDoGhknAd2jC9g%2BAAqLTAJgBAKBxMovkBXp4D6fpMhGtAhhaeDoEitAQEsxlcVEqBMmxJokRoiEsQ0DAmHReAfBEYaoAA1spNyxHqNlKkZalcQGCpMA4MVUMQqAsGx%2BGzsaXmpC0vZMsQ4ludh2kIKFNy1fEoiEfhPHNXQtnFcgkWMWGCR6oQzKVTcqBUL5sbxvQ4mbsFGh1YIDHTTqKKkRJFxAQAtNB/nIYFeK6cJBkKMeCWYFBz4quiSbnWqWb1vmWKhfhuaXAVP4clymm8vK708n2wK7hKd2vER45WJd6ZkhcL0doeeDLmuD75nyS6rhum4AFI7gqQ4A/dSiHgQ6DHqeAYXpg14vGB95Tc%2BSME0TDBnqT5O3rCaOnWiZ1uhmQFQ%2ByakAWpPPftDZqCuzMFMHBNxbShDCqatGE3FxeEEcDpHSZRsnYLRM0WtS6UIHlnoTBKw2%2BXt%2BmGdNK2K5KFFUbC25yZu8u28r%2BFNb5GsO24GPO4%2BdEWkxbDbflTbhlaNoTcZQFcS1Nx8YI9G%2Bp49Q24r3t4n72ubhbB2u4rGk/VB/OcwrH7mZZAj%2BjZdkMQ5TkuYNHleQQCA%2BdNMs7SFYUMBF0WCXFEfeO8g2pchGWCVlOVG7z%2BHFchbBlRVyVVTVYUfA1ApEfHPFtTcHVdZgPXEH1s6DWbC2Rwmk0BzNEQWlfS0aOnH4bc%2B0tIbLu16QdR2RidamHNpxg2nDdTUHhgDMCZEIREmxWwzmFvOOeeIILiwhJLBCX8dpl3%2BjcSB0DMCwIsr%2BV83NPwoNhMjeGQDjJ4KpJ5VAygmD6WjKDKcEMhagRhnDCUFwWBrEEPaMyWNnQMKIMw/SeJ%2BGCIIMI/8b5y7qSQWBNBm4xpR1HmXW2hEIjAEpCw/CMI5RYAhBpGOn4IAWIwiOA8VC6YgBYEwaKK5ibnivDeTY0iBFeCEWdbRttPzHjnnVRytA8Rd2yHyRaeINE3xokApugtPyuXBvzUBnCKEqJ4SjBsJskaw1ydgBm8iPzUmvHgakHwIB9FaDKNwxibjFPQK5NS9DsoSMMXiWpBA%2BTNNKWw6xIFCqqLFuo6%2B0cAkYV0UYAxrDGmmNoOY5JH4rErOAoDB6%2BNCaOOcauNxTNPFgR6aiWmOynEuIOR4imeJmlrROf40ygSPzBJUaEpyETsFRJdLEiZWic6PmfEkpRQFUnkI/JOK6mYlGUPAmM9cFxgDUmZIwK2UzVZ6LmUY2UkpGGSLAoi5FJZDLsyhZCtJ0KNTVhOICDUNwABilTxhNNUKwVkj0GR1mpTSiGGJwSQmxfiAQmxUhopfFyz%2BAVyxPUhtk0WRBSUDlERKSJAgyXgIbF4VI6QlDoAAErvC8EshBlwZn6KEFqnVykDUKCNRKRpqqgqwjMHyMwT4wFXApDau1JqLhmpuN641jSCEdmIV42Ejr7THnxXiN1Zdo1dNhBoPkXBXWuvdRDOl2l3gShlZXFcmCEgEAgEeEAChewFqMrCC12qMjWsNUsvkga5HPjBZm7l2ZaUUiEJgUUglsCsqLByg0XKO0AnbbcGtVr9UNtzZy01mRZlTrrTO21SyVxcBlHKSNsJU03DjcAid9Zm2%2Bv9c2jdW78GoCgaGuBYEd0vgTVI3dfIkhRpADGpNKa037ozddT1txs3Mrzc0b0lalCtBLQ48tbBK3dMtSu89e6kOojBRwFYtBOD%2BF4H4DgWhSCoE4A0yw1hPRrA2EY0EPBSAEE0OhlYkUAiSHXBoAAHGYMwABOTjXB/BsdY1wQIgRpCYY4JIXgLAJAaGTbh/DhGOC8EOsm2jeH0OkDgLAGAiAQBrAIKkeE5BKBoBZHQBIUReycFUKx4ia1iKSBuMAZAPopDrjMLwZShASAOT0PwQQIgxDsCkDIQQigVDqFU6QXQqaeLIVSJwHgGGsM4bowRzg8F4T6dNiNKzNm7MOaczcFzZgbgQA8CZ%2BgY4qNLF4CprQKwIBIGM6kUzZAKAQCay1kAwApAupoEshIh0ICxBS7ECILQkTxd4KN5gp94KxG0L2lT1HjPEvggwWgE2ItYFiF4YA4FaC0EOtwXgWAnFGHEFtypi28A9SO/hgMvb4RbGow/OoKXESxGQqfDwWAUsKjwJJ47pAT6xDrQ8M7wBERGDoysKgBhgAKC1G8Hi/lcPUd88IUQ4ggsY9C2oFLUX9CGGMNYaw%2Bg8CxEOpAFYqBRXZCO2tQkxjTAkcsGYOTJ84xYCpy5bo13nAQFcFMPwqawgRCGBUEYqadXFByJ4DoegZeBXmMMKofOHC9BNsLvQdh%2BcMB6SryXavZiTHl/kVNJuBji4WFLlYChyObAkIljg2HSCyd4PJm4OXbP2cc855jxWIC4E85VpIXBqs0ZhysfcWBEi88Y5IJI65OMpEkBoSQZhJCkQ0P4YinH9CcHE6QSTYf1zES4MRVjnGBPEX8JIXjKfiJu5S/JxTIBlMw/U1phrOmMsGbax1ir5m2CcBaCwMMgQ1pMAlrMrgnH1xcBY%2B5/ARAuc%2BdkP57H0hcdKHxxF3QLqYtMDi8d53rv3epY4OlvT8IhrZesz7mf%2Bi58L5YyVsrzWKvQlBGYCPtW1M96D4JCGbtY5Sf4jAYJGBz5cDJp9bLyUDDYRbTbjaTakDIGzbzaLaoEraoprYbYpbba7b7aHaoGnbE4Xb4b4DUga63YpYPbIBPaoGvaib4YfZfZIg/ZbD4b/aA7UYg5g7MjkF6Kd5w4sKI7I6o6oEY6b6Bbb6yB47hb4YH5E7Q4s5WCWDk6U7wA0507VycCM4EzM6k5s4c4JBc7vDaHq6BQuAMza6i4MyG6LDS5FCBR2GkBK7ZCOFS5WGa79BuG64a6NAmxeHG5a5m4i62DBHW6q5O6rDrCO7h4F4u7JYRae7e55aQHP7z6L4zRB4r4kDf5h5/5R6kAx4jC86iZF4l7z7p6BD%2BCcZCZJAZ5Z717N6pGcBt4d6qb1bd5IC6aZYgFAHEDD5bBj55YsAKBhg%2Bhhgv4/jjDL4h7eaprSFY6yHBbyC76KE6AgBJCkBH4n4JZJHn4t5pZ95ZZe7jGTHTGzEdjMqlZgEtaFFJDFHdHqaNYPEVaDEfEjBTHaorgzGcYrhzEEAriqB2Z8B0DwFDYjZjanyoHoFIhzYLYODYE5SrbrabaUGYA7Z7ZiAkFA5kHnZcEnZXY0EWERb0GMFA7MHvYU7sGcF/Zxi8G8D8FKDg5CHQ6vGiEI5I6YAo7chSEb6rESByEhabEE47EqEk6s42AfY846GBRHbbBHhqHWDs4e6c4OQWHU4%2BEC5C7hF6Bi5lAxHOGZCuEGmmmy4hE651B649L%2BG2mBH65RHGlG465hF5ARGW7WmJH27xGBZn4pFyacAXH2YTFTHhg3FMh3HB6r6FHh41YlFlFx7O5VEgBcbrhJBJD%2BB8b17SZZmBCV5tHBkKa2Dt6R7dEMYgCSD%2BDJ6CaBDSasaSA8ZcDsZmBN6iZJBBke4dEVl1bO5ubFk9mln/5LArAnyZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_slice.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_slice.test.hpp)
