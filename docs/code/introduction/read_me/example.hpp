/****************/
/**** Source ****/
/****************/

namespace Conceptrodon {
namespace Mouldivore {

/**** BindBack ****/
template<template<typename...> class Operation>
struct BindBack
{
    template<typename...Endings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Elements..., Endings...>;
    };

    template<typename...Endings>
    using Mold = ProtoMold<Endings...>;
};

/**** BindFront ****/
template<template<typename...> class Operation>
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};

/**** Trip ****/
template<template<typename...> class Radio>
struct Trip
{
    /**** Define Road ****/
    template<template<typename...> class Car>
    struct ProtoRoad
    {
       /**** Commitment ****/
       struct Commit
       {
           /**** Conjuration ****/
           template<typename...Signals>
           using Mold = Car<Radio<Signals...>>;
       };

       /**** Continuation ****/
       template<template<typename...> class...Agreements>
       using Road = Trip<Commit::template Mold>::template ProtoRoad<Agreements...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

}}

/***********************/
/**** First Example ****/
/***********************/

#include <map>
#include <functional>

namespace Conceptrodon {
namespace Mouldivore {

template<typename...Elements>
using MakeFunction = void(Elements...);

using SupposedMap = std::map<size_t, std::function<void(int, int*, void*, void**)>>;

template<typename...Elements>
using MakeMap = 
    Trip<BindBack<MakeFunction>::Mold<void*, void**>::Mold>
    ::Road<std::function>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Commit
    ::Mold<Elements...>;

static_assert(std::same_as<MakeMap<int, int*>, SupposedMap>);

}}

/************************/
/**** Second Example ****/
/************************/

namespace Conceptrodon {
namespace Mouldivore {

using SupposedNestedMap 
= std::map<size_t, std::map<size_t, std::function<void(int, int*, void*, void**)>>>;

template<typename...Elements>
using MakeNestedMap =
    Trip<MakeMap>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Commit
    ::Mold<Elements...>;

static_assert(std::same_as<MakeNestedMap<int, int*>, SupposedNestedMap>);

}}