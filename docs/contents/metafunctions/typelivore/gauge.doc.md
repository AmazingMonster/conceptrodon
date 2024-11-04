<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Gauge`

## Description

`Typelivore::Gauge` accepts a list of elements and a list of containers.
Elements will be placed into containers via a process similar to pack expansion.
Then, the value result of each packed container will be collected to invoke an operation.
Check out **Example** for more information.
<pre><code>   Element
->&nbsp;...Container<sub><i>i</i></sub>...
-> Operation
->&nbsp;Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
->&nbsp;Container
-> Operation
->&nbsp;Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
->&nbsp;...Container<sub><i>i</i></sub>...
-> Operation
->&nbsp;Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;::value...&gt;</code></pre>

## Type Signature

```Haskell
Gauge ::   typename... 
        -> template<typename...> class...
        -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct Gauge
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<auto...> class...>
        alias Rail = RESULT;

        template<template<auto...> class>
        alias UniRail = RESULT;
    };
};
```

## Example

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

static_assert(std::same_as<Result, SupposedResult>);
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

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::Gauge` separates cases according to the number of arguments.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

[*Check out this test to see how it works.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEmYAnKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHASYLGkGeyaBbgQAnmmMrJgAdPfY9GyCCifYJhoAgpPEXg4A1ABxJheYCYD6fEwAdisX3%2B8P%2BewOR3BpyRhyYxzRl2ubHutze/2QBgUCnxABFMAA3PDbV6Bd5whE/P4Ef7KYioIgAJVQTHQEIR/2hFmFTKF8PRKJOZ32GKxbhBRHxhOJTFJ/wA8ldiJicm9BRL4SyAZTWnRDUaRWLPkajV4skZETjhYFyVqdXqBDLKTS6TLHvtGAR6dgQCAqWIvHd7gbArDbXboeSTgnLRKpZjUbLkVmZUrUCqGUSSWT7p9gMRMEGXgbxRKHRFgP9uUw6K73Wa27QZRWqzWQ0WwyALldUxD00LMwrp9mC0OS%2BqFB6El6GHXE/bHc25Aw8K32yd3drV00fdTaZh6W5A88Q29w5HvDGCQzx/Xk%2B/Nzap3LpWi/zzbErmYPFY2LNUNV9S8NyFE02Q5LlUF5flzz9VFGW/a1JwRWcZTw0553A7BFw1E9dTPN96zgghflNTBzR7aiEWw5itybZ0rg7FcKP1U5oO2AMnmDUNHyjF84wTO1hShFN4wnNjEUAmdlLnLxlWI0iy1uPtqzvUMcPhRsnQPWhuK7C1Tl0gdtIfEccS/QylNzFSXLUjTXxIyDl3ItdYLtYydz3UzuN8yi3AE7NbxEuyn2jIcvyFT95K%2BdMCJzeVs1HXEJIg0sKQvf0qO/QKWz5dBuMQnlyrQy9bLfFLIVkxyvnS7LQMwf5osEDd4KBEEwSEgcNxFNLVPw8bgJyhdvIK9CDPrPqquQmqPxhH87TaybFXUwtNO8ni/OK6S%2BospjvyS9anKFUrstCz1wsi69uoIWLxISxrpOStNFK2tz812mb8vLSs9Ji46Au3Ftu3Mhju17UGbKHcNspai7cO29KiM8rTDsozDpNK3d9xho88b4iLCqvIa7ze58Pqkljmsasb/oAtmzhxDqgaXOa6v8oyoZQiqyeW4XarpBmJ2Zn7IS%2BAB6AAqZWVdV%2BWISV5WABVsCELWVfVhXVeNxXDblyEzECCJiS8LBXTcNAGG2NJ72KiE2q5m4uuEnrir6z50HQAAtBJUBtVjv3mRxkCJARJkwVQ0mIf4C3%2BOLwTWiwXrE59vvDmWFM%2BD2QK9l7eto1l/gD9BNUiaXRXTKPaVjhh48T5PU/T9MRWziNxOFSx/i4PPpbk2Xi5y73hr9iuAWrrWAHdUHrjbjVaaOW7bpOU92tPxO7mFe/TgfRTMEfUoL1LWu27Hy7otkwr42X5fl/4tavNkNEL0qhC8NJikwOgbkV4vC0DZGTR%2B3pTgaFIEPWBZ8Gqy1KsAhQoDwGpTdP1UE2ZJjoHDBEPYlYxAAH1HbzF9m4AhsCv4NUwuGcWVlA4h05LA6utdMCsMDovZexV6Hw1OJA9ciDC5N2QMQpcCQCAQFweGBQNxxHXhQWg2Bv9/6ZEAUosBbwVhoxfm/D%2BQ9v5Q1UQAoBICwHEK4PdU8FMuDwNgYESSRiOKaIIJY7iwJsEykbgQPBIACGYCIbQUhcdWgUKof8Gh2BSA%2BL8QEoJITW5hNeqcCJw8GQxMWr4/BghAm6mCWQ5JMoIkIMwnZBhbg2F114SAUyMpBFOKvt8detIFFKHaNI7JIA5FsAUTKVxKi/6mNcdo3Rr936TH%2BGfJpP8hnqLMagixZhrG8SgW4GBUzYGSEaebZB5i3HLLJp4wapxYk5MIfkxJ5CUmUMENQt4mTI5dPiZcwphgblpIeWc/xuSElvPCXcqZI0GT0Jqow4OodOE10iFC7hG4%2BGWTcA04RTTRFtMkZ0vxPTMB9NOAM/4Jj5kjIZDo%2BMHA1i0E4P4XgfhuC8FQJwNw1hrD/AUBsLYnVzCBB4KQAgmhyVrAANYBEkLcDQkguBQkCBofwGgzAADZ5VmAABzKv0JwSQvAWASA0DA2lWhSAMo4LwBQIAYF8o4FoNYcBYAwEQCADYBA0jqXIJQNABw6AJCiDcTgqhlXyoALTyskP8YAyAY5SFuGYXggDCAkDwHgux/BBAiDEOwKQMhBCKBUOoS1Og9AL11GkTgPAKVUppfyw1nBNTqWdWyVAVB/h%2BsDcG0N4ah6iuWRADwHr6DJy5VwFYvALVWtIBAJA7q0ierIBQCAk7p0gGAFIMwfA6B7GIKaiAsRK2xAiG0c4JbeC7uYMQc4mpYjaEwA4Q9pB3V3lrrQA9ebSBYFiKCRUtBaCmrpS%2B/YhhgDiGffgKsDg8BUivJWhOV71I7B5QEylz7aB4FiLqU9HgsCVtongbVP7wPEFiOoykLB/1IaMPytYVADDAAUAANTwJgBeJ5aU8uTcIUQ4gM2sezWoStug7EGDI6YSw1h9DIdNZANYqAXY5G/QG3BR4hNWEsGYA1qA8PEATRBiTvQr1NBcAwdwnguh6DCBEEYVQxh2OKNkAQMw/BWcyDZhgixRg1B06BgQAxphGYKHYuwun%2BhTCGGZpYlnbBBbs3oeY7QXMWZqGsNlmxtgSDLRwalpB9X0s4E2/1QaQ1hojZ2/4EBcBxv7ZbQdw7yNrAQJgfkYwIBCpAJIQItxkiBChJIcVZhJDyt1f4eVqQEOatINq7ltx5VcHlcq5Iyqpv%2BAlf4dr8qMuVqNSas1vLyNjrteOh1taXWzvnX271bBOBtBYFSKEAamCLidFwZItwuBipjfgIgGnE2ZrY2miQ0guNKB48%2B3QK7C1MGLXS1L6XMtVo4DWp16l/gNpTsQS713btqnu4957Ghis9qnX2gegQzBDq23m61E7UC9oSK6udlP8djAu1dgNGOl3JC4DAmgYCEibu3c%2B49%2B6b389Peey916f13uDA%2Bp9BrX3vrEF%2Bm9WBiNGEAzLvAIHHDge/QaqDyAYM3vg5WpDKH93oZ2AarDOGeV4YI0oIjJGmzbco0wajdGGNMZvax1NHG/uyG47mg1wP9D/pQMyywonYjica4a6TcdOByd8QpsPFgVP0vU5pqPCWGgBecBAVwkW7GmYqK5vQ1mmgF/SI5posXlh%2Bezx55oEWfP2fc00LzwXi9xai03/ILfosd/M7XhL7LkuDvVWlitz6jXI9Rzdu7zYHtPbFcV0r73CeVdJ1amrdWsCJGj8NrVIBAiPfFVCJbUIpWSB68Gux0P1u2E2yO8lO34B7cdXWmnx2vU%2Bo4Bd1tLAFAqQY4qRF8URJhXsysE09Avd2N01fcs0AcA981ghQdwdS1x8oc1tq0Dt61G0/8Q0ACgC05QCsxJlu06dp1CdAgScn9ycUAKC%2B1P8GCxggD/5iEQDkhiEwC3F8DV0ucN1KBecDUhcn0eURCRddMb0JdBApdK1ZdgAP0Fcf0lcSNzdeBgMAstdINVBoM9gDdckEMDVjdUNzgzdMMNMrdeAbdCM/0VdHcyc%2BAqNaN6NGMQJPdZBvc4Cvt/deMj9g9BNk8I9M8Y8mhv15YZFFNrBU9DV08sBgj/MG99NDNe8TMDMa8wsy8cgK9MiygQsS868%2BhPMe9jMCic9G8Fg8iu8/NijfNwsKjO8h91gkt01IdJ9VNst8D/hCDgCSC9gyDV8SB18aDqtSBat6s99UsRttUUhbhAhAh/BZUJVdU5ioRptVsp9OANtzURjhVJB/A2t/BlUFVkhJBkgpUOsuBggENAg2istjVN8BVx9o11j2j7jaC1g8MshnBJAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/gauge.hpp)
- [unit test](../../../../tests/unit/typelivore/gauge.test.hpp)
