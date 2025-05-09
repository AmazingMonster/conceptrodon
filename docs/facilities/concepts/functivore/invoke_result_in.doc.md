<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::InvokeResultIn`

<p style='text-align: right;'><a href="../../concepts.md#functivore-invoke-result-in">To Index</a></p>

## Description

`Functivore::InvokeResultIn` accepts a function-like type, a possible return type, and a list of argument type.
It returns true if the function-like type invoked by the argument types returns the possible return type .

## Structure

```C++
template<typename>
concept InvokeResultIn = REQUIREMENT;
```

## Implementation

```C++
template<typename Fun, typename Result, typename...Args>
concept InvokeResultIn
= std::same_as<typename GetInvokeReturnType<Fun>::template Mold<Args...>, Result>;
```

Note that since `std::invoke_result` does not work with volatile lvalue reference qualified(`volatile &`) member functions.

```C++
struct FO
{
    void operator()() volatile & {};
};

// This will fail.
static_assert(std::same_as<std::invoke_result_t<FO, int, int*, int**, int***>, void>);
```

The following code will not compile:

```C++
static_assert(std::same_as<GetInvokeReturnType<FO>::Mold<int, int*, int**, int***>, void>);
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAJxmpK4AMngMmAByPgBGmMQBABykAA6oCoRODB7evgFBaRmOAmER0SxxCf7JdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIpgprozIeJgKd8cX17dnAJOvyulxBZgAzOFkN4sHcTOC3GgGNsUgQFPDsKDzJDkTDMHCEQQAJ4vAD6BGITEI6PBmOuoP%2B%2BzuV2YtCJAC94t8jsCCJgWCkDHyCW5iS9mGwMaDZsQvA5mayOfFlMRUEQxfiTAB2Kxah7wqz0658gVCzWEkmMVj4gBKmAIpDuGolmAAdO6rsRgDS6VcZXKCAqxEriCq1WrLfC3HaCBBPd73a6VlL6TrQXcM3cvBkjHcAG7NPBMfDIcmW0kZYDMAibc0PO4xuNehSJ5Pgw0gvUGrHG/mCpjCqPO60N%2B2O4dsRPxn3SikBoNszmh1XqyMIxvTxOO1spzsdzNZnPAfOF4t4Usait4KsD2sE%2Bsb5tbu479tYrtvo1XE39wcW8UjjG46Wi6U7Nru/ryiywZLmGq4vFGj4Ju6Kx3Eisy7tq%2B6Ztm4THgWxBFiWZZkpW1Z3vCD72k2yFJt2qb6p%2BIK9qaA7mqKIGAWOTqcZOHrgbSs6ylBiqwSuEYIeu1Gbu624oWhAgYYJqbYRmuG5gRRHniRmBXjeNbEHWo6xjJrpyXRTHaoxHagj%2BZpDrx%2BIAGIMBBc4iTBox3CkXgxLQ54LiGcESZgUYuRicJph%2BNksb%2BoX/labB3OFyl%2Bu5gbQYu8RhQw%2By7iA3m%2Bf5yCBWJ4YajlEVYVZ9HMd%2Bfb2QlLp3AAsvyLnAQBSWNMJBnxb6kEZaJ2UIm1LAuXcPUBrWIAgHlqUFT5fkBZlQXiRVo3ta5tKRbq1k9vVrF8g5XXOQA8ruhkAI5eHghlfNdt33bt5gAGxOWds2oC8lJEMQEBtntQnzqtS5hRdC2FctJWgyNbhYNCGoQG9H1fT9A4kADbbYC90UHYydwACokueYgAOL2gAaqeJbEy8QjXuRhncocvINWxJ2Jc520DelRMk6ItAUwQ1OEWeyB05gDP6bW74WIeeE8S896lXDKXYLNmnizpelM/FQOWX8xx3MLotaRLlrS3rLPnLZ7PHU11pgd6u7qceps0%2BektW7ezOUfzKSk0LVOexb9OM778VuKZGKzRtMU3MbwsAJIMHmqAANaYDGmwMJLNts0dUcTtzbm9Sb9qp%2BnWc58QeeRip6aZnZHOO3xrrTruB5u61njoCrszoLN4TV7p91eLQBDklGHti7TlsR31lW0o6MeCZZeNfi3DscadyU86Cj13Z8dyD8PCiktCTAKBfebL7z5cp2nmfZ/aueS/fctNxm2/F45zszmuN3I8vdaD939mfEAI8X6knHpPaeCIOrMifO6KUG99pfkZICbBtsjb3GTqafkjAmi9ALgyHBFDcF1V/pzZqTkvAME6lzUcCgJ4OiVlzABu4kQokDFXF%2BdpWGT1TlicE9ZIEKGtKSa%2BtCRxP1HrXeukk3D0J5nHe2%2BIWp9yjGvbAjpBFsLQQnLB2DgQE0Jp8NEZC8GUOBMDeUH0v5AMzOnPA/dvrxAxv9FYAN8yeAHHQTUZhXq4wwZ2MJDJdhEwQHgL4AB3OgtA7hUCpLQV0s4AmlmvkoFoEAJFSJkQiSB0Cs6wM%2BGwhBKizqOnCOw2p%2BwamCEOI0ggRwMSOlcegDEgN8ZRMJjE%2BJiS7hiAUKgZJqT0nXFmJk6RN94ixnyWwWZM9K7Pxrm/OuH9EEQw1iALRYCoy1JaQ0u49STlnPmnovxbjukGg4GsWgnAACsvA/AcC0KQVAnA3DWGsKfDYWwgngh4KQAgmh7lrAziASQiRXTgn8P4LU4JEhIrMIkJ5khwTSEeRwSQvAWASA0BoUgbyPlfI4LwBQIBiVgvefc0gcBYAwEQCADYBAfIOgoBANAApAnEEiNaTgqhEivQALSvUkHcYAyASpSFdGYXgmB8B/TcXofgggRBiHYFIGQghFAqHUHS0guguCkDiZSFInAeAPOea88FnzOBnS8Oy51dxUBUDuMKsVEqpUyruHKswdwIAeF5fQYgcIIRcBWLwWlWg1gQCQDywOYbyCUCTXykAwApBBBoJPeIVKIAxHtTEcIzQiRWt4CW5gxAiRnRiNoOotKQU8rYIIM6DA2T2qwDELwwA3BiFoFS7gvAsAsEMMAcQRr8CGXqHmT49rMCqDqM6nYILandHtf5GIlIa0eCwPaikeACXDtIHO4gMR0iYCeGOow/kjDgrWFQAw3pKYfDiWdcUFbdXCEFtq6Q6r5BKDUPak1%2Bhx0oF%2BZYfQeAYhUsgGsb6vQh2isHpRUwlhrBmDJWewiWA4MAy6D0LILgGDuE8O0PQoQFjlEqHoQomQBBTD8Ka%2BjvQhg0dGKa2o9QBD9EmORvIXHuiNoaHMdjIwEhcbmExvQ0yWjiaWJJtYozNjbAkDajgLySX2vJZ6kV4rJXStlZIeVQbcCEBIBG4F0bQUPrWAgTAxZRgEahZi10/hwRakkBoSQZhJCvSJU816/h9CcDxaQAlwLXSvS4K9RI1RYsYq4E8jzr1tNGvJZS6ltm6XxuZQm1lzqOWpu5agUN8QBVsE4M0FgeYtSiqYGhAwuYuD%2BFdFwV0HylUWdw2q2QmrxA6oA/q4DRrdBBHNUwS1w6NNadJbwclTqXWBndXp71kqr4tbax1jQQaQ3Jq5NiMwNnY30oK%2BmlNXKLujE21m/wXBiW5r5MQAtRajVVrLV%2Bj7Na60NocF%2BltxD22dqnZgHtfaB1DpBaO8dk6PnTpE3OodXWl3IBXV%2B9dOKPlbp3USPdOwPmHuPSCs9F6lDXth3hB9fBn0KFfZgd9n6T0AYG3%2B79I3DUfPG2B%2B96GrBQa3fhhDqIsjIdQ2IvnmHsPxFw/O%2BDhGRPOAgK4GTpqqNlAk3R9IDHsgCeY6kbXbHqOa6E0R3j0m9eyeEzxvoYnjeKdkxb3I%2Bu5PzA1w7qN6xVPatm3ajLnA1sGaa%2BO/123OtmeVZZ7EUaY12dIA5pzCQCM4vC5FtrPmtQpa1Ei3z/nJCmvmw6ilthsunby/AArbLitXbKwd/lgqOA1Z9SwBQeYSp5la66M0sxFWR966alnv6JD/tkBzkDIBwRmotRW336WyWOqK661bqhm%2Bt/b537vgZg2175VZ8EJ3qfnZ35dtNx/Rht5SCkUkHf/Ckk36SFf/66DPde8W0tNavvv9rfWxtAOyutoIGB3LVB3B37VoEHS/Rh1vQJxHWPlnXnSNUXWXT5Ax0EA3SNRxzLXxwPUImJ14FJ0vQp1vSp1yxpyYBfTfQ/UYC/UHy1WH3ZyA05x0Anx52MEgxsEF3gGFyQ04F2DPkl0sCwwWxwzcTlwI2416BIzI2d0o1IwU1oxY0NyyFVwNyKCyHkM4wVxtz41aEt1N0V1twGA0Mk3GAGBUNd2MPUy90BSsJxTmx0wD0fzuBbzb3zA3zYlmAjx6ysxjxyzjXs0cywCTw01TxADMDa3BHBCeSeR8wew0EiK1DiznwW04CyxpTjyhSeQ6wCw0GCS4GCS1CkCC2iNCw4HBD93n2LzLw0wVWSKL1j1yzWDPQyGcEkCAA%3D%3D)

## Links

- [Source code](../../../../conceptrodon/functivore/concepts/invoke_result_in.hpp)
- [Unit test](../../../../tests/unit/concepts/functivore/invoke_result_in.test.hpp)
