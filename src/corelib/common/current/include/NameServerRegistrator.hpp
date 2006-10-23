/***************************************************************************
  tag: Peter Soetens  Thu Oct 10 16:16:57 CEST 2002  NameServerRegistrator.hpp 

                        NameServerRegistrator.hpp -  description
                           -------------------
    begin                : Thu October 10 2002
    copyright            : (C) 2002 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/ 
 
#ifndef NAMESERVERREGISTRATION_HPP
#define NAMESERVERREGISTRATION_HPP

#include "NameServer.hpp"
#include <boost/call_traits.hpp> 
namespace RTT
{

    /**
     * @brief Utility class to register a given object with a nameserver, and deregister upon destruction.
     *
     * Usage: you inherit from this class, and call it's constructor in your classes constructor,
     * then your object will be registered with the nameserver you specify, and will unregister the object on destruction.
     *
     * @param T the class you wish to contain in the nameserver
     */
    template <class T>
    class NameServerRegistrator
    {
        typedef std::string NameType;
        // to hold a reference to the nameserver
        // call_traits< NameServer<T> >::reference _nameserver;
        NameServer<T>* _nameserver;
        
        // to hold the name
        NameType _name;
        
    public:
        NameServerRegistrator()
            : _nameserver( 0 )
        {}

        NameServerRegistrator( typename boost::call_traits< NameServer< T > >::reference nameserver, const NameType& name,
                               typename boost::call_traits<T>::const_reference object )
            : _nameserver( &nameserver ), _name( name )
        {
            _nameserver->registerObject( object, _name );
        }

        ~NameServerRegistrator()
        {
            if ( _nameserver != 0 )
                _nameserver->unregisterName( _name );
        }
    };

}

#endif // NAMESERVERREGISTRATION_HPP