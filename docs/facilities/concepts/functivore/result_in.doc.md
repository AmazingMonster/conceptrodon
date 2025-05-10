<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::ResultIn`

<p style='text-align: right;'><a href="../../concepts.md#functivore-result-in">To Index</a></p>

## Description

`Functivore::ResultIn` accepts a function-like type and a possible return type.
It returns true if the function-like type returns the possible return type.

## Structure

```C++
template<typename>
concept ResultIn = REQUIREMENT;
```

## Implementation

```C++
template<typename Fun, typename Result>
concept ResultIn
= std::same_as<GetReturnType<Fun>, Result>;
```

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/result_in.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/result_in.test.hpp)
