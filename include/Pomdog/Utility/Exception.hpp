// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_EXCEPTION_46DED4E6_HPP
#define POMDOG_EXCEPTION_46DED4E6_HPP

#include <stdexcept>
#include <string>
#include <sstream>

namespace Pomdog {
namespace Detail {
namespace ExceptionInternal {

template <typename T> constexpr
char const* ToString() { return "Exception"; }

// Logic errors
template<> constexpr char const* ToString<std::logic_error>(){ return "Logic error exception"; }
template<> constexpr char const* ToString<std::domain_error>(){ return "Domain error exception"; }
template<> constexpr char const* ToString<std::invalid_argument>(){ return "Invalid argument exception"; }
template<> constexpr char const* ToString<std::length_error>(){ return "Length error exception"; }
template<> constexpr char const* ToString<std::out_of_range>(){ return "Out of range exception"; }

// Runtime errors
template<> constexpr char const* ToString<std::runtime_error>(){ return "Runtime error exception"; }
template<> constexpr char const* ToString<std::range_error>(){ return "Range error exception"; }
template<> constexpr char const* ToString<std::overflow_error>(){ return "Overflow error exception"; }
template<> constexpr char const* ToString<std::underflow_error>(){ return "Underflow error exception"; }

template <typename T>
T CreateException(std::string const& description, std::string const& source, char const* filename, int line)
{
    static_assert(std::is_base_of<std::exception, T>::value, "T is base of std::exception");

    // examples:
    // > File "filename", line 4 in source
    // > Runtime error exception: description
    std::stringstream ss;
    ss << "File \"" << filename << "\", line " << line
        << " in " << (source.empty()? "?": source) << std::endl
        << ExceptionInternal::ToString<T>()
        << ": " << description;

    return T(ss.str());
}

} // namespace ExceptionInternal
} // namespace Detail

#if !defined(POMDOG_THROW_EXCEPTION)

#define POMDOG_THROW_EXCEPTION(exceptionClass, description) \
    throw Pomdog::Detail::ExceptionInternal::CreateException< \
        exceptionClass>(description, __func__, __FILE__, __LINE__)

#endif // !defined(POMDOG_THROW_EXCEPTION)

} // namespace Pomdog

#endif // POMDOG_EXCEPTION_46DED4E6_HPP
