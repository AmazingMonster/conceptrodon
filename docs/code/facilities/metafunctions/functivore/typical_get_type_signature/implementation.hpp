/**********************/
/**** Dependencies ****/
/**********************/

/**** Analyzer ****/
template <typename>
struct AnalyzerPrototype {};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...)>
{
    using type_signature = Ret(Args...);
};

template <typename Ret, typename...Args>
struct AnalyzerPrototype<Ret(Args...) const>
{
    using type_signature = Ret(Args...);
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

template<typename Fn>
struct TypicalGetTypeSignature
{ using type = Analyzer<Fn>::type_signature;};

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

/**** SupposedTypeSignature ****/
using SupposedTypeSignature = int(int, int*);

/**** Tests ****/
static_assert(std::same_as<TypicalGetTypeSignature<decltype(fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<AbominableFun>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<decltype(FunAddr)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<decltype(&Tester::fun)>::type, SupposedTypeSignature>);
static_assert(std::same_as<TypicalGetTypeSignature<FO>::type, SupposedTypeSignature>);
