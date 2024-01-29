//
//
//      uti
//      string_view.hpp
//

#pragma once

#include <util/assert.hpp>
#include <meta/traits.hpp>

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int) (sv).size(), (sv).data()


namespace uti
{


template< typename CharType >
struct string_view ;

using string_view_t = string_view< char const > ;


template< typename CharType >
struct string_view
{
        using value_type = CharType ;
        using  size_type =   size_t ;
        using ssize_type =  ssize_t ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using       iterator =       pointer ;
        using const_iterator = const_pointer ;

                 constexpr string_view (                                     ) noexcept ;
        explicit constexpr string_view ( pointer _c_str_                     ) noexcept ;
                 constexpr string_view ( pointer  _data_, ssize_type _count_ ) noexcept ;

        constexpr string_view ( string_view const &  _other_ ) noexcept = default ;
        constexpr string_view ( string_view       && _other_ ) noexcept           ;

        constexpr string_view & operator= ( string_view const &  _other_ ) noexcept = default ;
        constexpr string_view & operator= ( string_view       && _other_ ) noexcept           ;

        constexpr       reference operator[] ( ssize_type const _index_ )       noexcept { return data_[ _index_ ]; }
        constexpr const_reference operator[] ( ssize_type const _index_ ) const noexcept { return data_[ _index_ ]; }

        constexpr bool operator== ( string_view const & _other_ ) const noexcept { return data_ == _other_.data_ && size_ == _other_.size_; }
        constexpr bool operator!= ( string_view const & _other_ ) const noexcept { return !operator==( _other_ ); }

        constexpr ssize_type operator++ (     ) noexcept { --data_; return ++size_; } // extends view on  left side
        constexpr ssize_type operator++ ( int ) noexcept {          return ++size_; } // extends view on right side

        constexpr ssize_type operator-- (     ) noexcept { ++data_; return --size_; } // shrinks view on  left side
        constexpr ssize_type operator-- ( int ) noexcept {          return --size_; } // shrinks view on right side

        [[ nodiscard ]] constexpr bool equal_to             ( string_view const & _other_ ) const noexcept ;
        [[ nodiscard ]] constexpr bool equal_to_insensitive ( string_view const & _other_ ) const noexcept ;

        [[ nodiscard ]] constexpr bool starts_with             ( string_view const & _prefix_ ) const noexcept ;
        [[ nodiscard ]] constexpr bool starts_with_insensitive ( string_view const & _prefix_ ) const noexcept ;
        [[ nodiscard ]] constexpr bool   ends_with             ( string_view const & _suffix_ ) const noexcept ;
        [[ nodiscard ]] constexpr bool   ends_with_insensitive ( string_view const & _suffix_ ) const noexcept ;

        constexpr ssize_type trim       () noexcept ;
        constexpr ssize_type trim_left  () noexcept ;
        constexpr ssize_type trim_right () noexcept ;

        [[ nodiscard ]] constexpr string_view trimmed       () const noexcept ;
        [[ nodiscard ]] constexpr string_view trimmed_left  () const noexcept ;
        [[ nodiscard ]] constexpr string_view trimmed_right () const noexcept ;

        [[ nodiscard ]] constexpr string_view substr ( ssize_type const _start_, ssize_type const _len_ = 0 ) const noexcept ;

        [[ nodiscard ]] constexpr string_view chop_left  ( ssize_type _count_ ) noexcept ;
        [[ nodiscard ]] constexpr string_view chop_right ( ssize_type _count_ ) noexcept ;

        constexpr void unchop_left  ( ssize_type _count_ ) noexcept ;
        constexpr void unchop_right ( ssize_type _count_ ) noexcept ;

        [[ nodiscard ]] constexpr string_view chop_to_first_of ( string_view const & _delims_, bool const _discard_delimiter_ ) noexcept ;

        [[ nodiscard ]] constexpr value_type chop_char_left  () noexcept ;
        [[ nodiscard ]] constexpr value_type chop_char_right () noexcept ;

        [[ nodiscard ]] constexpr ssize_type index_of ( value_type  const & _val_, ssize_type const start ) const noexcept ;
        [[ nodiscard ]] constexpr ssize_type index_of ( string_view const & _val_, ssize_type const start ) const noexcept ;

        [[ nodiscard ]] constexpr bool contains ( value_type const & _val_ ) const noexcept ;

        [[ nodiscard ]] constexpr ssize_type count ( value_type const & _val_ ) const noexcept ;

        [[ nodiscard ]] constexpr string_view chop_to_delimiter ( value_type  const & _delimiter_, bool _discard_delimiter_ ) noexcept ;
        [[ nodiscard ]] constexpr string_view chop_to_string    ( string_view const & _delimiter_, bool _discard_delimiter_ ) noexcept ;

        template< typename Predicate >
        [[ nodiscard ]] constexpr string_view chop_left_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) ) ;

        template< typename Predicate >
        [[ nodiscard ]] constexpr string_view chop_right_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) ) ;

        template< typename Integer >
        [[ nodiscard ]] constexpr Integer parse_int () const noexcept ;

        template< typename Float >
        [[ nodiscard ]] constexpr Float parse_float () const noexcept ;

        [[ nodiscard ]] constexpr       reference at ( ssize_type const _index_ )       noexcept ;
        [[ nodiscard ]] constexpr const_reference at ( ssize_type const _index_ ) const noexcept ;

        [[ nodiscard ]] constexpr ssize_type size () const noexcept { return size_; }
        [[ nodiscard ]] constexpr ssize_type  len () const noexcept { return size_; }

        [[ nodiscard ]] constexpr       pointer data ()       noexcept { return data_; }
        [[ nodiscard ]] constexpr const_pointer data () const noexcept { return data_; }

        [[ nodiscard ]] constexpr bool empty () const noexcept { return data_ == nullptr || size_ == 0; }

        constexpr       iterator  begin ()       noexcept { return   data_; }
        constexpr const_iterator  begin () const noexcept { return   data_; }
        constexpr const_iterator cbegin () const noexcept { return begin(); }

        constexpr       iterator  last ()       noexcept { return &data_[ size_ - 1 ]; }
        constexpr const_iterator  last () const noexcept { return &data_[ size_ - 1 ]; }
        constexpr const_iterator clast () const noexcept { return              last(); }

        constexpr       iterator  end ()       noexcept { return &data_[ size_ ]; }
        constexpr const_iterator  end () const noexcept { return &data_[ size_ ]; }
        constexpr const_iterator cend () const noexcept { return           end(); }

        [[ nodiscard ]] constexpr       reference  front ()       noexcept { return *begin(); }
        [[ nodiscard ]] constexpr const_reference  front () const noexcept { return *begin(); }
        [[ nodiscard ]] constexpr const_reference cfront () const noexcept { return  front(); }

        [[ nodiscard ]] constexpr       reference  back ()       noexcept { return *last(); }
        [[ nodiscard ]] constexpr const_reference  back () const noexcept { return *last(); }
        [[ nodiscard ]] constexpr const_reference cback () const noexcept { return  back(); }
private:
        pointer    data_ ;
        ssize_type size_ ;
};


template< typename CharType >
[[ nodiscard ]] constexpr long long strlen ( CharType const * str ) noexcept
{
        long long len { -1 };
        while( str[ ++len ] != '\0' ) {}
        return len;
}


template< typename CharType >
[[ nodiscard ]] constexpr CharType to_lower ( CharType chr ) noexcept
{
        if( 'A' <= chr && chr <= 'Z' ) return chr + 0x20;
        return chr;
}


template< typename CharType >
constexpr string_view< CharType >::string_view () noexcept
        : data_( nullptr ),
          size_(       0 )
{}

template< typename CharType >
constexpr string_view< CharType >::string_view ( pointer _c_str_ ) noexcept
        : data_(         _c_str_   ),
          size_( strlen( _c_str_ ) )
{}

template< typename CharType >
constexpr string_view< CharType >::string_view ( pointer _data_, ssize_type _count_ ) noexcept
        : data_(  _data_ ),
          size_( _count_ )
{}

template< typename CharType >
constexpr string_view< CharType >::string_view ( string_view && _other_ ) noexcept
        : data_( UTI_MOVE( _other_.data_ ) ),
          size_( UTI_MOVE( _other_.size_ ) )
{
        _other_.data_ = nullptr ;
        _other_.size_ =       0 ;
}

template< typename CharType >
constexpr string_view< CharType > &
string_view< CharType >::operator= ( string_view && _other_ ) noexcept
{
        data_ = UTI_MOVE( _other_.data_ ) ;
        size_ = UTI_MOVE( _other_.size_ ) ;

        _other_.data_ = nullptr ;
        _other_.size_ =       0 ;

        return *this;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::equal_to ( string_view const & _other_ ) const noexcept
{
        if( size() != _other_.size() )
        {
                return false;
        }
        if( !uti::is_constant_evaluated() && data() == _other_.data() )
        {
                return true;
        }
        for( ssize_type i = 0; i < size(); ++i )
        {
                if( at( i ) != _other_.at( i ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::equal_to_insensitive ( string_view const & _other_ ) const noexcept
{
        if( size() != _other_.size() )
        {
                return false;
        }
        if( !uti::is_constant_evaluated() && data() == _other_.data() )
        {
                return true;
        }
        for( ssize_type i = 0; i < size(); ++i )
        {
                if( to_lower( at( i ) ) != to_lower( _other_.at( i ) ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::starts_with ( string_view const & _prefix_ ) const noexcept
{
        if( _prefix_.len() > len() ) return false;

        if( !uti::is_constant_evaluated() && data() == _prefix_.data() )
        {
                return true;
        }
        for( ssize_type i = 0; i < _prefix_.size(); ++i )
        {
                if( at( i ) != _prefix_.at( i ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::starts_with_insensitive ( string_view const & _prefix_ ) const noexcept
{
        if( _prefix_.len() > len() ) return false;

        if( !uti::is_constant_evaluated() && data() == _prefix_.data() )
        {
                return true;
        }
        for( ssize_type i = 0; i < _prefix_.size(); ++i )
        {
                if( to_lower( at( i ) ) != to_lower( _prefix_.at( i ) ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::ends_with ( string_view const & _suffix_ ) const noexcept
{
        if( _suffix_.len() > len() ) return false;

        ssize_type pos = size() - _suffix_.size();

        if( !uti::is_constant_evaluated() && data() + pos == _suffix_.data() )
        {
                return true;
        }
        for( ssize_type i = 0; i < _suffix_.size(); ++i )
        {
                if( at( pos + i ) != _suffix_.at( i ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::ends_with_insensitive ( string_view const & _suffix_ ) const noexcept
{
        if( _suffix_.len() > len() ) return false;

        ssize_type pos = size() - _suffix_.size();

        if( !uti::is_constant_evaluated() && data() + pos == _suffix_.data() )
        {
                return true;
        }
        for( ssize_type i = 0; i < _suffix_.size(); ++i )
        {
                if( to_lower( at( pos + i ) ) != to_lower( _suffix_.at( i ) ) )
                {
                        return false;
                }
        }
        return true;
}

template< typename CharType >
constexpr typename string_view< CharType >::ssize_type
string_view< CharType >::trim () noexcept
{
        ssize_type count { 0 } ;
        count += trim_left();
        count += trim_right();
        return count;
}

template< typename CharType >
constexpr typename string_view< CharType >::ssize_type
string_view< CharType >::trim_left () noexcept
{
        ssize_type count { 0 } ;
        while( !empty() && ( front() ==  ' ' || front() == '\t' ) )
        {
                data_++;
                size_--;
                count++;
        }
        return count;
}

template< typename CharType >
constexpr typename string_view< CharType >::ssize_type
string_view< CharType >::trim_right () noexcept
{
        ssize_type count { 0 } ;
        while( !empty() && ( back() ==  ' ' || back() == '\t' ) )
        {
                size_--;
                count++;
        }
        return count;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::trimmed () const noexcept
{
        return trimmed_right().trimmed_left();
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::trimmed_left () const noexcept
{
        string_view new_view( *this );

        new_view.trim_left();

        return new_view;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::trimmed_right () const noexcept
{
        string_view new_view( *this );

        new_view.trim_right();

        return new_view;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::substr ( ssize_type const _start_, ssize_type const _len_ ) const noexcept
{
        string_view sub( *this );

        ( void ) sub.chop_left( _start_ );

        if( _len_ < sub.len() )
        {
                sub.size_ = _len_;
        }
        return sub;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_left ( ssize_type _count_ ) noexcept
{
        if( _count_ > size() ) _count_ = size();

        string_view chop( data_, _count_ );

        data_ += _count_ ;
        size_ -= _count_ ;

        return chop;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_right ( ssize_type _count_ ) noexcept
{
        if( _count_ > size() ) _count_ = size();

        string_view chop( &data_[ size() - _count_ ], _count_ );

        size_ -= _count_ ;

        return chop;
}

template< typename CharType >
constexpr void
string_view< CharType >::unchop_left ( ssize_type _count_ ) noexcept
{
        data_ -= _count_ ;
        size_ += _count_ ;
}

template< typename CharType >
constexpr void
string_view< CharType >::unchop_right ( ssize_type _count_ ) noexcept
{
        size_ += _count_ ;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_to_first_of ( string_view const & _delims_, bool const _discard_delimiter_ ) noexcept
{
        string_view chop( data_, 0 );

        while( !empty() && !_delims_.contains( front() ) )
        {
                data_++;
                size_--;
                chop.size_++;
        }
        if( !empty() && _discard_delimiter_ )
        {
                data_++;
                size_--;
        }
        return chop;
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::value_type
string_view< CharType >::chop_char_left () noexcept
{
        UTI_CEXPR_ASSERT( !empty(), "uti::string_view::chop_char_left: called on empty string_view" );

        size_--;

        return ( data_++ )[ 0 ];
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::value_type
string_view< CharType >::chop_char_right () noexcept
{
        UTI_CEXPR_ASSERT( !empty(), "uti::string_view::chop_char_right: called on empty string_view" );

        return data_[ --size_ ];
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::ssize_type
string_view< CharType >::index_of ( value_type const & _val_, ssize_type const start ) const noexcept
{
        for( auto i = start; i < size(); ++i )
        {
                if( at( i ) == _val_ )
                {
                        return i;
                }
        }
        return -1;
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::ssize_type
string_view< CharType >::index_of ( string_view const & _val_, ssize_type const start ) const noexcept
{
        string_view window( data_ + start, _val_.size() );

        bool found =  false ;
        ssize_type pos{ start } ;

        while( pos < size() - _val_.size() )
        {
                if( window.equal_to( _val_ ) )
                {
                        found = true;
                        break;
                }
                pos++;
                window.data_++;
        }
        if( found )
        {
                return pos;
        }
        return -1;
}

template< typename CharType >
[[ nodiscard ]] constexpr bool
string_view< CharType >::contains ( value_type const & _val_ ) const noexcept
{
        return index_of( _val_, 0 ) >= 0;
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::ssize_type
string_view< CharType >::count ( value_type const & _val_ ) const noexcept
{
        ssize_type count{ 0 } ;

        for( auto const & val : *this )
        {
                if( val == _val_ )
                {
                        ++count;
                }
        }
        return count;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_to_delimiter ( value_type const & _delimiter_, bool _discard_delimiter_ ) noexcept
{
        string_view chop( data_, 0 );

        while( !empty() && data_[ 0 ] != _delimiter_ )
        {
                data_++;
                size_--;
                chop.size_++;
        }
        if( !empty() && _discard_delimiter_ )
        {
                data_++;
                size_--;
        }
        return chop;
}

template< typename CharType >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_to_string ( string_view const & _delimiter_, bool _discard_delimiter_ ) noexcept
{
        string_view window( data_, _delimiter_.size() );

        bool found = false ;
        ssize_type pos( 0 );

        while( pos < size() - _delimiter_.size() )
        {
                if( window.equal_to( _delimiter_ ) )
                {
                        found = true;
                        break;
                }
                pos++;
                window.data_++;
        }
        if( found )
        {
                string_view chop( data_, pos );
                data_ += pos;
                size_ -= pos;
                if( _discard_delimiter_ )
                {
                        data_ += _delimiter_.size();
                        size_ -= _delimiter_.size();
                }
                return chop;
        }
        string_view chop( *this );
        this->data_ = nullptr ;
        this->size_ =       0 ;
        return chop;
}

template< typename CharType >
template< typename Predicate >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_left_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) )
{
        string_view chop( data_, 0 );

        while( !empty() && _predicate_( front() ) )
        {
                data_++;
                size_--;
                chop++ ;
        }
        return chop;
}

template< typename CharType >
template< typename Predicate >
[[ nodiscard ]] constexpr string_view< CharType >
string_view< CharType >::chop_right_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) )
{
        string_view chop( end(), 0 );

        while( !empty() && _predicate_( back() ) )
        {
                size_--;
                ++chop ;
        }
        return chop;
}

template< typename CharType >
template< typename Integer >
[[ nodiscard ]] constexpr Integer
string_view< CharType >::parse_int () const noexcept
{
        Integer num { 0 } ;
        for( auto const & digit : *this )
        {
                if( '0' <= digit && digit <= '9' )
                {
                        num *= 10;
                        num += digit - 48;
                }
                else break;
        }
        return num;
}

template< typename CharType >
template< typename Float >
[[ nodiscard ]] constexpr Float
string_view< CharType >::parse_float () const noexcept
{
        return Float{ 0 };
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::reference
string_view< CharType >::at ( ssize_type const _index_ ) noexcept
{
        UTI_CEXPR_ASSERT( !empty() && 0 <= _index_ && _index_ < size(), "uti::string_view::at: index out of bounds" );

        return data_[ _index_ ];
}

template< typename CharType >
[[ nodiscard ]] constexpr typename string_view< CharType >::const_reference
string_view< CharType >::at ( ssize_type const _index_ ) const noexcept
{
        UTI_CEXPR_ASSERT( !empty() && 0 <= _index_ && _index_ < size(), "uti::string_view::at: index out of bounds" );

        return data_[ _index_ ];
}


} // namespace uti
