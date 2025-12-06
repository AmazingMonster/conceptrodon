<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::AreSameVariadicTypeSignatureAs`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#are_same_variadic_type_signatrue_as">To Index</a></p>

## Description

`Functivore::AreSameVariadicTypeSignatureAs` accepts a function-like type and returns a metafunction.

When invoked by a list of function-like types, the metafunction returns true if their type signatures, including ellipsis, are the same as that of the previously provided function-like type and returns false if otherwise.

## Type Signature

```Haskell
AreSameVariadicTypeSignatureAs
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename>
struct AreSameVariadicTypeSignatureAs
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value{RESULT};
    };
};
```

## Examples

We will compare a few function-like types to `int(int, int*, ...)`.

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

/**** Metafunction ****/
using Metafunction_0 = AreSameVariadicTypeSignatureAs<int(int, int*)>;
using Metafunction_1 = AreSameVariadicTypeSignatureAs<int(int, int*...)>;

/**** Tests ****/
static_assert(Metafunction_0::Mold_v<decltype(fun)>);
static_assert(Metafunction_0::Mold_v<decltype(FunAddr)>);
static_assert(Metafunction_0::Mold_v<AbominableFun>);
static_assert(Metafunction_0::Mold_v<decltype(&Tester::fun)>);
static_assert(Metafunction_0::Mold_v<FO>);
static_assert(! Metafunction_0::Mold_v<VariadicFO>);
static_assert
(
    Metafunction_0::Mold_v
    <
        decltype(fun),
        decltype(FunAddr),
        AbominableFun,
        decltype(&Tester::fun)
    >
);
static_assert
(
    ! Metafunction_0::Mold_v
    <
        decltype(variadic_fun),
        decltype(fun),
        decltype(FunAddr),
        AbominableFun,
        decltype(&Tester::fun)
    >
);

static_assert(Metafunction_1::Mold_v<decltype(variadic_fun)>);
static_assert(Metafunction_1::Mold_v<decltype(VariadicFunAddr)>);
static_assert(Metafunction_1::Mold_v<VariadicAbominableFun>);
static_assert(Metafunction_1::Mold_v<decltype(&Tester::variadic_fun)>);
static_assert(Metafunction_1::Mold_v<VariadicFO>);
static_assert(! Metafunction_1::Mold_v<FO>);
```

## Implementation

The implementation of `AreSameVariadicTypeSignatureAs` relies on dissecting the structure of the function-like types into parameter types and return types using the metafunction [`Analyzer`](./analyzer.doc.md).

```C++
template <typename Known>
struct AreSameVariadicTypeSignatureAs
{
    template<typename...Unknowns>
    struct ProtoMold
    {
        static constexpr bool value
        {
            (...&&(
                std::is_same_v
                <
                    typename Analyzer<Unknowns>::variadic_type_signature,
                    typename Analyzer<Known>::variadic_type_signature
                >
            ))
        };
    };

    template<typename...Args>
    using Mold = ProtoMold<Args...>;

    template<typename...Unknowns>
    static constexpr bool Mold_v = Mold<Unknowns...>::value;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/are_same_variadic_type_signature_as/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/are_same_variadic_type_signature_as.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/are_same_variadic_type_signature_as.test.hpp)
