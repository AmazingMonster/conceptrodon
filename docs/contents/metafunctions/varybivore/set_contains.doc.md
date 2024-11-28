<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SetContains`

## Description

`Varybivore::SetContains` accepts a set of nonrepetitive variables and returns a predicate.
When invoked by an argument, the function returns true if the argument is in the previously provided set and returns false if otherwise.

<pre><code>   Variables...
-> Argument
-> Argument &in; Variables... ?
   true : false</code></pre>

## Type Signature

```Haskell
SetContains ::   auto...
              -> auto...
              -> auto
```

## Structure

```C++
template<auto...>
struct SetContains
{
    template<auto>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };

    template<auto>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

We will check whether `1` or `-1`  is inside `0, 1, 2`.

```C++
template<auto...Args>
using Metafunction = SetContains<0, 1, 2>
::Page<Args...>;

static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
```

## Implementation

We will implement `SetContains` using the method presented in `boost::mp_set_contains`.

We will create a class that inherits every 'variable' we want to check against.
Then, when provided with an argument, we inspect whether it is a base of our class using `std::is_base_of`, subsequently determining whether the argument is one of the variables our class inherited early on.

To 'inherit' variables, we need a helper class that transforms variables into types.

```C++
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };
```

Since inheriting the same type multiple times is illegal in C++, the initial list of arguments for `SetContains` must be nonrepetitive (hence the word `Set` in the name).

```C++
template<auto...Variables>
struct SetContains
: public Monotony<Variables>...
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {
            std::is_base_of
            <
                Monotony<Inspecting>,
                SetContains
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISWakrgAyeAyYAHI%2BAEaYxCAAzACcpAAOqAqETgwe3r7%2BgemZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfgG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmCWHI3lgA1CYJbl6OtIQAnifYJhoAgvcPBJgsqQavJ25M56iHADUWngmNF6LdnuNiF4HIcALICVBEBg3R4mADsFkOs0cyEOaAY40wqlSxEOvyIhwAbmIvJhjpigcQQWDMBiACInLEcrnPZ6vd6fNmnCmoAB0EqZLPoCghjyhMIIhyEmDasiYYVljxAh1SXjBeDxCIYSIEN1OUtBMtuErFfMxz0OTsOAo%2BTC%2BIr%2BhwAkoTUpgHGFgHKHs7sQRobDlMRTcomMA2Y8wxisU7HWHnTjDfiBESSWToqhPNTafT0xmGVYkxWM%2BN0CAQHgFAB9aJMJTN1BUcs1tOnHu9sPG00o76%2BhT%2BwNGW6kAeDp0qtWCDWEucV24NmneROhms8hJV3dp9Gcg986tO11C76i20PYDETBvRgEWUJO4Xw5eTJGQ5xhPHAk7J/jGRD/sKbj3o%2Bz6CAotoQmeaInryaKPAA9AAVFh2E4WhzyYVhAAq2BCIR2F4ehOFURhFFPGiZi7Aw%2BxeEc3znHQ1whvybxuh6Px/HexDAG%2BH4PN%2BQbwqqTBUF4TENIBwGLh4y6at8GikIcXAaWYIYNuB3wPEJcESghh6Qs0uLNu2SitBAcJSTJcnZN8XAbiAW50ksKEPFmyBWQoNkEBAYBgJJzSOYGAjfAAtK576bqWXkHhwKy0JwACsvB%2BBwWikKgnBuNY1jYmsGxlgxPCkAQmgpSsADWIDpeiYoJAAHAAbOiCSdRobVdUkCT6Jwki8CwEgaOp2W5flHC8AoIDqdVOUpaQcCwDAiAgGsBB6gQ5CUGg7x0HEESsFsqgddF7WSIcwDIHiUhimYvCYPgRDMvWWn8IIIhiOwUgyIIigqOoy2kLoWkAO7EEwqScDwqUZVlNV5ZwADy5y7YcXaHBd7VXTdd0PZIT2HBAHhHfQZI7FwSy8EtWgrBASCHakx1kBQECs%2BzIDAFIgQ0LQrzEPNEDRCj0RhC0Vzw7wkvMMQVxo9E2gBktlWHWwghowwtAy2DWDRF4wA/LQtDzdwvBYCwhjAOIBt4I%2BgZUpgFu5cSAbnFslVhK8aVg5c0Qw4rHhYCjEZ4GNlukC7xCFko7JvLblxGDVKxUAYwkAngmCQ2j/rZZV33CKI4gA8XwNqCjEP6LbKBFZY%2Bh4NE82QCsqCpA0FvRXWJzsqYljWGY02xx9rvwCsdhq9kLgMO4ngdHoIRhEMlQjFpRRZAIUx%2BBvGRbww8zDPEWlT5FjQTGqeS79008CH0rRH2vJ%2B2JfO96LMj8rws6%2BT6VmwSERhwTKpApq8BmrjS611br3U0iTMwZNcCEBIMcCqdMqppxWAgTATAsDxAgPVfwCQxQDXRJIDQARJDtQmuldqKR/YjVIGNBIXAxTtS4O1VqSRWocPSpILg6UBrtVASjGac0FoYOWkzDazMtqY3OPtLmqBKYnTOpwFoLAqTomikwfEBhfxcCSGKVh7s3okDwJ9QGJc/oSGkBXJQVcwa6ECNDWGssgEgLAajDgGMdrnGxlQckxBNHaN0fsW2mkjEmLJhTNmVNUEJDMOghmK1ZHcypoo9JIwNFaOiuEowhiuDqUFsLUW4swby2lrLUglTFbK1Vg4apmsXw6z1ijQ2xtTbm2qdbZOWxcr4Cdo4F2bsXqqE9q8apvs6go0DsHK4od%2Bn02ZFHSqsd46YETjbIwKdQBSL4JnBQ2dc750YNU4uv0y52NkJXUGuVnG11TgPKwjdA6twIXlTu2Ru69yAs8oeI84hj3eZPOod8/AQFcO/LSy9yjHz0JvBo0K0j7waE/RYp8wXnwflfRemKej30vui9er9%2BjIs/gMb%2B8LaarHWAAml/tPGiM4EEkJOi9ERMMcYsUGhEFmOpmg%2BmmDSDYNwSMD5DDRqjB5ZIdEgj0RdUoddLSXixG2AkSk6R8BZHbV2pk5RcTVFsHUcE6BLAFBUjxFSLlQpxgvX5RYvQFzS7/WuUDBxdydCJFIK4uGlsPHIzBjNXxWMcYaLNRaq1Nr3SuyVOTA17MEkJGSWnVaLME0ZM5lk%2BIlrUipGbNapIzZbUECsqauxdBSmUHKblWp%2BtKp1vqWrJpyitYEFafrAZmAjYmzEN06OvSdlLNIIM6eIyUYe2QF7KZggZkB2bvMxZ4cVnVPWRkTZScdlBlTRneMRyc55wLuc2QlzXVWNudXb1%2BjjANxsG8ienyu6cDQnWeug9LDD3AaPCx482633PrPee18l5z2JS/RF2RkUQdKFS5%2BH8sUNBxeShDvQiWwYxaSyYC98inzQ3CuDNKFD/3%2BgGkRQaWXhpuuay11Jo2vHGHy5BAqWEpqkVgnBeDKBAMYWNMwRiEgJHSulChRTeoJHRJwsj01ODiMWsKhqAQ2FcESe1RJSR2FmGoeiIaHAEiBuk7NSRjMgHPSk%2BAmTRnaoxziJkZwkggA)

## Links

- [source code](../../../../conceptrodon/varybivore/set_contains.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/set_contains.test.hpp)
