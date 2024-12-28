<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SensibleClassicPlume`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-sensible-classic-plume">To Index</a></p>

## Description

`Varybivore::SensibleClassicPlume` accepts a list of variables.
Its first layer accepts an operation and returns a function.
When invoked by sequences, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the type result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   V
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V&gt;::type, Transf<sub>1</sub>&lt;V&gt;::type, ..., Transf<sub>n</sub>&lt;V&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf
-> Oper&lt;Transf&lt;V<sub>0</sub>&gt;::type, Transf&lt;V<sub>1</sub>&gt;::type, ..., Transf&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper
-> Transf<sub>0</sub>, Transf<sub>1</sub>, ..., Transf<sub>n</sub>
-> Oper&lt;Transf<sub>0</sub>&lt;V<sub>0</sub>&gt;::type, Transf<sub>1</sub>&lt;V<sub>1</sub>&gt;::type, ..., Transf<sub>n</sub>&lt;V<sub>n</sub>&gt;::type&gt;</code></pre>

## Type Signature

```Haskell
SensibleClassicPlume
 :: auto... 
 -> template<typename...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;
    };
};
```

```C++
template<auto...>
struct SensibleClassicPlume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::SensibleClassicPlume`:

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
using Result = SensibleClassicPlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

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
using Result_1 = SensibleClassicPlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

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
using Result_2 = SensibleClassicPlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::SensibleClassicPlume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Variables
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Variables>::type...>;
        };

        // Multiple Variables
        // One Sequence
        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Variables>::type...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Variable
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <typename Cosmetics<Variable>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDMSaQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkixp9GyCTE13xxfXt2f/Zx%2BV0uVwImGeBjBJiSbiYXiIADokQA1Np4JixegKaHYO4gybELwOO5CRhZTGYNwGBRZZDKfKYEEmQJWa53dl3MEQj6MmFcl486FuAgATzSjFYmCRCJxd2Q1IUdwA8uLiB8cjiQRy7gSiQQ7spiKgiAAlVBMdBajnM1lXbXa3a7O4AWS8tEcL0wd1RxHRFOxbPt7MdLrdHvoJMwAEcvIxtgG7UHOeCBVC%2BSnIbzYfDUNLZfKmDTpR4FGxHMhsUlsFag7riQARTCtOg1%2B021tJu5eLJGTlir3Q%2BvK1XqgQdpNC0Xi5hsO4lst4CtCn1%2BrE4kAgKdSpGapK2zvM%2BvQ23j4NO13uvCe71ojFrwNBkNKyKRmNxxkP%2B38zOTjOCmFwoiO5VnKCpzpkC6mFWp46gQhINk2TAtjC85Noumqftq7aYUm3YRMAfbiniSRDiqCSjgwMFYXy/Yzl6qHlsut7%2Buum79nm0F7jBh7HkyOHst%2B/7Cn%2BabZkBMogQWRZIgxi6VtW/Fdj2BEmkhtDEUOjbNrQQqyRWHHYBuW68Z%2BPFcdcraCaJVlZludEGaBhYKNKVzAMQmDgowBDya2eG9maFoaQaRqmualowq57meYIznAdW5nAoER4JXxoIiVmgGoDevp3ryClXHW%2Bqkgw5L0FSTmLvSPhZiuuUYYl%2B4cjZv7ctZtGSg5UmKmRapNPV2qFcFxqoAFlqmSyMFPi%2BtUUpN55hleEakm%2BDDxjBzXpq1GU5p1CrFhBaFLtBil%2BSpalBT1FHcTR06SuBpaHZWbgzfQrFbgZJmJuyZknp%2BG3CVtk7tWwu1OS5bkeW83n9Ryp13KNQWGsNo1CpFkNebFEnxSeSWfSCfwAoT%2BxAgTdwAGJ4MQkx3NgqisNe3z40TzNAkyZhJBE8peFgxHCv2AD6cFIdDx3AuznPeDzQpoKtmBpCL%2BVM/cAAqaolfwxAsBRiqM9c/2ZY89WDQAWgkqADMQTIskp%2BGEQOJGwegG4RGCbliPzMvzIIQou6QhucRYeK4ylevpUKBsPEbcF6sqkQW1bgdw1uQWTE7IAu5gbu0B7AhewQPuCH7kdVvsx5B8lv1pYDAE5v7%2BWDcrADu5tTAmNo272yeDo7zuCJnarZ57rTezCvt14cZc/alpOXZ8utV6mtnA9uWP4tHxKzxqIc3McJJeGkxSYOgJqYAoYZfOcIJw0I%2B%2BH8fp/n93m9jhZMKtqnveuwPOclcP%2Bej4XO4GgcSkHfgQNOGcs4/zzgXAgftgEl1AZ%2BD%2B6c%2B5QKHoYf%2Bbgx4IOwBPV%2B2Np67xPmfd0F9DhAjhiQx%2BDtiqlUpAqSqDIhS4JBBuFGMJn6UVFuwtSQpTZGgtn7Z8mAhF3Cbi3NoPlt6k2VqffU895jln5k5BIBAIAoIUJKFRT1qHuj9jfA%2BmQj56P/tgFYeNfjMxZkrQ4kYZboBpnTCEXp54E2sYCIh9xDF31MeQ4mV9lJ7yMUoe%2BpCCD8y4BdEcfVX5uDARAtB38MEj2wYA3B%2BwkFfR7qgr%2B7sUlYLHlwHEmSEmf37vk3Of9YF%2BzMCUpkAcvF2L8fPKhD93SRKCnQvAFJyo0iYdVFhfsuC1PquwsKQouFjJAKpZCbgRHx0aRZKxKt5H%2BKBEoxcOilDtA0eAjcWi2A6KFKYyJBjb7GLCWGSJOILEyI8QCEmu9lYIEpo42m9MIxuIef8VmKy7E%2BMuS0y%2B1xr4XNCacsw0TyKxOBG/ZB%2BzckVMHlUzBNSgEgLKUi9BqLUlFJKVkgaiLIHJNxYUwBdSS6lwIZYne9xgUUMCbbSFXSyQ9LKowukzCYQaGGaMnhMyJmcJiVvfKvC5kCMkWQWOoiph%2BwkRbaRldZFrMUa0ZRqjdmaO0YWE57SIlmHOSEkx%2Br%2BaUvMceDgaxaCcH8LwPwHAtCkFQJweJlhrA6g2FsAc7MeCkAIJoK1awADWARJAIg0AADjMGYAAnLGrg/go2Rq4IEQI0gbUcEkLwFgEgNC8odU6l1HBeAKBALygNjqrWkDgLAGAiAQAbAIGkeE5BKBoGeHQBIURJScFUJGgAbAAWgHZIO4wBkDIDuFIBEZheBH0ICQPATsRn8EECIMQ7ApAyEEIoFQ6gq2kF0CMxuao0icB4Na219rA3Os4EqeELb9SoCoHcftw7R3jsndO8NUKIAeE7fQYgeJfUrF4JWrQawIBIA7WkLtZAKAQFg/BkAwApCGpoO6BIZaICxFvbECIbQRQXt4AR5gxARRKliNoTADgSOkA7VDZ8tBiOHqwLELwwBYS0FoGW7gvAsBayMOINjlNaOOAAG6n1vZgVQtH4Q7D9RnTNTraA9LVBRjwWBb1wTwLm/jpApPEFiMYxsQngBqaMIGtYVADDAAUMiPAmBG5kQdX6tdwhRDiG3R5vdahb3Hv0IYYw1hrD6B6WWyAaxUDyxyHxodqdBymHdZYMwRajO%2BiwJFiAaw7DiZyC4Bg7hPBdD0GECIIwqhjBGcUbIAgZh%2BBq5kOrDBFijBqL0fLAgLYdBKwUEZeWHD9CmEMCrSxqu2BGw1vQ8x2htaqzUXLXrtgSCvRwO1pBC28GLW%2BwdI6x0TqnTOv9uBF3AfMEkLgYH/XWbWAgTAFoxg5dIKGyQSQESxqSOmjQkgzCSAHfm/wA7Y36E4Nm0gubLsIgHVwAdkbY0poHf4SQibPsDs27e4tpby03arVB%2Bt0HG2PtbYh5DQGe1sE4G0FgEnAhDqYI5XsXBY0Ii4BG%2Bd%2BAiCZb0B5jd3npC%2BaUP5w9uhDWnqYOe/ja2NtbbvRwB9zb4R3Bfbtj9Y6CxM5Z2zjQdx/2oEAwkEDSQzDXYg9WwnZOEhtqQ/ruDQGUAGCMMzrgvLMNgippQPDh6yNEfoz7ijVGaN0YM4xryzHWNOvY5x7jvH6OCeCyJyPYmhtSb4062T8mwT0eU7etTsQNMii0zsJ1un9N%2BqMyZpQZmE/4Ws3wOzDmnMuenPR3nXmt0C9kH5g9TrRdBas8lqwlhwuxGy9F2LudOAJfAUl0LqX0sJEy9JqLnWhvOAgK4abIzysVHa3oWrTQt/pGa00ebywBsNC680KbfXGur6aD1s/E3Zu9fyHfl/T/FvrE2Ctq7oP1s3qHo7bvr7aM4ETM6s4Rq66nZc5G5Xbga3akD3aPaJDPaZrg6Q4s4/aBD%2BCxpppJC/b/Yo4Y5AGcDY4Vp161oNpNpPrW6W7EAU47DU6fosAKASZToSYQGZiTAc5nbLo86yB84d47ryBC4946AgCpDi6S6Xr/4y6Y73rE7PqvqqAsFsEcFcE8jUx64G7nbsxJCm6UEwa27wZ0EmH27sEHz8ycGxr8zcERKqEC50Du44Ze5Or%2B6sZ%2BoeGB7ib0ah6CDh63pR5cZiCx4Gbx7CbF4CbJ6SbSaHoZ7IAKbZ59wqa8B54F5F46a%2Bhl68AV6mbgg15WZ4715MD2aObOauat6CHt4SCd67piEBaSH94hYpY2B55j7OoT4lScC7AfyD7WBpbbYZbLrL7PaDZNCFbFZv5lZFaf774n45BH4H45BzEX59DdY37TFrFX6P5jZ74DabGlYHELB7ELarbf7ernGZryGkEcBvpqHsF3A2EIj2HQGc4kBwGGF453YPZYCoFrYYEgBxoIgpD%2BBJoo75opCBBw4kFFpkG2A45m4rAhogCSD%2BAfapqBD5qRqSAJpcDRpmDo6ZpJCAFwklq46QZrZzqwnbbwlIlrBGZZDOCSBAA%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/sensible_classic_plume/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/sensible_classic_plume.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/sensible_classic_plume.test.hpp)
