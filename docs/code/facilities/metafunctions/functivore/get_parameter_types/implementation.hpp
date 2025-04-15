/**********************/
/**** Dependencies ****/
/**********************/

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    template<template<typename...> class Container>
    using parameter_types = Container<Args...>;
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    template<template<typename...> class Container>
    using parameter_types = Container<Args...>;
};

template<typename Fn>
struct Analyzer: public AnalyzerPrototype<Fn> {};

template<typename Fn>
struct Analyzer<Fn*>
: public AnalyzerPrototype<Fn> {};

template<typename MemFn, typename Structure>
struct Analyzer<MemFn Structure::*>
: public AnalyzerPrototype<MemFn> {};

template<typename FO>
requires requires {&FO::operator();}
struct Analyzer<FO>
: public Analyzer<decltype(&FO::operator())> {};

/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Container>
struct GetParameterTypes
{ 
    template<typename...Args>
    using Mold = Analyzer<Args...>::template parameter_types<Container>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** DummyContainer ****/
template<typename...>
struct DummyContainer;

/**** SupposedParameterTypes ****/
using SupposedParameterTypes = DummyContainer<int, int*>;

/**** Tests ****/
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(fun)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<AbominableFun>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(FunAddr)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(&Tester::fun)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<FO>, SupposedParameterTypes>);
