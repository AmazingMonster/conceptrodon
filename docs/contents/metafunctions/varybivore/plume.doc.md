<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Plume`

## Description

`Varybivore::Plume` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.
When invoked by an operation, the function places the variables into sequences via a process similar to pack expansion;
then, it collects every packed sequence and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Variable
-> ...Sequence<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Sequence<sub><i>i</i></sub>&lt;Variable&gt;...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> Sequence
-> Operation
-> Operation&lt;...Sequence&lt;Variable<sub><i>i</i></sub>&gt;...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> ...Sequence<sub><i>i</i></sub>...
-> Operation
-> Operation<...Sequence<sub><i>i</i></sub>&lt;Variable<sub><i>i</i></sub>&gt;...&gt;</code></pre>

## Type Signature

```Haskell
Plume ::   auto... 
        -> template<auto...> class...
        -> template<template<typename...> class...>
```

## Structure

```C++
template<auto>
struct Plume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

```C++
template<auto...>
struct Plume
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

```C++
template<auto...>
struct Plume
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::Plume`:

- We will pack `0` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

template<typename...>
struct Operation;

using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

using Result = Plume<0>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `0`, `1`, and `2`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

using Result_1 = Plume<0, 1, 2>
::Rail<OneStar>
::Road<Operation>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

using Result_2 = Plume<0, 1, 2>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::Plume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Plume
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Variables>...>;
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
            using type = Operation<Cosmetic<Variables>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct Plume<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Variable>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwAbKSuADJ4DJgAcj4ARpjEEmZcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcBJgsqQa7Jv5uTF5EAHRXAGqteEyx9ArH2CYaAIITxF4OANTKeUwb3eJgA7FYPr8ob8APQw34AWS8tEcB0wv1uxHuj0wz0h0LhiORqPovyEmAAjl5GFs8e9ob9dvtDkCTkyDkwjiczpcri9fsgDAoFFcLh4FGxHMhnv5XvioV8fgR/sRUEQAEpMOi/YEMsEWHXyhmMvYcrludks44WgCeqUYrEwov5gqYwt%2BAHl7cROdkXrrjQqCN8/gARTAtOgBwP66OB6FeTJGRl29HHUOe72%2BgTW8WSvDS62Y7FPF7O2XHCH0%2BNg0OV4FxhmWzmsi2mq1s1PMNjl7ACoUiq7vYDETB7RgEGVy6uBxMRYC/dWoJjoHX%2BDPhyO0a3D0fjwSDi4vEAgAip%2BtG2sXkFGwlIlF4NEYu4PUu3%2BEeyJkynUhhbOPNuagGtjyqC9v2boKL8eYRgW/pGoqfzKKqGpatuJwwVK8Ezjq4KGjhTbti21rASRXaOuBrrul6CTZgw2Hxr8iHKpuaGNtCsZGoxc7Jme9prhmNE%2Bo0uYZPmpgnMWr64mWfIVv4VaMVeCkNlx0KkWyRFAeRPZyX2VGHruY5sAeDHxjxC5LiuAm/KxUYnEZ%2B6Tr2J58ayikcaCdYqR8AFaa2GmnOcYF6RBwqiphBZTnGFmLmhNnIWqqCavZbiRdKvbXspVbAoFoHPli0nYcx/yAkWL44thnE4YSn7olJlXvkSD5PuSVI0jJRqBXlwWUQOEVibBhYVghwZKiqSUpbQ%2BF6nh7FQt1/lkfa3ZOqFBmZrRIkjQR0IlXZ25qVC1WMQysVuTZQl0aJEpDTKbgNfQslHvJHkxl5WVHSazLEZpP3aStFHrf1Q4jsZE7RV9sVWau6a2RGbEOWDTmHsep7nj5OHZapOGLf9IG9cDkEDbdUqQzh0PxXDiWoal6Wo69DYfZjwIwgAVBznNczCrOcwAKtgQh85zPMfOzXMS6LN4gmY/gRIKXhYGubhoH%2BmCpJOVUfD1RC/AAkthsUAFoJKg/TEDZEzoCeES7COYgAPqq3MgjWrbpD6/6LPa0t3LBZ7O2xXV5uWwQ1sgLbmD27QTsCC7BBu4IHsG7KbOfe8OuoAH06xXzADuZuTFBcNWzbghRz6MfOy0rsnO72cc%2Bn3U6WtL3TiVV3bTlYvwnzuLKhoOOxUIXipEUmDoOquLEpdWYib5JxxqXEfl9HscMPHicEB7g%2ByqQS9h2XduV%2Bvm910nvy79gbP76N4eR2v1eGAn5/b5fLyNwvrze%2B80PTyiCUyonCvsCE8U1rQm1VObD2wdJge3zoXVo5MwHLnQNaTufpGa%2BQ%2BHMKUDtIIJAIBAZeChHT4PulPBQxIPYjzHhkCelDiQvGWOnQkfcJi/C4EPJMC5aHj0nv/AgDsuCzy2n6BebgD731XifJ%2Btc3D1yvjfKRR8K6OzkS/BRF8uGp1vjhZeD9ZFxxrpo%2BuZgP4NiwdLP%2BVCUTCMAT4VsGgPYpF%2BOYnaYDEZuFga0bCKCVzoLnpg7%2B3dPgtDwQQtoxDD4gFIWwch1pGF2NcXw%2BhAjbFCJ0dgFhP82H9zcdw%2BcZJR78KSUIswojhLiJBIvO%2BqjH7GOflvHeLw9EMgMTI9RjT5H1yycoupK9j5dI3iY5pBTU5py/unGxxIHYVOpkAtwzjOEe3cdOTxqVIGILIJ6SI0DfgIPNsgkAMNAliJzFY4EuCCzkKUFEkhZC3SJMEXMmhJS0llLmcwysHBVi0E4AAVl4H4DgWhSCoE4JIyw1gmLrE2GmWWPBSAEE0L81YABrEAALJAXA0JILgoJ/AaABRoMwgRAhmAAByUv0JwSQvAWASA0M4kFYKIUcF4AoEAziUWgt%2BaQOAsAYCIBAOsAgqRzjkEoGgfYdAEhREdJwVQlLAgAFpAiSF%2BMAZAyBOE4rMLwCehASB4GtikfgggRBiHYFIGQghFAqHUHy0gugUh5x9KkTgPA/mAuBai8FnAPTnAlcqVAVBfjKrVRqrVOq9UXAqRADwsr6AW3MP4LgyxeC8q0KsCASAZWpDlWQCgEAC1FpAMAKQZg%2BB0F2MQLlEBYj%2BtiBEVoNovW8BbcwYgNoPSxG0JgBwHbSAypMgQT8tB23OqwLELwwBTi0FoFy7gvAsAsEMMAcQ068CjgcHgAAbrif1mBVCDvONsJFkd/nOtoHgWIPoe0eCwP64MeBGUrtIIe4gsR6HhnXUYW9RhUWrCoAYYAChrh4EwHnGiIKkUWuEKIcQtqEMOrUP611%2BgN0oGsNYfQd6uWQFWKgDW2Rl2qqtumUw0LLBmDZV%2BrEWBCMQFWHYQdjQXAMHcJ4ToegwgRGGJUUYKQihZAENMPwImMhiYYAsEY1Qejsb6JMdoPH8jjHqEpgQ5tBgCcWMJ2wKmJN6DmG0OTQnqisbhVsCQPqOBAtIKy3g7KI0qvVZq7VuqpDxt%2BBAXAxrU2Iszci4DqwECYBXKMFjpBMWSH8BcAAnP4UEkg8VmEkIEZlALAgJdpRwelpBGXpouIELggRKUJcpWV7FXAAVJeCE5gNHLbDcpC3y3Nwq82iuDZKktZaU0KrYJwVoLB92glVUwCCyYuAJYuFwXFhr8BEEY3oBDVrkPSFQ0odDzrdDVvdUwT1K67MOca%2ByoN4rzi/DDb8EbY2JtTYXDNubuLfNJsLSmnUsszDBezfyrr/WEhStLagZNow7vjddEYGbXBnE0BRAkBtTbnVdrbcO1HPa%2B0DqHR%2B0dE4J1TrBTOudC6l3DrXRurdROd1KcPcusFJ6z27GHVe/1t771tqfdsMFr731Iq/T%2BpQf7KfzmA3wMDEGoMwZWsOtbSGbWbdkGhp1YK9tYaA9Rqwlh8OxGY8R0jcdOAUbDlR3DtH6MJEY0eojim93OAgK4YzKR%2BPlHk3oUTjQndpGk40czSwNO9G00ZtTknbeNB037gzpnVN5FD9HyPlm1gbBsxmvLp3/UuYhw9qHT3ZvzY0L5/zy2vvpt%2B6F0g4XIuJGi9egrRXZt4tBHV0EhLJDpY1SkM7nBOWtb%2Bx1%2BAXWxUhuB4D4gg3tgjejSwBQ%2B7dX7ueyyCYi2AumtW7IdbCu7XyG2yrnQARSAHaO96tPfrnXnZ66G8Nk/NXT9n78efs3F/KkTaDj7CQS/%2BDL%2B1gV%2BbX9FpH3/imiALPmPA7A/g7E/vgsQCwBqjWgjvWpQMjmChjlOkiigVjuxsOnjoIATv6sTvOmIGTh%2BhTgBtzqujTnunTseqesgOeizuXNemCuzg%2BjaFzi%2BliHzrwALr%2BnsCLkBt/qBkwOBpBtBrBrLuvvLhIIrvajvhhvvgYBrmbjYOznruCgbhvJwDCKXJrtYHRs5gxqatbtFmxnbn4A7lxl7i7oJv7t7sUNkF7h7tkAniZppqYTpl7iYeHips4eMMHrHiZt4Xpm7qngoNZjaidqfmypwLdtAVPjPnPgvi2Bwn5ktiQCXhmlmuXpXlgNXnZnXiAGYLNv4P4ACiSvisysUaCOVo5hnt3i1jyuXrFgColgCpSmSglpIAloSsllwP4Hlv4JEc5nUX3nZgajUWfsMeXl%2BpkM4JIEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/plume.hpp)
- [unit test](../../../../tests/unit/varybivore/plume.test.hpp)
