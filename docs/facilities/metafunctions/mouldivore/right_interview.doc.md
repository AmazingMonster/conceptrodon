<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::RightInterview`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-right-interview">To Index</a></p>

## Description

`Mouldivore::RightInterview` accepts a list of predicates.
Its first layer accepts a list of elements and returns a function.
When invoked, the function first binds the elements to the end of every predicate;
then, it returns the index of the first argument that satisfies all newly formed predicates, or `-1` if it cannot find the argument.

<pre><code>   Preds...
-> Es...
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>n</sub>
-> (...&&Preds&lt;Arg<sub>0</sub>, Es...&gt;::value) ? 0 : (
   (...&&Preds&lt;Arg<sub>1</sub>, Es...&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;Arg<sub>n</sub>, Es...&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
RightInterview
 :: template<typename...> class...
 -> typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<template<typename...> class...>
struct RightInterview
{
    template<typename...>
    alias Mold
    {
        template<typename...>
        alias Mold = RESULT;

        template<typename...>
        static constexpr std::make_signed_t<size_t>
        Mold_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = RightInterview<std::is_same>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Mold<int, int*, int**, int**>::value == 2);
static_assert
(Metafunction<void>::Mold<int, int*, int**, int**>::value == -1);
```

## Implementation

`Mouldivore::RightInterview` is implemented based on `Typelivore::SensibleRightInterview`. It changes the invocation order of the latter.

```C++
template<template<typename...> class...Predicates>
struct RightInterview
{
    template<typename...Interviewers>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = SensibleRightInterview<Elements...>
        ::template ProtoRoad<Predicates...>
        ::template Mold<Interviewers...>;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAGz%2BpK4AMngMmAByPgBGmMQSAMyJpAAOqAqETgwe3r566ZmOAmER0SxxCVxmQXaYDtlCBEzEBLk%2BfoG2mPbFDE0tBKVRsfFJKQrNre35XLZTQ%2BEjFWPV/gCUtqhexMjsHOaJ4cjeWADUJoluXo60hACel9gmGgCCh8enmBdXyJPoWCoTxe7zeAHoAFRQiFnISMTIxegAJTwwAQBAAkoJ4gA3PCYADuZ2hELBIIImBYqQMFMubgI91SjFYmAAdOzgW9JsQvA5YfC8IjMCi0ZjscQ8YSQSYAOxWN5nRVnClUmmYOkq6lMWlXBlM5hsdmsp5nE5MBQKI3KYiYfCiCkKTmvJVnbm8ghna2oIhI1BMdAgl2y%2BXOl1KzVqjWM5mGjmJZ4KsOKt18r1EACyngDiaTwddzUcyFNAkmmFUqWIZyYN1QZxxYi832DAFouLKACKXCwXGWdxIhwNJ5WUrU6%2BnRg1s9mvYA2ymMAiO%2BODpNeTJGM6Z2joH7tz3Eb2oLcBq4zudsQSWuPPfsrnt9gc54eq7Xq3UjyO6icso0ms0Wq0bTtV8lwTUNFTXcJgDOX1/V3fdD1gk83GtW08HtTAr2NZdbzeDsu2lN4I1fKN9RZM4ADE8GISYnRTD04QYBFkVRdEsQpCV8QJOkqJoggnWDO9iLHYS33HMjY2w7BTQMAD2VQ4CHSdF16IQn0/WzcCexDIdn1HMS9RjKdWRFdEhDwLBQLvFSCB5VMDwzLNrKVPNFWcpNJm1dDiyYily0rasiDrBsmyfXTBLC3SXIAVisaL2wgdYzmbE1/hAEAWCYABrTAAH1MmACJ0Fy/irkyAAvPLSrAqKhwirTaqTPAqB80t/IuSLGqVKBfxqcx/AU9CQJ46jJlIGDWOECzMN/eN0vrbxMHWdZ3K67SzhtAgdgYM4NC7e9CIatbFR6JRVq6vNNu25K237A7OqijtEvOlzewIh78Nw0EjsVUTSKMo0z0wedL2UodII3Y94LTI8nNPWdgYvRdZpvHTXofQ6XT%2B98XxE79JL/WSsKBkHFzBiD12gpDoYc1AkLpEmkaw4Evs%2Bx9Xmx8SjMo0aCHGwzJ35NAGHQfn8eMgB5AgEHiKyuVs91%2BSYwUWNFdjcS4ka%2BPGuFhdFs4pZlmiUelOUhI/Eicf0/7JxRmTzSwwaMLlrTVJh%2Bmn3q3TOYFn92VMqbLPJsM3dp49VtcjqfpDgtvOFtqKyrGtgsWqOLrNh7wtikx4sS5LUoIdB0synL8tRIqSrpCqquD9O0eOl1mtavzE5e2qeo5Pqaid4arl4saJtFczLJR%2BaQuWtvHrlDbMC24gdr2u78LwzPGtO74m/jlvK0n3SO%2BNLuBqAoalKuXWBH1gPh5m68x8WifV9qy7Z%2Bu27u2X76G7Ddezk3ktt93kOCAgDaqMWYsKSa6tOJSiuIbWWJtH5rXSqJGCGk6Q9wdAg6OX9kEWwpJuOGbgr7TWZsuRBXU76NjOGAMAlw9ythAWGFa5C6rT0YbpK688zhmAuJYJW4CA5QMlNxWB0t4HXnYUOXBuNvj0yuBgm%2BUlJFJmkfpAh246TEJHhIlhtVKFvnfrosMH9lFnHXqY5%2Bc8doMKXm9IxT1mHYPRu9aObNMZDh9uLQGCNSYu10hDaCUM6FqVhho%2BG54FykNRneNxK8tI%2BzwQZLx157ZyVZIzSJwcAmoLgsE92aDwmI0iSbVmb1WbghJIPNi4phHEmhGSIiiSNRNK/BJYyhMHaATQs7OiCs%2BSCJqZrPCGd4ktK5rbdkQiuKy2DqHQ84dPYjO9mM32klsD0CZrXJU2SgmJD3GAlWEC1aDJgW4dZvisG6VUWqEJciULH2dpcqRIAUHhyuFMwk4ilFfSDGU9mWMVnJNZOczZZCtI7KzDTeZhCQXFIkaUjGcTIQkhRSihprxkVQjOAAFUwouOpUJ0WYtRai9F0ozBHAYCcLw5w6Q3DoA8ASjSZE2z9uk4gwAXY7NnkwKgXgqV9HggMjiwiq6F3SngBQ%2BUWROnSm8twrwOVRJcSCTyhZcoO3iPxN4EB0w8r5QK7IdJwgEChE8OVhCTXjRNRCa1ggoR2tNRCc1IAFpULocEswK0vpqvQhqi0WqQS6v1fyhoAg6Q4lQBZF18qrW/3tY6h18anUurdU2PZwTWzeosBwTYtBODRV4H4DgWhSCoE4G4aw1hXTbF2E2ClPBSAEE0LmzYWUQDRQAJyskkAADhlL26KZhO1mC4L2/wkgZSJCCPmjgkheAsAkBoDQpBi2lvLRwXgCgQArubSW3NpA4CwBgIgEA2wCCpBuOQSgaAqR0HiJEFknBVDjubBOs4wBkBFikKyMwvA0JEGIBZPQ/BBAiDEOwKQMhBCKBUOofdpBdBzAJMQJgqROA8DzQWotLay2cAljcS9HpUAtRff4N9kgP1frOD%2BnhEAPB3voDvBt6xeB7q0JsCASBb2pHvWQCgEAeN8ZAMAKQZg%2BB0A4tuiAMRcMxHCC0e4GHeDyeYMQe4EsYjaHqHuxtt6kYSwYLQJTCGsAxC8MANwYhaDbu4LwLAmUjDiFM9RHTeAcSYVw2WeoNx9iNpNT0XDdwYiofUx4LAuHbJ4EXXZ0gHniAxAyJgdslJDDADuEYFtmwqAGE5QANS4hLfUynoPCFEOIKDoH5BKDULhpD%2Bg0soCrZYfQgpt2QE2KgVIfRbPNn%2BHQ0wlhrBmHXfFoDll4CbDqGGvwEBXAzD8HMUISxyiVAKBkLIAgFvraKNkYYq3VjdF6I0BY225jTb6AMVo%2B3RhVHmIMM793rsrduxIKbta9hvf0Nh1duGN1nDIxRqj37JC/rOBAXAhASC8MSFwVjTasubBlv6MYiVSDtskIkVknbEgykkBoSQZhJD%2BGXdFfwnbvtzoXSAWHrJ/BcH8L2ztvaGfRUkFwLt07fsIY3VundCP92cZPVxs9hGr0CaE0xx9bBOAtBYDiGUzYmD2w3FwbtXBWSloAyQYDcwqvgYq9IKrsHasId0OJlDaHlNYY4IW7n678Ni%2BIy1OXCulcq%2Bgmr1kGuNDg4Y7xpjMOvVsay4e7jqBGPxGvYJiPAexiu8V2aIwauuArpoLQKTlBZMIdU4pkruf1Oae0w4Er%2BmFyGeM7hszFmrO0BsyVhzaXnOlvwDaBoHnbNa9UD5ikJWAuztLcF0L9xwv7FLVFmLjb4uJaUClxz6WoKh5y0wfLhXiuxf1%2BVyDRvZAm/g6W83DXMuDasC14L7W0ddZ65wPrhcBvNYsCN3gqAxskMm0dtzzg5si0e8tsor25hChNschPAOgdtgCbsVg7sLsTsHtQDZgP8ZsrtFh/8oC9BPJph4DFsnsUDlg1s4ctgdhPsCDZ07c11n9OAqxiB5dFdlck9Pd1dNdwdIdAMYc4cQ9BckdMAUcEg0dZ151SBF1Ehu0CcZQu0ZQp1Cdid2d7cKDN1bB%2Bd2MD0j1T1z0iNo9JcH0n0OA5d30WAFAcQiwcQvc1RJh/18BANddSsDdt9Ss986sadSBLd0M7MbcyC/tHcL0bgzgSMqCWA9CDCjCTCQIPR6NY8%2BMYdEh4clDONw9I9%2BMb1wimNXVkBUhUhcpjDO1cpTCCANVqCJ0JMM9ZYs85MFN1N88yiNMtMdNS8I8DMjMTMW9MBzNLNrNbNG1G8nMx97NXN29PMENvNkBfM%2B9sQB9eAh9FNR9IsgNJ9eBp8ks58m9F9Bc%2BBcsFACtCQitGAStN8IMJAd8YMat98dBHCDBj8H9WsYgL9OtutshbMwQ0oT9htRt4hxtPMOtEC%2BgXAf8sC9A/88DDsgC%2BhHsgS9sXs0DzsehP9%2BhTtfjITjsBBkDID8CcDHsMDcCDsqh3siDIM3CcMedKDdDKN9DDC6xgiHRQiWDodDh2CBcOMuCeDKAbcBDF1h1WRkhopooCdU8NBkgZRGdZC8N5Dt1d1Ed0cQB8dWRopqgpAZQNAB0uBEgh0CjZ1Eh8SHd5CYibc/1BTec6TW04tZZsgJSgA%3D%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/right_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/right_interview.test.hpp)
