<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::InvokeReturnAs`

<p style='text-align: right;'><a href="../../concepts.md#functivore-invoke-return-as">To Index</a></p>

## Description

`Functivore::InvokeReturnAs` accepts a function-like type, a possible return type, and a list of argument type.
It returns true if the function-like type invoked by the argument types returns the possible return type.

## Structure

```C++
template<typename>
concept InvokeReturnAs = REQUIREMENT;
```

## Implementation

```C++
template<typename Fun, typename Result, typename...Args>
concept InvokeReturnAs
= std::same_as<typename GetInvokeReturnType<Fun>::template Mold<Args...>, Result>;
```

Note that `std::is_invocable_r` does not work with volatile lvalue reference qualified(`volatile &`) member functions.

```C++
struct FO
{ void operator()() volatile & {} };

// This will fail.
 static_assert(std::same_as<std::invoke_result_t<void() volatile &>, void>);
```

The following code will not compile:

```C++
// This will fail as well.
static_assert(InvokeResultIn<FO, void>);
```

## Links

- [Example code](../../../code/facilities/concepts/functivore/invoke_return_as/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/concepts/invoke_return_as.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/invoke_return_as.test.hpp)
