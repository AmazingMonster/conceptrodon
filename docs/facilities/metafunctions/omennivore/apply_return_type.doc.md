<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::ApplyReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-apply-return-type">To Index</a></p>

## Description

`Omennivore::ApplyReturnType` accepts a type and returns a metafunction.

When invoked, the metafunction yields a function type with the previously provided type as the return type and its arguments as parameter types.

<pre><code>   Ret
-> Args...
-> Ret(Args...)</code></pre>

## Type Signature

```Haskell
ApplyReturnType
 :: typename...
 -> template<typename...>
```

## Structure

```C++
template<typename>
struct ApplyReturnType
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will create a function type with `int` being the return type and `int, int*, int**` being the parameter types.

```C++
/**** SupposedResult ****/
using SupposedResult = int(int, int*, int**);

/**** Tests ****/
static_assert
(
    std::same_as
    <
        ApplyReturnType<int>::Mold<int, int*, int**>,
        int(int, int*, int**)
    >
);
```

## Implementation

```C++
template <typename Ret>
struct ApplyReturnType
{
    template<typename...Args>
    using Mold = Ret(Args...);
};
```

## Links

- [Example](../../../code/facilities/metafunctions/omennivore/apply_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/omennivore/apply_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/omennivore/apply_return_type.test.hpp)
