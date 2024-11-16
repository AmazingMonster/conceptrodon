# Transport Functions

These functions work as holders for arguments.
They are similar to `boost::mp11::mp_list` but with member templates that transport arguments to user-provided functions.

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
| [Pursuit](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/pursuit.hpp) | <code>template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Grit` & `UniGrit` | conceptrodon/pursuit.hpp |
| [Persist](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/persist.hpp) | <code>template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Will` & `UniWill` | conceptrodon/persist.hpp |
| [Sunrise](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/sunrise.hpp) | <code>template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Glow` & `UniGlow` | conceptrodon/morning.hpp |
| [Morning](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/morning.hpp) | <code>template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | `Dawn` & `UniDawn` | conceptrodon/sunrise.hpp |
| [Arcadia](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/arcadia.hpp) | <code>template<template<template<template<template<template<typename...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | | conceptrodon/arcadia.hpp |
| [Nirvana](https://github.com/AmazingMonster/conceptrodon/blob/main/conceptrodon/nirvana.hpp) | <code>template<template<template<template<template<template<auto...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...>&nbsp;class...></code> | | conceptrodon/nirvana.hpp |
