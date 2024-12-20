<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Contains`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-contains">To Index</a></p>

## Description

`Typelivore::Contains` accepts a list of elements and returns a predicate.
When invoked by an argument, the predicate returns true if the argument is in the previously provided list and returns false if otherwise.

<pre><code>   Elements...
-> Argument
-> Argument &in; Elements... ?
   true : false</code></pre>

## Type Signature

```Haskell
Contains ::   typename...
           -> typename...
           -> auto
```

## Structure

```C++
template<typename...>
struct Contains
{
    template<typename>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Examples

We will check whether `int*` or `void`  is inside `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = Contains<int, int*, int**, int**>
::Mold<Args...>;

static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);
```

## Implementation

`Typelivore::Contains` uses `std::is_same_v` to compare elements and a fold expression to combine results.

Here's the entire implementation:

```C++
template<typename...Elements>
struct Contains
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {(...||(std::is_same_v<Elements, Inspecting>))};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxBIArKQADqgKhE4MHt6%2BASlpGQKh4VEssfFcSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7Bzm/mHI3lgA1Cb%2BbgQAnsmYAPoExEyECofYJhoAgk/PBJgsyQYfh8dnjFYmAAdKDsPQ2IJ7v5Hi8FNcvA49h5BLcGPcXiYAOxWF57fF7D5fH6YP6nc7MNh7ACS6POtSMDzeBL28OIiIIe2UxFQRAAsp50MyCdiLCK8SyCfCmI5kHs0OiPqpksQ9tFUJ49gA3MReTAHCWSg44iCg4HYtwWiDw9AgEB4BQXBRAi5av7gz6MAgKUg0uk1RyMmHzebYgAih1xzxZ4cjb2F%2BKJ3xlpKO5MBbDNz2AxEwnqhTMNey86SMewFtHQB38Ya5PP5gr%2B2dz%2Be9ZqZ/ijsc78ZeAHoAFRD4cjvtvQdDgAq2CEk%2BHY/7I6XA4Xr0xZi2DB2Xn2fwVa2S3sLa/en2TvzTAMpINBz2IwGhsOeJbCwHLmAaVC8W8cAmrtZRBowmhNwwgIX0wIHCDBCHaCCCHY87QrIUjjvB92xhONMThBpZQuJgFCUJoID5D8mC/H9Mj%2BSCHjtHVvEwUMexwmU8GQfDCLiAgIDAMB30/b9OgYP4tVQPAUOwOjdUYyMOEWWhOASXg/A4LRSFQThLUsaxWWWVZ9U2HhSAITQ5MWABrEAEkkYENEkLgsX8DQEg0MwADY3LMAAOLz9E4SReBYCQNA0UgVLUjSOF4BQQFCkzVLk0g4FgGBEBAZYCGSLxwIoCA0C%2BOg4giIFOFULy3IAWjcyQ9mAZA5SkYEzF4TB8CIYhxL0fhBBEMR2CkGRBEUFR1AS0hdC4UgAHcbmSTgeHkxTlNM9TOAAeWyrLOVQKg9jKyrqtq%2Bq9kasw9ggDwCvoVVDPmXh4q0RYICQfLkkKshcte96QGAKQzD4OgPmIGKIGiFbojCRoTnm3gIeYYgTjW6JtADGHSHyyECDWhhaGhsasGiLxgDcMRaBi7heCwFhDGAcR8bwXNai1TBybUzBVBqbL1iMsDMAUsbaDwaIbgRjwsBW648CCinSGZ4h1SUMNPhpwWjFMxYqAMB8ADU8EwKa1opNHuuEURxAGk3hrUFaJv0GmUGsax9CFmLIEWVBD0ycmKptQ4w1MbTLDMCK5Y6rBXYgRYOl/PwIFcMY/EmkJplKco9FSdIY4T9OChjvpU7mWw%2BYDOpJmzybo9Lnp84GCphh6cv66aGvZgqKO9LWCRFo4JSwpWyK9vKqqarqhqbLOiBcEIEgDg3Lg7uM9XFgQTAmCweJI9ISzJH8YEAE5/CxSQ7LMSQ3JChI3L3vyOAC0ggv8LhgTcrg3K8vevNf6zKgPty%2B7GyK0VYqLwSk9VKz10qbWyuQSgX1rrFTYJwRoLAtRYgqkweUBgyxcD3sCJ%2BbM2okE6pNE2vVzbSEtkoa2Y1dD/RmkwOaFNu693CrwSKG1MrZT2DtPYyDUHoMwTTE6uD8HnUum9a6s9/BmAXg9RKEC4FxBgXlVAV1Bh8LQTsGmOCuChRoLQIGIMwZjThlDNGpiEZIxRg4NGGMvTY1xitAmRMSa0DJmjKmKt1hqXwIzRwzNWYtQ5sgLmaNeb8zUoLYWUMxbePuh1aWRk5YK0wEramRhVagFAXwLWChdb60NowY2sgyH9QobIK2o01K0LtmrAOVhLDO2iBHd2nsBDe19jWep1hg5sNDuJFm8Ao7FyEi4Bg7hPCtD0MnEotcc6Z0yI3DOhQGAtzThXEZMduijEmbkDZ9gtmTDWYXaUOyciJyblMWZrcu5LBWJ3eeN8WH904Lw4gKC0EYK0dgkRtlzpT3alI%2Be90l6kBXmvQYm9%2BZ3wfrguyWIEh7yxI5SQp9qqTVYatKKthgFyLAfACBGUtrKMUcQBB6xkGHRYAoLUcotQ4OBCSeELVCFhy6iUs2ZTBryCoVUnQeR6GMIWk85aAD1pQO2rtSlNVqW0u1AyplnILqqIkXEKR/hZHqySi9FV70SW6uuiAWlyRkiuhwRcRV%2BF3nVQBgYuIRjwaQwRuYp1iNkaoxlnYwQDi8Y%2BMwITYmpNyZGU8RkuJpBfElwCStdmnMPhhMEHzFaUSRYnFiRLBJaNklpFScrDJr4tWayYDrPWBsjYy1IZyiQ5Shq8ptnkLBxhHaNKiS09SbT0ScD7DaB2gcLC9PUv08OQyi4HMyGMiZ5zpnjOOXXZZWddkXPnZkWdehK5dDLoutdmyq7NxTnMium6p2Hurvum5jyFAd36sw0VEVXnSr2LKulCqUzwn%2BayoFmrQHL1XuvSg3cYUgDMLg/w/gEguXsiFUDWI37/zvdimKcVQXbwSPvBIXl3J70kEi6DXBAj838LethnAQXfpvs1ODxHsV4sWHLdIzhJBAA%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/contains.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/contains.test.hpp)
