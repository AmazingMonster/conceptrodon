<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::InsertTypes`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-2">To Index</a></p>

## Description

`Omennivore::InsertTypes` accepts a list of `std::index_sequence`, which indicates distances between adjacent indices.
Its first layer accepts a list of elements and returns a function.
When invoked, the function inserts the elements to its argument list according to the `std::index_sequence`s.
The result will be stored inside `Capsule`.

<pre><code>   std::make_index_sequence&lt;I<sub>0</sub>&gt;,
   std::make_index_sequence&lt;I<sub>1</sub>&gt;,
                    &vellip;
   std::make_index_sequence&lt;I<sub>n</sub>&gt;
-> E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>k</sub>
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>m</sub>
-> Capsule
   <
             Arg<sub>0</sub>,
             Arg<sub>1</sub>,
              &vellip;
       Arg<sub>I<sub>0</sub>-1</sub>, E<sub>0</sub>, Arg<sub>I<sub>0</sub></sub>,
       Arg<sub>I<sub>1</sub>-1</sub>, E<sub>1</sub>, Arg<sub>I<sub>1</sub></sub>,
              &vellip;
       Arg<sub>I<sub>n</sub>-1</sub>, E<sub>n</sub>, Arg<sub>I<sub>n</sub></sub>,
              &vellip;
             Arg<sub>m</sub>
   ></code></pre>

## Type Signature

```Haskell
InsertTypes ::   typename...
              -> typename...
              -> template<typename...>
```

## Structure

```C++
template<typename...>
struct InsertTypes
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;
    };
};
```

## Examples

We will insert `Vay<-1>, Vay<-3>, Vay<-5>` to indices `1, 2, 3` of `Vay<0>, Vay<2>, Vay<4>`.
To do so, we will calculate the distance from one index to its immediate next.
We will keep the first index, `1`, since it represents how many elements we must pass to reach the first target position.

<pre><code>   1, 2, 3
-> std::make_index_sequence&lt;1&gt;,
   std::make_index_sequence&lt;2-1&gt;,
   std::make_index_sequence&lt;3-2&gt;</code></pre>

We will pass these sequences to `InsertTypes`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = InsertTypes
<
    std::make_index_sequence<1>,
    std::make_index_sequence<2-1>,
    std::make_index_sequence<3-2>
>
::Mold<Vay<-1>, Vay<-3>, Vay<-5>>
::Mold<Args...>;

using SupposedResult = Capsule<Vay<0>, Vay<-1>, Vay<2>, Vay<-3>, Vay<4>, Vay<-5>>;

using Result = Metafunction<Vay<0>, Vay<2>, Vay<4>>;

static_assert(std::same_as<SupposedResult, Result>);
```

## Implementation

The implementation of `InsertTypes` is similar to that of `Typelivore::Inject`. However, since now we must deal with a variadic number of indices, we will perform recursion over the total number of the `std::index_sequence`s.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  - Handle several `std::index_sequence`s from the front of the list;
  - Invoke itself to deal with the rest;
  - Concatenate two resolved parts.

We will use the following helper class template to concatenate two parts.

```C++
template<typename...>
struct ExtendFront {};

template<template<typename...> class Container, typename...Elements>
struct ExtendFront<Container<Elements...>>
{
    template<typename...NewElements>
    using Mold = Container<NewElements..., Elements...>;
};
```

We will use `Prefix` to enumerate arguments like in `Typelivore::Amidst`.

```C++
template<typename, size_t>
concept Prefix = true;
```

`Capsule` is used to store the result. We declare `Capsule` as follows.

```C++
template<typename...>
struct Capsule;
```

Here is a simplified version of the implementation.

```C++
template<typename...>
struct InsertTypes {};

/**** Base Case ****/
template<auto...I>
struct InsertTypes<std::index_sequence<I...>>
{
    template<typename NewElement, typename...>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            NewElement,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

template<auto...I, auto...J>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> Capsule
        <
            FrontTargets...,
            FirstNewElement,
            MiddleTargets...,
            SecondNewElement,
            BackTargets...
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/**** Recursive Case ****/
template<auto...I, auto...J, typename...OtherSequences>
struct InsertTypes<std::index_sequence<I...>, std::index_sequence<J...>, OtherSequences...>
{
    template<typename FirstNewElement, typename SecondNewElement, typename...OtherNewElements>
    struct ProtoMold
    {
        template
        <
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            // We use `Prefix<J>...` to go across the distance
            // between two targets.
            Prefix<J>...MiddleTargets,
            typename...BackTargets
        >
        static consteval auto idyl()
        -> ExtendFront
        <
            typename InsertTypes<OtherSequences...>
            ::template Mold<OtherNewElements...>
            ::template Mold<BackTargets...>
        >
        ::template Mold
        <
            FrontTargets...,
            FirstNewElement,
            MiddleTargets...,
            SecondNewElement
        >;

        template<typename...Agreements>
        using Mold = decltype(idyl<Agreements...>());
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEEv4AbKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQlJqQqt7Z0FPZODw5XV4wCUtqhexMjsHOaBEcjeWADUJoFuXo60hACeZ9gmGgCCewdHmKfnyJPoWFT3jxeZn2DEOXhOZzcBBuaUwAH0CMQmIQFADnoCAPQAKhxWOO2FUBFcADFiLJjrisRjAUSWGkDETIdDYcw2AA6Dlop6TYheBz4wkksmCU4AdisooAImcrOjnrT6UxGecFQzMEyYYxWJgOWz7sdDkwFApjh5BMjImRjsyteyOdh6GxBKjAg9njy%2BQQBUSGOhSbJIWbWhEEpCHZgnQQFLqAa7ASZxYDjsnrRHFcqoZrWTqOVFMAB3cORl1up4p45eLJGY4AWU86E%2BktNsgtofOecLjsYUd1pHxXedMbjgVlLylMvjz2xuOOymImBoqgpuOp8rTao1LO1fayAC94QQuWhQZg0l65wu8Euzk3EV51SPJ09pzjTUw0govPRlzjV09VUqD6Zludp6nG7p3vybjvp%2B9ATnKz6UscACSDBKO0AAqmompSf4ARmNrZkOpYevyqHoQQWGwiaCYStKj4IS%2BeIWEaHzQUoP5UjS66AZCTCXKgurIVypFeuRCSUdhkI/CAIARFgqhwkoACO94npCyHEVytFJim%2BFAYR2rHB2Rbdn2hmgVy5aibOZJEHWtDoLpyY6c85blvpznuZCXnuSmGIYscADqHyVh8JjJBoF6Lhp9wxpF1qoMcjA%2BAkgGnJF/qCBhbTAJgUYRRoepuX57nRVesWurqWWUbl%2BUKKQvmlRZOZsixyAANY5cQeUFSVflWaV8yOMgBoCJMmAAG5iMc/FEMceDoDctAQCsTXJgAtPq0Efl%2B6r9d55zre5NXdb10Yco1B2lcZBamYIV1ljdKbtV1dU9py10prGo7HZ5KpZtqupPMA84Rt2JbHZWETALW9aNscWCHDaECLctkIg2DxbEata0MU9LnjvjXn/cBtqtZjmDg86g3JtD1YOQ2N62ag9n1hjoNU9jnLDr9RO/WudIbucc2CRyyF9qLuoAFIiZBYloRJVGYC6bgyXJvqYIpKlqdsGnETuBDoLJ8la0pmCqYwevnNLWngWOo4eTxBGA2wxzEngxCTCZA4EOZrsfEImDHugPvU371oB1pB02XOrOoIzXmuQT7meV9LlHen7kBcFoUcYV5WqJV2DxRoiXJQwqVIkSGUaKd72opFxUpzdhfF9Vwq1T19WPc9/mBSFFb55Fbc23FnIJfNwBJUwyBksa1oIB8%2BDzOpWfljn8QEPmVMMNa%2BZJVM53N33yaj24stVRyNaLeg9BnT3x0eVHHKvQ/fUt999s3cNeCjceE1pq0FmgJBaS0VprSzltV0b5dpwSzj5deKZ67dw%2BmyXup8PZewIGHSMGC%2B431%2BPfBuvYn4piDiHXBZkyHJjfiQz6n8M4PGJlnUmLVgac3DpDLO9NYaMwRkjWgKM0a0A5ljCGOMVh40dt9fmT4nZC14gDECFNOHFlpkPGGcNHIIzjmzRyYiuYSJ5swvm9EBaIRnAAJWDpsLIk02KsU4nhZ2QEpbi0lgJGW/sVG6gAPIECXsQIOlsTzcO5PLFCitMJSXOOrU22sLa6yAppExhtjYawUubUJ1sL4G2OAEoJITkkXTAqWZOCj0wGQDu7T23s7q%2Bx8eTY4FCBChwaeHJpREOSFISFQmm38UyxzsgndmB0KnNVccdRBjDs4DzzuFEe84YrnGElfPUk8kopTYNXRZddO7v0bkVGhtlLxF1WePNkKDzr4OejnQeYVa7n0viXCeZcp4zznpkE0gTl54FXnrJByZN75R3owfeh8SEnOeZcwhd9MCHNuTddhr9Z5vVQaiBBgy/K/3/uNIkQCQHzREatY60DsDeiFAGLFbgTktSiRRZWqtenBKSVbFW0dZnllkvpbRTlzgsv6WgjRN0eWuL5ZCOhGLOU3RFSmMViia6JxpSc659VSFAtqdgoVSLSpwuIdKy6JzWm%2BiFdM3m8jJmKuqb4jklMuFyrplWPh8NmaCOEeAwxXDJHSKTnIhClThZk26Wye16jsWaIZq6wITY9GjIMecMNxiynwTHOYp8TFKRZt/JiJCGEVZRmcbm7NJauIIVeKCd4nwLhXFuNpQWVS%2BKgLWSRSJdYGDxwYHcdE4pji4rGmhIkqg0jECJUlIB94xQWGEvzMU6aEJsJfimiCvIoIwT2qm7i1rNzk2Bj1cJvDaz5SYFQLwoImgI3EjE6i8ZM4p3ViwJgHV4QJOyckyEXB7i3IfU%2Bl9mtEk5KAmYDan7XTfqNrJR9z64Svp1uyyEgQNpmG0vbWSidzjts7Xcc4IGv1ww7UQLtkINqBDw5hwj2G3AbX8LGUsaH2aJv3XbCxh6hBeDSMUTA6AbGwS9MzHasEgLkYEJRjQZGBBYeI6B7AfZhNEfOMhsD%2BHJM4dI0puTlHJDiYIyJ4jNHhymKfIenjX4%2BMxqPa0U956ciQg05CMT6mJMUchIpmTynnPnC0wZzdEElR/zhEaCiEB1YKG1AF1WbGOOZC4yZoRfZYuHldNIjgaxaCcH8LwPwHAtCkFQJwWllhrB9o2FscKwIeCkAIJoFLawOoBDMGyUUZhJAAA4Wv%2BA0AATn8GYDQyQWvBDSxwSQvAWASA0BoUgWWct5Y4LwBQIBJtVeyyl0gcBYAwEQCADYBA0iXHIJQNAdI6B9O1JwVQLXkgbWSJIY4wBkCjSkGyMwvAuOEBIItPQ/BBAiDEOwKQMhBCKBUOoFbpBdBcFIPmJEaROA8FS%2BlzL1XcucD8ZcPbXpUBUGOBdq7N27sPeOE9swxwIAeGO/QUdewuArF4MtrQawIBICO2kE7ZAKAQBZ2zkAwApBmD4HQIkXtKCxGR7ECIbQbhw94OL5gxAbh%2BNiNoYOy2KtHcjH4hgtApdg6wLELwwBoK0FoAt7gvAsCPqMOIXXnsVd4AcabnLWtbFEml%2BQQQDRkfXFiEieXHgsDI8RHgMbZvSAOOILEaLkoIyGGANcIw1W1hUAMMABQAA1PABY/Esjd994QohxAA7z8DtQyOIf6Fjygaw1h9B4FiAtyAaxUBnhyKbjaPwbymEK5YXrvBUDh%2BIItFW8A1h2Dt84CArgZh%2BEh2EEMSwxiQ%2BKNkAQ0%2B9DL6aIsUYNRejj%2BaFMDonguh6DHw4foB%2Bt9VEX7YA/a/IfzHaJf5YNP1ibG2BIBHHAMtTeR7NnHl3rtbt7tHtJBntSdcB3sqdytadKtE81gl4mAsBEhVpSA6tJBAg2ROtAhRRJANBJBmtIoNAUhOt9BOARtSAxtAguA2RkguB%2BtOsWs6D/BJBagsDUhps%2B9OB5tFtYCVtGdNsmdtt0d9sOcudKcogzsOA2gWBJpRQNomADQDBqwuBOs2RqCnd8AiBB9jZIc89ftC9pBi8lBS8wddB%2Bdod3xpdP9v8OCUcOA0ddtLhjgsdZpiAZC5CFDDRlDVD1DSdydWdKdThgQzAYD6dVtBCxCEgDtOdUAKcxhpDZCNovDedOsuBJsaAhEEgFsIBRcwdZdJc3d8j5dFdlcHA3d1duxNdtdkc9cDcjcTc3cLdY9rcct8B5wz8HdkdndkBLgdgKsIgiQhsctvdfcbh/cdgcsg8Q8Ktw9I8lBo9Lc48YZE8%2BAU909M98xs9GBc9ZB9D/tDDZAS9QccszCK8E8u8rBLBa968R9csW9xpOB28jZO9q8e8ZsB8h8G8UDT8mgXBfQ78QhfQn9r8N8cgATQSyh59t8T8Gg98Bhpgj8Ch79YSz8BB4ShgoSr8d8H9D98gZ8b8FhMTn9R8St38X8hsbDf9OBXD3D5DFDY8icfC2Qy4IAICtCgiqDQi4DSAECkDKBP9yDKDVC8DRR/BOtRRRRAh8DJAbtIdbDZtuClsVj1stsdsMdojIjiAJC2BOBpD8cWAFBJpRpJoVC2Q1RJhXtNCPsdDAd88/sJADigdjDjidAQBggLDYczdrCkcwdZsHCMdnDsc9TbsDSjTjgTTVDzSvQydYiAiEgOTAguS%2BC1tmdYy2cNS0zKcQAjSOM4QIy4QoyAs3CbsBdMjhccixcJd5dCiqyFclcVdyjYiNctcddWjMB9dDcxAGjQ8mircJjzdbcOjh8wdujei3cBjPcwcRjJdxjA9B9pjeBZio8Y8rdljkzk8mBU8M8s8c9Q89CC99jbSjiy83SzjjBXibBvcvim97i0JOAMQZILjrBe9csPisBrzd9US/BJ9/jET8S58KhoSl9MgV9cg/z18QLN8iTr8fjz9BgATYK0SL9oLsTb9wL79kLAKsSP9X9SscKKSfSZtqTgzjhQzjTTSozwCrSoDOS6duTeSxgUChtBSQAzBVDAhAh/AOsWCJsOLRR%2Bsf9fSuDbAeCwipFUCQBJBRRntRSuApBOsRSsCuBRRSCOBAhCLOC5teCGdP8XtBKiKtKxK1hw8shnBJAgA%3D)

## Links

- [source code](../../../../conceptrodon/descend/omennivore/insert_types.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/insert_types.test.hpp)
