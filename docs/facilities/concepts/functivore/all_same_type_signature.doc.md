<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AllSameTypeSignature`

<p style='text-align: right;'><a href="../../concepts.md#functivore-all-same-type-signature">To Index</a></p>

## Description

`Functivore::AllSameTypeSignature` accepts a list of function-like types.
It returns true if all of them have the same type signature.

## Structure

```C++
template<typename...>
concept AllSameTypeSignature = REQUIREMENT;
```

## Implementation

```C++
template<typename FirstArg, typename...Others>
concept AllSameTypeSignature
= (...&&std::same_as<GetTypeSignature<FirstArg>, GetTypeSignature<Others>>);
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/all_same_type_signature.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/all_same_type_signature.test.hpp)
