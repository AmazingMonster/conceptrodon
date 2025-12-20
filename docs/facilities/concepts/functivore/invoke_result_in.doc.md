<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::InvokeResultIn`

<p style='text-align: right;'><a href="../../concepts.md#functivore-invoke-result-in">To Index</a></p>

## Description

`Functivore::InvokeResultIn` accepts a function-like type, a possible return type, and a list of argument type.
It returns true if the function-like type invoked by the argument types returns the possible return type.
If the function-like type is a pointer to a member function, then the first argument shall be the corresponding object type.

## Structure

```C++
template<typename>
concept InvokeResultIn = REQUIREMENT;
```

## Implementation

```C++
template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= Mouldivore::Confess<std::is_invocable_r, Result, Fun, Args...>;
```

Note that `std::is_invocable_r` does not work with volatile lvalue reference qualified(`volatile &`) member functions.

```C++
struct FO;

// This will fail.
static_assert(std::is_invocable_r_v<void, void(FO::*) () volatile &, FO>);
```

The following code will not compile:

```C++
static_assert(InvokeResultIn<void(FO::*) () volatile &, void, FO>);
```

## Links

- [Example code](../../../code/facilities/concepts/functivore/invoke_result_in/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/concepts/invoke_result_in.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/invoke_result_in.test.hpp)
