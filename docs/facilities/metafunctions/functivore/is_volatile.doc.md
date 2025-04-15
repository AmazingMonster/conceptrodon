<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::IsVolatile`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#is_volatile">To Index</a></p>

## Description

`Functivore::IsVolatile` accepts a function-like type. It returns true if the type is `volatile` qualified and returns false if otherwise.

## Type Signature

```Haskell
IsVolatile
 :: typename...
 -> auto
```

## Structure

```C++
template<typename>
struct IsVolatile
{
    static constexpr bool value {RESULT};
};
```

## Examples

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) volatile;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) volatile { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) volatile { return 0; }
};

/**** Tests ****/
static_assert(! IsVolatile<decltype(fun)>::value);
static_assert(IsVolatile<AbominableFun>::value);
static_assert(! IsVolatile<decltype(FunAddr)>::value);
static_assert(IsVolatile<decltype(&Tester::fun)>::value);
static_assert(IsVolatile<FO>::value);
```

## Implementation

The implementation of `IsVolatile` relies on extracting the qualifiers and specifiers of the function-like type using the metafunction `Analyzer`.

```C++
template <typename F>
struct IsVolatile
{
    static constexpr bool value
    { static_cast<bool>((1 << 7) & Analyzer<F>::value) };
};

template <typename F>
constexpr bool IsVolatile_v
{ static_cast<bool>((1 << 7) & Analyzer<F>::value) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcAJykAA6oCoRODB7evnrJqY4CQSHhLFExXPG2mPb5DEIETMQEmT5%2BXJXV6XUNBIVhkdGxCQr1jc3ZbcPdvcWlgwCUtqhexMjsHAD0AFTbO7t7%2B5vrJhoAgls7ANQAIpiJrozIeJgKF7tHp%2BcHX3vvJ8d/ZgAzMFkN4sBcTIC3MhhvhBJDsP9/p9NhcTsxaABPABe0VeO1%2BBEwLESBiJEKhBExd2YbAR/2GxC8DjRGJx0WUxFQRCpdwhAHYrPyrpCrKd/kSSWTMBS3LzGKwZQAlTAEUgXeW0zAAOl1J2IwAU9NOjOZBFZYnZxE53O51MwkLcKoIEH1ht12rmxr%2Bgv%2BF39F0mjmQFzQDGGmFUiWIgYI6BAIC8wQIgLMAH1zQA3MReGUmQVcWWOi6A/MiwFin3lysS4mkpjkx2axUXZ3q5tsD1uo2AxEmghMlnoy2461cnn2x3O10GhQeuYXTOeBt0B29pG%2B04B2MrkNhiNRmOwhNJwSpjOLnN5gtFqEXfkCtwXQuO4ul4WijfVpGnSX1olNvaWoXAAYgw3qmkObKjiAFyJF4ES0HgIbDlio42hOdyOmBCICkK37ir%2BdbSoBNItjh679oO5qoVa2EMJs3qwfBiHIRaaEcuOdpYVCFF9j6lbbkGbH7kSh6xvGibJueWZXn6Ab5oJ24Bi%2BULFmYj7ycpFwQFp2kqbeT6AhCACs/H6cptHoVx8r0QiCbZt4DpbvpXouf6ZafuKH4Vj%2BJx/iRlJAS2ACyxJge2wVsBcdTUcsa78ZBNHQdEjphSwYExQOZrxQmjGUSczEIUhKEpWOtq2VC6V8RuSn%2BsJe4CAe0YSSe0nprJTl6YpenbqpbjFi%2B/IDe5ym6aNFn9W%2BpnmRZAZWZxFWTlV4Xgb2DlyRNAZuSc26eb5hG7QGXipEYoYGAoCgZvaFJXFlcXEGuNY%2BTWRFSg2a5ylFMogQA8t6j0AI5Jo9LxAyDzx4eYABsf0JqgdzEA2JAQF6vkflRZrsXRvH/QVRWsaVI6pVCWCgvKulmLDv3w4jyPEKjaP8T1o0NaGTViS1x5SWeHWXl1o0s0d2lDSNwtjb1%2BlTXeL5mZL2kLcQjpk7QFMw3DIAI9E9OM/ZICObm8sXDte0vX524ncEwDnUwl3XXykJ3X9XlVi7yLfB7Pzu5cACSUrEow9Q1Pi2y/CinvfL8tbvY2QVkdFIEQdlLI%2BwoABqy6OPQtV6WzomRi1ESoJ4/OG4Lgo7sGaaiMMjpF54CJQNLT78guMPY6O2F6wbmBt2b3kEX8b3/nmccKgn3r5%2BJ9e0BcqcZ2Sq5ppmtWV8h1e2wQdfF7QjcQM395t1THck24ifrfrV594P3sRwSt%2BotgqisKSMpvA/d9Rx8uwXFQXgMA4dILx36nGCEhEIFxky/3/hAZM6pkybC9BXR6BBlgMAuBoUUAoRSHRRBcJgRcWDBAIfQaBACajAPvqcS2Z0TiEOIYhTAIF/63UgYIWBgh4GCEQYuTOq43bf0uH/ch6Q4KoGTNEShod/hgOCDKJgXgiCgX/icdA6AYyKQhFTYR2CBFnB/skCRMYlFsBKHiYRgCmoh0OAyZO5oAAqzwiRK28nVNh4CZRQOERwtUbCCA8KXIvUhmiUFoIwVgzyA89F4IscHVAERtCYAcFImxmMWTO1cXpKBWskZEAZnMHxXD/ELkCSuYJyDVRhMwRWXRUSDpD30ZcRxwwUm/AammW2ShGgQDAGAOe6c%2BHZ1Jkk1W9pqD/yZhtJyaNKztM6dEF089BmfToagIhzBGHMLWtgKZuYZm2N3B0y6Cyel9KWUEz6KsKZbNUeoyZl9pkuzmcc7p5yymXJGWrKmzTnEJmEfcnu%2Bz%2ByHPma8gZFzsJ4x2Q8vZLsOALFoJwEyvA/AcC0KQVAnABqWGsIGJYKw8xAh4KQAgmh4ULAANYgBMoCbU/ITImX5FwEyZguAAA42XlDMNIRFHBJC8BYBIDQGhSCovRZijgvAFAgBFaStF8LSBwFgDARAmtFHwTVBQCAaASSrmIKERUnBVBsuhgAWmhpIC4wBkAhikNqMwvBMD4DyXgeMbR%2BCCBEGIdgUgZCCEUCodQ8rSC6DaAAdyRokTgPAEVIpRWSjFnBfrqsURcVAVALjGrNRaq1NrnySHtTpDwur6AaKJXMXgcqtALAgEgHViQ9XkEoPWvVIBgBSDMHwOgzjpUQAiAmiIxDiCYmjbwQdzBh2/QSUkuVxKdVsEEL9BgWIE1YAiF4YAbgxC0GldwXgWAWCGGAOIYN%2BBHqAMzM8BNkYkmKLWMSiRvL0VIQiEjYdHgsAJoHHgQVe7SCXuIEXJQNxD1GHAaAeVCwqAGENGnJ4Ybfo0lHX64QohxC%2Bo9fIJQagE2hv0EelA1hrD6DwBEaVkAFgIwoZwU1sJHamBxZYMw4qAPEFdVeij7QZ3pBcAwdwngWj%2BD49MfoZQkgpDSAIMYrRxN5HSCJsxYm7DcYEF0UYAnxhccsbUEYPQ5EzAGBMXT0m9CTEaAp2YXAFgKHxasCQsaODItFQmiVmaTXmstda21BaNIQFwIQEgWjARWcrWSuYCwECYCYFgGIqNSBUskLSuIgJ%2BSSA0JIbl0NhUmWhgkXl/LSCCuC9qaGXBoZsriJy6GJlJDMuS9DZzwaJVSplSSsLiqVW1rVQQDVTbtVrIbaWg1bBOANBYJmfkpqmA2zOvEbUXBtToqdQFtjbqUNevQ9ITDAacPBt0J2iNTAo17oc05sVvAJXJp66m9Nbns2WtBEe58cR5uLaLQNvVQWzAVra5BxVdaPulr6y20tKADBGHiFwEVNBVaSMoP24N46Ggjr/Ujyd06HDIfnYHJdK7T2YHXZu7du7iUHqPSe9FZ7uOXt3Ut1Qt6iTIcfQml9b7MQfrWOi79v7iUAaA5gED5Orbteg0wWD8HEOMGQ5hjbPqtuyB20G9F%2B38NGEI4xmwL7yNxao0AmjdHARXAY1YJjLHoirY43F5T2neP8ayDJwI%2BnRM5AkzUEzbRciSYYBZwzWmahqaaBpmT1v/e6Z90p4zQfTNh6d4p%2Bzixlh2as/oONjXxWcDux5mb1s5sLY0DpfzeSgshd%2B9WiLUWYuUAcwVorL30v0riPyfkgIMuSAtW0c7ibJW2Fa1WhVSrVVLGu5q5tgPojDbWGNnNLAFCZhDJmOb0phiOudSQV1egZdoblyhxXuGQCAlIId47MaU%2BOfjU1pNKbzS3dUNP2f8/F8fWGO9kteJzCAkBD9vvNaAev7IFqkHAYOfRIRIZeeINMJfAgNMW/LbbtOHPtAdIdFHYlNHTEKdRJTHP9bHRdZdFHSnAnDdLdWgHdZDMnMDTnfdPAc9RwGna9enZAO9JnQQKoFnUjNnDnL9NjHnXgPnFIAXYkIXNXP7UXcXTABDJDP9Tfb1CQeXf1bDJXHQffVXYwIjSwEjMjeASjRIajDYY8Y3awZjC7VjdjbXazKoFTPwCAVwd3UgR3IoZ3D3V3dIGwz3GocPUzcw7TAPGwkPToGPewuPIzboHw/wvoQI6zWzH1U7c/dPDgTNO/OfRcR/IkZ/PzVfMtYLL/MLcvaLAYOLfLAVEAMwF7D/BldLKHDQD/fkcrNPC7TgFrWVbI%2BLEANve1SQDLNlSQfkTldlNlao0/QEGIuo7vb/BzB1WorvULSDBYADVIZwSQIAA%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/is_volatile/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/is_volatile.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/is_volatile.test.hpp)
