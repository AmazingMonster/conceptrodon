<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::Among`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-among">To Index</a></p>

## Description

`Omennivore::Among` accepts a packed vessel.

- Suppose the vessel is a container containing elements. In that case, It returns a function. When invoked by an index, the function returns the element at the index.

<pre><code>   Con&lt;E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>&gt;
-> I
-> E<sub>I</sub></code></pre>

- Suppose the vessel is a sequence containing variables. In that case, It returns a function. When invoked by an index, the function returns the variable at the index via the member `value`.

<pre><code>   Seq&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;
-> I
-> V<sub>I</sub></code></pre>

- Suppose the vessel contains operations. In that case, its first layer accepts an index and returns a function. When invoked, the function instantiates the operation at the index with its arguments and returns the result.

<pre><code>   Vessel&lt;Oper<sub>0</sub>, Oper<sub>1</sub>, ..., Oper<sub>I</sub>, ..., Oper<sub>n</sub>&gt;
-> I
-> Args...
-> Oper<sub>I</sub>&lt;Args...&gt;</code></pre>

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
/**** At ****/
template<auto...Args>
using At = Among<std::tuple<int, int*, int**, int***>>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = int**;

/**** Result ****/
using Result = At<2>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We will pick out the operation at index two from `Vessel<Flow_0, Flow_1, Flow_2, Flow_3`.

```C++
/**** Vessel ****/
template<template<template<template<typename...> class...> class...> class...>
struct Vessel;

/**** Dummy Arguments ****/
template<template<template<typename...> class...> class...>
struct Flow_0;

template<template<template<typename...> class...> class...>
struct Flow_1;

template<template<template<typename...> class...> class...>
struct Flow_2;

template<template<template<typename...> class...> class...>
struct Flow_3;

/**** Metafunction ****/
template<template<template<typename...> class...> class...Args>
using Metafunction = Among<Vessel<Flow_0, Flow_1, Flow_2, Flow_3>>
::Page<2>
::Flow<Args...>;

/**** Dummy Arguments ****/
template<template<typename...> class...>
struct War_0;

template<template<typename...> class...>
struct War_1;

/**** Test ****/
static_assert(std::same_as<Flow_2<War_0, War_1>, Metafunction<War_0, War_1>>);
```

Note that we must instantiate the operation before the comparison.
This is because the function returned by `Among` is an alias template pointing to the actual operation in the packed vessel.
It is not quite the same as the actual operation.

```C++
/**** Forlorn ****/
template<template<template<template<typename...> class...> class...> class...>
struct Forlorn;

/**** Tests ****/
// GCC compiles.
// Clang and MSVC fail.
static_assert(std::same_as<
    Forlorn<Metafunction>,
    Forlorn<Flow_2>
>);

// Clang and MSVC compile.
// GCC fails.
static_assert(not std::same_as<
    Forlorn<Metafunction>,
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

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBIAnADspAAOqAqETgwe3r56KWmOAkEh4SxRMVwJtpj2BQxCBEzEBFk%2BflxVNRn1jQRFYZHRcYkKDU0tOe0jPX0lZUMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYSa6MyHiYCpd7x2cXh9/7H6cn/zMAGZgshvFhLiYgW5kCN0FgqFDsACAV8tpcACoAT3utDwADcSOwQNiknhRLRTiwBMA3rs/sw2Aokkw1picdUCUTIfErGcAQRMCwkgZBVC3AQOYzMAA6OXYehsQQKJEAkbELwOdlkilUmk8qzxa5Qvn/M6C4WizDiyX3aWXABieGII1VZ3VmoI2vJYj1RnFTpdBDd/15AMuEcuFpFTDF0LSAC9MAB9L0ASRDkcuHq1ymIqCIyiYwEwBpMRpNKLOWejVvFiZT6czkeImAAjl5nS9LhAM0Djf2NPNw5Gc168wXUEWS%2BK%2B8jq5HyxZLl40kYoxzIf3Hc7XUDl%2BWB6aRxHa7HrdCmF4iHKZadgK2hYwCCqgfPTlnV8FadPS1DrpcE6FsWF5uPej5Ki%2Bt5IiAIC2hex4VvuVanGecYSlKrCloGIykBudpYZcQiYGgDDoHh8HSreADyBAINEr7vmO3q6tS/rQjhBB4cRpHkZctH0S60FviiYYLqeQoxuhDappcc4ntmBAarm%2BbASWkLiQaK5rrS8FbgBpI%2BpSbHAOKAkMcJ2CwWhpZAVOIGzpcAC0lxmDBcEciaPJHihNaSXW8Z4EmsnyZprYdl2ry9v%2B/5DgpzF2b%2Bs7NhGS7ad%2B%2BF/tunFeYelb8ppNn1kFjZySllzhZ2rZRX2A7XFww6aQlqn2TO0KhR%2Bi68ul656f%2BREkQI6C5Uhx6Ff557ileN5yuBmBPsq5Vfuuv76YBLVJdCc0LVBcqqsh/KjSheUFeceyOrQJA%2BgwdI7H8RXQg9EoTehT2UVhlmXGCTAKAon3fb9/0GL9REkPmADuIbMQ6l3ENdommn5lqTY9L2gW9mFsEDP1/Xtb5fcDuMygA6o0mAIMsSiMQpy20jDqDg2tQhgwz4qk62FOri8ln5aGPmnWiLG%2BiZt1HAKaM2pjF5MUpnpC8Z%2BpLnlB1mqhEuo8jr1S9jIMeIITDBNEFHa/KirPtT7qy1qhmsTS4p6w0hvEOKCo7UT%2B3viAlxJF4ER4sg2qcoSrawTbwt29CruQe7ImHYa/Oq0V/LQgpb3q89mvo%2Bn71Y3j2AEzjOsx/nAPFwXIMAGovHYpAKRsGyXNgqhKayXqEEKrxUPmLCXEw3usgA1pg6CXPi1fVDKqfZ9PmeSwRueT/jpdFyvcr0%2BDKrJzLylemHCvsW4Ve/dUAaXRvPOx6GiORk902oGVl9Zs1k5JZpSuaUjUlZ7PGtf3PjAfTzuXMuy9ZrEGAD4c25Usz10uMTUs4NGhJEuJgVkCBLioCoJCAAbBode7tcGXGCEQHBeDYbw1wQpGBDdDAj2CISIepDSRByJKHHERk/SmVwTKDSnUswRlphdBma1mF4mDsSPenDT5XVEAwaRG8kQ8w/pGayaNAIOXatAyMsCMT0VIfBEwhDwallQBER2IQ6GvEMEQhgUxBB4HPCPQxZCZGGGcZPZREZrKeU8ZcWB8CvpiFoFGPRNlLhsFKNEUh69nGXHBoQdBdFSyNAgdHDxfD%2BGqMzkIyGW1wGQOVBfa%2BqUjqnU/gFNwd9bynHydHJaOl1HqX6olDRYFanmyKaJBOqIfi9N%2BD0q4aZLQ7VjBkUWfw0R9J%2BH8cWP8MLz1lHKIsyAh7oCPnYC2pxmJSLOF7H2ftyTyykdCZZqz1nVGLgjZWY01ZzIxgsoulwHYGxCGQTKVFTZuyhlbL0xy3DPKdi7M2hS84hnfhk2%2B1574dSfj8m4mBHa0AUuC/hkZBF9W3KIrkIcSTsNtgfKOHTQW%2BKyV/daL9WkwtRZcbx9xeZZmub5G%2B6cqmzQfPNOpj80UNNWv1W4iLxTbTSXnWlCEum8wGVM6Zkr0ScUbqoVgIpSzvBlVKg4Mz%2BTAlBOCLKEovBKrBZ8c6qFxmzL/peKF1TwGbMESa/qfy4TWX1fQcUxC8LEK2O6wQOwvUEF2B7AEsFNptOAJclWMqiL6ryMPAASi8LwtAvQqrOIIoQUbUixvjYmtaHqtgSqNVcONCgE1JvpACQRRaS1rVQuKNyIlw0Fp2JiF4pa7pqgaI4ZAyYcbRAIBAR1IAFBYW7a%2BNwlbE3cXTUodA47gxvmHA2s6arpWNvRDxIa8rFX0FNau5d/SBbnXOcE5NtzzUZzPWnO5JtF4l0JqvG9wClFbLhUe/NS6m3XB8CwLElwampPNju09FTL0XuvUiR9QDQE3vbTvHJyYNBvpA8B7OYGl53sg%2Bh6DltYPr2TFwRDM8L0oYeRhwupHAbEufThs%2ByY603KQyjc9wHUO3rIw%2BqD3zqMM2TECN9gsACyCKmBUC8AwBwYyT0MdesRgBC9wMcbQ2xv9NqGmCYaCJsTtRq0mXFK%2BjiNGNB4Vw%2B0ODZgjM0d4/Wz2IBg11uszEvJobOkHquJ%2Blg37f3tOVIBqT6MWMQaw1RuW7N4MEbuTJj57HMOceC40PDfHzoYhbYBqYnaR1KCaP2gg6BYJDrYCO%2BRtG2ZxcM3AuL%2BG3x4TU8J0T4mBDFeIPBvCIWKvInnQlvdhwJmJYQM6EeTct3KrLbuzrbaXNNodCQWGN1JOEeQ%2BFq9JGotsfk9FxTFHAvQymyQORi7BZJZGK8E9sCADi/yvqoGFHQbmqIG5uAMOuWhlx%2BNCArm4S4VADa0HSal8k6Xe1ZZy4O4dP1xQKUm8Qab4pqsabq7t7AtdNIQ6h/p7jdmUTtb23dh7tInsvbexdq79B0mnfO59ugf122jK7T2zLDACyKSB3llMoOU5I%2B28QXbbgYe1dqEiRHGTkc7cK%2BjreC7TQcEWLQTgABWXgfgOBaFIKgTgbhrDWGzMsVYf5gQ8FIAQTQkvFgDxADLyQMoNAAA4zBmFiLELgMureW64PEeI0hpccEkLwFgEgNCGYV0rlXHBeAKBAIZg3ivJekDgLAGAiAQDLAID7LiFAIBoCJ9EUIWFOCqEt9gpy2DJCXGAMgAOUgZRmF4MPQgV0cvtH4IIEQYh2BSBkIIRQKh1CR9ILodo4NiBMCSJwHgUvZfy8N8rzg1FrzJ4wVg3P%2BfC/F9L5ccvZgeweAz8QSEuv5i8Aj1oRYEAkDp7JPQMgqfT/XZiMAKQZmaCJoYpQCIE%2BIjBEaFiYfvA3/MGIFiaiEQ2gJEEeeu6ekE1EDAtAn%2B3eWAEQXgwAlStAtAoe3AvAWALAhgwA4gMBXY4mY8KBSumAqgJE146weuxC1QE%2BeIEQA%2Bf%2BHgWAE%2BSkeAPuqBpAY8xAEQGatwGBRgeIRghuiwVABgoaFczw4M1EdoX%2BbewgFILe0gDe8gSgagE%2Bve%2BgmBKA6ulg%2BgeAEQoekAiwqASQtQKBTkcI/4pglg1gZgge7BcMWAehEAiwdgwBGQLgZE4wbQpAgQhsswgw7QeQ6QAgHhuQqQgRDAMwAw5QHQLhAg3QYwngrQegzhcOcRvQPhkRSRowzQCREwtgWRERkS5QThWuawEgo%2BHAcupAAevAQelwC%2BBeReJeZe5u6%2BEAuANe2%2B5gQIDU%2B%2BAhiw9ETAWAMQjhpAJukgQIMosQQIbuGgkgZgkguCGgMu2CsQ%2BgnAXupAPu3RMo2CXA2ClusQzu2CZuDuUx2CVRE%2BQeIeYe%2BuAh0ecex%2BCeM%2B145AlAV%2B5%2BWebAnAjQLA%2BI8QTkfc3064FQMoXAFuVe%2BARAdhegChTe4greChHeyh3eugZm/eg%2BX%2B5RlR1Rk%2BHA0%2BSe14c%2BdReeDRBcwJsQoJFuG%2Bl2Z%2BUSXRZge%2BtxkeR%2BJ%2BNJ1%2BrxaebJ5%2BKAOOFQXAhmD%2BgoLoz%2Br%2B7%2Bf%2BUhP%2BH%2BABQBDgUhYBz4EBUBE%2BsB8BiByBUh6BmB2BSu%2BArYeBLwE%2BRBJBgoUhFBHuSu1BtBWI9B6wSuTBLBeu7BnBSg3BWp34dxQhxYCgohmA4hkhrBsJshEg8hsgSJXeSuqJah/BFhVgWh1BDhBhRhGQJhZh/YMZVhNh0QdhBp%2Bh0RcObh7gORnh3hxQGR/hoRtQwR5Z%2BQGQBRcwkw1QMRdQWRVZeZtQqRdZfheRPQrZUwTQnZRRSwKwpRDUaxFR4%2B3etR9RS%2BQJtIIJYJGgPY7RUJO%2B3RjJB%2BRupAAxQxlA5RGxWxFJsx8QMuCQ8QQIcxCxkg7QOJVxtgNxG5R%2BDxSAieyeHJ7xme2eHAPxS%2BLACg%2BIAc%2BIIJVoIwEJHReAde0hcJch0hYZKhIAQIpA6JQ%2BqBWJE5geU%2BzxXomCdRP5f5AFQF54Iw1JW%2Bq5QI65dxjx75F%2BbxXJgw/5SQSQyYgFsQyYwFBAyYqghefAdAQpoeEAL%2B3ekp4prBQl/%2BgBwBcpl24BkB0BOpmAcBCBQSKBeumpvBtpaBuBjg%2BBhpxByApBppgglB3elpH%2BNpjBcMDpvATpXBQobp/BzJfAwh3pYhEhjAUhgZzewZMFSh4ZOg8FUZxgmhNg8Z8AiZxhnAGwjq6Zlg1hNRth4FOZIxyRtQBZrZJZ/QhRIRNZQRRZWVYRA5SRjZKRLZuVDZnQsR%2BR6RmVkwJV2QnhfZaRpZ1VxRw5LeqFFxk5nAOFRev5/5o8BFgoRFbRkJJAq5PRTJh%2B/RqCO5IxHu%2B5IAtuMoQIQIMujuV5fuy18Q%2BxHV6Fwed54efRoxIAkgMukxLu8Qfulukg9uXA1uZg5xHuQIaFNRnAvRzJ5RleO1L1e1D5iw7BaQzgkgQAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/among/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/among.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/among.type.test.hpp)
