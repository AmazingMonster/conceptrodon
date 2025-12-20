<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Shuttle`

<p style='text-align: right;'><a href="../utilities.md#shuttle">To Index</a></p>

## Description

`Shuttle` accepts a list of variables and returns a function.
When invoked by an operation, the function instantiates the operation with the variables.

<pre><code>   Variables...
-> Operation
-> Operation&lt;Variables...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the variables.

<pre><code>size() -> sizeof...(Variables)</code></pre>

Check out **Examples** for all the abilities of `Shuttle`.

## Type Signature

```Haskell
Shuttle
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

If `Shuttle` is instantiated by one variable:

```C++
template<auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();
};
```

If `Shuttle` is instantiated by two variables:

```C++
template<auto, auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();
};
```

If `Shuttle` is instantiated by three variables:

```C++
template<auto, auto, auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();

    constexpr auto third();
};
```

If `Shuttle` is instantiated by more than four variables:

```C++
template<auto, auto, auto, auto, auto...>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();

    constexpr auto third();

    constexpr auto fourth();
};
```

## Examples

- We will create a `Shuttle` with variables `0, 1, 2, 2`.
Then, we will transport the variables to `Operation`.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** Packed Vessel ****/
using PackedShuttle = Shuttle<nullptr, 1, 2, 2>;

/**** SupposedResult ****/
using SupposedResult = Operation<nullptr, 1, 2, 2>;
using Result = PackedShuttle::Rail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Shuttle`.

```C++
static_assert(PackedShuttle::size() == 4);
```

- We can retrieve the first four variables of a packed `Shuttle` via regular member functions `first`, `second`, `third`, and `fourth`.

```C++
static_assert(PackedShuttle::first() == nullptr);
static_assert(PackedShuttle::second() == 1);
static_assert(PackedShuttle::third() == 2);
static_assert(PackedShuttle::fourth() == 2);
```

- If a packed `Shuttle` contains only `size_t`variables, then it inherits the corresponding `std::index_sequence`.

```C++
/**** Packed Vessel ****/
using PackedIndexShuttle = Shuttle
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2),
    static_cast<size_t>(2)
>;

/**** fun ****/
template<size_t...I>
constexpr bool fun(std::index_sequence<I...>)
{return true;}

/**** Test ****/
static_assert(fun(PackedIndexShuttle{}));
```

## Implementation

First, we will create a helper function that is responsible for the regular transportation functionalities.

```C++
template<auto...Variables>
struct Payload
{
    static constexpr size_t size() { return sizeof...(Variables); }

    template<template<auto...> class Sequence>
    struct Detail { using type = Sequence<Variables...>; };

    template<template<auto...> class...Sequences>
    using Rail = Detail<Sequences...>::type;
};
```

Second, we will create a helper function to retrieve the first four arguments.

```C++
template<auto...>
struct Payroll {};

template<auto First, auto...Others>
struct Payroll<First, Others...>
{
    static constexpr auto first() { return First; }
};

template<auto First, auto Second, auto...Others>
struct Payroll<First, Second, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
};

template<auto First, auto Second, auto Third, auto...Others>
struct Payroll<First, Second, Third, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
};

template<auto First, auto Second, auto Third, auto Fourth, auto...Others>
struct Payroll<First, Second, Third, Fourth, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
    static constexpr auto fourth() { return Fourth; }
};
```

Then, we create an interface inheriting the two helpers.

```C++
template<auto...Variables>
struct Shuttle
: public Payload<Variables...>
, public Payroll<Variables...> {};
```

If the variables are all of type `size_t`, we also inherit the corresponding `std::index_sequence`.

```C++
template<size_t...Indices>
struct Shuttle<Indices...>
: public std::index_sequence<Indices...>
, public Payload<Indices...>
, public Payroll<Indices...> {};
```

## Links

- [Example](../../code/facilities/utilities/shuttle/implementation.hpp)
- [Source code](../../../conceptrodon/shuttle.hpp)
- [Unit test](../../../tests/unit/utilities/shuttle.test.hpp)
