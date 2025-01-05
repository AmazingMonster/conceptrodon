<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Front`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-front">To Index</a></p>

## Description

`Typelivore::Front` accepts a list of elements.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function collects elements of the amount from the front of the list and instantiates the operation with the collection.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
Front
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Front
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

## Examples

We will invoke the `Operation` with the first three elements from `int, int*, int**, int**`.

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = Front<int, int*, int**, int**>::Page<3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Front` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

`Fore` will help us translate `std::index_sequence` into a pack of indices.

```C++
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsAJykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCx0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bDAg87gRiF5MHCrNdQf9AdrDsCtXcAJJs%2BhsQRMJqM3WanU284Um5UgBiJEwlrt1xZxvNqvh3N5rB9GOuk2VDjuztpsIA7FYow81fbPezvQTsgAvTAAfQIADo8wbRVcQ14wxGfW5iSAQBEsKpM0oAI4qiUEg15nPkwJBkEx0F3fuK1nJzm%2Bocc8t%2BxgB9vou5QpgKL4AeRexHNuULA7u80cyDnAkmmAAbmJBcK7nh0CjaH2BxBb1v%2B7tdndsKp0oZ0LCkhoaXS8Korbkj%2BiqoPuXiCIqCCum0wA%2BIwBBfFQxCoCwUGushsgdtcj4Dn%2B9JAV2Z5EO2UzAJgiGkA%2Bj4zjhA4rNRAC0s4rgk64CFyPJTmwdxYFCk4QGRFEKCsVaTjOXYJhqcZSSClL3I6KGQT8oJJuOnH%2Bmw7bYCaCEKIWxalkpBCYr2dH9mpKbwumWZSlcLAbIIm4DoZUo0qgRDKEw5HUSYZlXLhFljlZbiWSOoVcXymASdgc4GIu7ZXMAtKsnpzm4V42RGHcABKqBMF%2BcIKnxtCTtRW73uZgX9mWqYEOgVYsEwADWWY1pgdaNs22wEvZjkmZJklVdVYnBSyF5Xje8JJSlpqITFECViAk6ZpeCGogSOmpYI%2BmSb2cbtgxw30bJW5%2BfGgTqnJAUDmF5ZCiReYzZg22IeldyZREwDUt5rpFdKHmoF5PnTclL1zQoMWyed0PybaVpw/sr6qKw7KuipiO2sCmLgpC0J/fC4rbOkb1Ddd%2BqsWuFoY1cd0adx0V5gZSollKlPsQwsMOvcQheOkJSYOgOWfF4pVusCn3Zbz/NZILwsKKLUr/ezTQEhEBACur%2Bya4Ihydld1r3PLivi6CkvfcbYv/Ypshq4IOsENrF6607Wv7OiVbA%2BWgQeyAeUFQSKsboNBuI3cAAqnxSjTO54MgmYLko7SLfVVYKAGCe7W40sC0LIulQKlsDdgDGXRway0Jw/i8H4HBaKQqCcG41jWNuGxbH94I8KQBCaOXazNQEkg5hoAAcZhmCkKRcP4Y%2Bj1wUZRtIlccJIvAsBIGgaKQtf143HC8AoIDb73dfl6QcCwDAiAgBsBDpIi5CUGgbJ0AkUQBpwqij0kjFJJIdxgDID3FIHMZheCC0ICQS8eh%2BCCBEGIdgUgZCCEUCodQZ9SC6C4KQAA7mudInAeAVyrjXPuDdOBLkRA/KUqAqB3G/r/f%2BgDgF3FAWYO4EAPCv3oMQWEXcVi8FPloNYEAkAv3SG/MgFAIASKkSAYAUgzB8DoCyYgR8ICxHIbECIbQUREN4Do5gxAURLliNoTADgDGkBfnNJcDBaD6MwVgWIXhgBuDELQI%2B3BeBYCakYcQzi8C0gcHgI8nxyEdUsYiHY3d1YNHIciWIa4TEeCwOQpUeAN4%2BNIOE4gsRZZPH8cAZERg%2B5rCoAYYACgABqHxcGsVrt3OBwhRDiGQS0tBahyHYP0IYYwLdLD6DwLEI%2BkA1ioBJrkbxjFiRFVMJYawZg955OIGtMZEA1h2EsU0FwDB3CeC6HoMIEQRjVDGDgkoOQBAzD8JcrI1yGCLFGIkHB2zQkCAGNMQ5hQ3kNB2f0KYQxTlLAubYIFty9DzHaM885rytnt22BIEhHBq473IfvBhP8/4AKASA4eHCIC4CgXwrEXBBE93KWsaCBUxibNIIPSQgQcwpECEvDQkgzCSB/BofwdQV5r1IBvQIXAcxJC4EkUeKR55JH8JIGerKkjoswfvQ%2Bx9KVn1EdfMRt9qGPxkXI3hH82CcDaCwI8UZGJMDiv0thKQcyivrpAogayGo4JaQg9p0hOlKG6Zg3Qyj8FMEIT4lFaLd68H3lQ%2B%2BiI7h0KxUwgB85spcHtY6zh3DJG8P4YEMwFLhHnx1YahIT9ZGoSzWMZNijp7bxoKVBIGitGYKMXo6xLaTFmIsVYnJtiEL2MceQlxbiPG0C8dYvx/TAn13wCExw4TvFOtUNElk1j4kr3rkklJKI0k7Hrpk7J3c8kFKUEUydX1yl8CqbU%2BpjTrEeraUg71sgukYPrgGvpZSFlWCGUkjZEypkHk4LM%2Bq8zBkWGWZG1Z6z4BbP%2BR8vwEBXCQpwScyoLy9BXKaMhjIDymiwuWH8vonyIU/Lub0AFxGFggvQ28kjBQyPQuBWhuFyL1ibCReS/QpDlV704AmnFNqU1ppHpw4lLqc3kqEVS0gNKsCJHpQK9eIBAj2o5VGfwKRF6BE5dy%2BVPHI2cDVSfC9l8b53xoaW4txBjU7DNcwlgCgjx7iPKmnM45JgQPwC6mB7rZCesfSg%2BQvrX06GU3gghBiw1kJVZQvVtD6GqHs455zrn3NSi4eWqRObAj5pM%2BIzLvDLMFbGE5/mmYXMpEzGlzMiXvWqIbZQJt9d21OO7i1ztOzrG9sEP2px07MCuPcZ47x3cJ0BN3b44JAL52RKXcgGJq7BAJMwZuvRO6MlrIPbwI9hTWRnrKZqy93lr2YAabyO9fmH0SCfag4LPSwsGE/WB4ZoyYMNwAwwbxuxKxfqWSshIrqInjPI/BvZBz6PHP2fhsFmHcjYdh%2BUajLHCMUeaHRo5KP4NfKY2cgj4LBjYcY9D%2BFbGO6sZXuGjFfHat3Ac05u4FW3PekmKJrzJAJO5c1dSzAtL5MosFRvSeOZAiBH8LPeVW8RdRklfpihB9bDqoLSsAeIBJD%2BBZQvKMW9R6SGnlwceZglUr0CNF3j8ulcovAbL1VGqRFrDydkZwkggA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/front/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/front.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/front.test.hpp)
