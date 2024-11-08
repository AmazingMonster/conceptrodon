<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreDistinct`

## Description

`Typelivore::AreDistinct` checks if its arguments are distinct.
<pre><code>Elements... -> AreDistinct ? true : false</code></pre>

## Type Signature

```Haskell
AreDistinct :: typename... -> auto
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

## Example

We will check if `int`, `int*`, and `int**` are distinct. Then, we will append `int*` and check again.

```C++
static_assert(AreDistinct<int, int*, int**>::value);
static_assert(AreDistinct<int, int*, int**, int*>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we are going to create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.
In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

```C++
// Adding a second parameter to the label is essential
// since inheriting the same class multiple is illegal in C++.
// Unfortunately,
// using this error for SFINAE is impossible based on my testing.
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };

template<typename...Elements>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    : public Label<Elements, I>...
    {
        // We bring every `lark` from its base class to the current scope.
        using Label<Elements, I>::lark...;


        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization before the primary template.
        template<typename, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Element`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        // This function checks if an element
        // is in the previously provided elements.
        template<typename Element>
        struct Hidden<Element, decltype(lark(std::declval<Element>()))>
        { static constexpr bool value {true}; };

        // We check every element in the previously provided elements.
        static constexpr bool value
        {(...&&Hidden<Elements>::value)};
    };

    static constexpr bool value
    {Detail<std::index_sequence_for<Elements...>>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCBmpAAOqAqETgwe3r4ByanpAqHhUSyx8Vy2mPaOAkIETMQEWT5%2BXIF2mA4ZdQ0ERZExcQm29Y3NOW0jvf0lZRIAlLaoXsTI7BzmAMxhyN5YANQmm25ejrSEAJ5H2CYaAIJbO3uYh8fICgToWFTXtw/3AHoAfs7l8wsB9kx9ko0Ax0Pskg1WJgCHF9kR0QgXgZYrR9ngFPtMAolII8GI/kDoTsXmEscR0kZMS8FMj9rsmCT9iwvLRHEl6PjCXR6MAxPiGPs3NZrAA6SnAuQMfiNLzMVG0C6kBX7LxpJkEBAEonEYgkfYq/ZCABiAEkIndsEL8SwUiS8NFBdFOZh4QJuRd0cTHEZ5fdUa6DKijm4CBckow2dh6GxBKRqQAvTAAfQI%2B1tv3uH2IXgc%2B2CTFxfxMAHYLND6o5kOyBB9MKoksR9gA3VB4eEGYgAawgycwqYI8yO9drABFp9Xw%2BOBUxo8c4wnmGxZTuxxOFIW7sXS3m7sRMLOCSGHNW6399g%2Bg5HV5gYxvE2xD4%2BGyWy7OUUwdCHHeNbzpsVj3Pej4Riua5uGkWa5jusoFpsNz3N%2Bx5/gBdAxh86AgCAYRYKo2ZKAAjl4jBrDGtrIb8aFQQ%2BVIAOovMg54vpCkqoN2cS0KgTDwkoeaGmaXjAAgEr0oQhhrGGdzfiACJeJ6eDNhWVbHHujAEAo6aodg9EYY%2BtYQYp36PqxLzRAyTKYHxxCBiYABsGiDkOrkaBaZosPien7N6SjsgYXIYoa7ErOegjQmgCYKZZj56uC5aVlUMY6YI%2Bn5tchEefR4GLv8FmJdZ%2BwAO4ivs6CoFadoOk6/oRdCnQCPCiLEMiqLEAliX7FSAAqWLVZgVBMLyeYNMAPi6Ycbm9v2XlEgwCgrMSTGWVSzVoK6dBosgWLIEOhLNQoCbIOS5wZquGSBaNJAvM1nZ4CwDSBjBUaYL1iUfS%2Bb7xh%2BmDpu%2BW6vpss4LegX59VheYABL9lgDAbd%2BZkNjdzawm2HZdtEqCeD2YhUcBFhjbQShztOwFgeZKNWcCbGQgoQ7Mi2u30F2GI0HCkJze5DSeW5mKrnTzHAlgHLnoSUIdV1aKoFQ6IA3zmUEF532bcCtqK9tqDs2i3PoCdw1eR52puaL/XAoaxpnZ0l14NdNSSpVtB4rEupKOgGvflSADyEXEJVSjA8Nz2vU5T6wS8rvuy8eq%2Bj79P7ENxpUGqXT%2BgdnTHfiiuGESKa6ZbVLGmErOdg5Th6pqCJmt2/a%2BoX466QoScPr9cEg0mReCNDiWw/sCNfIwGW9wQ6YS3yAMQB5ED4YRU/dhS2nj9cEDzJv/eWWjHwYy2K2ojjgX43iy/eC8ZkECWr6gVTlOFZBJmlQz7GHSzDlxIGVQtzF5dPeeBuywFC107LxRu8If77nbujJsB9sadhPgTc%2BVFLZmQgPRMwLlzAuWHkjMev89K5RACgzAU476PxKtTBcT8qF7zgVjI%2BiC8bIKJq%2BZ%2BJN/z1FwscBeRE4TtjIpgSi1EcwqgIdAncDFsCEVIQ/WmFDaaAgAFSqLUeogElI1EDWwEIAaajNEqPUcYwxxVHgMF2F4A4MZYRrCSEQxitD6HqWzJyJQjQIBngvFeHYatjhhAnhKAgyj0wBNUcQ0hU5KHOOQK4kkcQCAQDAGAEE55LwfF8TGAJoTBAhKCaonJwSIlsKiRYDgixaCcAAKy8D8NwXgqBODSksNYaEyxViXzMJsHgpACCaHKYsIcIAXKbFlAADjGTWDQLkqkaA0JsMwYyzD%2BECJUjgkheAsAkHM0gdStCkEaRwXgCgQAaF6f0xYcBYAwEQCAZYBAkinHIJQHaSQ9rEAiMiTgqgxkuQALQuUkPsYAyBmxSFlGYXgvpCAkH7HofgggRBiHYFIGQghFAqHUBwfZugKjlU6kkTgPAKnVNqf0g5nA/anEeXmBW%2Bwfn/MBcC0F%2BxwVmH2BADw%2BsuxbC4PMXgfTsXlNIBAJArz3nPIgOKjmIBgBSESDQPkcQTkQGiOS6IYQ3pEt4Bq5gTk/bRG0J0QVPSdoTj9gwTU5KsDRAkm4MQ5NtWkCwK9Iw4ghXOrwOeLofETkevbJ0U46wekBKqOS84tk3oeCwOS6%2BL0nWOTxkof8rrgDnCMBcvgBhgAKAAGp4EwOVP2m4nUIuEKIcQqKy0YrUOS3F%2BhDDGBlJYfQHoTmQEWKgexGQ/V/PwkcWcpgWmWDMPs3icQGRYHbRvSo1QMguDhOMVoQQ4QzEGOUPIaRnZLr0G6AoDA12lCGBUDomcGA9DGJ4FoehT3OwvX0MIAwj0br3pe7Iy7X0PuKOuhYSwVhrF/WsmpuzyWHPpb8gFQKQVgskBCjluAYU8q6XygVFzFhYiEkMGdQzJCjP8JsGskgNCSDMJINyGgqkuVWZwDZpAtndNlC5LgLkxn%2BDGcxqpkguBVPwy5EDHrDnHNOecoVlybmirudSp5FApV6zeRzT5bBOANBYN2GsfyoQciZG0WUXBZT7OhUQSd8LZBIsrdIatSha0et0IkfFTBCX1JJRwYDeyGmUqk7S/OxBVPqc0wYbT/hdP6Y5Vy%2BTaIthmH5SJrQlyxVyYlTJ6VQwVNqb%2BVpuV/guBnMVd1FVaqPW6q1fU0gRX9WGuNU6s1ukLVWo9Tau1Dq/U9JdY291%2Bz8DescL68lAbkBBqdaGtZ%2ByI2dSctG9Y%2By41bJK4m1IF5xxtfBJmqg2a80FqLSWkrZazMoos7IGtWKcXDAC024dNgI3Ts7d21snA%2B2fAHUOqwI6x2OUncSeAixb3zogK4HdFQQiPtmMezd%2B7/ug%2BdoeuYJ6f5nvveD77tRRhfqfdDqYb7r0nuR1D49X32kAb5foUl/Gx2cEhD5tL/nG2sqC3p7yo58BGcOMh6LgrYvocwJh%2BIM61m0fo0F4jNYeM1hrJsEjZGuMk/c0c2wwm2fCqubc%2B5NLJXJY%2BV8jgKmmUsAUN2Zs3YdOfQ%2BFCxnsKCIVB2xWvbaL5BWaOzoEAmxSD2cc8SonLmyUCY8w804%2Bw6Va6BTrvXPZDcvg%2BKFhLHNmebE2KzzNEm1eq8j0MPXSQkjZgN/4bMRuCCuJ84CvgdA8uUAK/ssrFwnXl4NUahwVW9bmstRX%2BrmBbXAHtW7ZrvBWtusm13r1xq8A9f9aoQNqJBuCDDR60bUaMC996QyGbPS5vJsW265boms1MBzfmwtxbGCltM1biQ%2B30V27rY7htGanvWFbdEK7BybsrU4ACBe1%2BXsNLe43e/iO/C/cXVeiYFddAHHDdPdbdAA5dMAjIEAm9WHO9ZHBHOA7obHIHH9LHXoBHFA79Z9X9BQfHFFZzVzUDMnAPbkXXfXUPVEcPBnRDaPFDGLAZUgDDLAbnZzPnBIILGPKpWZLjOZGPGsFjKXClGXE5M5eXTeUgIZTYFyXTLgZZMXFZFyGsLgKZCoNZTYT3UnGXcQ5zSFIQwTBgiQxyNIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/are_distinct.hpp)
- [unit test](../../../../tests/unit/typelivore/are_distinct.test.hpp)
