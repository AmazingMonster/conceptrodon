<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ModifyTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-modify-types">To Index</a></p>

## Description

`Omennivore::ModifyTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts an operation and returns a function.
When invoked, the function transforms the arguments from its argument list according to the `std::index_sequence`s using the operation.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> Transf
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>0</sub></sub>&gt;, Arg<sub>I<sub>0</sub>+1</sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>1</sub></sub>&gt;, Arg<sub>I<sub>1</sub>+1</sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, Transf&lt;Arg<sub>I<sub>n</sub></sub>&gt;, Arg<sub>I<sub>n</sub>+1</sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
ModifyTypes
 :: typename...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<typename...>
struct ModifyTypes
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

We will pass these sequences to `ModifyTypes`.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** UnaryMinus ****/
template<typename Val>
struct UnaryMinusHelper
{
    using type = Vay<-Val::value>;
};

template<typename...Args>
using UnaryMinus = UnaryMinusHelper<Args...>::type;

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = ModifyTypes
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

The index pack within each `std::index_sequence` will be wrapped into `Prefix` to produce concept packs.
Then, we expand the concept packs alongside the arguments to reach the items at the intended positions.

```C++
template<typename, auto>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

Note that we wrap the elements inside `std::type_identity`.
This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...>
struct ModifyTypes {};

/**** Base Case ****/
template<auto...I>
struct ModifyTypes<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename Target,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            Target,
            // Collect the rest.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            Operation<typename Target::type>,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<auto...I, auto...J>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> Capsule
        <
            typename decltype(front_args)::type...,
            Operation<typename FirstTarget::type>,
            typename decltype(middle_args)::type...,
            Operation<typename SecondTarget::type>,
            typename BackArgs::type...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct ModifyTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        template
        <
            typename FirstTarget,
            typename SecondTarget,
            typename...BackArgs
        >
        static consteval auto idyl
        (
            // Expand `Prefix<I>...` to count arguments before the first target.
            Prefix<I> auto...front_args,
            // Transform the next argument.
            FirstTarget,
            // Expand `Prefix<J>...` to go across the distance between two targets.
            Prefix<J> auto...middle_args,
            // Transform the next argument.
            SecondTarget,
            // Collect the rest.
            BackArgs...
        )
        -> ExtendFront
        <
            decltype
            (
                ModifyTypes<OtherSequences...>
                ::template Road<Operation>
                ::idyl(BackArgs{}...)
            )
        >
        ::template Mold
        <
            typename decltype(front_args)::type...,
            Operation<typename FirstTarget::type>,
            typename decltype(middle_args)::type...,
            Operation<typename SecondTarget::type>
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl(std::type_identity<Agreements>{}...));
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmGgBspAAOqAqETgwe3r56KWmOAkEh4SxRMXGJdpgOGUIETMQEWT5%2BXLaY9gUMdQ0ERWGR0bEJtvWNzTltCmN9wQOlQxUAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYSa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzMFkN4sDcTKC3F5HLRCABPWHYYHA367G7YVQEVwAMWIsk%2BB0B%2BJYSQM%2BNhbgIyKezDYADpWWjgdNiF4HDi8YTiYIYQB2KxCu6wqyXYEUqlMGlwmXUzC0%2BmM1iYVnMtE3SFMBQfDyCJhzMg3VWMdWa7D0NiCBTsy6c7kEXn4hjoImyWmG%2Bom2nWzC2ggKTXs0HoqUi4E3GNmwOy%2BV0hkWlms0KYADuAaD9vD0djXjSRhuAFlPOgYaC7jcfcaQsRaemszbGMHNaQcS27aG86DJUCxRKMT9DjdlMRMDRVKT9uT40qVcmmZgO0wEagHRc0AxNkkXePJ3hp7DqwQucq%2B8OrqO3EwkgovPQZ6dpfO5Rek2rU1q846z86azvB96CHKUR3%2BCCvkxUcAElKS7eoumfQEsUg/5AVfeD30XL8NTZX8LidHky3wKhkQAFWTD4TCjQdLzA69bgsPVMEApRkMwhMPzXIhNRgzciJdEi8DIyinlzNxpnQEAQGCLBVAAfSUABHLwXg/GCe3RAiaP7WM4ywxNFWwhUl0tfDsB1Ax9RuAB5J5iDlDJN30wSx2JIgACVUCYdB8xjXT/P0gyuKC/TaTC4KY3NZcbnIhpgEwAhSEiqKYvM5lmOQABrC5iGAe1LiigKCOKm5pic5AdQEaZMAANzEG4eNQG48HQZFaFSm4IC6/Ttm2XkkkMCsTHiDQDynWl%2BPDUMxrNFq0C8QUEp8VsPiifgJzNBBWLGRKCC1IqytjCajym7Vms1KgBQIBSEoUFKjuOm5%2BrixyGAUTaWG21iQjxJr8tWwRDouZ6Y3i/Kkse0GwderJOh%2Bm4J2mEGwZuLLcvykM2Se4Kli6gBabVb3vR9lVx8K4V62N0rYG4sEhc1qBuu6saWGTzXbamY3s6InIEHCU1YiH9o55M0WhtHadYjG8oKsWnlDCnYzDfsuuMoyzO/C5gAnQM1pc4rC2CYBS3LStqwZ2gmbajqICkhXMAUtrWxRWkdb1nN2Vou5NSWfH6JhgK6LV3GNY/cPBeXLSrL1bHmQ9zB9btQ2Y2N4tvN8i33NQLyfL8uFE%2BTtsLNAgdxUDziFzhS7WRg1d101AApAT/2IjARIoqjaQd2T3UwRSVLUncNK0jte7kgelMwVT1NpJutM3QKw7fIzV4jrW8J/SzdRs3nHK6VPyrb/cPNQTO/Nx5eg%2BCyPlZKtxubNTebgJPBiGmEWoaf6WbiEaoBDoC/slH%2Bm9NSyyxl1I%2BrlEJ4CqtuWqDVaBNXXK1dqnV77dSfq9XEQ13QwjGqdVQ50ZpsjmkQaqS0XQrRzDcDaJBdo7RuDQD%2BLo9pJVRmDIhJDLK12ZNdWQrMCqS1hgNci71PokG%2BgQJhf1qGAyDJw56b9WHAJEc9HBqg8EjUIROSacIW6kK1OQlqwAWpMGQMSGyMjWL4AqiPOhSUMxJwYGaDMLV2FtiftwgxF1G6shYG1dA9AhEPWwWIiRX1EZyIBsAIGB0n7/23EAhK39MF9QGvDaobCmHIwSek2MECCpKxvvpfGmCibhkAqTECmCIoFOii/K2TMBGCFCezEAnNWTqOOvvfmDAo7qlfu/T%2BqSCCOwlqA3C9NqjW2TBAQJ6BglO3uh0rpzIellT6YfUy0ykmAOARM8Mmziq/yKQoR2JSyqqyvGVSOuyhaaiLl7UqRsiymzLLQEaVYZmM3mbbWg9sCDSU6cmZ2WBBBu0LrrJOLz0Q%2Bz9gHPSKsQ63JpuvFUGKHnRwsrHfUTyYXF1zBGG%2B6dTYX2zuOXO5987u0JTmReldUUMSxDcTy1R1hpDqqxW87EoKXHubefxzJ64oN4qyJuHZpaalsjY4g/9Z4j2JRyE%2BZtSJd3Ej3YFMlJ6DxnsPTYU0x7HxBbq6eirDUGONbKna8r9XqXjkvKMK9DIRyxZ%2BR5uLd4fG2c5V5MY3JUrzr5IK187kYrqVTBpz9pkqNGZDEB0bf77PdGoqZnrMoWMxgVKB/rgoVUcPAmq%2BIkFipagCrqPVo2aO0QQ8aeizpwmmtgWaGh5qUOWgotajjNqMNYiw6YZoxlKOOj4twzay1XRZvdE5UVXriMMJI4g0jZED3kXExRT840EDTdWgauDhp1rHYYltZC20ULMU1SxqQPg2PpngexmxHEEGcYwNxHixkhm8Q24hviql8MWcs0Js7grzsiVI6Ja7YnxJHWVFNKSE0gYyTWTwCM715Ng8Vc5VzirlNKbGSpllcRug9DdXNj9o3NPFtGqt%2BHnrCVEt3OENrogKoNe8Re0b9Ic3Xmy2lzGHL9OgWDHV6CIDnMCmKP2T88PXLzdxzpvHPmXzo5WCjqn9K/yo08ZmgjVmXO6U/X1AtsVDO3Yc0FTxJlJqabMpmgGQn6cs1vJDsZjMDNM3TeDFnzTCZKtpUOqnBXStZM8g28mCzvLNl87O2nMAQABUCkF5pwWu3pHSz24X4Wil9qyf2ZdwrMqBC60KCp3Uhe3ni%2BOYWU55rJXxrOJ4c7BoLm4GrJdt5lxohXQLqE0IoVHLiVgVJWL8sYmhMkV5zDgh3FCVitJty7mDEvcC%2BwbgADUmDIg4gK91zUbjNpVVyHkm3USRgsMfSq1UPr4i0cQMtNwkFqWFBYfiIdhQ9avKyuQzBiDIhLMEQsO2LjBZfptzqBE3I/YaP9wHCgAASHQHIYmdaSqL5ps6ndpATcHMknsXgCyjz7DFQe4SeZAgi9Xod/YBwwIHTXqew7pwjpH0R3ZYy0kc3rN4gJk2B6TjNrdjsuhJsBC83PbgliSkwKgS0agCH5%2BVsBoWKckvq1L%2BosudxISawxjV7wMRRpvr3FgTBspOzNUPOecIuDWeN9qkApvzfO37nqi1H5QQEy4F7u3MCQVO4t67817HaQAFYCae9tzpAiMkL60kZ7Twsm4ZLKfZ8U0uldVvYiEF4JIeRMDoHZcBF0Y36s57z6kAvRfHwuia6LsmtIsdwg0BLDbW3sdR%2BwB2JvbgzCt57xH/v7e4SSCH6iOEBNQ9hkJyy0c1frbA/q/P2vPyNcy7lzstwPeW/HLb%2BPtwnfu/D972P2koJT8j4v24KfvYZ/FfG9ici7wS%2BTb/JVO6%2BpogECSzJBQ6oP%2B0jL4djl756F7vA15ohIrAgcArC0CcCh68B%2BAcBaCkCoCcCPyWDWDlRrAbDzZgg8CkDjLIEwErDZQgCh6SDMgaAAAcZgZgAAnPQVwKHjQdQVwEKEKNIHARwJILwCwBIBoBoKQEgSgWgRwLwBckIUQVoCsHALADAIgCAGsAQEkAiOQJQGgJSHQNEKEOqJwKoNQfEATPEJIDcMAMgFVFIMyGYLwAXoQCQG1HoPwIICIGIOwFIDIIIIoCoOoMQaQLoG0BmI5EkJwDwLAfAYgZoLwGIbZAiKoS6KgFQDcAYUYSYWYRYTcFYWYN1B4FofQPdtNlwEsLwNITAaQBAEgJoUkNoWQBQBAFUTUSAMAFIGYHwHQPiB/JQBEFEaQBEMEDDqEbwH0b9siLZBENoNkoMaQJoUGLZAwLQMiD0VgBEF4MALeLQLQBctwLwFgKbkYOIH4fgBODUNylsSgQPByviFMcEPiNwSgUiBEI5H9h4FgD0WeHgPwdsaQNysQBEJXg8HscAEiEYFESsFQAYAVOtm8BmLzEgQQc4cIKIOIB4Qid4WoD0QEfoIYMYNYNYPoHgBEBcpACsKgHuBkFsQTFJCeKYJgZYHENET8cQC7ESRACsFUPLn4BAK4BMK0KQIEHMCUGULkKkOkAIDycKfkBkP0IKUMFMB0NkrUDMOKXKZ0Iqb0NKYMDEFMEqZ4C0HoBVI0BqQsFqWyTgZsBIOERwAgcIT0WIckYYcYaYeYZYZQdkRALgPYQUfgcUYQaCSsDtL5EMKyaQGQZIKCMyPQaCJwRoJIGYJIGNBoKHvEPQfoJwLwaQPwaCFwMyPEFwPENQfQWwfEBQcwZGYkCIdEZwBISAFIaCeUQoRUUoXEWoXUQ0fkboWwJwA0CwHVEKATEwLHMWFwPQcyNmecfgEQEydJG0Aia4cidIKiUoOiX4boK0UEXeIMZadaRWagZwLESoQiDcIkfaakaYbqEOSOWOTkagHkdEDCGCGYD6aUbIZUTedUfkeofUW%2BY0eec0UwUITQNbNEBchAN0X4cMQMV8RBX9mMRMQ4FMTMa2HMQsUsZgCsWsWIJsVMbsdiQcSgUcQqacT0RccgAiFsAQTcR0D0Q8U8ciC8VsCge8Z8QQT8X8UoACbhSbHWeCUwJCdCbCVMbOUie4QubIGib4SgauViSCTSVYJYPiYSfACSWSTVJwJScCtSbiXSaIYycyUpe0Kqc4Fye6MqXye6EaUKW0HkKKZkLqZMMkCKV0BZbKQZQqQID0OMHZbyeyV0B5bMMUJqfqTqdkN5TMM5SaasOsOaUUamVaZEX4XaSkY6YOabMOaOVQd1B6ZOfeVmU%2BX6aQAGVgDEMGdwemZmSOTGUKKHvQRwaCLGfGZIG0DuWIdWbWcQbIQ2UgMofEZ%2BW2ToXoRwN2WkSwAoHVFVHVGlUqNMLYROQ4dOZ4YiW4RIKJV4UuRJToCAKCKQOuSEdsVufFaIXuc2QkUkaoMNaNeNZNe%2BIOhALke%2BXedNqCHle1eUa%2BbebURod%2BfkSAGNXngpBNfQQpFNbdGdQue0cBV0T0dBYsVBf0TBeMZMV8YhYIMhTDfhWhasesVhV8ThfsQxTse/IRe8MRaoJceRbwJRXcbwDRTDvRW8UycxbwKxf8YGJxSCS9TxXxZmAJV8UJUtSiWJWtRiZtdJTibSTYA8SycpV0FsdsA7LJdYPSagbpVgFLa5RyS4CZV5f4OZQKYFVZY5RkKZdZU5XrcafqfKRyX5aZT5WqYaWbZZaML0DbWFQ7bKaaVFe4ftTaQlZwMkedWNY9ldfiDdVlSQDlUUSUflYVUGZaWVbECOaCKCKHiwY1YIUnUKPmT7YdeIbYDWb6e1aQSAJIKHhGewUKIIdQZIEwVwLQWYIkNwaCAdZWbnc%2BZaTYdnS3VHYXd8cBRkMXUAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/modify_types/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/omennivore/modify_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/modify_types.test.hpp)
