<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::CognateFilter`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-cognate-filter">To Index</a></p>

## Description

`Mouldivore::CognateFilter` accepts an operation. Its first layer accepts a list of predicates and returns a function.
When invoked, the function removes every argument that satisfies all of the predicates from its argument list and instantiates the operation with the result.

<pre><code>   Oper
-> Preds...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> Oper
   <
       (...&&Preds&lt;Arg<sub>0</sub>&gt;::value) ? (nothing) : Arg<sub>0</sub>,
       (...&&Preds&lt;Arg<sub>1</sub>&gt;::value) ? (nothing) : Arg<sub>1</sub>,
                            &vellip;
       (...&&Preds&lt;Arg<sub>n</sub>&gt;::value) ? (nothing) : Arg<sub>n</sub>
   ></code></pre>

## Type Signature

```Haskell
CognateFilter
 :: template<typename...> class...
 -> template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct CognateFilter
{
    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will remove every element whose value result is divisible by two and three from the list `Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>` and instiate `Operation` with the elements left.

```C++
/**** Vay ****/
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

/**** DivisibleByTwo ****/
template<typename Val>
struct DivisibleByTwo
{
    static constexpr bool value
    {Val::value % 2 == 0};
};

/**** DivisibleByThree ****/
template<typename Val>
struct DivisibleByThree
{
    static constexpr bool value
    {Val::value % 3 == 0};
};

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = CognateFilter<Operation>
::Road<DivisibleByTwo, DivisibleByThree>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<Vay<1>, Vay<2>, Vay<15>>;

/**** Result ****/
using Result = Metafunction
<Vay<1>, Vay<12>, Vay<2>, Vay<6>, Vay<15>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateFilter` is implemented based on `Mouldivore::Sieve`.
It transfers the result of `Mouldivore::Sieve` to the given operation.
We will use the following function to send the result.

```C++
template<typename...>
struct Send {};

template<template<typename...> class Container, typename...Elements>
struct Send<Container<Elements...>>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<Elements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct CognateFilter
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Send<typename Sieve<Predicates...>::template Mold<Elements...>>
        ::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwA7KSuADJ4DJgAcj4ARpjEIACspAAOqAqETgwe3r4BwemZjgLhkTEs8YkpdpgO2UIETMQEuT5%2BQbaY9iUMjc0EZdFxCcm2TS1t%2BZ0KE4MRw5WjSQCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpiprozIeJgKd8cX17dnAJOvyulxuxzuHiaDDwADcSOwQAAVACeqTwoloyiYs0w3yOwOYbAUqSY2whqChsPhdxMgSs11BBEwLFSBiZJn8bgIqMYrEwADpBRzsKDZsQvA47ii0RisTiaXTaQ8OfSQX9dncLNjcW5tSBQYzmaymOzOdyXoTcVjkABrTDuWRMBbEYWigjiyXS9FiOWmtzWu0OwROyIu/wihmK653GN3LyZIx3c24jkPO4B%2B0eYPOlUGwLK/yq0G7DUAJTqm0yMJ1eoN1yZLLZmANnNBsaTRqbHK5PMtgv5wruyAMCi%2BWaazqupDbsYbxr9yb7QvDQ5HY8dzpsM5ji75/ew9DYgiuClINOjs97e8FB%2BZjAIFlP26TV7Y/YA8gQEAkFC2Iyf3QlAgpVRb1MWxP1xxDBIQU5W8jwIE9%2B2FM8oM3bt4PvR9kPDM9P2/YgFBw/9aVVdt4wiYAXxeGl/DTL1ZQg5sLxjbtn3bNDQ1gtxMOPIjBTPXiH34gdcPY2N8J/ZCWNo7AQBAZNc0jAsi2UuswXuXVUgULx6DxQ5gTnLszVfAVl3/MUgIhJhtN05tC3U/59juIQPmrfTzkNRsTXsrlOx87tdzfczV2xETlGIe1vSZX9wzdD1gNczBqzzMjZ38hdTLuITXRkyzJSeCdaHPK521IuMEyo5NaLTLSdPoNi4sLBUVPU9sjICkyLT5bLD3vXLStjSKAEcvDwSKvggBgKTuCBkLMAA2cwFoiqLRBijC%2BsEYV5JhMQvEwFYVmffLgMKp1aE2u9trimTyooxNqtTazbIauCtoIV1mqVJS1UGncMt8oKzP5ITYv/cjKruABZTx0Bq8lKThSL5IYn0mOfQKsvOugroQ8H5OTYjCZ5X6fochk/nBIRXA8wzAax7rgtEizAMlGmGHh0jydUq4OoXBmut5ZnB2HMLyWzUMz2B/cPvB%2BKrI59Bu04hI8fvESvpIqN/o7byBf1oHTOI0LRzud8XmIE1sgG9tTseTAisxnX20hyjqJTOjzct62BHVwRNaatLWPzMmZP5oHBZ7JmQdFtd%2ByuYBIuugh5Zkh6qNLVAmC5r2ccuzlE%2BT/HiYU0mKZBUOK%2BLQFa6BGv7gASUbFPfYYOmG7ruvgS8%2BdI8NxnhdjlcxbNi2Ejbgb7Y8YBmCZAAxOgmRdSNg71vvAqjmWQtH8LIvwdbPlt2N7YiilUCznPnbX9qt%2BNm85eP12Kvd2HaFztMlcHy0XLc3zVoPj5QOckFKAxhnDf2qdiJP1doTMBl9lacnHlbXoX0148zaulAeZo74xxNrvBOSdMApzTrrDOdwEEIzPkQBB3Yi7EJLuZMmVdeZOS7p5Km9xsCqFYKyXEPxO7sI4X9cw/gIjDi8FgWibg0AMG2KkVOA1BF3AAGpMGRB3esUcmBeCIHcRuU82bATUciVKdxZjW2QEOAQOJVCpGIHcHRei9reBTHSAxLCWphw0ocR4sI8CZFiPQCwyJEQAHdUCaL5rgoeqixCGISn4mEAS8BBMwCE8JqBUonSaI4KxsjbH2LuLEVAng7guIOtfNRtBdr7RTGYJIdwzA1WehoDBalq6cN8Q8fxgTgmhIQMnKJEdv49WqQkqyPTkl9PSQM5O2S8q5PRNYhghSHElLKRU5iutSLVNqa4mkDS7j%2BBaV7NpLC8ytUpj45yyC27DJiUuFmCtJR3NQZ0m5MNHZMCoF4ORvQHnYOjkPBOxBgCkPIdDb5vz/nZARjPOemBF60GXt2N5NtbpXHkrQzkUyUlpIyREs8eKZkZMGcQga8k36ILcFcMFwDvFORcl4VIRR7TlnqsBAR1xyFCBZWy9AHLdLAWeuiv2nITHdi4ChOJpjORmBlZKzkXAkha0ZeCIVKKonkM1SKr2UKmgwvqH7BkEr1FSsVea5VCrcKyu7Da7AZ4lVuCWra51Kq1UfKZYiT4XL8RuksQAfTCgkAgEBZjoHkgoPkwbYpuF1WePlrKMjss%2BMK4Ux1CwcDWDUjgSReB%2BA4FoUgqBOBuGsNYcxGwtj1P8DwUgBBNDZrWDaZIkh%2BQaAABxmDMAATl7SqrtnauCBECNIXNkheAsAkBoDQpBC3FtLRwXgCgQBzsbUW7NpA4CwBgIgEAGwCCpF0eQSgaAWR0ASFEPknBVCdoWgAWgWpIO4wBkBWKkPyMwvAopEGIHgSNXAZCCBEGIdgUhgPyCUGoJtpBdBAbCVbVInAeA5s4Pm%2BdsGl3vl0ce4CqAqB3DvY%2B59r7313E/c0iAHgL30AcaIrgKxeAbq0GsCASBz1ojo6eiAnHL2JGAFIMwfAl4/koLEWDsQIjNGRCh3gUnmDEGRO%2BWI2g6gbvreehC74GC0Fk5u0gWBYheGALqWgtBV3cF4FgFghhgDiAM/gSK9RqyWeLZgVQFYmRyfIIIbosHaCpKtkpjwWBYPujwNOqzpBqzEBKUoJ4tmjCBaME2tYVADDgpUR8MJ49C31v4CBjE4HpCFagyodQBn4P6DsygCtlh9CpNXZANYqAFHZEsw%2BiNqZTCWGsGYRdsX/1YGaxANYtRjV%2BAgK4KYfggNhAWBUKoegihZAELNlbGQ1sMCGEt0YQGJu9H6JMTw7Q9CHYaHMXbIxEgHbmBtu7AxrtLFu%2BN6t2wJBobzQWrDnAiP3qfS%2Bt9H721UdwIQEghy61MYbWltY34c6jDG6QVtkh/D8l7UESQGhJBmEkAtWdSQFq9v0JwSdpBp11v5AtLgC1O29uHQtJIkgVWY4WphgzS6V1rth5utje72MHtwyeigvHUC0avTejgzQWAwkCA%2BpgoVExcF7fyLgHaf34D/QBvQZXQPiAg2VxQFXYO6GE4hmycmvsYYXbwbDwv8OEeI4DpXVEVdq47bNGjXGEhQ7MDDljW7Bd8e46LkPowxZGBV1wOdNAUViYgBJgzCmZM%2BZT0plTamHA%2Ba0/eHTenYNGZM2ZizPmbN2Yc8Wpz6nYSfFgx5rzOx60RCZLm4tgXYjBeRKFnYxaItRfrbF%2BLmBEsV8omlvgmWFDZcwLli0Pm9fFYkKV2QxuYNVZAMJgwqXetWAax30brX2s2M4F1ggiCHi7/64NhIw268ta6D0bILhOYPZCJzZ7y2gOrd6G/n/2RP99tH8a8BBjtWhTt8gDtugQC%2BgrtFsbtzt7sIC5txgnt4CXtPt1hNgPtGNSdvsOdF0/tndSNI83dVd1cNBZpwc/0odGNmM4dSAEcsBEhkcJ0p0AhVccdAgkhe1R1/Bcd8cWcCC7dOBud10J8d191D08MeNw9iBr02BOAZdSMWAFAYQrEYR3cmxZhNcIdhtddZB9cStIM19Kti1dB/BSALdkMrNrcftOdOAcMj1dE7gCMiMVC1CNCtCgFgJqNxcfd6MzB/B/AA8JCON/D%2BNZCIi6MQB1DWVA1NDe1A1tCCBA1VBn0RN49CJxNJNpMlM088jlNVN1Mc9xdtNdN9Mq9MBjNTMxBS9oty9kte9rNxoa9XN69PNkBdEm9eAW9/MDMO8u8e9wt/0B9eAh8U1R9ktx8%2BdJ8mAsscs8sF9DCl9DdV9oMzCdAAgasd96sbAD94Aj9ehLNdgI06s%2BtLABs7chsAN79kcLtnBptX9kC9AFtygEDv8ttf8XjPjigAD0Cv9gDJswC38HjYC0D3iMDHsTs8gUCLEWhADXssCa1MDc0bdfsOB3CX1VD1DylvCYpfDqDIcGNQi%2Bd4dMBEcWCvtydp0%2B1%2BRgikgkgccY8NBgjAg6dhCS1RDbAedA8joUcQBJAkgMcR1AhZ1O1JAB0uBu1Fo8D/B7DCDl1edWMvtv1OSudlTm0Ysfxn9JAgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/mouldivore/cognate_filter.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/cognate_filter.test.hpp)
