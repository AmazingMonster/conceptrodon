<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ExtendBack`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-extend-back">To Index</a></p>

## Description

`Omennivore::ExtendBack` accepts a packed vessel and returns a function. When invoked, the function appends its arguments to the back of the packed vessel.

<pre><code>   Vessel&lt;Items...&gt;
-> Args...
-> Vessel&lt;Items..., Args...&gt;</code></pre>

The returned function also handles `std::integer_sequence`.
The arguments are cast to match the value type of the packed `std::integer_sequence`.

<pre><code>   std::integer_sequence&lt;Type, Integers...&gt;
-> Args...
-> std::integer_sequence&lt;Type, Integers..., Args...&gt;</code></pre>

## Type Signature

```Haskell
--Extend a packed `Mold`
ExtendBack
 :: typename...
 -> template<typename...>

--Extend a packed `Page`
ExtendBack
 :: typename...
 -> template<auto...>

--Extend a packed `Road`
ExtendBack
 :: typename...
 -> template<template<typename...> class...>

--Extend a packed `Rail`
ExtendBack
 :: typename...
 -> template<template<auto...> class...>

--Extend a packed `Flow`
ExtendBack
 :: typename...
 -> template<template<template<typename...> class...> class...>

--Extend a packed `Sail`
ExtendBack
 :: typename...
 -> template<template<template<auto...> class...> class...>

--Extend a packed `Snow`
ExtendBack
 :: typename...
 -> template<template<template<template<typename...> class...> class...> class...>

--Extend a packed `Hail`
ExtendBack
 :: typename...
 -> template<template<template<template<auto...> class...> class...> class...>

--Extend a packed `Cool`
ExtendBack
 :: typename...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>

--Extend a packed `Calm`
ExtendBack
 :: typename...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>

--Extend a packed `Grit`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>

--Extend a packed `Will`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>

--Extend a packed `Glow`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>

--Extend a packed `Dawn`
ExtendBack
 :: typename...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
template<typename>
struct ExtendBack
{
    template<typename...>
    alias Mold = RESULT:
};

template<typename>
struct ExtendBack
{
    template<auto...>
    alias Page = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<typename...> class...>
    alias Road = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<auto...> class...>
    alias Rail = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<typename...> class...> class...>
    alias Flow = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<auto...> class...> class...>
    alias Sail = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<typename...> class...> class...> class...>
    alias Snow = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<auto...> class...> class...> class...>
    alias Hail = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<typename...> class...> class...> class...> class...>
    alias Cool = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<auto...> class...> class...> class...> class...>
    alias Calm = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
    alias Grit = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
    alias Will = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
    alias Glow = RESULT:
};

template<typename>
struct ExtendBack
{
    template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
    alias Dawn = RESULT:
};
```

## Example

We will append `void, void*` to the back of `Capsule<int, int*>`.

```C++
template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = ExtendBack<Capsule<int, int*>>
::Mold<Args...>;

using SupposedResult = Capsule<int, int*, void, void*>;

using Result = Metafunction<void, void*>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement the case where we append elements to a packed container.

```C++
template<typename>
struct ExtendBack {};

template
<
    template<typename...> class Container,
    typename...PreexistingElements
>
struct ExtendBack<Container<PreexistingElements...>>
{
    template<typename...NewElements>
    using Mold = Container<PreexistingElements..., NewElements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCcpK4AMngMmAByPgBGmMT%2BAKykAA6oCoRODB7evv5BaRmOAmER0SxxCWbJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG4EAJ4pjKyYp9gmGgCCs8ReDgDU2Kp7DOgWTGQAGsPiYAOxWMEAEVOVmejyeewORzu8LOCI%2BmI%2BSMOTGOZ0u12YbAAdGT7h9kAYFAoPh5BEwFmQMVjCTdSWTlMRMJhVHhZuFgNh6GxBAoEfcEa93gQvj9XADgac3PSmkzlVyeXyBUZhftGAQFGSSZKTg94RCWZicSjlWziZhjZFMAB3PWiw2S55Yj5eDJGD4AWU86FBJyhdNkjIixA13N5/McupFBqNZNIH2dbpTYuNprhT3BMJOBYRAHoAFRV6s12tl8s1j4AFUws1pNfrz0rtZ71c7hfhZhO4SpXiwYbcaAY2xSnrNEueNrxdwJV3ZjvJ8%2Be0s%2BbiYKQUXnosIXiP2uPx5zXDuNT2IwHFW6efsFQcwTSoXmnvTDEe%2Bv3%2BQEgWVPcDyPFc3HCAgMygitTXNJ4QBAYNaHQZU7wfPN5xLU8XwDIQvBSQpMHQAAlVsj1lU4I1Aw9jzOKCYMECsMwAN1QPB0DYjj0Dg7DS2ePDgA%2Bci6Ko8M3w/L96gEZV2M47jOL4h4cPhbcmkcZAAH0mBpeICAgWZ0CQhRbh0x83FEyiMwIoj0hIqzaAIe4VlhDg1loThEl4PwOC0UhUE4NxrGsD4FA2LZMFBIceFIAhNHctYgRARIzBJMEzEkAAOLLEg0AJUo0AA2LKTn0ThJF4FgJA0DRSF8/zAo4XgFBAOr4r89zSDgWAYEQEANgIFIvGgigIDQA46HiSJbk4VQsqKgBaIrJA%2BYBkGQD4pBJMxeBIwgSE4vR%2BEEEQxHYKQZEERQVHUTrSF0LhSBdYh904HgPK8nyEoCzgAHkRuG2VUCoD55qWla1o2rbJB2j4IA8Sb6GIaKTi4FZeA6rQ1ggJAJpSKayDG/HCZAYApDMPg6D2YhWogGIfpicJmgud7eCZ5hiAuP6Ym0OoOtiiaPT%2BhhaFZ%2B6sBiLxgD3WhaFa7heCwFhDGAcQJbwbl6lY1sft5OoRp2WKoO6H7aDwGJXq5jwsB%2BghiDwarFdIHXiBieyoX2VXzaMBK1ioAwHwANTwV0/qJNmruEURxEuk75CUNQfse/RVZQELLH0C3WsgNZUFnLIFcWozqNMSxrDMRrXYdrAc4gNZahkvwIFcKY/Ce0IFnKSo9EKTIBDb3v0n7hghm70Ynsb3p%2BkmTx2j0KeGjmMeRgSSe5kH9eBhXpY14biLtgkT6OG8%2BqfqasGFuW1b1s27azHh3ADpR8w0YxuK/bWBBMCYLAEnr0gyVJAnBJAEE4YJJAaEkJlIqtVEhFSCJ5DglVSDVTRiSIqXASoBCylgxIkguCJDAUVM%2B90motTah/TqOM%2Bq4wGoDEa5BKAk2RjNNgnBmgsFYmCRaTBKQGADFwAIJIuAkn8vtIgNdjqyDOrHaQ8cbpJ3uroSmL03qK2PqfBqvAmoAyGiND4IMPicO4bw/hqstrCNERoeGiMCbI1RmYd%2BWMup0JYfEJh41UBI1GCYnhVJVZCK4HVGgTl4h0wZvdDmLNI7RK5jzPmDhI5CwNCLMWP1JbS1lvLSOytvY7H8vgLWjgdYK3EaoA2exI4myQf5c2lsWY2wKZjB2TtYqu3dkoT2KsjA%2B1ANQvggcFAhzDhHZ28dZEXXkbIRRd1/IqNTr7MuVhM71LrnnAuAgi4l3DMsiuVd4g111rnLoPQsguD%2BJvYIfwd49yen3XoVyHlZFuRPU5/Ml4DCuYvAQM95hlFXgvDec88hbxaK8ve6xNiH3RuVE%2B30yGcGMcQLhPC%2BEBMEVYsRj98CSNRujTGn9SDf1/qMABSCUFoOEVAsERCwRghONAyQK0nraN%2Bs1WwlCXE0PgHQwaQNPHuOIGwnYnDIYsAUKxTarEhEkhRLMPauLDrGSehMmOUyo6zOTiAMqaiUhs00Qixq/0GHA1BmK1aEqpUfBlcI%2BVsoEbePsfEVGJxnF%2B26njJ1hNBXeuRiAKVREtK2q0vanSKKVpUzCbTSgkT/JxPFrFBNCT%2BbJO8cLUW4tCmYCljLMQOTnZ5N6c00gRSPmlL1hU5AhtqmCFNvdepVsLhNLtq0yOHSPZe16YKD1AcmDB1Di6cOjBI5qvOhIaZ11E5zJ0DqxZxgM42DWfADZvQFZliMunculhK46OrpxY5ACfnN1biC9u1z0AQqHkULITzh69CvZPboHzfnAtyOe49fzH3jC%2BWeoF28u6AtheFaFF1DWkONRwZFLBxWSulbK%2B1OLn74vddQr%2BP8/6UGPpS/IJITgnESHlAhtV8NghKhBnRnAKHtSJUAsEO1aVcCkAEGlYCuBgjhScI1lGOXcuPrtCj7LCVoZduE85kggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/omennivore/extend_back.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/extend_back.test.hpp)
