# Metafunctions

This document will introduce every metafunction of the library.

## Transport Functions

These functions work as holders for arguments.
They are similar to `boost::mp11::mp_list` but with member templates that transport arguments to user-provided functions.
They are directly placed in the namespace `Conceptrodon` for easy access.

Names are linked to their source code.

| Name | Parameter Signature | Transport&nbsp;members | Location |
|:-|:-|:-|:-|
| [Capsule](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/capsule.hpp) | `typename` | `Road` & `UniRoad` | conceptrodon/capsule.hpp |
| [Shuttle](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/shuttle.hpp) | `auto` | `Rail` & `UniRail` | conceptrodon/shuttle.hpp |
| [Reverie](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/reverie.hpp) | `template<typename...>` | `Flow` & `UniFlow` | conceptrodon/reverie.hpp |
| [Phantom](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/phantom.hpp) | `template<auto...>` | `Sail` & `UniSail` | conceptrodon/phantom.hpp |
| [Forlorn](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/forlorn.hpp) | <code>template<template<typename...>&nbsp;class...></code> | `Snow` & `UniSnow` | conceptrodon/forlorn.hpp |
| [Travail](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/travail.hpp) | <code>template<template<auto...>&nbsp;class...></code> | `Hail` & `UniHail` | conceptrodon/travail.hpp |
| [Lullaby](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/lullaby.hpp) | <code>template<template<template<typename...>&nbsp;class...>&nbsp;class...></code> | `Lull` & `UniLull` | conceptrodon/lullaby.hpp |
| [Halcyon](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/halcyon.hpp) | <code>template<template<template<auto...>&nbsp;class...>&nbsp;class...></code> | `Calm` & `UniCalm` | conceptrodon/halcyon.hpp |
| [Pursuit](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/pursuit.hpp) | <code>template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Hope` & `UniHope` | conceptrodon/pursuit.hpp |
| [Persist](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/persist.hpp) | <code>template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Will` & `UniWill` | conceptrodon/persist.hpp |
| [Morning](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/morning.hpp) | <code>template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Glow` & `UniGlow` | conceptrodon/morning.hpp |
| [Sunrise](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/sunrise.hpp) | <code>template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Dawn` & `UniDawn` | conceptrodon/sunrise.hpp |
| [Arcadia](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/arcadia.hpp) | <code>template<template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | | conceptrodon/arcadia.hpp |
| [Nirvana](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/nirvana.hpp) | <code>template<template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | | conceptrodon/nirvana.hpp |

## Identity Functions

Each of these functions can only accept one argument.
The argument can be retrieved through a member.
The primary use of identity functions is to turn values or templates into types.
These functions are directly placed in the namespace `Conceptrodon` for easy access.

Since std::type_identity already exists, the identity function for types is omitted.

Names are linked to their source code, except std::type_identity(which is linked to cppreference).

| Name | Parameter Signature | Retriever Member | location |
|:-|:-|:-|:-|
| [std::type_identity](https://en.cppreference.com/w/cpp/types/type_identity) | `typename` | `type` | |
| [Monotony](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/monotony.hpp) |`auto` | `value` | conceptrodon/monotony.hpp |
| [Emissary](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/emissary.hpp) | `template<typename...>` | `Mold` | conceptrodon/emissary.hpp |
| [Diplomat](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/diplomat.hpp) | `template<auto...>` | `Page` | conceptrodon/diplomat.hpp |
| [Delegacy](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/delegacy.hpp) | <code>template<template<typename...>&nbsp;class...></code> | `Road` | conceptrodon/delegacy.hpp |
| [Legation](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/legation.hpp) | <code>template<template<auto...>&nbsp;class...></code> | `Rail` | conceptrodon/legation.hpp |

## Utilities

These templates are not considered functions by this library. They are introduced to facilitate various programming techniques. They are part of this library's interface and are placed in the namespace `Conceptrodon` for easy access.

Names are linked to their source code.

<table>
    <thead>
        <tr>
            <th>Name</th>
            <th>Parameter Signature</th>
            <th>Location</th>
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
            <td>conceptrodon/label.hpp</td>
            <td  rowspan=4>
                <ul>
                    <li>
                        <a href="https://youtu.be/LfOh0DwTP00?list=PLbylzvxDYXicFnd_E34j8D9dU7a9ArBYM&t=2048">
                            The Nth Element: A Case Study - Kris Jusiak
                        </a>
                    </li>
                    <li>
                        <a href="https://github.com/StarQTius/Unpadded/blob/unstable-v2/include/upd/detail/variadic/leaf.hpp">
                            upd::detail::variadic::aggregated_leaves
                        </a>
                    <li>
                        <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/typelivore/amid.hpp">
                            Conceptrodon::Typelivore::Amid
                        </a>
                    </li>
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
            <td>conceptrodon/descend/stamp.hpp</td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/totem.hpp">
                    Totem
                </a>
            </td>
            <td><code>template&lttypename...&gt, auto</code></td>
            <td>conceptrodon/descend/totem.hpp</td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/badge.hpp">
                    Badge
                </a>
            </td>
            <td><code>template&ltauto...&gt, auto</code></td>
            <td>conceptrodon/descend/badge.hpp</td>
        </tr>
        <tr>
            <td>
                <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/prefix.hpp">
                    Prefix
                </a>
                (it's a concept)
            </td>
            <td><code>typename, auto</code></td>
            <td>conceptrodon/prefix.hpp</td>
            <td>
                <ul>
                    <li>
                        <a href="https://youtu.be/LfOh0DwTP00?list=PLbylzvxDYXicFnd_E34j8D9dU7a9ArBYM&t=1494">
                            The Nth Element: A Case Study - Kris Jusiak
                        </a>
                    </li>
                    <li>
                        <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/microbiota/typella/fore.hpp">
                            Conceptrodon::Typella::Fore
                        </a><br>(used to define
                        <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/typelivore/front.hpp">
                            Conceptrodon::Typelivore::Front
                        </a>and
                        <a href="https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/mouldivore/front.hpp">
                        <!--no line break so that a whitespace won't be added before ')'-->Conceptrodon::Mouldivore::Front</a>)
                    </li>
                </ul>
            </td>
        </tr>
    </tbody>
</table>

## Symbols

These templates or instantiations of these templates act as commands when passing to a function. They are placed in the namespace Conceptrodon for easy access.

Names are linked to their source code.

| Name | Parameter Signature | Purpose | Location |
|:-|:-|:-|:-|
| [Peg](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/peg.hpp) | `auto` | Generates placeholders for [Conceptrodon::Mouldivore::Bind](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/descend/mouldivore/bind.hpp) and [Conceptrodon::Pagelivore::Bind](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/descend/descend/pagelivore/bind.hpp)| conceptrodon/peg.hpp |

## Categorized Functions

These functions are categorized by their signatures and placed in the respective namespaces accordingly.
Many names are reused for functions that have similar functionalities.

Functions with the same functionality but different implementations are often provided under synonymic names for performance comparison.

Names are linked to more detailed explanations, while locations are linked to the corresponding source code.

### Typelivore

These functions have the signature `template<typename...>` and are placed in the namespace Conceptrodon::Typelivore.

#### Algorithm

| Name | Functionality | Location |
|:-|:-|:-|
| Among | pick out the element at a given index from a list | conceptrodon/typelivore/among.hpp |
| Amid | same as Among | conceptrodon/descend/typelivore/amid.hpp |
| Amidst | same as Among | conceptrodon/descend/typelivore/amidst.hpp |
| Find | find from a list the index of the first element that satisfies a given predicate | conceptrodon/typelivore/find.hpp |
| LookFor | same as Find | conceptrodon/typelivore/look_for.hpp |
| FoldLeft | similar to [std::ranges::fold_left](https://en.cppreference.com/w/cpp/algorithm/ranges/fold_left) | conceptrodon/typelivore/fold_left.hpp |
| FoldLeftFirst | similar to [std::ranges::fold_left_first](https://en.cppreference.com/w/cpp/algorithm/ranges/fold_left_first) | conceptrodon/typelivore/fold_left_first.hpp |
| FoldLeftFirst | similar to [std::ranges::fold_left_first](https://en.cppreference.com/w/cpp/algorithm/ranges/fold_left_first) | conceptrodon/typelivore/fold_left_first.hpp |