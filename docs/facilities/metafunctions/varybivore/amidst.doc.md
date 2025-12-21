<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-amidst">To Index</a></p>

## Description

`Varybivore::Amidst` accepts a list of variables and returns a function.

When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst
 :: auto...
 -> template<auto...>
```

## Structure

```C++
template<auto...>
struct Amidst
{
    template<auto>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
/**** Metafunction ****/
template<auto...Args>
using At = Amidst<0, 1, 2, 3>::Page<Args...>;

/**** Test ****/
static_assert(At<3>::value == 3);
```

## Implementation

We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose. We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

There are two ways to enumerate the arguments.

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target variable.

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

Finally, we will make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            std::remove_pointer_t
            <
                decltype
                (
                    Midst<std::make_index_sequence<I>>
                    ::idyl(static_cast<Vay<Variables>*>(nullptr)...)
                )
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

- Second, we can use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target variable.

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
    (
        Prefix<I> auto...,
        Target,
        ...
    )
    -> Target;
};
```

Now, we make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            decltype
            (
                Midst<std::make_index_sequence<I>>
                ::idyl(Vay<Variables>{}...)
            )
            ::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

The function is implemented using concept expansion in this library.

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/amidst/implementation.hpp)
- [Example](../../../code/facilities/metafunctions/varybivore/amidst/implementation.point_to_void.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/amidst.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/amidst.test.hpp)
