<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ClassicModifyTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-classic-modify-types">To Index</a></p>

## Description

`Omennivore::ClassicModifyTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Oper
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>0</sub></sub>&gt;::type, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>1</sub></sub>&gt;::type, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Oper&lt;Arg<sub>I<sub>n</sub></sub>&gt;::type, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ClassicModifyTypes
 :: typename...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct ClassicModifyTypes
{
    template<template<typename...> class>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will apply `UnaryMinus` to elements of indices `1, 3, 5` from `Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position. We subtract an additional one from the rest since we only need the number of elements separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_container&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `ClassicModifyTypes`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinus
{
    using type = Vay<-Val::value>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ClassicModifyTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Road<UnaryMinus>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

/**** Result ****/
using Result = Metafunction<Vay<0>, Vay<1>, Vay<2>, Vay<3>, Vay<4>, Vay<5>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation of `ClassicModifyTypes` is similar to that of `Omennivore::InsertValues`.
We will perform recursion over the total number of the `std::index_sequence`s.

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
struct ClassicModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ClassicModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename Target,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            typename Operation<Target>::type,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            typename Operation<FirstTarget>::type,
            MiddleTargets...,
            typename Operation<SecondTarget>::type,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ClassicModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We will transform the next argument.
            typename FirstTarget,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            // We will transform the next argument.
            typename SecondTarget,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename ClassicModifyTypes<OtherSequences...>
            ::template Road<Operation>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            typename Operation<FirstTarget>::type,
            MiddleTargets...,
            typename Operation<SecondTarget>::type
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAHABspAAOqAqETgwe3r56KWmOAkEh4SxRMVwJtpj2BQxCBEzEBFk%2BflxVNRn1jQRFYZHRcYkKDU0tOe0jPX0lZUMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYSa6MyHiYCpd7x2cXh9/7H6cn/zMAGZgshvFhLiYgW4vI5aIQAJ5Q7AA8wghhgrwQqFuZAjdBYKjI1GfPaXbCqAiuABixFkb12fypLCSBipOIICPuzDYADp%2BcSziNiF4HOTKTS6YJIQB2Kwy65QqxnAHM1lMdnQtVszAcrmMViYfm85GXMFMBSvDyCJjBaKkS6c7mG43YehsQQKQWnYWigjiqkMdC02Q460NO3EHFuzAeggKY3EoEolVygGXDOO2PqzVuJ0Gvn80KYADuMbjXuT6czXjSRkuAFlPOhIUDrpdw7aQlHocWy%2B7GPHjQ7y4OEwKq0Dlf8FUqSecycpiJgaKoGTsmdmdXrnWwHWkAF6YAD6BG9aAxd39S5XeDXUPbBBFuqn86%2BWw7TCSCi89HXR1VLcNRfPN9R5I0JxTH0nz9T9v1/F9pwBd8flQgDSSuABJFkBxtWp/z%2BFC0O%2BP5AJw4CdwLCCTSrIUYLFNwDEtPBkCbfAqARAAVfVXhMNNZ1fFUMJ2S4LAtTBPyUAiyJzECmFhVBjUw71fQYpi0lYjA8A47j7krNx8RAEBgiwVRjyUABHLxHhAzDE0nKC%2BOnTMs3I3NtQorUwJdSCzXUy4AHl7mIDUMm9FzVOvOkiAAJVQJh0GrDMnKSlzXNk1KXJxTK0ozDYNkuAB1CTawkkx4g0G9VxxZTk0TCrHVQS5GB8aJgMhCqQ0ETjGmATB43KjQTTOXLcqqu8auRY0uoIHriD6%2BNSBy3L8qKiSSzoWhHRChgFH4YgWEdBAJJCSlLl61rBGG05RrS/NwMuOaFqWkbbsze6fN5MTkAAaye/qvVe3LwtGqZHGQM0BBGTAADcxHOhTLjwdAEVoCB5mWy4AFpTTcL8f3oTHsqBt6Zv%2Bod%2BRem63ozD62EC4LQoEHFyeRIz8ypmmM2%2Bv7eoBxMSayyckMF96gPc7zC15U5gGXWMxxB3La2CYBG2bVt2ywMF8wgZHUZxGW5YrezsHRjHBOp5KBJFy30u3LVxZAunqNNc1LWNQ3MHlz1FcuZX6zihKNcuJdUFi%2BLEuhT3vYpmiUQtvjFQTs4PNzeSiCUh108U/kACkVPo/1GItDS2O0rieJxQzjKDTAzMs6zLxqk39wIdAjJMuvzMwKybJxXOTe9FKSdTp3Hco8CTb8kuGba2pfcikPotQQPEpJ4fbZc0eiehTGXNW4q/akwbxtUSa6oFBqiGahhWpCqkOo0Mm%2BYGirrq5pfbzP6FauwaapVmi/BQnMuYH3Wptbahg9okEOgQY6lxTr%2BgunGd%2BXNnaXGpHgYgIxyYgJpmAo%2BZUKqn37lNS%2BGhGqXGAE1JgyA6SWiOhJfAUwm6ixWgVKIBASxewYI6EsTVRgLQTHvTMJDoT5wvryBsyN0D0HJsAkReUCqHw2rQLaT4oH7VgfAxB515qXQIKgmm6ChCYAvOgXBijHSS2ojzeRO8oK3TBixSGu0qRwy2tnJGKM0YYzYdjXG%2BMEI7zcFY5%2B81%2BaUysegoKc8wrQkwdgwBESzzJnZvqPBb1pEEjkUA4c0SbGz3vvEtwpjzGszSSADmVi7F5IFP4pMNtbrby8ruai0cKy%2Bxcv7VWTZaAtgfJcLWtAdZ61oAbWWXtjaQTNnOde1t5xb3Hg7NyTsbFTzduOaWkyY6VkcTWOsqtV7B1DuHBKEyjZjkHgnBZQkFxXBimYlYaQYYSTxlJd4Ml7Z4wUpnBGGc84OmdsaAKcDoimN7pePZAJF7F2YppdiFc9JVzbh3Wu9ce6NzWM3SCrd2411Mt3SF2LxEt0CmC4gEKsUvEHqmZyYtVkcmWaBNpGz/KxOKczWittF6nJXhHVKG9mnjwabvfx%2B9lElWPsQ5c1Uf5kJNFfJqLU2D3yIU/AB9i35WLEW4X%2B/9ZDyMybdAhqj1E7WgQdRhCC65IP0SggpbSMFYJwS/Y1o0CGlUfrqiRf9yGUOoedOhqRXhgqGXgFh2LxWZlWpw7hjA%2BECLyTq2VE1xEKuybIzARqrGmogRo3aWjrW6OQYOIxb0TFmIEBYt1jqqLGlqSkwGm9MxdMzM4iGF5oYeP%2BU1MZ6NMY42TAGSUoZRWhOjbTQpcLS5aR0pXaEoLjqUsxTZLZbbcrs0dpcVeOIOVMwYButKW7Vlq36TiRtQjaUtuSty26J7ZJnrXje1sE6X0uXCVeqJk7rFOv3fPBJLrkkLTZlUjJVjM25Kbfkn9MTGYAdKVWoMFTsDpPuA4uZ/x/EtJZfW/kHSFZ3tGj0p9wdhmjJ8RcqZVyZnzHNvSq2ScmkMoyis1juHJ6%2BU2R7HZnSiMZhI8cwZfLd1R14zRuOmHE5SeEsRDcyEyQUlYKyCSnzZNydIiqYEoJwRlWhBeNYSQBrcoU1cAAakwBE0kU7Mq8b/GFhdLgWaRHSy4HbXHQ1UEkYgvbLgeOsrKCwylrayiY2%2BMkchmDEARNI2%2Brw1OnBw%2Bgiz4zuWL0i40GLwRayojTCTEj%2BZg7OZxFjFLRl/MvnjkhW5WH7kiTxvBP8CWkvrMgg5kUDEgmE2TnVj8DZ%2BpMCoF4DE%2BFmvMuBfh%2Ba0Kzgkf6w0IbI2MjBxnSxMu87kUqjFTy1FIAWBMB%2BieTuGLiUgS4MiTJ1c9sHePEdol1KcRAixlwJ753UqXf24d9Fd2%2B7QgAKxY0e2dkz3KjKibcBl6LsWcsg5AH0yObhThTeuTbd8lwhBeCSHkTA6BHkE39Alkj6PMepGx7j38/pBkNYJiBYr0INDnac5ZkrQPsAOlp24MwDP2cA650z6EkhedImhFjX7SYqvhYeS8cn1nTiCalyM4Oc3BvDYcCU9n9Pkxs7524FnWuhcc8Fw9w3/PjduFFw5GTvXHovHx4yBzoVkDHhLtEAgEBq4KENE7/SZORkOiJ1jnH8vUnYHowCDgixaCcF%2B7wPwHAtCkFQJwUJlhrBueWKsMqwIeCkAIJocPiwfogF%2B5IXkGhYhmDMAATkr1wX7ZfYhcBlDKaQkeOCSF4CwCQGgNCkFj/HxPHBeAKBAD33Pcfw%2BkDgLAGAiAQDLAIEkWE5BKBoBZHQaIoRDScFUAkLG8RJBUOQBDKQvIzC8Gx4QEgyM9D8EECIMQ7ApAyEEIoFQ6hx%2BkF0O0EsIUkicB4BHlHjHnngnpwAFLCIvv6KgFQJcDvvEHvgfsAEfpcCfmYJcBAB4GvvQD5miFwPMLwGPloIsBAEgKvkkOvmQBQBAGQRQSAMAFIGYHwHQFSNgpQBECAREMEJlv/rwJwVFgiAFBENoGYmPtnqvnGAFAwLQAiCAVgBEF4MAHjGosPtwLwFgHtkYOIB/vgMuKrq8iofHnXE8lSDweQIINUCAfCBECFNFh4FgCAU%2BHgJ3qoaQK8sQBECTrcBocAPCEYHnosFQAYMAAoGZs8CWLErHtnrfsIKIOIE/tEa/moCAV/voIYMYNYNYPoHgBEMPpAIsKgEZhkCoVjPiA%2BKYCnpYGYP3m4cQMjC8PAIsHYCIRkC4EGOMG0KQIEHaLMIMO0HkOkAIO0bkKkAMQwDMAMOUB0M0QIN0GMJ4K0HoE0arjMaML0N0RMYsasUMZMKseMaUL0Y0enmsBIIARwNHr3iAQPrAbvvvofsfiXmgRALgJfjgVnvgTnv4YsMdAlIMOjKQIXpIECLyJXkCM3hoJIGYJIBVBoL9vEJXvoJwO3qQJ3kCFwLyPEFwPELEJXg3vEMXrXiCYkH3rwAPkPiPh8ePsQTPiQXPhAUvlQTQdgZvmwJwI0CwDDDKFjEwNPPWFwJXryGiYYfgEQLUe3O0NEffnEdIAkUoEkR/roIwT/l%2BDwaceccSaARwOAQvrCJcNAdcfAbceaLyfyYKegZgeQdgZCMCGYO8YQRPjSYyfaAyagFgYMEafQTXj3jQCMtEMPhAOwR/nwdwS4UGdFoIcIQ4KYeIYOJIdIbIZgPIYoWILQCodnuoWkVofHjoc0foSAUYcgLCOsNnsEFSK3vHlYTYQiHYesPHo4c4dnm4R4UoF4RmSrP4XwEESEWEREaYRKbEY/tKbIIke/vHgqakX4eUVYJYFkTkQ0QnoUVDJwCUW3GURkZUdUdEKKfUXkVMcsX4BAK4NsZ0UGHsXMH0SMbUEef0bUKeb0bubULMc0PMRMPeV0LsesfsZMVMHMdkB0d%2BWscUBsXgUsCsMccBa3mqZcZwPqQgTyarHyQKaXugc8SKVaaibaZ8aQN8VgDEH8a3kiSifyeCTKL9pXk3kCBCVCZIO0OqaSbYOSXaVSfADSfPpAcvtQS6RaRvlvhwGybcSwAoDDBDDDAhTqCMOfsKVfmKc/jEQ/hIIOS/rKSOToCAECKQEqX/qoaqcAR/gPlqZAbqTAaoPxYJcJaJcBCMGaZxRQWhUCBhZSZPqQdZdgexY6TEEJZjseCJZXseGJQQMeMZdKcwb6WwRwVwdFqYaGQIUISIVGS6RIVITIdoQmQoUoSmaYemZoTWWoVgjmfUR/vmYWaYSWRYR/hWZltWQ4bUfWbwI2Z4bGK2X4Q5YEUwMEaEaWD2S4X2XJfEUOUpckapeOekRUTYFYbkX8QUbUCoRsIZJOdYFUSSTUXUeNY0dUNMfuYec%2BR0V0YBZ%2BcMfkBkFeReRkLeV%2BWtXuY%2BUeUsQ%2Be%2BbtWebYFsVtZsdMB%2BWeYcaBY/tpRcbpdBYFZcAJUJX5uZVSJZU8ZJa8ehQQZhdhb8acQRSAFXryECECL9nXtRd3sjTKFid9f3pwGSaPphQCb9sCY3jKN3rEJIDXhUBXokK3kCDpbjYPhSUQacWfjjSSXjczfnq4b6S0ZIEAA)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/classic_modify_types.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/classic_modify_types.test.hpp)
