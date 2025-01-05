<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreDistinct`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-distinct">To Index</a></p>

## Description

`Typelivore::AreDistinct` accepts a list of elements. It returns true if no two elements in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreDistinct
 :: typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are distinct. Then, we will append `int*` and check again.

```C++
static_assert(AreDistinct<int, int*, int**, void>::value);
static_assert(! AreDistinct<int, int*, int**, void, int*>::value);
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
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
template<typename...Elements>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    // Since arguments are not allowed to have the type `void`,
    // which shall be a valid argument for `AreDistinct`,
    // we declare the parameters using `Elements*`.
    : public Label<Elements*, I>...
    {
        // We bring every `lark` from its base class
        // to the current scope.
        using Label<Elements*, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization
        // before the primary template.
        template<typename, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // This function checks if an element
        // is in the previously provided list.
        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Element*`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        template<typename Element>
        struct Hidden<Element, decltype(lark(std::declval<Element*>()))>
        { static constexpr bool value {true}; };

        // We check every element using a fold expression.
        // It returns true if and only if each element
        // appears only once in the list.
        static constexpr bool value
        {(...&&Hidden<Elements>::value)};
    };

    static constexpr bool value
    {Detail<std::index_sequence_for<Elements...>>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwA7KSuADJ4DJgAcj4ARpjEIIEapAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzBFkN4sDcTKC3F5HLRCABPWHYYHmcEMSFeaGwtzIcboLBUNEYn6HG6hJjxWifA6AgiYFipAxM/EEZFPZhsG7YehsQSkG6ZABemAA%2BgQbgBJMmXcbELwOKk0uoYwIWEXNRzIG5oBjjTCqVLEG4AN1QeHQNwMxAA1hB%2BczGAQlrCtSZAncPeSrv8AwDgb9drKWQLXUwGvT9oCQ4H/oDgUzw1HMByuYxWJgAHR552CggKeUXRXK6UXYiYO54cYQggaqyXG4tm4p1lpjPc7Ml1vapUqh7NOgwzVen2gptA5ut9ts9NwsWSgh5nNy0HomctsuDzDD2j4okgEARLCqCVKACOXheC7cMtXZI3wL7222NwA6ph9VW0zdDDcqDmgktCoEwNpKNKBAIMQazAAgNwRAgCSEIYmw5i%2BrZvjcQgQt%2BLTAD4rofC034MKg0piKBADumA2kQNwIEwwFtshbaZjC/gaJa1omFxpCYS22HUQgeDIAhChMbQdLxP%2BFpiNa/7EIRhY3PwZp8ZcVY1nW2INvxgk3MJ35YJCpGsd%2BqQtNmTLEB8XiZEYnEaAWxG7JpGFbjcIA3KkXixEierUrS%2BKuYICi7MK67YI%2BXlelOfavu%2BX43LExARMANyYMBxDIs5dr2ppamwSwiFFqlTBKPqBgKMWXlJW2qAWfq6xVoIIpoE8nkXIlrYORlqohXCYVFpFsposeBWPpOfq9UJyXftRdB0ugTVCAAYjKUQXNggEMM1SgGjaVnEDZCTdXNRnvgAKmxJJMF4tCUcpRHtZpPHoEVjAKOs7yGQ10HfmgLJ0Ak%2BrIcg9ofIDIpPK8CmilG2T/Vh77xOp34w6aeAsC0eVzmmF1zQT7Jwpy3ZsMK5NZmwsJ3B9vZzTu0oABLWlgDAoy28XakjeoGkaJpmrEqCePJ3jfvFVBiEo44eqOE5TlzV03LdtZqV4enZODmCQx8eBUP%2B%2B11C6gjK9h6sRM1prZU4Dm0HlppAdadG2rWK7mwt/4KPazXA6koNmgxNAMDaTD5S0hVcaxUaezcpl2u8cknWdZqoIb1POSN7lcUTvXYTKGdsf7gdqae0NsZpBUCVxcfQerChw3gCNIwINxLdJqXfg5dF54l2EAPKA8QS1KFTbHY7juVtsyHZMu3y1dzcPfoH3fYk3e1M8t%2BI2M71zM3GzxKMKFEZCvHutPZmEAFRAR4gAn5piKfpsEO5G4QEsX974lPOzLq%2BoBCC1NKlUWdIn4S1HBYAgSp0zenlnLGalw44pXErrX22UEh5RNqpfqTlw78FoDaY0NtarZDXqjWU0oqwEHWIaNssDEKG0MDaAQDsmFZSYOJLKZ8Gz1UoUwVITwWgfDYXlAQmxEL7RhkicYFDtw6jEoAw0TIhagLFhAm8yt4oQEfGYfw5h/BHw5i/QsxYNzHk0Zgd08CkE9VbIgpWXl/5KIFqokBIsNFiC0XFTUQ4mB0EPAQdAx5TzGgvJga8t4JTqVMcRaa6ILEgCsY4jUis/TxgTHGSk2BVCsFZN%2BL4wYExBmQQqRRyAJSVSUK0CAlZqzu3rPiCIBBhQtLGu0saDMklWPdHYlxlTqkJAIBAMAYAbj1J0o4PSzTz7tLaYIfYwoPoLLfhNZJ3jrEeg4CsWgnAACsvA/AcC0KQVAnA3DWGsCKNYGxJZgh4KQAgmgdkrHtCAfZkgcwaAABxmDMAATgBVwfZvyflcECIEaQeyOCSF4CwCQGgUjHNOecjgvAFAgBSM8k5OzSBwFgDARAIA1gED8q0igEAS70GIFEbMnBVA/P8AAWn8JIG4wBkB6ikDmMwvA6KEBINaPQ/BBAiDEOwKQMhBCKBUOoXFpBdBcFINRU6qROA8F2Qco5LyzmcAHgiclgFDaMpZWyjlXKbg8rMDcCAHgQY0phA8pYvAcVaBWBAJA1KEjkEoN6xIwApBmD4HQWymKICxF1bECIeMNW8GjcwXKA9YjaF1jix5wNCwDwYA7XVWBYheGAG4KimLuC8CwLjIw4gFX4CrA4PAwFS2nONLrBEWxHktLqLqpEaU8YeCwLqmBOM42kByiLJQDxK3ACREYF5KwqAGGAAoAAam8aiA9uQjtFcIUQ4gpXbtlWoXVSr9CGGMFcyw%2Bg8CxExZAFYqBUgNFLcyokdNTCWGsGYVFOV0pYFvZ/boabsguFDlMPwyqwgRCGJUEYyqihZAEGBvQ8GGjzGGIkZVdggMCD6JMTwHQ9BYfrThiYAwoMLFg7YUjSHMOkbQzBjDKwFC3M2BILVHBDmkBRbwNFNxTWsvZZy7lXybVOnwEQDSzrXVzpWMhcCIwAPvMkKCHMALQRQo0JIMwkguIaH2f4AF%2BhOBwtIAi0EXAcz%2BC4P4H5ALwX%2BE%2BSCtT/guO6rRRirFTy534qJZ6klhqES%2BqpagB1CQ6VsE4C0Fg5pAjMvDmZJyXAAU5gs828TQqQnKu3eKvd0gD1KCPQq3QwbVWCLjexzj3G9UcANWShExq%2BNMoE9VM9VrkupdtfagOjrMRmBdV53FHqvUhe6z6yl/qUAGCMElrgKQaBPQSOGyNCqE2xrLaQVbSaU1ppHZm102bc01swAWotJaR0VrPdW05tagONt1S25AbaR2dphacntp1cr9q2KcodCL1tjoyNWZkl2MreYXUwJdq7MDrs3et7Lu7JV5dkIe%2BVpziuntne%2Bqwl6e3/vvY%2B7Iz7X2gjuFjz936Ei/vePAJjJtiN%2BAgK4GjIRQ70cWHBjICGcj4fyBz4o2Q2eUaIw0XDbQefgcA/T0XguMNUf6Mz2YrQZdsdWOsVjXAKs6oVbx/j5qEuZSSyl75trcCCsk%2BZ/rbrXmkDk1gRIAGYUmbM8lzTgR9kAshaCLTOnJDKqq%2B52wnmrcet80gUl5Kgv%2BvC1sKL5qWAKHNHqc0hv5zjH5el39IrZA5cR9K%2BQBXUc6BAKCFVarytGY41r1F%2BqAvSnTnxuPCek8p7TOMTrI3S6YlBJb7zfn/WR47zS5JyAhESmTwCiUqeCASlUGykNC27KUGW6czbyIR2r%2BTamhwu2QtZpzWvo7J3i3SVLY8i7VbvvlrwHWxwd2FUPae%2Btl73br0feRF9wd6U/uPIBxO4HVbQdBs%2BBF0V010N1GAt1s8EcJAkcZUC9j1i8Mdz0P0cdr08czkCcgFOBtgjwydLAv0eMf0XZ0DhdgNGdQNxc9BINyh0NkNOcGhmcUMBdyNaDMM6cRdqNKC2CegSM5gWCGNCNOC8gJdFcyMaCBCNdVc7kVcYVKs3NOAG92V49E8LQW8mQ28xMzcnULdpNBtZNMB5N7d2MncQBAUcxQRQR9lQVfckULDAgbNXNtdOAPNsUZNSAlN9lVMIVkhflJBgUuA/l9EK9QQq8eNnCBt3V2M%2BVHDq90UIjrccpMhnBJAgA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/are_distinct/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/are_distinct.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/are_distinct.test.hpp)
