# Conceptrodon
A C++20 metaprogramming library focusing on composition and continuation.

## Introduction
The goal of this library is to make metafunction composition simple and natural.

Both **boost::mp11** and **kvasir::mpl** contain a function called 'compose.' It takes a variadic pack of metafunctions and uses the result from the previous function to invoke the next one.
Namely, `mp_compose<F1, F2, …​, Fn>::fn<T…​>` is `Fn<…​F2<F1<T…​>>…​>`. However, since we still don't have a universal template parameter token, signatures of `F1...` must be specified.
Regarding **boost::mp11** and **kvasir::mpl**, `F1...` can only take type arguments, which means many functions in both libraries are not composable.  

This library expands the idea of 'quoted metafunction.' By taking arguments in steps, it groups commonly used functions together based on their signatures, creating better candidates for compositions.

## Implementation
This library mainly handles four types of signatures:
- *Mold*, which has signature `template<typename...>`.
- *Page*, which has signature `template<auto...>`.
- *Road*, which has signature `template<template<typename...> class...>`.
- *Rail*, which has signature `template<template<auto...> class...>`.

These identifiers are deployed inside a metafunction to take corresponding arguments. For example, assuming we plan to pass `int`, `std::tuple`, `std::index_sequence` to function *Fun*:
1. The function itself can always take a kind of argument. we let *Fun* take types and pass `int` to *Fun*: `Fun<int>`.
2. Since the next parameter(`std::tuple`) is corresponding to *Road*(`template<template<typename...> class...>`), we pass it to *Road*: `Fun<int>::Road<std::tuple>`.
3. The last parameter(`std::index_sequence`) is corresponding to *Rail*(`template<template<auto...> class...>`), we pass it to *Rail*: `Fun<int>::Road<std::tuple>::Rail<std::index_sequence>`.

More details can be found in [*./conceptrodon/EXAMPLAR.hpp*](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/EXEMPLAR.hpp)

Most functions in this library are tailored to fit this pattern. Since the inner structures of functions are predictable, different signatures can be composed by invoking member templates corresponding to the signature. Examples can be found in:
- [*./tests/composition/mouldivore/trip.test.hpp*](https://github.com/AmazingMonster/conceptrodon/blob/main/tests/unit/mouldivore/trip.test.hpp)
- [*./tests/unit/mouldivore/trek.test.hpp*](https://github.com/AmazingMonster/conceptrodon/blob/main/tests/composition/mouldivore/trek.test.hpp)

[TODO: Add More Explanations]

## Observation
*Mold* can be further abstracted as the set of all metafunctions of signature `template<typename...>`. The same applies to *Road*, except the corresponding signature becomes `template<template<typename...> class...>`. Function *Fun* then turns into a map from set *Mold* to set *Road*. In other words, we are making maps from function to function by taking arguments in steps.

If we reverse the order of *Road* and *Fun* and call the new function *FunReversed*, we can invoke it by `FunReversed<std::tuple>::Mold<int>::Rail<std::index_sequence>`. *FunReversed* is then a map from set *Road* to set *Mold*. The result will be the same as before. In conclusion, there is a loose correspondence between 'maps from set *Mold* to set *Road*' and 'maps from set *Road* to set *Mold*.' 
 
This library is structured according to these ideas.

## Structure
This library contains 6 main namespaces:
- *Typelivore*. It contains functions of signature `template<typename...>` (that output a function of signature `template<template<typename...> class...>`).
- *Mouldivore*. It contains functions of signature `template<template<typename...> class...>` (that output functions of signature `template<typename...>`).
- *Varybivore*. It contains functions of signature `template<auto...>` (that output a function of signature `template<template<auto...> class...>`).
- *Pagelivore*. It contains functions of signature `template<template<auto...> class...>` (that output functions of signature `template<auto...>`).
- *Roadrivore*. It contains functions of signature `template<template<template<typename...> class...> class...>`.
- *Raillivore*. It contains functions of signature `template<template<template<auto...> class...> class...>`.

Even though parenthesized statements are not followed strictly, these rules guide most decision-making.

A few more namespaces are provided to handle functions that cannot fit in the namespaces above naturally.
- *Cotanivore*. Functions in this namespace take arguments of form `Container<Elements...>`, where `Container` has signature `template<typename...>` and `Elements...` are types.
- *Sequnivore*. Functions in this namespace take arguments of form `Sequence<Variables...>`, where `Sequence` has signature `template<auto...>` and `Variables...` are values.
- *Warehivore*. Functions in this namespace take arguments of form `Warehouse<Containers...>`, where `Warehouse` has signature `template<template<typename...> class...>` and `Containers...` have signature *template<typename...>*.
- *Stockivore*. Functions in this namespace take arguments of form `Stockroom<Sequences...>`, where `Stockroom` has signature `template<template<auto...> class...>` and `Sequences...` have signature `template<auto...>`.
- *Omennivore*. It contains functions that do not fit in the namespaces above.

The library is further divided according to dependency. Functions in *./conceptrodon/descend/descend* depend on facilities in *./conceptrodon/descend*, while functions in *./conceptrodon/descend* depend on facilities in *./conceptrodon*.

## Speed
Many functions are tested against **boost::mp11**. If the function being tested is slower than its counterpart, the implementation from **boost::mp11** is used. Therefore, This library is generally faster than **boost::mp11**. Tests can be found in *tests/unit*. 

## Limitation
This library is only tested with Clang. GCC won't compile since explicit specialization inside a struct is still unavailable. Workarounds exist, and a GCC-compatible version is planned for the future.

## Future
Descriptions will be gradually added to each function. A GCC-compatible version will be added after.

## Install
Since this is a header-only library, you can download it to your project and use it like your own headers.  

In directory *./conceptrodon*, including headers named after namespaces consequently includes all functions within the corresponding namespaces, while including *conceptrodon.hpp* includes everything inside the library.

You can also install it using CMake:

#### Windows
1. Download the library.
2. Open Developer Command Prompt that comes with Visual Studio. Redirect to the library folder. Generate a project buildsystem using CMake:
```
cmake -S . -B "Where to build"
```
3. Redirect to the build directory that you specified after -B. Run command:
```
cmake --install . --prefix "Where to install"
```
[TODO: Add instructions for other systems]

After installation, in the CMakeList.txt of your project, Add:
```
find_package(Conceptrodon REQUIRED CONFIG)
target_link_libraries(YourProject PRIVATE Conceptrodon::Contents)
```
Now, you can include what you need in your project.

    
