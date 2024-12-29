<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::TypicalDiversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-typical-diversity">To Index</a></p>

## Description

`Varybivore::TypicalDiversity` accepts a set of nonrepetitive variables and returns a function.
When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every variable from the previously provided set and the arguments;
- doesn't contain repetitive variables;
- preserves the relative order of every variable;

The resulting list will be held inside a `Shuttle`.

<pre><code>   Vs...
-> Args...
-> Shuttle&lt;(make set)&lt;Vs..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalDiversity
 :: auto...
 -> auto...
 -> typename
```

## Structure

```C++
template<auto...>
struct TypicalDiversity
{
    template<auto...>
    alias Page
    {
        using type = RESULT;
    };

    template<auto...>
    using Page_t = RESULT;
};
```

## Examples

We will use `TypicalDiversity` to append `0, 1, 2` to `1, -1`:

```C++
/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = TypicalDiversity<1, -1>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Shuttle<1, -1, 0, 2>;

/**** Result ****/
using Result = Metafunction<0, 1, 2>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

This function used to be a helper class for `Varybivore::MakeSet`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

In general, `TypicalDiversity` is a simplified version of `Varybivore::AreOverlapping` as we won't worry about short-circuit here.
After instantiating the first two layers, `TypicalDiversity` has two lists of variables to work with.
We will implement the function using recursion over the length of the second list:

- **Base Case**: When only one variable exists, the result is:

  1. The first list if the variable is already in the first list
  2. or the list made by appending the variable to the end of the first list if it is not already present.

- **Recursive Case**: Pop the first variable from the second list. We invoke `TypicalDiversity` with:

  1. The first list if the variable is already in the first list
  2. or the list made by appending the variable to the end of the first list if it is not already present.
  
  Then, we invoke the first layer by the popped second list.

To check if an variable is in the first list, we use a method described in `Varybivore::SetContains`.
Namely, we will create a class that inherits every 'variable' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the variables our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, variables in the first list must be nonrepetitive.

Here's the entire implementation:

```C++
template<auto...>
struct Shuttle;

template<auto...InspectedVariables>
struct TypicalDiversity: public Vay<InspectedVariables>...
{
// Recursive Case:
    template<auto InspectingVariable, auto...RestVariables>
    struct ProtoPage
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedVariables..., InspectingVariable>
        >::type::template ProtoPage<RestVariables...>::type;
    };

// Base Case:
    template<auto InspectingVariable>
    struct ProtoPage<InspectingVariable>
    {
        using type = std::conditional
        <
            std::is_base_of<Vay<InspectingVariable>, TypicalDiversity>::value, 
            Shuttle<InspectedVariables...>, 
            Shuttle<InspectedVariables..., InspectingVariable>
        >::type;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADswQAOqAqETgwe3r4BaRlZAuGRMSzxiSm2mPaOAkIETMQEuT5%2BQTV12Y3NBKXRcQnJwQpNLW35nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpiprozIeJgK1wenF1fHv4df5zOgLMgQiyG8WGuJkCbgIAE9HgB9AjEJiEBTQ7BAoE/HbXIQILwEAj0D77AEETAsVIGSnQtxMImoAB0rMxQLGxC8DnxhOJ9GhVguOIO1wAakw4WS9hSqTSmHSYYyiOLmngmLEBYEsRdOdyCKq4dikhZrjNHMhrmgGGNMKpUsRrsrUNcAG5iLyYKEmiXEdWazAmJK3QXekOBIWA75/GP/EU3ACS1PobEECuy0pO8djsYBQMpyYVgaVTNZzITNseDkw6F9/voGO1HJR%2BuuABUEXhRLRbnhXQlMvCQNdUl5NV3DfSKwoq5Ta2qNQ3MWXjZGtltrgAlTDINaZfvXBlKEBA65n64F%2BWKhlM67T2cRYB1xeYUhO0us7djZ8Bxs687nmaLY8soxCoEQyhMMAgYXIBQaRoBgFeJkRgXgiXrQrcQHoCAKACPg9TMLQp6IWe9IkaRgFjDhIB4AoiKxEwSiIqgVD0hKRowveO6OEYP5atgb4dqkXZiL2/bEIOnHYLh7reK%2BUKwZRgHCaJPZ9gOhBwm%2BFHKe2nbduJmnwlOlY8TW/FvGWb7cQ4j6WeySmkZiuHwo8rlyrSXqgeBqCQdB9JfgQlkKCu2quehgq6UG4aRjiG4WExXpHuwumXl59LOneZl2XxC4Bo5AHnnqIFgRBUHFm4tm8U%2B%2BUCdFJq6UhKHAGhjxQoEWHUbh1oEdkYhNee5FOXp3W0fRjHMax7GSqZM48fZdXFoJ%2BkiYZGmSVpLkgHJno6SNykEkSJKVdVFlLaFbLavtRV6byx1alVOVziF1nZfNuW1X6L6Fcp21ucWCFDcGUXCiN6VFplH7MiFv3nshj7XP5GGdUjZV%2BRVM3fb%2BYVYhGxqxdi0Y5p82Z4tgqisDSXqk8TJMykTwKggw4JeJC9LWhsqQEH%2BjO4vd/I0%2BS%2BaeZDJZELjzZcjyR2C6DUaXKKACymBNFQXgs4RmayoW17OmW5zEMAvMXAjqEq2rGt2QIHVYap60SVJ9JcG%2BAC0XCFbhyP0obxuS/jYOKzcQheKk6RKOgX5eLQBq0%2BcZutSHYcZDWUcx7bAsnc7bsu9cGhvmY7IBwr/Np7Hwumy1W5vNHBqYdcFtMOrmvZPS%2BfXLnhfhSAAPy2T7ZvOXDO6k0FqIkxSgtBAY0KKwmDj42bhl2%2BSfh6nNcx5iiyChwyy0Jw/i8H4HBaKQqCcG41jWGaqzrBhII8KQBCaLvywANYBJIzIaAAHGYZgAE4AFcH8L/H%2BXAkhJGkPvDgkheAsAkBofOx9T7nw4LwBQIB87PxPrvUgcBYAwEQCAVYBBRwEHIJQNA1I6AJCiHPTgqgf4ADZXbMMkNcYAyBLRSGZGYXgNZCAkDwDhF2/BBAiDEOwKQMhBCKBUOoXBpBdAuwAO6olSJwHge8D5HxfmfTgAB5Ik5DrisWuEw1h7DOHcI7l/Mw1wIAeBofQR05hAhcEWLwHBWhlgQCQNQkSrjKEQECbQxIwApBmD4HQSkklKCxH0bECIzQ4RaN4Mk5gxA4SGNiNoHi6TSDUNTAQQxDBaBpKUVgWIXhgAMloLQTB3BeBYBYIYYA4gql4GIAtfsTTT52h3ESTYj8IiUhgafWgeBYiomyR4LA%2BiUR4AQc00gElYgp3uG0owUyjAv2WFQAwxsxSvFUYYx4x9H7iOEN2aR0hrnyLUPolR%2Bh2koCvpYfQ0zMGQGWKgbm2Qmmu2ophUwlhrBmFQRJP0WAfkQGWHYBazgICuEmH4F2YQIiDAqMMF24dig5E8O0PQ%2BLCJzCGIkF2iLrYMF6BMIl%2BQqW1CRbS8Y/QsXzFxbYNlaK9AzBaOSnFlKEW3w2BIHRHBD6kBQbwNBFiWFsI4Vwnh9jHG4CEW4h%2BXin77OWAgTATAsCJHhaQD%2BkhAjMgAYEKBGhJBmEkMwpB/hmEAP0JwOBpAEEeOZMwrgzCf4APAcw/wkgQFWuYdK/RaCMFYJ1bgvxRD/EkJMUSEJYTXH0LYJwZoLBXRJFdkwK0BhUJcAAcyLg38BEEWEaI2RNypESHubIR5ijT66GieopgmjmkSqlTKgxHBjFkKJGYqg8qrEcPBO0juZaK0aEcc4oJCQoQgjMNqnxeCk3poSGm1ALjhhTqMKWrg%2BcaAxwHAkpJKTsmFMyak3J%2BSHCFOKYwUp5TKmn2qbU%2BpjTCmtPaZ0z93TelvH0YM3clJCljNqPoqZMzUnzM2KfJZKzH7rM2VSADj59l8COQoE5mAzkXMKdcyR4gZEPKUE8pR7bXl7LBVYT5cG4V/IBQIIFILOoMYhVChIMLQO/K6CylwDB3AMvRSEUTgqFh4qKIRXlsnBzZGk1y6lhE6WtHE3y5lNKNMqcpdyvoCnDMCo5RS8VKw1his8W6yVeilFyssYqot07S3lu/mq6tmqPHrt1aQfVhrhgmpgR6r1ZbbVJH8AAyBgQ7UOtDZGhznAY3YJwwQ4hpDyG7v3cQTNmwc3WJYAoV0lpXRua8mMKtGqRF6FI7cxtdaW3PJAMETt3btG2b7VGoxKaDTmNUIV4rpXytFjGAuvdS7vOBF8/G/BASJvhOy5NnayAw6IjKwAxEFWCCIgG/c2JF6ICJKUXem9qzTs5LyQU1ZL7BBlIqfor9dSxC/tWf%2BnZSGWnAbsn0sDqghmQdWdBiZvA4OzLhIhxZfpUO8HQ0oLZWG9mzcOVBfDpzzmMBI7IMjdzGtUdbToFrdHjAfJsMx%2BArHCJNK2N1bjlhIWyuhSIgTJq1PZBE2JvIEnMVlHM4pglxnSXKbM0K7T3QGg8q00y8XrLZgi5kyZzTXO%2BVsv0xZhQorpG9vs6gzgFjBslbdCNykY2IDqqIN5zx3i/MBaNZQCVoWQCAOZIEQI/hQGhqQa7pI/rEu6/QbYWNG7FjvxAJIfwlqIFJCQT/SQwCuB/zMBGmBgQdeyuS3G3xEr%2BF%2B/TwH4PyxHbs8kEAA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/typical_diversity/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/diversity.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/typical_diversity.test.hpp)
