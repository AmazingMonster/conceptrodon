<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsNoGreater`

<p style='text-align: right;'><a href="../../../index.md#arithmetic-examinations">To Index</a></p>

## Description

`Varybivore::IsNoGreater` accepts a target and a list of variables.
It returns true if the target is less or equal to all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &le; V<sub>0</sub>) && (Target &le; V<sub>1</sub>) && ... && (Target &le; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsNoGreater :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct IsNoGreater
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsNoGreater_v
{RESULT};
```

## Examples

```C++
static_assert(IsNoGreater<5, 5, 6, 7>::value);
static_assert(! IsNoGreater<4, 2, 3, 4>::value);
```

## Implementation

We will implement `IsNoGreater` using only `<`, meaning <code>Target &le; Variable</code> is expressed as:

```C++
not (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsNoGreater
{
    static constexpr bool value
    { (...&&(not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoGreater_v
{ (...&&(not (Variables < Target))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCcpK4AMngMmAByPgBGmMQSAOykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHASYLCkGeyYAzG5MXkQA1AAqzcCYBKRXF0QAdB8Aas14TDH0ClO2BMGgAgrNiF4HFcAJIKSKoADixEwTD2xBBoJMiSsYKu%2BKuszReGQVzQDFmmFUKWIVxiqE8VwAbmIvJhMQSrtiLFcIB83uYAGxCiAMVAEXnfYi/f6YBRcs63e6PFaqrmJAAip1xWM12sxmL2ByO7LOr1QSuIDyeL0uqH5UplAKBmPJlOptPpjLhCORqPRAH0mQacbz%2BUKRWKJRBHX8AQq3JbraqVuqtScdZiAPQAKjz%2BYLWez%2BZu2CEN3zRbBuYLtarWLBRMcyADTAUShaEB9SJRaPipzcAFZnsOroLnokgSAQCzvJgVvrG01m632/ECBAwGBYfCe/7%2B2dpFczM8Ts9JFOZ6z59qOGtaJxB7w/BwtKRUJw3NZrISNltMFyZgnDwpAEJod5rAA1iAg5mG8iRmJIAAcSGDhoASwRogpIWeD4cJIvAsBIGgaKQL5vh%2BHC8AoICkWBr53qQcCwDAiAgBsBApJc5CUGgBx0PEkSsDsqhIYKAC0gqSFcwDIKSUhvGYvCYPgRDSugej8IIIhiOwUgyIIigqOoDGkLoXCkAA7sQTApJwPD3o%2Bz7ge%2BnAAPKXFxEqoFQVyiRJUkyXJVwKWYvIePx9C0uYwErLw9FaGsEBIHxKQCWQFAQKl6UgMAUgnjQtDojREAxC5MThM0ACe9m8BVzDEFVbkxNodT0SBfFsIIbkMLQNWmVgMReMA5y0LQNHcLwWAsIYwDiANeAovUTJyi5VJ1JcOwgeEex4W%2BtB4DENmNR4WAuQQ0pEZNpArcQ9JKBq%2ByzQdRjgWsVAGMACifHgmCWW5KSMLVBnCKI4j6Vp8hKGoLnmfos0oN%2Blj6IdNGQGsqApL0E3ibM6CnBqpiWNYZgUbd6mrejXQ9FkLgMO4njtHooQLOUlR6IUmQCFMfgWZzvRDGzyzU21DRzDzei1PUAj9C0gsjFU4wDBLFlEnLrMKxIawKH%2B2xa/oTlkS5lF%2BWJknSbJ8mSIpvK4IQJCAbF8VvWsCColgCQQFB/gnG8AQnIkkgaJIiGCiRg6CkEeEEaQRHAW8gpcNhARIUng6SFwg7%2B%2BO5G8JR1G0aBb1MaxyXsZ53GZdlUVCWwnDNCwTKJOJTBkgYRghQEbxcG8b4qfb6mabIOng9IkNGTDpm6Ce1m2bVjkcE%2BRumZRHmcZcVw%2BS8xCN83rfIO3wCd93vfhagkXxI7ZhxUXDFJSl59pVFPFZY/OUN034kH7NXABFwpGFWKpQMqpl6rVWBmAxqzVWoOGBp1RgBAep9RcoNYao1xrA2ms9HYb58BLUcCtCafdVAbT2MDHa3QXIHSOtVU6OD4qXWBrde6mBHozSMC9UAd8%2BCfW%2Br9f6gMXwgUhiPPSY9ZATxMm%2Bae8NXpEysMjahaMvbvixlkHGeMCbyJJmTeIFNlHa26KLZwEBXAq2CPTeWSxFb8yyOY2xJQNbWMlkY6WfRxaMzyKrVxvRZbzDKJrVWHjci8yVurAJziuDa11npBeS9c6uQ4NvXeLc26zWPj3DQttVIOxilE52d9Xbu1GCo6OhEQAnC7sHRIWdEiJBOCHSQUkLIJPzrYQuCVGLMTYhxLyL9q6CWEvXHegUWAKCZKSJkv83gmlmMpHJg8LIiLBmIkGkjYYVKsjZOyk04nORXu5Cu3lfIN1GeMyZ0zZnRgik/S%2BMUTg306ffFAb9n5V1eaMCZKQUhBl/gGK5rYRljzoEA0q5VKqNQgRCpqLU2pwPPl1RBvV%2Bq4MwENEaYgMHXSwRw%2BhpA8Gi0IWtEhyBNrkMEJQ0y1DjpVToedRh11mHpFYU9Dh4QuGJR4UwL6P0/oAyBtdZZukJDiMMtDKROhNmH0RsTRRqN4AYzUQICaWY8YyoURYUmedyZ4CwAYkWbi6YMxCczSxTj2Z83SFzbInjQkOIYFYi1BrfHBKZt4mmMs5iOuFmrVotrJZevNcsaJmw9ZRINovfZFFODJLORM5kly%2ByzGyQPR2%2BTb6JSKUwD2lAF4xyImYLuJwTiDjQhnEixbEjYWXtGqi7S6Iu1INBSQiRFI1K4FIAI1T/bVAjScKNedOAFMzRGpSNbB11qeWsW6GRnCSCAA)

## Links

- [source code](../../../../conceptrodon/varybivore/is_no_greater.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_no_greater.test.hpp)
