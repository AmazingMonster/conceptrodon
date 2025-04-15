/**********************/
/**** Dependencies ****/
/**********************/

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    using result_type = Ret;
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using result_type = Ret;
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

/**** TypicalGetReturnType ****/
template<typename Fn>
struct TypicalGetReturnType
{ using type = Analyzer<Fn>::result_type;};

/************************/
/**** Implementation ****/
/************************/

template<typename...Args>
using GetReturnType = TypicalGetReturnType<Args...>::type;

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

/**** SupposedReturnType ****/
using SupposedReturnType = int;

/**** Tests ****/
static_assert(std::same_as<GetReturnType<decltype(fun)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<AbominableFun>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<decltype(FunAddr)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<decltype(&Tester::fun)>, SupposedReturnType>);
static_assert(std::same_as<GetReturnType<FO>, SupposedReturnType>);
