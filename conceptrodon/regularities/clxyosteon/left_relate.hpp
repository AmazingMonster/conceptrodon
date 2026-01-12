// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_LEFT_RELATE_H
#define CONCEPTRODON_CLXYOSTEON_LEFT_RELATE_H

#include <type_traits>
#include <memory>
#include "conceptrodon/concepts/mouldivore/confess.hpp"

namespace Conceptrodon {
namespace Clxyosteon {

template<template<typename...> class...>
struct LeftRelate {};

template<template<typename...> class Predicate>
struct LeftRelate<Predicate>
{
    template<typename Right>
    struct ProtoMold
    {
        struct DetectorConcept
        {
            virtual bool idyl() = 0;
            virtual ~DetectorConcept() = default;
        };

        template<typename Left>
        struct Detector
        : public DetectorConcept
        {
            bool idyl() override
            { return false; }
        };

        template<typename Left>
        requires Conceptrodon::Mouldivore::Confess<Predicate, Left, Right>
        struct Detector<Left>
        : public DetectorConcept
        {
            bool idyl() override
            { return true; }
        };

        template<typename Left>
        struct BrokenDetector
        : public DetectorConcept
        {
            bool idyl() override
            { return Left::value; }
        };
        
        template<typename Left>
        ProtoMold(std::type_identity<Left>)
        : detector {std::make_unique<Detector<Left>>(Detector<Left>{})} {}
        
        ProtoMold(std::true_type)
        : detector {std::make_unique<BrokenDetector<std::true_type>>(BrokenDetector<std::true_type>{})} {}
        
        ProtoMold(std::false_type)
        : detector {std::make_unique<BrokenDetector<std::false_type>>(BrokenDetector<std::false_type>{})} {}

        bool operator()()
        { return detector -> idyl(); }

        std::unique_ptr<DetectorConcept> detector;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif