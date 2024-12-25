/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<typename...> class...>
struct RoadLike;

/**** Items ****/
template<typename...>
struct MoldLike_0;

template<typename...>
struct MoldLike_1;

/**** Tests ****/
static_assert(IsRoadful<RoadLike<MoldLike_0, MoldLike_1>>::value);
static_assert(! IsRoadful<int>::value);