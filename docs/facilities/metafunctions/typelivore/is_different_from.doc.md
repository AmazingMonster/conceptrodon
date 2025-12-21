<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferentFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-different-from">To Index</a></p>

## Description

`Typelivore::IsDifferentFrom` accepts a element and returns a function.

When invoked by an argument, the function returns true if the argument differs from the element and returns false if otherwise.

<pre><code>   E
-> Arg
-> Arg `different from` E ?
   true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsDifferentFrom
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
using Metafunction = IsDifferentFrom<int>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(!Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename Target>
struct IsDifferentFrom
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {false}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/is_different_from/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/is_different_from.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/is_different_from.test.hpp)
