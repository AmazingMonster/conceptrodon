<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::ClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-classic-plume">To Index</a></p>

## Description

`Varybivore::ClassicPlume` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.
When invoked by an operation, the function places the variables into sequences via a process similar to pack expansion;
then, it collects the type result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;::type, Transf<sub>1</sub>&lt;V&gt;::type, ..., Transf<sub>n</sub>&lt;V&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf
-> Oper
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::type, Transf&lt;V<sub>1</sub>&gt;::type, ..., Transf&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
ClassicPlume
 :: auto... 
 -> template<auto...> class...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<auto>
struct ClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct ClassicPlume
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

```C++
template<auto...>
struct ClassicPlume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::ClassicPlume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** Transformations ****/
template<auto I>
struct ZeroStar
{ using type = std::integral_constant<int, I>; };

template<auto I>
struct OneStar
{ using type = std::integral_constant<int, I>*; };

template<auto I>
struct TwoStars
{ using type = std::integral_constant<int, I>**; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

/**** Result ****/
using Result = ClassicPlume<0>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

/**** Result ****/
using Result_1 = ClassicPlume<0, 1, 2>
::Rail<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
/**** SupposedResult ****/
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

/**** Result ****/
using Result_2 = ClassicPlume<0, 1, 2>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::ClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct ClassicPlume
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Cosmetic>
    struct ProtoRail<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Variables>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct ClassicPlume<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Variable>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEpJmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlSKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQlJtc2t7fldCpNDESOVYzUAlLaoXsTI7BwA9ABUR8cnp2fHeyYaAIKHxwDUAJIsqfRsgkx99yeXN3fnAPOv2uV2uBEwLwM4JMAGY3EwvEQAHQogBqLTwTFi9AUsOwoLmxC8DnubgMCkyyGUeUwoJMgSsN3uzPuez29wAsl5aI5Xph7ujiJjsZhcUyWWzOdzefR7kJMABHLyMHZi64s%2B7gyGfWlwrWvHWw%2BGI1AopF4%2B7IckKM0eBRsRzIXEw/Hi5mE4kEe7KYioIgAJSYdHuoI19IsIbdGs1EIN0L1sahurcBAAnqlGKxMGaLVamBT7gB5DPET7ZPGh6PughEkkAEUwzTolar4ZbVZZXkyRk16f5sLrRZLZYERrTGeYbFJGQdeCdRsFwpxeJAIHH2ZRFZhjPVHfpddhO/bGv1SbHicNer7k435pdlutZuuwGImAhjAIztdu6rXYiwHuf1UCYdAQxhQcGybWgjWfV930EG1NxdVd10Pdt9zQm520lLkeTwPkBQxLFlyjSVC0iOVFWVBgdnbU9LxTC942NZEkOwB98wUad7UbOcKyjD0SR9P1UEDZs4TtWdTBddCGUjH9o3o5ilOTdcbxze88wLYsEhHBh%2BIUjVBK9SCg2gqMwwZY8Oz/Ht1zAwcdNLPox2vLNuKkhciJFL8UL7DT8W3azmQwoKsIslkVPPbVlLctgAo4iknxfN93k/AyO3uWyAKAkCHPuUzxLcWDUo/RC72wPyM0whTQqPKMooTGLkwRViKsS8rJN4%2BcZKjbLALM/LhIDMyjS6x1yq3I9AgPMKQRuRqWNQQihWI3Vv2M0lrTnakfGTRc1oMttSPZcj%2BQOkVsPZXCZX5eUlRVUU6KY1SXqNVrTTYjrbRnbqv3bTbhtEwbZIjYKY2a6K41UuLb1za0h10lzesMllNsK8zUZCqyIt/bsAPsgdEec8srwndzxrnZ03Au%2BgVzXfy2JqzK6rpXGIehqGzzJzN4q%2BrTypK%2BD0pRzL%2Bty0CiYxmCUuFybkIZ6q5ss2b6oUxbFo%2BhKBZ%2BniJoyzt8YG4MiaBsToIk36JoCmrWfC25AUdn5QX%2BA57gAMTwYg5nubBVFYAjnb%2BJ2Q%2BBOkzBhCIrS8LAwJTPsAH0ayDEXv3MSOaO8WOjTQGjMFSVO2Ydh4ABVSwYBR%2BGIFg9K4oOwTeuEPqeAzNoALQSVABmIOk5P6wnwPuOZ0FXCJwRfMQE9zuZDAII0x9IFuZO3EMZtthbG6WpeNprT0i0ibve4jfu%2B3y4fR8ETAJ9oKeBBnwR58ERfHjxA5D1X1Wi81k1t4JXeSRLgAdy7pMNU4YspGwHoOc%2BIAx5X1LDfaezQH5wgXtvI4787bzWLkcYmelvgXFBBrWGNsbibScnpdeOC3ZCC8KkIomB0D%2BlFNKAhRxgT9VofQjIjDmEKFYUTChLksJwgBgQEesDL7X1vhXZBc9UFP3uBoPEpAxESLgdIpBs9H4EEXsol0BxVECXERfceCCZH33kW4NB%2BjsAYJEYFNWrtAIsJ5Gwg4HCjZ8IEYPMknEdo0iNLY0Eq5zZGg7r6bui8zpRPuEAkBLR/o3FCcBdARohGk0cUXZxJdRRenrjPR0CdOIJAIBAGBCgszFOpt4nki8uEMKYa4%2BR2BVhUNdiHAEwJnHylzqBP2AdZT1w6Z0s4Ydg4PAaTwpp/C3H104XQxptSCAJy4PlDJo4RFuDUaY%2BBk8tEoOsYo2xhidmSLMfsu%2BcidGLy4K/IxCkYEaPMQcqxaCzCvzpMvJxJwXGzPyYQm44tmmrPyn4ikAS9pBNuYvD5KNQmjThDEyYBkUkgXScOZGWT7Y5Lye44EhS5zVKUK0cpJiQCVLYNUo0yzVn1MWdM2ldyXRtLmi7UZgJum/JLggL2/T/aQn5MMjlXTsm/KmUoGZrD5lGwlbwkFZh1mYvLFss5zzLmyO0Qo3RSiVFqqkS8q5Wqjk6uZXYh5RlyXqsQUaw57zX5vwce035yz8WgmBf8hOiqibgspLtNg0L7hcFhaikAYS4QRISWQfemBYnxO7kk64aK0lIuVaOb5YrS54oKc0IpJTSUVKqfmGlCr6XcMlbSuFrTDwcHWLQTg/heB%2BA4FoUgqBODbMsNYIemxtj9gjjwUgBBNC1vWAAawCJIJEGgAAcZgzAAE4F1cH8LOmdXBAiBGkPWjgkheAsAkBoDQpBm2tvbRwXgCgQDHuHS22tpA4CwBgIgEAmwCCpEROQSgaAXh0ASFELMnBVAzoAGwAFoQOSHuMAZAyAg1TrMLwRhhASB4BHsG/gggRBiHYFIGQghFAqHUHe0guhg2ANLKkTgPA60NqbSOttnBCyIg/V6VAVB7jAfA5B6DsH4NIkVRADwv76DEBDAO1YvBb1aHWBAJAP7Uh/rIBQCACmlMgGADUPgdBwTe0oLEBjsQIgtFTNR3gRnmDEFTIWWI2h6i3sHT%2BtK5FaCmZI1gWIXhgDwloLQK93BeBYBrkYcQ7mvb2bwAAN1FAxzAqh6iIl2IOuBO7W20DwLEUsVmPBYAYzWPAB6AukGi8QWIPCGzBeAOlowI71hUAMMABQqI8CYEATpZtg7MPCFEOIPDXXCNqAY2R/QhhjDWGsPoDLV7IDrFQAXbI/mwPDwHKYLtlgzBnpK0KLA02IDrDqA0ZwEBXDTD8MGsIiwKhVD0EULIAhTs3YyHdhgwwrsrG6L0Ro8wHvBoO30buCxyijGqLYb7ngOh6Bnq0V7wOJD7d7TsOH%2Bg6MnoY%2BezjoGINQZg3BqQAn7gQFwChsT6cuCSaHbV9YCBMAgTGHt0gE7JAwiRAumEW6NDJEkCBo9/gQMLuR7u/dIAYRcCRCBrgIGZ0LvXSB/wkgV2s5A6jkj57L3Xop3e2Tz65OvpY5%2BlTanRMAbYJwFoLBIuBDA0wDiPYuALqRKL1tyGiDbb0F17DvXpD9aUINkjugUgUaYFRgLtGOCNuV2epjeu2Mca41jm3AE7cO%2BnQT4TinRPiZhGYcn0n7068NwkL9qnUAibGHmIwduuDHpoDyBIV6IAGZIxZkzZnSDN6szZuzDhW9OY/C5tzraPNeZ8351vQXRuhcH%2BFho0X/NO/i8gRLreUsMfS5lkzOXditvy4VwdJWytKAqxP/8tW%2BANaay1trE5W/u567hr3sgBvEdbf7kbNXVtWEsJN2Iu3ZvzbvpwEtuIituNutptgkNtjFjNh9hFkdiduDvkOdgwOgDDssCDrdn0D9mkE9n0Kgddr9j0LAf0GDnkGdjAYdsQYMHge9lDm0AgWQbQdQdUPDlsIjmTgLuHqerwOjnHjxuXonvbo7gTkTi7pnmTlJpTqQNTrTokPTjunuqQAejCPbhzoEP4AupujCJzpBsGlwYxherYOrrnlrvADrm%2BqxkXgXsQMbrsGbjxiwAoJFnBpFknkmHMEhvgC7mhm7rIB7vfvhvID7s/joMLqQIHsHjRhwfRirlHu%2BoiPcOxpxvYY4c4a4TqD7EJiXungkJnjCDnqfvnlkUppYUUaJiAE4fQgnC4QugnG4SsqoJBtprXnpg3oZsZlZq3u3tZrZvZj3iXs5gwK5gxkPt5mIKPkVuPiFlvoFtPo4LPrFgvkvkViviRmvllqmJvnlkKLvrwPvuVhCMfjVprmfkwI1s1q1u1jfr4XfkkAEU/kNqEQYO/qATYGvr/m2v/hXJwHsOfB/tYBttwVtmhlAfTn9tkC4MgVgRdkDmgY9sUNkFgRgdkEwZDoQRQQDlgWCQIADiib9iQRDniVQZdrDuwQoAjrhqHpwWjpwEkVBg4U4fcNUUiHUcIZ4SQGIfkZrlTjTlgLIaHgoQeoukiDCDCP4KuvLkeiKYEJLhHtwZwGrjepIYzv4CzhuoEEejOpIMulwHOmYErjujCNEZHgYcYaHohrKfoRIVycVnXuCZIEAA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/classic_plume.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/classic_plume.test.hpp)
