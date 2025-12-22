<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::TypicalGetTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-typical-get-type-signature">To Index</a></p>

## Description

`Functivore::TypicalGetTypeSignature` accepts a function-like type and returns its type signature via the alias member `type`.

## Type Signature

```Haskell
TypicalGetTypeSignature
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalGetTypeSignature
{
    using type = RESULT;
};
```

## Examples

We will extract the type signatures from several function-like types.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);

/**** Tests ****/
static_assert(std::same_as<TypicalGetTypeSignature<decltype(fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<AbominableFun>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<decltype(FunAddr)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<decltype(&Tester::fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<FO>::type, SupposedTypeSignature>);
```

## Implementation

The implementation of `TypicalGetTypeSignature` relies on dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template<typename Fn>
struct TypicalGetTypeSignature
{ using type = Analyzer<Fn>::type_signature;};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/typical_get_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/typical_get_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/typical_get_type_signature.test.hpp)
