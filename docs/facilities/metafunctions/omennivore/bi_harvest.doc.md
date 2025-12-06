<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::BiHarvest`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-bi-harvest">To Index</a></p>

## Description

`Omennivore::BiHarvest` accepts a list of elements.

Suppose every element has an alias member `type` and a static constexpr data member `value`. In that case, it returns two functions.

- When invoked by a container, the function collects the type results from the elements and instantiates the container with the collection.

<pre><code>   Es...
-> Oper
-> Oper&lt;Es::type...&gt;</code></pre>

- When invoked by a sequence, the function collects the value results from the elements and instantiates the sequence with the collection.

<pre><code>   Es...
-> Oper
-> Oper&lt;Es::value...&gt;</code></pre>

## Type Signature

```Haskell
-- Collect `type`
BiHarvest
 :: typename...
 -> template<template<typename...> class...>

BiHarvest
-- Collect `value`
 :: typename...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<typename...>
struct BiHarvest
{
    template<template<typename...> class>
    alias Road = RESULT;

    template<template<auto...> class>
    alias Rail = RESULT;
};
```

## Example

- We will collect the type results from `Crop<0>, Crop<1>` to instantiate `Oper_0`.

```C++
/**** Crop ****/
template<int I>
struct Crop
{
    using type = std::integral_constant<int, I>;
    static constexpr int value {I};
};

/**** Operation ****/
template<typename...>
struct Oper_0;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction_0 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult_0 = Oper_0
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>
>;

/**** Result ****/
using Result_0 = Metafunction_0<Oper_0>;

/**** Test ****/
static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will collect the value results from `Crop<0>, Crop<1>` to instantiate `Oper_1`.

```C++
/**** Operation ****/
template<auto...>
struct Oper_1;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction_1 = BiHarvest
<
    Crop<0>,
    Crop<1>
>
::Rail<Args...>;

/**** SupposedResult ****/
using SupposedResult_1 = Oper_1<0, 1>;

/**** Result ****/
using Result_1 = Metafunction_1<Oper_1>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- Note that the `crops` are not required to have both member `type` and `value`. In the following example, we will collect the type results from `std::type_identity<int>, std::type_identity<int*>` to instantiate `Operation_2`

```C++
/**** Operation ****/
template<typename...>
struct Oper_2;

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction_2 = BiHarvest
<
    std::type_identity<int>,
    std::type_identity<int*>
>
::Road<Args...>;

/**** SupposedResult ****/
using SupposedResult_2 = Oper_2<int, int*>;

/**** Result ****/
using Result_2 = Metafunction_2<Oper_2>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);
```

## Implementation

```C++
template<typename...Crops>
struct BiHarvest
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<typename Crops::type...>; 
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    
    template<template<auto...> class Operation>
    struct Hidden
    {
        using type = Operation<Crops::value...>; 
    };

    template<template<auto...> class...Agreements>
    using Rail = Hidden<Agreements...>::type;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/bi_harvest/implementation.hpp)
- [Source code](../../../../conceptrodon/omennivore/bi_harvest.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/bi_harvest.test.hpp)
