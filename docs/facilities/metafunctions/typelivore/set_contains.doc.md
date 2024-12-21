<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::SetContains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-set-contains">To Index</a></p>

## Description

`Typelivore::SetContains` accepts a set of nonrepetitive elements and returns a predicate.
When invoked by an argument, the function returns true if the argument is in the previously provided set and returns false if otherwise.

<pre><code>   Es...
-> Arg
-> Arg &in; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct SetContains
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check whether `int*` or `void`  is inside `int, int*, int**`.

```C++
template<typename...Args>
using Metafunction = SetContains<int, int*, int**>
::Mold<Args...>;

static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

We will implement `SetContains` using the method presented in `boost::mp_set_contains`.

We will create a class that inherits every element we want to check against.
Then, when provided with an argument, we inspect whether it is a base of our class using `std::is_base_of`, subsequently determining whether the argument is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, the initial list of arguments for `SetContains` must be nonrepetitive (hence the word `Set` in the name).

Since fundamental types are not inheritable, we pack every argument into a wrapper--in this case, `std::type_identity`--before the inheritance.

```C++
template<typename...Elements>
struct SetContains
: public std::type_identity<Elements>...
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                std::type_identity<Inspecting>,
                SetContains
            >::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCBmAMykAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0bEJCnUNTdmtQ109xaUDAJS2qF7EyOwc5nHByN5YANQmcW5ejrSEAJ772CYaAIJX1wSYLIkGD/tuBKeJjKyYAHT/2HobEECgudyGxC8Dh2QkwjVkTGCoJuIB2iS8EROyB2Q3QIBAHy%2BAH08FhBGc3oDHowCKC4th/r87iYAOxWG47Tk7B5PF6YN6E75sHYASQYCi%2BDmCwDBHK5EKhBB2ymIqCIAFlPOg7ly9myuTrdfK6o5sWhxQ9VIliDsIqhPDsAG5iLyYPZyo169nXT2e3H4vAKIkRJhKImoKiG30Gg5R6NG/0Ez6YElkxwfN5iiWYKVGC6kOPxrmw%2BGCRHiwu%2Bi7453efkeo2sgAi%2B29uubreZDZ5zyYrwOguYbEZ12AxEw1JBsp9XK8qSMO01tHQeziTeVqo1Wreo/Hk9pjLBcW9HePXeuAHoAFQ3293i93a83gAq2CEz9vD5uT7v9/P602bY3TeI46Apelzx7PkBWTIc/n%2Ba5iGAOlLhuOdpUXOEmCoLwGClARV3XEsPDLJE3mCAhSB2Ciryomir2nfEl21A5EOQw8ILPG5wRNPBkCJUMlAaCB1SwnC8OqcjBAY%2BkaxdTBZk7G4JlNASFCEggIDAMBMLqcT8IYN5HVQUlqxAWtXUU48OHmWhOAAVl4PwOC0UhUE4NxrGsHFFmWYD4h4UgCE0Gz5gAaxAeyWV%2BOIAA4ADYWTiRKNDipKAE4EjsjhJF4FgJA0DRSGc1z3I4XgFBAIrgpcmzSDgWAYEQEBFgIdFKIoCA0CeOholCH5OFUBKAFp4skHZgGQbEpF%2BMxeEwfAiGIUk9H4QQRDEdgpBkQRFBUdRatIXRWgAd2IJhEk4HhbIcpyQrczgAHkjnanYIx2Ib4tG8bJumyRZp2CAPB6%2BgbXWLhZl4GqtHmCAkG6xJerITqEaRkBgCkMw%2BDoB5iEqiAInuiJgnqU4rt4YnmGIU5HoibQcxqwLuuBAhHoYWgycOrAIi8YA3DEWhKu4XgsBYQxgHELm8HHKVHUwIXXMwVQcyOVZAooyp7pOCJzupjwsHughlvy4XSDl4g7SUJtHnFk4jBC%2BYqAMZCADU8EwE7Hq%2BZzArW4RRHEba/b2tR7uO/RxZQLzLH0PAIkqyB5lQRJqiF4bcX2JtTEsawzFK83lqwBOIHmOwGfSFwGHcTxmn8Kupj6GJWlyNIBFGFokhSVuGAbkp%2BnGSpy4EToRhrsY2iHmphm6YJej7pvbGn9u9AmBpe5mCGFiWFYJBujhHOK%2B6yo%2BkaxomqadhmsxAdwQgSD2ALIaCh35gQTAmCwGIS9ICLJDiX5MoskkBoSQZhJDxUKvZeK6V9CcFyqQfKcQuC/HilweKsV0qxTQfZSQXB7KZXiofQ6ZUKpVWfrVWGTU4YtRekccglBUag36mwTg9QWCOhZMNJgOwtji0vulX4yDFaLRICtVofsNqB2kMHJQodDq6CxmdC65M94HxKrwMqz02pHDelQHYbCOFcJ4QYBcXABFCMBsDRGoMH5xDME/aGdVqGMOiPQrqqAQb9AMZw3hRgzFcCKjQWguN8aE0OpTUm5NSAROprTemDgonMxpGzDm91ua835rQQWUTRa21WK5fAMtHBywVvNZWyBVZRI1tlVy2tdanH1vkqGxsonm0tpga2YsjB21ABQvgzsFBuw9l7RgUSJEBy2tI2QIcDquQURHe22crAx21sXJOKd0hpwzmuJZud87RELvLeApdB4GUrtXLIHdAiz2mP3TueR0jL2bl3ao687llwMiPeElyV6nOqF8t5C9V7fNruMaegLd5bz8pC7Kaij6cH0cQdhnDuG%2BOAPwwRvwNA3xEWDR%2BUMX6kDfh/fo39srwMQQIkBLJ8EsiSqA8BuCiGlU4KQ6qDt6pUKQK1dqbiXHEGYasNhZ8WAKEdNiR0Zjfh8iGPNXFYidr%2B02hIKZu1ZGzJ0CABISjLrC1UXdYhT1aFKnesK8aorxVOilTKpUQMPHWOiLYuIDiOXOPtUjPl7rQbmWQIkRIRJJXpSJDagSSKxrY2CdEUJRMSbUyiTEmmdMGaJI8SzFJnMCmYB5nzAWQtAq5O6U00ghTy4lPukrFWDwqmCE1odOppNGmGxaabNpKQOk226dKDlTsmCu3dp7b2YzZCSMmYqmZYctULOMNHGwqzjluQ2QIIWF5/S7MsHnDRBdSRHMThPM5EBXBPNINcoojccgvMeWPDuLdXk3LPQPdow8l5Xt%2BY%2Bqekw73zxXs%2Bn5YKP2nq/ZvBQvkd6b1hQallHBEUsBFWKiV1q%2Bzy1tbfJatiIYEooa/d%2Bn9KB7wpbEARcQ4j2XsiAgJqU4gsnQcyjRrLbBkMcbMcKIBQEoK4HY%2BKdj0qoLMBAlksCOBxAg7R8q5CYZ7zmjRh6onGPzHNqkZwkggA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/set_contains.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/set_contains.test.hpp)
