# Todo

## Oops

I thought I could finish the documentation in about a week. This is not the case now.

I have to admit that I never thought of C++ templates as a built-in functional programming language. After all, I knew nothing about functional programming except a few things I read here and there.
My intuition for templates was the polynomial algebra instead of lambda calculus since `template<template<typename>>` looks like $x^2$ to me. However, it didn't get me very far.
A couple of days ago, I read [CppMl's tutorial](https://github.com/ZigaSajovic/CppML/blob/master/docs/index.md).
It presented some interesting ideas about functional programming.
I started to read a book about Haskell and realized what I was doing in this library was essentially currying. Take `Fun` as an example:

```c++
Fun :: template<typename...> -> template<template<typename...> class...> -> template<auto..> -> template<template<auto...> class...>
Fun Elements... Containers... Variables... Sequences... = True
```

Here, we think of template-head as types and parameter packs as parameters.

I am not sure if this idea is useful at all since template-head is much less flexible than types in Purescript or Haskell. Nonetheless, I will spend some time studying Haskell and finish Conceptrodon afterward.

## Halt

- Add more explanations for the mechanics of composition.
- Finish documentation.
- Add more tests for composition.
- Add convenience headers for each namespace.
- Add installation instructions for other systems.
- Add speed tests against kvasir::mpl.
- Develop a GCC-compatible version of the library.

## Maybe

- Use macro to reimplement Trip and Trek for maintainability.
- Change the structure of Memorize to conform to rules better.
