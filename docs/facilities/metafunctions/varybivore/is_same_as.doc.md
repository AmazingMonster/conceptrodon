<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSameAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-same-as">To Index</a></p>

## Description

`Varybivore::IsSameAs` accepts a variable and returns a function.

When invoked by an argument, the function returns true if the argument is the same as the variable and returns false if otherwise.

<pre><code>   Target
-> Variable
-> Variable `same as` Target ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSameAs
 :: auto...
 -> auto...
 -> auto
```

## Structure

```C++
template<auto>
struct IsSameAs
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

```C++
/**** Metafunction ****/
template<auto...Args>
using Metafunction = IsSameAs<1>
::Page<Args...>;

/**** Tests ****/
static_assert(!Metafunction<1.0>::value);
static_assert(Metafunction<1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto Target>
struct IsSameAs
{
    template<auto Variable>
    struct ProtoPage
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Variable` is deduced as `Target`.
    template<>
    struct ProtoPage<Target>
    { static constexpr bool value {true}; };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Args>
    static constexpr auto Page_v 
    {ProtoPage<Args...>::value};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_same_as/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_same_as.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_same_as.test.hpp)
