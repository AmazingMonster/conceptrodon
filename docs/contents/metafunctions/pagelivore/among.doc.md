<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::Among`

## Description

`Pagelivore::Among` accepts a list of sequences. Its first layer accepts an index and returns a function.
When invoked, the function instantiates the sequence at the index from the list with the arguments and returns the result.

<pre><code>   ...Sequence<sub><i>i</i></sub>...
-> I
-> Variables...
-> Sequence&lt;Variables...&gt;</code></pre>

## Type Signature

```Haskell
Among ::   template<auto...> class...
        -> auto...
        -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct Among
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will pick the sequence at index `3` out of the list `Shuttle_0, Shuttle_1, Shuttle_2, Shuttle_3`.

```C++
template<auto...>
struct Shuttle_0;

template<auto...>
struct Shuttle_1;

template<auto...>
struct Shuttle_2;

template<auto...>
struct Shuttle_3;

template<auto...Args>
using Metafunction
= Among<Shuttle_0, Shuttle_1, Shuttle_2, Shuttle_3>
::Page<Args...>

using SupposedResult = Shuttle_3<0, 1, 2>;

using Result = Metafunction<3>::Page<0, 1, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

Note that we must instantiate the sequence before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual sequence in the list.
It is not quite the same as the actual sequence.

```C++
template<template<auto...> class...>
struct Carrier;

// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Carrier<Metafunction<3>:: Page,
    Carrier<Shuttle_3>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Carrier<Metafunction<3>:: Page,
    Carrier<Shuttle_3>
>);
```

However, after instantiation, both of them will converge to the same result.

## Implementation

We will implement `Among` using recursion over the requested index.

- **Base Case:** Handle several small indices directly.
- **Recursive Case:** If the index is small enough, the sequence at the index is returned. Otherwise:
  1. Drop several sequences from the front;
  2. Reduce the requested index by the same amount;
  3. Invoke `Among` by the rest of the list and the first layer by the reduced index.

A simplified version will be as follows:

```C++
template<template<auto...> class...Sequences>
struct Among {};

template<template<auto...> class First>
struct Among<First>
{
    template<size_t I>
    struct ProtoPage {};

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct ProtoPage 
    {
        template<auto...Agreements>
        using Page = Among<Others...>
        ::template ProtoPage<I - 2>
        ::template Page<Agreements...>;
    };

    template<size_t I>
    requires (I==0)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = First<Agreements...>;
    };

    template<size_t I>
    requires (I==1)
    struct ProtoPage<I>
    {
        template<auto...Agreements>
        using Page = Second<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIaa4AMngMmAByPgBGmMQSGgCspAAOqAqETgwe3r56KWmOAsGhESzRsQCcAGy2mPYFDEIETMQEWT5%2B0naYDhmNzQRF4VExcYkKTS1tOVy2EwMhQ6UjVQCUtqhexMjsHOYAzCHI3lgA1CZ7bsjj6FhU59gmGgCCj08EmCxJBu/nbu%2Bf30wvyYXiIADoIfcTkcmAoFBCwUJMABHLyMbYKe6vcbELwOE5PFgCYBnADsVlJABFzlZnq9/l8mD8LgzAcDQagEVCYXCTgAxPDEcZY544vEEAlEoy/AVCggil7k14nFUnVlMoEXNIAL0wAH0JQBJBWqk5i/HKYioIjKJjATBkinUva0l7PU3q5luHX6o0m1XEFFeQWYBQnCDGvbOykaFbK1XmiWW62oW3236Rh7u1UmJXZ00qz2atwg8EQp7AQMfRgETF7LNPAuqrxpIwnNMO86U/mC4UXCtVtiCeGQ%2Bs0%2BMq3PO10TtUfRle0uc8uVzDV4f%2BlUtkIkjtnKPtq02u3Fgdroe1rljl2vKfjunPIu3i6zp8XJdX7DQgy82XjUivvObLvhyn7frCYZImgDDoAB%2BZzgCGrsmWYLcj%2BI5ggA8gQCAxJidJjqKBC4vihLEjKvYEKQJxQQIsEnNhuFCp%2Bt55o2qpvt6eC6gaJyZrOiaHime6zrmrpNoWQFISBKFnuutabgW25tiJB5kdKFyMXhLHwaaIAgEWQnHumFyGicAC0JxmIpekGVJ7ztievxyReGFYje8F3h5brsZJiFej6vH8fBgaoiGYYRl2XaxgJxHikZqZOaZilibOHr2cWH4roONZ1g2EknMpu4nvu3Z/vK/arvJbnXuJOZUvePnpf5xaBX6hG%2BScoXBoGEWRtGXBxvBgnJsZxbBZ1qW6RxGXIcuYIublNnNq2xX2qVNHdHRzlVa5LHeaaXkzvBnFZQtu1LR1ppFY561dglHY7Tlw77TODXea8AD0ABUv1/f9n1fX9AAq2BCMDf2A88P3/bDUM%2BfshzHJ2FzQdsSQKR19KzTJ80KoJQgIKCBD0HqGiNdjLVzTpTwE0TBAk/qXAU4%2BOMlqBo4NnTxOk9ZH2s1TuM09zDOk3sLNvGzZ1PMQwB5a8N0ALKYE0VBeAwPQCM%2B3bqcAvyEzz%2BoaNRBui0zJv04zepmBbht6uLHX6Y9/ayzVDz808N1CF4SR5Jg6AAEqhl4tASvdptWw7bjGycMxWe5x2e6tJxBwoIdhweyuq%2BrmsML8DvYE7SXR9Rcd8%2B7ifjEyeDIHqEExAQEDXPpCisPqsK/Kn6cmz7fuB8Hof3HGHucadHOofW4FwsLcX4iWxDEHgMQS59n0nAA4m4bjQqgnx0KGqHQ2vbgGG2hjoCcitCAAatvVBMHQh%2B000ji1/XLRNwQ6At23dd1m4s556L2XhcLOTA1Ya3qPne4%2BlbqYDgp1IBS9iD60tmLBUQ8V7H1PiSc%2Bl8b7bzQHvegT9V4by3ice%2BdB4TYhfjXP%2BSgP4MGtGaL%2BP82B/1%2BIA5owCUGgJVuAnOUCLgF1gR2BBpokEgLcBHdBWN6zD1dBwNYtBODxF4H4DgWhSCoE4AAyw1gzQbC2J2MweweCkAIJoZRawADWIB4iSDBBoSQXBSR7ASBoMwlRKhmAABx%2BP0JwSQvAWBxGNpo7RuiOC8AUCAY2VitHKNIHAWAMBEAgA2AQJIoJyCUCIUkfexAwht04KoPxlRzKVEkCcYAyBkCxycWYXg/tCAkDwN/GY/BBAiDEOwKQMhBCKBUOoJJpBdAzAAO7ECYEkTgPAVFqI0dYnRnBMKghyRKVAVATjlMqdU2p9TGlgjMOGDwxCYhnDMYNXgiStBrAgEgApRS8kQGefQWIwApA2xoKHPClBIgrMiCEZoABPeZvBgXMGIKCzCkRtDdESRYohF5MIMFoOCsZWBIheGACWWgtA4ncF4FgFghhgDiCxSGHoAA3UMKzMCqG6KCHYFiQjvFUWM2geBIgzJhR4LAKziJ4DCcS0gdLiCRFSJgSkHxyXcqMNYtYVADBy2vkvSZmEkiMAhYM4QohxADO6fIJQagVkTP0OSlA1hrD6B5XEyAaxUAYwyES8y1wuymAMZYMwUSJWLywA6iAawui5xcDBKYfgZhBAWCUMouRUjpAEJGhN%2BQMiDDjSMGYob6h9EmJ4doegc29DmBm4YsRs1zBTZW/oZalgVpDcY7YEhFkcHUaQSJvBom7IqVUmpdSGlSBOeGXAbTiBXPMSsW5Sq1i4SYFgWIwbSD2MkHsME5Q9ikkkC4swkhKgaASJUcoQSOAhNIGE8xYJKhcEqH48ofib2OK4PEDd1RO2rJibYeJlilUpPSY8zJGzckUDebvQpHySlsE4M0FgNLSTmSYOBNsXByhgi4M4lp%2BAiABr0Ma3phrpDGuGWasZugbbTNmRC1t7b33RPWdk0EJxtknBg3BhDSGSQobQ84s5YGikTrMFOn9SSHlPL4x8157yRisfgzCIwKGuDG1%2Be8IUAKgUgphbqqFYK4UIocLqlFNY0UYpWdi3F%2BLCW6tJfKnY2j8CBlpfSsZjLmXvF1ey2oKzuW8rBQK2ztzF6iosRKqVShZVkqMAq0AIm%2BCqoUOqzAmrtWaIsXhg1/TCOyGI6M7RZHLWKq9VYSwdrIhBqdS6gQbqPVRkK9YX1Xb/UdPpY6modQMjhvcAW6YpAY3FHLampNmQutRuSIm%2Bodb43ZtqIikt/Rq2tZmwIPN8w%2Bv1qLVW4b63a2xv64NdYmxm17c5TRlZ3aZPsbk5x1D6GNAjqwyQCdNzhP3NnZgedIwl2crPRe1DLjSQvtJO4yQu7qkzFo5wWJ367nJNSRkrJmzJPiZiJBnYMGDksAUDShpNKuOAnGJhsdHTcOyHwxlvV2XzUgD2KQCjcziXUeWWMujQGtk7LRzUjHWOTg49Q3jiUEBzngcufsPYQnoeiZQEjsgIGpOxCx77PUPO9R87rsQFg1S%2BB0BU3EiAgKxnac02Kg3sL4WIoM7vVF6LMV2cwDivFYhLNius5F/zpB7MzbpUS7RLnkAsvc4ITzXKeV8tBX5oVgXdUheleF%2BVO5f0qrtPFjVWqdVirS30iQmWhmmpyzoKn%2BXjA2uK95srOiKsMCJZ9ZutWfV%2BpiAG5rS7i3OAgK4ebvXFiTdG2m5Nm2Zh5EGxNrNC3c7Lfm83hopadtrZrfm7II2q4tCHw2/bJiW0npO0zzgLG1fo8x9j3HGpxh3bHY9sXM7SBzoXZQVt32QBmFQ3sPY8R4guMUxoJ/pJb0dtOxDr9CSL8V14h114g/FvFyhJByh3FN0uBqdOU9hGcok/9xdW1mkf8t9P0UDxU8J2tJAgA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/among.test.hpp)
