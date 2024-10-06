# Conceptrodon
A C++20 metaprogramming library focusing on composition and continuation.

## Introduction
This library is inspired by pipe syntax and aims to create a similar way to compose metafunctions.  

Both **boost::mp11** and **kvasir::mpl** contain a function called 'compose'. It takes a variadic pack of metafunctions and uses the result from the previous function to invoke the next one.
Namely, *mp_compose<F1, F2, …​, Fn>::fn<T…​>* is *Fn<…​F2<F1<T…​>>…​>*. However, since we still don't have a universal template parameter token, signatures of *F1...* must be specified.
In the case of **boost::mp11** and **kvasir::mpl**, *F1...* can only take type arguments, which means many functions in both libraries are not composable.  

To resolve this, Conceptrodon expands the idea of 'quoted metafunction'. By using member templates dividing the duty of taking arguments, Conceptrodon groups commonly used functions together based on their signatures, which subsequently creates cleaner call sites and better candidates for compositions:

## Implementation
This library mainly handles four types of signatures:
- *Mold*, which has signature *template<typename...>*.
- *Page*, which has signature *template<auto...>*.
- *Road*, which has signature *template<template<typename...> class...>*.
- *Rail*, which has signature *template<template<auto...> class...>*.

These identifiers are deployed inside a metafunction to take corresponding arguments. For example, assuming we plan to pass *int*, *std::tuple*, *std::index_sequence* to function *Fun*:
1. The function itself can always take a kind of argument. we let *Fun* take types and pass *int* to *Fun*: *Fun\<int\>*.
2. Since the next parameter(*std::tuple*) is corresponding to *Road*(*template<template<typename...> class...>*), we pass it to *Road*: *Fun\<int\>::Road\<std::tuple\>*.
3. The last parameter(*std::index_sequence*) is corresponding to *Rail*(*template<template<auto...> class...>*), we pass it to *Rail*: *Fun\<int\>::Road\<std::tuple\>::Rail\<std::index_sequence\>*.

Every function in this library is tailored to fit this pattern. Since the inner structures of functions are fixed, composing various signatures is now possible[TODO: Add examples].

## Intuition
Let's take another look at *Mold*. It can be thought of as the set of all metafunctions with the signature *template<typename...>*. The same is true for *Road*, while the corresponding signature becomes *template<template<typename...> class...>*. Function *Fun* then turns into a map from set *Mold* to set *Road*. In other words, by taking arguments in steps('quoted metafunction' in **boost::mp11** is an example of this), we are making maps from functions to functions.

If we reverse the order of *Road* and *Fun*, say the new function is called *FunReversed*, we can invoke it by *FunReversed\<std::tuple\>::Mold\<int\>::Rail\<std::index_sequence\>* to get the same result as before. *FunReversed* is then a map from set *Road* to set *Mold*. In conclusion, there is a loose correspondence between all the maps from set *Mold* to set *Road* and all the maps from set *Road* to set *Mold*. 
 
This library is structured according to these ideas.

## Structure
This library contains four main namespaces:
- *Typelivore*. It contains functions that take type arguments and output a function of signature *template<template<typename...> class...>*.
- *Mouldivore*. It contains functions of signature *template<template<typename...> class...>* and output functions that take type arguments.
- *Varybivore*. It contains functions that take value arguments and output a function of *signature template<template<auto...> class...>*.
- *Pagelivore*. It contains functions of signature *template<template<auto...> class...>* and output functions that take value arguments.

While there are many exceptions, these rules guide the majority of decision-making. Most functions presented in the library are included in these namespaces. 

A few more namespaces are provided to handle functions that do not naturally fit in one of the above namespaces.
- *Roadrivore*. It contains functions of signature *template<template<template<typename...> class...> class...>*.
- *Raillivore*. It contains functions of signature *template<template<template<auto...> class...> class...>*.
- *Cotanivore*. Functions in this namespace take arguments of form *Container<Elements...>*, where Container has signature *template<typename...>* and *Elements...* are types.
- *Sequnivore*. Functions in this namespace take arguments of form *Sequence<Variables...>*, where Sequence has signature *template<auto...>* and *Variables...* are values.
- *Warehivore*. Functions in this namespace take arguments of form *Warehouse<Containers...>*, where Warehouse has signature *template<template<typename...> class...>* and *Containers...* have signature *template<typename...>*.
- *Stockivore*. Functions in this namespace take arguments of form *Stockroom<Sequences...>*, where Stockroom has signature *template<template<auto...> class...>* and *Sequences...* have signature *template<auto...>*.
- *Omennivore*. It contains functions that do not fit in the namespaces above.

The library is further broken down according to dependency. Functions in *\Conceptrodon\descend\descend* depend on Functions in *\Conceptrodon\descend*. Functions in *\Conceptrodon\descend* depend on Functions in *\Conceptrodon*.

## Speed
Many functions are tested against **boost::mp11**. If the function being tested is slower than its counterpart, the implementation from **boost::mp11** is used. Therefore, This library is generally faster than **boost::mp11**. Tests can be found in *tests/unit*. 

## Limitation
This library is only tested with Clang. It won't work with GCC since GCC still doesn't support explicit specialization inside a struct. There are workarounds and a GCC compatible version is planned in the future.

## Future
Descriptions will be gradually added to each function. A GCC compatible version will be added after..

## Install
Since this is a header-only library, you can download the library and include what you need just like your own headers.  

You can also install it using CMake:

- Windows
 1. Download the library.
 2. Open Developer Command Prompt that comes with Visual Studio. Redirect to the library folder. Generate a project buildsystem using CMake:
    ```
    cmake -S . -B "Where you want to build"
    ```
 3. Redirect to the build directory which you specified after -B. Run command:
    ```
    cmake --install . --prefix "Where you want to install"
    ```
[TODO: Add instructions for other systems]

After installation, in the CMakeList.txt of your own project, Add:
```
find_package(Conceptrodon REQUIRED CONFIG)
target_link_libraries(YourProject PRIVATE Conceptrodon::Contents)
```
Now, you can include what you need in your own project.

    
