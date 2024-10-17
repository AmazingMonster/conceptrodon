# Todo

## Oops

I thought I could finish the documentation in about a week. This is not the case now.

I have to admit that I never thought of C++ templates as a built-in functional programming language. After all, I knew nothing about functional programming except a few names I picked up here and there.
My intuition for templates was the polynomial algebra instead of lambda calculus since `template<template<typename>>` looks like $x^2$ to me. However, it didn't get me very far.
A couple of days ago, I read [CppMl's tutorial](https://github.com/ZigaSajovic/CppML/blob/master/docs/index.md).
It presented some interesting ideas about functional programming.
I started to read a book about Purescript and realized what I was doing in this library was essentially currying. Take `Fun` as an example:

```c++
Fun :: template<typename...> -> template<template<typename...> class...> -> template<auto..> -> template<template<auto...> class...> -> typename
Fun Elements... Containers... Variables... Sequences... = struct { static constexpr bool value{true}; }
```

Here, we think of template-head as types and parameter packs as parameters.

I am not sure if this idea is useful at all since template-head is much less flexible than types in Purescript or Haskell. Nonetheless, I will spend some time studying Haskell and finish Conceptrodon afterward.

## Halt

- Use macro to reimplement some functions for maintainability.
- Add more functions that are synonymic to Memorize to handle slightly different situations.
- Use Typical\* or Classic\* prefix to rename functions that have members called 'type'
- Change SubMold to M_ld, P_ge, ect.
- Add M_ldTrip, P_geTrip, ect. to compose functions with respect to M_ld, P_ge, ect.
- Add function Restore(for currying)

- Add more explanations for the mechanics of composition.
- Finish documentation.
- Add more tests for composition.
- Add convenience headers for each namespace.
- Add installation instructions for other systems.
- Add speed tests against kvasir::mpl.
- Develop a GCC-compatible version of the library.
