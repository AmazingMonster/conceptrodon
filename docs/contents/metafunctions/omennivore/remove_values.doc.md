<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::RemoveValues`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-2">To Index</a></p>

## Description

`Omennivore::RemoveValues` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices and returns a function.
When invoked, the function removes arguments from its argument list according to the `std::index_sequence`s.
The result will be stored inside `Shuttle`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Shuttle
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
RemoveValues ::   typename...
               -> template<auto...>
```

## Structure

```C++
template<typename...>
struct RemoveValues
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will remove variables of indices `1, 3, 5` from `0, -1, 2, -3, 4, -5`.
To do so, we will calculate the distance from one index to its immediate next.

We will keep the first index, `1`, since it represents how many variables we must pass to reach the first target position.
We subtract an additional one from the rest since we only need the number of variables separating two targets.

<pre><code>   1, 3, 5
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;3-1-1&gt;,
   std::make_index_sequence&lt;5-3-1&gt;</code></pre>

We will pass these sequences to `RemoveValues`.

```C++
template<auto...>
struct Shuttle;

template<auto...Args>
using Metafunction = RemoveValues
<
    std::make_index_sequence<1>,
    std::make_index_sequence<3-1-1>,
    std::make_index_sequence<5-3-1>
>
::Page<Args...>;

using SupposedResult = Shuttle<0, 2, 4>;

using Result = Metafunction<0, -1, 2, -3, 4, -5>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `RemoveValues` is similar to that of `Omennivore::Insert`. We will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<auto...> class Sequence, auto...Variables>
struct ExtendFront<Sequence<Variables...>>
{
    template<auto...NewVariables>
    using Page = Sequence<NewVariables..., Variables...>;
};
```

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

We will use `Prefix` to enumerate arguments like in `Varybivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Shuttle` is used to store the result. We declare `Shuttle` as follows.

```C++
template<auto...>
struct Shuttle;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct RemoveValues {};

/**** Base Case ****/
template<auto...I>
struct RemoveValues<std::index_sequence<I...>>
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
    // Note that `Shuttle` is instantiated by values
    // extracted from the template parameters.
    // This is because we will pack every variable
    // into `Vay`.
    -> Shuttle
    <
        FrontTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

template<auto...I, auto...J>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>>
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
    -> Shuttle
    <
        FrontTargets::value...,
        MiddleTargets::value...,
        BackTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct RemoveValues<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
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
        typename RemoveValues<OtherSequences...>
        ::template Page<BackTargets::value...>
    >
    ::template Page
    <
        FrontTargets::value...,
        MiddleTargets::value...
    >;

    template<auto...Agreements>
    using Page = decltype(idyl<Vay<Agreements>...>());
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArLGkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwc5gDMwcjeWADUJutuXo60hACeB9gmGgCCG1s7mPuHyEPoWFSX13dmmwzbXj2BzcBDOiUwAH0CMQmIQFF9bt8APQAKjRKN22FUBFcADFiLJduiUUjvjiWIkDDjgaDwcw2AA6JkIm5DYheByY7F4gmCfYAdis/IAIgcrIjbuTKUxqYcpVTMMCmMdUEyGZddtsmAoFLshJgAI5eRgrUi7ZVENUANXqeCYEXo8PWV1ubI5BC5OIY6HxsmB%2BqNJsVhxtxDtDswCjVX2d3xMgu%2BuyTu3lMuDbgtqqZoUwAHdQ%2BHHSzk7svKkjLtlExgE8DsK9Ybjf90zn87b7Y61WaCx3I9HY%2BtxXcRWK47dUejdgBZASoIgMM5E9GkyWYCkKpUq3Y9iMst2cmcMOcCC6IwW7CaOZCagRDTCqRLEc1bgBuYmNAosO/o8dFg4Ff5DsixKVsQmA0KoS5oiuNyprKIJgowrCYGaqQAF6QgQLJoM2iQesoYEQc89bQsao4SjcE5onqCDHAQ9BQSSZJrtK8GZv2LqsqRnJCLRBD0cGQHjiBABKa6oC%2BmA2t4kaMTBcHprSSGMsysautxHpiSwElSe%2BsnxkKgFjpRIEWNqTwZkocnMeuaabpaTIAJJ7hpuxaTp0nGk6bhvCAIDBFgqgQkogbNsCjkcSyBmJsmCkxUmwLxSWuxIkiuwAOpPGWtYAGwaAR4F4Ko4WXNGeUpqguyMD40RpvseW%2BoIAAq9Q1gQ8J5eqtzJcmBUQSVzpqo1BAtcQbUKKQSUlqlGVPOgBKJCmCBPCE2LmmNNWCF1Nw9UmSn0ihU2xYhB1qmZyAANajeNSXFsml54NeOF3m%2BtDPkQux4OgZy0BAsxJTNoRzk8BAIDK9UaLxdE/uVeC6sEEyCHaOLoLsESLq9XkA2l97QkwDiYKjVAEiwS0gyxCq7Ik9TITixBRtjuxNQgcOfbqUSiNluy5k8uZ0G91OXVVknEBj7a7t1yYzcEH0mHlh7HgucsaNtJYALQalD/E/pLCWHEdSbDddmDtX5mOYF2Bu7OdV2tSbChm3p0a688VyDsZJZxYc7FMjcwBgWujDtXdSZlsEwCVtWtbrPWWDbEpEBfT9wIK/OFyHH7AdsIITrYBxf3/e7Z5GRRXsZiqaqOWaPsMgAUi57Kcu5kmeZGwK%2Bf53r3sFjZBuFHGoQQ6B%2BQF3chU2KzArXkVqcOQ6exTdku4lLvTWlmWllZyt9UVA158y5UfdVbAwjiENG3bwedVbO/FYczmDUyF9jfbk2r1L69zQtZO7KtHqtZtAgqtdr7WQm/Hau0Zoby5tvQiu9Dj10fuqQ%2BlVgCVXxgSHUP98CI0nu/JMM0ogEB5owFMuZKrDHGsAnqt8p6lSZFOL66B6DG3auA3aKVP67HmqgRaoMVq43WsAQB1DkqgLYOwkBJ1kJnXxrbF%2Bwdl6zxLA9J6t4cSvXepVJOv1/ouw1s6Gi0NFRKLcFbZ%2B41HYyUtvg6cTCWGXwdiAc2NiIE9RtqwpxLjmRKLdkJNxKZF5sQrr7f2mBA45xDpvcOkcazEW4ZgeOiFE7fVoCnWcadgSZ3CdnYOSDLgF3IsOEudxhKTjEsgJYqRJK7Esk8Yk8kgnphrlXLRapa5mnERbJkAB5fhxAAwTzbrPfcmlxItz0t5Duo8grjz7vfAeF4h4jy7rM3uYUEGLL6ctAZ6yVhRlUpxaKLs4qmKtlArKW88q0PvvQ5BGgKpVQYDVU%2BuUNAWPtsrURJYbluAfvvBkHy2HnK4Twvhy1f6CIAbk75x06RgJBbNTebzfmIIBcrR5aDzTIEwbqfh3C4Z1DCrYwhJsSEMDIRQxxsKkyoruYw94DiFETURRvMFP8/5CJEVbLpkiepdNkZdTxt1lH3TqFeG8DAXpiC0Z9VJf0koGOwJ6Hkfozm2K6W5cZukZLeW2dEQZQYDnqlFT1PyClYnpg8Y4qxxpIq%2BKSuapplqRVmNsUCrxTsmR8uSgy5hmBPG2u6aImM/iF62WCQ5Bk2SIl5M4iWMOFYqxxLrAkpJ4IUnJ0OKnE8WSwmxtzvnWYhcgIjiLqUkyxIq1VpglRDETVIztWsmU6traYJxl%2BA8QE0cjgnHOFFVcEbmkhJNZxUZRjtaCWMmXGuNwxq52%2BImiOU4TZMCoF4f41R4nNx1VjRE%2BsXYdxYEwC6kIZk91CpPQ4XBLg%2BqPSes9qyL1DOBOsNWXB323qSve09EJz1zI2W4WIas303tniyPyyb0xzuAMa0Nxkl16i8IkXIhMxIKC8LQD0qatYCWBBoM0ZgzSSHgxRRD6HMPYZjtOVd67N3pHw2ad9hGmPrGI0x2IpGK2qIhNqJQDQIAdwUMhXj3khDIdQ%2BgCjWGzTSaws6EtHB5i0E4LEXgfgOBaFIKgTgZjLDWAvIsZYtZfg8FIAQTQSn5gXTiGYBk/IzCSAABxOdiBoAAnLEMwGgcpObYypjgkheAsAkBoAjGmtM6Y4LwB2BGLOaaU6QOAsAYCIBAIsAgiRjjkEoGgCkdBoihGQpwVQTmcpqxypIXYwBkDXikAyMwvBCaEBIF9PQ/BBAiDEOwKQMhBCKBUOoBLpBdCtFzDCRInAeDKdU%2Bpyz2nOA9OOFlj0qAqC7FK%2BVyr1Xau7Hq2YXYEAPD5foE%2BDYXBZi8Hi1oeYEAkB5cSAVsgFAIAPaeyAYAUgiM0Cw9EB2EAIjzYiMEeoZwpu8GB8wUWPSIjaESfFszeXck9IYLQMHw2sARC8MADMtBaAO24LwLAx6jDiAx3gMCDg8CSQJ1p%2B8iTjirDMzLSo83TgRBhKLDwWB5vQjwCFwnpARYRBSJgYUa5DDAFOEYSz8wqAGFg1aPAeYel0nB314QohxC9Y6/IJQah5ujf0JLlA1hrD6DwBEB2kB5i8OqATtWbw6ymH05YbzvAdLEDDFga3f02jw/SC4b0owWikECMEXoJR%2BitFyGkAQIecgpDjwwKYfQYjjEqAHgQnQRieGaHoOwWeajDG6BH6Y0fbAl4T%2BMEvqeo/p/mAoIzKwJAzY4Gp0gEWPecA22VirVWat1ckA1w7uAWtndM5d8zsv5jLSYFgGIfubOSHWAydz6x%2BSSA0JIRzeUNCxByu5/QnAgukBC%2BsLgDIcpcF8%2B5pzN/YiSC4LEdfOVO/zaizFkAcXZdJdS3d9LZbbLF7N7U7IrNgTgeoFgF8fkNWJgTUAwCsLgdzBkS/OnfAIgb3drWQLrbXaQXXAbA3YbXQIjcbJgSbQnNvDvLvBbDgJbTLY4XYNbdaaA2A%2BArUJAlAtAw7Y7R7U7fYX4MwKfa7RLAA0A6IHLV7VAE7foKAmAtWDgz7dzLgAjH7Omf7QHYbSHUHdXbQ6HWHeHdXJHIOFHNHebTHbHXHfHdXYnSXMnLTfASnRwGnebenSpHEdXFnALLTdnTnM4bnVYLTPnAXMzYXUXcXEnKXcOX/eXasBQJXFXNXQXXXXAnrfA2QQgobLTEg43GXF3KwSwC3K3eAW3PCdIB3J3GOfI6wd3bTEWb3SMEo/3KnZwCAVwavMPb0OvGYGPJPaoDo2PaoboivQvFo4vLoDo0Y6oHPUvIoNPAvKvPPMYSvSYMveYi7BYJYFvDYgLagj/HvOQtghAyXPbLghkB5CAMfTAgQi/YQmfUgOfBfSgNvU/c/FA7ffkF/fkfkdYHfSQSrVoGgz/Wwb/afBLW7f/JADLFbSQ8Q4gcA1YKA7bFgBQF8a8F8ZAhkBUIYJrDA1rYeVoFIrXNIjXTIw3EANjMgig6bY/dvObYbKLeglbJg9bJEqrFEtE3YDElA7Ej0I7aQvg6IG49YO48EpLe7AUp7WEyU07ZxZAFDCEbkiEXk3jYgFgSrPgOgdQygTQrTPQ9HMzfUmHOHBwIw6Q5HVHdHBwzALHHHMQawwXWw0nQIonCnAPFw4bNwxnTwwQVnYbXw0HAI3nMMEI3gMIpQCIuw6IsU2IxXZXXMVXRgdXIk7rCQdI/rfXLInQCk3I4wM3Qo9nX3Uo%2B3TgJEXyaot3SLeor6Rom3Zo6oIPdwJY0PcPOY%2BvRPPIdIAYvo9IYY9PesjoRYrIUPKYwc1YtsnolY3PYchY8cyPHoxvZvHrKg%2BkyLA4tU5E1E9EzE3k0fPEifW4q7e4x4/oP3ALV4kAMwFA9YdYeIbfFQjQG8/kXzd/BkzgL/H/cE6zEASQfkBrT4rgKQdzD49fLgfkWk9YVc7vaLMEm7NvRrV8tcmCkQ4tIXP7QPSQIAA)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/remove_values.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/remove_values.test.hpp)
