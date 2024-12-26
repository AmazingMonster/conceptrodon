/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct SensiblePlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // Multiple Elements
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        struct Detail
        {
            using type = Operation<Cosmetics<Elements>...>;
        };

        // Multiple Elements
        // One Container
        template<template<typename...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation<Cosmetic<Elements>...>;
        };

        template<template<typename...> class...Cosmetics>
        using Road = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename Element>
struct SensiblePlume<Element>
{
    template<template<typename...> class Operation>
    struct ProtoRoad 
    {
        // One Element
        // Multiple Containers
        template<template<typename...> class...Cosmetics>
        using Road = Operation<Cosmetics<Element>...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Transformations ****/
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = SensiblePlume<int>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<OneStar>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = SensiblePlume<int, float, double>
::Road<Operation>
::Road<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);