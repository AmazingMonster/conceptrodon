<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AnyConditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-any-conditional">To Index</a></p>

## Description

`Typelivore::AnyConditional` accepts two elements and returns several functions.
Check out **Examples** for more details.
Overall, `AnyConditional` yields one of the two elements according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...||Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
AnyConditional
 :: typename...
 -> template<auto...>
```

```Haskell
AnyConditional
 :: typename...
 -> template<typename...>
```

```Haskell
AnyConditional
 :: typename... 
 -> template<typename...> class...
 -> template<typename...>
```

```Haskell
AnyConditional
 :: typename... 
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<typename, typename>
struct AnyConditional
{
    template<auto...>
    alias Page = RESULT;

    template<typename...>
    alias Mold = RESULT;

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see four examples that present different use cases of `Typelivore::AnyConditional`:

```C++
/**** Choices ****/
struct IfTrue;
struct IfFalse;

/**** Select ****/
using Select = AnyConditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if any of its arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 0>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value result of any of its arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 0>
    >, 
    IfFalse
>);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies any of the predicates;
otherwise, the function returns `IfFalse`.

```C++
/**** VoidInt ****/
struct VoidInt;

/**** Void Tester ****/
template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

/**** IntTester ****/
template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

/**** Tests ****/
static_assert(std::same_as<Metafunction<int>, IfTrue>);
static_assert(std::same_as<Metafunction<void>, IfTrue>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Metafunction<double>, IfFalse>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfFalse>);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies any of the predicates;
otherwise, the function returns `IfFalse`.

```C++
/**** NonpositiveTester ****/
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0 )
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

/**** Metafunction ****/
template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

/**** Tests ****/
static_assert(std::same_as<Metafunction_1<1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<-1>, IfTrue>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Metafunction_1<nullptr>, IfFalse>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfFalse>);
```

## Implementation

The implementation is straightforward.

```C++
template<typename IfTrue, typename IfFalse>
struct AnyConditional
{
    template<auto>
    struct Detail {};

    template<auto I>
    requires I
    struct Detail<I>
    { using type = IfTrue; };

    template<auto I>
    requires (!I)
    struct Detail<I>
    { using type = IfFalse; };

    /**** Page ****/
    template<auto...Agreements>
    using Page = Detail<(...||static_cast<bool>(Agreements))>::type;

    /**** Mold ****/
    template<typename...Elements>
    using Mold = Detail<(...||static_cast<bool>(Elements::value))>::type;

    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {
        template<typename...Elements>
        using Mold = Detail<(...||static_cast<bool>(Predicates<Elements...>::value))>::type;
    };

    /**** Road ****/
    template<template<typename...> class...Predicates>
    using Road = ProtoRoad<Predicates...>;
    
    template<template<auto...> class...Predicates>
    struct ProtoRail
    {
        template<auto...Variables>
        using Page = Detail<(...||static_cast<bool>(Predicates<Variables...>::value))>::type;
    };
    
    /**** Rail ****/
    template<template<auto...> class...Predicates>
    using Rail = ProtoRail<Predicates...>;
};
```

[Run this snippet on GodBolt.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGxmpK4AMngMmAByPgBGmMQSAOzSAA6oCoRODB7evgFBaRmOAmER0SxxCVzJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxSdIKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsKfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJgAzG4CABPFKMViYe5UAAqxC8mFINzhCOYbBRADExEoodggeMMQ4bhcGLCPAx8A0xECTIkrJcblycaCnm9MFC3EwvEQyUDuTdKV5qQARTDNOg3NlWRIyqEcwGc7kgsH8wXCoj3MVarnETAARy8eDNCiNJslBCpBBucoVtEFd2NFwlypuXgyRhx8ORUJlKPRmPVStV6tZ9p1fIh0INqCNkPJ9rNlutmFtEDAYDuS3F3KlsvlTDoHq9PvZfoDwCDCKVkLDdyoxNopMhFmjap7ce93J%2BuxuyiYwGRnxLXIT4IFyZFqAAdKuLsAzaDGAQFDXuf7wo3x5OW2HXZX3dCIKvl2y3HfZo5kAB9UTjQUxVCeMkQdebl47ksxbpiAIC4guGozjcI43AAsp46AfKcUFznq0LgfimA3tgzzbru6ZQQegbwbQiGhi6FZVleN53g%2BzRPq%2BTDvtCn7fumEA4VuggKKBABuYiYkBZKgeBsaXChvLzoKqFJjCwaYTR6Y3MgBgKAoN7KGa%2BCiCC%2BEZkOXJls6mmoEQABKqBMOgUHKlBEoyQucl4ki2G4dxe4SlyRGNiRZGthRbqCteq60YkbiPngL5vgQH5fpe2AQJpmDafy%2BFuJxAHqSFIEgPx3iYEJOWiQO9psv2kH2jBFlWUh%2BwAvZkloTCjWyRhLnZdgymqVly5JSlukefWh43NVflhiZ5mWdZ0J9ZFqWKeSJUGUq8YtY5Dn6kuC1dUxPWzTpuaDUZY7EKZqBmReNnsnZ2prZtRA3gAai0eBMDE9B6TdXkNmOE4hv555UW4wW3mFdFvJFjHMW4rHxYlWlzQN0LPcQr3vbmC18QJBXAdgInBmJy1lYTPqVYcI0XrVuz1bduqtXdi4PR1O1qRpCMHZ99reRTirkRN52XTN7PzR1hPE0tQIjn80sAjBhLWuMNzYKorBPFOyHfNLWt1YO5iQuEKleFgLZuGgDCbCkO5epL5NuAgqCRbmVMAsd7YRhBFKOtKzrtp23YVVc5NCHUmDUtOlzc8H9SnjSdIMkyWQstCbsYliRIkgui0BzBqK5juzuexDL67fEBAQOM6CgQoSLPkxgpR6HBCgcejlcNiZhktiKeRumwEahFxdqaX5cEJXIDV2wtdpQ3DjN39goaO3nfhqnZJ94XDEl60I9jxPmBT/XIezyALcL9iGjL77Gdr2Lmva1rstB6HAiIcrqv0AXd/338AIb5DW9lwrlXGuddxLQigjPJuIBfI2XAfaCUQCQDhBBBuMQr4BCzEEIKZB2IuDLy%2Bg6MeyDMCoNoOghgmCYrQhwTcDuBFSrpmxFBbuAowHYHXuJS4A8p5KG3ogveB8wH3ntJA0CMCGHCOWgg0eoFiGkPIZQ7Bghz74PgaWGRSDBAkOIGgs2ijqHKNoYNVRy0WGsl7rfC43CAE72AZPUBgI4HLVEdAhCsDJGeXUUQrR8i9HNCwQYggKjGErSkV42RPidFkL8YYKhbgaEX3oUTEJzCOzXzYRwzUgdv6/EfrcVECBrSvxVmCdWOsv45KOL/CpNxHoO3QHcQQn8rFe2pHUvADSAnZ3Ju0xCudxjxGaRtdC8l2q3iScdXp/SQQJBuCkLw71IqENAlQDOz5wLRhVOVQcwz7wTNac6KZed4iCl4vU4ScyFm0CWYgr2%2B8Nm2RjBLS4uyvSTPqdMk5yN6mNKoXjS5izkDLLAqndZwZNni26bcX5nziBDIZk5REbAFqeydPcQQsKQAAuuUCxBqyuz3PBY87ZnDgQIreQc9FBBYVKL%2BVi%2BZgLgV3LBc2YlljXn7LRTC45xBBS9N%2BRchlOKmWgoeddJ5UL9hwQrFQLw5t3jhzJXTdaozkVrmIMATmFxuawRlXKhwWQY6QKBKBUafKPk8q7hinlXoxFuOhBcDVPUxTPOyVK6ZtpFXWKHnwjRAi67Ql1c0WV8qsi0svmiVeFilret4YAv1IC0pBqYCGg1AhTnnJCWY6N/d6L/x9fG3eibBTJtTQ0c1HSBVZsjT3dhhNY3D34cWwNerQ3puhOgNY6MI1%2B0zpkhtvqi32OnkfKBZrwE5RgRO7AXc0kEpvq6qWlSNZutHISNYrQEBKxKWrZpS7l3U0HDBSIAhCiZF4pgWF8LlX3RXKLLhlKT0MDPY4C9mLsU3I0fipQLKQzipJVk3ZKY0z6SzFaG0NwIB3BNuRDQNxiwPrRU%2Bl9eA302uToKq5n6x7MrFVs9lCKUwosQ97G4T6IjAAhmhgZsyhXYZWWsvDkKdmEaXCBoEYGcx5jg4KciRZUWkfIyQqjl70NuE9CBD9uKNG4aJf%2ByxMFS36oVSuoDW11Waq9Dq1taaGDPi4Ea0dJqQAXSBsh9I57RM0exEJyjr6rMzNtSfeeDqnUosXeTD1zSB2FrsfvANbglNtr03g6EoWZ0r1rf2vNg8422PHs2wLOmGj6cFAAWnC7O92C7c1Fx4Y2hNw6S3JayKl6EiSIvZrrTGmL%2BXB1%2BYPi24NynSuhbcAwLwtBaCW15dW3tOW/6xYK0O/zI76imsFnsvGznJy8b69fHNHAVi0E4AAVl4H4DgWhSCoE4PeSw1hJQbs2EqMwkIeCkCbltpbKwADWIBVuSGXBoAAHGYMwABOD7XBVuvZe9UGoK2OCSF4CwCQGhF6be27tjgvAeKLyu1oFYcBYAwEQCANYBB5lBIoBANAjw6DxEiEiTgqgXv%2BDS/4SQNxgDICBVIZcZheDJUICQDpeh%2BCCBEGIdgUgZCCEUCodQ13SC6DbgAdx0SkTgPBltrY25oXgMOADyIpsc3FQFQG4ZOKdU5p3Tm4DOzCQY8AT%2BgcK9ZcCWLwRHS3SAQCQPjlIhOyC46dy7kAwApBBBoLQGZPEIAxEV6QGI4QWiwhl7wUPzBiCwmVzEbQjdI%2BkHxwBZXDBaAR5F1gGIXhgBCi6zxbgvAsAsEMMAcQ2ecwGovUX7bmBVChxFFsC7xCgfbeuTEHRsePBYGD46PAYPi%2BkAvcQT8Sg5Rl6MNcowiuVhUAMJqx6eBMDi%2BV3iZPnPhCiHEHzrfgu1DB7F/ocvKBrDWH0HgGIPFIArFQJbLIRe0sV1DKYA7lgzDQ9H6jLAN%2BIArDsEbiyBcEZCmD8DblCHCCGAqBGDbhQwEDAL0HgIYHmGGCqG6CAIED6EmE8A6D0EAN02wIGCgIWFgNsAmDaFwLyDblmFaFQJgKqAAOO15zlw4HW1IChyV04G13J0p2p1p3pye2Nw4iZBIFO3O2t0uznxWAQEwCshGH/1IHu0kEhGXA%2B0hGSA0EkDMEkH8Ah1W38A%2B30E4BB1IDB3O2XH8C4H8Bew%2B3%2B38Eex%2B3UP8A4ODxhzhxAARzn3tzRwdwxzVxFHIEoHd3N2JzYE4BaBYF4kSDSyYB2kDC4A%2B2XC4Ge2Z1EJ/w51kG5132kH3yUEPxF10CCElyYGl2L1YPYM4J204FVyxxFA1y1x1z4PiMbESOSOexN1QDN0GT1jMEkNt2R0dy6Od3NyCLx2GI9xUnL0SK4EXl9390oCDxF2j3D2TxWNj3j0T1nmH1T23HT0z2DxzzzwLy7GT1L3L0r223wDNBr1zGDwbybxBGTzb2D07273pAwC2G2wHyHwu1H3H0wEnwuMPG8IXwnAUGX1X3X0YE3yyJ3151yNkAP2F22yKJP1nzfysEsEv2v3gDvwfwwU4Gf1Hlf3Pw/y/3iB/zuNvwwN0xAPcCoPAOCEZHoMWDgIswaEQPZKKCyFZLIIIIaCIK5NpMFIoL5PQNoMoNyCZMlPFIkCYPWE2HlOMLYIVxFxhx4N12pymISKSJSLgxENZwtzOytxt2kNIFkPkISEUKB1MPMKSK0MSFWw%2B0SESEhG0N0MkDbiqPcNsE8KkOu2R18KQEx2xzGJCKJxJw4EiL1xYAUF4iBV4jaPnHGDSKNPZzbi32yIRP53kHyJRJ0BAEhFIBKLKNlxVMqLcJqICOdE1211jPjMTOTNSmdAgFNxGJ6LO0hH6O8L8IjNd2CImPN1ymQBSBSGfCTI%2B2fBTIIGfFUCpz4DoAWMD2D3WKzwuzXM2KTx2K6LTwzyzyuMwFz3zzEFOOH3OOny%2BJL2r3szr2Z0b2QGb2eK0Xb14DePD17yvMu1Rl%2BN4H%2BPSEBNBGBNn0DL4EXwhJXzXw32HyzPhIkERIF3zKPyLPROMDJJsE7z/3xIaCL22CAUxOsE/yV2/w6WpMUIFOAIgFcGFMgLKDQKQI5KyGFOQLlJoNHV6AoOFIoqwLFJIPopoM4sZPwN4rooYOVIUGYOVKB0rPVO4PnOpzjITJuEnOXBnMg1wCNPENNIDKRxkLkKwGtNYLtJAE%2B2XEhEhFW1%2By9Ih3MsSBsNcNkthz9K8MDLuxAEkFWzUIBwhxe0kG%2By4DezMBcKB0hDVOh04DNNcpVKZwcvCqcoGJWFHwyGcEkCAA)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/any_conditional.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/any_conditional.test.hpp)
