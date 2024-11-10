<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Duplicate`

## Description

`Typelivore::Duplicate` accepts an element, which we will duplicate.
Its first layer accepts the number of copies we want and returns a function such that when invoked with an operation, the function becomes the operation instantiated with the number of copies of the element.
<pre><code>   Element
-> N
-> Operation
-> Operation&lt;(1, Element), ..., (N, Element)&gt;</code></pre>

## Type Signature

```Haskell
Duplicate ::   typename...
            -> auto...
            -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Duplicate
{
    template<auto...>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `int`:

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int, int, int>;

using Result = Duplicate<int>
::Page<4>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion. We start with an empty list, adding the element while subtracting the number until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this in a similar way to `Typelivore::Amid`.

We want to bundle the element and each index from a pack.
Then, we will pull out the element from each bundle by a pack expansion over indices.

First, we need to create a Bundle alias:

```C++
template<typename Element, auto>
using Bundle = Element;
```

The entire implementation is presented below:

```C++
template<typename Element>
struct Duplicate
{
    template<typename>
    struct ProtoMold {};

    template<size_t...I>
    struct ProtoMold<std::index_sequence<I...>>
    {
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation
            <Typella::Bundle<Element, I>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;

        template<template<typename...> class Operation>
        using UniRoad = Operation
        <Typella::Bundle<Element, I>...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<size_t I>
    struct ProtoPage
    : public ProtoMold<std::make_index_sequence<I>>
    {};

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQAcpAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnufYJhoAgvuHx5hnF8hz6FhUDyerxeBEwLFSBlB5zcBFuqUYrE%2B2HobEEpBOTCuqEBLy8mSMJwsXgY6HoXwAIidkWDGARzlYXkDQeDIZhobD4cw2FSUbScc85sQvA4TuSvBC8KIoYyAOwM54nRUnZkQphQi4chFsflKk6C4UEE7KYioIgAWU86DOcpMMvJ9KBQN1KtZ0MyAC9MAB9AgAOn9AEkdUr9SLjabUBbaOg3QR0CAQBEsKovUoAI5eRg7aEB/2%2BwGBR4vXW2%2BW651g1XqmGV10auFazB5h4nI5MBQKE4AeXhxDV2WD5b1BCFIvJmGadCdQ%2BtZZnurxEWAyobFO7vf7Amn88V0KJJPo0OpqII6KDhebhYdxZntvtgXl2/LLrVbI1tdf7IbXKb/pbbY7PNnmAYhMBpQQFEHctFwJAAlVAmCtc5KXHSdaGhYDQPAggFEvbAE01a9gQVGcX2rMi3xhb9ETw1sDA7dcEk3BgoIXfFlzkBg8HgxC1x7Ji%2BifEsLn3UlKOPWkzwePCiJLO0iKfCiv05Gj/UwsCT0gq8b0VGDlyjJDAkpcNzUtDCQI02lcL/K8H0dHTlQ/asPW9Q1zyLEjFVDQ0TNQZQmGANkHJAE5Ui8WIbmQI0TVM6NY3jEAWCYABrb0k0wFN00zBhswudyoNLO8FIcpSLkxIggIs7CtI8tilyNALPmQ6KI38wLzKwzSZLs2V70fF4AHoACoRtGsaBqBYaRoAFWwIRptGibBrGlahqW4i3hyj4vkua47n5JknMozUfxkl5vMYvtBJ64i9JOIRxSKTB0FgzAFC8WhDWa/iroHC4IlPE4AfRYGgcEAt%2BueO7Xvez61zFCUpUogH%2BQTNrKMkVGQB4mMLh%2B5iIfsgVmkcZAvXbJRWggX4EwURFya0twYY%2BwGHtSJ6XrelmHlWekOHWWhOH8Xg/G4XhUE4NxrGsPVNm2JqzECHhSAITR%2BfWZKAjMX0ZTMSQkiSfwNAATn8MwNAANiSYJBY4SReBYCQNA0UhRa0UgJY4XgFBAF3VY4LR1jgWAYEQEBNgIMLTwoCA0HBOgEiiRFOFUJILYAWgtyQTmAZAoqkX0zF4Z7CBIPB4y4GRBBEMR2CkKv5CUNQ1dIXRK4Adz7VJOB4AWhZFlvPa7K4o5OVAqBOVOM6znO85OAuzBOCAPHj%2BhiDORWuFWXh/cD0gICQOPUgTsgY6Pk%2BQGAKQzD4OhQWIH2IFiFvYgiFpbh73hX%2BYYhbi7WJtD1H9srOOJ4uwMFoB/AOvAsCxC8MANwYhaA%2BzFqQLASUjDiGgWgvAoEGgADc3otwyvUK4uxlYAx6C3G4sQ%2By/w8FgFuI48CO1QYQ4gsQMiYHHBg4ANwjBq3WFQAwwAFAADU8CYHbvxUWyt%2BDV1EOIeu8jG4qHUNgtu%2BhDDGGlpYfQeBYg%2B0gOsVAqQ%2BgoPTr8ZCphLDWHNuLdhxBy5EOMd0Xo2QXAkmmH4SuYRFgVCqHoIoWQBDeKCRkEJDBhgBLGJXOoDQBADCmJ4Doeh4l9CSQscooxEhxPmGEvJgxok5IkOsBQcsdilP0P3V2g9OCTzTpnbOud86SELkvXApd177C3jvQR6wECYEQmMCAGsQCSECL6Y2gQZSSA0JIPWFtnb%2BAtsbapdsHYgCVr6C2XArbGySHs/wkguD%2BGmRbWp2DPbe19irQR%2B9Q4H3DiPK45BKDnzXknNgnAWgsHwTKdOTA6LaPnsbX0XBfTuxLkQJxFcG41yUdIFRig1Et10DfTuTBu5iz7hwYWlz3ZDxeYaceGJiB/IBUCtsBIuBgohRoJeK9j5rw3oEMw287nQKDofVAq8EhvNjry5lYxfn/PTtSq%2BxsuAuxoJ9BIj9n7YO/u/T%2BpBlW/3/oAhwqrQG0nAZAlusD4GINoMg1V6DtFYPdvgPBjhCEoKhaoUhoJVWUNtu7GhdDbgMN2O7ZhrDlbsM4UoHhlqlz3OEQFcRkjpGclVSohFdckWyBRc3DRIAb4GAETYqweiaFGNGR7Mx2QLFWKMjmuxhLHHOILWUnoQCPEQFcAUkIJJinLFyWkCJfQW3BL6O2wJcT60JP6PklJ%2BQh3uMSfMAdsSJiDBbXMIp/iSlbw2FsSpa7bb4rduLeporKXAppXSyFHT8AwtZb0zlgcBlDKwIkQttt7akEdoEMF8yZRnJlDKQICzJBZ0rruj2nAbl%2B3ucHMOEco4Co%2BYnZOHBfkzxYAofBUV8G0t9KyOYxdz1lzhQmxRSaG6pvUe7XQwRMXYt7usnddSODD0jlcMeE9EPZ2Q6hk46GwVYcNMvIVJ9WWBA5bvfm%2B8eV8tPu8/ja8QCofZl6LjXoePk3JVnW%2BcqH6UEVe7dVUDla6c1UAnVvKwEQKgdazAcCEFIJQcrC1mDfUwNwQ2%2B1xCnXIDIa6wQVDsGevfj6phTiA28CDVw0NmDw1cr4CI6NUiZHxtkImiQybBAkbRVsrR2bdE2HzfAExxaBAoIGjTCtlh7Ee2rVgWtbiG3OCbV48dPjW3oFnZ2vt2Re3duyK1tJw6MljryE19JjQZ0ro7WkgbqTCmtB62u8pG6664to1c/dqm2MobQxhnjZ6umXuE/00ggzhkPtxc%2Bx2ZgwWBECP4I2JznZXZlFbAle6va2FuSJ1YYzJAykLp%2BrgUhjYfumVwGU6zAgDxW69j7uKi7PeA1Dg77DMjOEkEAA)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/duplicate.hpp)
- [unit test](../../../../tests/unit/typelivore/duplicate.test.hpp)
