/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct ClassicPlume
{
    // Multiple Elements
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Elements
    // one Container
    template<template<typename...> class Cosmetic>
    struct ProtoRoad<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetic<Elements>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

template<typename Element>
struct ClassicPlume<Element>
{
    // One Element
    // Multiple Containers
    template<template<typename...> class...Cosmetics>
    struct ProtoRoad 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<typename Cosmetics<Element>::type...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<typename...> class...Cosmetics>
    using Road = ProtoRoad<Cosmetics...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** Transformations ****/
template<typename Element>
struct ZeroStar { using type = Element; };

template<typename Element>
struct OneStar { using type = Element*; };

template<typename Element>
struct TwoStars { using type = Element**; };

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<int, int*, int**>;

/**** Result ****/
using Result = ClassicPlume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int*, float*, double*>;

/**** Result ****/
using Result_1 = ClassicPlume<int, float, double>
::Road<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, float*, double**>;

/**** Result ****/
using Result_2 = ClassicPlume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);