#ifndef __tc_timestamp_h__
#define __tc_timestamp_h__

#include <tc.common/tc.hpp>
#include <tc.common/timespan.hpp>

namespace tc {

    class timespan;
    /*!
     *  \class timestamp
     *  \brief 
	 *  based on 1970/1/1 00:00:00 
	 *  microseconds / utc
     */
    class timestamp {
    public:
		//! from tick
        explicit timestamp(const s64 tick = 0 );
		//! copy construct
        timestamp( const timestamp& rhs );
		//! assign
        timestamp& operator=( const timestamp& rhs );
		//! to tick
        s64 tick( void ) const;
        
        bool operator==( const timestamp& rhs ) const;
        bool operator!=( const timestamp& rhs ) const;
        bool operator> ( const timestamp& rhs ) const;
        bool operator>=( const timestamp& rhs ) const;
        bool operator< ( const timestamp& rhs ) const;
        bool operator<=( const timestamp& rhs ) const;

        timestamp operator+( const timespan& rhs ) const;
        timestamp operator-( const timespan& rhs ) const;
        timestamp& operator+=( const timespan& rhs ) ;
        timestamp& operator-=( const timespan& rhs ) ;

        timespan  operator-( const timestamp& rhs ) const;
        
        static timestamp now( void );
    private:
		s64 _tick;
    };

}

#endif
