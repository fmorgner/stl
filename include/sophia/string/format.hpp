#ifndef SOPHIA_STRING__FORMAT
#define SOPHIA_STRING__FORMAT

#include "sophia/concept/io.hpp"
#include "sophia/concept/type_descriptor.hpp"

#include <array>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>

#include <cxxabi.h>

namespace sophia::string
  {

  namespace internal
    {

    /**
     * @internal
     * @author Felix Morgner
     * @since 0.2
     *
     * @brief Demangle a C++ identifies into its human-readable form
     *
     * @param type A std::type_info like object obtained via typeid(...) or similar
     */
    template<typename TypeDescriptor,
             typename = sophia::concept::type_descriptor<TypeDescriptor>>
    std::string demangle(TypeDescriptor const & type)
      {
      int status{};
      auto demangled = std::unique_ptr<char, void(*)(void *)>{
        abi::__cxa_demangle(type.name(), nullptr, nullptr, &status),
        std::free
        };

      if(status)
        {
        return type.name();
        }

      return demangled.get();
      }

    /**
     * @internal
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief A type-unaware wrapper for formatable objects
     *
     * This abstract base defines a type-independent interface for object that can be formatted. This is required since type
     * information matters when formatting, but at the same time having a type-aware base would prohibit the use of standard
     * containers.
     */
    struct formatable
      {
      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief Print a description of the wrapped value
       */
      virtual void format(std::ostream &) = 0;
      };

    /**
     * @internal
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief A fully type-aware wrapper for non-formatable objects
     *
     * This concrete implementation of #sophia::io::internal::formatable provides a generic wrapper for objects of types that
     * do not support the use of operator "<<" in order to write them to a stream. Instead it formats the type information and
     * the address of the object.
     */
    template<typename ValueType, typename = void>
    struct typed_formatable: formatable
      {
      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief Construct a new typed_formatable wrapping the given value
       */
      typed_formatable(ValueType const & value)
        : m_contained{value}
        {

        }

      void format(std::ostream & stream) override
        {
        stream << '<' << demangle(typeid(ValueType)) << '@' << &m_contained << '>';
        }

      private:
        ValueType const & m_contained;
      };

    /**
     * @internal
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief A fully type-aware wrapper for formatable objects
     *
     * This concrete implementation of #sophia::io::internal::formatable provides a generic wrapper for objects of types that
     * support the use of operator "<<" in order to write them to a stream.
     */
    template<typename ValueType>
    struct typed_formatable<ValueType, concept::outputable<ValueType>> : formatable
      {
      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief Construct a new typed_formatable wrapping the given value
       */
      typed_formatable(ValueType const & value)
        : m_contained{value}
        {

        }

      void format(std::ostream & stream) override
        {
        stream << m_contained;
        }

      private:
        ValueType const & m_contained;
      };

    }

  /**
   * @ingroup sophia_io
   *
   * @brief A type-safe implementation of string formatting
   *
   * This function provides a type-safe way for replace placeholders in format strings. The syntax of the format string is
   * inspired by the Python format syntax. The parameters are "addressable" in the format string. Addressing an invalid
   * argument index causes the original placeholder to be formatted.
   *
   * @par Example:
   * @rst
   * .. code-block:: c++
   *    :linenos:
   *
   *    #include <sophia/string/format.hpp>
   *
   *    int main()
   *      {
   *      auto s = sophia::string::format("{1} is second argument, {0} is the first!", 1337, 42);
   *      }
   * @endrst
   *
   * @param format A python like format-string using {#} as placeholders, where # is the index of the parameter to format.
   * @param values The values to substitute for the placeholders.
   * @author Felix Morgner
   * @since 0.2
   */
  template<typename ...ArgumentTypes>
  std::string format(std::string const & format, ArgumentTypes const & ...values)
    {
    std::array<std::unique_ptr<internal::formatable>, sizeof...(values)> elements{
      {std::make_unique<internal::typed_formatable<ArgumentTypes>>(values)...}
      };

    auto opening = 0ull;
    auto closing = 0ull;
    auto lastpos = -1ull;

    auto && stream = std::ostringstream{};
    while((opening = format.find("{", closing)) != std::string::npos)
      {
      closing = format.find("}", opening);
      auto placeholder = std::string{};

      if(closing != std::string::npos)
        {
        stream << format.substr(lastpos + 1, opening - lastpos - 1);
        placeholder = format.substr(opening + 1, closing - opening);
        lastpos = closing;
        }
      else
        {
        break;
        }

      try
        {
        auto idx = std::stoull(placeholder);
        if(idx >= elements.size() || idx < 0)
          {
          stream << '{' << idx << '}';
          }
        else
          {
          elements[idx]->format(stream);
          }
        }
      catch(...)
        {
        stream << '{' << placeholder << '}';
        }

      }

    stream << format.substr(lastpos + 1);
    return stream.str();
    }

  }

#endif
