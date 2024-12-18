<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllClarify`

<p style='text-align: right;'><a href="../../../index.md#concepts-varybivore-conceptualization">To Index</a></p>

## Description

`Varybivore::AllClarify` accepts a callable predicate and a list of variables.
It returns true if the predicate evaluates to `true` for every variable and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...&&Predicate(Variables))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AllClarify = REQUIREMENT;
```

## Examples

`AllClarify` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&Pred_0(*))` and `(...&&Pred_0(*)) && (...&&Pred_1(*))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return true;};

constexpr auto Pred_1 = [](auto...){return true;};

template<auto...Args>
requires (...&&Pred_0(Args))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...&&Pred_0(Args)) && (...&&Pred_1(Args))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHGgMs5iqKcQA1ExeRCfKxJjoAPoaJyaJACJPAVYBLxDnRAB0AJWJgA7BYbgRNgwTgRiF5MM8rMCXgiTBoAIKotF7A5HU6/VBXG73LhPV7vT7ffEAv5A0HgyHQ2HwxKI5EszGYgiYFgpAxc55uKkAtHEYAKZ7YTE3ACOXjwNwUJwg1PMADY1ddbg8ICKxSsgejsVzcScYqhPCcqF4GBBaWDMBDiFCqGIlCikRz0VyeXzmYKLqhqbrxYlJeiZXKFUqVWZ1bHNfcNDrRQp9U9Y2rowC1RqiXcuMm9QasQIccdTebaJbrbaQfbHVCYXD3cj0ZjZkxHMg7kwFEoWtRrQKuBLbUCWRw1rROAFeH4OFpSKhOG5rNYTgoNltMOnEjxSARNJO1gBrEABVV/AAcqqkAWBqskAE5Eg%2BzMlpxxJLwWBINBpSHnRdlw4XgFBAADDwXSdSDgWAYEQEANgIFILnISg0B5Oh4kiVgdlUG8AFpHxOYBkGQE4pD%2BMxeFuQgSDwdA9H4QQRDEdgpBkQRFBUdRoNIXQuFIAB3YgmBSTgeCnGc5yPJdOAAeQuVCCBOVAqBOAjVWIyRSPIyjJGopUPCw%2BhTnMPcVl4KCtDWCAkEwlJsLICgIEc5yQGAKQzD4OguWIcCIBiOSYnCZoAE9JN4ULmGIcKFJibQ6ig/dMLYQQFIYWhIv4rAYi8YBBVoWhwO4XgsBYQxgHEXL5WSvAADdMFKxdDjqC4dn3cIuU/RdaDwGIxLijwsDkmE8F/MrSCa4gzSUF5uSq/qjCPNYqAMMUADU8EwYSFJSRgoq44RRHETiWPkJQ1DkwT9CqlA10sfQBvAyA1lQFJelKwjZnQZ4XlMSxrDMYCZuIRjmvgNZanqZwIFcKY/CE0IFnKSo9EKTIBERjH0ixhghjR5Yuh6Bo5hxoSYd6foWkJkYqnGAYKcZ2nUfpiRoa3bYOf0GTALkkDNKIkiyIoqizCVXB6PM98uCsg9VrWBBMCYLAEltUgz0kRI/hfYFJA0SQzEkVV/wvJ9ea/H8QD3P5b1VK8nyvLhVQCSQuACF9VX5/iQLAiCFeguyEPspDlLQ1z3LM3C2E4ZoWAa4FCKYE5kAMIxKKfP4uD%2BVr8CIcGmKEi62LO6QLp467%2BN0HzRPEqLpI4WcfeAxTw9U9SzmIBOk5TtOqsz7Pc%2BM1BTPiXczHlmyYNDqP4nQtzR6csyQHjxPCP7owuCfLgAJoWh/MC4L%2BJiiKjtPuKEqShwjrSxgCEy7K5LygqipKo6KqWnZF3wG56ialqtFVDtS5Edbq3Q5L9UGhFEa39rLg0mvuGac1MALUqkYZaoAg58A2gobau19qHSmiXU6HFy6yErnxRcNc7orUBlYJ6UDXoaw%2Bl9TgP0CB/VePQ4GoN4iF0hm9Em9U4YI08O0PQKMyjsyEpjXozM5FZDpksBmVMyZM3EXkSm3QRF9DmMo9GlNyaaKRizeY0iVE803JsbmctLbNyArwQWa9e6p3TsAQeOdHgQClgXXcctrKK1IMrVWowNafm/KQX8iQs6G2BJ7YEwJEhGxNu7FuTjOD%2B0gqtWCIckDIRUgvOexAY47HjiRFgCgGoUQatvP4vpZi0XzgxIux1S5kOOpQm6NsRJiQkmVRuDiBZtxQhcNSGlym6UqdUk4tSs4NNUhAEyy9x4WUSFPHJs8l7OSKdsle1SUgpDuHMu4Cyezd0fL5A%2B8Qj4hTCnFc%2B9z4qJWSrfUe6UH5ZRyj/TA%2BVCpiHflNT%2BGC4GkF/vVABck2rIA6mAwQED%2BJQKGuFWBY0EFHWQekVBi0MHhCwbZHBTAto7T2gdec%2B4SHsQkOQ7iV0qE6B6e4h6QNGEvShkuT6WRSoAHpfrMoYRYEGTiwYQ2YdDHRsM/DwwYO4ExkiZUGOJoo7GcrZF416Iq1RErqbGNyKYtRAgabmMWIYsxzMOyswsYYzmNiOKDNkr7TgXcWAVKqTUupCzJbNJlpZQJQclYqzVpQRukTfxmCzokRIAQAiG13hoSND4rzpPkqBWwAdp76k1iAbW2dEhXjdu%2BGNqp3wPktokB1rdU0ZsbjRZNftA62TWDNDIzhJBAA%3D%3D)

By turning `(...&&Pred_0(*))` and `(...&&Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AllClarify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AllClarify<Pred_0, Args...> && AllClarify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AllClarify = (...&&Predicate(Variables));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQgZqQADqgKhE4MHt6%2BAUGp6Y4CYRHRLHEJSXaYDplCBEzEBNk%2BfoG2mPZFDPWNBCVRsfGJtg1NLbntCmP94YPlw2YAlLaoXsTI7BwEmCzJBjsmAMxuTF5EANTKxJj4ojukF2dEAHRvAGqNeEwx9ArH2BMGgAgmgGJtkgQLsDaLQ3AZiHgqABPC7HAAiFwgbxe5gAbPjrrc8PdMBBPoifn8lktjlYQUDgQB6ABUbPZHM5TMZrPZFwAKphpgoLhzuSDeZypWzxcDGWDpphVMliE9zqgrjd0AB9DRoo6Ykz%2BKz%2BdEQZ6oHG0gDsFhuBHWDAuBGIXkwdJM1vRHoZIIVO2Vqotmtu2q4%2BsNxqNZotVs9dswDuITpdbo9Xp9cpBOz2B3dJ1jb2BxGA/yOgJBNwAjl48DcRTC4Qikcjjm4iTqgtCSwocQD5QJFYGLjFUJ4LlQvAwIDaE0mnVQxEp097fcCc/smIcC%2BqccXS/3K5ga3WhdDYfCvii2x3dY99723gC0WYCa/z02r62TreuPee325YDgwQ4qiOY60BOU4zvG9qOs6rr5lYGZrtMW4ktqTAKEoTTUFObZcACM60kcFgcCstCcP4vB%2BBwWikKgnBuNY1gXAoawbJgL5HDwpAEJo5ErAA1gEkgvBokhcNaRwaIEr54mYAAcin6Jwki8CwEgaEEtH0YxHC8AoIBBPxdHkaQcCwDAiAgGsBDJOc5CUGgex0PEkSsFsqiKXiAC0eKSBcwDIMgFxSC8Zi8MSRCIugej8IIIhiOwUgyIIigqOoZmkLof4AO7EEwyScDwFFUTRAkMZwADy5wOVCqBUBc3l%2BQFQUhWFYlmFiHiufQqrmDxSy8KZWgrBASAuckblkBQEBTTNIDAFISQ0LQOzEEZEAxJVMThI0yIlbwe3MMQyLVTE2g1KZvEuWwgjVQwtCHdlWAxF4wCnLCRncLwWAsIYwDiK9p61AAbkKlVKjU5xbLx4Q7JR2W0HgMSFWdHhYJVLp4Jpv2kBDxCjko6K7IDKNGAJKxUAYpbvHgmB5dVySMEdaXCKI4ipQl8hKGolW5fogMoCxlj6KjRmQCsqCQpkP2%2BdM6AYqYljWGYemE7FkNSx0XSZC4DDuJ4rR6KEcxlBUegFBkAgTH4f7W90AwW8Mf7VLUAi9OMxu5G7nTXXUMzO0MCRuzMdt6GhTTBwsocrOx6ybBIZUcNRpC6bw%2BnNT5/mBcFoXhd1EC4IQJDcVww18VTKwIJgTBYAkM6kCJkhHC8ACcRzWpIElmJIeLaf4eLt6pHDqaQmk8S8eJcHiint4ps/%2BJJ/id3i6eVfphnGVXZnjdZE22XVjlzQt/UeWwnCNCwYPWr5TAXMgBhGGF7cvFw4lRfgMV4HFf480lLm0geYZX5tlXQSQCpFSOinNOGcqocFqvZc4FxGpPGIDfO%2BD8n6A1fu/cSPVUB9XiNxZYI0qYWUmkQ6a/UnLzWoYta%2Bt9fI4KMFwduXAghrQ2ltHa2UToHTZgIs6F0roODZndRgBBHrPUqm9D6X1aA/V4v9cmWx6L4BuODSG2VobIFhmzBGnRKoozRgdTG6iRqIjxrxQmxNMCkwBkYCmoA958FpgoemjNmas3xgAzmKVgGyFAVleiEChaUxVlYMWpjJZNxlt0eWitlaiwsOrTOmtf7aybu7boBsjY5HtsEQ2MdLYOzSDbLIPsimO0yKU12usA6e3DtUyO/sPY9CDubEOkcWmFN6X0epcdViJxSrAiq2Us5MKwY/Z%2BwA8Efz1MXb%2BZdBoV3IXvGudcG6UBTuPSeb8JLWlXtaaSkg%2B4BT/PAretgd6jXMpZGydl6p0LPu5TyV8MFtRYAoMGoUwbsJeHmaYX9S6xXirIQBgT2YhIFiAI4pAoHFV%2BuMjekyarHwak1a%2B3zfn/MBcCqEEBeo0JIYNI4ld7njSocQ2azkGH9RAH85IyRtQAvbtqQlmEvnALoDwygfD6LCJerxYVojroSKIfdaRT0XoaMwO9T6YglFs1Uc4yxpBNEBwhj9eieiDH4yMUjeipj0bIgsdjaxbM7FpAcWTZx4RXFjXcUwOmDMmYs1orxfxyUJBBPSnzUJOh4UROMKk8WMQ4nS1loOTgTJFYi1VpYdJDFMlYCjY0jp%2BSI5/jNqUHp5TCiZBzSkCpTtumxzaXrZpfQS25MDoMitZTRi1taWHRt%2BbK0VxGZxZOo84Gb04OglguK/kXHZUCrcQoiUlxiuXSl1dSC13rsMJuSN9mJDfkcI4/hAiSW0tu60c80V6U4NvEyi6W7%2BA7v4RSr526SHbtJLuXAEVIyOBM09Bld5jRTpFE9mcz0/sEgTeI6RnCSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/all_clarify.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/all_clarify.test.hpp)
