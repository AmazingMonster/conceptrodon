<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreOverlapping`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-overlapping">To Index</a></p>

## Description

`Typelivore::AreOverlapping` accepts a set of nonrepetitive elements and returns a predicate.
When invoked, the predicate returns true if the list created by appending arguments to the previously provided set contains repetitive members and returns false otherwise.

<pre><code>   Es...
-> Args...
-> Es... `overlaps` Args... ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct AreOverlapping
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename...>
    static constexpr bool Mold_v 
    {RESULT};
};
```

## Examples

We will showcase three examples.

Check whether `int*, void` and `int, int*, int**` overlap:

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = AreOverlapping<int*, void>
::Mold<Args...>;

/**** Test ****/
static_assert(Metafunction<int, int*, int**>::value);
```

Check whether `int*, void` and `int, int**, int**` overlap:

```C++
static_assert(Metafunction<int, int**, int**>::value);
```

Check whether `int*, void` and `int, int***, int**` overlap:

```C++
static_assert(! Metafunction<int, int***, int**>::value);
```

## Implementation

The name `AreOverlapping` is probably a bit misleading.
This function used to be a helper class for `Typelivore::AreUnique`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

After instantiating the first two layers, `AreOverlapping` has two lists of elements to work with.
The first list must be a set, meaning repetitive elements are prohibited. The reason for this will be apparent later on.
For the function to return true, the second list must satisfy two properties:

- Every element in the second list is not contained in the first.
- The second list does not contain repetitive elements.

To check if an element is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'element' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, elements in the first list must be nonrepetitive.

We will implement `AreOverlapping` using recursion over the length of the second list:

- **Base Case:** When only one element exists, the function returns true if the element is in the first list and returns false otherwise.

- **Recursive Case:** Pop the first element from the list.
The function returns true if the element is in the first list.
Otherwise, we append the element to the first list and pass the result back to `AreOverlapping`.
Then, we invoke the second layer by the popped second list.

To 'inherit' fundamental types, we wrap every element into `std::type_identity`.

Here's the entire implementation:

```C++
template<typename...>
struct Capsule;
```

```C++
template<typename...InspectedElements>
struct AreOverlapping
: public std::type_identity<InspectedElements>...
{
    struct Detail
    {
        template<typename...>
        struct ProtoMold
        { using type = void; };
    };

// Recursive Case:
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Case:
    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, AreOverlapping>::value, 
            void,
            Capsule<InspectedElements..., InspectingElement>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/are_overlapping/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/are_overlapping.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/are_overlapping.test.hpp)
