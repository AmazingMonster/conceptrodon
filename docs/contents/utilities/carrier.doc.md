<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Carrier`

## Description

`Carrier` accepts a list of sequences and returns a function.
When invoked by an operation, the function instantiates the operation with the sequences.

<pre><code>   Sequences...
-> Operation
-> Operation&lt;Sequences...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the sequences.

<pre><code>size() -> sizeof...(Sequences)</code></pre>

## Type Signature

```Haskell
Carrier ::   template<auto...> class...
          -> template<template<template<auto...> class...> class...>
```

## Structure

```C++
template<template<auto...> class...>
struct Carrier
{
    constexpr auto size() -> size_t;

    template<template<template<auto...> class...> class>
    alias Flow = RESULT;

    template<template<template<auto...> class...> class>
    using UniFlow = RESULT;
};
```

## Examples

- We will create a `Carrier` with sequences `int, int*, int**, int**`.
Then, we will transport the sequences to `Operation`.

```C++
template<auto...>
struct Sequence_0;

template<auto...>
struct Sequence_1;

template<auto...>
struct Sequence_2;

template<auto...>
struct Sequence_3;

template<template<auto...> class...>
struct Operation;

using PackedCarrier = Carrier
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

using SupposedResult = Operation
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

using Result = PackedCarrier::Flow<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Carrier`.

```C++
static_assert(PackedCarrier::size() == 4);
```

## Implementation

```C++
template<template<auto...> class...Sequences>
struct Carrier
{
    static constexpr size_t size()
    { return sizeof...(Sequences); }

    template<template<template<auto...> class...> class Stockroom>
    struct Detail { using type = Stockroom<Sequences...>; };

    template<template<template<auto...> class...> class...Stockrooms>
    using Flow = Detail<Stockrooms...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAGxcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAeHI3lgA1CYBbsjj6FhUJ9gmGgCCd/cEmCypBi8nbi9vH5hfTC8RAAdKCbod9kwFApQcChJgAI5eRibBQ3J7jYheByHNwtYh4eJPEwAdisD0OlMOs0cyAhAnGmFUqWI1LwAC9MAB9AhszkQJZPKnHMmHYiYAjrBh8zCoKiwiDwpEozAKQUBCwigAixIpVJ%2B7yYn1OBr%2BX1NRv%2Bp0BILBAWwEIM0Nh4Mh0MOTVQyAA1sRUKgWOi9ZTMdjeVqJUw6CLNV5MkZDgQAJ6pTDHAJaj1EH1%2BgNfJXIhiol32k6a0k6jW6%2B7Ci3G76vQ31utWvFA1Alh1umF2rtOntw7O%2B/0sNGl4OHOPhYCHABitFQAHd05mI806Pmh7nR52QCBk6my8SSZXyY8HgB6ABUN9vd/vF6e19vhwAKtghK%2BhIc74/L/eAN/asdj2A40y%2BNAi0wVICDHW4HieFsAXbTsMQILEcQLFUuQ0I8EIeJDrRQ3s0Iw3ksKgrkuDw89nkbM0iNtYEg3uUNMMRQtNi5MwaMQ%2BjLWQpiWLY8iOOwgJeII/jm2k1sbQ7XtHShAdhPQsNDgAeVTYgjWyST7mfG85zwYhxkObBVFYd40yA/D7inBNlCYH1MHcfFCVZE5MzxYgCSJBDTiFKkKK4jRSGOCcQu5FIIprYKxMosxwqCykoq5CSAtuKs7IcmchC8VIilcgAlVUvFoXkvM07TdIEYlAsihLQuSxrlUomKUo9JruSS2LhTSjLHlLbLaNyw5SoUcrKozQ4nJctzfI8vd5yXL4tPiWqGHREa0N05AuWU%2BICAgC49wUVhuShL4Jqm8L8sKjISrKiqbnVM8nzvLrIPQczLN%2BGzbz/WiaTwfbDtaCA5u9VyfL8hIQEyfklhXKrJDep4OBWWhOAAVl4PwOC0UhUE4NxrGsak1g2cCzACHhSAITRMZWb0QBxjRgTMMwAE4AA4NG5nHecSAJJDMElJESfROEkXgWAkDQwoJomSY4XgFBAMLGcJzHSDgWAYEQEA1gIVIgXISg0DeOh4kiC7OFUYWAFpEkkQ5gGQOkpE53hXMIEg8HQPR%2BEEEQxHYKQZEERQVHUHXSF0FJFx01JOB4LHcfxpnic4DSgTN3k5UOR3Ehdt2Pa9yROcOCAPGt%2BhPNprgll4bWtBWCAkCt1IbbICgIG73uQGAKQkpoCr4g1iAYmzmJwhaJM094OfmGIJMNJibRMAcJfSCtthBA0hhaEX%2BOsBiLxgDxWhaA17heCwFhDGAcQz5M7fHAAN1VbOmW3oEtj03CC8bG8daB4BiDpNeHgsDZ3QngeW99SDf2IDER6EYn5GHAUYJmKwqAGGAAoAAaoSRc60Cb0xDsIUQ4hI5UJjmobOid9DPxQOTSw%2BgIEa0gCsVAMFsh3ydhcLyphLDWDMCrFBBIsDcIFN0D%2B2QXAMHcJ4DoehQjhCGJUEYKQihZAEFMPwuiMj6IYPMYYCQxh1AUQIPokxVH5CsT0WxEwBiaIWDo2wrjDF6FmK0cx2jLErAUFTTYEgM4cDxqQZWvBVbF2dq7d2ntDjezMDXXA/tG50xbgzXBKwECYCYFgBIcjWaBGBNzAIEsNBi0lorHGiRubSw4LLUg8s6bAmSIkXmfMuCJBxpILgONKlSxiTnNWthNa5J1h3Q2ndjb53Nv3QeDc7ZsE4C0Fgn8SROyYEpBMXBubAi4MCImfsiDSODrIMOtDpD0KUIw%2BOugkrJyYKne%2BESoljNVnnU2QJDhF02ds3Z%2ByZyHOOacmudce4N2OLTMwOS2663mSs%2BIFsB4BhhSMIFOzIRGEOVwMK48XimUoDPeOK8F670pWvDeW8d5IP3owAgR8T7Z3Ppfa%2Bt9d6P2fq/Im%2BBxQODwN/O%2BZzVD/xeLvYBdRs7gMgQvGBWwibwMQfTFBaClAYL5dOXBfACHENIeQ3eVCbkRzubIBhccibPJYTg0RVgOHytkbw/hDJOBCIIOgER7CLASNiVIwOP8eHyOFc4CArgfEpA0eUCxeg9ENCjWkExDQAmLCcTYxo3iHFGNDQ0OxbjY2BN8dmvIua/GFq0em4JoSI6fKzvHOJOKQV4rBUck5Gh0n4AuXC7Jrc8mkAKUUkYcjQGtPaUcmpJJhkkhJKLMwktBnROzqrdWUykWzPgPMk2Bd0WouIGsrYmzEmjk/nST%2B4K/jjF9t2gOQcUimpoeaqO8gHnWp0CAIIrz3np2aV8ldudFmFyoIcY9btT3nsvZaMytdMW917QERFeqUVwYbnu1DIwz2FS5Be7mXIr0EAOsQFgrs%2BB0BJVPclRMaWn3pjRulH9d5MsPsfU%2BArMAXyvmIblSDeVYOVQ/d%2BwrRW/wlcgAB0rBCyrARAqBSYlVwIJGq3gGr0GvB1TgmZ%2BqmCEJIZgMhqYKG8EfeHCQFro5vqYZ%2Bu1xhfWcJiC64mbqGB3wvKdB14jJHxGkcGuRdhM1KJUWW9Ryi02eITdkJNEXSjuLjRmsNWb%2BhJv8wlgtYXLFeKSzmktcxYvFubqsdYYSCugP/Y2zgoHiMnoUGew4uHgQEa7Zk3tzd%2B0zPyYU4plAInjpADzYEAQAg43ZoMxWg2STdOXeViZGstYDrKUc2dGhDk1K4AEfpJIzADOaQEBtKtOBtfbhEswe3YkHemUd5Bk9FGSCAA%3D)

## Links

- [source code](../../../conceptrodon/carrier.hpp)
