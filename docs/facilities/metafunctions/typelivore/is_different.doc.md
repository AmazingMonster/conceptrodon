<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::IsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-is-different">To Index</a></p>

## Description

`Typelivore::IsDifferent` accepts a target and a list of elements.
It returns true if the target is different from every element;
otherwise, it returns false.

<pre><code>   Target, E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> (Target different from E<sub>0</sub>) && (Target different from E<sub>1</sub>) && ... && (Target different from E<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsDifferent :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct IsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<typename...>
constexpr bool IsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(IsDifferent<int, int*, int**, int**>::value);
static_assert(! IsDifferent<int, int, int*>::value);
```

## Implementation

We will implement `IsDifferent` using `std::is_same_v`.

Here's the entire implementation:

```C++
template<typename Target, typename...Elements>
struct IsDifferent
{ static constexpr bool value
{(...&&(not std::is_same_v<Elements, Target>))}; };

template<typename Target, typename...Elements>
constexpr bool IsDifferent_v 
{(...&&(not std::is_same_v<Elements, Target>))};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwDMpK4AMngMmAByPgBGmMR6AA6oCoRODB7evv5ByamOAmER0SxxCVy2mPYFDEIETMQEmT5%2BgZXV6XUNBEVRsfF6CvWNzdltQ929JWUSAJS2qF7EyOwc5gHhyN5YANQmAW4EAJ6JmAD6BMRMhAr72CYaAIIPjwSYLIkGb/uHJ4ysmB2ABUGsBMARSDtjqdmGwAHQI7D0NiCW4Be5PIbELwOHYASQUABE8FQqPFGAQXiYAOwWHYTRzIHZoBhDTCqRLEHYxVCeHYANzEXkwVNpEARcPMADZpRAGKgCPSCOgQCA8AozgoAWd%2BT8ke8KQpISDiGDKejZrMaYT9nTrbaqU83h8viKDtD/mxgaDwZCPbDMBL9SiCGiMY8WWyOVyeXyCcTSeTBDq9k8aRZxQjpbL5Yqhiq1RqtWwdXrkYbjT7zdhLfaAlY008APQAKjb7Y7nabL1b7eBmCGCh2He7zc745HjseDLwyDOTAUSkaEHjJLJxApP3CEJ225bkL3%2B93gjbd1Vgu8mCt9ZeM7nC6XBAgYDA%2BKJa6T5rc24Pgl/BBbM8QAvYVrwsDh5loTgAFZeD8DgtFIVBODcaxrHpRZlkBdYeFIAhNAg%2BYAGsQGgsw4WpMxJAADmo6CNAATjIjQpWooIoI4SReBYCQNA0Uh4MQ5COF4BQQH4/CEIg0g4FgGBEBARYCESLwIQoCA0A%2BOh4kiAFOFUaipQAWilSQdmAZAmSkOEzF4TB8CIYg8BVCp%2BEEEQxHYKQZEERQVHUKTSF0CoAHcrkSTgeEgmC4IIpDOAAeVUlTFVQKgdgM4zTPMyydmsswdggDwtPoLkcNmXhJK0eYICQTTEm0sh1PqxqQGAKQzD4Og3mIMSIBiOKYnCBojki3ghuYYgjgSmJtEwBwxtITSQwShhaFGwKsBiLxgDcMRaDE7heCwFhDGAcRNrwDcHDwfkBzi9l5tU1ZcO3Ko4toPAYiuKaPCwOLLjwHijtIO7iB5JRCXeM7PqMAj5ioAxgAUAA1PBMBChKYUWtzhFEcRvNxvy1Di4L9DOlA0MsfQvrEyB5lQRIakOoz832QlTEsawzCEsGnKwOmIHmOx5pqFwGHcTwWj0UJwj6UoBgqPI0gEUY/CVlIVYYKZ%2BnKdpRc6YYmil7IKhFm6BC6RodYVvWJhGE31dsI2bZmLhhcwlY5n0GKBLi4SMsMkyzIsqzJBswrcEIEg9kCd3Kvh%2BYEEwJgsASIXSBIyQAjhBiAmpSQNEkKipT46CpQYn3OO4kAAi4OEpS4ViGOopvoMkLhoLzqU/cC4TRPEvD4Zk%2BTasU5LVPISgWtK3S2E4BoWH5akjKYZkDCMPKGLhevEPs6P%2Bb0XGPIJ6QiaUEnAt0TqwqYCKjuijhYN7oTEon1L0sX5fV/Xs6t53uEGhCrFQaqVWOAQzAVSHlJGqdVUAlXiFPDS8DQEDC/ivLYZ0uAMS4PxGgtAep9QGoFCaI1FqkKmjNOaC0QbLQpKtdacUto7T2rQA6i0Tow1WIhfA11HB3UOnvVQT03iLTehxRCn1vojT%2BtwyqTlga4TBhDTAUNTpGFhqAGBfAkao3RpjbGINj74y8mfWQxMAqIWvuTOGnMrDUykYLBmTN0gszZgEDmVMLA814KgPmzl7r031hbPwEBXBqxlhLV2itSDKxqBEjW%2BR0jRLtlUA2lsjYJOCTUK2PQ5bTBifbY2WQnZFJSd7BQnsvKP2foJXxnAdjoJ/pgze2CAFAIgFHRy4D47QOqknFOadKCPy4qQHiARt5F2pF3ak1IAjF0kKZCodT4oiVsIPKq0lZIKSUilJBM8dJ6Q4IvbKLAFD8iZPyNprohh2QciQZyR9ZAn1MT5eQF9LE6FrqQW%2B98opV1qf7N%2BylVI7DSo04gLBTnnMudcpgbwhjAJQY1cBAQoGbNgSgZFpV9nYoGBcxIiQdTYLODcgg85IWmS6gQ%2BIRDBrDSmuQhl01Zqi0WnQwQDCNo8MwNtXa%2B1Dq4U4RouRpBeEGwEQ9YRyBnpiMEO9QKUifpHFkQDBRi1lEpFUdDDR4QtHVR0UwZGaMMZY0YDjZ5JiJBmN8h80m3yN7GC8TTGITikIuIEIdJs%2BZKZc0sD4pC/iBbwGFmkkJ4tJYlMiegcpiStZZLick/JutBhhpyZkx2qaOgZMmMm22gwM1RrNi7PNbsPZLC9u7AFsU%2B4NJOWZM5FyBRwoRYqTp9yypx3RYnUgydU4DAzhxUZPEzDbwCAEaC9EO58XHdSViL96lrLEhJHtWdqQ2WmVwKQDEpl5y4NSKuAQa2vzWRix%2BtkF2rITjA%2BYYNUjOEkEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/is_different.hpp)

- [unit test](../../../../tests/unit/metafunctions/typelivore/is_different.test.hpp)
