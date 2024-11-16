# Identity Functions

Each of these functions can only accept one argument.
The argument can be retrieved through a member.
The primary use of identity functions is to turn values or templates into types.

Since `std::type_identity` already exists, the identity function for types is omitted.

Names are linked to their source code, except `std::type_identity`(which is linked to cppreference).

| Name | Parameter Signature | Retriever Member | location |
|:-|:-|:-|:-|
| [std::type_identity](https://en.cppreference.com/w/cpp/types/type_identity) | `typename` | `type` | |
| [Monotony](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/monotony.hpp) |`auto` | `value` | conceptrodon/monotony.hpp |
| [Emissary](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/emissary.hpp) | `template<typename...>` | `Mold` | conceptrodon/emissary.hpp |
| [Diplomat](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/diplomat.hpp) | `template<auto...>` | `Page` | conceptrodon/diplomat.hpp |
| [Delegacy](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/delegacy.hpp) | <code>template<template<typename...>&nbsp;class...></code> | `Road` | conceptrodon/delegacy.hpp |
| [Legation](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/legation.hpp) | <code>template<template<auto...>&nbsp;class...></code> | `Rail` | conceptrodon/legation.hpp |