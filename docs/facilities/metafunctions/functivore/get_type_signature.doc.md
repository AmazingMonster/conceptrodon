<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#functivore-get-type-signature">To Index</a></p>

## Description

`Functivore::GetTypeSignature` accepts a function-like type and returns its type signature.

## Type Signature

```Haskell
GetTypeSignature
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using GetTypeSignature = RESULT;
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
static_assert(std::same_as<GetTypeSignature<decltype(fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<AbominableFun>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<decltype(FunAddr)>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<decltype(&Tester::fun)>, SupposedTypeSignature>);
static_assert(std::same_as<GetTypeSignature<FO>, SupposedTypeSignature>);
```

## Implementation

The implementation of `GetTypeSignature` relies on the metafunction [`TypicalGetTypeSignature`](./typical_get_type_signature.doc.md), which is implemented by dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template<typename...Args>
using GetTypeSignature = TypicalGetTypeSignature<Args...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/get_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_type_signature.test.hpp)
