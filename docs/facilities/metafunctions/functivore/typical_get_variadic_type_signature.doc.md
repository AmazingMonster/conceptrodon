<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::TypicalGetVariadicTypeSignature`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typical_get_variadic_type_signature">To Index</a></p>

## Description

`Functivore::TypicalGetVariadicTypeSignature` accepts a function-like type and returns its variadic type signature via the alias member `type`.

## Type Signature

```Haskell
TypicalGetVariadicTypeSignature
 :: typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalGetVariadicTypeSignature
{
    using type = RESULT;
};
```

## Examples

We will extract the variadic type signatures from several function-like types.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }
inline int variadic_fun(int, int*...){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;
using VariadicAbominableFun = int(int, int*...) const;

/**** function pointers ****/
inline auto FunAddr { &fun };
inline auto VariadicFunAddr { &variadic_fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
    inline int variadic_fun(int, int*...) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

struct VariadicFO
{
    int operator()(int, int*...) const { return 0; }
};

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);
using SupposedVariadicTypeSignature = int(int, int*...);

/**** Tests ****/
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<AbominableFun>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(FunAddr)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<FO>::type, SupposedTypeSignature>);

static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(variadic_fun)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<VariadicAbominableFun>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(VariadicFunAddr)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<decltype(&Tester::variadic_fun)>::type, SupposedVariadicTypeSignature>);
static_assert(std::same_as<TypicalGetVariadicTypeSignature<VariadicFO>::type, SupposedVariadicTypeSignature>);
```

## Implementation

The implementation of `TypicalGetVariadicTypeSignature` relies on dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template<typename Fn>
struct TypicalGetVariadicTypeSignature
{ using type = Analyzer<Fn>::variadic_type_signature;};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/typical_get_variadic_type_signature/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_variadic_type_signature.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/typical_get_variadic_type_signature.test.hpp)
