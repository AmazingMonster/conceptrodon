<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyKindredRepack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-kindred-repack">To Index</a></p>

## Description

`Omennivore::EasyKindredRepack` accepts a list of packed vessels and returns a function.
When invoked by an operation, the function concatenates the packed vessels and instantiates the operation with the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Oper
-> Oper&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
KindredEasyRepack
 :: typename...
 -> template<template<typename...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<auto...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<typename...> class...> class...>
 
KindredEasyRepack
 :: typename...
 -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<typename...>
struct KindredEasyRepack
{
    template<template<typename...> class>
    alias Road = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<auto...> class>
    alias Rail = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;
};

template<typename...>
struct KindredEasyRepack
{
    template<template<template<auto...> class...> class>
    alias Sail = RESULT;
};
```

## Examples

- We first concatenate `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>`. Then we pack the result into `Container`:

```C++
/**** NewContainer ****/
template<typename...Args>
requires (sizeof...(Args) == 4)
struct NewContainer;

/**** SupposedResult ****/
using SupposedResult_0 = NewContainer<int, float, float*, double>;

/**** Result ****/
using Result_0 = EasyKindredRepack
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::Road<NewContainer>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
/**** NewSequence ****/
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct NewSequence;

/**** SupposedResult ****/
using SupposedResult_1 = NewSequence<0, 1, 2, 3>;

/**** Result ****/
using Result_1 = EasyKindredRepack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<NewSequence>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
/**** NewWarehouse ****/
template<template<typename...> class...>
struct NewWarehouse;

/**** Warehouses ****/
template<template<typename...> class...>
struct Ware_0;

template<template<typename...> class...>
struct Ware_1;

template<template<typename...> class...>
struct Ware_2;

/**** Dummy Arguments ****/
template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

/**** SupposedResult ****/
using SupposedResult_2 = NewWarehouse<Con_0, Con_1, Con_2, Con_3>;

/**** Result ****/
using Result_2 = EasyKindredRepack
<
    Ware_0<Con_0>, 
    Ware_1<Con_1, Con_2>,
    Ware_2<Con_3>
>::Flow<NewWarehouse>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

Here, we first concatenate `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>`. Then we pack the result into `Stockroom`:

```C++
/**** NewStockroom ****/
template<template<auto...> class...>
struct NewStockroom;

/**** Stockrooms ****/
template<template<auto...> class...>
struct Stoc_0;

template<template<auto...> class...>
struct Stoc_1;

template<template<auto...> class...>
struct Stoc_2;

/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** SupposedResult ****/
using SupposedResult_3 = NewStockroom<Seq_0, Seq_1, Seq_2, Seq_3>;

/**** Result ****/
using Result_3 = EasyKindredRepack
<
    Stoc_0<Seq_0>, 
    Stoc_1<Seq_1, Seq_2>,
    Stoc_2<Seq_3>
>::Sail<NewStockroom>;

/**** Test ****/
static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyKindredRepack` by uniting `Cotanivore::KindredRepack`, `Sequnivore::KindredRepack`, `Stockivore::KindredRepack`, and `Warehivore::KindredRepack` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyKindredRepack` to produce partial specializations.
Hence, we create the following helper classes.

```C++
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

We will leave the functionality of `Sequnivore::KindredRepack` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyKindredRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyKindredRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCCSAOwAzKQADqgKhE4MHt6%2BeqnpjgJBIeEsUTHxSXaYDplCBEzEBNk%2Bfly2mPaFDPWNBMVhkdGxibYNTS257Qrj/cGDZcOVAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimMmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMCWCyG8WFuJgSbmQM3QWCosOwIPM4IYkK80Nhbi8jlohAAnqj0b8jrcPA0GHgAG4kdggADSwXQxEw6AASk8mMgANZfQ5A5hsBTJPmYKmoGn0xkwuJWK4ggiYFjJAyqvEEYnPUWYAB0RrJVxmxC8DipTGSCi89FhSuBV1V6s1mG1usYrENxoSaNNBHNltZDHZnJ5EoFCqscXuDvJ1x2twsTCUVqUIATLo1TC1cOzbo9eu9RoNqNukNTnw8giY8zItx1xbYpew9DYggUJsuZotBFuIbD3N5ArxNYa9bxbbVjAIClLZL96MVINua8bapzebcBdz7vznv1C79FYMCk%2BAHlnsRc5lu%2Bvbr3LY8J7RV%2BuTCurg%2BH150kZG09GEEnuW4r2iW8BCndtZ3nX00QSR0H0/ONEITB9d23TD9x3Q8S3g08q1LS5gA5GdO3vdc/2CYBbi5VAmHQYDQJfOs3zhEiyI7Odj2wEAQCbfdHRQ%2BNlV%2BJMeWQDZ0jpKU3FTdgs03QtlThd812wosvRbAjK3PaVa3rS5SHUjdXT3LSj10s9q1kOsQmIGxTMEqyDWnbie1IGFv3XFz8LcmDBAsBQTJ8jS8J0g0LwIBBoi7VT/R7QM%2BwHNkOWHSN%2BTHOyjOg8iCB7XivPHezoisOF3NnYKirAmK4t45ckN85SLPzFqsIin0yxPPTL2vSCGEotcn37Vi6FMz8mp/W5qIAwTmNS0N0ojPksrCn88VM6a13km07RwyrBEKo0vMOghqvg0LLm2n9oti4g4LLdbkL9fjsLohj0DxcCb26RcpoVVDhPWzS2vMjrmy68teuI0jMHyrsl3W2baPoxiFrG9i3E4%2BHuMe1E3s9UTgVjYnlzjMTrkpIRMAARy8WkGQ5fjB2WkdBW%2BEF9XFSVbhp%2BnGflSalPBnCmAJVAGoDIN%2ByEBACQIe00Mp0HcMhqWkplxahxWqNhdJ5WnUTZMFPTRSVfanDVfFoheMI/T%2Ba8V5MC8m3JaNAA1Ro8CYCJ6ERxKRu1tnMrxR3nbxL3iB9v2PgapGSYB1XrYlu3erA/q/oTh8g8xiav2u7aUcA54Fp%2BgbI%2B933/fjgGRMN5zLe1Ju4TdtObNhrjYKGmb/1Rz6McwV88RxhHeMJ54yYN4HLmTlu1e0l3bjb6yqz5umnaxJe/LYW4ABVPVd1PPar2OA5BIPWfDdmw43iO4QP54vKjmOa/g7thZB%2BeU9t1f9PLrOiUc7JWfEPNi%2BcAa/j7iXKUsJQIALvM9D8cIZi3mQAAfVEDMPEiJ%2BIsCYPyTA6D0jABCOgdBBAcF4AAF5EMoUuP0EAX7Vw%2BMsWu%2BcgboWaqLZuPDW7H26tge2j1R54x7sXNGTE4EPDAeNDicMx7wQnkJcmZNxJ0RqNJekckFKZgtjw1SbhG58PkgI6GNl1702dsZYxW4xZmJ6hY8OW8nLrRXgaZhsdPLeULmudxnj6DBSuhhTqpY7pxXRAnS%2BaVr6hzhM4rYwI4QBMwMdQRXkEmYHKm4FJF10m1XuvjBOn9fFmTsbw8p/Df6COERnCCgDTK51kW%2BdaJSbrF3mtIq%2BGVVpbWQUYpB005YKyVjk0%2B9A0nP3GVkop2Bgk3XXOEh6C5BnAT4gJS2H1GLfUzneBhddp5cI0t/ee7jzFESNKI7u2cqLQMkYPYe8iu6dnHgJImDdDn6PKYY2xhYDyQyPtU85Ds75bxsV/ExO8l5nMcWvTJrjSlQv3uCxFnV94IofP46Z3jTJYujiwoJzlQlGiWfFJJgcQH9m6brLK8TQWJLxHvYytwUlpNRBk%2BlWTGU2BZdMvJ7KCn1XfsqAuGETkmJhUI9OCCoI3OGpSmRw9WmiqLtAzpIFg6xN6aszaqzgHoH4sEVUwBojEM5X06aurSkLPXLgkA%2BDCHELwKQzkFCcEEANSAdItC3V%2BnmTa4BaDMGpnoW4O1DqiEkLIb6sNHr%2BLeroYubATDsUKDYSdC1CzUGOAwVg0N4aCGRuddG/NcavU0MTQw5NuS00rOtdtdlmaHykrrTdAmGzRZbK%2BnCGVg19kcLUYi8VlTTFAtheeTuuNrlANuTRLtDzwFPKnS8pRbzJ4fM4ZTESlM/h7D5kQAUcpmYshiT0qMnMrjc0jFKeoqBD1M1gQXFUw6/mjvdjUmGwrNYpXksQaO0RB3J2JYIi%2BCrqXs2jPXGeOwkwpjTPJDMIsR1zwlQ4qVHc/6fFvcgLyP933Asepk8%2B0sUrgbiW4bDt8rFb1mR/FVxzIUvtam%2B9uFyP0WN7T3JpSrSltNVXO9V8Ddmyoo5y2jhtkKfKNmKxjsmR2SuEaxidlyFFiLlb3OdQg2ILrkdjVTsFXmCSnpuo2MGNFSQetos2eijaaR%2BRC5Dpy0OKcw/uu9KKZOOdQ2O9DbGCNueQBi7h8nnOfoNJknFDnX0KbC/CkKRL1Ykrqg9SJFKtZkd6fEg9STRPUcSbMjJB7slxZqi2r9fGGNeaq9F0LGH2Nr04%2Bp7j4DlWQNnXNICXTT00szVagNVo/3vGIFRze%2BXSwcryzMoqTbFnJfxjq16Ha7F80XW4RrCEDkmd%2BcxlDIWfMufq8pg0VyKLqeLlpugOmsYnZ4quozG7B3btM5SAA6o0TACAj1Mgy%2Be4UXNvQ8y2LcN7HJPsPsg1819QHEuHdoyRy0HsPt4EhCoyHO3gPdmiUtLVesVxSZBGZuDOjENo6wkxiGi8lOzNqSD7e38MfjseiVesxHv3Bm6zfOEtPsqGQcuJxKFWylQ/J1bBnvmjv%2BfW40hVedWuZo6Z1jVjW3DM75%2Bw5VW2os7ZF5ZfyBGqeToRuI6BAAxWgqAADuV2R76ZXYI5RxnB1mcklo2S1mkMqRy9tsnkKxcHf87TjzwXhe%2B5h/r1ztOguVah37sLqvoiRaHaHynmHSzx8cvFkGwHSWpdA%2Bljn5HA884nA5Nlfrgfveyen/l5eysgZFUnHXYNkOx7q5L4TfaZ3yq1rL3j9GfwK9Ll17HZ61r1rXH1gNiPPso%2BL6VYgkyDIl7KgVmba46%2B9cW%2B9M3ludn1L2RtgdDctc%2B%2Bq%2BjsPjODcqeeXOY3c6d9W%2BkXnJdij7drtRyTTXn%2BEy7tuAASQUAAFlPB0AqA7QhQDggQzMXwah%2BxMpOQYQAA2DQYA2gL6ZA59ZPfUTHBVAA1A0Au0RqR8BoHNCsAQGYTAVQZIYgW4CIVATwW4OkMQJ2aMKgMQJQKDQGQDJvBeVyfzdPXDYDM6VnIOPAkAsArGdPPKPGeOAXRUYgtBMghgCgqgmgughgpg7wR9CwZKd0aeLg4/KmO4AA5QJgE1CQiAs4AnJMGAy0eAqRZA0wk1EwDA50enSGHArWEwswzACQog7NZHJQlQ6g2g%2Bg2gRg5g7Qtg2gDg/QqDD3bXbzfDRnSxUbaFARFJEQ3AhQJw3wwgulSbSufFM%2BWQ/wkgwItAZQ1UVQ0IjQyI6MXQzg%2BIndSkAAyRCwi9Y2WwuA1aBAlwjQSRfozAlvDwqJbI9owghvBQ0gyo4ItQsIiIrQ1g9gvQoGAwmeOzL3E/K2dwlPWHKnCvDkf1IXc/PY8PA0dPMlTwlKNoz6Pwrnd7OfFnUoqYgI5AII6okI9Q8IzQlgyaRouI/HCkYwhQLkNiDov7dRbo24ewpAgY8BVw2eXY7AsYrw0E8EyYxOaYio8gz4%2BYuopYyaaI2ItY5o2zJuezJPM/bcGLNvFI7DY4vDK/cLMTXPeHfsNojErGSjAotI/nMoxQ2YvE2on4%2Bo/480VYh0dYn/AEWUwEAnVo10fKAaSwqAuU9Uqw0nUXGHUwgUHwrIrWbAVMYkH7MfEAGErwP2QIx2QWY9U0vEXU/kfUjWfWL/aHPYx0/U7sDkemPADkT4CABcMwRA8wRAsQtA%2B4twT0k1AOfiX4zAZYPPFKI0hQE0gvTLKM1aZ0r9c05IS0okd46kQwL7FmdM0cOEaMuOcrPHN05E/ySs1nH0rwP0j4W4QM40YM0M24xiSMhs9teMxM9k24FMtMkfHrCsrMmMjWXM/MwI2nMHRkUsscznTMvUqc6smMWsrA%2Bsycj4b0jeFsgMoMkM4MzkugXs3c2MkAAcpMy0Ec%2B0ictcqs%2BvS4Gcq0947DfkEsk9Zc8jBsl0msp3DU2UtUu4E3P0mYYc1QVgDUKUTo3dYC%2BUrdMECEKEWBOESorYZIW/YpYEg4W4UITAC3dPVU4YmPGHS4YgYARsg8/0tshNVAKgUsCASi6i5YZiaRSQQctnfsQi4inKByICu4IQLwZIfIa%2BW0WgfsTo87US8S4cSSggdBDQBaPiqQuEI1LyKgc3XMLSnSggPYLydAdYWOf6GUu4HkRS0iq4CRD4O0JSlS6Re8sssfSfeVT1AgUS0ZI1AVaXDyrynCbShiAgPS4KvYRtdaO1Ty2CvEYy/M/cAXRbQYuENSgSgDftFou4PeD4aSyEpKINKsaIAgCAO1BQb0dBVMPESy%2By5SjJOStICSmqjQVERMwwhCxC%2BC6mGoAQJibAaCpU6yowjqk4IEBUu4PizJQa1WAtR1KNV1UtT1BNX1bAYiKimi30uikqitRi5i1itNDijVLi283ioizJIS/CkSsShqhS%2Bywa2Sq6pQG6qS9BLgVS0681OEDQLydoW4MwLyBIMyzK/C6qqSu6u5Oy5616py40%2B0yk/VQ1QQTAE1YgM1QojSwQLyZq8vPyhGrAVQVGtIvEH6swCK0pO1NkSggm%2B%2BNwAG4pJKz6PECaj6w/IGvdbKyCzot4iq88IqkqstMqtgbmqqiGpSn6y6%2BSkG0Wlq864avK3/PeT7YgXq/q2Cwa9q4a0avCvdPi%2Bc9YNMTo3bcis4y/L9IOHW97BAPWj/Ma/C3Wv8Vsg2ngqFZk64y0WnZS7guTI2vgk2l8oOd2rgT26k7U428XOHHiw4ohEmtqyke4HwFgYkW4VinwWCKausyKV2/sGsD2ww90n2tLH9AQF6oO72vXVEwuhgdBaOjY9OqGcuy0bO2m6Dameqx6yWsGzTVuxq56swN6i3O2jguEbOr6gyF64qIuv60e2mlm57CykWjugCSWquhaZy387VLY0pd2rGlXIurGuZHxB8AOnnMe0e6OuZUyd26Oneyu6e1LfiB/RmoigehKmW/eHKwarmwqpoPmxa8qyquEJeye8W66wB6WmO2WpCoavdE3dYJoBAKCmC%2BgNWiByBm27W06g9fkYgeglgNOr25jWkvzeuk6i3T87B1AFgV%2BshnBz4R2/Bmk2rIhguy0bDHOmu%2Bh%2BxfbMLTOgLYu3OngwhiXYh3h6u8y/CuOlgBOpOqilOzsPBvbZI5h2WOmNhhIhhnzY6yxPh9hhRjWIOfmKukughtDTRgxpusRvdYBtu%2BemS6BKx7upShIPu6hihqjWqrRsWlRoBlR2%2B8B4GmxvK2yxS9BJx6G1M2Gjeh8Vh7egxveryUyVhwOgok%2Bgxs%2B441hq%2Bsxj%2BRbC7LGCazB8hyhjK2e/C9m3KyA0DAqnm7%2B0qv%2BxGNwJepIPmLup6xxsBx0DgVYWgTgAAVl4D8A4C0FIFQE4CMUsGsEfFgaBwxB4FIAIE0E6dWH5BAB6ckANA0AAA4zAzAABOHZrgHpzZjZrgOIOIaQbpjgSQXgFgCQDQL6gZoZkZjgXgBQEAL6%2BZwZzp0gOAWAGARAEAdYAgPMkKigCANAdUOgaIUIb0TgVQDZxAgAWkQMkFuGAGQHeKkANDMF4E5EIBIDwANXaH4EEBEDEHYCkBkEEEUBUHUE%2BdIF0HaAtxvGSE4B4C6d6f6YWeGc4AvAJGBduEYtuDhcReRdRfRduExd7ogA8AhfoBoJmeWF4A%2Ba0FWAgCQHBeSEhbIFBY1a1ZAGACkD%2BpoCkrikoAiC5YiGCEaGJFZd4EteYGIGJAvAiG0FgNtdIHBe4gvAYFoBtbpawAiC8GAHkloBiPdawHwSMHEH9ZbNqFklebpcoM0VVHdaNU6C5aJAiBvEdY8CwC5cDDwBue4F4FkmIDoKUEeEjeACJCMAWdWG0rMIUA9neAt3AgGdmeJeEFEHEApc7epbUC5YZf0EMGMGsGsH0DwAiFecgFWFQGwsyATYRcRDgVMHGcsDMEedLejiwGnYgFWGqFqGcAgFcEmDaFIECHmFKHKDyDSAyAEFPZvYKEyAGCveGGmE6FgLqFmAfffa6C/b6BfaGBiGmG/c8FaD0FQSaEA8WGA/3amfJfZY4D6dIAed4CeaFfhaRZRbRYxbWaldwDxflbBC4EVbmbrdWFikYmGD3dIGWckASANB2YSDOY0EkDMEkGQI0B6cQJ2f0E4CudIBuYSC4ANEQK4EQI2Z2eOcQNWYOaY8QJQ65aeZebebI8%2BdVb%2BbVYBb5YJHIEoF1blehbYE4EaBYDpDiARaYEIgAi4B2YNBE6GdxaIG3b0E7dJZ7ekD7aUAHbpd0D%2BqZetFtcQ%2BQ9Q%2B5Y4F5aBYJAFaoAw5FZRcrBs7s4c7bJlc1blZhDBDMFI%2BVa%2Ba04M%2BiD07BYobS%2BGAS4Nf2a%2BuNdVAejNYtatcdfdftetedddYcHdc9dnG9d9a5YDaDZDbDeLdIAjZHejaGfwA5DjY%2BC5aTakhTcG7TYuaGczezeJFze2CGYLaLdmdLfLcwErZG5ojrb4AMGoubaIrbfdbc%2B7fJc89kH7dpaGb8%2BHdrdXasEsAnanfgFnfnfIM4CXY9RXbHfXc3eiG3am5nY6D/aPZPbA6mHPdDGg%2BvfaHyDvayFh7PZR%2B6ER7fch8/YEF6AmHR4g4/cPZ6FmGx%2BA7GD6B/ap6g8vaA4kDg42C2EZ746Q85bpfQ%2BFaw%2Bs9ols/s/WbbII%2Bc4y%2BE%2By/I9IEo6wBiBo4uYE6E7s9Y7iB6Z2dOYSDY448kHaFC%2BU9sFU5y40/gC08BeBcK/y%2BICM%2B2FM9FZYAUDpHeLpH57dBmBxfwGc4Jdc9kHc5u8pfkG84e50BACSAC5ZeLeC458eZ5Z0/7EFdUBt7t4d6d73EguleK61dF4SHF/U%2B%2BfVbT7lbN7z%2BGHt7EvQUd52fQWd6Urj887oGq9eYgHNbpaa4a8G%2Bb6dZdbdcG468EC679bG8wEDeDbEAG9meG6jfW94HG8/fjem9UGTe2FmYW4zcnZW7W/zeji25LeiF2/26jcO%2Bz4bdO5bYu8G6u7JYkFu6pf98HaD%2Be9HbXZsEzd3e%2B%2B6ATZ2FwVe%2BsA3bQ63YJfB5o4PbdAXAoYGnhexKAM9ket7boDT0x7Pt6eMHYnlDzJ7U8iev7PHsgLp7gCEBIHFATkDPaQc5gWApHkz02AIc2eIXJTpwCFbx97ejBJPqqBT7C8SAovEjkqwl5S9qOiHeXiAF2YGgEgCQHpocy153N%2BBcQCTop056cAVO7zCXnRx6aMcTmcQO5hs0kD7MuAWzYMmzwSAR80OUgtTiq0Q7YsJBkfZ5voMWakBS26QZwJICAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/easy_kindred_repack/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/descend/omennivore/easy_kindred_repack.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/easy_kindred_repack.type.test.hpp)
