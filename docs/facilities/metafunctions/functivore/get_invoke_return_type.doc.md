<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetReturnType`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_invoke_return_type">To Index</a></p>

## Description

`Functivore::GetInvokeReturnType` accepts a function-like type and returns a metafunction.

When invoked by a list of argument types, the function returns the return type of the function-like type called by objects of these argument types.

## Type Signature

```Haskell
GetInvokeReturnType
 :: typename...
 :: template<typename...>
```

## Structure

```C++
template<typename...>
struct GetInvokeReturnType
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

We will extract the return types from several function-like types. Note that `GetInvokeReturnType` yields the correct answer even though `FO::operator()` is overloaded.

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
    double operator()(int, int*, int**) const { return 0; }
};

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<GetInvokeReturnType<decltype(fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<AbominableFun>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(FunAddr)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<decltype(&Tester::fun)>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*>, SupposedReturnType>);
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**>, double>);
```

Note that since `std::invoke_result` does not work with volatile lvalue reference qualified(`volatile &`) member functions, the following code will not compile:

```C++
// This will fail.
static_assert(std::same_as<std::invoke_result_t<FO, int, int*, int**, int***>, void>);

// This will fail, too.
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**, int***>, void>);
```

## Implementation

```C++
template<typename Fn>
struct GetInvokeReturnType
{
    template<typename...Args>
    using Mold = std::invoke_result_t<GetVariadicTypeSignature<Fn>, Args...>;
};

template<typename Fn>
requires std::is_class_v<Fn>
struct GetInvokeReturnType<Fn>
{
    template<typename...Args>
    using Mold = std::invoke_result_t<Fn, Args...>;
};
```

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_invoke_return_type/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/functivore/get_invoke_return_type.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_invoke_return_type.test.hpp)
