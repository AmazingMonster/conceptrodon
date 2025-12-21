<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::SameVariadicTypeSignatureAs`

<p style='text-align: right;'><a href="../../concepts.md#functivore-same-variadic-type-signature-as">To Index</a></p>

## Description

`Functivore::SameVariadicTypeSignatureAs` accepts two function-like types.
It returns true if they have the same variadic type signature.

## Structure

```C++
template<typename, typename>
concept SameVariadicTypeSignatureAs = REQUIREMENT;
```

## Implementation

```C++
template<typename Arg, typename Given>
concept SameVariadicTypeSignatureAs
= std::same_as<GetVariadicTypeSignature<Arg>, GetVariadicTypeSignature<Given>>;
```

## Links

- [Source code](../../../../conceptrodon/concepts/functivore/same_variadic_type_signature_as.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/same_variadic_type_signature_as.test.hpp)
