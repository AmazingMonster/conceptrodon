<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetVariadicTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_variadic_type_signature">To Index</a></p>

## Description

`Functivore::GetVariadicTypeSignature` accepts a function-like type and returns its variadic type signature.

## Type Signature

```Haskell
GetVariadicTypeSignature
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using GetVariadicTypeSignature = RESULT;
```

## Examples

We will extract the variadic type signature from several function-like type.

```C++
/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...)>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using variadic_type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args..., ...) const>
{
    using variadic_type_signature = Ret(Args..., ...);
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn> {};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn> {};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())> {};

/**** TypicalGetVariadicTypeSignature ****/
template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};
```

## Implementation

The implementation of `GetVariadicTypeSignature` relies on the metafunction [`TypicalGetVariadicTypeSignature`](./typical_get_variadic_type_signature.doc.md), which is implemented by dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template<typename...Args>
using GetVariadicTypeSignature = TypicalGetVariadicTypeSignature<Args...>::type;
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_variadic_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/get_variadic_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_variadic_type_signature.test.hpp)
