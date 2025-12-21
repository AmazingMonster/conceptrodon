<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsNonoverloadedFunctionObject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_nonoverloaded_function_object">To Index</a></p>

## Description

`Functivore::IsNonoverloadedFunctionObject` accepts a function-like type. It returns true if the type is a function object whose function call operator is not overloaded and returns false if otherwise.

## Type Signature

```Haskell
IsNonoverloadedFunctionObject
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsNonoverloadedFunctionObject
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** Testers ****/
struct NonoverloadedFO
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
};

struct OverloadedFO
{
    int operator()(int const, double&...) const volatile && noexcept { return 0; }
    int operator()(double const, double&...) const volatile && noexcept { return 0; }
};

/**** Tests ****/
static_assert(IsNonoverloadedFunctionObject<NonoverloadedFO>::value);
static_assert(not IsNonoverloadedFunctionObject<OverloadedFO>::value);
```

## Implementation

`IsNonoverloadedFunctionObject` is implemented by attempting to access the address of the object's call operator.

```C++
requires {&FO::operator()};
```

The validness of such an expression indicates that the call operator exists and the access is not ambiguous, meaning the call operator is not overloaded.

```C++
template<typename>
struct IsNonoverloadedFunctionObject
{
    static constexpr bool value {false};
};

template<typename FO>
requires requires {&FO::operator();}
struct IsNonoverloadedFunctionObject<FO>
{
    static constexpr bool value {true};
};

template<typename FO>
constexpr bool IsNonoverloadedFunctionObject_v
{
    requires {&FO::operator();}
};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_nonoverloaded_function_object/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/is_nonoverloaded_function_object.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_nonoverloaded_function_object.test.hpp)
