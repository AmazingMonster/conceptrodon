<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalDiversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-diversity">To Index</a></p>

## Description

`Typelivore::TypicalDiversity` accepts a set of nonrepetitive elements and returns a function.

When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every element from the previously provided set and the arguments;
- doesn't contain repetitive elements;
- preserves the relative order of every element;

The resulting list will be held inside a `Capsule`.

<pre><code>   Es...
-> Args...
-> Capsule&lt;(make set)&lt;Es..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalDiversity
 :: typename...
 -> typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalDiversity
{
    template<typename...>
    alias Mold
    {
        using type = RESULT;
    };

    template<typename...>
    using Mold_t = RESULT;
};
```

## Examples

We will use `TypicalDiversity` to append `int, int*, int**` to `int*, void`:

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = TypicalDiversity<int*, void>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int*, void, int, int**>;

/**** Result ****/
using Result = Metafunction<int, int*, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

This function used to be a helper class for `Typelivore::MakeSet`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

In general, `TypicalDiversity` is a simplified version of `Typelivore::AreOverlapping` as we won't worry about short-circuit here.
After instantiating the first two layers, `TypicalDiversity` has two lists of elements to work with.
We will implement the function using recursion over the length of the second list:

- **Base Case**: When only one element exists, the result is:

  1. The first list if the element is already in the first list
  2. or the list made by appending the element to the end of the first list if it is not already present.

- **Recursive Case**: Pop the first element from the second list. We invoke `TypicalDiversity` with:

  1. The first list if the element is already in the first list
  2. or the list made by appending the element to the end of the first list if it is not already present.
  
  Then, we invoke the first layer by the popped second list.

To check if an element is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'element' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, elements in the first list must be nonrepetitive.

To 'inherit' fundamental types, we wrap every element into `std::type_identity`.

Here's the entire implementation:

```C++
template<typename...>
struct Capsule;
```

```C++
template<typename...InspectedElements>
struct TypicalDiversity: public std::type_identity<InspectedElements>...
{

// Recursive Case:
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = std::conditional
        <
            std::is_base_of<
                std::type_identity<InspectingElement>,
                TypicalDiversity
            >::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;
    };

// Base Case:
    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<
                std::type_identity<InspectingElement>,
                TypicalDiversity
            >::value, 
            Capsule<InspectedElements...>, 
            Capsule<InspectedElements..., InspectingElement>
        >::type;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_diversity/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/typical_diversity.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_diversity.test.hpp)
