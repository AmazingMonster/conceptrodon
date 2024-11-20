// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_REPACK_H
#define CONCEPTRODON_OMENNIVORE_EASY_REPACK_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/descend/cotanivore/repack.hpp"
#include "conceptrodon/descend/sequnivore/repack.hpp"
#include "conceptrodon/descend/warehivore/repack.hpp"
#include "conceptrodon/descend/stockivore/repack.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct EasyRepack
: public Sequnivore::Repack<Packages...>
{};

template<typename...Packages>
requires AllMoldful<Packages...>
struct EasyRepack<Packages...>
: public Cotanivore::Repack<Packages...>
{};

template<typename...Packages>
requires AllRoadful<Packages...>
struct EasyRepack<Packages...>
: public Warehivore::Repack<Packages...>
{};

template<typename...Packages>
requires AllRailful<Packages...>
struct EasyRepack<Packages...>
: public Stockivore::Repack<Packages...>
{};

}}

#endif