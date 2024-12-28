<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSegment`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-segment">To Index</a></p>

## Description

`Pagelivore::CognateSegment` accepts an operation and returns a function.
When invoked by a list of indices in ascending order, the function collects the differences between adjacent indices and instantiates the operation with the collection.

<pre><code>   Oper
-> I<sub>0</sub>, I<sub>1</sub>, ..., I<sub>i-1</sub>, I<sub>i</sub>, ..., I<sub>n-1</sub>, I<sub>n</sub>
-> Oper&lt;I<sub>0</sub>, I<sub>1</sub>-I<sub>0</sub>, ..., I<sub>i</sub>-I<sub>i-1</sub>, ..., I<sub>n</sub>-I<sub>n-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSegment
 :: template<auto...> class...
 -> template<auto...> class

--The list can also be provided via `std::index_sequence`.
CognateSegment
 :: template<auto...> class...
 -> template<typename...> class
```

## Structure

```C++
template<template<auto...> class>
struct CognateSegment
{
    template<auto...>
    alias Page = RESULT;

    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will invoke `Operation` with the differences between adjacent indices collected from `2, 3, 6, 8, 10`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    static_cast<size_t>(2),
    static_cast<size_t>(3-2),
    static_cast<size_t>(6-3),
    static_cast<size_t>(8-6),
    static_cast<size_t>(10-8)
>;

/**** Result ****/
using Result = CognateSegment<Operation>
::Page<2, 3, 6, 8, 10>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will pop the last variable from the list and then subtract the new list from the original one. The process can be described as follows.

<table>
  <tr>
    <td style="text-align: center">Original</td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub></code></td>
    <td style="text-align: center"><code>I<sub>2</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n</sub></code></td>
  </tr>
  <tr>
    <td style="text-align: center">New</td>
    <td style="text-align: center"></td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i-1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n-1</sub></code></td>
  </tr>
  <tr>
    <td style="text-align: center">Subtraction</td>
    <td style="text-align: center"><code>I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>1</sub>-I<sub>0</sub></code></td>
    <td style="text-align: center"><code>I<sub>2</sub>-I<sub>1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>i</sub>-I<sub>i-1</sub></code></td>
    <td style="text-align: center">...</td>
    <td style="text-align: center"><code>I<sub>n</sub>-I<sub>n-1</sub></code></td>
  </tr>
</table>

We will use `Varybivore::TypicalPop` to remove the last variable from the list. Then, we will employ `Send` to utilize the result.

```C++
template<typename...>
struct Send {};

template<template<auto...> class Sequence, auto...Variables>
struct Send<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    struct Detail
    {
        using type = Operation<Variables...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = Detail<Agreements...>::type;
};
```

The result of `Varybivore::TypicalPop` will be sent to `Detail`, which performs the subtraction through a fold expression.

```C++
template<size_t I, size_t...J>
struct Detail
{
    template<size_t...K>
    requires (...&&(K < J))
    using Hidden_t = Operation<I, J-K...>;
};
```

Here is the entire implementation.

```C++
template<template<auto...> class Operation>
struct CognateSegment
{
    template<size_t I, size_t...J>
    struct Detail
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Hidden_t = Operation<I, J-K...>;
    };

    template<auto...Agreements>
    using Page = Send<typename TypicalPop<Agreements...>::type>
    ::template Rail<Detail<Agreements...>::template Hidden_t>;

// Indices can also be passed using `std::index_sequence`.
    template<typename>
    struct Hidden {};

    template<size_t I, size_t...J>
    struct Hidden<std::index_sequence<I, J...>>
    {
        template<size_t...K>
        requires (...&&(K < J))
        using Detail_t = Operation<I, J-K...>;

        using type = Send<typename TypicalPop<I, J...>::type>
        ::template Rail<Detail_t>;
    };

    template<typename...Agreements>
    using Mold = Hidden<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEoEapAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdsKoCK4AGLEWRfQ5AnY7W4AdUwtwA7nRaLcvEpbgQEHhPlQvNjGiLUCC2bc0NimLTmLSRQhualiB8EgA3TDoW6GI065AbJRG1IDBQAOhBtJYqQMtPxBGRz2YbDJVwmxC8DipNPpjMEMIA7FZw/dYVYrg7ME6XZg3YnnSqU3CmAjULa82jFQYFJ8hJgAI5eV6YUjGnN520ANVaeCYsXoCh9lz9AYIQdV6AZsnxpYrVfxTeILbbH3rZMC6PjkZBtxXIrTyfx2aI9YsmGAEQYEWAHfny9XQqPt2UTGA3Nh91uI8r2Mzbl3%2B4Yh6MdrzNYnU/bWdT0CONgWjWNyWuSkhAQBECHoZkDiBR101dLM63zU9fQIf1AxguD6Ag%2BMKTuAAVD08FEWhlFQVJELOBMkwzTcMPtLCuxwntbnI1JKLEGi6JMJdwJAyCUI3dCiFuOk8GICZO27QMeL46jaPxGS5IITshNA1dBUyIwRQ9O9AgffCCHg1851AoSY1E4jLnE5jJNQaTZImGst1c0slXQBTOKUiiqIE9T3IIGsfIEPz2J0s8VwvQz3WeGFTMfWCLMIuENPk4CbJEmyrictC3C8tzNM8nNH0wXyKu3PMAHlRQSE8Fw43De2U4K1KysKIuqqKa0azU5KA1rYquPSEuAIznjilKH2pftB0EN1jK9blOv47q3CG5rRpAEAkszVq9IOoruWvW9QvKqrfOsjF8sgv49iqhgjW%2BRjUNfI71tGkFFN7Us3ojKM7IKxz12ctxzpYuq2OwQsmGLKrRxfWrczzf9W3bfz2te6K3CfMc4Sx6cf3h7Slwm1cYbhWmStYgtISRz56ueYgVWyTs9IBh5MBaOg5vGy49MmgzpqO%2BbbjZhJOYEcdm2xmdMPReyRdXWyiOBamV3p%2BmvNGxHi3rS5gB1RNGAIFq5qm24ACUmDoKXHgF2h8VN822EEcm0TO4ytc1tX5QBEPAWDu4AEkkwtwQ5YYejWVDpOGIc57bg8YA1UwUtgC93sPsKyHiv1xn5yN1n2bj3GuIzrOc7zh7dJpovX0yAAvTAAH1ewjmt267gh6wAKW51deZdx23Z1kG5r0%2Bn%2B%2B7%2BsAGlR9F24dQrWSPluCBZzMAA2cx94gJeUrcW4h%2BWZZZ/PcXbgACTwYlGG7qWZY5xp8V7i%2BAFol7%2BtWelA7gzni3WGGNbQe0wDHK2q99KXkuiZMyrhVqelYBtIKW1UjuzNtAvOPt5x%2B1muxU6h0W720nviCegs4RQJgQQ7AZ1yGP2fgwbu91U7sgjm9Si29RDxzEAoVy8RbjWmLIaeBhkTD7w0ESA6EQsCqE7koVGWxpEaHtNPPWa10FwN5iwrA8dYqPQcqApixUF49z7ngDui88wjxIWPAKvYDGMHxHIkACjMBKJUc%2BNRcJv5DwASdDWVN1Zr3njYgey84F6Q3l4Lenxd75gPkfE%2BZ8L5XxvvFO%2B1DaCv3vNLSun8Ak1iHn/ABIC16SIlsZKWQMCY/XQdxTBqlsGlIvvtQ6/tHFryYeY7kDsaFuDyew3KQsTHa3CWuAZqDGDoJNrg%2BhcDbYAFlPBGkKa4hgODPaWwYUQzMeUwZPWTgXKCdxqSsGdNyc5z1k5AgxGCCEUITIEgEFsVIsCYokQOEU2WMpzklzhtXQM78q5B1%2BS9IQXhUhFENHbD4XhaD5xZCCW2MK4UZARUilFb9ilc3jHCOacxHDIE7qIHKbhLFoggGYVYJKWhkopUjLScIaXzggIEH%2B9LSCMs5uSylbLqVRLGdgCA%2B8f6BAZdPUllEWVUo5eKgAHD/feMrplysFay9xoq2Xiq4BoH%2Byrr5EtVuDNOiKFDItRUhdFd8rU2qlrXDM9dLb4nBSU1qB1EH4jMDWYItx941mVTWQ1HCplp1Ih8W1KcOICs7izBIBAIAeIUOgxNJ43COpRRFWF8L0A5v1dfECHBVi0E4P4XgfgOBaFIKgTgbhrDWFuEIjYWwYRgh4KQAgmgy2rAANYBEkLaDQyqzBmAAJyTq4P4MdyquDhnDNICtHBJC8BYBIDQKQa11obRwXgCgQApF7bWstpA4CwBgIgEA6wCCpAROQSgaAnR0ASFEdBnBVDKslfvSQtxgDIGQLcKQtozC8ENIQEgT89D8EECIMQ7ApAyEEIoFQ6gz2kF0FwUgPIOapE4Dwctlbq19vrZweqCIH29lQFQW437f3/sA8B0DZgd4eFffQYgnbAhcGWLwU9WhVgQCQC%2B3iXGn0QDE2%2BxIwApD%2BpoCi5qlBYhkdiBEVoyJCO8HU8wYgyJ6qxG0NVU93aX153qgwWgWnMNYFiF4YAJVaC0CPdwXgWAWCGGAOIWzW8HB4ANK5ut3jqoIm2N2iItJV11qRLEDm%2BmPBYDIzhPAm63OkANMQWI2LHieaMEiIwfbVhUAMMeBs7weQyxrd2uDwgqJIekLVtDagyPYf0F5lAzbLD6DwLEI9kBVi0UaK5n%2BRJ7ymEsNYMwe7MuTiwP1iAqw7AmeyC4N60w/A4bCBEYYlRRg4aKFkAQG29CHcaAsEY1QegrYEP0KYnhOh6GW/527kxBg7cWPt2wb2Ts4bmG0C7e3qhLfWJsJDxGOBVtILu3g%2B76M/rVUxoDIGR1sYgLgKD3HMR8YE0V1YmomBYESIt0gQ7JCBFtJOwIy6NCSDMJIGRGh/D70nfoTg67SCbt47afeXB97KsnQu/e/hJCzqp8GmH5GD22GPT2orF7r0idvVRx9FApOoE4%2B%2Bz9HBWgsD1OGH%2BTBEaGS4JO20XBR0QfwEQObsHZAIfEMhprSgWuYd0P6vDTACNuYh1DyX%2B7KP3oRLcWj8PGPG%2Bmqb83o72Ma/EwkHj9LcdnuE6JuPMnJPSa4ygAwRhTeGr4HQWkckVNqY0/p7TpBdOacM8ZhwlfzOW0s9ZsjdmHNOZc5XjzXmfN1vwGaRwgWyMhfNLSSvkX6hkdi/F5EiXth1pS2l7tmXstKFyz3o88uSs3gUOVzAlXPSV9qw7hrKH5Au4w3W937XCsTasN12LC3BtfOyCNsbpk79TZmwkObHx4BLfqBuz8AgFcF%2BxCDekByWAOwyCOxyAe3yGgOKGyEgK%2B2e0aDu3aHgM22uxeyaDexQKu3%2B0wLyGwKIIIIkBB3bXBzZ0h1I0wzhwY0RwjxAzNwtw0B3gxxtx4xxzlxT3x0wEJ1GBJ1XQ5y5zN1p3DH8EnSXUCDpwZ1F2hzI33UPVl0E3PUvRvTvWo0z3Ty4w/TYE4F1z/VuBYAUD1GAz1Cj2TAmCt0xxgxw2P3qwkEa1kGa0vx0BAGCE929yIxoL9yUIoxVxozo1UGMNMPMNuEsLN2sN7AgA43jyxzBGlWTyEwvTT01zIDVyz1GHMLhU7iiM7hiM7lCMayL2UwgFU0w2rwr3S2qIMyMxMwbw1wsysxsz70wHs0czEE73S273y3n3cz80Hz/0wxHzC3H0EEn0w2n00zn2S0nCX14BXxy0TA30KxTz4FK13wqyqyP3tycKd1cIv1a08Jv2MC6xsEf3/3rRfwEFcx2DkU/0sGm1h1myfj/wGxwMaDW3cCwL0G23KEu1OxgMaDALO2QI%2ByBL%2B0ANwIwLALQL6HwMhKByex%2Bz%2BL%2ByRMBJRL4zWCoIoL8LoL3U4HozCLMIsKsIzAmA4OtxIG4P414KE34MEOJwh1EJACnVtECECH8DnVF23S5PDH50UPoM4BUJPTx1JxAEkH8Ep0XXDG3WVUkBnS4HHQPhoMCEJNh1FIZP7RoPA2FKJOlzUKvgy2alW0kCAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_segment/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/pagelivore/cognate_segment.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_segment.test.hpp)
