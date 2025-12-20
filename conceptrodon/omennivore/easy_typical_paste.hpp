// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_TYPICAL_PASTE_H
#define CONCEPTRODON_OMENNIVORE_EASY_TYPICAL_PASTE_H

#include "conceptrodon/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/cotanivore/typical_paste.hpp"
#include "conceptrodon/sequnivore/typical_paste.hpp"
#include "conceptrodon/warehivore/typical_paste.hpp"
#include "conceptrodon/stockivore/typical_paste.hpp"

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