//
//
//      uti
//      string_view.hpp
//

#pragma once

#ifndef UTI_MOVE
#define UTI_MOVE(...) \
        static_cast< decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int) (sv).size(), (sv).data()


namespace uti
{


struct string_view
{
        using value_type =    char const ;
        using  size_type = unsigned long ;
        using ssize_type =     long long ;

        using         pointer = value_type       * ;
        using   const_pointer = value_type const * ;
        using       reference = value_type       & ;
        using const_reference = value_type const & ;

        using       iterator =       pointer ;
        using const_iterator = const_pointer ;

        constexpr string_view (                                          ) noexcept ;
        constexpr string_view ( value_type * _c_str_                     ) noexcept ;
        constexpr string_view ( value_type *  _data_, ssize_type _count_ ) noexcept ;

        constexpr string_view ( string_view const &  _other_ ) noexcept ;
        constexpr string_view ( string_view       && _other_ ) noexcept ;

        constexpr string_view & operator= ( string_view const &  _other_ ) noexcept ;
        constexpr string_view & operator= ( string_view       && _other_ ) noexcept ;

        constexpr       reference operator[] ( ssize_type const _index_ )       noexcept { return data_[ _index_ ]; }
        constexpr const_reference operator[] ( ssize_type const _index_ ) const noexcept { return data_[ _index_ ]; }

        constexpr bool operator== ( string_view const & _other_ ) const noexcept { return data_ == _other_.data_ && size_ == _other_.size_; }
        constexpr bool operator!= ( string_view const & _other_ ) const noexcept { return !operator==( _other_ ); }

        constexpr ssize_type operator++ (     ) noexcept { data_--; return ++size_; } // extends view on left  side
        constexpr ssize_type operator++ ( int ) noexcept { return ++size_; }          // extends view on right side

        constexpr ssize_type operator-- (     ) noexcept { data_++; return --size_; } // shrinks view on left  side
        constexpr ssize_type operator-- ( int ) noexcept { return --size_; }          // shrinks view on right side

        constexpr bool equal_to ( string_view const & _other_ ) const noexcept ;

        constexpr bool starts_with ( string_view const & _prefix_ ) const noexcept ;
        constexpr bool   ends_with ( string_view const & _suffix_ ) const noexcept ;

        constexpr void trim       () noexcept ;
        constexpr void trim_left  () noexcept ;
        constexpr void trim_right () noexcept ;

        constexpr string_view trimmed       () noexcept ;
        constexpr string_view trimmed_left  () noexcept ;
        constexpr string_view trimmed_right () noexcept ;

        constexpr string_view chop_left  ( ssize_type _count_ ) noexcept ;
        constexpr string_view chop_right ( ssize_type _count_ ) noexcept ;

        constexpr void unchop_left  ( ssize_type _count_ ) noexcept ;
        constexpr void unchop_right ( ssize_type _count_ ) noexcept ;

        constexpr value_type chop_char_left  () noexcept ;
        constexpr value_type chop_char_right () noexcept ;

        constexpr ssize_type index_of ( value_type const  & _val_, ssize_type const start = 0 ) const noexcept ;
        constexpr ssize_type index_of ( string_view const & _val_, ssize_type const start = 0 ) const noexcept ;

        constexpr string_view chop_to_delimiter ( value_type  const & _delimiter_, bool _discard_delimiter_ = true ) noexcept ;
        constexpr string_view chop_to_string    ( string_view const & _delimiter_, bool _discard_delimiter_ = true ) noexcept ;

        template< typename Predicate >
        constexpr string_view chop_left_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) ) ;

        template< typename Predicate >
        constexpr string_view chop_right_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) ) ;

        constexpr       reference at ( ssize_type const _index_ )       noexcept ;
        constexpr const_reference at ( ssize_type const _index_ ) const noexcept ;

        constexpr ssize_type size () const noexcept { return size_; }
        constexpr ssize_type  len () const noexcept { return size_; }

        constexpr       pointer data ()       noexcept { return data_; }
        constexpr const_pointer data () const noexcept { return data_; }

        constexpr bool empty () const noexcept { return data_ == nullptr || size_ == 0; }

        constexpr       iterator  begin ()       noexcept { return   data_; }
        constexpr const_iterator  begin () const noexcept { return   data_; }
        constexpr const_iterator cbegin () const noexcept { return begin(); }

        constexpr       iterator  last ()       noexcept { return &data_[ size_ - 1 ]; }
        constexpr const_iterator  last () const noexcept { return &data_[ size_ - 1 ]; }
        constexpr const_iterator clast () const noexcept { return              last(); }

        constexpr       iterator  end ()       noexcept { return &data_[ size_ ]; }
        constexpr const_iterator  end () const noexcept { return &data_[ size_ ]; }
        constexpr const_iterator cend () const noexcept { return           end(); }

        constexpr       reference  front ()       noexcept { return *begin(); }
        constexpr const_reference  front () const noexcept { return *begin(); }
        constexpr const_reference cfront () const noexcept { return  front(); }

        constexpr       reference  back ()       noexcept { return *last(); }
        constexpr const_reference  back () const noexcept { return *last(); }
        constexpr const_reference cback () const noexcept { return  back(); }
private:
        pointer    data_ ;
        ssize_type size_ ;
};


// template< typename CharType >
// string_view ( CharType const * _c_str_ ) -> string_view< CharType const > ;


#ifdef STRING_VIEW_IMPLEMENTATION


template< typename CharType >
constexpr long strlen ( CharType const * str )
{
        long len = -1;
        while( str[ ++len ] != '\0' ) {}
        return len;
}


constexpr string_view::string_view () noexcept
        : data_( nullptr ),
          size_(       0 )
{}

constexpr string_view::string_view ( value_type * _c_str_ ) noexcept
        : data_(         _c_str_   ),
          size_( strlen( _c_str_ ) )
{}

constexpr string_view::string_view ( value_type * _data_, ssize_type _count_ ) noexcept
        : data_(  _data_ ),
          size_( _count_ )
{}

constexpr string_view::string_view ( string_view const & _other_ ) noexcept
        : data_( _other_.data_ ),
          size_( _other_.size_ )
{}

constexpr string_view::string_view ( string_view && _other_ ) noexcept
        : data_( UTI_MOVE( _other_.data_ ) ),
          size_( UTI_MOVE( _other_.size_ ) )
{
        _other_.data_ = nullptr ;
        _other_.size_ =       0 ;
}

constexpr string_view &
string_view::operator= ( string_view const & _other_ ) noexcept
{
        data_ = _other_.data_ ;
        size_ = _other_.size_ ;

        return *this;
}

constexpr string_view &
string_view::operator= ( string_view && _other_ ) noexcept
{
        data_ = UTI_MOVE( _other_.data_ ) ;
        size_ = UTI_MOVE( _other_.size_ ) ;

        _other_.data_ = nullptr ;
        _other_.size_ =       0 ;

        return *this;
}

constexpr bool
string_view::equal_to ( string_view const & _other_ ) const noexcept
{
        if( size() != _other_.size() )
        {
                return false;
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

constexpr bool
string_view::starts_with ( string_view const & _prefix_ ) const noexcept
{
//      UTI_CONSTEXPR_ASSERT( size() >= _prefix_.size(), "string_view::starts_with: prefix longer than string" );

        for( ssize_type i = 0; i < _prefix_.size(); ++i )
        {
                if( at( i ) != _prefix_.at( i ) )
                {
                        return false;
                }
        }
        return true;
}

constexpr bool
string_view::ends_with ( string_view const & _suffix_ ) const noexcept
{
//      UTI_CONSTEXPR_ASSERT( size() >= _suffix_.size(), "string_view::ends_with: suffix longer than string" );

        ssize_type pos = size() - _suffix_.size();

        for( ssize_type i = 0; i < _suffix_.size(); ++i )
        {
                if( at( pos + i ) != _suffix_.at( i ) )
                {
                        return false;
                }
        }
        return true;
}

constexpr void
string_view::trim () noexcept
{
        trim_left();
        trim_right();
}

constexpr void
string_view::trim_left () noexcept
{
        while( ( front() ==  ' ' || front() == '\t' ) && !empty() )
        {
                data_++;
                size_--;
        }
}

constexpr void
string_view::trim_right () noexcept
{
        while( ( back() ==  ' ' || back() == '\t' ) && !empty() )
        {
                size_--;
        }
}

constexpr string_view
string_view::trimmed () noexcept
{
        return trimmed_right().trimmed_left();
}

constexpr string_view
string_view::trimmed_left () noexcept
{
        string_view new_view( *this );

        new_view.trim_left();

        return new_view;
}

constexpr string_view
string_view::trimmed_right () noexcept
{
        string_view new_view( *this );

        new_view.trim_right();

        return new_view;
}

constexpr string_view
string_view::chop_left ( ssize_type _count_ ) noexcept
{
        if( _count_ > size() ) _count_ = size();

        string_view chop( data_, _count_ );

        data_ += _count_ ;
        size_ -= _count_ ;

        return chop;
}

constexpr string_view
string_view::chop_right ( ssize_type _count_ ) noexcept
{
        if( _count_ > size() ) _count_ = size();

        string_view chop( &data_[ size() - _count_ ], _count_ );

        size_ -= _count_ ;

        return chop;
}

constexpr void
string_view::unchop_left ( ssize_type _count_ ) noexcept
{
        data_ -= _count_ ;
        size_ += _count_ ;
}

constexpr void
string_view::unchop_right ( ssize_type _count_ ) noexcept
{
        size_ += _count_ ;
}

constexpr string_view::value_type
string_view::chop_char_left () noexcept
{
        // assert !empty()

        size_--;

        return ( data_++ )[ 0 ];
}

constexpr string_view::value_type
string_view::chop_char_right () noexcept
{
        // assert !empty()

        return data_[ --size_ ];
}

constexpr typename string_view::ssize_type
string_view::index_of ( value_type const & _val_, ssize_type const start ) const noexcept
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

constexpr typename string_view::ssize_type
string_view::index_of ( string_view const & _val_, ssize_type const start ) const noexcept
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

constexpr string_view
string_view::chop_to_delimiter ( value_type const & _delimiter_, bool _discard_delimiter_ ) noexcept
{
        string_view chop( data_, 0 );

        while( data_[ 0 ] != _delimiter_ && !empty() )
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

constexpr string_view
string_view::chop_to_string ( string_view const & _delimiter_, bool _discard_delimiter_ ) noexcept
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
        string_view ret = UTI_MOVE( *this );
        this->data_ = nullptr ;
        this->size_ =       0 ;
        return ret;
}

template< typename Predicate >
constexpr string_view
string_view::chop_left_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) )
{
        string_view chop( data_, 0 );

        while( _predicate_( front() ) && !empty() )
        {
                data_++;
                size_--;
                chop.size_++;
        }
        return chop;
}

template< typename Predicate >
constexpr string_view
string_view::chop_right_while ( Predicate _predicate_ ) noexcept( noexcept( _predicate_( value_type() ) ) )
{
        string_view chop( end(), 0 );

        while( _predicate_( back() ) && !empty() )
        {
                size_--;
                chop.data_--;
                chop.size_++;
        }
        return chop;
}

constexpr typename string_view::reference
string_view::at ( ssize_type const _index_ ) noexcept
{
//      UTI_CONSTEXPR_ASSERT( !empty() && _index_ >= 0 && _index_ < size(), "string_view::at: index out of bounds" );

        return data_[ _index_ ];
}

constexpr typename string_view::const_reference
string_view::at ( ssize_type const _index_ ) const noexcept
{
//      UTI_CONSTEXPR_ASSERT( !empty() && _index_ >= 0 && _index_ < size(), "string_view::at: index out of bounds" );

        return data_[ _index_ ];
}


#endif


} // namespace uti
