<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-amidst">To Index</a></p>

## Description

`Typelivore::Amidst` accepts a list of elements and returns a function.

When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amidst
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = Amidst<int, int*, int**, int***>::Page<3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We want to count elements one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the elements to enumerate.

We will use variadic functions for this purpose.
There are two ways to achieve it.

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target element.

We will need the desired number of `void*`s in the front of the function's parameter list to enumerate the unwanted arguments.

`PointToVoid` will turn an index into a `void*`.

```C++
template<auto>
using PointToVoid = void*;
```

With its help, we expand a pack of indices to produce `void*`s.
`Midst` will help us extract the pack from a `std::index_sequence`.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    static constexpr auto idyl(PointToVoid<I>..., auto* target, auto*...)
    { return target; }
};
```

Now, we make a template that generates the `std::index_sequence` and translates the result.

```C++
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(static_cast<Elements*>(nullptr)...)
        );
    };

    template<auto...Agreements>
    using Page = std::remove_pointer_t
    <typename Detail<Agreements...>::type>;
};
```

- Second, we use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target element.

`Prefix` will turn an index into a constraint that evaluates to `true` for every type.

```C++
template<typename, auto>
concept Prefix = true;
```

`Midst` will help us extract the pack from a `std::index_sequence`.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<typename Target>
    static constexpr auto idyl
    (Prefix<I> auto..., Target, ...)
    -> Target::type;
};
```

Now, we make a template that generates the `std::index_sequence` and translates the result.

Note that we wrap the elements inside `std::type_identity`. This ensures we can create objects to invoke the ordinary function.

```C++
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(std::type_identity<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};
```

The function is implemented using concept expansion in this library.

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/amidst/implementation.hpp)
- [Example](../../../code/facilities/metafunctions/typelivore/amidst/implementation.point_to_void.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/amidst.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/amidst.test.hpp)
