<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSameAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-same-as">To Index</a></p>

## Description

`Typelivore::IsSameAs` accepts a element and returns a function.

When invoked by an argument, the function returns true if the argument is the same as the element and returns false if otherwise.

<pre><code>   Target
-> E
-> E `same as` Target ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSameAs
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsSameAs
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = IsSameAs<int>
::Mold<Args...>;

/**** Tests ****/
static_assert(!Metafunction<int*>::value);
static_assert(Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename Target>
struct IsSameAs
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {false}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {true}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_same_as/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/is_same_as.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_same_as.test.hpp)
