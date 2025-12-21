// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_TYPICAL_PASTE_H
#define CONCEPTRODON_OMENNIVORE_EASY_TYPICAL_PASTE_H

#include "conceptrodon/concepts/omennivore/all_moldful.hpp"
#include "conceptrodon/concepts/omennivore/all_roadful.hpp"
#include "conceptrodon/concepts/omennivore/all_railful.hpp"
#include "conceptrodon/metafunctions/cotanivore/typical_paste.hpp"
#include "conceptrodon/metafunctions/sequnivore/typical_paste.hpp"
#include "conceptrodon/metafunctions/warehivore/typical_paste.hpp"
#include "conceptrodon/metafunctions/stockivore/typical_paste.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct EasyTypicalPaste
: public Sequnivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires AllMoldful<Packages...>
struct EasyTypicalPaste<Packages...>
: public Cotanivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires AllRoadful<Packages...>
struct EasyTypicalPaste<Packages...>
: public Warehivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires AllRailful<Packages...>
struct EasyTypicalPaste<Packages...>
: public Stockivore::TypicalPaste<Packages...>
{};

}}

#endif