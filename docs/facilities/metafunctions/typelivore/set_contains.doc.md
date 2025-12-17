<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SetContains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-set-contains">To Index</a></p>

## Description

`Typelivore::SetContains` accepts a set of nonrepetitive elements and returns a predicate.

When invoked by an argument, the function returns true if the argument is in the previously provided set and returns false if otherwise.

<pre><code>   Es...
-> Arg
-> Arg &in; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct SetContains
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check whether `int*` or `void`  is inside `int, int*, int**`.

```C++
/**** Metafuntion ****/
template<typename...Args>
using Metafunction = SetContains<int, int*, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

We will implement `SetContains` using the method presented in `boost::mp_set_contains`.

We will create a class that inherits every element we want to check against.
Then, when provided with an argument, we inspect whether it is a base of our class using `std::is_base_of`, subsequently determining whether the argument is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, the initial list of arguments for `SetContains` must be nonrepetitive (hence the word `Set` in the name).

Since fundamental types are not inheritable, we pack every argument into a wrapper--in this case, `std::type_identity`--before the inheritance.

```C++
template<typename...Elements>
struct SetContains
: public std::type_identity<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                std::type_identity<Inspecting>,
                SetContains
            >::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/set_contains/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/set_contains.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/set_contains.test.hpp)
