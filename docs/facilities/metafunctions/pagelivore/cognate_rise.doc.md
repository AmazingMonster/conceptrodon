<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRise`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-rise">To Index</a></p>

## Description

`Pagelivore::CognateRise` accepts an operation and returns a function.
When invoked, the function sorts the arguments in ascending order and instantiates the operation with the result.

<pre><code>   Oper
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Oper&lt;V<sub>i<sub>0</sub></sub>, V<sub>i<sub>1</sub></sub>, ..., V<sub>i<sub>n</sub></sub>&gt; where V<sub>i<sub>0</sub></sub> &lt; V<sub>i<sub>1</sub></sub> &lt; ... &lt; V<sub>i<sub>n</sub></sub></code></pre>

## Type Signature

```Haskell
CognateRise
 :: template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRise
{
    template<auto...>
    alias Rail = RESULT;
};
```

## Examples

We will sort `2, 2, 1, 0` and use the result to instantiate `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<0, 1, 2, 2>;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateRise<Operation>
::Page<Args...>;

/**** Result ****/
using Result = Metafunction<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateRise` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `arise`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{    
    // `std::index_sequence<I...>` is created
    // for the length of `Variables...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            // `original` will be reused for the result.
            std::ranges::sort(original);
            return original;
        }();
        // We use `std::type_identity` to avoid construct
        // an object of type `Operation<*>`.
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<template<auto...> class Operation>
struct CognateRise
{
    template<auto...Variables>
    using Page = decltype(arise<Operation, Variables...>())
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABs0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZkCEWQ3iwNxMgTcXkctEIAE8YdhgeYwQwIV4oTC3C1iEwUYE0ZcMeDIZhobCxMASIQECxUeifocbi08EpPgdAQRMCxUgY%2BXi%2BQKhZg8Ux4agAHRy1E3CFMBQfADyT0JDVI7OlcplADUOUxYvQFMzLrNHMhFQJxpgAG5iHVEdnETmYCBLdEAdgsN390MuAZu2220KSGnG6BAIAiWFUAH0lABHLwvCWwgCSeuZEZunMVxEwTD56GBwdDN34xBuBAQVPoRjrN1QVHDGkNbuNppzEZl5YDRYI6wY0P8Vn8dzxmQAXpgEwQ9ZnURAozG45hEym01iM25s/KSV6gwGTL6B8H/WgGHbVKka1KXQoSKXqXcxxO7p6L5ez1YT5el5riABJEi2brABETp/p2eDdu8ObelOgT/hcgGAZWJgRvSkHMLQWEaDcADudC0Dc8Q3EWXhKOgVYkLW9aUe8Xi0IuP7oTcwGEkY7wxs%2BrQQDhUG0F6KHsehQ4juBeC4WIMKoRxZ5fqJCnoZWADqVLUVSBHAQQSJPAmeBYIIyIEbWqDsvaqDGTaN4EMQXgOOJ/qVoYLaxNomAOC2bb6U87bqgkJbZHiuy5ho/YAZeknEKOekGfOxmMI4%2Bl4kFmqhbC/GljKJYQJmSw5iSCp/kp8k/kpq4ENGIAsEwADWSUMPGSaYKm6bTngc6tnqECwfBCiiWi55ISpPrIahwK/P8s37ICM03JmYr8ilIUCNy83TXNO2nCyFyioKJZ7od4qSrqh7YIqBgqjcGXrQw5oXOMjk%2BR4wDMHyABK7o%2Bqp/qncd51EHqA0mu8T3BtRETADcyhMMAOmBO%2BWAQv5Hocko6Uag92pgz2l2eseaEBjG6MVWSSEU0CrK7Ty223NgqisIKVJfAzdN7WSZKghSOJI2416bKkBBmiV3NXGy90NJtXMHfyR3CjSF39uLz0OU5BB3TjDTUxzuw3EIXipEUmDoF9zGsbLgLQ0YhvG6b5uW1rMLvtLWVuBo2pcNqZi%2B8yYkS4tACymDNFQXhYjL7OXIDSv4irFzEMAYukhctuw6H4eRw42Rvjc72fZgP1Y7C7sCE9Mbw4jeJJynxVooHNOS7cFsKCxWsx%2BnmR223Hf51nTAR1HHtezcPs3H7k8B1NtP7DcAAq7yd/TFrNFaCbKkoAnAQorDzsqeJ96x2pGybGRm8fBCoipHArLQnD%2BLwfgcFopCoJwbjWNYnFrBsOmgh4KQAgmg74rAagESQMoNAAA4zBmAAJwIK4P4WBMCuDem9NIB%2BHBJC8BYBIDQXsX5vw/hwXgCgQBexAa/O%2BpA4CwBgIgEAawCCpHhOQSgaABR0ASFEfenBVAwKSAAWhSDcYAyBrRSBlGYXgZtCD0mjD7fgggRBiHYFIGQghFAqHULQ0gugfZEUJKkTgPB76P2fqA9%2BnBVTwnYVrVsNwhGiPEZI6RUCzA3AgB4Hh9AawYi4EsXgNCtArAgEgbhqReFkAoBAaJsSQDACkH7GgrEEiUIgLEGxsQoLECROY3geTmAFNVJ5byNCgHcLYIIVUDBaCFIMVgWIXhgD4loLQSh3BeBYHqkYcQzS8BFlzvaXiBjNzeXhFsIBEQ%2BQ4LfoiWIhICkeCwDYhyeACE9NIGM4gsQL4PH6cARERhQErCoAYFO%2Bo3hESCi/IBqjhCiHEFop5ui1A2KMfoQwxhv6WH0HgWIlDIArFQCLbI3SRFRldqYSw1gzCkL2W6LAILPTdEqdkFwLUph%2BB9mECIQxKgjB9kULIAhcV6DJQ0eYwxEg%2BzsJigQfRJieA6HoRludmUTAGIShYJLbA8spQynltLiX0pWM%2BdYmwJCWI4E/UgJDeBkJccIsRkgJFSPHl4nxuBFGBMASE4B5yVj1iYFgRI6KIGSECDKBBgQsEaEkGYSQEYND%2BCSAg/QnA8GkAIYELgMokhcCSDAhB6Ckj%2BEkCg%2B1SRFU2LIRQqhxraERKYZElhDiOHxMSQE/hbBOAtBYPab0IimDXV%2BePBBMpA1vwUUQFFegnnqNedId5ShPkGN0H7ExTAzE9LlQqpVtiOD2LYfCXyqq3EaqVHbLg1ba0%2BL8TEgJ0JQRmCNWEuhGbc0JE4Qk1A/iRizpScgr26S%2BTECyTkgxJSWhNKAXespFSHBFNIDUlK9TGk2JaW0jpXS319N%2BYMt%2B%2BARmODGd0utqgpl8jfXMuoNilkrKRGsrYb9NnbKAXsg5SgjnAZhucvgVyFA3MwHcp4DzeDNpeZottsgPn6Lft2n5Zy4VWABUstFYKIW2k4NCmqsL/kWERcq5FyVuMYq5X4CArhhUhBamKxYpKMjkpyGy/IKnijZCUwKzlDQWVtA03iqTBnRV8rpRyoVxmrNzAs%2BK2VqxpWaMHdYgxKrXHqorXOhd0DdX4AbWugNm6TWkDNRaygcrfX%2BurU670/gEGYMCM6110b43uc4Em6hRGGHMNYY4/du7iD5q2EW8RLAFD2mtPaedMpxTjHkQFpRTbZAtro9o%2BQHamM6BAMEXt/aLHevlW50hdis1OLbKocrlXqu1fq1rXxh6V0JCC4EELqb6FRKW7Ewr22AkgCqybBMNWEEJnmwmKbba6CXuvbk/JD7in3fKV5V9OyP11IaU00DmBWntLEABnZQGBnod6cMzFkGbGTOQNM%2BDghEMGOQ/etDGy3RYd4Dhw5/ICNnI25chGpHbn3LfTRjREh6M6K6183rrG/nws40CyT4KGjdO2GudjCKkUJBRbxUFpmsWyZxTZ/Fin7PKdINS7I8mJelFF3puoTLGjWbyCZ/TvRzPlEsyK/o8nZitF0xKpz/9HM4KHQmzgLjptVZuCdurx1xj%2Bf1UF4JoTQvhZGOinB0WQCIJlIEQI/hUHRqIX770ob0ujfIbYZNW6ljgJAJIfwdqMHeiITAyQyCuBwLMHGnBgQRvKsyym8Jcq5Hh4L5HmPKw9mZGcJIIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_rise/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_rise.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_rise.test.hpp)
