# Metafunctions

This document will introduce every function of the library.

## Transport Functions

These functions work as holders for arguments.
They are similar to `boost::mp11::mp_list` but with member templates that transport arguments to user-provided functions.
They are directly placed in the namespace `Conceptrodon` for easy access.

| Function | Parameter Signature | Transport members |
|:-|:-|:-|
| Capsule | `typename` | `Road` & `UniRoad` |
| Shuttle | `auto` | `Rail` & `UniRail` |
| Reverie | `template<typename...>` | `Flow` & `UniFlow` |
| Phantom | `template<auto...>` | `Sail` & `UniSail` |
| Forlorn | <code>template<template<typename...>&nbsp;class...></code> | `Snow` & `UniSnow` |
| Travail | <code>template<template<auto...>&nbsp;class...></code> | `Hail` & `UniHail` |
| Lullaby | <code>template<template<template<typename...>&nbsp;class...>&nbsp;class...></code> | `Lull` & `UniLull` |
| Halcyon | <code>template<template<template<auto...>&nbsp;class...>&nbsp;class...></code> | `Calm` & `UniCalm` |
| Pursuit | <code>template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Hope` & `UniHope` |
| Persist | <code>template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Will` & `UniWill` |
| Morning | <code>template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Glow` & `UniGlow` |
| Sunrise | <code>template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Dawn` & `UniDawn` |
| Arcadia | <code>template<template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> ||
| Nirvana | <code>template<template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> ||

## Identity Functions

Each of these functions can only accept one argument.
The argument can be retrieved through a member.
The primary use of identity functions is to turn values or templates into types.
These functions are directly placed in the namespace `Conceptrodon` for easy access.

Since std::type_identity already exists, the identity function for types is omitted.

| Function | Parameter Signature | Retriever Member |
|:-|:-|:-|
| std::type_identity | `typename` | `type` |
| Monotony | `auto` | `value` |
| Emissary | `template<typename...>` | `Mold` |
| Diplomat | `template<auto...>` | `Page` |
| Delegacy | <code>template<template<typename...>&nbsp;class...></code> | `Road` |
| Legation | <code>template<template<auto...>&nbsp;class...></code> | `Rail` |

## Utilities

These templates are not considered functions by this library. They are introduced to facilitate various programming techniques. They are part of this library's interface and are placed in the namespace `Conceptrodon` for easy access.

<table>
    <thead>
        <tr>
            <th>Name</th>
            <th>Parameter Signature</th>
            <th>Demonstration of the technique</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Label</td>
            <td><code>typename, auto</code></td>
            <td  rowspan=4>
                <ul>
                    <li><a href="https://youtu.be/LfOh0DwTP00?list=PLbylzvxDYXicFnd_E34j8D9dU7a9ArBYM&t=2048">The Nth Element: A Case Study - Kris Jusiak</a>
                    <li><a href="https://github.com/StarQTius/Unpadded/blob/unstable-v2/include/upd/detail/variadic/leaf.hpp">upd::detail::variadic::aggregated_leaves</a>
                    <li><a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/typelivore/amid.hpp">Conceptrodon::Typelivore::Amid</a>
                </ul>
            </td>
        </tr>
        <tr>
            <td>Stamp</td>
            <td><code>auto, auto</code></td>
        </tr>
        <tr>
            <td>Totem</td>
            <td><code>template&lttypename...&gt, auto</code></td>
        </tr>
        <tr>
            <td>Badge</td>
            <td><code>template&ltauto...&gt, auto</code></td>
        </tr>
        <tr>
            <td>Prefix</td>
            <td><code>typename, auto</code></td>
            <td>
                <ul>
                    <li><a href="https://youtu.be/LfOh0DwTP00?list=PLbylzvxDYXicFnd_E34j8D9dU7a9ArBYM&t=1494">The Nth Element: A Case Study - Kris Jusiak</a>
                    <li><a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/microbiota/typella/fore.hpp">Conceptrodon::typella::Fore</a><br>(used to define <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/typelivore/front.hpp">Conceptrodon::typelivore::Front</a>)
        </tr>
    </tbody>
</table>

## Symbols

These templates or instantiations of these templates act as commands when passing to a function. They are placed in the namespace Conceptrodon for easy access.

| Name | Parameter Signature | Purpose |
|:-|:-|:-|
| Peg | `auto` | Generates placeholders for [Conceptrodon::Mouldivore::Bind](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/descend/mouldivore/bind.hpp) and [Conceptrodon::Pagelivore::Bind](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/descend/pagelivore/bind.hpp)

## Categorized Functions
