<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Gauge`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-6">To Index</a></p>

## Description

`Typelivore::Gauge` accepts a list of elements.
Its first layer accepts a list of containers and returns a function.
When invoked by an operation, the function places the elements into the containers via a process similar to pack expansion;
then, it collects the value result of each packed container and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Container
-> Operation
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
Gauge ::   typename... 
        -> template<typename...> class...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<typename>
struct Gauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        using UniRail = RESULT;
    };
};


template<typename...>
struct Gauge
{
    template<template<typename...> class>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        using UniRail = RESULT;
    };
};


template<typename...>
struct Gauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        using UniRail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::Gauge`:

- We will pack `std::integral_constant<int, 0>` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<typename Element>
struct AddZero 
{ 
    static constexpr auto value
    {Element::value}; 
};

template<typename Element>
struct AddOne
{ 
    static constexpr auto value
    {Element::value + 1}; 
};

template<typename Element>
struct AddTwo
{ 
    static constexpr auto value
    {Element::value + 2}; 
};

template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result 
= Gauge<std::integral_constant<int, 0>>
::Road<AddZero, AddOne, AddTwo>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<1, 2, 3>;

using Result_1 = Gauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>::Road<AddOne>
::Rail<Operation>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `std::integral_constant<int, 0>`, `std::integral_constant<int, 1>`, and `std::integral_constant<int, 2>` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<0, 2, 4>;

using Result_2 = Gauge<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>,
    std::integral_constant<int, 2>
>::Road<AddZero, AddOne, AddTwo>
::Rail<Operation>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Typelivore::Gauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Gauge
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Device>
    struct ProtoRoad<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Elements>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};

template<typename Element>
struct Gauge<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Devices>
    struct ProtoRoad
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Element>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Devices>
    using Road = ProtoRoad<Devices...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArAAcpAAOqAqETgwe3r566ZmOAqHhUSyx8Vy2mPbFDEIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BdXj/YPllRIAlLaoXsTI7BwEmCypBjsm/m4EAJ6pjKyYAHS32PRsggpH2CYaAILjxF4OANQA4kwvMBMG93iYAOxWD6/WG/AD08N%2BAFkvLRHPtML97rtGARnjC4YiUWiMfRfh5BEwwnECe84b8dnsDqDjkz9kxDmzzpc2Ldri9fsgDAoFPyACKYABueE2z38r0JsK%2BPwIv2UxFQRAASqgmOgwQzIRZfoaGXD2SyjiddhyuW4gUR%2BYLhUxRb8APIXYic7IvM3m34qv6Spp0APm42mpWBuFeTJGRk803%2BcWe72%2BgTWyUyuXWnGPfEvEAgKViLw3W7%2B/zQ%2BmxyHio61iMMy2c1k25nt62O1DOhVCkVi27vYDETC4p7%2BmMM%2BNhYC/bXU2gptOh5fW0fjyf4/vYEtnC5NiMN48fCPE1HovCY7EPPF0hnEgRYylh8LECNt%2B3fjuH3mVgKA6uu6Oayqyip1sqBDfH8Gpaqgur6tm0rgdOUGmlC0YYa2tpWmyeHdscvZ7oOboKOmcSZgw6GxkGMGqr867hjOcJRi2sZzom/6rpRPr1ChuYdgWD7FqW5aAdWtZ0aeNZghxsK/taSnEV4TpVsBQ78luE6FvKkF0VxC5LnQvHMbQm5jrpD57gePJnhhsnNjGKmdnaf48swfIadgZGihKqF5gqEZGYueroLx8E6uFgngcOQGvHJ54Qo2SXgh8rn/l5WIiYI6HBmqgLAsJ955cFyXSUSSIeuEd47heSJXmSr6yNSH6PhahE/l1HkXNlpEgfFYFBQZcIFeqmrRchMbsaxik9cpC2qepCV%2BRRXpUQJ5U4WNDEhpgYYWXNmEmgp5qhTxRxpht/F%2Bscw2YPKbi5QQYllt4knBWlMkpQ5Z2ZUtDpqX2PlrdpVk7vpZ2hSZK5XUxB0bscOmQ7ZID/g5Rq/WlX6A5lnlXANWm3A9UMxjD4WRZNiExfdgWPXuf3Y857zwgAVBznNc/CYLsxzAAq2BCPznM8x8fNc9z8nnmY/hhMKXhYCmbhoAwmypEW21gvjfVXHVhb5XtarvOg6AAFpxKg2GzRhsyOMgQoCOMmCqKkxC/L2vzvRWJ5Qi9Jbe6CzPW8z0vvDrAH63ihuwcbps1aCFXYQyduyo7DDO677ue4HvsWP74kfaali/FwTkh6lLMR9lUdlZB40m%2Bg/MAO6oPJWERqnDuq5nbse8DXsSXnBeB8XJpmOX7eV2HrkkT5YLjTd1F/eLSL849aoaGHoVCF4qSFJg6Dao9pK8UvW1uBopCl9fE9fSzMMn%2Bi1upgCQIgta4zoCWYQ7GOYgAH0e5NDKm4X%2B18t5fUgiWJCBpkamwtpqa%2BjcE7INNi3Nu20YFIzcOfO6iUWZdwAeROIBAIBfxLAoK4xCnrHwUKSa%2Bu994ZEPnQ0kLwlgr1ZmvDepdt4JgXEwg%2BR8n4EAAVwM%2BGYL7VF%2BGYa%2B/gpL8PnIuUR4jeJFQ/scTuBBv4gF/pgf%2BtAgFOxAa9Y44DfiQOwKQbRuj9GGOMRnUx1oLFlwVDYmMFC9GCAMT6IxwDDBmLAYIW%2B6ExKwM3PHcI6FsHhmOHgrM98w5EJIS0chOjKHULdNaNh6JxGML3sI3JYi3HYE4TjVevx17jFkUoxMQiWEiPoXkswkjNp3Uvrfa%2BkhFHng%2BI/ZpYjWnww0R2WxP8fEOICaAixViPG2wyd4v%2BfjHGzBmSEvh7jxlLN8YA6ZQSLF30guE2mbhG6INQGg9AqDfiNwwTEkAsNrQJJokkvpnwmj2xoUoNJXiqFsBoTk1RcjfgNKUE00kACjnlIsBwFYtBOAJF4H4DgWhSCoE4G4aw1ggxrA2Ficw/geCkAIJoOFKwADWiRJDXA0JILgEJ/AaASBoMwAA2NlZgkgpARRwSQvAWASA0FfFFaKMUcF4AoEAV9SWorhaQOAsAYCIBAGsAgqQ1LkEoGgPYdA4gRCuJwVQSQ2UAFo2WSF%2BMAZADspDXDMLwQ%2BhASB4G/tUfgggRBiHYFIGQghFAqHUHK0guhqjNx9KkTgPB4WIuRWS9FnAPRqQ1WqVAVBfjGrNRaq1NrS40taRADwur6Du0JVwJYvBZVaBWBAJAOrUh6rIBQCA9bG0gGAFIORNB0S0koNEeN0QwjNFOFG3gg7mDEFOB6aI2huiyuJTqwsNVaAjuDVgaIwIHS0FoFK7gvAsAsEMMAcQa68Djh6FKR68aXbdDUlsYl%2BjeVotoHgaIPpJ0eCwPGmCeBBV7tIJe4g0QWGSkPUYF9RgyUrCoAYYACgABqeBMDNw2ii4lHrhCiHEL6jDAa1DxtDfoI9KBsWWH0K%2BqVkAVioA1tkXdpqv5XVMJYawZgxWAeIK6q9VGah1GyC4Bg7hPDtD0CEGkCwRjVEKFkAQUw/BSYyDJhg8xhhVF43O3oExWjCemOpnoAg%2BgtBUxUSTtgtNyb0LMIz4nVPLFWOsTYdneVItIKK3g4qM0mvNZa61tr82/AgLgZ1pbZblsrVBlYCBMD6hGBASlIBJD%2BGuAATn8BCSQdKzCSDZcKhIbLkv6E4Py0ggqiXXDZVwNlSRktJEqwkelCRUtstc/G8VkrpUkqgwq5VtbVXJs1c21tJaDVsE4M0FgUoISmqYGRRMXBkvXC4LSx1%2BAiCcbdX6zD3qJDSFw0ofDwbdByPDUwSNe6Y0cBc25hNHAk3qrUr8NNHtiATamzN10c2FtLY0AFotDaS3F38GYCtnW5U1rragYtcQtUtsh/9kY43Jumo%2Bx25LXAr7dp2MQKVEB%2B3BvHcO0dpACeTunbOhwRPF14mXautF67N1iB3UTg9R6T107PRpy9u60U3uQHeonj740vrfcOz9Ww0U/r/cSwDwGlCgdZ/OLrMGmBwcQ8h1DROMNeuw7t2QeGg1oqO0RyDzGrBkeF5RuL6LaNO04AxnRTHSMWDY%2B5jjXHLcrC6PpvwEBXAWeqGJsotmFNFGyP7tIin6jGcWDMWoGmDPmZ0/JvT9RDMDBsyZtTVntN5GT9n6PknPd4sc%2BWwrl243Bo84jt7s2FzzcW7SgLQW1uA7C6D6tkXotYHiFb3lxXSsLbpRCRrEJGWSCyxa6o122u2A61W%2BViqVVqpTTDob%2BrDUcHG9mlgCgpQOylPXlk4wVvBddXoLXWGfW6/9ftg3OgAikBO2d6NZerutcTf11N6at%2BWp33vr2h%2B7YNShacOjagO/gIO8%2B4OKAoBJaq%2BsBIwe%2B%2B8ACB%2ByWACR%2BYiP%2BfAdAWOOOeOaKJOq6xKhBZOc6lOkOS6DAK68a9OwAW6TO/6LO4G4u%2B6HOF6V6wavO/O/6guwawu76pwYu36nGUuvAMuIGuwCukGYOfAsGCGSGKGfUmusg2uV%2Bm2%2BuBGD%2BBgJuTu5G0QHu1u9Qu68IFCpurG7GcQ623GVuXu9QAmQmueomgmBeam0m9Q4ebh2QLhlmce3uae4ethmmcwGeMeZm/QARWm3hpeCgxePqF2b%2BlenAz2LA2%2Bu%2B%2B%2BgBOwwBzeJArekBEWpAUWMWPeF2/eIAZgC2/g/gCQLK9KwqlREIVWLWiREqs%2BMq%2BRVKkgCQKWyQ7KyWkgyWjKaWXAgQvK/gFeYqnA4WYOF2DqTRExLRUBKwgGmQzgkgQAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/gauge.test.hpp)
