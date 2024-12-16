// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

template<typename...>
struct Mold {};

template<auto...>
struct Page {};

template<template<typename...> class...>
struct Road {};

template<template<auto...> class...>
struct Rail {};

using MoldInt = Mold<int>;
// Fails since `int` does not match `auto`.
using PageInt = Page<int>;

using PageOne = Page<1>;
// Fails since `1` does not match `typename`.
using MoldOne = Mold<1>;

using RoadMold = Road<Mold>;
// Fails since `Mold` does not match `template<auto...> class`.
using RailMold = Rail<Mold>;

using RailPage = Rail<Page>;
// Fails since `Page` does not match `template<typename...> class`.
using RoadPage = Road<Page>;