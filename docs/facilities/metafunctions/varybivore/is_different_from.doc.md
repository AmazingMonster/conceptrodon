<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferentFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-different-from">To Index</a></p>

## Description

`Varybivore::IsDifferentFrom` accepts a variable and returns a function.

When invoked by an argument, the function returns true if the argument differs from the variable and returns false if otherwise.

<pre><code>   V
-> Arg
-> Arg `different from` V ?
   true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct IsDifferentFrom
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = IsDifferentFrom<1>
::Page<Args...>;

/**** Tests ****/
static_assert(Metafunction<1.0>::value);
static_assert(Metafunction<0>::value);
static_assert(! Metafunction<1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto Target>
struct IsDifferentFrom
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {false}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_different_from/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/varybivore/is_different_from.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_different_from.test.hpp)
