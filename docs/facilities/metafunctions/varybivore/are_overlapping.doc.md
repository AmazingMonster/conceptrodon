<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreOverlapping`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-overlapping">To Index</a></p>

## Description

`Varybivore::AreOverlapping` accepts a set of nonrepetitive variables and returns a predicate.
When invoked, the predicate returns true if the list created by appending arguments to the previously provided set contains repetitive members and returns false otherwise.

<pre><code>   Vs...
-> Args...
-> Vs... `overlaps` Args... ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct AreOverlapping
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto...>
    static constexpr bool Page_v 
    {RESULT};
};
```

## Examples

We will showcase three examples.

Check whether `1, -1` and `0, 1, 2` overlap:

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = AreOverlapping<1, -1>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<0, 1, 2>::value);
```

Check whether `1, -1` and `0, 2, 2` overlap:

```C++
static_assert(Metafunction<0, 2, 2>::value);
```

Check whether `1, -1` and `0, 3, 2` overlap:

```C++
static_assert(! Metafunction<0, 3, 2>::value);
```

## Implementation

The name `AreOverlapping` is probably a bit misleading.
This function used to be a helper class for `Varybivore::AreUnique`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

After instantiating the first two layers, `AreOverlapping` has two lists of variables to work with.
The first list must be a set, meaning repetitive variables are prohibited. The reason for this will be apparent later on.
For the function to return true, the second list must satisfy two properties:

- Every variable in the second list is not contained in the first.
- The second list does not contain repetitive variables.

To check if a variable is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'variable' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, variables in the first list must be nonrepetitive.

We will implement `AreOverlapping` using recursion over the length of the second list:

- **Base Case:** When only one variable exists, the function returns true if the variable is in the first list and returns false otherwise.

- **Recursive Case:** Pop the first variable from the list.
The function returns true if the variable is in the first list.
Otherwise, we append the variable to the first list and pass the result back to `AreOverlapping`.
Then, we invoke the second layer by the popped second list.

Here's the entire implementation:

```C++
template<auto...>
struct Shuttle;
```

```C++
template<auto...InspectedVariables>
struct AreOverlapping
: public Vay<InspectedVariables>...
{
    struct Detail
    {
        template<auto...>
        struct ProtoPage
        { using type = void; };
    };

// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, AreOverlapping>::value, 
            void,
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_overlapping/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/are_overlapping.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_overlapping.test.hpp)
