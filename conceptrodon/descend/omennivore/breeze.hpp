// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_BREEZE_H
#define CONCEPTRODON_OMENNIVORE_BREEZE_H

#include "conceptrodon/omennivore/concepts/mold_probe.hpp"
#include "conceptrodon/omennivore/concepts/page_probe.hpp"
#include "conceptrodon/omennivore/concepts/road_probe.hpp"
#include "conceptrodon/omennivore/concepts/rail_probe.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename Melody>
struct Breeze {};

template<typename Melody>
requires MoldProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;
};

template<typename Melody>
requires PageProbe<Melody>
struct Breeze<Melody>
{
    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;
};

template<typename Melody>
requires RoadProbe<Melody>
struct Breeze<Melody>
{
    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;
};

template<typename Melody>
requires RailProbe<Melody>
struct Breeze<Melody>
{
    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& PageProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& RoadProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires PageProbe<Melody>
&& RoadProbe<Melody>
struct Breeze<Melody>
{
    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;

    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;
};

template<typename Melody>
requires PageProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires RoadProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires PageProbe<Melody>
&& RoadProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;

    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& RoadProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& PageProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& PageProbe<Melody>
&& RoadProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;

    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;
};

template<typename Melody>
requires MoldProbe<Melody>
&& PageProbe<Melody>
&& RoadProbe<Melody>
&& RailProbe<Melody>
struct Breeze<Melody>
{
    template<typename...Tunes>
    using Mold = Melody::template Mold<Tunes...>;

    template<auto...Tunes>
    using Page = Melody::template Page<Tunes...>;

    template<template<typename...> class...Tunes>
    using Road = Melody::template Road<Tunes...>;

    template<template<auto...> class...Tunes>
    using Rail = Melody::template Rail<Tunes...>;
};

}}

#endif