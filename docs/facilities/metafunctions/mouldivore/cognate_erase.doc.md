<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateErase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-erase">To Index</a></p>

## Description

`Mouldivore::CognateErase` accepts an operation.

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
CognateErase
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

```C++
template<template<typename...> class>
alias CognateErase
{
    template<auto, auto>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
}；
```

## Examples

We will see two examples that demonstrate two different use cases.

In the first example, we will remove the element of index one from `int, int*, int**, int**`.
Then, we instantiate `Operation` with the resulting list.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int**, int**>;

template<typename...Args>
using Metafunction = CognateErase<Operation>::Page<1>::Mold<Args...>;

using Result = Metafunction<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<int, int**>;

template<typename...Args>
using Metafunction_1 = CognateErase<Operation>::Page<1, 3>::Mold<Args...>;

using Result_1 = Metafunction_1<int, int*, int**, int**>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateErase` using concept expansion.

- In the case where the second layer of `CognateErase` only accepts one index, we want to remove the element at the index from the list.

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
        template<typename...> class Operation,
        Prefix<I>...FrontTargets,
        typename,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Operation<FrontTargets..., BackTargets...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `CognateErase` accepts two indices, we want to remove the elements between them.

```C++
template<typename, typename>
struct Expunge {};

template<size_t...I, size_t...J>
struct Expunge<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template
    <
        template<typename...> class Operation,
        // We use `Prefix<I>...` to reach the start of the unwanted elements.
        Prefix<I>...FrontTargets,
        // We use `Prefix<J>...` to enumerate the elements we want to erase.
        Prefix<J>...,
        typename...BackTargets
    >
    static consteval auto idyl()
    -> Operation<FrontTargets..., BackTargets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<typename...> class Operation>
struct CognateErase
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Ditch<std::make_index_sequence<Index>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<typename...Elements>
        using Mold = decltype
        (
            Expunge<std::make_index_sequence<Start>, std::make_index_sequence<End-Start>>
            ::template idyl<Operation, Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEhoAnKQADqgKhE4MHt6%2BehlZjgLhkTEs8YlcGma2mPYlDEIETMQEeT5%2BQfWNOS1tBGXRcQlJqQqt7Z0FXLZTQxEjlWM1ZgCUtqhexMjsHOYAzBHI3lgA1CaHbl6OtIQAnlfYJhoAgkcnZ5iX18iT6CwVGerw%2B7wA9AAqaGQ87KYiYGiqc4wyHg0EETAsNIGTFXNwEB5pRisTCkc5MW6oEHvNAMPZpAhwhFI34AEXOBGIXkwVys71BUJh5zZhGQCBRMPR70x2NxvOuhOJzDYNLek25DhFYolJkCVkCbL5oIxWJxTDx1yyAC9MAB9AgAOmdAEk1RqvFrRQRxfiASAQBEsKo7UoAI48%2BkKtwu52OkGHF4C/Wg85pzlm%2BWp9P47Pp9Oy82WglEklsOPPc6nJgKBTnADyxOIFpypDz%2BeZiLwqnxbsTcYAYsRZAAVNrATAEBRt94dgullVk9v5pVlzBxixMZAAazHxAnU/bavzkxbyCrAkmmAAbmIKVTznh0A9aBB1u2ALSVxsJFsCfFDqO46TgocbkpuO57geoHOgm/IfIaxoChCqLnNgqhpF4Rg/Ki0pvIWWaKgupLkqui7ulynpMuhmHYZcKaIYc8GmnKFrRja9pOq65IcQ6cYAFIUZq1EYVhE5%2BgQ6ABkGmAhuGkZ7L2FaJjxknSQwwahpgEaMIp1z8cpLyJiaKazgWmZsUe1zLuZrHFmRpKGVWBi1g2TZ/gwM5vHOabguC5wAOo/F4SiXAAbBo8Jdj21x9tgFYRZyqDnAiW4SgQCA/Ke7TnKgVCcpl5xYQA7oYmLoOcDRYowU7xmZc5RUivbPIOw6CFBIFeT55x%2BYFwWhSYEWNd2%2BKCf2sGJUQlUMD4v6YgVPxVWwgh1sVPylYISWVc2Sh1d5PnDTFbhjfFzpdT5Dnls6EG7sBh71b8Sb7Wmp6OOedJXretD3lNT4vm%2Bn7fu5TQAW1BAdbVZ3nDdEMwfGxlMSZRqI8hbxCtC5weMAzCYtgO04VKLFFtGBGWURyqObBibOTWdY/s2IPGe8HpaljOM4PjJnwSuFnFrxXHw09J6UVq8KoEQyhMBO9EGsjzEPaTfN4LaDrnC6Gmyce6Ys0yYsS1L0bq8GWtpnq3MXbzJPEVdjrYPQy2Hkzz0diFETAOcACyngVVcHJYKcq42WmEBBx23q%2BlaakgCwTDbvaMlydpCmGxrMVGUL3XpgGis/H9tD4vTHnknb1UrYZAMPfm74o87epyyaCuW36yucecAztDxLeq9gGkmylSd4AidYQO3TK5ocHI9%2Bg74PTrzLi6gkvidco/F73Tv5mboc5/il3rs6JcOwoff5q7Rie977LnP7tCB5X6Yh/fc40WJ7FRzHcd2gnWk6VG%2BKj88VSUlo6x3jqnH%2Byd8RTw/AAhGGdM7nGzpbR8z587XELk0Yu9sapw2eBXZ2VckK10YvLZ2O9riUiIHGN4wAESl0dvAoqWRz5Lx%2BL7ee%2Btl5uBoXQo%2BhkiF1wEShVEIiRF4XRrCEcmBJh1lwoKURCjoR4RNGYY49Jvi/BuHcR4aoiaERLBTG2QkqJuTmjkIRaNUIDkHpMNCqhWA4gJkohubwz7uyEF4NIRRMDoAAErSK8LfK%2BGDzHXAiAQck4ToSRMENCOCLjyEGLXNQ/cx8nZuM9pOJgVAsIOByFfNmbE8Y1mjCE/8iYAysPxFwZ4AYva0HQPiN4qT%2BE11BBk/xChAljwnpk1oOT6SMzcOEmJBBISjOiY%2BWJkJ4mo1engZAdpaYJAIBAf0IAFCkiWWktwHivGZB8Z07p5Ijm32eNXUhEi26YDpBVdCDj6CSmcajDJezvF%2BICbfO0XBgnA1CcMwQEyZkI1IYkveKTgBpKehkj2WSBl5IEN8gpqBsZFM5ugv55TsCVINtU8khxakgHqY064zTIWtNIR0z5BAkXsNhf03JTRvn4hGVMsZQKgWzLBOqVob1tlKHaGsqOmy2DbP/p495pyaVzHOFK5liYLkcE2LQTg/heB%2BA4FoUgqBOBuGsNYc4Chti7DYaongpACCaCVZsbcAQzCOkCGYSQAAOZ1/gUj%2BDMBoMKzrDj6E4JIXgLAkgaFIBqrVOqOC8AUCAUNlrNVKtIHAWAMBEAgG2AQTCESKAQDQNiOgCQoikk4KoZ1YUPxhUkOcYAyBzxSEdGYXgPjCAkCfHofgggRBiHYFIGQghFAqHUAm0gug5jFWbGkTgPBlWqvVVa7VnB6y3CzblfKpby2VurbW849azDnAgB4fN9BiCXDNesXg8atCbAgEgPNaQC1kBzXeh9IBgBSDqDQW%2BCQY0QFiPO2IEQ2gPCnbwADzBiAPHrLEbQNz43mrzQ7esDBaDAeHVgWIXhgBuDELQGN3BeBYBjkYcQaHB6wbwNeaR87ZI3NuPsc14SGjzvuLEZsEGPBYHnVyPAwb8OkEo8QWIBy2RYkMMAe4RgrWbCoAYSFAA1PAmBio/g1eajtwhRDiF7epgdah52jv0GJlA%2BrLD6DwLEGNkBNioEZDkPDH4AS%2B1MJYawXreCoAE8QJ8VGrO9HI84CArgZh%2BDmGEJYFQqiFEyNkAQwWovFByMMCLqw/MIuaAsOLcw7D%2BfS4MJLoxqjzEGJlor7R8srGqJsI1Ow9gSBnRwNVYb52RvOOuitVaa11skA2/duAW0nqOFwc9FqpObEykwLAiQ3ykFtZIQ4jpkiHECJIDQkgnURQ0P4MKqQVUcEDaQYNhwuCOjClwH1yRnVnf8JILg/hFthSa8OyN0bY0jYTde1NN703LtuOQSgz7j1FrYJwNoLBryBA/EwGm58uDJEdMdrVzaiBeaknMdTXatPSB00oPTw7dB1HHUwSd%2BH6uNfDe5xdP2mR5QpMQMHEOofVhh3DhH%2B7D33uPaew4GwL1SaTbe1AR6Eh/dzYLjnYxQfg4/Ezt9yQah8DoJiYgP6/3DrA0BkDpB1cQagzBhwmuEM1SQyh%2Bd6HMPYdoLhzXhGxMka1fgBEeTKN4cR6oWjmJNeMd21qljbGHgcf2Fq7jvHzUCaE0oETRHxNuz5zJqWCgFNKZU5r9Hmme1Y9kLpodWr8eGck85qwpmWOWemzZpo9nHMTwL65iNnnvMl6q1VNLLgNIlbC%2BUAr8WYu5E8F0LvTRyuRay03poo8SvZbS6PQfKXsodF77MUriwO8Vbq1sGrPbSdzqe5wWn9PIfQ/drD%2BHjoNC9fwMjrnQ3efvbG5gCbYxpu7f24duHq3Ah3cCIEQ4a3JCVrmOThdKNWwV7S9RNZNNNDNLNEXAHQtYtDgUHTdFgBQa8c8a8I/eUSYJtc/VtVHPtDTbtCQDPftHHbPHQEAP1QnYnadf1BrLfCNSnTNW4VdXfRA5A1A9AtiWxA9MXB9LnQ4YbUA69AXIXR9f7Hg49EAFArxO0NA5IO0DAmlBArHRXb9SgVXLVbXVDc1TQ3XWDA3QXRDZDVDe3TADDLDHDPDc1G3YjQPAjMjJ3KjYdGjZAOjT3QQJjYdX3IDAPLjLzEPXgMPYTUTYjGPd7PgWTBPRTZTZUFPWQDHdPPArPfTcgvPYwEzGwYveAazWzS8TgcEf0avSwNzbVOvLABvVLJoFvdwefELEIDSafQrIobvErJogfcLTvYfPoAQMfGovQCfUfBYBovojLXorLQY9olfIbNfE1VfXbMnZrHfJQ84JAlA84WQx0BQs/frS/AQ0bUgcbSbSgerZ/EAMwOHQ4Q4fwd1G7DQDQC4wIH1R7egoAmNONPY2bQIBtd/LgKQZIN/RbLgYIXbQ4OginIAwQ%2BrRtJ4sE6/K9TYATLIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/cognate_erase.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_erase.test.hpp)
