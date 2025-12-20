<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreDistinct`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-are-distinct">To Index</a></p>

## Description

`Varybivore::AreDistinct` accepts a list of variables.

It returns true if no two variables in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreDistinct
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `0, 1, 2, 3` are distinct. Then, we will append `1` and check again.

```C++
static_assert(AreDistinct<0, 1, 2, 3>::value);
static_assert(! AreDistinct<0, 1, 2, 3, 1>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we will create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.

In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
This is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

```C++
template<typename Treasure, size_t I>
struct Label
{ static constexpr void lark(Treasure); };
```

To instantiate `Label` with variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Then, given a `Variable` and an index `I`, we will instantiate `Label` as follows:

```C++
Label<Vay<Variable>, I>
```

Here's the entire implementation:

```C++
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
```

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/are_distinct/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/are_distinct.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/are_distinct.test.hpp)
