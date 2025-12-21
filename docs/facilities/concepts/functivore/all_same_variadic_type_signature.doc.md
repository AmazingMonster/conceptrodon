<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllSameVariadicTypeSignature`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-same-variadic-type-signature">To Index</a></p>

## Description

`Functivore::AllSameVariadicTypeSignature` accepts a list of function-like types.
It returns true if all of them have the same variadic type signature.

## Structure

```C++
template<variadictypename...>
concept AllSameVariadicTypeSignature = REQUIREMENT;
```

## Implementation

```C++
template<typename FirstArg, typename...Others>
concept AllSameVariadicTypeSignature
= (...&&std::same_as<GetVariadicTypeSignature<FirstArg>, GetVariadicTypeSignature<Others>>);
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/all_same_variadic_type_signature.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_same_variadic_type_signature.test.hpp)
