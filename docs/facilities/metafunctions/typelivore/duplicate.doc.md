<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Duplicate`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-duplicate">To Index</a></p>

## Description

`Typelivore::Duplicate` accepts an element.
Its first layer accepts an amount and returns a function.
When invoked by an operation, the function creates copies of the element of the amount and instantiates the operation with the result.

<pre><code>   E
-> N
-> Oper
-> Oper&lt;E,<sub><sub>1</sub></sub> E,<sub><sub>2</sub></sub> ...,<sub><sub>N-1</sub></sub> E&gt;</code></pre>

## Type Signature

```Haskell
Duplicate
 :: typename...
 -> auto...
 -> template<template<typename...> class...>
```

## Structure

```C++
template<typename>
struct Duplicate
{
    template<auto>
    alias Page
    {
        template<template<typename...> class>
        alias Road = RESULT;
    };
};
```

## Examples

We will instantiate `Operation` with four `int`:

```C++
/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int, int, int>;

/**** Result ****/
using Result = Duplicate<int>
::Page<4>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

One way to implement `Duplicate` is through recursion.
We start with an empty list, adding the element while subtracting the required number of copies until the number reaches zero.

Our method will be different.
The goal is to generate all the copies 'simultaneously' in the sense that there are no intermediate stages.
We will achieve this by pack expansion.

We want to bundle the element and each index from a `std::index_sequence`.
Then, we will pull out the element from each bundle by a pack expansion over indices.

First, we need to create a `Bundle_t`:

```C++
template<typename Element, auto>
using Bundle_t = Element;
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
            <Bundle_t<Element, I>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABsABykAA6oCoRODB7evgHBmdmOAuGRMSzxiam2mPZlDEIETMQE%2BT5%2BQfWNuS1tBBXRcQnJaQqt7Z2FPZODw1U14wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpjprozIeJgKd8cX17dnAJOvyulxBZkCEWQ3iwdxMgTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/oCqUDQf99ncAJIsdL0NiCJhNb5HYF06mA4G0453CxeBjoegAfQIXMOwIImGZBnlBIIKJezDYd2wrMYBFIdyYiNQ5OuXmyRmFovFmClsMCDy1OsEcKs10F9weXhZeFE8pl51B8sVHMwKrVjFYmEdCt1Jquk2IXgcjy9yN9obdAHZXVc7nm7kGWSGw%2BrI3H83cE0npcpiKgiABZTzoWHZkyZh4uim5/OFpWh%2BHZABeNoIADoJwzy/mq8na/XUE3aOgCcSQCAIlhVBKlABHLxvAduBkTsfkwIY64V9s5isVvvF%2BEP5VP8MazCn9F3KFMBRfADyLzEByuTTnelYEImyZPK0dCguBeY3vBCEVmaETAAW4Z2g6gEJCBAjIShiHwiKYqSgQBLajGgj6lOF6fheXZXgh7adoEOaEXez5HtxJYRmwDHYN%2BBh/qeVzAMQmDUQQChgXeaEWgASqgTAtnCDowUwcHwuJknSQognrqqLxMT2iEdqZnG8a%2BpYCROulSWyMlyQpGFLmp9p3POjbNgSDn6YJlnMXm1luMOo6MnJs41nWRDKEwwAZmZdwgHc6ReLEaZebFi6%2BYOBDoOuLBMAA1jam6YNue4HjiR50RijHBa2VgWex3b3gqRYvm4hpEGJEmObqsmNclrleQlUbqdlC7xYlfkDQFE7nhxrUcZSfI/O6hxaqorAslGm3rRtsrdlikLQpN8JoLV6TOSNW30rhwGcodVyhcZ/EfktI3RXcT34QwQU3EKQheiUmDoIpnxeLQ0qvWNoPpODkPQ7D2F/UBAMEhEep3Dj%2Br43jzqMW1bpHfSUMKDDcPcqCY2U9T6Oet66bY8Tl5XOus1HpIcbrspqkEv9TTLd2dJ3AAKp8NMndc8yOMgEq/ko7QQGuIAKJGSvDW4DOw/qiPI3rFEXisLocGstCcP4vB%2BBwWikKgnBuNY1iVhsWyTeCPCkAQmgW2sJUBJIY4aCkZhmAAnJHXD%2BGHKRcJmmbSFbHCSLwLASBoGikHbDtOxwvAKCAOd%2B/bFukHAsAwIgIAbAQ6V6hQEBoMydAJFEkacKoKRJAAtEkkh3MAyDIHcUhjmYvAQ4QJB4IVXAyIIIhiOwUhL/IShqP7pC6IvADuwHpJwPCW9bts7wX/6Io3dyoFQdw9/3g/D6P48h2YdwQB4bf0MQsLexWLwMuWg1gQCQK3dI7cyDN0gdAkAwApBmD4HQeUxBi4QFiDvWIEQ2gohPrwHBzBiAon/LEbQmAHAENIK3Jy/4GC0HweXUgWBYheGAD1WgtBi7cF4FgYqRhxDMPwJJBweAABunwd6VUoYiHYPscYNB3siWIwESEeCwDvSCeBM68NIJI4gsQsiYCeAI4AyIjD%2BzWFQAwwAFAADUPj71wnbH2/Bl6iHEOvdxm8VDqGYXvfQhhjCu0sPoPAsRi6QDWKgW6uQeF92JOpUwlhrBmHzgY4g88pHRN6JQpoLgxQzD8IvMIEQRjVDGIvEoOQBDFL0DUpoixRiJEXnYfJ/QpgdE8F0PQ7SxECAGO0ZplTWm2C6fUtpXSRnLC4GsBQHttgSDPhwG2udL6cEfr3AeQ8R5jwnp/CAuBZ7/yxHM4BVi1gIEwKpMYEBA4gEkIEMckdAjJw0JIMwkgkjZ38EkSO%2BhODp1IJnQIXAxxJC4KkSOCckj%2BEkLHV5SR1nMILkXEuvsrGVxruAuuN9ETkEoHAv%2Bnc2CcDaCwcRmY%2B5MGEsE8ekcxzgodjPIgWSF4bxXl46QPjFB%2BJ3roZBh8mDH14SstZedeBX3xdKe%2BWzn5Dx/BaLgjLmVfx/lAv%2BADAhmCAZi8uYCIGoF/gkQlLdjWarGEqxBMcc40FhgkDBWDmFELwdQ11JCyEUKoXo2hup6GMJ3qw9hnDuHUP4cEoRDsREdMkTwllqhZHymoYo1ODsVFqJRBonYDttG6J9gYoxShTGRvQlimxCUHFOJcdQnxXK148tkHy7eASQDIIMJYlJVgwkqKifcx2cSBAJKSfaLtaSMkJHZTk/t/SCkQFcJMkIYoZlVIyFkWpeQemFGqeupp5SlirtnZ0wYi6j2DOmfulpfSJlbpKeMhYl7RnLPWJsJZczAWrIvqizZT8dl0uVaq0OX9jlsu1ec/VoCrk3KwIkftqdgWgsZR8zM/hI5J0CJ875CKUX504Oi0uWKq613ro3M1xKO5dw4BSl%2BLAFDiLHuIlVY5%2ByTGnvgNl889B1s8Q2jezb/EO10MEYVorT4folRsjg18G6Ijvg/VQNG6MMaYyx6U38LXQO1YEPVICK64vIzAolGm/4gHo0jCUjHI4SlUxKBTPLUGOsoM6h2HqmE%2B1c16/J1C/WCADUw6NmA2EcLEGGvREbBE5r4XgURjg43SMTcgORKbBBKOYRmvB2atFZPzbwQtxiS2CLLQavgtiq2YGceqWtsh60SEbYIfjAqQDBA7SE1JPaIl9piYOhgPDdhrjHZYdJUrMnZM63kgZfh51FNvXoMplQr07tKLkRdjTcgrrGWe5oN6Ch3s20MoYj7Zn3umDNqZD75tPvfQs19a9xVftwxwR%2Bin6N3Es8xkMkxgPsZIGBnTlzSDXNubBlZCG22MsCIEfwccEXZwh5mOokrHZ4dsBi3TKwHmSH8C8xOmZs4pEkDHLg4czDItToEe7Urkdo5WVPHDlPC4QYDvox1uRHlAA%3D%3D%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/duplicate/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/duplicate.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/duplicate.test.hpp)
