<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsEqual`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-equal-to">To Index</a></p>

## Description

`Varybivore::IsEqual` accepts a target and a list of variables.
It returns true if all variables are equal to the target.
Otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> == Target) && (V<sub>1</sub> == Target) && ... && (V<sub>n</sub> == Target)</code></pre>

## Type Signature

```Haskell
IsEqual
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto...>
struct IsEqual
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto...>
static constexpr bool IsEqual_v
{RESULT};
```

## Examples

```C++
static_assert(IsEqual<1, 1.0, 1>::value);
static_assert(! IsEqual<1, 2, 2>::value);
```

## Implementation

We will implement `IsEqual` using only `<`, meaning <code>Variable == Target</code> is expressed as:

```C++
(not (Target < Variable)) && (not (Variable < Target))
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsEqual
{
    static constexpr bool value
    { (...&&(not (Target < Variables) && not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsEqual_v
{ (...&&(not (Target < Variables) && not (Variables < Target))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCBmXKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxibaY9kUMQgRMxATZPn4B1bWZDU0EJZExcQlJCo3Nrbkdo739ZRXDAJS2qF7EyOwcAPQAVLt7%2BweHe5smGgCCO3sA1ACSLMn0bIJMdVf7J%2BeXR99HH2enZwImHuBiBJgAzG4mF4iFcACpNYCYAikK7QogAOixADUmngmNF6AoIdgAaNiF4HLcFNgAI5eMQAkwAdis5yuHKu00cyCuaAYo0wqmSxCu0VQniuADcxF5MADOVcWRYrhAsRjzAA2LUQBioAiqhHEJEGiFuK644j4wmYBQLJVmbWOq56g0QS3WolKyHwxHIhYBpXMgAiELZ/xDYaZ5yBIJe8sh6NQvuNyNRSfVHoJRJJAP5guFovFkpuNPpYgA%2BlKmazVeqtTrXYa/aafVmbXaHU7NS79ar216zSmTQH7SzQ%2BDwwCvj8Dn8Z1dsKpWA9MG9jtPZ79o2duXhkBWmAolM0IKW6QzaGaklcuBiNKiuCSQCAZd5MAso%2Bc9wejyeCBAYBgNSF6MpCN6BFcZjPq%2BsofmGHBLLQnAAKy8H4HBaKQqCcG41jWFyKxrGu5jgjwpAEJoiFLAA1iAKGSPeAAcZhmAAnGxXAoRoTFMVwzLMtIyEcJIvAsBIGgPhhWE4RwvAKCAD6UZhiGkHAsAwIgIArAQyQwuQlBoPcdBxBErAbKoTGagAtJqkhXMAyC8lIGJmLwmD4EQVroHo/CCCIYjsFIMiCIoKjqCppC6EkADuxBMMknA8EhqHoVR2GcAA8jCekGqgVBXJZNl2Q5Tm3oxZiqh4xn0KKpFcAsvDKVoSwQEgRnJCZZAUBAHVdSAwBSIENC0ECxAKRA0TpdEYRNAAnklvAzcwxBzZl0TaJgDiLaQRlPAQmUMLQC2RVg0ReMAUK0LQCncLwWAsIYwDiKdeDEFtjhSra6VCltMIbORYRAsJWG0Hg0TxatHhYOlBBWuJd2kF9xDikowbAk9YNGFRSxUAYwAKNieCYDFmXJIwO1%2BcIojiMFVNhWo6XRfoT0oPhlj6ODCmQEsqDJHUt3WaM6AQsGpiWNYZgycj3nfTznQfZkLgMO4nhtHoIRhAM5RDEkBQZAIEx%2BHraQGwwsyDPEIw1IrAg9OMau5NbXR22MfRa3Muu2G7Rt6NMzQWzrVtLAoRHrBIKUcGhpDSbwsmFVZtn2Y5zkVaquCECQDpkY1FE40sCCYEwWDxBAtH%2BOCGJseCgkaAEkiapJKGamx%2BicKJpDiWRGKalwmpMWxfGagxXHV5qMfpbJ8mKXnKmtZpbXaTl%2Bk9X1tVmWwnBNCwUrMtZTB8gYRi3mxGJ3lhHmZ95vmyAFtPSPTSiM5FuiBHFCWLZH0exxlHDZbpMIrj5QTsVeyyAj7ABPmfe8VVUA1TiNnMwudmqqUXmvOIBlepwM6rVFAECuCcQfCNMaE0pqRWWvNHaFDVrrU2ttRGe1GAHSOidLCZ0LpXRujtB6mMNhsLeorL6t0L6qD%2BkCHaQMajpTBhDea0M%2BFNXhjtZGqNMDo0ekYLGoA558HxoTYmpNyYYXIlTO%2BQUH6yAZhFLCr8WbY3FlYDmMjuZl2wvzTIgthaiwcZLaWcRZYuJDjbBwSsICuF9kkTWpRLZ6H1nUCJKRTZ1EDvMZ2tt6g%2B0dsbBWITXYzA9jEkYmScjZP9u7aJQcI7LFWOHBqbco5pUivHIqSdD5PSgefdOnks71WQfnUghdi5DFccJDuXdT512ZChNiAlwT1zskkH%2BU9bAzxQfPeAi8dK5Uweg4gG8NjbxKiwBQUpeRSgIRiUEtoCDuW6dfJIpiabmJCvIJ%2B1idAgHBKQd%2BiU7pf0aTJLKy88oFVUEck5ZyLlXNGLA%2BBdUzDgnBH0nRaDsFdR2Wi3BpzkjJCrAQis0KCAVjBQ/OgJDKBkKwtQk65FqW0I%2BjtRhghDrHXSuwy6YguGIx4ZohRpB8DvRCUIn6ojkD/QkYIKRkUZGQzmvI2GSjEYqLSGojGmiwjaJaropgBMiYkzJhTRGjzAoSAsaFN5TNPl2OMOzGwzj4C83cQIW6mxhZswlpYKWccZZ4CwIEnJdRlaqxKRrFWKSvZxMyAkyNxQCmVLSbkjJvQEl2HSfbcp2tUne2TVkv2btw3B2qcRKpwlv6T04IVcFpzpRQvjDCiAGcvLZwak1fpgyS6UEjmMhIp9EUoW4pILgklEXMn7hPJpnBp5KX6XRSQKEq78WZJJJikhOJcBYo6ep4IAVx0nbPFqkc3LjsBXJfd1EkZxHSM4SQQA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/is_equal.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/is_equal.test.hpp)
