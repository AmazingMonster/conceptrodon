/************************/
/**** Implementation ****/
/************************/

template<typename Element, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Element;
    static constexpr auto lark(Element) -> Key;
};

/*****************/
/**** Example ****/
/*****************/

#include <utility>
#include <cstddef>
#include <concepts>

/**** Element ****/
template<auto>
struct Element {};

/**** Key ****/
template<auto>
struct Key {};

/**** Lexicon ****/
// We will use this helper template to create
// overload sets for `idyl` and `lark`.
template<typename...>
struct LexiconHelper {};

template<auto...I, typename...Es>
struct LexiconHelper<std::index_sequence<I...>, Es...>
: public Label<Es, Key<I>>...
{
    // Pull every `idyl` to the current scope.
    using Label<Es, Key<I>>::idyl...;
    // Pull every `lark` to the current scope.
    using Label<Es, Key<I>>::lark...;
};

template<typename...Es>
struct Lexicon
: public LexiconHelper<std::make_index_sequence<sizeof...(Es)>, Es...> {};

/**** YellowPages ****/
using YellowPages = Lexicon<Element<0>, Element<-1>, Element<-2>, Element<-3>>;

/**** Tests ****/
// Retrieve the element corresponding to the key `Key<size_t(1)>`.
using SupposedElement = Element<-1>;
using ResultElement = decltype
(YellowPages::idyl(std::declval<Key<static_cast<size_t>(1)>>()));

static_assert(std::same_as<ResultElement, SupposedElement>);

// Retrieve the key corresponding to the element `Element<-1>`.
using SupposedKey = Key<static_cast<size_t>(1)>;
using ResultKey = decltype
(YellowPages::lark(std::declval<Element<-1>>()));

static_assert(std::same_as<ResultKey, SupposedKey>);