/************************/
/**** Implementation ****/
/************************/

template<typename>
struct IsFlowful
{ static constexpr bool value {false}; };

template
<
    template<template<template<typename...> class...> class...> class Sorrow,
    template<template<typename...> class...> class...Warehouses
>
struct IsFlowful<Sorrow<Warehouses...>>
{ static constexpr bool value {true}; };

/*****************/
/**** Example ****/
/*****************/

/**** Vessel ****/
template<template<template<typename...> class...> class...>
struct FlowLike;

/**** Items ****/
template<template<typename...> class...>
struct RoadLike_0;

template<template<typename...> class...>
struct RoadLike_1;

/**** Tests ****/
static_assert(IsFlowful<FlowLike<RoadLike_0, RoadLike_1>>::value);
static_assert(! IsFlowful<int>::value);
