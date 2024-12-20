<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-among">To Index</a></p>

## Description

`Omennivore::Among` accepts a packed vessel.

- Suppose the vessel is a container containing elements. In that case, It returns a function. When invoked by an index, the function returns the element at the index.

<pre><code>   Container&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;
-> I
-> E<sub>I</sub></code></pre>

- Suppose the vessel is a sequence containing variables. In that case, It returns a function. When invoked by an index, the function returns the variable at the index via the member `value`.

<pre><code>   Sequence&lt;O<sub>0</sub>, O<sub>1</sub>, ..., O<sub>I</sub>, ..., O<sub>n</sub>&gt;
-> I
-> O<sub>I</sub></code></pre>

- Suppose the vessel contains operations. In that case, its first layer accepts an index and returns a function. When invoked, the function instantiates the operation at the index with its arguments and returns the result.

<pre><code>   Vessel&lt;O<sub>0</sub>, O<sub>1</sub>, ..., O<sub>I</sub>, ..., O<sub>n</sub>&gt;
-> I
-> Args...
-> O<sub>I</sub>&lt;Args...&gt;</code></pre>

## Type Signature

```Haskell
-- Pick a `type`
Among
 :: typename...
 -> template<auto...>
 
-- Pick a `value`
Among
 :: auto...
 -> auto...
 -> auto
 
-- Pick a `Mold`
Among
 :: template<typename...> class...
 -> auto...
 -> template<typename...>
 
-- Pick a `Page`
Among
 :: template<typename...> class...
 -> auto...
 -> template<auto...>
 
-- Pick a `Road`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<typename...> class...>
 
-- Pick a `Rail`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<auto...> class...>
 
-- Pick a `Flow`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<typename...> class...> class...>
 
-- Pick a `Sail`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<auto...> class...> class...>
 
-- Pick a `Snow`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<typename...> class...> class...> class...>
 
-- Pick a `Hail`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<auto...> class...> class...> class...>
 
-- Pick a `Cool`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<typename...> class...> class...> class...> class...>
 
-- Pick a `Calm`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
 
-- Pick a `Grit`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
 
-- Pick a `Will`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
 
-- Pick a `Glow`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
 
-- Pick a `Dawn`
Among
 :: template<typename...> class...
 -> auto...
 -> template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
```

## Structure

```C++
// Pick a `type`
template<typename>
struct Among
{
    template<size_t>
    alias Page = RESULT;
};

// Pick a `value`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};

// Pick a `Mold`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<typename...>
        alias Mold = RESULT;
    };
};

// Pick a `Page`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};

// Pick a `Road`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<typename...> class...>
        alias Road = RESULT;
    };
};

// Pick a `Rail`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<auto...> class...>
        alias Rail = RESULT;
    };
};

// Pick a `Flow`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<typename...> class...> class...>
        alias Flow = RESULT;
    };
};

// Pick a `Sail`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<auto...> class...> class...>
        alias Sail = RESULT;
    };
};

// Pick a `Snow`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<typename...> class...> class...> class...>
        alias Snow = RESULT;
    };
};

// Pick a `Hail`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<auto...> class...> class...> class...>
        alias Hail = RESULT;
    };
};

// Pick a `Cool`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<typename...> class...> class...> class...> class...>
        alias Cool = RESULT;
    };
};

// Pick a `Calm`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<auto...> class...> class...> class...> class...>
        alias Calm = RESULT;
    };
};

// Pick a `Grit`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
        alias Grit = RESULT;
    };
};

// Pick a `Will`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
        alias Will = RESULT;
    };
};

// Pick a `Glow`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
        alias Glow = RESULT;
    };
};

// Pick a `Dawn`
template<typename>
struct Among
{
    template<size_t>
    alias Page
    {
        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
        alias Dawn = RESULT;
    };
};
```

## Examples

- We will pick out the element at index two from `std::tuple<int, int*, int**, int***>`.

```C++
template<auto...Args>
using At = Among<std::tuple<int, int*, int**, int***>>
::Page<Args...>;

using SupposedResult = int**;

using Result = At<2>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pick out the operation at index two from `Vessel<War_0, War_1, War_2, War_3>`.

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Vessel;

template<template<template<typename...> class...> class...>
struct Flow_0;

template<template<template<typename...> class...> class...>
struct Flow_1;

template<template<template<typename...> class...> class...>
struct Flow_2;

template<template<template<typename...> class...> class...>
struct Flow_3;

template<template<template<typename...> class...> class...Args>
using ResultOperation = Among<Vessel<Flow_0, Flow_1, Flow_2, Flow_3>>
::Page<2>
::Flow<Args...>;

template<template<typename...> class...>
struct War_0;

template<template<typename...> class...>
struct War_1;

static_assert(std::same_as<Flow_2<War_0, War_1>, ResultOperation<War_0, War_1>>);
```

Note that we must instantiate the operation before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual operation in the packed vessel.
It is not quite the same as the actual operation.

```C++
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn;

// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Forlorn<ResultOperation>,
    Forlorn<Flow_2>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Forlorn<ResultOperation>,
    Forlorn<Flow_2>
>);
```

## Implementation

`Omennivore::Among` is implemented based on `Omennivore::TypicalAmong`.
When handling a packed container, `Among` returns the element directly instead of through the alias member `type`.

```C++
template<typename...PackedVessels>
struct Among
: public TypicalAmong<PackedVessels...>
{};

template<template<typename...> class Container, typename...Elements>
struct Among<Container<Elements...>>
{
    template<auto I>
    struct Detail
    {
        using type = Typelivore::TypicalAmong<Elements...>
        ::template ProtoPage<I>
        ::type;
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIABxmpK4AMngMmAByPgBGmMQSAKyJpAAOqAqETgwe3r4BQemZjgJhEdEscQlcybaY9iUMQgRMxAS5Pn6BdQ3Zza0EZVGx8UkpCi1tHfndEwNDFVVjAJS2qF7EyOwc5gDM4cjeWADUJrtuyBPoWFRn2CYaAIIPjwD0AFSf78cAKgCeqXqeAAbiR2CB/qk8KJaI8WAJgMcvu9Xi9mGwFKkmFtfgCgaDiJhTgB2KxPF4ETAsVIGSlnNwEPHozAAOjZ2HobEECjuLwmxC8DlxUJhcIRJKsxIAImcyc8npTqbTMPTGYDmccAGJ4YgTXlPfmCgjC6FiMVGena3UEfXPUkvY6O46KmlMOnnTIAL0wAH1jQBJW1O46GoXKYioIjKJjAIkme3S2UvB1Ol3K%2Ble30BoNOwkARy8OswCmOEEDuxlFY0yxTjtDxvDkdQ0dj9PL9yewfjFmOXkyRmdeNOFa1Or1ux78crctrzqprvdbiYXiIbJZj2AhKpjAIPN2Hcewb74URLbjI8bUZjKvOG63XN3a7uIBAapvM8TE%2BTCvn6fOb41K0JlIQd1VYIkhEwNAGHQECAPAtcAHkCAQeI9wPesTVFeELXOICCBAyDoNg45kNQ3Un33ZN7U7VNfzdG83EzP1jnbWdMMvZtr1OWjHW7Xt%2B0RN9hylLCzRw4B6TItDKOwF80wY45OLPNtjgAWmOMxn1fPFZRJadv0POilQYjM8G9Fi2N44580LQkSzLM5Kylat2IIAUwwjK9W3OKyjL40kBJPUDz1E/C9KnJNyWshTF2Y7MqOs2yiwc8tnK4GtrI4ryuJ8tw/K7QLjwHYSnOOIiBHQCLPxnGL6MXZdVzZO9MG3bkc0dYrT24srlOvekWrax82V5L9yRqwzIuit5kS1WgSFNBgkS%2BVEfxMxdYsYzbVXqramQQkb92OQ4mAUBRZOOgwzouk6zvKkgIwAd1tTDNXm4hFuouVg22/9dp29a9rAtgbqu87DuwS7TvBlkAHVWkwBB1iUdDZy6ubUEekT7uIJ76Xhwkkb7YtZKiu0DOmj4vjE2EJOWz5VseX6GX2tgXvco0afNRFu0isb5SZ/6/sB1VWdZCGobujxBCYcJ4jgsW1w5IbUYNDmhUhU1aYRelpZaOXiHpZWHxh0aDxAY5Ui8GJaGhYV8TBF9NewnXzmNndTcSu1JQpgXtvJc5Z2Z4OhYZUP4JBiXbs9yHo9B6H47ugA1Ys7FIWdXleY5sFUdzsWNQgqRLKgIxYY4mEt7EAGtMHQY5gVT%2BoWSD8PW5F/9FajsHE5jyWYbezGeQDjD1eNZ3xNdtwU7O%2BpLXmx6Y9tXm6vbpcV1QViOpDUelJylTrOX/zgznVeQ9Pzvm6OuOu4T5riGAHwPa34NM%2BOWGiUe1pUmOTBsQQY5UBUFOAANg0APBeT5QHHHCEQEBYD3qfVAbOF%2BWdDB13CKCGucDIQO0JE7AEWtuYmFASyHiR8jyCQxljMqODbYEnBOPbWuE3ADw%2BqIBgc9B53FJtZYM8ldpKX6r5Z%2BTpX4/FQnAt8xCNDHEekSVAMR9YRHQSWQw0CGBzEEHgBiddpGsMQRoZuvCnTyV0sYx0r937HTELQZ0EjNrHDYJUeIcDwHSNkYQf%2BKEiStAfibIx5CTGvgEW42899H7clJvzQqvsW6r0aqgNcjxwkmy3ujM82M%2Bp5WSX4j2USPyxKeFTT4xxub0xRBScOF9ozIBrugaedhVaPEwkQp4FsrY2ztowoh5wal1IafURe40fZk0qafKpwNxaX1jmDY4etZYRDICFZkStORPy9i0iSutZALPiEbNZkSIZLxokfZmCTN5e2DJhKUmB9a0FnIfY%2BTp0alRHLQkEjsIQEJdsw92hzpnIKCQ4rJjECpPOOKYwEZMYmjJXguRiCSkmblaqky5zzKEZLKjcu5A1kUq1kpC981FCkzWRGSsljNinfB%2BMWXc5TKXksZQzSaZh9gMEOF4E49IVx0EIH8JeRTZr4WzqoVgNIiTIkZmc9eST75NPRkzbGPSmIEHQPJLw4r6QwJAjA94OrBCfH1QQL4ZsXgvhUmE4Ai9%2BYvHRkIDVRRa4ACVixeFoMaMqur3iwseOjF1Cg3UepHEzekWkqI2rVm6aEPpobxAIBAK4L4FDgRjXuNw/rA2EQdRkZ1rr3V3BrBG0lJSKowRFWK%2Bg9KxnwoBjW4Wdaw7n0mT3FtN9rpHLVh5Y0Az7lFrPg24OF87h91bQCztnNwE%2Bg0D6/tf5G0DqHVfbubahnNJ3pOrgM624DomYwA60yR0rp4WurtVCfRhtqoLcZ16F3NqPfesdJ6J3zx9LsLdN652DrvQe6%2BP7l3rjlbaP1eaCCIUBMQKNAglVbPOD2zhj0p0gQ3Uhl9QQz1vvDebEAFq3Bhqw6EtwOTrWXtnaZDu37h2/vZqegmU7307qbXuyOf7b6PswrRzdRa5iOGQKmpQbQE2qqTSm068Hz341aIht%2BknOPYBAhm91YH4iQY4ecWjGgQIcbNoWy9VLfgIB1HXHOFaJUrWrZ%2B7dFnGMrIfZR/9dnWPUYnSQd6qndNZwAOJuDcMdVA1I6AkxeK/NwBgBxoOOAAWSEEnHzVBZa0ACdx6NsaBOJpAMmtgqb6Szk1C5kgqn00gaUxBxodx07WVy8QVzYm8PJn3DpwywXQuInC1FmLvn/P0ACa/LzsX4vnT5C0HjfG40QAYJGbear0sibTTlvLxACsKdA%2BBlTZW5tVfyzVpe9XZQcFWLQTgiReB%2BA4FoUgqBOBuGsNYEM6xNhxlZTwUgBBNB7dWFXEAiRJAsg0JILgxJdgaESBoMwwDgFmH8P4fQnBJC8BYBIDQGmTtnYuxwXgCgQAaZe6dvbpA4CwBgIgEA6wCBWwIhQCAaBOvxEiOBTgqh/DALUsAyQxxgDIGQMcKQLIzC8FroQBaaquAyEECIMQ7ApAi/kEoNQr3SC6GF49CDqROA8H24d47cvUeIRXGTgBQCGdM5Z2zjnXPvtmFLB4anxBTiPeWLwbHWhVgQCQFTqE9AyAU7dwFhIwApBBBoO6tClAYhy5iOEVofxVe8HD8wYgfxEIxG0FBbHT2qcPkQgwWgUecekCwDELwwAly0FoBj7gvAsAsEMMAcQuf8CEgcCCYscvMCqCgiubYT2YH1Dl7bGIEH48eCwHL9yeB4fl9IA3YgMQc03Kr0YW2RhXurCoAYK1Sc8CYEekpk7T3%2BCi5hBL6Q%2B/pcqHULnhX%2Bhq8oGu5YfQeAYgY8gKsVAqRGhl7UlcJyphLDWDMCjqfD6LAJ/CAVYOwFPbIFwGCaYPwYXUIOWRYUYYXIoLIAQGAvQFAxoBYEYaoHoCAgQfoKYTwToPQcAxvAgyYQYBAnA0gyg9A4XOYNobA5xaoMAu7LYCQdXDgI7UgZHXgVHY4Q3ZnVndnTnbnC3CAXAAXG3PYDKB3ZfVYVCJgLABIUA0gD7SQXYFkAATl2GJEkF%2BzMEkFASB2AW0Ohw4Fh1IHh12C4BZGAS4GAX8G0P8EcK%2BxqF0OAV4K104HR0x2e2Xzx0Jxd2J11xXHIEoG9w91pzYE4FaBYGBGJDUgrhOgHC4G0JZDsLO35yICAL0BPzF3EElxP0UDPzl10CCCVyYBV3Ly4J4L4PO04B11JxXH13LmIASKSJSOay5wyKyMtz83dxcT2DMHtwCJx2d1d0GJ9wiMp2mI9xAHiMSLUlSL920K4A00D0pF1BDzDwj3j2j1IFj0j0T2TwcEOPTx3Ez2zzl3z0L2L1L0OMr2r1rzO3rwgIbjL2yLb2QA70OO7wO1zz7wHz%2BCH22DO1H3HyeynxnyUDnxeJPECNXxjAUA3y3x30OIKMPwkGP1kFKNlwvxACCGaxv1/zvz7xAJfzf2yA/y/wrB/ysEsH/34MALwGAPgDAPqHwL8AgFcHoOCBgmYKWGQIyFQJyGIPyBFOKGyCFKQLwPIKaDoIlNgPlMaEIKoPKBoIYKVLyBVMYI1OGBYM4LWA2A4IygsPqJ8I4HaM6OSKhjSL6J%2B1LCkNyNt1sLGMdze1ICUJUMoC4KsJsIyN%2B2JESG0OJAB0kCMJZ2FwaNRz8Kx0CPxyJxJzJ1mKiJpzpw4HiONxYAUGBE52BHSJZGVAmD53wFyLZPyNkEKKPyl3xPPzO10F2FICqJqLVwtM11z21zCONEARtJzLzILKLJLONAgCtyGJkNZV2A9MTKmOtzTPmNGHzNSFSB9ELO0J9BHJjQ6JZz4DoG2IxwgFD1z2OIOIn1PITyTxTwuL8wzyzxzzeMwALyLxsTLye2eIX3BIryLEb0%2BJbx%2BL%2BInwBN7wfxBLBJHw%2BihN4BhNnypARKXwmL4DX1RM3233VExOrOxOKLxJlwbJ0BAGbJJIZOsHv0fw5PO2pIEDL1eETWIqZIAPiCAOb2f1VMgN5OgOVL0HgM1KNKlLFP5MwJlOoN4tYooIGH5LILVMoNlNwP1IkukuEuFLYNNIlzqM7JR04H7NZ1zPzPrmHIYgmGdPLJIDdLkPGKd0UN/l9LUMBIDKJIyN2F2GSF%2Bw2I0EcuJCcO8K7N8NsH8M9OWHexAEkESB0MSECDMMkDDPcq4EIs4F2HUv4J8v8q4N5y8o0rR3Mq9Kn0yGcEkCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/among.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/among.type.test.hpp)
