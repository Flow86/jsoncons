// Copyright 2018 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSON_VISITOR_HPP
#define JSONCONS_JSON_VISITOR_HPP

#include <string>
#include <jsoncons/json_exception.hpp>
#include <jsoncons/bignum.hpp>
#include <jsoncons/ser_context.hpp>
#include <jsoncons/json_options.hpp>
#include <jsoncons/config/jsoncons_config.hpp>
#include <jsoncons/tag_type.hpp>
#include <jsoncons/byte_string.hpp>

namespace jsoncons {

    template <class CharT>
    class basic_json_visitor
    {
    public:
        using char_type = CharT;
        using char_traits_type = std::char_traits<char_type>;

        using string_view_type = basic_string_view<char_type,char_traits_type>;

        basic_json_visitor(basic_json_visitor&&) = default;

        basic_json_visitor& operator=(basic_json_visitor&&) = default;

        basic_json_visitor() = default;

        virtual ~basic_json_visitor() noexcept = default;

        void flush()
        {
            visit_flush();
        }

        bool begin_object(semantic_tag tag=semantic_tag::none,
                          const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_object(tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_object(std::size_t length, 
                          semantic_tag tag=semantic_tag::none, 
                          const ser_context& context = ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_object(length, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool end_object(const ser_context& context = ser_context())
        {
            std::error_code ec;
            bool more = visit_end_object(context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_array(semantic_tag tag=semantic_tag::none,
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_array(tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_array(std::size_t length, 
                         semantic_tag tag=semantic_tag::none,
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_array(length, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool end_array(const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_end_array(context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool key(const string_view_type& name, const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_key(name, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool null_value(semantic_tag tag = semantic_tag::none,
                        const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_null(tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool bool_value(bool value, 
                        semantic_tag tag = semantic_tag::none,
                        const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_bool(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool string_value(const string_view_type& value, 
                          semantic_tag tag = semantic_tag::none, 
                          const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_string(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool byte_string_value(const byte_string_view& b, 
                               semantic_tag tag=semantic_tag::none, 
                               const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_byte_string(b, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool byte_string_value(const uint8_t* p, std::size_t size, 
                               semantic_tag tag=semantic_tag::none, 
                               const ser_context& context=ser_context())
        {
            return byte_string_value(byte_string(p, size), tag, context);
        }

        bool uint64_value(uint64_t value, 
                          semantic_tag tag = semantic_tag::none, 
                          const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_uint64(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool int64_value(int64_t value, 
                         semantic_tag tag = semantic_tag::none, 
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_int64(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool half_value(uint16_t value, 
                        semantic_tag tag = semantic_tag::none, 
                        const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_half(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool double_value(double value, 
                          semantic_tag tag = semantic_tag::none, 
                          const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_double(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_object(semantic_tag tag,
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_begin_object(tag, context, ec);
        }

        bool begin_object(std::size_t length, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_begin_object(length, tag, context, ec);
        }

        bool end_object(const ser_context& context, std::error_code& ec)
        {
            return visit_end_object(context, ec);
        }

        bool begin_array(semantic_tag tag, const ser_context& context, std::error_code& ec)
        {
            return visit_begin_array(tag, context, ec);
        }

        bool begin_array(std::size_t length, semantic_tag tag, const ser_context& context, std::error_code& ec)
        {
            return visit_begin_array(length, tag, context, ec);
        }

        bool end_array(const ser_context& context, std::error_code& ec)
        {
            return visit_end_array(context, ec);
        }

        bool key(const string_view_type& name, const ser_context& context, std::error_code& ec)
        {
            return visit_key(name, context, ec);
        }

        bool null_value(semantic_tag tag,
                        const ser_context& context,
                        std::error_code& ec) 
        {
            return visit_null(tag, context, ec);
        }

        bool bool_value(bool value, 
                        semantic_tag tag,
                        const ser_context& context,
                        std::error_code& ec) 
        {
            return visit_bool(value, tag, context, ec);
        }

        bool string_value(const string_view_type& value, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec) 
        {
            return visit_string(value, tag, context, ec);
        }

        bool byte_string_value(const byte_string_view& b, 
                               semantic_tag tag, 
                               const ser_context& context,
                               std::error_code& ec)
        {
            return visit_byte_string(b, tag, context, ec);
        }

        bool byte_string_value(const uint8_t* p, std::size_t size, 
                               semantic_tag tag, 
                               const ser_context& context,
                               std::error_code& ec)
        {
            return byte_string_value(byte_string(p, size), tag, context, ec);
        }

        bool uint64_value(uint64_t value, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_uint64(value, tag, context, ec);
        }

        bool int64_value(int64_t value, 
                         semantic_tag tag, 
                         const ser_context& context,
                         std::error_code& ec)
        {
            return visit_int64(value, tag, context, ec);
        }

        bool half_value(uint16_t value, 
                        semantic_tag tag, 
                        const ser_context& context,
                        std::error_code& ec)
        {
            return visit_half(value, tag, context, ec);
        }

        bool double_value(double value, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_double(value, tag, context, ec);
        }

        template <class T>
        bool typed_array(const span<T>& data, 
                         semantic_tag tag=semantic_tag::none,
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_typed_array(data, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        template <class T>
        bool typed_array(const span<T>& data, 
                         semantic_tag tag,
                         const ser_context& context,
                         std::error_code& ec)
        {
            return visit_typed_array(data, tag, context, ec);
        }

        bool typed_array(half_arg_t, const span<const uint16_t>& s,
            semantic_tag tag = semantic_tag::none,
            const ser_context& context = ser_context())
        {
            std::error_code ec;
            bool more = visit_typed_array(half_arg, s, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool typed_array(half_arg_t, const span<const uint16_t>& s,
                         semantic_tag tag,
                         const ser_context& context,
                         std::error_code& ec)
        {
            return visit_typed_array(half_arg, s, tag, context, ec);
        }

        bool begin_multi_dim(const span<const size_t>& shape,
                             semantic_tag tag = semantic_tag::multi_dim_row_major,
                             const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_begin_multi_dim(shape, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_multi_dim(const span<const size_t>& shape,
                             semantic_tag tag,
                             const ser_context& context,
                             std::error_code& ec) 
        {
            return visit_begin_multi_dim(shape, tag, context, ec);
        }

        bool end_multi_dim(const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_end_multi_dim(context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool end_multi_dim(const ser_context& context,
                           std::error_code& ec) 
        {
            return visit_end_multi_dim(context, ec);
        }

    #if !defined(JSONCONS_NO_DEPRECATED)

        JSONCONS_DEPRECATED_MSG("Instead, use key(const string_view_type&, const ser_context&=ser_context())") 
        bool name(const string_view_type& name, const ser_context& context=ser_context())
        {
            return key(name, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use key(const string_view_type&, const ser_context&, std::error_code&)") 
        bool name(const string_view_type& name, const ser_context& context, std::error_code& ec)
        {
            return key(name, context, ec);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use byte_string_value(const byte_string_view&, semantic_tag=semantic_tag::none, const ser_context&=ser_context()") 
        bool byte_string_value(const byte_string_view& b, 
                               byte_string_chars_format encoding_hint, 
                               semantic_tag tag=semantic_tag::none, 
                               const ser_context& context=ser_context())
        {
            switch (encoding_hint)
            {
                case byte_string_chars_format::base16:
                    tag = semantic_tag::base16;
                    break;
                case byte_string_chars_format::base64:
                    tag = semantic_tag::base64;
                    break;
                case byte_string_chars_format::base64url:
                    tag = semantic_tag::base64url;
                    break;
                default:
                    break;
            }
            return byte_string_value(b, tag, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use byte_string_value(const byte_string_view&, semantic_tag=semantic_tag::none, const ser_context&=ser_context()") 
        bool byte_string_value(const uint8_t* p, std::size_t size, 
                               byte_string_chars_format encoding_hint, 
                               semantic_tag tag=semantic_tag::none, 
                               const ser_context& context=ser_context())
        {
            switch (encoding_hint)
            {
                case byte_string_chars_format::base16:
                    tag = semantic_tag::base16;
                    break;
                case byte_string_chars_format::base64:
                    tag = semantic_tag::base64;
                    break;
                case byte_string_chars_format::base64url:
                    tag = semantic_tag::base64url;
                    break;
                default:
                    break;
            }
            return byte_string_value(byte_string(p, size), tag, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use string_value with semantic_tag::bigint") 
        bool big_integer_value(const string_view_type& value, const ser_context& context=ser_context()) 
        {
            return string_value(value, semantic_tag::bigint, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use string_value with semantic_tag::bigdec") 
        bool big_decimal_value(const string_view_type& value, const ser_context& context=ser_context()) 
        {
            return string_value(value, semantic_tag::bigdec, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use string_value with semantic_tag::datetime") 
        bool date_time_value(const string_view_type& value, const ser_context& context=ser_context()) 
        {
            return string_value(value, semantic_tag::datetime, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use int64_value with semantic_tag::timestamp") 
        bool timestamp_value(int64_t val, const ser_context& context=ser_context()) 
        {
            return int64_value(val, semantic_tag::timestamp, context);
        }

        JSONCONS_DEPRECATED_MSG("Remove calls to this method, it doesn't do anything") 
        bool begin_document()
        {
            return true;
        }

        JSONCONS_DEPRECATED_MSG("Instead, use flush() when serializing") 
        bool end_document()
        {
            flush();
            return true;
        }

        JSONCONS_DEPRECATED_MSG("Remove calls to this method, it doesn't do anything") 
        void begin_json()
        {
        }

        JSONCONS_DEPRECATED_MSG("Instead, use flush() when serializing") 
        void end_json()
        {
            end_document();
        }

        JSONCONS_DEPRECATED_MSG("Instead, use key(const string_view_type&, const ser_context&=ser_context())") 
        void name(const char_type* p, std::size_t length, const ser_context& context) 
        {
            name(string_view_type(p, length), context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use uint64_value(uint64_t, semantic_tag = semantic_tag::none, const ser_context&=ser_context())") 
        void integer_value(int64_t value)
        {
            int64_value(value);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use int64_value(int64_t, semantic_tag = semantic_tag::none, const ser_context&=ser_context())") 
        void integer_value(int64_t value, const ser_context& context)
        {
            int64_value(value,context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use uint64_value(uint64_t, semantic_tag = semantic_tag::none, const ser_context&=ser_context())") 
        void uinteger_value(uint64_t value)
        {
            uint64_value(value);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use uint64_value(uint64_t, semantic_tag = semantic_tag::none, const ser_context&=ser_context())") 
        void uinteger_value(uint64_t value, const ser_context& context)
        {
            uint64_value(value,context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use string_value with semantic_tag::bigint") 
        bool bignum_value(const string_view_type& value, const ser_context& context=ser_context()) 
        {
            return string_value(value, semantic_tag::bigint, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use string_value with semantic_tag::bigdec") 
        bool decimal_value(const string_view_type& value, const ser_context& context=ser_context()) 
        {
            return string_value(value, semantic_tag::bigdec, context);
        }

        JSONCONS_DEPRECATED_MSG("Instead, use int64_value with semantic_tag::timestamp") 
        bool epoch_time_value(int64_t val, const ser_context& context=ser_context()) 
        {
            return int64_value(val, semantic_tag::timestamp, context);
        }

    #endif
    private:

        virtual void visit_flush() = 0;

        virtual bool visit_begin_object(semantic_tag tag, 
                                     const ser_context& context, 
                                     std::error_code& ec) = 0;

        virtual bool visit_begin_object(std::size_t /*length*/, 
                                     semantic_tag tag, 
                                     const ser_context& context, 
                                     std::error_code& ec)
        {
            return visit_begin_object(tag, context, ec);
        }

        virtual bool visit_end_object(const ser_context& context, 
                                   std::error_code& ec) = 0;

        virtual bool visit_begin_array(semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec) = 0;

        virtual bool visit_begin_array(std::size_t /*length*/, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec)
        {
            return visit_begin_array(tag, context, ec);
        }

        virtual bool visit_end_array(const ser_context& context, 
                                  std::error_code& ec) = 0;

        virtual bool visit_key(const string_view_type& name, 
                             const ser_context& context, 
                             std::error_code&) = 0;

        virtual bool visit_null(semantic_tag tag, 
                             const ser_context& context, 
                             std::error_code& ec) = 0;

        virtual bool visit_bool(bool value, 
                             semantic_tag tag, 
                             const ser_context& context, 
                             std::error_code&) = 0;

        virtual bool visit_string(const string_view_type& value, 
                               semantic_tag tag, 
                               const ser_context& context, 
                               std::error_code& ec) = 0;

        virtual bool visit_byte_string(const byte_string_view& value, 
                                    semantic_tag tag, 
                                    const ser_context& context,
                                    std::error_code& ec) = 0;

        virtual bool visit_uint64(uint64_t value, 
                               semantic_tag tag, 
                               const ser_context& context,
                               std::error_code& ec) = 0;

        virtual bool visit_int64(int64_t value, 
                              semantic_tag tag,
                              const ser_context& context,
                              std::error_code& ec) = 0;

        virtual bool visit_half(uint16_t value, 
                             semantic_tag tag,
                             const ser_context& context,
                             std::error_code& ec)
        {
            return visit_double(jsoncons::detail::decode_half(value),
                             tag,
                             context,
                             ec);
        }

        virtual bool visit_double(double value, 
                               semantic_tag tag,
                               const ser_context& context,
                               std::error_code& ec) = 0;

        virtual bool visit_typed_array(const span<const uint8_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const uint16_t>& s, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const uint32_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) 
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const uint64_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) 
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int8_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int16_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int32_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int64_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(half_arg_t, 
                                    const span<const uint16_t>& s, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = half_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const float>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = double_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const double>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = double_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_begin_multi_dim(const span<const size_t>& shape,
                                        semantic_tag tag,
                                        const ser_context& context, 
                                        std::error_code& ec) 
        {
            bool more = visit_begin_array(2, tag, context, ec);
            if (more)
            {
                more = visit_begin_array(shape.size(), tag, context, ec);
                for (auto it = shape.begin(); more && it != shape.end(); ++it)
                {
                    visit_uint64(*it, semantic_tag::none, context, ec);
                }
                if (more)
                {
                    more = visit_end_array(context, ec);
                }
            }
            return more;
        }

        virtual bool visit_end_multi_dim(const ser_context& context,
                                      std::error_code& ec) 
        {
            return visit_end_array(context, ec);
        }
    };

    template <class CharT>
    class basic_default_json_visitor : public basic_json_visitor<CharT>
    {
        bool parse_more_;
        std::error_code ec_;
    public:
        using typename basic_json_visitor<CharT>::string_view_type;

        basic_default_json_visitor(bool accept_more = true,
                                           std::error_code ec = std::error_code())
            : parse_more_(accept_more), ec_(ec)
        {
        }
    private:
        void visit_flush() override
        {
        }

        bool visit_begin_object(semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_end_object(const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_begin_array(semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_end_array(const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_key(const string_view_type&, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_null(semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_string(const string_view_type&, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_byte_string(const byte_string_view&, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_uint64(uint64_t, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_int64(int64_t, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_half(uint16_t, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_double(double, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }

        bool visit_bool(bool, semantic_tag, const ser_context&, std::error_code& ec) override
        {
            if (ec_)
            {
                ec = ec_;
            }
            return parse_more_;
        }
    };

    using json_visitor = basic_json_visitor<char>;
    using wjson_visitor = basic_json_visitor<wchar_t>;

    using default_json_visitor = basic_default_json_visitor<char>;
    using wdefault_json_visitor = basic_default_json_visitor<wchar_t>;

#if !defined(JSONCONS_NO_DEPRECATED)
template<class CharT>
using basic_json_content_handler = basic_json_visitor<CharT>; 

JSONCONS_DEPRECATED_MSG("Instead, use json_visitor") typedef json_visitor json_content_handler;
JSONCONS_DEPRECATED_MSG("Instead, use wjson_visitor") typedef wjson_visitor wjson_content_handler;

template<class CharT>
using basic_default_json_content_handler = basic_default_json_visitor<CharT>; 

JSONCONS_DEPRECATED_MSG("Instead, use default_json_visitor") typedef default_json_visitor default_json_content_handler;
JSONCONS_DEPRECATED_MSG("Instead, use default_wjson_visitor") typedef wdefault_json_visitor default_wjson_content_handler;
#endif

} // namespace jsoncons

#endif