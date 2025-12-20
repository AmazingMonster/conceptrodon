<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalDiversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-diversity">To Index</a></p>

## Description

`Varybivore::TypicalDiversity` accepts a set of nonrepetitive variables and returns a function.

When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every variable from the previously provided set and the arguments;
- doesn't contain repetitive variables;
- preserves the relative order of every variable;

The resulting list will be held inside a `Shuttle`.

<pre><code>   Vs...
-> Args...
-> Shuttle&lt;(make set)&lt;Vs..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalDiversity
 :: auto...
 -> auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalDiversity
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };

    template<auto...>
    using Page_t = RESULT;
};
```

## Examples

We will use `TypicalDiversity` to append `0, 1, 2` to `1, -1`:

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TypicalDiversity<1, -1>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<1, -1, 0, 2>;

/**** Result ****/
using Result = Metafunction<0, 1, 2>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

This function used to be a helper class for `Varybivore::MakeSet`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

In general, `TypicalDiversity` is a simplified version of `Varybivore::AreOverlapping` as we won't worry about short-circuit here.
After instantiating the first two layers, `TypicalDiversity` has two lists of variables to work with.
We will implement the function using recursion over the length of the second list:

- **Base Case**: When only one variable exists, the result is:

  1. The first list if the variable is already in the first list
  2. or the list made by appending the variable to the end of the first list if it is not already present.

- **Recursive Case**: Pop the first variable from the second list. We invoke `TypicalDiversity` with:

  1. The first list if the variable is already in the first list
  2. or the list made by appending the variable to the end of the first list if it is not already present.
  
  Then, we invoke the first layer by the popped second list.

To check if an variable is in the first list, we use a method described in `Varybivore::SetContains`.
Namely, we will create a class that inherits every 'variable' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the variables our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, variables in the first list must be nonrepetitive.

Here's the entire implementation:

```C++
template<auto...>
struct Shuttle;
```

```C++
template<auto...InspectedVariables>
struct TypicalDiversity: public Vay<InspectedVariables>...
{
// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            Shuttle<InspectedVariables...>, 
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_diversity/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/typical_diversity.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_diversity.test.hpp)
