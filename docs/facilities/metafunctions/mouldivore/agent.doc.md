<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::Agent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-agent">To Index</a></p>

## Description

`Mouldivore::Agent` accepts an operation and returns a function.
When invoked by a packed container, the function extracts the list of elements from the packed container and instantiates the operation with the list.

<pre><code>   Oper
-> Con&lt;Es...&gt;
-> Oper&lt;Es...&gt;</code></pre>

## Type Signature

```Haskell
Agent
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Agent
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will create an `Agent` of the `Operation` and invoke the returned function with `Capsule<int, int*, int**>`.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Operation ****/
template<typename...>
struct Operation;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Agent<Operation>::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = Metafunction<Capsule<int, int*, int**>>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Mouldivore::Agent` uses partial template specialization to extract elements from a packed container. Here is the entire implementation:

```C++
template<template<typename...> class Operation>
struct Agent
{
    template<typename>
    struct Detail {};

    template<template<typename...> class Container, typename...Elements>
    struct Detail<Container<Elements...>>
    { using type = Operation<Elements...>; };

    template<typename...Agreements>
    using Mold = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIJLSAA6oCoRODB7evgHBaRmOAuGRMSzxicm2mPbFDEIETMQEOT5%2BQTV1WY3NBKXRcQlJ0gpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMgTcwNBr0wEKhAE8UoxWJgAHQYiHYa7IAwKBTXADyyOIryyWMBY2IXgc13OwEYBEBJgA7FYLtdOddoY9YfCCEiUWwKRyuVSaQRrgARTBNOjXVlWFlSiHsgGizk8sFwyFavm6wXMNgYtFYnF4gkeF4RBKkbmG1Em7BPRkKEXnLnXcW0mVy2jwq1yyLEeHOkGuk0UwLYQGexXXLwZIz25EKwJSokkskCUMuwQKSPR1UK5Wq5ka7kg3ngg3Io3ojH04iYcP592exMRYDXACynnQaYzvqYdHhTZbzwIBcx0ZAIAFyLLF1ZKsCasB31%2Bh3%2Bm%2Bu2FUrEemHeJw3W7%2B5YBZkCEVxXiwabcaAYGxSU/dZ5ubiYKQUXnoJ57P8eo1oidaOjOMYXN6krfr%2B/46uuXwHJmCTZgwgE7MBVbavyDrGpBlIENStLEmh9RLuqlwoT2spMFQXgvm8HyAiBOpgUKDZoucxDAG6RYXJ2ya0U0DFMVkg50gygjwmRpIUbOIB9rQ6Bjrx06mkWa6XruQheCkhSYOgABKmB/rQkosYJSbdnpBnpEZpnmZKEIZnJ6HwhEBB2l5Ow%2BYIexRkh1E3E5/6Wae1ldtcYUWZJIn0YxDjkpCcHmexXn%2BQQfnXL5OxRjG2nLshNwACpmRFQFEWSyAAPpMPiCQEBAYzoHOCiovV/FuLF3nXHZhkmWZ4VYosqocMstCcP4vB%2BBwWikKgnBuNY1heqs6zHuYgQ8KQBCaBNywANYBJIaIaJIXAsoEGj%2BBoZgAGwPWYAAcL36Jwki8CwEgaBopBzQtS0cLwCggP9%2B3zRNpBwLAMCICAqwECkXjeRQEBoA8dAJFEqKcKoL0PQAtA9kjXMAyDINcUhomYvBGYQJB4G1XAyIIIhiOwUhs/IShqAdpC6KzADupIpJwPCTdNs0C8DhKoyjkqoFQ1wE8TpPk5T1NnWY1wQB4WP0MQCrXlwiy8JDWjLBASCYyk2NkOjdsOyAwBSGYfB0MCxBgxAsQC7EETNAiEu8IHzDEAihKxNomAOKHpCY5OhIMLQIdQ6QWCxF4wDfrQtBg9wvBYCwhjAOIGf4M2yUAG5mQLmCqHHqObLtXm1ALtB4LEpKRx4WAC8ReA/UXpB18QsQOTKpdGF3RgHcsVAGHxABqeCYMLZFzbt/Ds6I4jc7vvMqOoGdC/oZcoKtlj6N3YOQMsqBvlkhdE61rmmJY1hmED4/EMz9cH5dDjvUFwDB3CeHaHoMINp5jDFZoUTIAhJh%2BAQekJBDA5hDESKzOwICejjFaJAvIuDaj4IEL0FoWCKjwNsIQlBegZhUNgdgiQywFAbQ2Gwj6HAZoA1lpwVWhMSZkwplTGmusIC4EZsbbaZsLYL2WAgTATAsCJAgMdJIgQ0QAE5AgskkBdMwkgHp/X8A9HRPCvqkB%2BjtNED0uAPRejol6jj/CXX8Hoh6/CM7A1BuDPaC8YbwxtojBWqNyCUGdkbXGbBODNBYDXFkRMmDmjLtTHRaIuDnXpvgIg/8WY8w5gfaQR9FAnwFroD2osfyhylrwmWvjODy2Rqja4yshHqzJridJXBMnZI0HrA29sjYm0CGYc2gSobW1tqgQ2tonZzJGcMHpRg%2BlcH%2BjQCyCRfb%2BwzuHYOCcDmR2jrHeOo8k6MhTmnAWWcc55wLgnEuZcK4LSrvguuhcFqN2bsCBO7cpoZy7j3YO/dNgLSHiPXa49J5KGni8rsQSl5MFXuvTedYE5H2KVzUpshyn8zPiAD2Bh56fysDfYF98NGLWfgIV%2B790xku/r/BIBTAHUrwclZwEBXAMNZjAsorC0FFCyHy0giD6jUIWKQ7oFD6HENQcArlDRCFStoUwohuRFUarVTg9hnCub1L4YDXgwNOkiLScmPpWTzp62kfksZ8iplWyUSotRlB6nWNsZki6LJPEsmupIYxpNWYmsWpwfxEMgmwwRkjRWkSMZLIdrEzYCSNYsAUDXKmNdrXajGLkmRzM9BYv3jinm%2BLT4LV0MEGp4si5GsaUDZp4SlYq1UOmzN2bc2wjGEMpNoztqBEmZbaGoTokLKif24YWaDK1RzTo2qeaCC1XbaUr2OzKB7IWsc9Ou0d2nJAQnS5ghrnpzeZgbOucxCPNHs82e4Li54Gro4T5Dcm7IBbv8wQHcgXd17giMFg9/5Qt4DCqeIIEXz2mXwZeCg14by3pi2Q2KJC4sEBWypIBggkuMNfGwlL4CP1pQwQuWxWpXy/pYH%2Bpq/4AKpewshyqwEQK1dA8Buq9AStFQqzj6DJUsJoTgpV9RKGaqgTK8hKrZgCelXQvoYqdUyfgfqtYXCzY8ONQIjgqsO1ZuuPOtES67V5JII64dijSDKNUcMalgKvVEsyYEQI/g7qXT%2Bk5lkTifFNpBrYAJI7FiaMkP4XR/gXqPR0ZIHR119FcGw5wQIjbTURudYdHhdNvPJd8wF5Y48MjOEkEAA)

## Links

- [source code](../../../../conceptrodon/mouldivore/agent.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/agent.test.hpp)
