<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Label`

<p style='text-align: right;'><a href="../utilities.md#label">To Index</a></p>

## Description

`Label` accepts an element and a key.
Then, it returns a map from the key to the element and a map from the element to the key.

<pre><code>   Element, Key
-> idyl: Key -> Element
   lark: Element -> Key</code></pre>

## Structure

```C++
template<typename Element, typename Key>
struct Label
{
    static constexpr auto idyl(Key) -> Element;
    static constexpr auto lark(Element) -> Key;
};
```

## Examples

This utility creates projections between an element and a key.
We will make overload sets for `idyl` and `lark`.
Then, we will retrieve the element corresponding to the key `Key<size_t(1)>` and retrieve the key corresponding to the element `Element<-1>`.

```C++
/**** Element ****/
template<auto>
struct Element {};

/**** Key ****/
template<auto>
struct Key {};

/**** Lexicon ****/
// We will use this helper template to create
// overload sets for `idyl` and `lark`.
template<typename...>
struct LexiconHelper {};

template<auto...I, typename...Es>
struct LexiconHelper<std::index_sequence<I...>, Es...>
: public Label<Es, Key<I>>...
{
    // Pull every `idyl` to the current scope.
    using Label<Es, Key<I>>::idyl...;
    // Pull every `lark` to the current scope.
    using Label<Es, Key<I>>::lark...;
};

template<typename...Es>
struct Lexicon
: public LexiconHelper<std::make_index_sequence<sizeof...(Es)>, Es...> {};

/**** YellowPages ****/
using YellowPages = Lexicon<Element<0>, Element<-1>, Element<-2>, Element<-3>>;

/**** Tests ****/
// Retrieve the element corresponding to the key `Key<size_t(1)>`.
using SupposedElement = Element<-1>;
using ResultElement = decltype
(YellowPages::idyl(std::declval<Key<static_cast<size_t>(1)>>()));

static_assert(std::same_as<ResultElement, SupposedElement>);

// Retrieve the key corresponding to the element `Element<-1>`.
using SupposedKey = Key<static_cast<size_t>(1)>;
using ResultKey = decltype
(YellowPages::lark(std::declval<Element<-1>>()));

static_assert(std::same_as<ResultKey, SupposedKey>);
```

## Implementation

```C++
template<typename Element, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Element;
    static constexpr auto lark(Element) -> Key;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIABs0gAOqAqETgwe3r4BwemZjgLhkTEs8Ykptpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJydIKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsqfRsgkwNN4dnl9cnvydfF3OFwImEeBhBJkCbgIAE9UoxWJgbthnowCKQbrD4cw2DcANKYGGQ7BA8bELwOG6hJjxWhAkwAdgsNyBNzZN1mjmQNzQDHGmFUqWINyYXiINzw6BhtAgBJhSxuAFpicjUYJIVZLuyOc0uTyBPzBcLReKDMQANYQFGgtEK5WBbD4wka%2BkMgAiLsuQJ%2BfyOAJ9yNUrCeSM%2B3t9/3pXrMgQiyG8WBZULFdEIRId9JjcYTSMhbmQ43QWCoxMzsYY8a8ibzvM2qQIClLXu%2Bh1VNsEH1OQJBYLemDzJtQTYuZIpBDbL3HjKs7s9gJbtzlnf2AJ7Tz7A7FQ4zl1HlKX08ZHsCmvnV1boQFeF5y92/u2NwA6kiAO50Wg3LxKTEIPAKG4IHU8LCmu4JIuKyDEJgG7fA%2BqAAG4JLQqBMOgHKYA2Nz8MKJhJBokrSrhGgigwaFEWa5pEQAdN2oLrhCUJYgibBUaxw57uOl6qNeAgABJAQkLJMkec60b2DFuIOrFUXcGJMTimDSdgjY7iOBDkpSXE8Qw/G0MBeaFiAIARFgqgAPpKAAjl4jCbHmdzScSGLKY5qkgDcqReLEtDXlSNJ1HmykYnK9mlg6jlesJWrstsD7KF4tAfpgiHEDCLJ4QRdJ4ZiqA/kiyDrFBHYKGg8I0dFbJfhEwB%2BbSgUKMFzpQncYXYEZmWuae2qxTc8WJTcyUJGl5EtJR2XigQgE8oVaIcqVimsuyVVGLVAVQkFTrpm4LUZg6RkUZ1rrHqeYn0f2jFwsximscp7HqWOVJXryQLuZ53m%2BVpvK6fpUKGSALBMOamBmSZAoWZg1m2edbiZAAXpgqBUNJVoKEsTnIgormOoes4nlG563AAmnUyEvsoTDAJg/5hpcy01cTiWoGTFNU0mbqPdxz3rWqBB5ho6PWpOeaKlwAs88LZhi%2B2vNQoqgStaJC77DcAAqVOYTTVwPgAShhxB4INeUDTz%2BrEFBCjpKR1U5UbQPDXhIW/Xg8NmQQEBcGjGZ4eVFx0zcQheKkRSYOgguzZC7Nh%2Bqsui7tp5%2B7rCgJQQUdToE7NYPGTFAhADOk%2BTlMKO1Uoyn9me0PBYh5o7MO6teZmiOMBnO8DMvYO7nskg6EBLL3itqW89dMAoSitBAf0KIiZnD3mifJ6nGIB0HGQh6nxKeydsE3Lr6kG4htuEqb5uW/gK0TVNdTS%2BlGhrzHpbe0CftL8H6AHunm0GXXyAN8PMswy3rtiQdzCvHTIK0560AIG/DOmAs6XRznnJmBcqb7VGuPAg6AjLl0rnSbm0thaxy7u3XuG98aciHiPBIbsJ5TxnlCCBUDCSL0Di/R22AN4cBWLQTg/heB%2BA4FoUgqBOBuGsNYDkawNi5hjDwUgBBNCcJWOaAIkgqIaAABxmDMAATm0VwfwGj1FcAZAyaQ3COCSF4CwCQGgNCkH4YI4RHBeBFzsfIgRnDSBwFgDARAIA1gEE8uiCgEA0CPDoAkKIiJOCqHUUkRUKQbjAGQNyKQVEzC8BDoQEgko9D8EECIMQ7ApAyEEIoFQ6gPGkF0FwUgL5iBMFSJwHgXCeF8IUUIzgAB5MUQSbiIxuLE%2BJiTkmpNUWYG4EAPDhPoDhGRSxeDuK0CsCASAwmpAiWQEJ6zNkgGAFIMwfA6AgmIEXCAsQOmxAiC0GEzTeBXOYKlLpsRtCwPcbIsJk4ukMFoLcqpWBYheGAJJRKRduC8CwADIw4h/l4Cgg4PAiEwWCIFLAsUWxZERBBOYwRPlYgNNSh4LAHTd7WPBaQFKsQV5ulBIYYAPkjAKJWFQAwwAFAADUDYvi6diO5pThCiHECU/J8glBqA6TU/QdKUBiMsPoPAsQi6QBWKges2QwWKkLBHUwlhrBmEcSlfWWAlU926G87ILhSJTD8LUsIEQhiVBGLUooWQBDWr0C6ho8xhiJFqXYc1Ag%2BiTE8B0PQ/qEWBomAMe1CwnW2Cje6v1UbvWOt9SsBQkjNgSFaRwXh9iOlOMGXEhJkgkkpJuGkiZVp8BEDmYED2iymUrEAqhEYprlGSECFRbRgRTEaEkGYSQeEND%2BCSNo/QnBLGkGsfWqiSQuBJHUdooxSR/CSH0T2pI%2BaqlOJcSANxTKvG%2BNWf43pYpyCUB2bMqJbBOAtBYPBBkiomA8gMCtLg2iqJcDUZkmtOTMG1JFYUoV0gRXlPFVU3Qhz6mNLuTmvNDjeBOJ6YEsU/SqBFuGaW%2BMdKK2fu/cRKZqAZmCXMIEMwCy5GHpPVehIF7QnEY2bMlAb79l6LsTQSBCQzkXKqQ8m5fL%2BNPJeW8vlny0TfN%2BR0gFQKQW0DBbIyFdKYWCPwPCxwSKOmooKiCPlWK6gdLxQSmERKtiCNJXyyl1LaXQuqoellFMOVcp5YwPlQHBXFNA7IcDlTBFQalYynVVg5V4pNSqtVBpOCaowdq2VFh9VIcNZKFByqzURr8BAVwiaQikRTYsZ1GRXU5BDfkArxRsh5bjeGhoQa2glZtWlmryaY0%2BrDQm%2BrbW5gtdTdm1Y6ws0ewnbm9pO7OCYZLa%2B3DH6v1qMmbgbJdaG1UY8b3UgLasCJFNeYqdM7P39oZP4bRJjAgDqHeu7djjOB7oPSto98AT0BKCfR2jxAb1bHvYklgCh4LcngtNsC4xf0LdyYB2QwHPP8p8xKkAwQYNNPBfBkbl2OAob6QM1Qn3vu/f%2B32cYkzplMdIzGQIlGlmeJo4xzZz3KfMZ%2B0HMyf3tFmQBwQMyGPQPHO45QXjgihN/NkXz55ryHBieI18n5fzVOYEBcCsQ8m%2BVKehWZiFcLzWaaqdp9FenBAGaqUZm5pmSX6zJbIqzSgaVQvpXZ27Dm2WcswNy3l5L3NFIkF5spYrfM6BhwF4wcX5WKvgOFhoYLtiGSC3qg1CQjUpdNdVi1mWrUddtbl7r%2BXSCeuyNlzPpQ09Vcvul2r2X4%2BRq6%2BUVrSb%2BjF%2Ba%2BXnrg2M39eKYji7SGxvs5uF9n7NxGdURZ3Nv9i3SdNrW9BDblAc07ZADoqigRAj%2BAMeu2xs%2BGSLpb505xth93LeWUokAkh/DduMQyWx6jJB6K4JoswW7zGBCR63jfZPVvmIyWv3d2/FEUu4xayQQA%3D%3D)

## Links

- [Example](../../code/facilities/utilities/label/implementation.hpp)
- [Source code](../../../conceptrodon/label.hpp)
