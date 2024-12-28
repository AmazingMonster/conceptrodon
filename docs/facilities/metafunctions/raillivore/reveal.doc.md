<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Reveal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-reveal">To Index</a></p>

## Description

`Raillivore::Reveal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and becomes its type result.
Overall, `Reveal` turns a `Typical` operation into its non-prefixed counterpart.

<pre><code>   Operation
-> using Mold&lt;***&gt; = Operation&lt;***&gt;::type</code></pre>

## Type Signature

```Haskell
Reveal
 :: template<template<auto...> class...> class...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Reveal
{
    template<template<auto...> class...>
    alias Rail = RESULT;
};
```

## Examples

We will reveal `Operation`.

```C++
/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Carrier ****/
template<template<auto...> class...>
struct Carrier;

/**** Operation ****/
template<template<auto...> class...Args>
struct Operation
{ using type = Carrier<Args...>; };

/**** SupposedResult ****/
using SupposedResult = Carrier<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = Reveal<Operation>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Raillivore::Reveal`:

```C++
template<template<template<auto...> class...> class Operation>
struct Reveal
{
    template<template<auto...> class...Sequences>
    using Rail = Operation<Sequences...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArADMpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHAD0AFTbO7t7%2BzvrJhoAgls7ANQAkixJ9GyCTDUXu0en5wefB28nxycEmFuBgBJnibgBQKemFB4MBdyhMKYXiIADo0aDsBdkAYFAo0SiMVicQoLgB5JLRJ4ZDF/YbELwOC4AJUwADdMGI/iYAOxWU4XAUXCHwkFg4XA6FgpGo9HxTHYpi4/FCTAARy8jFWChp/MFXjSRmZTDoF1BABEyRTiFSBDCVerNZg8bLsCAQAQAJ4U0F837cs0%2BrnvL6fH4fTYXbCqVh3TAvQ5/cMhhOnLlmeLBbFeLCmsFoBirJIEbVyoNnXYXM0%2BFgei4nYjAHyMYvx7Y/cUIqXI1D4nUnOkMggXe0AfQ0gdTpw7orc0p7LtpBHpjNHXAnvyncIliO7vdLpwHK7VI7M67%2B08ls93C4PS8Hw%2BP8TPwcus%2BIxDw0Vbm3bW87sMhGc5z3eViRAxdlyHN8P2iZ9y0uclKWeV5zz/GcLx3GUCTlIlFWdFF62AEtsAg%2B9EOtGouV5C59WCYAhS9ONzQuaDP2IGFCPwml4gsU1/Tg8Nhy8JI8kwdAWQULxaCHFDTlow0hGE0TxKdKSh2Y1jYLBUczFIB9VRHRJ9LHPTV2431EwrABZTB6ioLwC2QlN/jQy8MK7LDCQVJU0U4vt5Pomy7IchwMlzC0WXZTkwXIm0GD7N0mWNWgOIbLjSx4stBIktTvx%2BALmVU6TwouIKmHsxzqW049dOMozRw0UzjzXDKLJfbYLgAFSdGTnMmRxkBHPDogICBhnQN0FFYTAhpLNwcuk0ylNSMSFoIDE5nXDgFloThYl4PwOC0UhUE4NxrGsC4FCWFYmPTHhSAITRtoWABrOJJBRDQAA4zDMABOf6uFiH7vq4bluWkXaOEkXgWAkDRGsO47To4XgFBARqnqO7bSDgWAYEQEAlgIJJkXISg0FuOholCabOFUb6ADYAFomckC5gGQZALikFEzF4MTCBIPAJrafhBBEMR2CkGRBEUFR1Bx0hdDaAB3a0kk4Hgdr2g7npOzhSWRMmh1QKgLkZ1n2c57nec%2BswLggDxqfoYhTXuuZeGxrQFggJAqaSGmyAoCBA%2BDkBgCkXSaGk6IMYgCIDYiYIGg9bXeBT5hiA9UkIm0TAHAz0gqYeAhSQYWh0%2BVrAIi8YBZ1oWgMe4XgsBYQxgHEGu8GIQvHHZFvjswVRC%2BRNYHuCAFoeO2g8Aia0c48LADaXPB4db0h2WICIVrNQFO7noxnoWKgDCIgA1T81cQw6Hol4RRHEWWH4VtQDdV/RO5QC7LH0eeMaQAWKgIsGQW4s3GuaUwlhrBmBRtvD8WBAEQAWHYfuGQXAMHcJ4Fo/gsHTH6DENoeR0gCDGK0ZIqRSEMAIaUAYEwqjoIEF0UYODxjtCYbUEYPRgh9DoUQ2w3DyF6EmI0WhswuCoJuqsCQusOD7VIMjXgqNLbMzZhzLmPM%2BaOwgLgYW7tzDxEkd7E%2BCwEAciwDEFBpB3qSHiCif68RIYaEkGYSQTNEaxCZv9fQnBYakHhkYlETMuBM2%2Bv9MGTNYiSGBo4pmiiDao3RpjR6J88aE39sTE25NQ7hzdnTNgnAGgsFZNyFmTBcKGi4P9FEXAvqC3wEQRBegH5S2ftIV%2BSh37K10LpDWTAtatzkQopRhsODG1JsiC45tVHWw5gqKpNS6kaCdi7IObsPbxDMF7VJOM/YB1QK7aIFMw6HPWQMBZUcgaNVjgCYgCck7KyzmnYuzyc55wLkXTepdmwVyrgbWu9dG7N2Lu3Q%2Baxjr4D7qFQeBsR5jwBMXKeVQDZzwXmnZeELvYfg3g9beu8lD7w7kYI%2BoA9l8HPgoK%2BmAb4UjvrwVpT8ZYdNkG/JWx1elf2PtAqwf80XIOAaAgQ4DIHxDNDy2B8DoiIKdPAVBjDQrOAgK4YRbRAi8JmPQyh%2BQMiqu1dQ8RWq0GKq4d0PVxqagsJ4cUQhIihFsIoaI61fCJFSOWDIyRvj5H62Vioq26jKn0WqbUr6Ts9FNM2cY3ZvszEWIGNY6G/jAk1JcdyWI/0IbxFce4mJCTfWcGSVjNJ%2BMiYk1NicvJtN6YcGKTbFgChWQ81ZMGiUwwGn6NFi02QbTmVy3kF09lOgQCJH6YMnWXqRmJKNtks2FtVB1obU2ltUJhirLOcHTZ8Qdk%2B1xpkytIdKbrrdiARtIkRzNv%2BiOVtBARzzo6XQO5Dzk6pxzq8l9ud8792Lj8wQfzq6QswHXBuYgQWbzBSSrFpAoXoNhcreFyBx5IsECi5WaLF4ekxavHFxd8V7wPiSuiaSz5MEvtfW%2BxdGXSwkCy%2BWA6P7Dq5cYX%2BNh%2BVypOkKhgLd1jjR/jAywcDlEINFrKoBHCTWYOwdkCh6qbX8NyFQmoeqSE1ENQIi1nR7VSZEQqy13DVN2rNQ6gzYiNW2s9ddd1Mthk%2BpRpwS2C7G0XAvSia9YbGkkEjdu0xpBzFMEsZQORSaQAAxRPEeIsQQYxMRmF7kYS822bRrYFJO65hvRAJIWIDjwbckRt9SQQMuC/TMPE6G8QbPKILdGl6XqBbxYq4llLCxt5pGcJIIAA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/raillivore/reveal/implementation.hpp)
- [Source code](../../../../conceptrodon/raillivore/reveal.hpp)
- [Unit test](../../../../tests/unit/metafunctions/raillivore/reveal.test.hpp)
