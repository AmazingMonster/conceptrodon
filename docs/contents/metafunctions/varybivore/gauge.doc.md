<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Gauge`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-7">To Index</a></p>

## Description

`Varybivore::Gauge` accepts a list of variables.
Its first layer accepts a list of sequences and returns a function.
When invoked by an operation, the function places the variables into the sequences via a process similar to pack expansion;
then, it collects the value result of each packed sequence and invokes the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Variable
-> ...Sequence<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Sequence<sub><i>i</i></sub>&lt;Variable&gt;::value...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> Sequence
-> Operation
-> Operation&lt;...Sequence&lt;Variable<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Variable<sub><i>i</i></sub>...
-> ...Sequence<sub><i>i</i></sub>...
-> Operation
-> Operation<...Sequence<sub><i>i</i></sub>&lt;Variable<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
Gauge ::   auto... 
        -> template<auto...> class...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<auto>
struct Gauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        using UniRail = RESULT;
    };
};
```

```C++
template<auto...>
struct Gauge
{
    template<template<auto...> class>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        using UniRail = RESULT;
    };
};
```

```C++
template<auto...>
struct Gauge
{
    template<template<auto...> class...>
    alias Rail
    {
        template<template<auto...> class>
        alias Rail = RESULT;

        template<template<auto...> class>
        using UniRail = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Varybivore::Gauge`:

- We will pack `0` into `AddZero`, `AddOne` and `AddTwo`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
template<auto I>
struct AddZero 
{ 
    static constexpr auto value
    {I}; 
};

template<auto I>
struct AddOne
{ 
    static constexpr auto value
    {I + 1}; 
};

template<auto I>
struct AddTwo
{ 
    static constexpr auto value
    {I + 2}; 
};

template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2>;

using Result 
= Gauge<0>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `AddOne` to pack each of `0`, `1`, and `2`.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<1, 2, 3>;

using Result_1 = Gauge<0, 1, 2>
::Rail<AddOne>
::Rail<Operation>;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We will pack `0`, `1`, and `2` into `AddZero`, `AddOne`, and `AddTwo` separately.
Then, we will collect `value` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<0, 2, 4>;

using Result_2 = Gauge<0, 1, 2>
::Rail<AddZero, AddOne, AddTwo>
::Rail<Operation>;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

`Varybivore::Gauge` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one variable, we pack the variable in each sequence separately;

- If the user only provides one sequence, we use the sequence to pack each variable separately;

- Otherwise, the number of variables shall match the number of sequences.
We pack each variable into its corresponding sequence.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Gauge
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Device>
    struct ProtoRail<Device>
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Device<Variables>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};

template<auto Variable>
struct Gauge<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Devices>
    struct ProtoRail
    { 
        template<template<auto...> class Operation>
        struct Detail
        { 
            using type = Operation<Devices<Variable>::value...>;
        };

        template<template<auto...> class...Agreements>
        using Rail = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Devices>
    using Rail = ProtoRail<Devices...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArAAcpAAOqAqETgwe3r566ZmOAqHhUSyx8Vy2mPbFDEIETMQEuT5%2BgXaYDtmNzQSlkTFxiSkKTS1t%2BdXj/YPllRIAlLaoXsTI7BwEmCypBjsm/m5MXkQAdJcAas14TNH0CkfYJhoAguPEXg4A1ADip2AmFebxMAHYrO8ftCfgB6WE/ACyXlojn2mB%2BN2IdwemCeUJh8KRKLR9B%2BQkwAEcvIxNvi3jCfjs9gdgcdmfsmIdjqcLpdnj9kAYFApLucACKYABueDpzxBjM%2B3wIP2UxFQRAASkw6AqYeCLD89YzoRzWUc3GauWyTmdUGKBUKmCKfgB5VJxLnZeUEk0/JW/SVNXW%2Bk0Go2hv3QryZIxMgCeHqN/nFbo9xC9AgtkplcuOWJxj2eIBAUrENId/he/khDKj4PFR1rxpNVu5lt2nPbvPt/KrguFosub2AxEwu0YBCeVZbjJjYWAP21dGTqaDOtoFpHY4ngiH52LIAIibZtcZDabIJbRORqLw6Mxt3uRdDRNd4XJVJpDE2LbbNv/C0e0rbAB2dBQfhzWU2ReUMAxVNUNVQZdN2OKDfxnUNw1nGFAPZTtzR5O0QLAl13U9eofTrP14MgzBg03SN9QhCNqKjaNY0XY8kyOVNyIzSi0OlaCLQLZ88UPMtvEwEDLyY6ELxrK95KZAjrQtPDbT5A9%2BydEUxW3cc2D3Kj2PnOMUNXOiGK3UcjMnfdD2408W0U5tQ00zTgL7UC9P3dCJMwtjzMXSzeNVdUtQ3bNhLpWSlPeNzlLeLy7UfbFxKo2iAS8IFRKfXEqINa8EXfDExMK18EVvUkMQpalaQkjy1PbVLtMdQcxQC6dYLY2jEKikM2OwlTPJam1vJ03zBzTCjvSC9jaPXIb2JGtizM4hMeJTWaBPmtxuvyjLCqrEspIrHy5PW5jGwS0FRvGjTHqI9rdM64c7N3KdTKjEKlw3KzltQtxDK%2BxzTqPE8rvPMFbvctixpZdSXt7KbSP82LAt6udNrCnaBuQ6KhNzPF4ubWGruS2EACpabp%2BnYRBGnaYAFWwIQWbpxn3mZ%2BmGeS8x/DCIUvCwZM3DQH9MFSb6gpBNrUB%2BABJLKCC%2BX43nQdAAC04kVq8WJbWZHGQQUBHGTBVFSYgfh7H5zuBLCIRVima1YpLEveBXldV9WVU19AyoNw0jaaE2zYYC2rZtu2Hdc52jUsH4uDc93Xfh72VaC2iA5ZgB3VBg9YxUw9lCOo%2Bt220rjp2LCVxPDTMVODbh5KFdk95aP4zMGEpnmERZvEVQ0ZK/qELxUkKTB0E1PESSs7vBLcDRSGT1em5nO6QT%2B2eFHnq8dpyvLjhHoKSxQrctd19VV4Dsrb61/PC7PkAL%2BORf5ureHjdlAB9cC4gEAgOMdAJYFCsEwP/acbhd4klXuPSeGRp6wNRM8JYfc3hEkHuMZOo9NoIKnjPOeqJf5cAXumHuFpqg/DMKvfw8ot7vB3sQggpCrJHxtCvNeNCqLnyJiDLWQcX5vzcB/LMm9v6l2QFApQLRgEEFASAcBbAoEWhQaw6hBCkFEL3iQlOVZ0GMMwQPIePDPZvDHhPQh6jf5mHIXNcRy916r0kAw%2BGzDdGsLseFDhFouHUI3r1PhupjgB2vqgB%2BgdwiRKfrw1%2B/CxG9wkclH%2B0iAFyJAWAiBqjjg2NoeSKx2i8loKbBwFYtBOAJF4H4DgWhSCoE4G4aw1h/RrA2BiQWPBSAEE0GUlYABrRIkhzgaEkFwME/gNAJA0GYAAbLMswSQUgVI4JIXgLAJAaBXjUupDSOC8AUCAFePTallNIHAWAMBEAgDWAQVIZxyCUDQHsOgcQIgQM4KoJIsyAC0szJA/GAMgU2UhzhmF4NPQgJA8CgOqPwQQIgxDsCkDIQQigVDqFOaQXQ1Q84ZlSJwHg5TKnVN6fUzgrozj3JVKgKgPwvm/P%2BYC4Fydhl2IgB4F59AbadKWLwE5WgVgQCQM81IryyAUAgKK8VIBgBSFoTQVEcRDkQGiGS6IYRmjxkJbwDVzBiDxldNEbQ3QTldOecZAg75aDaqxVgaIuUTi0FoIc7gvAsAsEMMAcQdq8Bjh6FKPEZLLbdDOFsLpYQdgrLqbQPA0QMwGo8FgMlas8AbLdaQQNxBohIMlJ6owsajC9JWFQAwwAFBXDwJgPO5EaldPhcIUQ4gUUNvRWoMlOL9BepQM0yw%2Bg42HMgCsVAMtsiup%2BSA3iphLDWDMLsrN2IsCDogCsLoPRnAQFcFMPw1QQhhCGBUEY1RChZAENugoGRT0MHmMMKoNQ6i9AmK0Tw7Q9BrvqH0FoN7D13tmJMF90xbBPu/YsLgq62mbGWPoElpAdm8D2fS75fyAVApBWyn4EBcBQp5WYfwYH%2BXFpWAgTATAsDxBXaQQZkh/DnAAJz%2BDBJIUZZhJCzK2QkWZtHoOrPWQELg5xZlcFmUkWjSQhMJDGQkejszYNkr2Qco53Ti3nKucKm5VKHmSuldy95bBODNBYFKMEPymBgTjFwWj5x%2BN1MhUQRdegG2IubdIVtSh21Yt0LQvFTACVuuJRwKpsmsV7MpXcs4PxaW22IIZ4zpmnTmcs9ZjDnKxXcsTv4MwfKlOnKFSK1AXK4iPKlfl1LIwDNGZ%2BfFuVtGuAr0VTsYgKq1VYr1VqnVpBWsGqNSahw7WLWTmtbaup9rHViBde1j1XqfXDb9aavAgbXU2dUKGnY7XI21DJbG%2BNWqk1bDqam9NXSs05qUHmqbC5lOlqYOWyt1ba3tcc025FLnZBtsxXUzzXai3TqsH2rby7h2jvNpwCdCip29osHO%2BDC6YVBqHfeubG6t0AZ3UEBg6AQNHrSJe%2Bo57j04%2ByJj39tREcNCfXjhH66ydzH3QsLHf7n15FRwzonUGFAQeRf5wLcHyUcCizFkzZnFwWasyMjDWG7Ppfw9lwVRGSNkcoP5tZpANn%2BEs6MsEUmwQTMkCx/51QefydsIpgVZyLnXNudSor2m3kfI4AZplLAFBSlNlKEXrJxgQvwHZmFDnZBOee6i%2BQbn3s6ACKQbzvmiXce53JilGmaV0odwCp3Lv7bu%2BtDgjlJXxXpf8Fl03uWUA5%2B5dbkvIwXeT1/m72jv8PesOT3wOgDWmvqs1Qa9rnXDXGtNX1/LlrBtkpG8AJ142M2TYLXt91s2A1BqxSG5AYa1uCA21irbCb4y7ZTdiQ7vBju5t2OdotOW%2BBlorVWmtHo628Ee0iiQL20Uh47eHgw32If9uiAD%2BpQPI6cFhJkn7WdedOIRdOHCjd9bIFwdHCnPdMoW9C9IobICnE9eoVnGYEnKnT9RnV9dAh9AQLAtAoDfoCnFnWneAsDVYdYSDCglZWPYLTgfnR3Z3V3DPHYLPCXEgKXAvQjUgYjUjEYCjFZZXDZMwSzfwfwBIaZMZLZcQsEYTILXZTgBTY5HgqjBIOjZIOZWjSQWjCZBjLgQIFZfwUleg/ZGXPpbjcFBQ%2BDJQ8wpYFYLNTIZwSQIAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/gauge.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/gauge.test.hpp)
