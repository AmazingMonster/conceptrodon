<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Erase`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-erase">To Index</a></p>

## Description

`Typelivore::Erase` accepts a list of elements.

- Suppose its first layer is instantiated by an index.
In that case, it returns a function.
When invoked by an operation, the function removes the element at the index from the list and instantiates the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>
-> I
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I+1</sub>, ..., E<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function removes the elements of indices within the interval from the list and invokes the operation with the result.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>I</sub>, ..., E<sub>J-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>
-> I, J
-> Oper
-> Oper&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I-1</sub>, E<sub>J</sub>, ..., E<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Erase ::   typename...
        -> auto...
        -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
alias Erase
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
}；
```

```C++
template<typename...>
alias Erase
{
    template<auto, auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
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

using Result = Erase<int, int*, int**, int**>::Page<1>::Road<Operation>;

static_assert(std::same_as<SupposedResult, Result>);
```

In the second example, we will erase elements between indices one and three from `int, int*, int**, int**`. Then, we instantiate `Operation` with the resulting list.

```C++
using SupposedResult_1 = Operation<int, int**>;

using Result_1 = Erase<int, int*, int**, int**>::Page<1, 3>::Road<Operation>;

static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Typelivore::Amidst`.
We want to count elements one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Typelivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Erase` using concept expansion.

- In the case where the second layer of `Erase` only accepts one index, we want to remove the element at the index from the list.

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
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

- In the case where the second layer of `Erase` accepts two indices, we want to remove the elements between them.

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
    static consteval auto idyl() -> Operation<FrontTargets..., BackTargets...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<typename...Elements>
struct Erase
{
    template<auto...>
    struct ProtoPage {};

    template<size_t Index>
    struct ProtoPage<Index>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Ditch<std::make_index_sequence<Index>>
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Typella::Expunge
            <
                std::make_index_sequence<Start>,
                // `End-Start` is the number of elements we will erase.
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Agreements..., Elements...>()
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIACcSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwc5gDMEcjeWADUJrtuXo60hACeZ9gmGgCCewdHmKfnyBPoWFT3jxeZn2DEOXhOZzcBBuaUwAH0CMQmIQFADnoCCJgWGkDJjIdDYcw2KRjkxLqg0U80KDMGkCMdlMRMDRVJ8ACLHRFeTBnKzo56Y7G4nnnAmMVgih7PCbELwOY5swjIBCnQJWQJs3mAjFYnFMPHnLIAL3hBAAdBaAJKUmVy%2BmKgjKyE/EAgCJYVRwpQAR25NMhlotZoBuylLzVgOOUc5uuFkejkPj0ejgr1BqhMPFbCD92OhyYCgUxwA8rCkY1SEnkwymSyA/cgwAxYiyAAqrWAmAICkrz2rKczRMwvae/ajYqHQYsTGQAGt28RO92q5Tk3NHMg8wIJpgAG5iUnk454dA3WgQZbHAC0udLCX1OUhzbbHa7CiDJOnc4XS/fFpDfLhpquyATqQr6iKGaEhKJIThKNpcvK2CqGkXhGB8JgRhqWr8k8qZxoaeAmgiQaWiSxqmkGABSCGykhKFoZ2zoEOgrrupgno%2Bn6WwBjmobkSxbEMB6XqYL6jA8ecVF8Q8obahGfYprGEErucVbJvhKmioOEoyXmBiFiWZYPgII5jscAD0FnHAA6h8XhKKcABsGiMsyeCqPWoY5i5nKoMcTIziqBAIB8cxtMcqBUJyoXHGhADuhiYugxz1FijDdsGin9m5dbnNa3kWs%2Bgg/m%2BZljlZtn2Y5JgublHmQjRhXBr5RCpQwPj3piMUfGlbCCEW8UfIlgh%2BalSJKFlo5jvVnlSQ2Frlf2cHZhaX7zq%2By7ZZ8YZri0G5bgwO77rQh5tSeZ4Xtet7GY0T4tiVm1/man4zhti5vjJOFAd9YFppBK2YEG2D0P1y5ydKiH0tgE08uiCnTeOynpmSRBfdttryoyqBEMoTCdqq6rAaB22aemFEIsclrCRxq7Rpj9LY7j%2BOQdTHp01GmGAeZZMA8jAM6atwahvpBbPU8wBMulA0c9WDkRMAxwAEqoEwKVnByWCHGK6nRhAuv9g6TqGoJIAsEws7wuxnFidxrM03Nsm7eZ0aurzx6nrQkIS1LYPPSSIPS5l/6hheBvHMs33JphxPaqT/POkRprHP0bTkUnlPYMJstMr6eBMkWECp/Sia7ByWfoJHGNQzWOOoHjTHnMXAfZxDiOE%2BHvP4gn2nQULub5oWQY%2B5gQeom35ny0Yyuq%2BrZfHFrtA69tyb6yvY7Iah6Hh9Hanry7xwumbFtWw7onif6TeTAQ9xLQf0aVbVGgV1exdP8eRYhR8HVVAkkXRX1DKg1hp0FOveSaO8xxH3NpbOE1tz520hC/N%2BE976y3Mm7fmHszze0lqPP2H5jiBwISHbAYd94RyjgmbCIE47ty7ucVGqBh54LHrLKeisG4YXnkzeuLNcG%2ByAV9Wh8NY64QsgAKikdImRFlASSKka2bAQhWzSLkc8BRMjZF0NeKCd4nw3DUi2HSceYY/oESglmIGpDAQMyMl1R8IiXjPA4SnLwaRiiYHQErTACgvBL3ZPY8sji3ARAICSMJUiImCCkQBOhrifF%2BICRrIhsNIRhOiQQCRmSonHhiRI%2B4rouGQi4IUkAKs1aQjvMEgQcTcLrjwMgOEYsEgEAgEfBQEpmnjzcEIdxnjvG%2BP8eE5WQyl73Ejk4wEri%2BkeMyF4xJwy4RcECdUkyDB0mCByQUuSUyXFZGnospeyzAkwwLJBDJeSsnbO2WU4p5wuAkl2GUip6Aqm3UcbJEmTwGlNJaW0dpptOlsG6ZCWZAyjkEGWSSSFyyJm8g4KsWgnB/C8D8BwLQpBUCcDcNYawh91ibAwsCHgpACCaERasWcAQAAcZonK7EkGYQIkhJD%2BBpbsDQ/gkg0v0JwSQvAWASA0BoUg6LMXYo4LwBQIBRXkoxYi0gcBYAwEQCAdYBBULhIoBANA2I6AJCiBKTgqgaVOSvE5SQxxgDIE3FIM0ZheBeMICQE8eh%2BCCBEGIdgUgZCCEUCodQCrSC6EefFJEaROA8CRSitFFKsWcGLJcLV/9jimvNZa61trjj2rMMcCAHh9X0GIKcElyxeDyq0KsCASA9VpANWQHVdaG0gGAFIMwfA6CYmIDKiAsR42xAiK0G4UbeCDuYMQG4xZYjaEwA4UdpA9Vg2LAwWgI7g1YFiF4YAbgxC0BldwXgWBzZGHEBu/Oc7HC7l8fGjic7LjbFJWE%2Bo8brixCRJOjwWB42IjwEKw9pBr3EFiPMtkWJDDAGuEYClqwqAGGAAoAAangTA8U7zotJR64QohxC%2BqwwGtQ8bQ36AgygPFlh9B4FiDKyAqxUB0hyAeq8PwNamEsNYMwEqgPEBPDe2jPRL05BcMJaYfhHlhAiMMX%2BiRHnFGyAIUTeg5ONAWCMGTAmHB9Gvopx5dhBMCGLqp6TehwrtE8J0Ez18jNLC4KsBQhKtgSBjRwVFYr42SrTWai1VqbV2skA6/NuAXUlr2LZitMHVihTVqMC8pBqWSF2GaJIuwWUaCZZIFyXKnKpGRRwAVpAhW7C4PSrgTkaU8tK/4SQXBuW7Ccm54NkrpWyrJTBpVqqa3quTZccglBm3FqNWwTgrQWC7kCFeJgotp5cCSGaYrmLnVEB46xR5WGvW4ekPhpQhHg26A7eGpgkbD3Odc%2BK3gkqk2asuKmkbY2JtTcVjNubZoND5sLfW4tpbdhmHLa1hV1ba2oCLQkXruqgcfdGLd8b%2BYjAza4KKmgS8Ei9v7cG8dw6F3o8ndO2d86ANLoyiutd8bN3bt3bQfdC7j0QbPZi/ATJNPXoPQt1Q97MQLufblzFb6P03C/dsTFv7/2kqAyBpQYGT2QYVm1uD%2BMkMobQ4SBda2cM%2Bs27IAjQbMV7ZI9BtjVgKNvpo7F%2BjjQmMsbLvrjjXGEjLb47FvTmnnAQFcDpkIwlrOjFk5keTuRzMFG9yUHInv1OO8aMXN3YetPzEk4sL3thtP%2B7EwnmPFQ1NObWBsRztm%2BUubjY1zgpJiCjfG5NmHj3ZvzcC/gJbX2wt/arZFzA0XEixdy/lwrs20uBG5YEQIjKzAZeqw1iVnBmtyra8qtVGqtWg/64a41HARuZpYAoXcm5dxPeFBMJ1NfXUrb9dh71Eh1f%2Bu21rnQIBdikAO0d6NufTvucTd1%2BkUUi8sBX2vjfW%2BIITDe%2BDhtL7XYX7StRVTrefRtPrAA4tEAdfDxOETfJIOEbfKFZfTbLtZHSgVHTFLHddUlXAnHS9BdAnQQInddOnTALdHdPdA9UlanU9AXI9C9RnG9YNO9ZAB9DnQQF9YNHnYdfnH9HjYXXgUXUDcDU9aXf7PgeDeXVDdDZXWQdbNXQ/TXIjK/XXYwcjGwI3eAOjBjbcTgCyF0K3SwTjc7bjXjY3OzNKJ3PwF3ETJPPQCTNPYzQPX3N3ZTYPWPdPXTGw8PRPfIZPKPAzKzbw1wlPKYRw3TUIlwmzOzBzH1E7fPUfDgd/T/dfY4RAs0FA6vYLOvEAiLUgKLLAVvZzDvEAMwWbXYXYfwfwNLeHDQaowIMrEfc7MfWwFrUA5YKlEAarM0OrIIMwWo6rbLSQDQDtXLXYZItoqVBvSlXPR1VohNWYro1YIDLIZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/erase.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/erase.test.hpp)
