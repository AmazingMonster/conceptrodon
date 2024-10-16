# Conceptrodon

A C++20 metaprogramming library focusing on metafunction composition.

## Introduction

The goal of this library is to make metafunction composition simple and natural.

Both [**boost::mp11**](https://www.boost.org/doc/libs/master/libs/mp11/doc/html/mp11.html) and [**kvasir::mpl**](https://github.com/kvasir-io/mpl) contain a function called 'compose.'
It takes a variadic pack of metafunctions and uses the result from the left function to invoke the right one.
Namely, `mp_compose<F1, F2, …​, Fn>::fn<T…​>` is `Fn<…​F2<F1<T…​>>…​>`. However, since we still don't have a universal template parameter token, signatures of `F1...` must be specified.
Regarding **boost::mp11** and **kvasir::mpl**, `F1...` can only take type arguments, which means many functions in both libraries are not composable.  

This library expands the idea of 'quoted metafunctions.' By taking arguments from different categories using dedicated member templates, this library categorizes metafunctions based on their signatures, creating better candidates for composition.

## Implementation

The library mainly uses four types of member templates:

- *Mold*, which has signature `template<typename...>`.
- *Page*, which has signature `template<auto...>`.
- *Road*, which has signature `template<template<typename...> class...>`.
- *Rail*, which has signature `template<template<auto...> class...>`.

These templates are deployed inside a metafunction to take corresponding arguments. For example, assuming we plan to pass `int`, `std::tuple`, `0` and `std::index_sequence` to function *Fun*:

1. The function itself can always take a category of arguments. we let *Fun* take types and pass `int` to *Fun*: `Fun<int>`.
2. `std::tuple` is corresponding to *Road*(`template<template<typename...> class...>`), we pass it to *Road*: `Fun<int>::Road<std::tuple>`.
3. `0` is corresponding to *Page*(`template<auto...>`), we pass it to *Page*: `Fun<int>::Road<std::tuple>::Page<0>`.
4. `std::index_sequence` is corresponding to *Rail*(`template<template<auto...> class...>`), we pass it to *Rail*: `Fun<int>::Road<std::tuple>::Page<0>::Rail<std::index_sequence>`.  

We finalize the structural design of `Fun` as follows:

```c++
template<typename...Elements>
struct Fun
{
    template<template<typename...> class...Containers>
    struct ProtoRoad
    {
        static constexpr bool value {true};

        template<auto...Variables>
        struct ProtoPage
        {
            template<template<auto...> class...Sequences>
            struct ProtoRail
            {
                static constexpr bool value {true};
            };

            template<template<auto...> class...Sequences>
            using Rail = ProtoRail<Sequences...>;
        };

        template<auto...Variables>
        using Page = ProtoPage<Variables...>;
    };

    template<template<typename...> class...Containers>
    using Road = ProtoRoad<Containers...>;
};
```

More details can be found in [*./conceptrodon/EXEMPLAR.hpp*](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/EXEMPLAR.hpp)

All metafunctions in this library are tailored to fit this pattern. This means every *Mold* can be passed to every *Road* as an argument, and every *Page* can be passed to every *Rail* as an argument.
In the previous example, we can pass `Fun` to `Fun<>::Road` and pass `Fun<>::Road<>::Page` to `Fun<>::Road<>::Page<>::Rail`:

```c++
static_assert(Fun<>::Road<Fun>::value);
static_assert(Fun<>::Road<>::Page<>::Rail<Fun<>::Road<>::Page>::value);
```

[Run this snippet in Godbolt.](https://godbolt.org/z/vPhhe7TW3)

Since the structural layout of a metafunction is predictable, different signatures can be composed by high-level functions. Examples can be found in:

- [*./tests/composition/mouldivore/trip.test.hpp*](https://github.com/AmazingMonster/conceptrodon/blob/main/tests/unit/mouldivore/trip.test.hpp)
- [*./tests/unit/mouldivore/trek.test.hpp*](https://github.com/AmazingMonster/conceptrodon/blob/main/tests/composition/mouldivore/trek.test.hpp)

## Observation(oops)

I thought I could finish the documentation in about a week. This is not the case now.

I have to admit that I never thought of C++ templates as a built-in functional programming language. After all, I knew nothing about functional programming except a few names I picked up here and there.
My intuition for templates was the polynomial algebra instead of lambda calculus since `template<template<typename>>` looks like $x^2$ to me. However, it didn't get me very far.
A couple of days ago, I read [CppMl's tutorial](https://github.com/ZigaSajovic/CppML/blob/master/docs/index.md).
It presented some interesting ideas about functional programming.
I started to read a book about Purescript and realized what I was doing in this library was essentially currying. Take `Fun` as an example:

```c++
Fun :: template<typename...> -> template<template<typename...> class...> -> template<auto..> -> template<template<auto...> class...>
Fun Elements... Containers... Variables... Sequences... = True
```

Here, we think of template-head as types and parameter packs as parameters.

I am not sure if this idea is useful at all since template-head is much less flexible than types in Purescript or Haskell. Nonetheless, I will spend some time studying Haskell and finish Conceptrodon afterward.

## Structure

This library mainly contains six namespaces:

- *Typelivore*. It contains functions of signature `template<typename...>` (that output functions of signature `template<template<typename...> class...>`).
- *Mouldivore*. It contains functions of signature `template<template<typename...> class...>` (that output functions of signature `template<typename...>`).
- *Varybivore*. It contains functions of signature `template<auto...>` (that output functions of signature `template<template<auto...> class...>`).
- *Pagelivore*. It contains functions of signature `template<template<auto...> class...>` (that output functions of signature `template<auto...>`).
- *Roadrivore*. It contains functions of signature `template<template<template<typename...> class...> class...>`.
- *Raillivore*. It contains functions of signature `template<template<template<auto...> class...> class...>`.

Even though parenthesized statements are not followed strictly, these rules guide most decision-making.

A few more namespaces are introduced to handle functions that cannot fit in the above namespaces naturally.

- *Cotanivore*. Functions in this namespace take arguments of form `Container<Elements...>`, where `Container` has signature `template<typename...>` and `Elements...` are types.
- *Sequnivore*. Functions in this namespace take arguments of form `Sequence<Variables...>`, where `Sequence` has signature `template<auto...>` and `Variables...` are values.
- *Warehivore*. Functions in this namespace take arguments of form `Warehouse<Containers...>`, where `Warehouse` has signature `template<template<typename...> class...>` and `Containers...` have signature *template<typename...>*.
- *Stockivore*. Functions in this namespace take arguments of form `Stockroom<Sequences...>`, where `Stockroom` has signature `template<template<auto...> class...>` and `Sequences...` have signature `template<auto...>`.
- *Omennivore*. It contains functions that do not fit in the namespaces above.

The library is further divided according to dependency. Functions in '*./conceptrodon/\*/descend*' depend on facilities in '*./conceptrodon/\**.'
For example, functions in '*./conceptrodon/descend/descend*' depend on facilities in '*./conceptrodon/descend*,' while functions in '*./conceptrodon/descend*' depend on facilities in '*./conceptrodon*.'

## Speed

Many functions are tested against **boost::mp11**. If the function being tested is slower than its counterpart, the implementation from **boost::mp11** is used. Therefore, This library is generally faster than **boost::mp11**. Tests can be found in *tests/unit*.

A few functions are tested against **kvasir::mpl**. The tested functions are optimized similarly to before. More tests against **kvasir::mpl** are planned for the future.

## Limitation

This library is only tested with Clang. GCC won't compile since explicit specialization inside a struct is still unavailable. Workarounds exist, and a GCC-compatible version is planned for the future.

## Future

Each function will be given a description. A GCC-compatible version of the library will be added after. Tests against **kvasir::mpl** will be gradually added.

## Install

Since this is a header-only library, you can download it to your project and use it like your own headers.  

[In directory '*./conceptrodon*,' including headers named after namespaces consequently includes all functions within the corresponding namespaces, while including *conceptrodon.hpp* includes everything inside the library. (Not true at the moment; those headers will be added soon)]

You can also install it using CMake:

### Windows

1. Download the library.

2. Open Developer Command Prompt that comes with Visual Studio. Redirect to the library folder. Generate a project buildsystem using CMake:

```
cmake -S . -B "Where to build"
```

3. Redirect to the build directory you specified after '-B' earlier. Run command:

```
cmake --install . --prefix "Where to install"
```

After installation, add the install directory you specified after '--prefix' to CMAKE_PREFIX_PATH in your project's CMakeCache.txt.  

In the CMakeList.txt of your project, Add:

```cmake
find_package(Conceptrodon REQUIRED CONFIG)
target_link_libraries(YourProject PRIVATE Conceptrodon::Contents)
```

Now, you can include what you need in your project.

## Links

[Documentation for Conceptrodon(WIP)](https://github.com/AmazingMonster/conceptrodon/blob/main/docs/index.md)
