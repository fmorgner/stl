#ifndef SOPHIA_IO__PRINTF
#define SOPHIA_IO__PRINTF

#include "sophia/concept/io.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <typeinfo>

namespace sophia
  {

  namespace io
    {

    namespace internal
      {

      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief A type-unaware wrapper for printable objects
       *
       * This abstract base defines a type-independent interface for object that can be printed. This is required since type
       * information matters when printing, but at the same time having a type-aware base would prohibit the use of standard
       * containers.
       */
      struct printable
        {
        virtual void print(std::ostream &) = 0;
        };

      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief A fully type-aware wrapper for non-printable objects
       *
       * This concrete implementation of #printable provides a generic wrapper for objects of types that do not support the
       * use of operator "<<" in order to write them to a stream. Instead it prints the type information and the address of
       * the object.
       */
      template<typename ValueType, typename = void>
      struct typed_printable: printable
        {
        typed_printable(ValueType const & value)
          : m_contained{value}
          {

          }

        void print(std::ostream & stream)
          {
          stream << '<' << typeid(ValueType).name() << '@' << &m_contained << '>';
          }

        private:
          ValueType const & m_contained;
        };

      /**
       * @internal
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief A fully type-aware wrapper for printable objects
       *
       * This concrete implementation of #printable provides a generic wrapper for objects of types that support the use of
       * operator "<<" in order to write them to a stream.
       */
      template<typename ValueType>
      struct typed_printable<ValueType, concept::outputable<ValueType>> : printable
        {
        typed_printable(ValueType const & value)
          : m_contained{value}
          {

          }

        void print(std::ostream & stream)
          {
          stream << m_contained;
          }

        private:
          ValueType const & m_contained;
        };

      }

      /**
       * @ingroup sophia_io
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief A type-safe implementation of the classic printf with a python-like format syntax
       *
       * This function provides a type-safe version of the classic printf C API. The syntax of the format string is inspired
       * by the Python format syntax. The parameters are "addressable" in the format string. Addressing an invalid argument
       * index causes the original placeholder to be printed.
       *
       * Example:
       * @code
       * #include <io/printf.hpp>
       *
       * int main()
       *   {
       *   sophia::io::printf(std::clog, "{1} is second argument, {0} is the first!", 1337, 42);
       *   }
       * @endcode
       *
       * @param stream The stream to print to. Must be descendent from std::ostream.
       * @param format A python like format-string using {#} as placeholders, where # is the index of the parameter to print.
       * @param values The values to substitute for the placeholders.
       */
    template<typename StreamType,
             typename = std::enable_if_t<std::is_base_of<std::ostream, StreamType>::value, void>,
             typename ...ValueTypes >
    void printf(StreamType & stream, std::string const & format, ValueTypes const & ...values)
      {
      std::array<std::unique_ptr<internal::printable>, sizeof...(values)> elements{
        {std::make_unique<internal::typed_printable<ValueTypes>>(values)...}
        };

      auto opening = 0ull;
      auto closing = 0ull;
      auto lastpos = -1ull;

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
            elements[idx]->print(stream);
            }
          }
        catch(...)
          {
          stream << '{' << placeholder << '}';
          }

        }

      stream << format.substr(lastpos + 1);
      }

      /**
       * @ingroup sophia_io
       * @author Felix Morgner
       * @since 0.1
       *
       * @brief A type-safe implementation of the classic printf with a python-like format syntax
       *
       * This function provides a type-safe version of the classic printf C API. The syntax of the format string is inspired
       * by the Python format syntax. The parameters are "addressable" in the format string. Addressing an invalid argument
       * index causes the original placeholder to be printed.
       *
       * Example:
       * @code
       * #include <io/printf.hpp>
       *
       * int main()
       *   {
       *   sophia::io::printf("{1} is second argument, {0} is the first!", 1337, 42);
       *   }
       * @endcode
       *
       * @note This version of the function prints to standard output. See #printf for a more generic version.
       *
       * @param format A python like format-string using {#} as placeholders, where # is the index of the parameter to print.
       * @param values The values to substitute for the placeholders.
       */
    template<typename ...ArgumentTypes>
    void printf(std::string const & format, ArgumentTypes const & ...values)
      {
      printf(std::cout, format, values...);
      }

    }

  }

#endif

