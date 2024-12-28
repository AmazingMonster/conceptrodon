<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Repack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-repack">To Index</a></p>

## Description

`Mouldivore::Repack` accepts an operation and returns a function.
When invoked by a list of packed containers, the function concatenates the packed containers and instantiates the operation with the result.

<pre><code>   Oper
-> Con<sub><i>0</i></sub>&lt;Es<sub><i>0</i></sub>...&gt;, Con<sub><i>1</i></sub>&lt;Es<sub><i>1</i></sub>...&gt;, ..., Con<sub><i>n</i></sub>&lt;Es<sub><i>n</i></sub>...&gt;
-> Oper&lt;Es<sub><i>0</i></sub>..., Es<sub><i>1</i></sub>..., ..., Es<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Repack
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Repack
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

Here, we first concatenate `std::tuple<int>`,  `std::tuple<int*, int**>` and `std::tuple<int**>`. Then we pack the result into `NewVessel`:

```C++
/**** NewVessel ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewVessel;

/**** SupposedResult ****/
using SupposedResult = NewVessel<int, int*, int**, int***>;

/**** Result ****/
using Result = Repack<NewVessel>
::Mold
<
    std::tuple<int>,
    std::tuple<int*, int**>,
    std::tuple<int***>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Repack` is implemented similarly to `Typelivore::TypicalPaste`. Intermediate results are kept in `Capsule`.
After all elements are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<typename...>
struct Capsule;

template<template<typename...> class Operation>
struct Repack
{
    template<typename...>
    struct Detail {};

// Base Case:

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    {
        using type = Operation<Elements...>;
    };

// Recursive Case:

    template
    <
        template<typename...> class ContainerA,
        template<typename...> class ContainerB,
        typename...ElementAs, 
        typename...ElementBs,
        typename...Others
    >
    struct Detail<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
    {
        using type = Detail
        <
            Capsule<ElementAs..., ElementBs...>,
            Others...
        >::type;
    };

    template<typename...PackedContainers>
    using Mold = Detail<PackedContainers...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAA7ACspAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIphJrozIeJgKF7tHp%2BcHX3vvJ8cnBEwLCSBkBJgAzG4CABPO7MNgAOiREOw/2GxC8DgubiYSQUXnoEKsp3%2Bn2%2B5O2vzJFwAksD6GxBEwaq8dlSKRzDv9/oD6czMBCoUCQfzBTC4axMEiESiLsgDAoXgB5O7EZkZFFoggYrEAJVuTGQAGtubFiScLpaLryRWDIeLGJLpZrTlaLujMQRrph6nQLiYzQGrkTuR91hcLEwlNio%2BxQxarTbQQL7cLk2LYY7Ecjwdg5QqXh4mcFoqRrZn4VKkdgGYwCAoXQnLR6sTdfbRBUXfSFiIKa0C6wpnbnG26A%2Ba3W6vGkjOW7v7wVcLirouqBH3a4IhznUeCJ1agyGSWGLvrkMs0gA3TAxpQgeNupOi10HyH/SeJtOi%2B0Vp07/NRoWshMCWxAnKQ74ftaX52lCv7ZjKuYAYq2LAaBNiQR%2BDqVtK/aMgQJwKGWmGTthf4InhdYWERJGPvBVYIkqBAINEDYvpao5Wi2XptiBHaQl2IE9n8kKUYIhHDtgZaCehG4DoI1GSWWTEscQ26Iai7H%2BoGWlTjOwBzjeEJLrxdC0a%2BbjmR%2BOJ4gSKZuGJBHqWWjmKTuEG6VBKmsc6nkcbmIAgA6R5NtpwZ7g%2Bn58rBZEIcohpGpg7hoT2DYjlp07BAZACynjoAuJk%2BnxgrxcaSUyalkmBcFEUkrE4XmqSnJvE1lzYKorAgjeLUfM1bLxuY4LBPKXhYAuUJeF1jaDcN3hjYKaAMKsST1tNvWXKEmAAO4AGrPHYrKUjyMH2bFDEnMQwBpZpF2YAAjl4eDEM8FwQGkABemCoFQ0oQBdV1zAVxkXJIcxajqXqbbt%2B1VCFrXbBcQiTXkSX6vitBej1JyZbOSNJCj6BowSXrA1De2KrDkLBAQZbU5stOCNsDMEDsmq1X860I0TGOHVypw4wZ3Mk4up4GsagpkzD/E3YFuW0Og3JvlpwzoNVk2ElTggoh5oUq2rU2ayzzPbNrJF60F6v2XTJvpSJu6NZzmwXAAKs8mP9ackyOMgAD6gHRAQb0EKrIAKJKftpW4QtlnjBNCyiYPsxwCy0Jw8S8H4HBaKQqCcJZljWO6SwrEZZjgjwpAEJoycLEaIDxJICIaAAHGYZgAJzt1w8Qt83XCxLE0ipxwki8CwEgaBopCZ9nuccLwCggFPVdZ8npBwLAMCICASwEEkXg0xQEBoMCdDRKEkqcKozcAGwALQ35IFzAMgyAXFICJmLwSWECQeCq20fgggRBiHYFIGQghFAqHUKvUgug2hbTVEkTgPAU5pwztXHOnAlQH33l6b6Fxr730fs/V%2B79G5mFeh4U%2B9BiD%2BjLlwOYvAV5aAWBAJAJ8khnzIEfTh3CQDACkGYPgdBARqUoBETBERggNGhCg3g0jmDEGhEqCI2hMAOHkaQE%2B%2BElQMFoHI2BWAIheGADiWgtBF7cF4FgFghhgDiCMU9DRjhrxWOzpgVQGiD5rArtTKomDaB4AiGqZRHgsCYO1Hgce1jSDXmIBEVImAbh2KMEEow1cFhUAMFdHaTwtorkzhXIBwhRDiHASUqBahMHwP0PYlA1hrD6GCYvSACxUArQyFYu%2BKtjKmALpYMws94nEH/s8eACw7AuIyC4BgyVsitFIIEEsMwBhtDyOkAQYxFkbJqNMfoMQJhVGmQILooxPAtD0FMhwnQRg9BWQcq5dztlPKmA80oazJnF1WBINBHB07T0wXPQht8H5Pxfm/D%2BlCIC4F/nQwajDmGZIWCxJgWAYgQFriASQ4IETt3BIPDQkgzCSBvpPeIN9276E4KPUg49y4IhvlwG%2Bzd259xvg3bu%2BKb6AtgXPBeS9K6ZPXlvdhO9cEH3IJQPhtCL5sE4A0Fgl5Yh3yYABWcXB24Ii4E3b%2B%2BAiCjIARA0poCJDSEqUoapsDdDCMQbieRfyAUz14HPHBe8D4XAIUQsF6qDKau1U3KhqAaHRHoeCMwTChWrzYRw4NXDaFSuPnG/h8p7Gaq4FPGgGNWISKkTI5RWjFGyNUeozRsSdF1j0QYzBxjTHmMsVo2x9jHHZ3wM9G5bjMGeO8YCLR/jh7ZyCSE2R4S1jZyiTEiu8TElKBSc2rKwrslMFyfkwpWiSkgPKea2QVSYHZxtXUjJ/SrCWGaREVpmKc6dIEN03pi5j3WCGS6kZYyL2TOOTc5wEBXAvLaMs4ojz1mpE2ZkC54xkjAb2e82YRyOinOeWBxZ1yahnPuQBj5hzbAIYWa8xo%2ByMO/MWMsH5jDqX/IwXyzgILiFP1TRqrVOqNCvVhQasNiKo2sJRZgNFAxL3D1pfSrVRKEjtwHuCYlpLJBtGdVg%2BethBUsLXhvbeu88GJplefS%2BHBFUkJYAoS8b9Lz%2BuTMMPVcL/56A3WUsB27IGWr3ToEA4JSB2uQdYx1FHZ7YIlfgqghDdP6cM8Z/kwwg0hvhWXcEkbFMxpQMmhNvD4sDAM/jH2Rn24%2BxMwQH2qhH4iOzeIiAkjYFFoLbE0rKi1EuK0RWwQVbDGtswCYsxYgG2xKbWksdNjnEdvGbA7t55e2xP7YE4JoToSjsiaMydvBp1JLnWkhd0a%2BA5IUHk7aa7YlWdNRUnd9malOcPcYRpp6h1vqvTUKx6w9YPsGcM6IhrxltPaCcvw365m/qWXM/DMGIP5AyJ93ZGQftrJe5%2B2o2HLmwde6hkHmHJjnJwxMO5cPCMKG%2BWAjzvKvMcH80/PTBmLjpYRFl5j%2BqSBsei8i0gqL0WUD%2BQJkAHcETgnBPEHuUnJ6s9iCy7HLrOACuXtTuukh4h4v7rESezdJBdy4K3MwPLh7gk8/zuTMW/lfz57JpF0aFjxLSM4SQQA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/mouldivore/repack/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/mouldivore/repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/mouldivore/repack.test.hpp)
