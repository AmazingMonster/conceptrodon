// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_PASTE_H
#define CONCEPTRODON_OMENNIVORE_EASY_PASTE_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/cotanivore/paste.hpp"
#include "conceptrodon/sequnivore/paste.hpp"
#include "conceptrodon/warehivore/paste.hpp"
#include "conceptrodon/stockivore/paste.hpp"

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

template<typename...Packages>
using EasyPaste = EasyTypicalPaste<Packages...>::type;

}}

#endif