/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Label ****/
template<typename Treasure, size_t I>
struct Label
{ static constexpr void lark(Treasure); };

/**** Vay ****/
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    : public Label<Vay<Variables>, I>...
    {
        // We bring every `lark` from its base class
        // to the current scope.
        using Label<Vay<Variables>, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization
        // before the primary template.
        template<auto, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // This function checks if a variable
        // is in the previously provided list.
        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Vay<Variable>`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        template<auto Variable>
        struct Hidden<Variable, decltype(lark(std::declval<Vay<Variable>>()))>
        { static constexpr bool value {true}; };

        // We check every variable using a fold expression.
        // It returns true if and only if each variable
        // appears only once in the list.
        static constexpr bool value
        {(...&&Hidden<Variables>::value)};
    };

    static constexpr bool value
    {Detail<std::make_index_sequence<sizeof...(Variables)>>::value};
};

/*****************/
/**** Example ****/
/*****************/

static_assert(AreDistinct<0, 1, 2, 3>::value);
static_assert(! AreDistinct<0, 1, 2, 3, 1>::value);