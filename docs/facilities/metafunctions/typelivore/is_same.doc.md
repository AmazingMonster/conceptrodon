<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsSame`

<p style='text-align: right;'><a href="../../../index.md#entity-examinations-3">To Index</a></p>

## Description

`Typelivore::IsSame` accepts a target and a list of elements.
It returns true if the target is the same as every element;
otherwise, it returns false.

<pre><code>   Target, E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> (Target same as E<sub>0</sub>) && (Target same as E<sub>1</sub>) && ... && (Target same as E<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsSame :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<typename...>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(IsSame<int, int, int, int>::value);
static_assert(! IsSame<int, double, int>::value);
```

## Implementation

We will implement `IsSame` using `std::is_same_v`.

Here's the entire implementation:

```C++
template<typename Target, typename...Elements>
struct IsSame
{ static constexpr bool value
{(...&&std::is_same_v<Elements, Target>)}; };

template<typename Target, typename...Elements>
constexpr bool IsSame_v 
{(...&&std::is_same_v<Elements, Target>)};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQSAOykAA6oCoRODB7evgFBaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHOYAzOHI3lgA1CZ7bgQAnimYAPoExEyECufYJhoAgh%2BfBJgsKQMf3OlxujFYmBOABVmsBMARSCdrrdmGwAHQY7D0NiCV57d5fWbELwOE4ASQUQghPxMiQsJ1mTEcyBOaAYs0wqhSxBOMVQnhOADcxF5MDS6RAMWjzAA2WWzdAgEB4BR3BQQu6CkFY/6MAgKREw4hwghvFa0gAi53plutNK%2BfwBQLFF2R4LY0Nh8MRbtRmClOpx%2BrePzZHK5PL5AopVLYmrOX1pFklGNl8oIiuVqvVca1F0DeoNnuN8LNtr2VkTXwA9AAqesNxtN6s/OsN6GYWYKE6Nls1psD3v2z6M5l3JgKJQtCAx6kXcIIk4LxHLpeCN5K4XeTDmis/Ud4ZDjyfxAgQMBgcmUuduVfoDYxegr9f4zcinfWjhrWicfy8PwcFopCoJwbjWNYDIbFskL7DwpAEJoX5rAA1gEZhookZiSAAHNhgQAJz%2BGYGgythez6Jwki8CwEgaEEAFASBHC8AoIBBAhgFfqQcCwDAiAgBsBApF4CIUBAaAAnQ8SRBCnCqNhMoALQypIJzAMgLJSGiZi8Jg%2BBEMQeCKlwMiCCIYjsFIpnyEoaiIaQugmQA7k8KScDw36/v%2B9lMQA8iJwkECcqBUCc8lKSpakaScWlmCcEAeJJ9A8rBKy8BxWhrBASASSkUlkGJuX5SAwBSGYfB0H8xCsRAMT2TE4TNFc7m8A1zDEFcvkxNodQcXBElBr5DC0M1nGkFgMReMAbhiLQrHcLwWAsIYwDiGN%2BDEL1eCCp29mcnUIk7HBC7dPZtB4DETwdR4WD2Y8eA0QtpA7cQfJKBa/wredRiIWsVAGMACgAGp4JgTm%2BSiLXWeZ4hWfwgiKCo6hjY5%2BgrSg4GWPoF2sZAayoCkvTzYpCrnBapiWNYxG8KgL2GVguMQGstT1M4ECuFMfgmaECzlJUeiFJkAicwL6RCwwQx88sXQ9A0cwiyZLO9P0LSSyMVTjAMCua6rvPqxIzNQdsBsURwf6kAxNOcGFCnKap6maZI2nxbghAkGcZh7FwaXwb9awIJgTBYAkTOkKhkh7Gi%2BF7IkkgaJIWEynR/gyvhptUaQNFe2iMpcKR%2BHYXn/iSFw/jRzKFs%2BZwLFsb7nFZXx2UCQFInkJQRXJTJbCcM0LCCokilMKyBhGDF%2BFolwaJAXpbv03o8PCKIsPSAviN2SjIDlS5TBuQtnlm95Y1%2BS3QUhScvf94Pw8rWPE9T/FiV5clHt7GYPsZVxTcd/EbfiagSWjAvgPI4K0uD4S4EEGgtAqo1TqmNNqTUoYII6l1HqDgoYDT1ENEa9kJpTRmrQOaUMlpfR2EBDaW0drzWnqoA6fwoYnR/GNc6l0mo3TIelQyj04IvTepgD6y0jDfVAPXPgANgag3BpDJ6C8YaWRXrINeyMgK6HKiPYwmMbAsMZvjQmWRiakz2OTTR1NgJ0yMrtPGMstpsw5p4doegeZlH1iZQWvRtZuKyGrJYGslZyy1vYvIitug2L6HMbx/NFby0CVzHW8xnE%2BJNgoI2ll97m0tsBa2QCr4gNHmAu%2BGgXb6XdqldKftSAByDqMUOTCM5Z3HvHRIZdEiJD2AnSQKkTIZKYjXdiv1uKNyQIJQKv9v7EC7jsXukUWAKEFCyQU%2BTnSzF0sUueJlZFL3kdZJR9ldDkW3rvDypt0lVw4P5ISIlgqhSmapGZcyhSLKZJ2IKCV/5P3iC/PY79%2BlfzeflUZfzkogDmSkFImowF3CWQQccxAWAqQqtA%2BIsD6qNQ6kg1FnVuq9Qwf/Qaw1RrkMwJNaas15pwRIUIjh408CbXqFQvatDkCHQYYIU6zCLpXSuOwu6XCoa8PSPwz6QjwgiMymIpggMQZgwhowKGGyLISAUQjWyyidAgHIuojGlMsbaPgLoomnBqwKi1VYSwpjabxHppY0OfjbEMHcDExx9qInS08cLR1rixa9Bdb4kJrMwkBNyLE21AbdYJMiXE7WjIw2LEiYbTYxtvbHMPoxLJsLpmzPmY8v4swimzxft7Mp9d/aB2DpQfedTN7jz2HsfwgQS50RrYkUilcj7V1sLXD%2BKwUIgEkIkbSTSuBSHwo06O1RTZ7BTVbZiddMr7x0q21NM6u1rBehkZwkggA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_same.hpp)

- [unit test](../../../../tests/unit/metafunctions/typelivore/is_same.test.hpp)
