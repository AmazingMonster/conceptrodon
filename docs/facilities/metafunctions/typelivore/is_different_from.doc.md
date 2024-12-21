<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferentFrom`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-different-from">To Index</a></p>

## Description

`Typelivore::IsDifferentFrom` accepts a element and returns a function.
When invoked by an argument, the function returns true if the argument differs from the element and returns false if otherwise.

<pre><code>   E
-> Arg
-> Arg `different from` E ?
   true : false</code></pre>

## Type Signature

```Haskell
IsDifferentFrom ::   typename...
                  -> typename...
                  -> auto
```

## Structure

```C++
template<typename>
struct IsDifferentFrom
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Examples

```C++
template<typename...Args>
using Metafunction = IsDifferentFrom<int>
::Mold<Args...>;

static_assert(Metafunction<int*>::value);
static_assert(!Metafunction<int>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<typename Target>
struct IsDifferentFrom
{
    template<typename Element>
    struct ProtoMold
    { static constexpr bool value {true}; };

    // This partial specialization will be chosen
    // if `Element` is deduced as `Target`.
    template<>
    struct ProtoMold<Target>
    { static constexpr bool value {false}; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr auto Mold_v 
    {ProtoMold<Args...>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCBmZqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BfoF2mA6Z9Y0ExZExcQlJCg1NLbntY31hA2VDiQCUtqhexMjsHOb%2BYcjeWADUJv5uBACeyZgA%2BgTETIQKx9gmGgCCL68EmCzJBl/HpwujFYmAOABVGsBMAQnh9RsQvA4DgBJBQAETwVCocUYBAAYsRUCwPiYAOxWN4HKkHL4/P6YAHnS7MNgHbD0NiCWGU6nwxEEA7KQlEACynnQH2pR3JB1GTEcyAOaAYo0wqmSxAO0VQngOADcxF5QWSLLcjWS0ccLNLLf4Ke8eVSAPRO8EIPAKA7JXp4MSyy7IX20PAAL3lmQOAHc6LQtaDkAg0oxJdSXQdMUcAGwadnfXEmbPpz1YdCIzDoA5MT0FjQQ4hQmHZgB0KaptN%2B8oZJ25rylfKRQtQovFALrDZ7UpNsoaCqVAlV6s12t1Bu8xvJVDESgtVptVpJjpp3w7/xOTOBbCbV9ewGImDzgke/meh686SMBzFtArxzRguFqBfhKJw3neD4EAoV4ts%2B%2B5vK2R50p2jJAiymBQa89ZPi%2Bva8jOeCKsqC4apWXhEJ%2B4pXHqRyHiag7Dt%2BAIYcAkFXk8IAgKu5qkra9o7naB6vE6ABUImiWJTofMJIlgtgQhgqJElvFJYniQJ7b0shzIguhmE9m%2BYTAJ%2B0JMFQXgMF0AhHP4f6ohiWI4oIBJEgCYQwjBbzsUBjGYVBsL8XBbxygqVxVkoTQQCKxmmeZtQMC5ghCWxHGGpgiywa8QX4SFChhQQEBgGAkUNNFFlxScrlJZxqVWhwyy0JwACsvB%2BBwWikKgnBuNY1iyqs6zGmY/g8KQBCaLVywANYgA1khNhokhcKS/gaA1GhmJmmZmAAHFt%2BicJIvAsBIGgaKQLVtR1HC8AoICnaNrW1aQcCwDAiAgKsBDJKR5CUGgPx0HEEQgpwqhbZmAC0maSAcwDIIqUhNmYvDloQJB4Ogej8IIIhiOwUgyIIigqOoD2kLoXCkJGdzJJwPB1Y1zVje1nAAPKkV9AqoFQBygxDUMw3DBwI2YBwQB4/30Jq2xcIsvD3VoywQEgf3JADZAUBAKtqyAwBSEkNC0F8xA3RA0RM9EYSNGctO8BbzDEGcLPRNonT3cNf2cgQLMMLQ1uk1g0ReMAbhiLQN3cLwWAsIYwDiP7eB3l0eqYOHbVqp0pGbMNrnVEzwbRHcDseFgTO3HgR0R6QyfENqShot8MfBkYY3LFQBjMQAangmCRizzI2wTwiiOI%2BNY/IShqEz5P6DHKDdZY%2Bh4NEN2QMsqDJLF4fg6MwFoqYljWGYF3V8Q6Mp/AywdKVLgMO4nitHoISzKU5R6Kk6SxRMfgU%2B/hQMP0L8hgUyvrFHo4x765GAdUV23RpgAMGPEYB0wv56DlE0eB8xEGXz6hsCQ9MOBNTOkzS6PMwaQ2hrDeGs0RYQFwKjKWg0ZZyxbssBAmAmBYHiBASaIBJD%2BCbAATn8KSSQ80zCSGzCtTMAi9ocAOqQI6Q0myZi4JmLaAitqqJmlwBqQjMxENJpda6t0Rotyeq9JW712bfQ1lrSWQM2CcEaCwPUpJwZMCVAYD8XABFNi4HNZG%2BAiCnwxhTMeOMR7SDHkTSepNdBJCpkwGmEd8GEPOrwS6bNPqkQOFzSsxAXFuI8XsGOQtfH%2BI0KLcWqtJZHEGmYWWpiHqK2VkSGpcQfqazadrZxrjwYlKMD4rgp0DZGxNmbUmdsrYDymQ7J2LsHADw9rib2vsmYByDiHWgYcB5R0bpsNq%2BBE6OGTqnZGqgM5fAHjneqpN86FzOMXA5ctT4V2GtXWumB67RyME3UAzS%2BDtwUF3HufdGAD3CcPPGUTZAxJJm1eJM9m77ysAvfOK9uHtQ3pkLeO9fwosPsfOIITz6ryqDUTIN8745G/kEW%2BGDX4/wKJ/CBtLf6xQZUA8lMC6jINZag6BpUwEzBKAg1BfKaXit6JyrBKw1i4JlrItJxDOD5MKe4zxpSfF%2BLmqLOhwS6lDUafLcapA2EcKGJi258jFG%2BPmqSXRpIlqSHEVDCm6TmZXVsCYk1isLFIA%2BhzTpdjAbAw4M4/mLAFB6kVHqbV9JRiBPoejTGsgInQsHnCqeeREnJLpkqxmhjWbWM5tzCN0Mo0xv1PGzsowqndNqdsfwxqzGWJDerX6DahgxuSMkSiPirgJoICFApUM%2BB0DGZQCZbVZl%2B2GrO%2BZrsllEk9qsv2hzMCB2DqHcOw09m/OeaQI5MDTlM3TsgTO1zBC5zuUvB5TzS6vIHh8pM3zG4GTMW3Jgndu6937pXSFuMJAwsJhPeFOg8heOMPPGw6KL5Ys3pwJ0O854H0sEfDJJ8z4YsvoK2KVKUEUyfqKzBb9mWZEI/kD%2BmQZUCopby3olGQGwOlc/MVSDGP8o4%2BgtjpHFUKBwXjVJhaLqqvLQcStsaa1fDrbQoJJBDVMKaQrVh7DOGUHwTahIvj/D%2BAaqtBaJ1dOkjUQY0TXqbp3RYaQKakgGqCIaltdaAjJACKWsIrggRbn%2BBExkzgzDmn4KRmZvzXrfXLGrukZwkggA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_different_from.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/is_different_from.test.hpp)
