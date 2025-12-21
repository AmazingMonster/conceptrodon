<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::SameTypeSignatureAs`

<p style='text-align: right;'><a href="../../concepts.md#functivore-same-type-signature-as">To Index</a></p>

## Description

`Functivore::SameTypeSignatureAs` accepts two function-like types.
It returns true if they have the same type signature.

## Structure

```C++
template<typename, typename>
concept SameTypeSignatureAs = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg, typename Given>
concept SameTypeSignatureAs = std::same_as<GetTypeSignature<Arg>, GetTypeSignature<Given>>;
```

## Links

- [Source code](../../../../conceptrodon/metafunctions/functivore/concepts/same_type_signature_as.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/same_type_signature_as.test.hpp)
