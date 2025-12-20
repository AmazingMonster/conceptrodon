<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SetContains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-set-contains">To Index</a></p>

## Description

`Varybivore::SetContains` accepts a set of nonrepetitive variables and returns a predicate.

When invoked by an argument, the function returns true if the argument is in the previously provided set and returns false if otherwise.

<pre><code>   Vs...
-> Arg
-> Arg &in; Vs... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct SetContains
{
    template<auto>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

We will check whether `1` or `-1`  is inside `0, 1, 2`.

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = SetContains<0, 1, 2>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
```

## Implementation

We will implement `SetContains` using the method presented in `boost::mp_set_contains`.

We will create a class that inherits every 'variable' we want to check against.
Then, when provided with an argument, we inspect whether it is a base of our class using `std::is_base_of`, subsequently determining whether the argument is one of the variables our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, the initial list of arguments for `SetContains` must be nonrepetitive (hence the word `Set` in the name).

```C++
template<auto...Variables>
struct SetContains
: public Vay<Variables>...
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                Vay<Inspecting>,
                SetContains
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/set_contains/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/set_contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/set_contains.test.hpp)
