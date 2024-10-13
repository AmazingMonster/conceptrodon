# Metafunctions

This document will introduce every metafunction of the library.

## Transport Functions

These functions work as holders for arguments.
They are similar to `boost::mp11::mp_list` but with member templates that transport arguments to user-provided functions.
They are directly placed in the namespace `Conceptrodon` for easy access.

| Function | Parameter Signature | Transport members |
|:-|:-|:-|
| [Capsule](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/capsule.hpp) | `typename` | `Road` & `UniRoad` |
| [Shuttle](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/shuttle.hpp) | `auto` | `Rail` & `UniRail` |
| [Reverie](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/reverie.hpp) | `template<typename...>` | `Flow` & `UniFlow` |
| [Phantom](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/phantom.hpp) | `template<auto...>` | `Sail` & `UniSail` |
| [Forlorn](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/forlorn.hpp) | <code>template<template<typename...>&nbsp;class...></code> | `Snow` & `UniSnow` |
| [Travail](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/travail.hpp) | <code>template<template<auto...>&nbsp;class...></code> | `Hail` & `UniHail` |
| [Lullaby](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/lullaby.hpp) | <code>template<template<template<typename...>&nbsp;class...>&nbsp;class...></code> | `Lull` & `UniLull` |
| [Halcyon](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/halcyon.hpp) | <code>template<template<template<auto...>&nbsp;class...>&nbsp;class...></code> | `Calm` & `UniCalm` |
| [Pursuit](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/pursuit.hpp) | <code>template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Hope` & `UniHope` |
| [Persist](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/persist.hpp) | <code>template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Will` & `UniWill` |
| [Morning](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/morning.hpp) | <code>template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Glow` & `UniGlow` |
| [Sunrise](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/sunrise.hpp) | <code>template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Dawn` & `UniDawn` |
| [Arcadia](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/arcadia.hpp) | <code>template<template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | |
| [Nirvana](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/nirvana.hpp) | <code>template<template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | |

## Identity Functions

Each of these functions can only accept one argument.
The argument can be retrieved through a member.
The primary use of identity functions is to turn values or templates into types.
These functions are directly placed in the namespace `Conceptrodon` for easy access.

Since std::type_identity already exists, the identity function for types is omitted.

| Function | Parameter Signature | Retriever Member |
|:-|:-|:-|
| [std::type_identity](https://en.cppreference.com/w/cpp/types/type_identity) | `typename` | `type` |
| [Monotony](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/monotony.hpp) | `auto` | `value` |
| [Emissary](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/emissary.hpp) | `template<typename...>` | `Mold` |
| [Diplomat](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/diplomat.hpp) | `template<auto...>` | `Page` |
| [Delegacy](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/delegacy.hpp) | <code>template<template<typename...>&nbsp;class...></code> | `Road` |
| [Legation](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/legation.hpp) | <code>template<template<auto...>&nbsp;class...></code> | `Rail` |

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
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/label.hpp">
                    Label
                </a>
            </td>
            <td><code>typename, auto</code></td>
            <td  rowspan=4>
                <ul>
                    <li>
                        <a href="https://youtu.be/LfOh0DwTP00?list=PLbylzvxDYXicFnd_E34j8D9dU7a9ArBYM&t=2048">
                            The Nth Element: A Case Study - Kris Jusiak
                        </a>
                    <li>
                        <a href="https://github.com/StarQTius/Unpadded/blob/unstable-v2/include/upd/detail/variadic/leaf.hpp">
                            upd::detail::variadic::aggregated_leaves
                        </a>
                    <li>
                        <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/typelivore/amid.hpp">
                            Conceptrodon::Typelivore::Amid
                        </a>
                </ul>
            </td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/stamp.hpp">
                    Stamp
                </a>
            </td>
            <td><code>auto, auto</code></td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/totem.hpp">
                    Totem
                </a>
            </td>
            <td><code>template&lttypename...&gt, auto</code></td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/badge.hpp">
                    Badge
                </a>
            </td>
            <td><code>template&ltauto...&gt, auto</code></td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/prefix.hpp">
                    Prefix
                </a>
                (it's a concept)
            </td>
            <td><code>typename, auto</code></td>
            <td>
                <ul>
                    <li>
                        <a href="https://youtu.be/LfOh0DwTP00?list=PLbylzvxDYXicFnd_E34j8D9dU7a9ArBYM&t=1494">
                            The Nth Element: A Case Study - Kris Jusiak
                        </a>
                    <li>
                        <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/microbiota/typella/fore.hpp">
                            Conceptrodon::typella::Fore
                        </a>
                        <br>
                        (used to define <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/typelivore/front.hpp">Conceptrodon::typelivore::Front</a>)
                </ul>
            </td>
        </tr>
    </tbody>
</table>

## Symbols

These templates or instantiations of these templates act as commands when passing to a function. They are placed in the namespace Conceptrodon for easy access.

| Name | Parameter Signature | Purpose |
|:-|:-|:-|
| [Peg](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/peg.hpp) | `auto` | Generates placeholders for [Conceptrodon::Mouldivore::Bind](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/descend/mouldivore/bind.hpp) and [Conceptrodon::Pagelivore::Bind](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/descend/pagelivore/bind.hpp)

## Categorized Functions
