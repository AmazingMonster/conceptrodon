<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Reverie`

<p style='text-align: right;'><a href="../utilities.md#reverie">To Index</a></p>

## Description

`Reverie` accepts a list of warehouses and returns a function.
When invoked by an operation, the function instantiates the operation with the warehouses.

<pre><code>   Warehouses...
-> Operation
-> Operation&lt;Warehouses...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the warehouses.

<pre><code>size() -> sizeof...(Warehouses)</code></pre>

## Type Signature

```Haskell
Reverie
 :: template<template<typename...> class...> class...
 -> template<template<template<template<typename...> class...> class...> class...>
```

## Structure

```C++
template<template<template<typename...> class...> class...>
struct Reverie
{
    static constexpr auto size() -> size_t;

    template<template<template<template<typename...> class...> class...> class>
    alias Snow = RESULT;
};
```

## Examples

- We will create a `Reverie` with warehouses `Warehouse_0, Warehouse_1, Warehouse_2, Warehouse_3`.
Then, we will transport the warehouses to `Operation`.

```C++
/**** Items ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<template<typename...> class...>
struct Warehouse_3;

/**** Operation ****/
template<template<template<typename...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedReverie = Reverie
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** Result ****/
using Result = PackedReverie::Snow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Reverie`.

```C++
static_assert(PackedReverie::size() == 4);
```

## Implementation

```C++
template<template<template<typename...> class...> class...Warehouses>
struct Reverie
{
    static constexpr size_t size()
    { return sizeof...(Warehouses); }

    template<template<template<template<typename...> class...> class...> class Sorrow>
    struct Detail { using type = Sorrow<Warehouses...>; };

    template<template<template<template<typename...> class...> class...> class...Sorrow>
    using Snow = Detail<Sorrow...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTyAJ7PZhsAB04tRt0hTAUCnFosl0tl8oA6q1MAh1koFKiQRNiF4HLcAEqYABu8Xe6MSViut3ttzmjmQUoEE0wqjSxEdeAAXpgAPoEH3%2BiDLEEOmE227ETAEDYMEOYVBUeUQNWxzVebXhgIWKP3emXSO8lncuGl/kVpl81nVzl19lCxisTDyxUGZUSgLYKWduXd3tKz5CEjEVAAd11dod%2BsNwceLToUfz2fCwFuBGbMIC91uo%2BI46ncIzGq1H3bPdh%2BZMiULeaLJZrZZ5z6r7LfjcrX%2BbIrbg77GUBwVHtAK7ECh37eUDyPadiwdNcjH3BhJx3PdFyYOg2RgydL2wEAQC3Z5r2te9bWBX5aSxak7gAMTwYgJlubBVFYYlMEpHEMSogEgXRMEIShDi2TQBgtjSAgdSvK5uLufEOU%2Bb4QW/csPwbVSiJbMUAOHPC9QIA0jVPLMlADDQSJkhlPw06zBWFVs8LA4C4LnIz1RMwMuAsijLhU191LsrT/wgpy9KuVzg2M88AzMbzlNs%2Btaw038HJ0qDB30wzIvc6KAjiyi7gAeWeYhyRyTi6SsgLEpfGr300v9HN0tKgLCy4ItuYr4jKgR8uuI5bmUJhkAAa0wdBbgANQ%2BOwKqBRCNyG0bxtNC1iHeNCTXNS1uRkuEIwdKLs0DDRSBhGd7SO0yuDOg7Lpy46Ytui7biuwM8r2tEH0s/q7iELw0mKFaPi8WhgyUq4Fv3AGgfQU0FFB4NYT3LrSsadF9pet6zOe%2BD7szaKbvOvHXoe0yzFxyNsY%2B4Er2%2Bny8XhxG5pBKGmbBzalrGuHtvW9gQCEFDjzcVGeoYXV6dkg5bgAFQ%2BcGqX0srkADID4gICBEQIhRW1VqS3HZggzv%2BwHMmBhGwdRXNyKlniTho6WhEwUSJpYtj6BZgq7ftosnTwFW1baCAueBtb3m1v1MDDNDkduSRrY4VZaE4ZJeD8DgtFIVBODcaxrEddZNmEsEeFIAhNET1YRpAZJJFFDQAA4zDMABOFuuGSRuG64RJEmkZOOEkXgWAkDRTvTzPs44XgFBAU7y4zxPSDgWAYEQEB1gINIvCNigIDQIk6HiSJW04VQG4ANgAWgvyRbmAZAXSkUUzF4cbCBIPB0D0fhBBEMR2BSBkIIRQKh1CL1ILoG6E5SppE4DwJOKc04VyzpwQqO9t7BhTLcc%2B19b730frcZ%2BZhbgQA8Ifeg3pzABC4MsXgC8tCrAgEgA%2BaQj5kD3qw9hIBgBSApjQMG8RZ4QBiCgmI4RWgCngbwcRzBiACkKjEbQzsF6lwPqSAghUGC0CkRArAMQvDADcGIWgs9uC8CwCwQwwBxB6IYiovAFozGZw9M7He2xS7hEZAPTOtA8AxFKvIjwWAUEGTwCPcxpA1oxDNo8KxRg/FGArqsKgBhgAKEmu8CcXV06l1/sIUQ4ggH5NAWoFBUD9DWJQHnSw%2Bh/Gz0gKsVAEkchmKvoiZGphLDWDMJPNa60sANLDD0BxzgICuGmH4G6oRwjDCqKMG6xRsgCEmXoJZjQFgjASDdOwoymiTHaJ4ToehdkOD6AczZ8ztm2AOasnZFzZmLAWasBQhctgSEQRwVOpAJ68Cnjgy%2BN874PyfnXEhEBcAfyoSXOhZdkmrAQJgJgWAEjDOroEUULcAh9w0JIMwkgL5j2SBfFu%2BhOBD1ICPGhooL5cAvg3Fu3cL61w7lii%2BPyUFTxnnPOFi8mFr2YRvDBO9yCUC4ZQk%2BbBOCtBYGaRIV8mCASQlwFuoouD1zfvgIgAyf6yH/kU6QJSlBlIgboCmMCmBwPMZ875vzUEcHQVvHetxsG4KBUqjcKq1X11IeQthlCYRgjMLChhS9BXiviKK/eqAKGjGlEYFVXBToCMZIxSgoiIGyMkdI0gWb5GKOUQ4HN6jGCaO0bozO%2BjDHGNoKYnNljrG2MrfYs5TiUGuOQO4nNXj6goL8QEyRwTtiZzCRE0u0TYlMkbeuZJfA0kZKyTknN%2BT9WAMNbIUp4DM5msqUkrpVhan9qGU0lpbpODtIIOgTpNSLC9L%2Bf0r%2BHx4AvPqHslwDB3BHIKNMj9lyliLMyMs3IX6pnpEAxsx5WyTmvrOQIfoUwQPQd6HBh5FQoP3IGHcm58xINXI%2BWsDY7zaFkq%2BcgiB/y3X4PjZ61V6qNCkMhdqwNNCQ3wtIIi5FoxhkDwpVS1VuKUgt17gEPFBLJA3TtVy2wPLQ38vgIKzemCo0RuIJK7YMr8EsAUGaF0ZovVlgmJqqFX9dV/0KWu4B8hjVbp0CAIIFqrUIJI7azlaDhVYKoDgzT2ndP6a5ExMhMb/XxGYwEVjfLl4sKC%2Bw5T0XKEgB04DAMemW4BgMwQAMqhb58DoKm4RGbM55t0aXIrBaVHFpjRorROiUFVqMSYsxpcG0JOHRYltjg20QI7V2yJPafG8H7YEgUQ7QnrTHbwCdSg4nTqSRF1JTB0mZMwNk4Uy69XmYkOukB1nyl2d3cYG9dSYjHqzqehgZidha33T0vp8QBlPsaSM2DfhxkfqwzMtDeGAMlByFh9ZOQ/0LKe40eDhz8igdOSD1Dcz/3YYQ%2BDk50OnnbJeW8wBNqyOT04F5u%2BWmdO3BS6KdLDGtUkGY7Q%2BhbGOMosoJ83jIBW6igCAEZIndxNj2Z4kelHLyOcG5fPNj6LkiYp7okMeDdJDty4E3Mw7KB4BEx38vnvLGGfNfjzrH08VeVyiUInI/ggA%3D%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/reverie/implementation.hpp)
- [Source code](../../../conceptrodon/reverie.hpp)
