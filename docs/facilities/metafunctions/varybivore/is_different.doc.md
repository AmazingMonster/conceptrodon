<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-different">To Index</a></p>

## Description

`Varybivore::IsDifferent` accepts a target and a list of variables.
It returns true if the target is different from every variable;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target `different from` V<sub>0</sub>) && (Target `different from` V<sub>1</sub>) && ... && (Target `different from` V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsDifferent :: auto... -> auto
```

## Structure

```C++
template<auto...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<1, 2, 3, 4>::value);
static_assert(! IsDifferent<1, 1.0, 1>::value);
static_assert(IsDifferent<1, 1.0>::value);
```

## Implementation

We will implement `IsDifferent` using `Varybivore::SolitaryIsDifferent`.

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsDifferent
{
    static constexpr bool value
    {(...&&SolitaryIsDifferent<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsDifferent_v
{(...&&SolitaryIsDifferent<Variables, Target>::value)};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgZgAcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2B7sA1EKehC0AngCSCgAieFRU8YwEhwe72yYaAIIEmCypBl%2BJgCbiYXiIpEOYKIwOwny%2B42IXgcx1OEyut3uj2Iz3hJgA7BZDrNHMhDmgGONMKpUsRDjFUJ5DgA3MReTCHAkWAhIzAEm7Aon8wV476/f6Avkg6GoQ4ANRaeCYMXosPhiORLxOtDOxAxdweT0EwLcCuISpVmEhZotqoCcO%2BXOJzVJ5IEVJpdIZTNZ3g5XKoYiUwoCQvxAtDoq%2BewOqJ16OuBuxz1eBw%2BYr%2BAKYQOl4NlABUWsBMARITKAHSVm3K%2BgKNXfDUoxNYo0EPGE%2BGHLvO7N4MkUj20%2BmM2gstl877dzmEiCV8vmABsi%2B1uv1LZxxpB1ctCkhheIxbb9pAIF97KWIasjvDIsdGYl2aloLzh33h7Lebn29r9a%2BA9%2BnrDkyzaGhuBAAPrMu2FizpWi7LmiFwgcmm6moqNaYLur5FiWsInmemAXjekZ3tGbzkRR6ZkbG%2BaYQQCipvsVExhRrFUeqLp9uBTAKEorQQMhrYmlwkJmJCQSHJIeGnuOF4kQinHINxvHxAQEBgGAhyCWBwmQlw5YaHp0kEXJV4Kb2Sk8XxanabiIIiYc%2BkaMZsmChwKy0JwACsvB%2BBwWikKgnBuNY1jEmsGz%2BmYAQ8KQBCaO5KwANYgF5ZjlviZiSEkSReRoACcaUaAuSRBJ5HCSLwLASBohl%2BQFQUcLwCggIZ8X%2Be5pBwLAMCICAawEKk4LkJQaD/HQ8SRKwWyqEkC4ALQLpIhzAMgZJSOWZi8Jg%2BBEOa6B6PwggiGI7BSDIgiKCo6gdaQugiQA7sQTCpJwPAed5vkJYFnAAPLgkNLyoFQhyzQtS0rWtjmSJthwQB4430HS5gxUsvDtVoKwQEgY2pBNZAUBAuP4yAwBSGJNC0L8xAtRAMTfTE4QXG9vCM8weq/TE2iYA4LOkGNbCCL9DC0Oc31YDEXjAKCtC0C13C8FgLCGMA4i3fgOIOHgzKYd91I8%2BCWyxeEvzlQFOoxM9eoeFg308ng1UK6QOvEAySg3H8Ks6kYCUrFQBjAAocp4JgD2/akjB80dwiiOI53R1dajffd%2BgqygoWWPoeAxC1kArKgqQNPL83jOgwI3KYljWGYDUu/tut590PMNC4DDuJ4HR6KE4RDJUIwiUUWQCFMfgDxkQ8MPMwwJCJdjN70ExtB3%2BSz3U88CH0rRT33M%2B2IvI96LMW89ws/crAoEWbBIH0cD5pD1bwjWg3Ni3Lat60w2YcO4IQJCctFXA0ZxV9isBAmAmBYASBAZKBRyz5QCPiSQGhJBZQXLVLyC58r6E4JVUg1UYrlgXFwEq%2BUkjEK8pILgXl4ELnvt9RqzVWrAI6ljXq2N%2BoA2GoTYmSMppsE4C0FgzJ8TzSYOSAwRhHL5XLE5bau0SB4AOiJaOJ047SATkoJOt1dBiSei9FmN874Px%2Bhwf6g1wSHGBlCYgQiRFiOQBI4AUiZEGThgjPGSN/4BDMEAjGnV2E8PiCNImqBEYjEEcI%2BaDiVZcHylwQylNqa03prdNmzMnZpI5lzZufMBbPGFqLcWmBJbSzEHLPmSsvZbAChreeOt5YBX1sgQ2fMTZ1G%2BhbK25wbbVPRuaR2sUXZu0wB7ZWRhvagBYXwAOQcQ5hwjn5WKKjY5nXUbIRON0Ao6NTj7SuVhM4W1ztAwKhdsjF1LuXPZ1da7xHrkc8%2Ba8tbOAgK4A%2BIlu7lGnnoQeDQ3lpHHg0beixV49A3vvZeo8m5PMaIvIF/c979D%2BUfAYJ8vmANWOsK%2B6LypGPoZwaxtjRHiJVs4py395HIwAb4kBpAwEQJGMc8quD8HSOQfiah%2BJ8QBBQZIJaIljEMNsEwvxrD4DsIGoDYJgTiB8K2IIiGLAFDMjJMyWJ5ZJTjDkb/fah1ZCqNWRdeQmjNk6BAEEPRr0FaGK%2BrdRqZjAaWJBvK5airlUsjVRql48NQkePiF4gI1KpkBJ9fjKVIakanmQKkVIkFYngU9dxGxS0%2BB0CSZQFJAVMliwyUzLJ3NeZOzyULEW2aanFKljLcpTtKnjN6aQWpWt6l61UAbX4rTBDtNup0i4PS7b9L5kMjIIzPbjPCJMzG0ymCB2DqHcOkcnbLNOhINZl1jXJzNTs4wGcbCHPgPnU57pODbFLunKulga6Pzroohuxy57Qtbu3PIkKPm92Bf84o2Q/k/OyHC3ed6GibyXk%2Bw%2BjyAOwtRTvQ%2B4LgOz3A58yD6KL6YrOtauhtr8XOsOK6lVHrHzjHJdqrxgD0Y0rpZAygN9mWJGkQEAIXk8qUNqrR/EJU0MNU4IwtqNKUqSHxJtdlXApD5TZfArg%2BJsEcACDa9jTVmGYxvltNjj8ONycSs7eImRnCSCAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/is_different.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_different.test.hpp)
