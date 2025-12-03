<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsFunctionPointer`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_function_pointer">To Index</a></p>

## Description

`Functivore::IsFunctionPointer` accepts a funtion-like type. It returns true if the type is a pointer to a function and returns false if otherwise.

## Type Signature

```Haskell
IsFunctionPointer
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsFunctionPointer
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
static_assert(IsFunctionPointer<void(*)()>::value);
static_assert(not IsFunctionPointer<void()>::value);
```

## Implementation

```C++
template<typename>
struct IsFunctionPointer
{
    static constexpr bool value {false};
};

template<typename FP>
struct IsFunctionPointer<FP*>
{
    static constexpr bool value
    {std::is_function_v<FP>};
};

template<typename FP>
constexpr bool IsFunctionPointer_v
{
    IsFunctionPointer<FP>::value
};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_function_pointer/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_function_pointer.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_function_pointer.test.hpp)
