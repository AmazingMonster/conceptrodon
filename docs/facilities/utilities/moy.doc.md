<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Moy`

<p style='text-align: right;'><a href="../utilities.md#moy">To Index</a></p>

## Description

`Moy` accepts a `Mold` operation and returns the operation via member `Mold`.

<pre><code>   Oper
-> struct { using Mold = Oper; }</code></pre>

## Type Signature

```Haskell
Moy
 :: template<typename...> class...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct Moy
{
    template<typename...>
    alias Mold = RESULT;
};
```

## Examples

This function injectively maps a container to a type.
In the following example, We will create an overload set of `fun` using containers `Con_0` and `Con_1`.

```C++
/**** Operations ****/
template<typename...>
struct Con_0 {};

template<typename...>
struct Con_1 {};

/**** fun ****/
constexpr bool fun(Moy<Con_0>) { return false; }

constexpr bool fun(Moy<Con_1>) { return true; }

/**** Tests ****/
static_assert(not fun(Moy<Con_0>{}));
static_assert(fun(Moy<Con_1>{}));
```

If we only want compilers to perform an argument-dependent lookup, we can utilize `decltype` and `std::declval` to avoid defining the function body.

```C++
/**** gun ****/
constexpr auto gun(Moy<Con_0>) -> std::false_type;

constexpr auto gun(Moy<Con_1>) -> std::true_type;

/**** Tests ****/
static_assert(not decltype(gun(std::declval<Moy<Con_0>>()))::value);
static_assert(decltype(gun(std::declval<Moy<Con_1>>()))::value);
```

## Implementation

```C++
template<template<typename...> class Container>
struct Moy
{
    template<typename...Elements>
    using Mold = Container<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGwArKSuADJ4DJgAcj4ARpjEIJLBAA6oCoRODB7evgGp6ZkC4ZExLPGJybaY9o4CQgRMxAQ5Pn5B1bVZDU0EJdFxCUnBCo3NrXkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLCn0bIJMdQxX%2Byfnl0c/R59npzOBEw9wMwJMAGY3MDQS9MJDoQBPFKMViYAB0mMh2CuyAMCgUVw8zwiCWxgNGxC8DiuAFlUIjASYAOxWc5XDlXGEPOEIgjI1FsTHo7CPRgEBTk9mcrwZIx0zzoK6QgAiRNkTFJxARopB4oUwvJELZAOZKshJsB31%2BNu2/2tVwAYnhiKMrthVKwHph3scrbaA/9/dcAPIo4gvLKEj6A7lg%2BFQ/ko5hCrEQ7AUghUmnEgD6GmVrJZ5uNTPOcd5iYFKYxaYz50p1II6oYua4hasZotZYu%2ByuVC8bxj5zQDFGmFUKWIV1iqE8/cHEHpjKheY02IWHauxEwBFWbyoYiUFsL5vOgNH48n09n84HDCXDIRea4G63O73xDeWa8CYsp57B0ABVMFGaM/QbRpHGQXMmAJBICAgBhUGbe9HxXNw13JIszQWBZu0gyMYLgpRmmoRdl2fAQ22wzsVTwgiAS%2BANA2DXYriETBRyVD0vXoX1dntFjbSDc8zAhCI8S8LBlSrFFcyzTUJSlJje2uYBBwEu0LwEK8pyuJgvCIK4NIfSjV2o9d003ABabErlGdAQBAQ9aCUBSBUYnSx2Ba8DKM1ATIop8LNbV9rKuOz0wcggnJAH9MA8lEvOY64QLArT/mmaDYPgsjkObLA8STTBoEXRznKK2gADcxARczMMso1sAgPCFmc2rvEwfDS0InKSIQiAqpKsqHwqkAqs6%2BqQsasLmtavCOrEX8eosDglloThAl4PwOC0UhUE4NxrGsByVjWH1zAhHhSAITR1qWABrEBAkkdENAADjMMwAE4fq4QJPo%2BrhmWZaRNo4SReBYCQNA0Uhdv2w6OF4BQQHhu69vW0g4FgGBEBAFYCBSIzyEoNB7joBIojRThVA%2B/wbP8SQTOQZArikdEzF4TB8CIYg8CcrgZEEEQxHYKQRfkJQ1Hu0hdGFgB3CMUk4HgNq2na5eRkMjJJ5tUCoK56cZ5nWfZzmzCuCAPEp%2BhpyurgFl4TGtCWCAkAplIqbICgIC9n2QGAKQzD4OhgVdShYjl2IIiaRE1d4WPmGIREQ1ibQuMxm6KaeAgQwYWgE6x0gsFiLxgDcMQ3MT0uQUMYBxBL/AdwcPBqtAuWJy4oyNhuiJgQh/baDwWII1TjwsDlrM8Bh7heA74hZyUFV66MEejHupYqAMYAFAANTwTBFbDRha/4UXRHESWL%2BllR1BLhX9AblATssfRR7RyAllQFJXjRjgNlHKqlMJYawZgkaLwFlgL%2BrVOhZyyC4Bg7hPBtD0GEUkcwhjCzSBkV4Ew/A4MKK8WYgxEjCzsAg%2BoYwWioLyBQmoVCGA9GaKQ8o2DbA0IIXoaYrDMFkIkEsBQ511iCP0JrBG2tODGwZkzFmwA2YczelbCAuBCAkGVOJJ2Lst5LAQJgJgWBEhwOepICE6IfoQjBhoSQZhJD%2BDhoEfwP1xGQ2hiAa66J/BcH8B9H6wMgiSABpY/wkiS7I1RujW6W8cb4w9oTPWpM/YB3tjTNgnAmgsGqsyGyTBcQGHlFwH66IuDvR5nzEggs9C3zFtfaQt9FD3zlroUOysmCq3nhrDg20wlI04LrYmRkriGxkabFmeIG4c2KaUgsNtUB2wSJoiEZhnbRKxu7T28zvb2zJv7LZgcJlGCKVweGNBaARzRhAaOJdk7x1rrc1O6dM4OFrrncUBci5yzLhXKutAa7zzriwBuTd9otwQR3AB%2B1u7IF7rXAeNQ5YjzHvHSeGx9ozznjdRey9MCryBevCIoB1l8F3gfI%2BJ9kzn1kLUiW9TZCNNlo/EAocCnGDfjYJFsCf5/yjJwIBsUQHsogbwVAUDBad2/vAtuzgICuG4cLDBpQBFELwVkeVpBcFFAYGw%2BYDCujUN6Oqyh0rmE0J1Rw3htDciEM4TMfh7DyFCJERLLpPTEYiukSbOR%2BTJlFJKe9a2aj%2BZLO0Wst2eiDFGMoF0qGpAYYQmKTY5kgQfqgwhLY%2BxQTekepRrYKJrtsa4wJkTfWuyUnU1phwTJZsWAKGquzaqfr4yjHKeo6B1TqVX1pVLBlD99q6AhKQNpHT1auLdVIjgAz9bDKNqoGtdaG1NrhG6OZCyHbiQhKsgtGyUD7J2ckvdQx60pBSLmRtP1czNoILmOd9Tw4JEudc/aDzi43RfU8rOrz5l5w%2BcXUFmBy6V2rgAm6WB8WNzRbwMFbcIVd1UD3YEcLBAIpLki8eiJUXTwFpiheCQcV4uBYSmJO8mB70PsfU%2Bu0bo1K7RIOlghe3NI8c/TeoCrDv05fAbl/9OCbAqmx8BkCEjQIlXA41rwkEoOteg5B5ryEauIWquhNrNUkPtbqqVrwWFWrQXqph2m5M8K4cpozdqlUOrEcI1YoinZjq1uEz18761XHPeiK9gaKnruulu3RpB9GGKGHAiGsaYa/XRBCCEgRAZBLhhF5kvjs0HU4JEjGvnTGBAsSDZkcMPqSH%2BlwL6ZhQkQwhPZvpubt1dO5oliJYaHqkEXhkZwkggA%3D)$Done$

## Links

- [Example](../../code/facilities/utilities/moy/implementation.hpp)
- [Source code](../../../conceptrodon/moy.hpp)
